/* Opt-in native race placement and telemetry boundary.
 *
 * None of this code belongs to the retail Sim_MainGameLoop MIPS body.  Keep
 * the two calls from that function tiny and put all observation-only state in
 * this host translation unit so it cannot alter the recovered stack frame or
 * inject signed-C++ arithmetic into the simulation loop. */
#include "../nfs4_types.h"
#include "../mips_semantics.h"
#if NFSHS_DIAGNOSTICS
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" int random(void);

static unsigned long host_environment_get(const char *name, char *buffer, size_t capacity)
{
    const char *value = getenv(name);
    size_t length;
    if (value == 0)
        return 0;
    length = strlen(value);
    if (capacity != 0)
    {
        size_t copied = length < capacity - 1 ? length : capacity - 1;
        memcpy(buffer, value, copied);
        buffer[copied] = 0;
    }
    return (unsigned long)length;
}

#define GetEnvironmentVariableA host_environment_get
#define ExitProcess(code) exit((int)(code))

extern "C" void NFSHS_HostLog(const char *, ...);
extern "C" void NFSHS_HostRaceStart(Car_tObj *playerCar);
extern "C" unsigned int NFSHS_HostPSXRandSeed(void);

extern Car_tObj *Cars_gHumanRaceCarList[9];
extern Car_tObj *Cars_gList[9];
extern Car_tObj *Cars_gTrafficCarList[9];
extern int Cars_gNumTrafficCars;
extern u_int fastRandom;
extern u_int randSeed;
extern "C" extern GameSetup_tData GameSetup_gData;
extern "C" extern tfrontEnd frontEnd;
extern "C" Sim_tSimGlobalVar simGlobal;
extern "C" tPadModuleState gPadinfo;
extern int Input_gHandler[184];
extern Input_tResults Input_gResults[2];
extern Input_tResults Input_gSim;
extern Trk_NewSlice *BWorldSm_slices;
extern int gNumSlices;
extern int SceneLoaded;
extern int Object_customSliceNum;

static Car_tObj *hostCar;
static int hostStartX;
static int hostStartY;
static int hostStartZ;
static int hostTelemetryTick;
static int hostMoved;
static int hostCollided;

/* Test input for the sound subsystem we intentionally do not run. Restore the
   captured initial EAC state ONCE; then execute only the observed audio calls.
   Every ordinary game's random call must match its observed tick and all six
   state words, or the replay fails. No per-frame/particle state replacement. */
extern "C" void NFSHS_HostEacAudioReplay(unsigned *state)
{
    static int fd=-2, active, initialized;
    static unsigned initialTick, endTick, remaining, initial[6];
    if(active) return;
    if(fd==-2) {
        char path[260];
        unsigned length=GetEnvironmentVariableA("NFSHS_EAC_AUDIO_REPLAY",path,sizeof(path));
        fd=-1;
        if(length && length<sizeof(path)) {
            fd=_open(path,_O_RDONLY|_O_BINARY);
            unsigned header[4];
            if(fd<0 || _read(fd,header,16)!=16 || header[0]!=0x31434145U ||
               _read(fd,initial,24)!=24) {
                NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("EAC_REPLAY invalid fixture"));
                ExitProcess(93);
            }
            initialTick=header[1]; remaining=header[2]; endTick=header[3];
        }
    }
    if(fd<0 || simGlobal.gameTicks<(int)initialTick || simGlobal.gameTicks>(int)endTick) return;
    if(!initialized) {
        memcpy(state,initial,24);
        initialized=1;
    }
    unsigned record[8];
    if(!remaining || _read(fd,record,sizeof(record))!=sizeof(record) ||
       record[0]!=(unsigned)simGlobal.gameTicks) {
        NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("EAC_REPLAY call mismatch tick=%d remaining=%u",simGlobal.gameTicks,remaining));
        ExitProcess(93);
    }
    active=1;
    for(unsigned i=0;i<record[1];i++) random();
    active=0;
    if(memcmp(state,record+2,24)) {
        NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("EAC_REPLAY state mismatch tick=%d remaining=%u",simGlobal.gameTicks,remaining));
        ExitProcess(93);
    }
    --remaining;
    if(!remaining) NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("EAC_REPLAY all non-audio calls verified"));
}

#ifdef AP_WIN
enum { HOST_STATE_TRACE_VERSION=1, HOST_STATE_TRACE_TRAFFIC_SLOTS=9 };
struct HostStateTraceHeader {
    char magic[8];
    unsigned int version, carSize, trafficSlots, recordSize;
};
static int hostStateTraceFd=-2;
static unsigned int hostStateTraceEnd=0x7fffffffU;

static void host_write_all(int fd,const void *data,unsigned int size)
{
    const unsigned char *bytes=(const unsigned char *)data;
    while(size) {
        int written=_write(fd,bytes,size);
        if(written<=0) return;
        bytes+=written;
        size-=(unsigned int)written;
    }
}

static void host_trace_car(Car_tObj *car)
{
    static const unsigned char zeroCar[sizeof(Car_tObj)]={0};
    unsigned int present=car!=0;
    host_write_all(hostStateTraceFd,&present,sizeof(present));
    host_write_all(hostStateTraceFd,car ? (const void *)car : (const void *)zeroCar,
                   sizeof(Car_tObj));
}

/* Observation at the same Camera_SetCamera boundary as the PSX capture.
   Phase 0 precedes GetViewInfo; phase 1 includes wall/ground correction. */
extern camera_info Camera_gInfo[2];
extern long Camera_gGeomScreen[2];
extern "C" void NFSHS_HostTraceCamera(int player,int view,int phase,const void *camera,const void *calcView)
{
    static int fd=-2;
    if(fd==-2) {
        char path[260];fd=-1;
        unsigned len=GetEnvironmentVariableA("NFSHS_CAMERA_TRACE",path,sizeof(path));
        if(len && len<sizeof(path)) {
            fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
            if(fd<0)ExitProcess(95);
            unsigned header[4]={0x4d41434e,1,sizeof(camera_info),sizeof(DRender_tCalcView)};
            host_write_all(fd,header,sizeof(header));
        }
    }
    if(fd<0)return;
    int header[5]={simGlobal.gameTicks,player,view,phase,(int)Camera_gGeomScreen[player]};
    host_write_all(fd,header,sizeof(header));
    host_write_all(fd,camera,sizeof(camera_info));
    host_write_all(fd,calcView,sizeof(DRender_tCalcView));
}

/* Test-only interface event boundary. The original demo's mode/counter
   transition identifies the pre-simulation tick of each next-camera press.
   Replay the button action, never camera coordinates/matrices/mode values.
   Use a companion PAD fixture with Triangle masked to prevent double input. */
extern void Camera_NextMode(int);
extern "C" void NFSHS_HostReplayCameraButton(void)
{
    static int initialized,count,next;
    static int ticks[256];
    if(!initialized) {
        initialized=1;char path[260];
        unsigned len=GetEnvironmentVariableA("NFSHS_CAMERA_BUTTON_EVENTS",path,sizeof(path));
        if(len && len<sizeof(path)) {
            FILE *f=fopen(path,"r");if(!f)ExitProcess(96);
            int tick;
            while(fscanf(f,"%d",&tick)==1) {
                if(count==256 || tick<0 || (count && tick<=ticks[count-1]))ExitProcess(96);
                ticks[count++]=tick;
            }
            if(!feof(f))ExitProcess(96);
            fclose(f);
        }
    }
    if(next<count && simGlobal.gameTicks==ticks[next]) {
        Camera_NextMode(0);++next;
        NFSHS_HostLog("CAMERA_BUTTON tick=%d event=%d/%d",simGlobal.gameTicks,next,count);
    }
}

static void host_trace_state_tick(void)
{
    if(hostStateTraceFd==-2) {
        char path[260];
        char endTick[32];
        unsigned long endLength=GetEnvironmentVariableA("NFSHS_STATE_TRACE_END",endTick,sizeof(endTick));
        if(endLength && endLength<sizeof(endTick)) {
            hostStateTraceEnd=0;
            for(unsigned long i=0;i<endLength && endTick[i]>='0' && endTick[i]<='9';++i)
                hostStateTraceEnd=hostStateTraceEnd*10+(unsigned int)(endTick[i]-'0');
        }
        unsigned long length=GetEnvironmentVariableA("NFSHS_STATE_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) {
            hostStateTraceFd=-1;
            return;
        }
        if(length==1 && path[0]=='1') strcpy(path,"nfshs-state-trace.bin");
        hostStateTraceFd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,
                               0666);
        if(hostStateTraceFd>=0) {
            HostStateTraceHeader header={{'N','4','S','T','A','T','E','\0'},
                HOST_STATE_TRACE_VERSION,sizeof(Car_tObj),HOST_STATE_TRACE_TRAFFIC_SLOTS,
                (unsigned int)(4*4+(1+HOST_STATE_TRACE_TRAFFIC_SLOTS)*(4+sizeof(Car_tObj)))};
            host_write_all(hostStateTraceFd,&header,sizeof(header));
            NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("STATE_TRACE opened path=%s carSize=%u recordSize=%u",
                          path,header.carSize,header.recordSize));
        }
    }
    if(hostStateTraceFd<0) return;
    int tick=simGlobal.gameTicks;
    if(tick>=0 && (unsigned int)tick>hostStateTraceEnd) return;
    unsigned int randomState[2]={fastRandom,randSeed};
    int trafficCount=Cars_gNumTrafficCars;
    if(trafficCount<0) trafficCount=0;
    if(trafficCount>HOST_STATE_TRACE_TRAFFIC_SLOTS)
        trafficCount=HOST_STATE_TRACE_TRAFFIC_SLOTS;
    host_write_all(hostStateTraceFd,&tick,sizeof(tick));
    host_write_all(hostStateTraceFd,randomState,sizeof(randomState));
    host_write_all(hostStateTraceFd,&trafficCount,sizeof(trafficCount));
    host_trace_car(hostCar);
    for(int index=0;index<HOST_STATE_TRACE_TRAFFIC_SLOTS;++index)
        host_trace_car(index<trafficCount ? Cars_gTrafficCarList[index] : (Car_tObj *)0);
}
#endif


extern "C" void NFSHS_HostRaceBoundaryStart(void)
{
    hostCar=Cars_gHumanRaceCarList[0];
    if(hostCar==(Car_tObj *)0) hostCar=Cars_gList[0];
    NFSHS_HostRaceStart(hostCar);

    hostStartX=hostStartY=hostStartZ=0;
    hostTelemetryTick=-1;
    hostMoved=0;
    hostCollided=0;
    if(hostCar) {
        hostStartX=hostCar->N.position.x;
        hostStartY=hostCar->N.position.y;
        hostStartZ=hostCar->N.position.z;
    }
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_RACE_LOOP car=%p list0=%p human0=%p index=%d start=(%d,%d,%d)",
                  hostCar,Cars_gList[0],Cars_gHumanRaceCarList[0],
                  hostCar?hostCar->carIndex:-1,hostStartX,hostStartY,hostStartZ));
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_INPUT_SETUP config=(%d,%d) pad=(id=%u,nopad=%u) handlers=%08x,%08x,%08x,%08x,%08x,%08x",
                  GameSetup_gData.controllerData.controllerConfig[0],
                  GameSetup_gData.controllerData.controllerConfig[1],
                  (unsigned)gPadinfo.buf[0].ID,(unsigned)gPadinfo.buf[0].nopad,
                  Input_gHandler[0],Input_gHandler[1],Input_gHandler[2],
                  Input_gHandler[3],Input_gHandler[4],Input_gHandler[5]));
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_SETUP race=%d laps=%d track=%d traffic=%d seed=%d scene=%d/%d/%d loaded=%d customSlice=%d playerLap=%d crtSeed=%08x fe=(track=%u laps=%u traffic=%u list=%u opp=%u)",
                  GameSetup_gData.raceType,GameSetup_gData.numLaps,
                  GameSetup_gData.track,GameSetup_gData.trafficDensity,
                  GameSetup_gData.randSeed,GameSetup_gData.SceneNumber,
                  GameSetup_gData.SceneStartLap,GameSetup_gData.SceneEndLap,
                  SceneLoaded,Object_customSliceNum,
                  hostCar ? *(int *)((char *)hostCar+0x360) : -1,
                  NFSHS_HostPSXRandSeed(),
                  (unsigned char)frontEnd.track[0],(unsigned char)frontEnd.laps,
                  (unsigned char)frontEnd.traffic[0],
                  (unsigned char)frontEnd.carListType,
                  (unsigned char)frontEnd.oppNumber));
}

extern "C" void NFSHS_HostRaceBoundaryTick(void)
{
#ifdef AP_WIN
    host_trace_state_tick();
#endif
    if(!hostCar) return;

    int hostDx=nfs4_mips_subu_s32(hostCar->N.position.x,hostStartX);
    int hostDy=nfs4_mips_subu_s32(hostCar->N.position.y,hostStartY);
    int hostDz=nfs4_mips_subu_s32(hostCar->N.position.z,hostStartZ);
    if(!hostMoved &&
       (hostDx>0x10000 || hostDx<-0x10000 ||
        hostDy>0x10000 || hostDy<-0x10000 ||
        hostDz>0x10000 || hostDz<-0x10000)) {
        hostMoved=1;
        NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_MOVED tick=%d delta=(%d,%d,%d) speed=%d",
                      simGlobal.gameTicks,hostDx,hostDy,hostDz,hostCar->speed));
    }
    if(!hostCollided &&
       (hostCar->N.collision.collided!=0 ||
        hostCar->N.collision.impulse!=0 ||
        (hostCar->N.collision.lastTime>0 &&
         (unsigned int)(simGlobal.gameTicks-hostCar->N.collision.lastTime)<2U))) {
        hostCollided=1;
        NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_COLLISION tick=%d collided=%d impulse=%d lastImpulse=%d other=%p",
                      simGlobal.gameTicks,hostCar->N.collision.collided,
                      hostCar->N.collision.impulse,hostCar->N.collision.lastImpulse,
                      hostCar->N.collision.otherObj));
    }
    if(hostTelemetryTick>=0 &&
       (unsigned int)(simGlobal.gameTicks-hostTelemetryTick)<64U) return;
    hostTelemetryTick=simGlobal.gameTicks;

    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("ORIENT_STATE tick=%d orient=(%d,%d,%d;%d,%d,%d;%d,%d,%d) road=(%d,%d,%d;%d,%d,%d;%d,%d,%d) angvel=(%d,%d,%d) angacc=(%d,%d,%d)",
                  simGlobal.gameTicks,
                  hostCar->N.orientMat.m[0],hostCar->N.orientMat.m[1],hostCar->N.orientMat.m[2],
                  hostCar->N.orientMat.m[3],hostCar->N.orientMat.m[4],hostCar->N.orientMat.m[5],
                  hostCar->N.orientMat.m[6],hostCar->N.orientMat.m[7],hostCar->N.orientMat.m[8],
                  hostCar->N.roadMatrix.m[0],hostCar->N.roadMatrix.m[1],hostCar->N.roadMatrix.m[2],
                  hostCar->N.roadMatrix.m[3],hostCar->N.roadMatrix.m[4],hostCar->N.roadMatrix.m[5],
                  hostCar->N.roadMatrix.m[6],hostCar->N.roadMatrix.m[7],hostCar->N.roadMatrix.m[8],
                  hostCar->N.angularVel.x,hostCar->N.angularVel.y,hostCar->N.angularVel.z,
                  hostCar->angularAcc.x,hostCar->angularAcc.y,hostCar->angularAcc.z));
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("ROAD_QUADS tick=%d flags=(slice=%d quad=%d simrot=%d triangle=%d) q=(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)",
                  simGlobal.gameTicks,(int)hostCar->N.simRoadInfo.slice,
                  (int)hostCar->N.simRoadInfo.quad,(int)hostCar->N.simRoadInfo.simRotFlag,
                  (int)hostCar->N.simRoadInfo.triangleFlag,
                  hostCar->N.simRoadInfo.quadPts[0].x,hostCar->N.simRoadInfo.quadPts[0].y,hostCar->N.simRoadInfo.quadPts[0].z,
                  hostCar->N.simRoadInfo.quadPts[1].x,hostCar->N.simRoadInfo.quadPts[1].y,hostCar->N.simRoadInfo.quadPts[1].z,
                  hostCar->N.simRoadInfo.quadPts[2].x,hostCar->N.simRoadInfo.quadPts[2].y,hostCar->N.simRoadInfo.quadPts[2].z,
                  hostCar->N.simRoadInfo.quadPts[3].x,hostCar->N.simRoadInfo.quadPts[3].y,hostCar->N.simRoadInfo.quadPts[3].z));
    for(int wheelIndex=0;wheelIndex<4;++wheelIndex) {
        Car_tWheel *wheel=&hostCar->wheel[wheelIndex];
        NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("WHEEL_STATE tick=%d wheel=%d pos=(%d,%d,%d) normal=(%d,%d,%d) actual=%d acc=%d air=%d rebound=%d impact=%d surface=%d",
                      simGlobal.gameTicks,wheelIndex,
                      wheel->currentPos.x,wheel->currentPos.y,wheel->currentPos.z,
                      wheel->roadNormal.x,wheel->roadNormal.y,wheel->roadNormal.z,
                      wheel->actualHeight,wheel->wheelAcc,wheel->wheelInAir,
                      wheel->rebound,wheel->impactCompression,wheel->roadSurfaceType));
    }
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_STATE tick=%d started=%d finish=%d crash=%d gear=%d/%d rs=%d rpm=%d air=%d%d%d%d pos=(%d,%d,%d) vel=(%d,%d,%d) accCh=(%d,%d,%d) accWorld=(%d,%d,%d) shadowZ=(%d,%d,%d) speed=%d ground=(alt=%d,elev=%d,orient=%d,center=%d,q0=%d,slice=%d) input=(%d,%d,%d,%d) desired=(%d,%d) actual=(%d,%d) collision=%d impulse=%d",
                  simGlobal.gameTicks,simGlobal.gameStarted,(int)hostCar->stats.finishType,
                  (int)hostCar->crash,(int)hostCar->control.gear,
                  (int)hostCar->control.desiredGear,(int)hostCar->RSControl,
                  hostCar->flywheelRpm,
                  hostCar->wheel[0].wheelInAir,hostCar->wheel[1].wheelInAir,
                  hostCar->wheel[2].wheelInAir,hostCar->wheel[3].wheelInAir,
                  hostCar->N.position.x,hostCar->N.position.y,hostCar->N.position.z,
                  hostCar->N.linearVel.x,hostCar->N.linearVel.y,hostCar->N.linearVel.z,
                  hostCar->linearAcc_ch.x,hostCar->linearAcc_ch.y,hostCar->linearAcc_ch.z,
                  hostCar->linearAcc.x,hostCar->linearAcc.y,hostCar->linearAcc.z,
                  hostCar->N.shadowMat.m[2],hostCar->N.shadowMat.m[5],hostCar->N.shadowMat.m[8],
                  hostCar->speed,hostCar->N.objAltitude,hostCar->N.groundElevation,
                  hostCar->N.orientationToGround.y,hostCar->N.roadCenterPoint.y,
                  hostCar->N.simRoadInfo.quadPts[0].y,(int)hostCar->N.simRoadInfo.slice,
                  (int)Input_gResults[0].steering,(int)Input_gResults[0].gas,
                  (int)Input_gResults[0].brake,(int)Input_gSim.gas,
                  (int)hostCar->control.desiredGasLevel,(int)hostCar->control.desiredBrakeLevel,
                  (int)hostCar->control.gasLevel,(int)hostCar->control.brakeLevel,
                  hostCar->N.collision.collided,hostCar->N.collision.impulse));

    int slice=(int)hostCar->N.simRoadInfo.slice;
    if(BWorldSm_slices && slice>=0 && slice<gNumSlices) {
        int next=slice+1<gNumSlices?slice+1:0;
        NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_ROAD slice=%d right=(%d,%d,%d) normal=(%d,%d,%d) forward=(%d,%d,%d) centerDelta=(%d,%d,%d) orientZ=(%d,%d,%d)",
                      slice,
                      (int)BWorldSm_slices[slice].right[0],(int)BWorldSm_slices[slice].right[1],(int)BWorldSm_slices[slice].right[2],
                      (int)BWorldSm_slices[slice].normal[0],(int)BWorldSm_slices[slice].normal[1],(int)BWorldSm_slices[slice].normal[2],
                      (int)BWorldSm_slices[slice].forward[0],(int)BWorldSm_slices[slice].forward[1],(int)BWorldSm_slices[slice].forward[2],
                      nfs4_mips_subu_s32(BWorldSm_slices[next].center[0],BWorldSm_slices[slice].center[0]),
                      nfs4_mips_subu_s32(BWorldSm_slices[next].center[1],BWorldSm_slices[slice].center[1]),
                      nfs4_mips_subu_s32(BWorldSm_slices[next].center[2],BWorldSm_slices[slice].center[2]),
                      hostCar->N.orientMat.m[6],hostCar->N.orientMat.m[7],hostCar->N.orientMat.m[8]));
    }
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("AUTOTEST_MATS orient=(%d,%d,%d;%d,%d,%d;%d,%d,%d) shadow=(%d,%d,%d;%d,%d,%d;%d,%d,%d)",
                  hostCar->N.orientMat.m[0],hostCar->N.orientMat.m[1],hostCar->N.orientMat.m[2],
                  hostCar->N.orientMat.m[3],hostCar->N.orientMat.m[4],hostCar->N.orientMat.m[5],
                  hostCar->N.orientMat.m[6],hostCar->N.orientMat.m[7],hostCar->N.orientMat.m[8],
                  hostCar->N.shadowMat.m[0],hostCar->N.shadowMat.m[1],hostCar->N.shadowMat.m[2],
                  hostCar->N.shadowMat.m[3],hostCar->N.shadowMat.m[4],hostCar->N.shadowMat.m[5],
                  hostCar->N.shadowMat.m[6],hostCar->N.shadowMat.m[7],hostCar->N.shadowMat.m[8]));
}


#endif

extern "C" Sim_tSimGlobalVar simGlobal;
extern "C" int NFSHS_HostCurrentGameTicks(void)
{
    return simGlobal.gameTicks;
}
