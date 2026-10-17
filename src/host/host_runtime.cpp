/* Native host replacement for the PsyQ surface used by NFSHS.
 *
 * The shared xport platform owns the OS boundary. Game/frontend code is left untouched;
 * Video decoding, GPU commands and SPU state belong to the shared runtime
 */
#include "diagnostics.h"
#include "psx.h"
#include "psx_gpu.h"
#include "psx_gte.h"
#include "xport.h"
#include "psx_spu.h"
#include "psx_stream.h"
#include "../frontend/psx/video.h"
#include "../frontend/psx/movie.h"
#include "../eaclib/psx/pad.h"
#include "../eaclib/psx/eacpsxz/fileroot.h"
#include "../lib/nfile.h"
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#if defined(_MSC_VER)
#include <io.h>
#else
#include <unistd.h>
#define _close close
#define _dup dup
#define _fileno fileno
#define _lseek lseek
#define _open open
#define _read read
#define _write write
#define _O_BINARY 0
#define _O_CREAT O_CREAT
#define _O_RDONLY O_RDONLY
#define _O_RDWR O_RDWR
#define _O_TRUNC O_TRUNC
#define _O_WRONLY O_WRONLY
#define _S_IREAD S_IRUSR
#define _S_IWRITE S_IWUSR
#endif
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef uint32 DWORD;
typedef uint32 UINT;
enum { MAX_PATH = 260 };

static DWORD host_clock_millis(void)
{
    return (DWORD)(xport_timer_get() / 1000u);
}

static DWORD host_environment_get(const char *name, char *buffer, size_t capacity)
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
    return (DWORD)length;
}

#define GetEnvironmentVariableA host_environment_get
#define GetTickCount host_clock_millis
#define ExitProcess(code) exit((int)(code))

struct Car_tObj;
extern int gNumSlices;
void AILife_PlaceCarAtLocation(Car_tObj *,int,int,int,int,int);

static intptr g_host_packet_begin;
static intptr g_host_packet_end;
static intptr g_host_added_prims[16384];
#if NFSHS_DIAGNOSTICS
static intptr g_host_added_ots[16384];
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_added_callers[16384];
#endif
#if NFSHS_DIAGNOSTICS
static unsigned int g_host_added_links[16384];
#endif
static unsigned int g_host_added_generation[16384];
#if NFSHS_DIAGNOSTICS
static intptr g_host_prev_added_prims[16384];
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_prev_added_ots[16384];
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_prev_added_callers[16384];
#endif
#if NFSHS_DIAGNOSTICS
static unsigned int g_host_prev_added_generation[16384];
#endif
#if NFSHS_DIAGNOSTICS
static unsigned int g_host_prev_add_generation;
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_all_added_prims[32769];
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_all_added_ots[32769];
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_all_added_callers[32769];
#endif
static unsigned int g_host_add_generation;
#if NFSHS_DIAGNOSTICS
static intptr g_host_last_added_prim;
#endif
#if NFSHS_DIAGNOSTICS
static intptr g_host_last_added_end;
#endif
#if NFSHS_DIAGNOSTICS
static unsigned int g_host_packet_overlap_count;
#endif
#if NFSHS_DIAGNOSTICS
#endif
#if NFSHS_DIAGNOSTICS
static int g_host_dma_tag_fault_seen;
#endif
extern "C" void NFSHS_HostLog(const char *fmt);
struct HostOtRange { intptr begin, end; };
static HostOtRange g_host_ot_ranges[16];
static unsigned int g_host_ot_range_count;

#if NFSHS_DIAGNOSTICS
/* Diagnostic history may forget provenance, never stall gameplay.
   Index 32768 is a permanently empty sentinel for a full-table miss. */
static unsigned int host_history_slot(intptr key)
{
    unsigned int slot=((unsigned int)key>>2)&32767u;
    for(unsigned int n=0;n<32768;n++,slot=(slot+1)&32767u)
        if(!g_host_all_added_prims[slot] || g_host_all_added_prims[slot]==key)
            return slot;
    return 32768;
}
#endif

static void host_check_linked_tags(intptr observer)
{
#if NFSHS_DIAGNOSTICS

    if (g_host_dma_tag_fault_seen) return;
    for (unsigned int i=0; i<16384; ++i) {
        if (g_host_added_generation[i] != g_host_add_generation) continue;
        unsigned int actual=*(unsigned int *)g_host_added_prims[i]&0x00ffffffu;
        if (actual != g_host_added_links[i]) {
            g_host_dma_tag_fault_seen=1;
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "FIRST_DMA_TAG_MUTATION prim=%p owner=%p ot=%p expected=%06x actual=%06x observer=%p",
                (void*)g_host_added_prims[i],(void*)g_host_added_callers[i],
                (void*)g_host_added_ots[i],g_host_added_links[i],actual,(void*)observer); NFSHS_HostLog(nfshsLogLine); }()));
            return;
        }
    }

#else

#endif
}

static int g_window;
#if NFSHS_DIAGNOSTICS
static int g_host_log_fd = -2;
#endif
static unsigned short g_pad_buttons;
static char g_auto_sequence[256];
static int g_auto_initialized, g_auto_active, g_auto_index;
static DWORD g_auto_stage_start;
static int g_host_race_gas;
static int g_host_race_started;
static int g_host_fast_test = -1;
static int g_host_test_verbose = -1;
#if NFSHS_DIAGNOSTICS
/* Temporary deterministic-input harness.  The table is generated from the
 * raw digital-pad packets captured from DuckStation, not reconstructed from
 * steering/throttle observations. */
struct HostDuckReplayRun {
    unsigned short firstGameTick;
    unsigned short lastGameTick;
    unsigned short keys;
};
#include "duckstation_half_lap_input.inc"
static const HostDuckReplayRun *g_host_duck_replay_data=g_host_duck_replay_runs;
static unsigned g_host_duck_replay_count=sizeof(g_host_duck_replay_runs)/sizeof(g_host_duck_replay_runs[0]);
static HostDuckReplayRun g_host_duck_external_runs[4096];
static int g_host_duck_replay_initialized;
static int g_host_duck_replay_enabled;
static int g_host_duck_replay_finished;
static unsigned int g_host_duck_replay_run;
#endif
extern "C" void NFSHS_HostPadPoll(void);
extern "C" int NFSHS_HostCurrentGameTicks(void);
extern "C" int libticks;
extern "C" void NFSHS_HostLog(const char *fmt);
static void ensure_window(void);
static void pump_messages(void);
static void host_pump_audio(int forceFrame);

static int host_fast_test_enabled(void)
{
#if NFSHS_DIAGNOSTICS

    if (g_host_fast_test < 0) {
        char value[2];
        g_host_fast_test = GetEnvironmentVariableA("NFSHS_TEST_FAST",value,sizeof(value)) != 0;
    }
    return g_host_fast_test;

#else
return 0;
#endif
}

static int host_test_verbose_enabled(void)
{
#if NFSHS_DIAGNOSTICS

    if (g_host_test_verbose < 0) {
        char value[2];
        g_host_test_verbose = GetEnvironmentVariableA("NFSHS_TEST_VERBOSE",value,sizeof(value)) != 0;
    }
    return g_host_test_verbose;

#else
return 0;
#endif
}

/* Optional deterministic render schedule used only by OT replay tests.  The
 * listed ticks are direct DrawOTag observations from DuckStation.  Before the
 * first listed tick native startup/render history remains untouched. */
extern "C" int NFSHS_HostShouldRenderTick(int gameTick)
{
#if NFSHS_DIAGNOSTICS

    static int initialized;
    static int enabled;
    static int first_tick=0x7fffffff;
    static unsigned char ticks[65536];
    if (!initialized) {
        char path[MAX_PATH];
        initialized=1;
        if (GetEnvironmentVariableA("NFSHS_RENDER_TICKS",path,sizeof(path))) {
            int fd=_open(path,_O_RDONLY|_O_BINARY);
            if (fd>=0) {
                char buffer[4096];
                int value=0,have=0,count;
                while ((count=_read(fd,buffer,sizeof(buffer)))>0) {
                    for (int i=0;i<count;i++) {
                        unsigned char ch=(unsigned char)buffer[i];
                        if (ch>='0' && ch<='9') {
                            value=value*10+(ch-'0');
                            have=1;
                        } else if (have) {
                            if ((unsigned int)value<sizeof(ticks)) {
                                ticks[value]=1;
                                if (value<first_tick) first_tick=value;
                            }
                            value=0;
                            have=0;
                        }
                    }
                }
                if (have && (unsigned int)value<sizeof(ticks)) {
                    ticks[value]=1;
                    if (value<first_tick) first_tick=value;
                }
                _close(fd);
                enabled=first_tick!=0x7fffffff;
            }
        }
    }
    if (!enabled) return 1;
    if (gameTick<first_tick) return 1;
    return (unsigned int)gameTick<sizeof(ticks) && ticks[gameTick]!=0;

#else
return 1;
#endif
}

static int host_duck_replay_keys(int gameTick, unsigned short *keys)
{
#if NFSHS_DIAGNOSTICS

    if (!g_host_duck_replay_initialized) {
        char value[2];
        g_host_duck_replay_enabled =
            GetEnvironmentVariableA("NFSHS_DUCK_REPLAY",value,sizeof(value)) != 0;
        g_host_duck_replay_initialized = 1;
        char path[MAX_PATH];
        if(GetEnvironmentVariableA("NFSHS_DUCK_REPLAY_FILE",path,sizeof(path))) {
            FILE *file=fopen(path,"r");unsigned first,last,keys,count=0;
            if(!file)ExitProcess(94);
            while(fscanf(file,"%u %u %x",&first,&last,&keys)==3) {
                if(count>=4096 || first>last || last>65535 || keys>65535 ||
                   (count && first!=g_host_duck_external_runs[count-1].lastGameTick+1))ExitProcess(94);
                g_host_duck_external_runs[count].firstGameTick=(unsigned short)first;
                g_host_duck_external_runs[count].lastGameTick=(unsigned short)last;
                g_host_duck_external_runs[count++].keys=(unsigned short)keys;
            }
            if(!feof(file)||!count)ExitProcess(94);
            fclose(file);g_host_duck_replay_data=g_host_duck_external_runs;
            g_host_duck_replay_count=count;g_host_duck_replay_enabled=1;
        }
        if (g_host_duck_replay_enabled)
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "DUCK_REPLAY armed records=%d runs=%u ticks=%u..%u",
                          HOST_DUCK_REPLAY_SOURCE_RECORDS,
                          g_host_duck_replay_count,
                          (unsigned)g_host_duck_replay_data[0].firstGameTick,
                          (unsigned)g_host_duck_replay_data[g_host_duck_replay_count-1].lastGameTick); NFSHS_HostLog(nfshsLogLine); }()));
    }
    if (!g_host_duck_replay_enabled || !g_host_race_started) return 0;

    /* The capture is indexed by simGlobal.gameTicks (the original 64 Hz game
       clock), so repeated PAD polls in one tick must return the same packet. */
    if (gameTick < g_host_duck_replay_data[0].firstGameTick) {
        *keys = 0xffff;
        return 1;
    }
    while (g_host_duck_replay_run + 1 <
               g_host_duck_replay_count &&
           gameTick > g_host_duck_replay_data[g_host_duck_replay_run].lastGameTick)
        ++g_host_duck_replay_run;
    const HostDuckReplayRun *run=&g_host_duck_replay_data[g_host_duck_replay_run];
    if (gameTick <= run->lastGameTick) {
        *keys=run->keys;
    } else {
        *keys=0xffff;
        if (!g_host_duck_replay_finished) {
            g_host_duck_replay_finished=1;
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "DUCK_REPLAY finished tick=%d",gameTick); NFSHS_HostLog(nfshsLogLine); }()));
        }
    }
    return 1;

#else
return 0;
#endif
}

extern "C" int NFSHS_HostTestRaceRequested(void)
{
#if NFSHS_DIAGNOSTICS

    char value[2];
    return GetEnvironmentVariableA("NFSHS_TEST_RACE",value,sizeof(value)) != 0;

#else
return 0;
#endif
}

/* NFSHS_TEST_RACE is deliberately parsed at the platform boundary.  The game
 * receives ordinary frontend selections and still uses Front_BuildStream and
 * GameSetup_StartUp, exactly like a menu-started race. */
extern "C" int NFSHS_HostTestRaceParam(const char *name, int fallback)
{
#if NFSHS_DIAGNOSTICS

    char config[512];
    DWORD length=GetEnvironmentVariableA("NFSHS_TEST_RACE",config,sizeof(config));
    if (!length || length >= sizeof(config) || !name || !*name) return fallback;
    const size_t name_length=strlen(name);
    for (char *p=config; *p;) {
        while (*p==' ' || *p=='\t' || *p==',' || *p==';') ++p;
        char *key=p;
        while (*p && *p!='=' && *p!=',' && *p!=';' && *p!=' ' && *p!='\t') ++p;
        char *key_end=p;
        while (*p==' ' || *p=='\t') ++p;
        if (*p!='=') { while (*p && *p!=',' && *p!=';') ++p; continue; }
        ++p;
        while (*p==' ' || *p=='\t') ++p;
        char *value_end=0;
        long value=strtol(p,&value_end,0);
        if ((size_t)(key_end-key)==name_length && !strncmp(key,name,name_length) && value_end!=p)
            return (int)value;
        p=value_end!=p ? value_end : p+1;
        while (*p && *p!=',' && *p!=';') ++p;
    }
    return fallback;

#else
return fallback;
#endif
}

static unsigned short host_auto_mask(char key)
{
    switch(key) {
      case 'u':return 0x0010; case 'r':return 0x0020;
      case 'd':return 0x0040; case 'l':return 0x0080;
      case 'x': case 'g':return 0x4000; case 'z':return 0x8000;
      case 's':return 0x0008;
    }
    return 0;
}

enum { HOST_VRAM_W = 1024, HOST_VRAM_H = 512 };

#if NFSHS_DIAGNOSTICS
struct HostFlareReadback { int tick; unsigned short pixels[25]; };
static HostFlareReadback g_host_flare_readbacks[2048];
static int g_host_flare_readback_count=-1;

static void host_load_flare_readbacks(void)
{
    if(g_host_flare_readback_count>=0) return;
    g_host_flare_readback_count=0;
    char path[MAX_PATH];
    if(!GetEnvironmentVariableA("NFSHS_FLARE_READBACK_REPLAY",path,sizeof(path))) return;
    FILE *file=fopen(path,"rb");
    if(!file) return;
    unsigned char header[12];
    if(fread(header,1,sizeof(header),file)!=sizeof(header) ||
       memcmp(header,"N4FRDBK\0",8)!=0 || *(unsigned int *)(header+8)!=1) {
        fclose(file); return;
    }
    while(g_host_flare_readback_count<2048) {
        unsigned char row[54];
        if(fread(row,1,sizeof(row),file)!=sizeof(row)) break;
        HostFlareReadback *dst=&g_host_flare_readbacks[g_host_flare_readback_count++];
        dst->tick=*(int *)row;
        memcpy(dst->pixels,row+4,50);
    }
    fclose(file);
}

extern "C" void NFSHS_HostReplayFlareReadback(void *memory)
{
    host_load_flare_readbacks();
    if(!memory || g_host_flare_readback_count<=0) return;
    int tick=NFSHS_HostCurrentGameTicks();
    for(int i=0;i<g_host_flare_readback_count;i++) if(g_host_flare_readbacks[i].tick==tick) {
        memcpy(memory,g_host_flare_readbacks[i].pixels,50);
        return;
    }
}

#endif

static int host_readable(const void *p)
{
    return xport_memory_readable(p, 1);
}

#if NFSHS_DIAGNOSTICS
extern "C" short gClutDepth[256][16];
extern "C" void NFSHS_GTE_DebugState(int *,int *,int *);
extern "C" void NFSHS_GTE_DebugTransform(void *,void *);

struct HostDrawQuadCandidate {
    unsigned int marker;
    int tick,call;
    intptr sd,quad,material;
    unsigned char quadBytes[16],materialBytes[4];
    int sxy[4];
    int transformed[4][3];
    int otz,offset;
    short matrix[10];
    int translation[3];
    int h,ofx,ofy;
    unsigned char mirror,fogstate;
    short startfog,distfog;
};

struct HostDrawCPrimEntry {
    unsigned int marker;
    int tick,call,envmap;
    intptr matrix,translation,obj,overlay,cache,primPtr,mprimPtr;
    unsigned char objHead[32];
    unsigned char matrixBytes[36];
    int translationValues[3];
    unsigned char cacheHead[32];
};

extern "C" void NFSHS_HostTraceDrawCPrimEntry(
    const void *matrix,const void *translation,const void *obj,const void *overlay,
    int envmap,const void *rawCache)
{
    static int fd=-2,startTick,endTick=0x7fffffff,call;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_DRAWC_PRIM_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_DRAWC_PRIM_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_DRAWC_PRIM_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4DCPRM\1",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !matrix || !translation || !obj || !rawCache || tick<startTick || tick>endTick) return;
    const unsigned char *cache=(const unsigned char *)rawCache;
    HostDrawCPrimEntry record={};
    record.marker=0x5043444eU; record.tick=tick; record.call=call++; record.envmap=envmap;
    record.matrix=(intptr)matrix; record.translation=(intptr)translation;
    record.obj=(intptr)obj; record.overlay=(intptr)overlay; record.cache=(intptr)rawCache;
    memcpy(&record.primPtr,cache+4,sizeof(record.primPtr));
    memcpy(&record.mprimPtr,cache+8,sizeof(record.mprimPtr));
    memcpy(record.objHead,obj,sizeof(record.objHead));
    memcpy(record.matrixBytes,matrix,sizeof(record.matrixBytes));
    memcpy(record.translationValues,translation,sizeof(record.translationValues));
    memcpy(record.cacheHead,cache,sizeof(record.cacheHead));
    _write(fd,&record,sizeof(record));
}

struct HostR3DCarEntry {
    unsigned int marker;
    int tick,call,carIndex;
    intptr car;
    unsigned char position[12];
    unsigned char render[152];
    unsigned char visible[57];
};

extern "C" void NFSHS_HostTraceR3DCarEntry(const void *rawCar,const void *rawVisible)
{
    static int fd=-2,startTick,endTick=0x7fffffff,call;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_R3DCAR_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_R3DCAR_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_R3DCAR_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4R3CAR\1",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !rawCar || !rawVisible || tick<startTick || tick>endTick) return;
    const unsigned char *car=(const unsigned char *)rawCar;
    HostR3DCarEntry record={};
    record.marker=0x4333444eU; record.tick=tick; record.call=call++; record.car=(intptr)rawCar;
    memcpy(&record.carIndex,car+0x254,4);
    memcpy(record.position,car+0x18,12);
    memcpy(record.render,car+0x840,sizeof(record.render));
    memcpy(record.visible,rawVisible,sizeof(record.visible));
    _write(fd,&record,sizeof(record));
}

struct HostPrimStartResult {
    unsigned int marker;
    int tick,call,result,carIndex;
    intptr car;
    unsigned char center[8];
    unsigned char screenMatrix[32];
    unsigned char cacheHead[80];
};

extern "C" void NFSHS_HostTracePrimStartResult(
    const void *rawCar,int result,const void *center,const void *screenMatrix,const void *cache)
{
    static int fd=-2,startTick,endTick=0x7fffffff,call;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_PRIMSTART_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_PRIMSTART_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_PRIMSTART_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4PSTRT\1",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !rawCar || !center || !screenMatrix || !cache || tick<startTick || tick>endTick) return;
    const unsigned char *car=(const unsigned char *)rawCar;
    HostPrimStartResult record={};
    record.marker=0x5350444eU; record.tick=tick; record.call=call++; record.result=result;
    record.car=(intptr)rawCar; memcpy(&record.carIndex,car+0x254,4);
    memcpy(record.center,center,sizeof(record.center));
    memcpy(record.screenMatrix,screenMatrix,sizeof(record.screenMatrix));
    memcpy(record.cacheHead,cache,sizeof(record.cacheHead));
    _write(fd,&record,sizeof(record));
}

extern "C" void NFSHS_HostTraceDrawQuadCandidate(
    const void *rawSd,const void *quad,const void *material,
    long sxy0,long sxy1,long sxy2,long sxy3)
{
    static int fd=-2,startTick,endTick=0x7fffffff,call;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_DRAWQUAD_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_DRAWQUAD_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_DRAWQUAD_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4DQUAD\1",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !rawSd || !quad || !material || tick<startTick || tick>endTick) return;
    const unsigned char *sd=(const unsigned char *)rawSd;
    HostDrawQuadCandidate record={};
    record.marker=0x4451434eU;
    record.tick=tick; record.call=call++;
    record.sd=(intptr)rawSd; record.quad=(intptr)quad; record.material=(intptr)material;
    memcpy(record.quadBytes,quad,sizeof(record.quadBytes));
    memcpy(record.materialBytes,material,sizeof(record.materialBytes));
    record.sxy[0]=(int)sxy0; record.sxy[1]=(int)sxy1;
    record.sxy[2]=(int)sxy2; record.sxy[3]=(int)sxy3;
    for(int i=0;i<4;i++) memcpy(record.transformed[i],sd+0x98+i*0x10,12);
    memcpy(&record.otz,sd+0x94,4); memcpy(&record.offset,sd+0xec,4);
    memcpy(record.matrix,sd+0x14,sizeof(record.matrix));
    memcpy(record.translation,sd+0x14+20,sizeof(record.translation));
    NFSHS_GTE_DebugState(&record.h,&record.ofx,&record.ofy);
    record.mirror=sd[0x0c]; record.fogstate=sd[0x10e];
    memcpy(&record.startfog,sd+0xdc,2); memcpy(&record.distfog,sd+0xde,2);
    _write(fd,&record,sizeof(record));
}

extern "C" void NFSHS_HostTraceFlareState(const void *state)
{
    static int fd=-2,startTick,endTick=0x7fffffff;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_FLARE_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_FLARE_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_FLARE_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4FLARE\1",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !state || tick<startTick || tick>endTick) return;
    _write(fd,&tick,4);
    _write(fd,state,128);
}

extern "C" void NFSHS_HostTraceFlareEmit(
    const char *kind,const void *center,int otz,const void *caller)
{
    static int fd=-2,startTick,endTick=0x7fffffff;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_FLARE_EMIT_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_FLARE_EMIT_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_FLARE_EMIT_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4FEMIT\1",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !center || tick<startTick || tick>endTick) return;
    struct Emit { int tick,otz,xypack; intptr caller; char kind[12]; } record={};
    record.tick=tick; record.otz=otz; memcpy(&record.xypack,center,4);
    record.caller=(intptr)caller;
    if(kind) strncpy(record.kind,kind,sizeof(record.kind)-1);
    _write(fd,&record,sizeof(record));
}

static int host_flare_halo_trace_fd(void)
{
    static int fd=-2;
    if(fd==-2) {
        char path[260];
        unsigned long length=GetEnvironmentVariableA("NFSHS_FLARE_HALO_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return fd; }
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4FHALO\1",8);
    }
    return fd;
}

extern "C" void NFSHS_HostTraceFlareHaloEntry(
    const void *view,int scale,int type,const void *fpt,const void *fpt2,const void *cache)
{
    int fd=host_flare_halo_trace_fd();
    if(fd<0 || !view || !fpt) return;
    struct Entry {
        unsigned marker; int tick,scale,type;
        intptr view,fpt,fpt2,cache;
        int viewPos[3],point[3],point2[3];
    } record={};
    record.marker=0x48454e54U; record.tick=NFSHS_HostCurrentGameTicks();
    record.scale=scale; record.type=type;
    record.view=(intptr)view; record.fpt=(intptr)fpt;
    record.fpt2=(intptr)fpt2; record.cache=(intptr)cache;
    memcpy(record.viewPos,(const char *)view+8,12);
    memcpy(record.point,fpt,12);
    if(fpt2) memcpy(record.point2,fpt2,12);
    _write(fd,&record,sizeof(record));
}

extern "C" void NFSHS_HostTraceFlareHaloRTPS(
    const void *diff,const void *screen,int flags,int scale)
{
    int fd=host_flare_halo_trace_fd();
    if(fd<0 || !diff) return;
    struct RTPS {
        unsigned marker; int tick,flags,scale,diff[3],screenPack,sz;
    } record={};
    record.marker=0x48525450U; record.tick=NFSHS_HostCurrentGameTicks();
    record.flags=flags; record.scale=scale;
    memcpy(record.diff,diff,12);
    if(screen) memcpy(&record.screenPack,screen,4);
    _write(fd,&record,sizeof(record));
}

#endif

#if NFSHS_DIAGNOSTICS
extern "C" void NFSHS_HostTraceSkyProjection(void *scratch)
{
    static int fd=-2,startTick,endTick=0x7fffffff;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_SKY_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_SKY_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_SKY_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4SKY\0\2\0",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !scratch || tick<startTick || tick>endTick) return;
    _write(fd,&tick,4);
    _write(fd,scratch,0x2c0);
    struct { unsigned char matrix[20]; int translation[3]; } transform;
    NFSHS_GTE_DebugTransform(transform.matrix,transform.translation);
    _write(fd,&transform,sizeof(transform));
}

extern "C" void NFSHS_HostTraceHorizonCache(void *scratch)
{
    static int fd=-2,startTick,endTick=0x7fffffff;
    if(fd==-2) {
        char path[260],number[32];
        unsigned long length=GetEnvironmentVariableA("NFSHS_HORIZON_TRACE",path,sizeof(path));
        if(!length || length>=sizeof(path)) { fd=-1; return; }
        if(GetEnvironmentVariableA("NFSHS_HORIZON_TRACE_START",number,sizeof(number))) startTick=atoi(number);
        if(GetEnvironmentVariableA("NFSHS_HORIZON_TRACE_END",number,sizeof(number))) endTick=atoi(number);
        fd=_open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666);
        if(fd>=0) _write(fd,"N4HRZ\0\1\0",8);
    }
    int tick=NFSHS_HostCurrentGameTicks();
    if(fd<0 || !scratch || tick<startTick || tick>endTick) return;
    _write(fd,&tick,4);
    _write(fd,scratch,0x168);
}


#endif

extern "C" int NFSHS_HostReadableRange(const void *p,unsigned int bytes)
{
    if (!p || !bytes) return 0;
    return host_readable(p) && host_readable((const unsigned char *)p + bytes - 1);
}

#if NFSHS_DIAGNOSTICS
extern "C" void NFSHS_HostLog(const char *fmt)
{
#if NFSHS_DIAGNOSTICS

    if (host_fast_test_enabled() && !host_test_verbose_enabled()) {
        /* Geometry probes can produce tens of thousands of formatted disk
           writes per second.  Fast tests retain lifecycle, state and failure
           evidence; NFSHS_TEST_VERBOSE restores every diagnostic. */
        if (strncmp(fmt,"UNHANDLED",9) && strncmp(fmt,"TEST_",5) &&
            strncmp(fmt,"AUTOTEST_",9) && strncmp(fmt,"startup",7) &&
            strncmp(fmt,"WORLD_CAPTURE",13) &&
            strncmp(fmt,"main ",5) && strncmp(fmt,"Nfs2_",5) &&
            strncmp(fmt,"Sim_",4) && strncmp(fmt,"autopilot",9) &&
            strncmp(fmt,"DUCK_REPLAY",11) &&
            strncmp(fmt,"EAC_REPLAY",10) &&
            strncmp(fmt,"pad keys",8) && strncmp(fmt,"open ",5))
            return;
    }
    if (g_host_log_fd == -2)
        g_host_log_fd = _open("nfshs-runtime.log", _O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,
                              _S_IREAD|_S_IWRITE);
    if (g_host_log_fd < 0) return;
    char line[768];
    size_t length = strlen(fmt);
    if (length > sizeof(line)-2) length = sizeof(line)-2;
    memcpy(line, fmt, length);
    int n = (int)length;
    line[n++]='\r'; line[n++]='\n';
    _write(g_host_log_fd, line, n);

#else

#endif
}
#endif

#if NFSHS_DIAGNOSTICS
extern "C" void NFSHS_HostTraceMapMarker(int player,int index,int shape,int x,int y,
    int scaleX,int scaleY,int offX,int offY,int mapCos,int mapSin,int slice)
{
#if NFSHS_DIAGNOSTICS

    char enabled[2],first[16],last[16];
    if (!GetEnvironmentVariableA("NFSHS_MAP_MARKER_TRACE",enabled,sizeof(enabled))) return;
    int tick=NFSHS_HostCurrentGameTicks();
    int start=GetEnvironmentVariableA("NFSHS_MAP_MARKER_TRACE_START",first,sizeof(first)) ? atoi(first) : 0;
    int end=GetEnvironmentVariableA("NFSHS_MAP_MARKER_TRACE_END",last,sizeof(last)) ? atoi(last) : 0x7fffffff;
    if (tick<start || tick>end) return;
    NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "TEST_MAP tick=%d player=%d index=%d shape=%d xy=%d,%d scale=%d,%d off=%d,%d trig=%d,%d slice=%d",
        tick,player,index,shape,x,y,scaleX,scaleY,offX,offY,mapCos,mapSin,slice); NFSHS_HostLog(nfshsLogLine); }()));

#else

#endif
}
#endif

extern "C" int NFSHS_HostIsHeadless(void)
{
    char value[2];
    return GetEnvironmentVariableA("NFSHS_HEADLESS", value, sizeof(value)) != 0;
}

#if NFSHS_DIAGNOSTICS
extern "C" void NFSHS_HostTraceOtProducerSpan(const char *domain,const void *begin,const void *end)
{
#if NFSHS_DIAGNOSTICS

    static int fd=-2;
    if(fd==-2) {
        char path[MAX_PATH];
        fd=GetEnvironmentVariableA("NFSHS_OT_PRODUCER_SPANS",path,sizeof(path)) ?
            _open(path,_O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY,0666) : -1;
    }
    if(fd<0) return;
    char line[256];
    int count=_snprintf(line,sizeof(line),
        "{\"tick\":%d,\"domain\":\"%s\",\"begin\":%u,\"end\":%u}\n",
        NFSHS_HostCurrentGameTicks(),domain,(unsigned int)(intptr)begin,(unsigned int)(intptr)end);
    if(count>0 && count<(int)sizeof(line)) _write(fd,line,count);

#else

#endif
}
#endif

extern "C" void NFSHS_HostRaceStart(Car_tObj *playerCar)
{
#if NFSHS_DIAGNOSTICS

    g_host_duck_replay_run=0;
    g_host_duck_replay_finished=0;
    /* Test-only placement uses the game's own complete placement routine so
       Newton, road slice/quad, orientation, wheel and collision state remain
       synchronized.  With no startSlice parameter this boundary is inert. */
    int startSlice=NFSHS_HostTestRaceParam("startSlice",-1);
    if (playerCar && startSlice >= 0) {
        if (startSlice < gNumSlices) {
            int lateral=NFSHS_HostTestRaceParam("startLat",0);
            int direction=NFSHS_HostTestRaceParam("startDirection",1);
            int speed=NFSHS_HostTestRaceParam("startSpeed",0);
            int rotation=NFSHS_HostTestRaceParam("startRotation",0);
            if (direction != -1) direction=1;
            AILife_PlaceCarAtLocation(playerCar,startSlice,lateral,direction,speed,rotation);
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "TEST_PLACE_CAR slice=%d lat=%d direction=%d speed=%d rotation=%d",
                          startSlice,lateral,direction,speed,rotation); NFSHS_HostLog(nfshsLogLine); }()));
        } else {
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "TEST_PLACE_CAR_REJECT slice=%d numSlices=%d",startSlice,gNumSlices); NFSHS_HostLog(nfshsLogLine); }()));
        }
    }
    /* Input remains input: headless rendering must not silently press Cross.
       Automated gas is available explicitly through NFSHS_AUTOPILOT. */
    g_host_race_started=1;

#else

#endif
}

extern "C" void NFSHS_HostPumpTimers(void)
{
    ensure_window();
    pump_messages();
    NFSHS_HostPadPoll();
    psx_root_counter_poll();
    (void)VSync(-1);
}

#define host_log NFSHS_HostLog

static void ensure_window(void)
{
    static int initialized;
    if (g_window || initialized) return;
    initialized=1;
    xport_set_headless(getenv("NFSHS_HEADLESS") != 0);
    g_window = xport_window_init();
}

static void pump_messages(void)
{
    if (!xport_poll())
        exit(0);
}

static void host_pump_audio(int forceFrame)
{
    static uint64 renderedVblanks;
    static int initialized;
    uint64 wantedVblanks;
    uint32 renderBudget;

    if (forceFrame) {
        wantedVblanks = renderedVblanks + 1;
    } else {
        wantedVblanks = (uint64)(xport_timer_get() * 60u / 1000000u);
        if (!initialized) {
            renderedVblanks = wantedVblanks;
            initialized = 1;
            return;
        }
    }

    if (!forceFrame && wantedVblanks > renderedVblanks + 2) {
        sint16 discardedSamples[735 * 2];
        uint64 discardVblanks = wantedVblanks - renderedVblanks - 1;
        while (discardVblanks-- != 0) {
            spu_render(discardedSamples, 735);
            ++renderedVblanks;
        }
    }

    renderBudget = 2;
    while (renderedVblanks < wantedVblanks && renderBudget-- != 0) {
        xport_audio_vblank((uint32)renderedVblanks++, 60);
        if (!xport_audio_is_running()) {
            sint16 samples[735 * 2] = {0};
            spu_render(samples, 735);
        }
    }
}

extern "C" {

void NFSHS_HostBeginPacketArena(void *begin,void *end)
{
    g_host_packet_begin=(intptr)begin;
    g_host_packet_end=(intptr)end;
}
void NFSHS_HostBeginDMAFrame(void)
{
    g_host_ot_range_count=0;
#if NFSHS_DIAGNOSTICS
    g_host_dma_tag_fault_seen=0;
    memcpy(g_host_prev_added_prims,g_host_added_prims,sizeof(g_host_added_prims));
    memcpy(g_host_prev_added_ots,g_host_added_ots,sizeof(g_host_added_ots));
    memcpy(g_host_prev_added_callers,g_host_added_callers,sizeof(g_host_added_callers));
    memcpy(g_host_prev_added_generation,g_host_added_generation,sizeof(g_host_added_generation));
    g_host_prev_add_generation=g_host_add_generation;
#endif
    if(!++g_host_add_generation) {
        memset(g_host_added_generation,0,sizeof(g_host_added_generation));
        ++g_host_add_generation;
    }
#if NFSHS_DIAGNOSTICS
    g_host_last_added_prim=0;
    g_host_last_added_end=0;
    g_host_packet_overlap_count=0;
#endif
}

#if NFSHS_DIAGNOSTICS
void NFSHS_HostValidateOTPhase(const char *phase,void *otBase,int otSize,void *usedEnd)
{
#if NFSHS_DIAGNOSTICS

    if (!phase || !otBase || otSize <= 0 || otSize > 65536) return;
    intptr otBegin=(intptr)otBase;
    intptr otEnd=otBegin+(intptr)otSize*4u;
    intptr packetUsedEnd=(intptr)usedEnd;
    unsigned char *cur=(unsigned char *)(otEnd-4u);
    intptr previous=0;
    intptr seen[8192];
    int seenCount=0;
    while (host_readable(cur) && seenCount < (int)(sizeof(seen)/sizeof(seen[0]))) {
        intptr address=(intptr)cur;
        for (int i=0;i<seenCount;i++) if (seen[i]==address) {
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "OT_PHASE_CYCLE phase=%s step=%d cur=%p prev=%p ot=%p..%p packet=%p..%p",
                phase,seenCount,cur,(void *)previous,(void *)otBegin,(void *)otEnd,
                (void *)g_host_packet_begin,(void *)g_host_packet_end); NFSHS_HostLog(nfshsLogLine); }()));
            return;
        }
        seen[seenCount++]=address;
        unsigned int tag=*(unsigned int *)cur;
        unsigned int rawNext=tag&0x00ffffffu;
        if (rawNext==0x00ffffffu) return;
        unsigned int next=rawNext&0x00fffffcu;
        intptr base=address&~(intptr)0xffffffu;
        intptr candidate=base|next;
        if (!host_readable((void *)candidate)) {
            candidate=(otBegin&~(intptr)0xffffffu)|next;
        }
        if (!host_readable((void *)candidate)) {
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "OT_PHASE_UNREADABLE phase=%s step=%d cur=%p prev=%p tag=%08x next=%06x",
                phase,seenCount,cur,(void *)previous,tag,next); NFSHS_HostLog(nfshsLogLine); }()));
            return;
        }
        int inOt=candidate>=otBegin && candidate<otEnd && ((candidate-otBegin)&3u)==0;
        int currentPacket=candidate>=g_host_packet_begin && candidate<packetUsedEnd;
        int previousPacket=0;
        unsigned int slot=((unsigned int)candidate>>2)&16383u;
        unsigned int probe=slot;
        { unsigned int remaining=16384;
        while((g_host_added_generation[probe]==g_host_add_generation &&
              g_host_added_prims[probe]!=candidate) && --remaining)
            probe=(probe+1)&16383u;
    }
        if(g_host_added_generation[probe]==g_host_add_generation) currentPacket=1;
        probe=slot;
        { unsigned int remaining=16384;
        while((g_host_prev_added_generation[probe]==g_host_prev_add_generation &&
              g_host_prev_added_prims[probe]!=candidate) && --remaining)
            probe=(probe+1)&16383u;
    }
        if(g_host_prev_added_generation[probe]==g_host_prev_add_generation) previousPacket=1;
        if (!inOt && !currentPacket) {
            intptr owner=0,ownerOt=0;
            intptr predecessorWriter=0,predecessorPrim=0;
            for(unsigned int wi=0;wi<16384;wi++) {
                if(g_host_added_generation[wi]==g_host_add_generation &&
                   g_host_added_ots[wi]==previous) {
                    predecessorWriter=g_host_added_callers[wi];
                    predecessorPrim=g_host_added_prims[wi];
                }
            }
            unsigned int allSlot=host_history_slot((intptr)candidate);
            if(g_host_all_added_prims[allSlot]) {
                owner=g_host_all_added_callers[allSlot];
                ownerOt=g_host_all_added_ots[allSlot];
            }
            NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "OT_PHASE_FOREIGN phase=%s step=%d cur=%p prev=%p tag=%08x next=%p previousFrame=%d owner=%p ownerOt=%p prevWriter=%p prevPrim=%p ot=%p..%p packet=%p..%p",
                phase,seenCount,cur,(void *)previous,tag,(void *)candidate,previousPacket,
                (void *)owner,(void *)ownerOt,(void *)predecessorWriter,(void *)predecessorPrim,
                (void *)otBegin,(void *)otEnd,
                (void *)g_host_packet_begin,(void *)packetUsedEnd); NFSHS_HostLog(nfshsLogLine); }()));
            if ((intptr)cur >= g_host_packet_begin+48u && host_readable(cur-48u)) {
                unsigned int *w=(unsigned int *)cur;
                NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "OT_PHASE_FOREIGN_WORDS phase=%s at=%p m12=%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x cur=%08x,%08x,%08x,%08x",
                    phase,cur,w[-12],w[-11],w[-10],w[-9],w[-8],w[-7],w[-6],w[-5],
                    w[-4],w[-3],w[-2],w[-1],w[0],w[1],w[2],w[3]); NFSHS_HostLog(nfshsLogLine); }()));
            }
            return;
        }
        previous=address;
        cur=(unsigned char *)candidate;
    }
    if(seenCount==(int)(sizeof(seen)/sizeof(seen[0])))
        NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "OT_PHASE_LIMIT phase=%s steps=%d",phase,seenCount); NFSHS_HostLog(nfshsLogLine); }()));

#else

#endif
}
#endif
void NFSHS_HostEndPacketArena(void *usedEnd)
{
    NFSHS_DIAGNOSTIC_CALL(host_check_linked_tags((intptr)__builtin_return_address(0)));
    intptr end=(intptr)usedEnd;
    if(end>=g_host_packet_begin && end<=g_host_packet_end)
        g_host_packet_end=end;
}
/* ---- Controller: keyboard mapped to a digital PSX pad ----------------------- */
void NFSHS_HostPadPoll(void)
{
    pump_messages();
    unsigned short keys=0xffff;
    uint32 buttons=xport_input_read(0);
    g_pad_buttons=(unsigned short)((buttons>>8)|(buttons<<8));
#if NFSHS_DIAGNOSTICS
    // Headless input tests supply menu commands/PAD replay themselves. Do not
    // let unrelated desktop typing inject keys into that opt-in test run.
    static int testNoLiveInput=-1;
    if(testNoLiveInput<0)testNoLiveInput=getenv("NFSHS_TEST_NO_LIVE_INPUT")!=0;
    if(!testNoLiveInput)
#endif
    {
        keys &= (unsigned short)~g_pad_buttons;
        if (g_host_race_gas) keys &= (unsigned short)~0x4000;
    }
    
#if NFSHS_DIAGNOSTICS
{
        DWORD now=GetTickCount();
        if (!g_auto_initialized) {
            GetEnvironmentVariableA("NFSHS_AUTOPILOT",g_auto_sequence,sizeof(g_auto_sequence));
            g_auto_stage_start=now;
            g_auto_initialized=1;
            if (g_auto_sequence[0]) NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "autopilot sequence=%s",g_auto_sequence); NFSHS_HostLog(nfshsLogLine); }()));
        }
        if (g_auto_sequence[g_auto_index]) {
            /* 'g' is a terminal, continuously-held accelerator stage.  Menu
               confirmations use short 'x' pulses; once the race is entered,
               `...,g` keeps the same PSX Cross bit down indefinitely. */
            if (g_auto_active &&
                (g_auto_sequence[g_auto_index] != 'g' || !g_host_race_started) &&
                now-g_auto_stage_start >= 1000) {
                g_auto_active=0;
                /* Before Sim_Init has entered the race, terminal `g` must
                   continue producing press/release edges.  A permanently
                   held Cross cannot advance frontend states which sample a
                   fresh key-down.  Once the race starts it becomes the
                   intended continuously held accelerator. */
                if (g_auto_sequence[g_auto_index] != 'g') g_auto_index++;
                g_auto_stage_start=now;
            }
            while (!g_auto_active && g_auto_sequence[g_auto_index] &&
                   (g_auto_sequence[g_auto_index]==' ' || g_auto_sequence[g_auto_index]==',')) g_auto_index++;
            if (!g_auto_active && g_auto_sequence[g_auto_index] && now-g_auto_stage_start >= 1500) {
                g_auto_active=1; g_auto_stage_start=now;
                NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "autopilot key=%c mask=%04x",g_auto_sequence[g_auto_index],host_auto_mask(g_auto_sequence[g_auto_index])); NFSHS_HostLog(nfshsLogLine); }()));
            }
            if (g_auto_active) keys &= (unsigned short)~host_auto_mask(g_auto_sequence[g_auto_index]);
        }
    }
#endif

    /* Replay overrides only the emulated hardware packet.  With the opt-in
       environment variable absent this branch is inert and keyboard handling
       above remains byte-for-byte the normal native-port path. */
    NFSHS_DIAGNOSTIC_CALL(host_duck_replay_keys(NFSHS_HostCurrentGameTicks(),&keys));
    static unsigned short last_keys=0xffff;
    if(keys!=last_keys){NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "pad keys=%04x",keys); NFSHS_HostLog(nfshsLogLine); }()));last_keys=keys;}
    pad_publish(0,1,keys);
    /* Only one keyboard-backed controller exists.  Advertising the same pad
       on port two made every frontend pulse execute twice, eventually drawing
       an uninitialized player-two car-select screen. */
    pad_publish(1,0,0xffff);
}



/* The native compiler owns SP; this preserves the port's existing hint carrier */
void *NFSHS_NativeStackHint(void *p) { return p; }

}

extern "C" { extern void Platform_InitMemory(void); }
extern "C" { extern char *Platform_ReserveMemory(int,const char *); }
extern "C" { extern char *Platform_TempReserveMemory(int,const char *); }

static int host_platform_memory_self_test(void) {
    Platform_InitMemory();
    char *a = Platform_ReserveMemory(1,(char *)0);
    char *b = Platform_ReserveMemory(5,(char *)0);
    char *peek = Platform_TempReserveMemory(7,(char *)0);
    char *c = Platform_ReserveMemory(7,(char *)0);
    if (!a || !b || !c) return 1;
    if (b - a != 4 || c - b != 8) return 2;
    if (peek != c) return 3;
    if (((intptr)a & 3U) || ((intptr)b & 3U) || ((intptr)c & 3U)) return 4;
    if (getScratchAddr(0) != SCRATCHPAD || getScratchAddr(255) != SCRATCHPAD + 255) return 5;
    if (getScratchAddr(256) != SCRATCHPAD + 256) return 6;
    if (psx_addr(0x1F800000u, 1024) != getScratchAddr(0) ||
        psx_addr(0x9F8003FCu, 4) != getScratchAddr(255)) return 7;
    if (psx_addr(0x00000000u, 4) != DRAM || psx_addr(0xA0000000u, 4) != DRAM) return 8;
    return 0;
}

extern "C" int initmemadr(int,int);
extern "C" int largestunused(void);
extern "C" int getblocksize(void *);
extern "C" void *reservememadr(const char *,int,int);
extern "C" int purgememadr(void *);
void *__builtin_new(unsigned int);
void __builtin_delete(void *);
void FeDraw_SetABRMode(int);
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;

static int host_gpu_packet_self_test(void)
{
    uint32 *ram = (uint32 *)(DRAM + 0x12340u);
    uint32 *scratch = SCRATCHPAD + 128;
    uint32 native[4];
    const uint32 links[3] = {0x00012344u, 0x00800204u, (uint32)(intptr)(native + 1) & 0x00ffffffu};
    uint32 *locations[3] = {ram, scratch, native};
    for (unsigned int index = 0; index < 3; ++index)
    {
        uint32 *ot = locations[index];
        uint32 *packet = ot + 1;
        *ot = 0x7fabcdefu;
        *packet = 0x04fedcbau;
        AddPrim(ot, packet);
        if (*packet != 0x04abcdefu || *ot != (0x7f000000u | links[index])) return 1;
        *ot = 0x6b123456u;
        AddPrim(ot, ot);
        uint32 selfLink = (links[index] - 4u) & 0x00ffffffu;
        if (*ot != (0x6b000000u | selfLink)) return 2;
    }
    if (ClearOTagR(ram, 4) != ram || ram[0] != 0x00ffffffu) return 3;
    if (ram[1] != 0x12340u || ram[2] != 0x12344u || ram[3] != 0x12348u) return 4;
    if (ClearOTag(scratch, 4) != scratch || scratch[3] != 0x00ffffffu) return 5;
    if (scratch[0] != 0x800204u || scratch[1] != 0x800208u || scratch[2] != 0x80020cu) return 6;
    static uint32 registered[4];
    if (!gpu_register_packet_range(registered, sizeof(registered))) return 7;
    registered[0] = 0x2aabcdefu;
    registered[1] = 0x03fedcbau;
    AddPrim(registered, registered + 1);
    uint32 registeredLink = registered[0] & 0x00ffffffu;
    if (registeredLink < 0x200004u || registeredLink >= 0x800000u || registered[1] != 0x03abcdefu) return 8;
    if ((registered[0] >> 24) != 0x2au) return 9;
    if (!gpu_register_packet_range(registered, sizeof(registered))) return 10;
    registered[0] = 0x00ffffffu;
    AddPrim(registered, registered + 1);
    if (registered[0] != registeredLink || registered[1] != 0x03ffffffu) return 11;
    if (getenv("NFSHS_GPU_MIPS_FIXTURE"))
    {
        FILE *file = xport_fopen("../status/gpu-addprim-fixture.bin", "rb");
        if (!file) return 12;
        uint32 count = 0;
        if (fread(&count, sizeof(count), 1, file) != 1 || !count || count > 4096) { fclose(file); return 13; }
        for (uint32 index = 0; index < count; ++index)
        {
            uint32 record[5];
            if (fread(record, sizeof(record), 1, file) != 1) { fclose(file); return 14; }
            ram[0] = record[0];
            if (!record[2]) ram[1] = record[1];
            uint32 *packet = ram + (record[2] ? 0 : 1);
            AddPrim(ram, packet);
            if (ram[0] != record[3] || *packet != record[4]) { fclose(file); return 15; }
        }
        int extra = fgetc(file);
        int failed = ferror(file);
        fclose(file);
        if (extra != EOF || failed) return 16;
    }
    u_char *saved_packet = Render_gPacketPtr;
    u_char *saved_palette = Render_gPalettePtr;
    ram[0] = 0x00ffffff;
    ram[4] = 0;
    Render_gPalettePtr = (u_char *)ram;
    Render_gPacketPtr = (u_char *)(ram + 4);
    FeDraw_SetABRMode(2);
    bool menu_link_valid = ram[0] == 0x12350 && ram[4] == 0x02ffffff &&
        Render_gPacketPtr == (u_char *)(ram + 7);
    Render_gPacketPtr = saved_packet;
    Render_gPalettePtr = saved_palette;
    if (!menu_link_valid) return 17;
    return 0;
}

static int host_eac_allocator_self_test(void)
{
    int before;
    void *low;
    void *high;
    initmemadr((int)(intptr)(DRAM + 0x148b0c),PSX_DRAM_SIZE - 0x148b0c);
    before = largestunused();
    low = reservememadr(0,64,0);
    high = reservememadr(0,96,0x10);
    if (!low || !high)
        return 1;
    if (getblocksize(low) != 64 || getblocksize(high) != 96)
        return 2;
    purgememadr(low);
    purgememadr(high);
    if (largestunused() != before)
        return 3;
    low = __builtin_new(8);
    if (!low)
        return 4;
    if ((uint8 *)low < DRAM || (uint8 *)low >= DRAM + PSX_DRAM_SIZE)
        return 5;
    __builtin_delete(low);
    return largestunused() == before ? 0 : 6;
}

static int host_spu_self_test(void)
{
    uint8 block[16] = {0, 3};
    sint32 samples[2048 * 2] = {0};
    uint32 peak = 0;
    for (int index = 2; index < 16; ++index)
        block[index] = 0x77;
    SpuInit();
    if (!spu_upload(0x1000, block, sizeof(block)))
        return 1;
    SpuSetVoiceVolume(0,0x3fff,0x3fff);
    SpuSetVoicePitch(0,0x1000);
    SpuSetVoiceStartAddr(0,0x1000);
    SpuSetVoiceLoopStartAddr(0,0x1000);
    SsSetMVol(0x3fff,0x3fff);
    SpuSetKey(SPU_ON,SPU_KEYCH(0));
    spu_mix(samples, 2048);
    for (int index = 0; index < 2048 * 2; ++index) {
        sint32 sample = samples[index];
        uint32 magnitude = (uint32)(sample < 0 ? -sample : sample);
        if (magnitude > peak)
            peak = magnitude;
    }
    printf("spu_selftest peak=%u\n", (unsigned)peak);
    return peak ? 0 : 2;
}

static int host_gte_trig_self_test(void)
{
    if (ccos(0) < 4000)
        return 1;
    if (csin(0) < -64 || csin(0) > 64)
        return 2;
    if (ccos(377) < 3400 || ccos(377) > 3500 || ccos(-377) < 3400 || ccos(-377) > 3500)
        return 3;
    if (csin(377) < 2200 || csin(377) > 2300 || csin(-377) < -2300 || csin(-377) > -2200)
        return 4;
    if (csin(0x400) < 4000)
        return 5;
    if (ccos(0x800) > -4000)
        return 6;
    return 0;
}


static int host_gte_mvmva_self_test(void)
{
    MATRIX matrix = {};
    SVECTOR vector = {1, -2, 3, 0};
    int mac[3] = {};

    matrix.m[0][0] = 4096;
    matrix.m[1][1] = 4096;
    matrix.m[2][2] = 4096;
    gte_SetRotMatrix(&matrix);
    gte_SetTransMatrix(&matrix);
    gte_lwc2(0, (unsigned short)vector.vx | ((int)(unsigned short)vector.vy << 16));
    gte_lwc2(1, (unsigned short)vector.vz);
    gte_rt();
    gte_swc2(25, &mac[0]);
    gte_swc2(26, &mac[1]);
    gte_swc2(27, &mac[2]);
    if (mac[0] != 1 || mac[1] != -2 || mac[2] != 3)
        return 1;
    gte_rt();
    gte_swc2(25, &mac[0]);
    gte_swc2(26, &mac[1]);
    gte_swc2(27, &mac[2]);
    return mac[0] == 1 && mac[1] == -2 && mac[2] == 3 ? 0 : 2;
}

static int host_gte_normal_self_test(void)
{
    uint8 header[2048];
    uint8 table[384];
    uint32 base;
    sint16 coefficient;
    VECTOR input = {1, 0, 0, 0};
    SVECTOR output = {};
    FILE *image = xport_fopen("DATA/NFS4.EXE", "rb");
    if (!image) return 1;
    if (fread(header, 1, sizeof(header), image) != sizeof(header)) {
        fclose(image);
        return 2;
    }
    memcpy(&base, header + 24, sizeof(base));
    if (base > 0x8013485Cu || fseek(image, 2048L + (long)(0x8013485Cu - base), SEEK_SET) ||
        fread(table, 1, sizeof(table), image) != sizeof(table)) {
        fclose(image);
        return 3;
    }
    fclose(image);
    memcpy(psx_addr(0x8013485Cu, sizeof(table)), table, sizeof(table));
    memcpy(&coefficient, table, sizeof(coefficient));
    InitGeom();
    sint32 result = VectorNormalS(&input, &output);
    printf("gte_normal result=%d xyz=%d,%d,%d expected=%d,0,0\n",
           result, output.vx, output.vy, output.vz, coefficient);
    return result == 1 && output.vx == coefficient && output.vy == 0 && output.vz == 0 ? 0 : 4;
}

static int host_pad_packet_self_test(void)
{
    // Keep the digital fixture independent of connected physical controllers
    xport_input_override(1, 0);
    uint8 first[8];
    uint8 second[8];
    sint32 index;
    memset(first, 0xA5, sizeof(first));
    memset(second, 0x5A, sizeof(second));
    PadInitDirect(first, second);
    if (first[0] != 0xFF || first[1] != 0 || second[0] != 0xFF || second[1] != 0)
        return 3;
    for (index = 2; index < (sint32)sizeof(first); ++index)
        if (first[index] != 0xA5 || second[index] != 0x5A)
            return 4;
    PadStartCom();
    pad_publish(0, 1, 0xb7de);
    if (PadInfoMode(0, 1, 0) != 4 || PadInfoMode(0, 4, -1) != 1 ||
        PadInfoMode(0, 4, 0) != 4 || PadInfoMode(0, 4, 1) != 0)
        return 7;
    if (first[0] != 0 || first[1] != 0x41 || first[2] != 0xde || first[3] != 0xb7)
        return 1;
    pad_publish(1, 0, 0);
    for (index = 0; index < (sint32)sizeof(second); ++index)
    {
        if (second[index] != 0xff)
            return 2;
    }
    PadStopCom();
    if (PadGetState(0) != 0 || PadGetState(0x10) != 0)
        return 5;
    PadStartCom();
    if (PadGetState(0) != 6 || PadGetState(0x10) != 0)
        return 6;
    if (PadSetMainMode(0, 1, 1) != 0 || PadInfoMode(0, 3, 0) != 0)
        return 11;
    psx_pad_bind_owner_packets(0x80147600u, 0x801476F0u, 0, 0, 0, 0);
    for (index = 0; index < 2; ++index)
    {
        uint32 owner = 0x80147600u + 0xF0u * (uint32)index;
        memset(psx_addr(owner, 0xF0u), 0, 0xF0u);
        w_u32(owner, 0x80148000u);
        w_u16(0x80148000u, 4u);
        w_u16(0x80148002u, 7u);
        w_u8(owner + 0xE3u, 2u);
        w_u8(owner + 0xE4u, 1u);
        w_u16(owner + 0xE6u, 0x1234u);
        w_u8(owner + 0xE8u, 7u);
        w_u32(owner + 0x4Cu, 0x89ABCDEFu);
    }
    if (getenv("NFSHS_PAD_QUERY_FIXTURE"))
    {
        FILE *fixture = xport_fopen("../status/pad-query-fixture.bin", "rb");
        uint32 count, record[4];
        if (!fixture || fread(&count, sizeof(count), 1, fixture) != 1 || !count || count > 4096u)
            return 8;
        for (uint32 row = 0; row < count; ++row)
        {
            if (fread(record, sizeof(record), 1, fixture) != 1 ||
                (uint32)PadInfoMode((sint32)record[0], (sint32)record[1], (sint32)record[2]) != record[3])
            {
                fclose(fixture);
                return 9;
            }
        }
        bool complete = fgetc(fixture) == EOF;
        fclose(fixture);
        if (!complete)
            return 10;
    }
    if (getenv("NFSHS_PAD_COMMAND_FIXTURE"))
    {
        psx_pad_bind_main_mode_commands(0x80105DD8u, 0x80105E2Cu);
        FILE *fixture = xport_fopen("../status/pad-command-fixture.bin", "rb");
        uint32 count, record[6];
        uint8 expected[0xF0];
        if (!fixture || fread(&count, sizeof(count), 1, fixture) != 1 || !count || count > 4096u)
            return 12;
        for (uint32 row = 0; row < count; ++row)
        {
            if (fread(record, sizeof(record), 1, fixture) != 1 ||
                fread(expected, sizeof(expected), 1, fixture) != 1)
            {
                fclose(fixture);
                return 13;
            }
            uint32 owner = 0x80147600u + ((record[0] & 0xF0u) ? 0xF0u : 0u);
            memset(psx_addr(owner, 0xF0u), 0xA5, 0xF0u);
            w_u8(owner + 0x46u, (uint8)record[4]);
            w_u8(owner + 0xE4u, 1u);
            w_u16(owner + 0xE6u, (uint16)record[3]);
            if ((uint32)PadSetMainMode((sint32)record[0], (sint32)record[1], (sint32)record[2]) != record[5] ||
                memcmp(psx_addr(owner, 0xF0u), expected, 0xF0u) != 0)
            {
                fclose(fixture);
                return 14;
            }
        }
        bool complete = fgetc(fixture) == EOF;
        fclose(fixture);
        psx_pad_bind_main_mode_commands(0, 0);
        if (!complete)
            return 15;
    }
    if (getenv("NFSHS_PAD_CALLBACK_FIXTURE"))
    {
        psx_pad_bind_main_mode_commands(0x80105DD8u, 0x80105E2Cu);
        FILE *fixture = xport_fopen("../status/pad-callback-fixture.bin", "rb");
        uint32 count, record[5];
        uint8 expected[0xF0];
        if (!fixture || fread(&count, sizeof(count), 1, fixture) != 1 || !count || count > 4096u)
            return 16;
        for (uint32 row = 0; row < count; ++row)
        {
            if (fread(record, sizeof(record), 1, fixture) != 1 ||
                fread(expected, sizeof(expected), 1, fixture) != 1 || record[0] > 1u)
            {
                fclose(fixture);
                return 17;
            }
            uint32 owner = 0x80147600u;
            memset(psx_addr(owner, 0xF0u), 0xA5, 0xF0u);
            w_u8(owner + 0x46u, (uint8)record[1]);
            w_u8(owner + 0x53u, (uint8)record[2]);
            w_u8(owner + 0x49u, (uint8)record[3]);
            uint32 target = record[0] ? 0x80105E2Cu : 0x80105DD8u;
            if (xport_missing_pad_owner_callback(target, owner) != record[4] ||
                memcmp(psx_addr(owner, 0xF0u), expected, 0xF0u) != 0)
            {
                fclose(fixture);
                return 18;
            }
        }
        bool complete = fgetc(fixture) == EOF;
        fclose(fixture);
        psx_pad_bind_main_mode_commands(0, 0);
        if (!complete)
            return 19;
    }
    if (getenv("NFSHS_PAD_STATE_FIXTURE"))
    {
        FILE *fixture = xport_fopen("../status/pad-state-fixture.bin", "rb");
        uint32 count, record[7];
        if (!fixture || fread(&count, sizeof(count), 1, fixture) != 1 || !count || count > 4096u)
            return 20;
        for (uint32 row = 0; row < count; ++row)
        {
            if (fread(record, sizeof(record), 1, fixture) != 1)
            {
                fclose(fixture);
                return 21;
            }
            uint32 owner = 0x80147600u + ((record[0] & 0xF0u) ? 0xF0u : 0u);
            memset(psx_addr(owner, 0xF0u), 0, 0xF0u);
            w_u32(owner + 0x34u, record[1]);
            w_u32(owner + 0x10u, owner + (record[2] ? 0u : 0xF0u));
            w_u8(owner + 0x38u, (uint8)record[3]);
            w_u32(owner + 0x30u, 0x80149000u);
            w_u8(0x80149000u, (uint8)record[4]);
            w_u8(owner + 0x49u, (uint8)record[5]);
            first[0] = second[0] = (uint8)record[4];
            printf("pad_state %u %u %u\n", row, (uint32)PadGetState((sint32)record[0]), record[6]);
        }
        bool complete = fgetc(fixture) == EOF;
        fclose(fixture);
        if (!complete)
            return 22;
    }
    psx_pad_bind_owner_packets(0, 0, 0, 0, 0, 0);
    return 0;
}

extern "C" const uint32 xport_cd_status_address;

static int host_cd_position_self_test(void)
{
    sint32 saved_debug = CdSetDebug(0), previous_debug = 0;
    for (uint32 bit = 0; bit < 32u; ++bit)
    {
        sint32 level = bit == 31u ? (-2147483647 - 1) : (sint32)(1u << bit);
        if (CdSetDebug(level) != previous_debug)
        {
            CdSetDebug(saved_debug);
            return 9;
        }
        previous_debug = level;
    }
    bool debug_ok = CdSetDebug(-1) == previous_debug && CdSetDebug(2147483647) == -1;
    sint32 last_debug = CdSetDebug(saved_debug);
    if (!debug_ok || last_debug != 2147483647)
        return 9;
    uint32 status_word = r_u32(xport_cd_status_address - 1u);
    for (uint32 status = 0; status < 256u; ++status)
    {
        uint32 expected = 0xC3D400A5u | (status << 8);
        w_u32(xport_cd_status_address - 1u, expected);
        if (CdStatus() != (sint32)status || r_u32(xport_cd_status_address - 1u) != expected)
        {
            w_u32(xport_cd_status_address - 1u, status_word);
            return 8;
        }
    }
    w_u32(xport_cd_status_address - 1u, status_word);
    CdlLOC position;
    memset(&position, 0xA5, sizeof(position));
    if (CdIntToPos(0, &position) != &position || position.minute != 0 ||
        position.second != 2 || position.sector != 0 || position.track != 0xA5)
        return 1;
    if (CdPosToInt(&position) != 0)
        return 2;
    if (getenv("NFSHS_CD_POSITION_FIXTURE"))
    {
        FILE *fixture = xport_fopen("../status/cd-position-fixture.bin", "rb");
        uint32 count, record[4];
        if (!fixture || fread(&count, sizeof(count), 1, fixture) != 1 || !count || count > 16384u)
            return 3;
        for (uint32 row = 0; row < count; ++row)
        {
            if (fread(record, sizeof(record), 1, fixture) != 1 || record[0] > 1u)
            {
                fclose(fixture);
                return 4;
            }
            if (!record[0])
            {
                memcpy(&position, &record[2], sizeof(position));
                if (CdIntToPos((sint32)record[1], &position) != &position ||
                    memcmp(&position, &record[3], sizeof(position)) != 0)
                {
                    fclose(fixture);
                    return 5;
                }
            }
            else
            {
                memcpy(&position, &record[1], sizeof(position));
                if ((uint32)CdPosToInt(&position) != record[3] ||
                    memcmp(&position, &record[1], sizeof(position)) != 0)
                {
                    fclose(fixture);
                    return 6;
                }
            }
        }
        bool complete = fgetc(fixture) == EOF;
        fclose(fixture);
        if (!complete)
            return 7;
    }
    return 0;
}

static int host_memcard_self_test(void)
{
    static uint8 image[0x20000];
    uint32 buffer[64], expected[64];
    char name[] = "BASLUS-TEST";
    char pattern[] = "BASLUS-*";
    DIRENTRY directory[2] = {};
    sint32 command = 99, result = 99, count = -1;
    MemCardInit(1);
    MemCardStart();
    if (MemCardSync(1, &command, &result) != -1 || command != 99 || result != 99)
        return 1;
    for (unsigned i = 0; i < 64; ++i)
        buffer[i] = expected[i] = 0xA5000000u + i;
    if (!MemCardReadFile(0, name, buffer, 0, sizeof(buffer)) ||
        MemCardSync(0, &command, &result) != 1 || command != 3 || result != 1 || memcmp(buffer, expected, sizeof(buffer)))
        return 2;
    memset(image, 0, sizeof(image));
    if (!psx_memcard_mount(0, image, sizeof(image)) || !MemCardExist(0))
        return 3;
    if (MemCardSync(1, &command, &result) != 0 || command != 1 || result != 0)
        return 4;
    psx_vblank_signal();
    if (MemCardSync(1, &command, &result) != 1 || result != 3 || MemCardFormat(0) != 0)
        return 5;
    if (MemCardCreateFile(0, name, 2) != 0 || MemCardCreateFile(0, name, 1) != 6)
        return 6;
    if (!MemCardWriteFile(0, name, buffer, 0x1F80, sizeof(buffer)) || MemCardCreateFile(0, name, 1) != -1)
        return 7;
    if (MemCardSync(0, &command, &result) != 1 || command != 4 || result != 0)
        return 8;
    memset(buffer, 0, sizeof(buffer));
    if (!MemCardReadFile(0, name, buffer, 0x1F80, sizeof(buffer)) || MemCardSync(0, &command, &result) != 1 ||
        result != 0 || memcmp(buffer, expected, sizeof(buffer)))
        return 9;
    if (MemCardGetDirentry(0, pattern, directory, &count, 0, 2) != 0 || count != 1 ||
        strcmp(directory[0].name, name) || directory[0].size != 16384 || sizeof(DIRENTRY) != 40)
        return 10;
    if (MemCardDeleteFile(0, name) != 0 || MemCardDeleteFile(0, name) != 5 ||
        MemCardGetDirentry(0, pattern, directory, &count, 0, 2) != 0 || count != 0)
        return 11;
    MemCardEnd();
    return psx_memcard_mount(0, NULL, 0) ? 0 : 12;
}

static int host_irq_test_count;
static int host_vsync_test_count;
static void host_irq_test_callback(void) { ++host_irq_test_count; }
static void host_vsync_test_callback(void) { ++host_vsync_test_count; }
static sint32 host_event_test_callback(void) { ++host_irq_test_count; return 0; }

static int host_events_self_test(void)
{
    const uint32 event_class = 0xf2000002u, specification = 2;
    host_irq_test_count = 0;
    sint32 callback = OpenEvent(event_class, specification, 0x1000, host_event_test_callback);
    sint32 polling = OpenEvent(event_class, specification, 0x2000, NULL);
    if (callback < 1 || polling < 1 || callback == polling) return 1;
    DeliverEvent(event_class, specification);
    if (host_irq_test_count || TestEvent(polling)) return 2;
    if (!EnableEvent(callback) || !EnableEvent(polling)) return 3;
    DeliverEvent(event_class + 1, specification);
    DeliverEvent(event_class, specification + 1);
    if (host_irq_test_count || TestEvent(polling)) return 4;
    DeliverEvent(event_class, specification);
    if (host_irq_test_count != 1 || TestEvent(callback) || TestEvent(polling) != 1 || TestEvent(polling)) return 5;
    DeliverEvent(event_class, specification);
    UnDeliverEvent(event_class, specification);
    if (host_irq_test_count != 2 || TestEvent(polling)) return 6;
    if (!DisableEvent(callback) || !DisableEvent(polling)) return 7;
    DeliverEvent(event_class, specification);
    if (host_irq_test_count != 2 || TestEvent(polling)) return 8;
    if (!CloseEvent(callback) || !CloseEvent(polling) || CloseEvent(callback) || EnableEvent(polling)) return 9;
    if (EnableEvent(0) || DisableEvent(0) || CloseEvent(0) || TestEvent(0) ||
        EnableEvent(33) || DisableEvent(33) || CloseEvent(33) || TestEvent(33)) return 10;
    sint32 handles[32];
    for (int i = 0; i < 32; ++i) {
        handles[i] = OpenEvent(event_class, specification, 0x2000, NULL);
        if (handles[i] < 1 || handles[i] > 32) return 11;
        for (int j = 0; j < i; ++j) if (handles[i] == handles[j]) return 12;
        if (!EnableEvent(handles[i])) return 13;
    }
    if (OpenEvent(event_class, specification, 0x2000, NULL) != -1) return 14;
    DeliverEvent(event_class, specification);
    for (int i = 0; i < 32; ++i)
        if (TestEvent(handles[i]) != 1 || TestEvent(handles[i]) || !CloseEvent(handles[i])) return 15;
    callback = OpenEvent(event_class, specification, 0x1000, host_event_test_callback);
    return callback > 0 && CloseEvent(callback) ? 0 : 16;
}

static int host_callbacks_self_test(void) {
    ResetCallback();
    host_irq_test_count = host_vsync_test_count = 0;
    if (InterruptCallback(8, host_irq_test_callback) != NULL) return 1;
    psx_interrupt_raise(8);
    if (host_irq_test_count != 1) return 2;
    if (EnterCriticalSectionPSX() != 1) return 15;
    if (EnterCriticalSectionPSX() != 0) return 16;
    psx_interrupt_raise(8);
    if (host_irq_test_count != 1) return 3;
    ExitCriticalSection();
    if (host_irq_test_count != 2) return 4;
    if (InterruptCallback(8, NULL) != host_irq_test_callback) return 5;
    if (VSyncCallback(host_vsync_test_callback) != 0) return 6;
    psx_vblank_signal();
    if (host_vsync_test_count != 1) return 7;
    if (VSyncCallback(NULL) != (sint32)(intptr)host_vsync_test_callback) return 8;
    if (InterruptCallback(4, host_irq_test_callback) != NULL) return 9;
    if (!SetRCnt(0, 1000, 0x1001) || !psx_timers_advance(1000, 0, 0)) return 10;
    if (host_irq_test_count != 3) return 11;
    InterruptCallback(4, NULL);
    sint32 event = OpenEvent(0xF2000000u, 2u, 0x1000u, host_event_test_callback);
    if (event < 1 || !EnableEvent(event) || !StartRCnt(0)) return 12;
    if (!SetRCnt(0, 1000, 0x1001) || !psx_timers_advance(1000, 0, 0)) return 13;
    if (host_irq_test_count != 4 || !CloseEvent(event)) return 14;
    PsxInterruptCallback saved_dma[7];
    for (uint32 channel = 0; channel < 7; ++channel)
        saved_dma[channel] = DMACallback(channel, NULL);
    for (uint32 channel = 0; channel < 7; ++channel)
        if (DMACallback(channel, host_irq_test_callback) != NULL) return 17;
    if (DMACallback(7, host_vsync_test_callback) != NULL ||
        DMACallback(0xffffffffu, host_vsync_test_callback) != NULL) return 18;
    if (CdDataCallback(host_vsync_test_callback) != host_irq_test_callback) return 19;
    if (DMACallback(3, NULL) != host_vsync_test_callback) return 20;
    if (CdDataCallback(host_irq_test_callback) != NULL ||
        CdDataCallback(NULL) != host_irq_test_callback) return 21;
    for (uint32 channel = 0; channel < 7; ++channel)
        if (DMACallback(channel, saved_dma[channel]) !=
            (channel == 3 ? NULL : host_irq_test_callback)) return 22;
    if (host_irq_test_count != 4 || host_vsync_test_count != 1) return 23;
    ResetCallback();
    return 0;
}

struct HostSortTestRecord { int key, id; };
static int host_sort_test_compare(const void *left, const void *right)
{
    const HostSortTestRecord *a = (const HostSortTestRecord *)left;
    const HostSortTestRecord *b = (const HostSortTestRecord *)right;
    return a->key < b->key ? -1 : a->key > b->key;
}

static int host_libc_self_test(void)
{
    HostSortTestRecord records[] = {{1,0}, {1,1}, {1,2}, {1,3}};
    const int expected[] = {2,0,1,3};
    const int random_values[] = {16838,5758,10113,17515,31051,5627};
    qsortPSX(records, 4, sizeof(records[0]), host_sort_test_compare);
    for (int i = 0; i < 4; ++i)
        if (records[i].key != 1 || records[i].id != expected[i]) return 1;
    records[0].key = 4; records[1].key = -2; records[2].key = 0; records[3].key = 4;
    qsortPSX(records, 4, sizeof(records[0]), host_sort_test_compare);
    if (records[0].key != -2 || records[1].key != 0 || records[2].key != 4 || records[3].key != 4)
        return 2;
    srandPSX(1);
    for (int i = 0; i < 6; ++i)
        if (randPSX() != random_values[i]) return 3;
    srandPSX(1);
    return 0;
}

static int host_single_math_self_test(void)
{
    FILE *fixture = xport_fopen("../status/softfloat-single-fixture.bin", "rb");
    if (!fixture) return 1;
    sint32 domain = OpenEvent(0xF4000002u, 0x301, 0x2000, NULL);
    sint32 range = OpenEvent(0xF4000002u, 0x302, 0x2000, NULL);
    if (domain < 1 || range < 1) { fclose(fixture); return 2; }
    EnableEvent(domain);
    EnableEvent(range);
    unsigned char record[36];
    size_t count = 0, bytes;
    int failed = 0;
    while ((bytes = fread(record, 1, sizeof(record), fixture)) == sizeof(record)) {
        uint32 kind = xport_load_le32(record);
        uint32 left_bits = xport_load_le32(record + 4);
        float left, right, result;
        memcpy(&left, record + 4, sizeof(left));
        memcpy(&right, record + 8, sizeof(right));
        math_errno = math_err_point = 0;
        uint32 result_bits, result_high = 0;
        if (kind == 0) {
            result = __floatsisf((sint32)left_bits);
            memcpy(&result_bits, &result, sizeof(result_bits));
        } else if (kind == 1)
            result_bits = (uint32)__fixsfsi(left);
        else if (kind == 2) {
            result = __divsf3(left, right);
            memcpy(&result_bits, &result, sizeof(result_bits));
        } else if (kind == 3) {
            result_bits = (uint32)_err_math((sint32)left_bits, (sint32)xport_load_le32(record + 8));
        } else if (kind == 4 || kind == 6) {
            double converted = kind == 4 ? __extendsfdf2(left) : __floatsidf((sint32)left_bits);
            uint64 encoded;
            memcpy(&encoded, &converted, sizeof(encoded));
            result_bits = (uint32)encoded;
            result_high = (uint32)(encoded >> 32);
        } else if (kind == 5) {
            double input;
            memcpy(&input, record + 4, sizeof(input));
            result_bits = (uint32)__fixdfsi(input);
        } else if (kind == 7) {
            result_bits = __mulsf3PSX(left_bits, xport_load_le32(record + 8));
        } else if (kind == 8) {
            double input;
            memcpy(&input, record + 4, sizeof(input));
            result = __truncdfsf2(input);
            memcpy(&result_bits, &result, sizeof(result_bits));
        } else { failed = 3; break; }
        uint32 expected = xport_load_le32(record + 12);
        uint32 expected_high = xport_load_le32(record + 16);
        sint32 error = (sint32)xport_load_le32(record + 20);
        sint32 point = (sint32)xport_load_le32(record + 24);
        uint32 event_class = xport_load_le32(record + 28);
        uint32 event_spec = xport_load_le32(record + 32);
        int domain_delivered = TestEvent(domain);
        int range_delivered = TestEvent(range);
        if (result_bits != expected || result_high != expected_high || math_errno != error || math_err_point != point ||
            domain_delivered != (event_class == 0xF4000002u && event_spec == 0x301u) ||
            range_delivered != (event_class == 0xF4000002u && event_spec == 0x302u)) {
            FILE *failure = xport_fopen("../status/softfloat-single-native-mismatch.txt", "w");
            if (failure) {
                fprintf(failure, "Case %u kind %u: input %08X/%08X result %08X/%08X expected %08X/%08X errors %d/%d expected %d/%d events %d/%d\n",
                        (unsigned)count, kind, left_bits, xport_load_le32(record + 8), result_bits, result_high, expected, expected_high,
                        math_errno, math_err_point, error, point, domain_delivered, range_delivered);
                fclose(failure);
            }
            failed = 4;
            break;
        }
        ++count;
    }
    if (!failed && (bytes != 0 || ferror(fixture) || count != 10152)) failed = 5;
    CloseEvent(domain);
    CloseEvent(range);
    fclose(fixture);
    return failed;
}

static int host_double_arithmetic_self_test(void)
{
    FILE *fixture = xport_fopen("../status/softfloat-double-fixture.bin", "rb");
    if (!fixture) return 1;
    sint32 range = OpenEvent(0xF4000002u, 0x302, 0x2000, NULL);
    if (range < 1) { fclose(fixture); return 2; }
    EnableEvent(range);
    unsigned char record[44];
    size_t count = 0, bytes;
    int failed = 0;
    while ((bytes = fread(record, 1, sizeof(record), fixture)) == sizeof(record)) {
        uint32 kind = xport_load_le32(record);
        uint64 left = (uint64)xport_load_le32(record + 4) | ((uint64)xport_load_le32(record + 8) << 32);
        uint64 right = (uint64)xport_load_le32(record + 12) | ((uint64)xport_load_le32(record + 16) << 32);
        uint64 expected = (uint64)xport_load_le32(record + 20) | ((uint64)xport_load_le32(record + 24) << 32);
        math_errno = math_err_point = 0;
        uint64 result;
        if (kind == 0) result = __adddf3PSX(left, right);
        else if (kind == 1) result = __muldf3PSX(left, right);
        else if (kind == 2) result = __divdf3PSX(left, right);
        else { failed = 3; break; }
        sint32 error = (sint32)xport_load_le32(record + 28);
        sint32 point = (sint32)xport_load_le32(record + 32);
        uint32 event_class = xport_load_le32(record + 36);
        uint32 event_spec = xport_load_le32(record + 40);
        int delivered = TestEvent(range);
        if (result != expected || math_errno != error || math_err_point != point ||
            delivered != (event_class == 0xF4000002u && event_spec == 0x302u)) {
            FILE *failure = xport_fopen("../status/softfloat-double-native-mismatch.txt", "w");
            if (failure) {
                fprintf(failure,"Case %u kind %u: %08X%08X / %08X%08X result %08X%08X expected %08X%08X errors %d/%d expected %d/%d event %d\n",
                    (unsigned)count,kind,(uint32)(left >> 32),(uint32)left,(uint32)(right >> 32),(uint32)right,
                    (uint32)(result >> 32),(uint32)result,(uint32)(expected >> 32),(uint32)expected,
                    math_errno,math_err_point,error,point,delivered);
                fclose(failure);
            }
            failed = 4;
            break;
        }
        ++count;
    }
    if (!failed && (bytes != 0 || ferror(fixture) || count == 0)) failed = 5;
    CloseEvent(range);
    fclose(fixture);
    return failed;
}

static int host_double_compare_self_test(void)
{
    FILE *fixture = xport_fopen("../status/softfloat-compare-fixture.bin", "rb");
    if (!fixture) return 1;
    unsigned char record[20];
    size_t count = 0;
    size_t bytes;
    while ((bytes = fread(record, 1, sizeof(record), fixture)) == sizeof(record)) {
        double left, right;
        memcpy(&left, record, sizeof(left));
        memcpy(&right, record + 8, sizeof(right));
        sint32 expected = (sint32)xport_load_le32(record + 16);
        if (__ltdf2(left, right) != expected) {
            fclose(fixture);
            return 2;
        }
        ++count;
    }
    int failed = bytes != 0 || ferror(fixture) || count != 2624;
    fclose(fixture);
    return failed ? 3 : 0;
}

extern "C" void NFSHS_ConfigurePsyQHost(void);
extern "C" int ticks, timerhz;

static int host_pc_file_self_test(void)
{
    if (PCinit() != 0 || !psx_pc_set_root("../status", 0)) return 1;
    char name[] = "pc-runtime-fixture.bin";
    const int count = 70001;
    std::vector<char> input((size_t)count), output((size_t)count + 16u, (char)0xa5);
    for (int i = 0; i < count; ++i) input[i] = (char)(i * 73 + 19);
    int file = PCcreat(name, 0);
    if (file < 0) return 2;
    if (PCwrite(file, input.data(), count) != count || PClseek(file, 0, 2) != count) return 3;
    if (PClseek(file, -count, 1) != 0 || PCread(file, output.data() + 8, count) != count) return 4;
    if (memcmp(input.data(), output.data() + 8, (size_t)count) != 0) return 5;
    for (int i = 0; i < 8; ++i)
        if ((uint8)output[i] != 0xa5u || (uint8)output[count + 8 + i] != 0xa5u) return 6;
    if (PCread(file, output.data(), 1) != 0 || PCread(file, NULL, 0) != 0) return 7;
    if (PCread(file, output.data(), -1) != -1 || PCwrite(file, input.data(), -1) != -1) return 8;
    if (PCread(file, NULL, 1) != -1 || PCwrite(file, NULL, 1) != -1) return 9;
    if (PClseek(file, 0, 3) != -1 || PCclose(file) != 0 || PCclose(file) != -1) return 10;
    file = PCopen(name, 0, 0);
    if (file < 0 || PCwrite(file, input.data(), 1) != -1 || PClseek(file, count - 3, 0) != count - 3) return 11;
    memset(output.data(), 0x5a, output.size());
    if (PCread(file, output.data() + 8, 10) != 3 || memcmp(output.data() + 8, input.data() + count - 3, 3)) return 12;
    for (size_t i = 0; i < output.size(); ++i)
        if ((i < 8u || i >= 11u) && (uint8)output[i] != 0x5au) return 13;
    if (PCclose(file) != 0) return 14;
    file = PCopen(name, 1, 0);
    if (file < 0 || PCread(file, output.data(), 1) != -1 || PCwrite(file, input.data(), 1) != 1 || PCclose(file)) return 15;
    file = PCopen(name, 2, 0);
    if (file < 0 || PCread(file, output.data(), 1) != 1 || output[0] != input[0] || PCclose(file)) return 16;
    if (PCopen(NULL, 0, 0) != -1 || PCopen(name, -1, 0) != -1 || PCopen(name, 3, 0) != -1) return 17;
    int handles[64];
    for (int i = 0; i < 64; ++i)
        if ((handles[i] = PCopen(name, 0, 0)) < 0) return 18;
    if (PCopen(name, 0, 0) != -1 || PCinit() != 0) return 19;
    for (int i = 0; i < 64; ++i)
        if (PCread(handles[i], output.data(), 1) != -1 || PCclose(handles[i]) != -1) return 20;
    return psx_pc_set_root("DATA", 1) ? 0 : 21;
}

static int host_pc_completion_self_test(void)
{
    if (PCinit() || !psx_pc_set_root("../status", 0)) return 1;
    char name[] = "pc-completion-fixture.bin", value = 'Q', output = 0;
    int file = PCcreat(name, 0);
    if (file < 0 || PCwrite(file, &value, 1) != 1 || PCclose(file)) return 2;
    FileMgr saved = gFileMgr;
    ReadCmd saved_read = readcmd;
    FileOp operation = {};
    gFileMgr = {};
    gFileMgr.cbpending = 1;
    file = PCopen(name, 0, 0);
    if (file < 0) return 3;
    gFileMgr.curop = &operation;
    if (writefile(0x02000000 | file, (int)(intptr)&value, 0, 1) ||
        operation.status != -2 || gFileMgr.curop) return 4;
    for (int i = 0; i < 3; ++i)
    {
        operation = {};
        gFileMgr.curop = &operation;
        readcmd = {1, i == 2 ? 64 : file, (int)(intptr)&output, 0, i == 1 ? 2 : 1};
        if (readfile_systask(0, 0) || operation.status != (i == 0 ? 1 : -2) ||
            readcmd.pending || gFileMgr.curop || (i == 0 && output != 'Q')) return 5 + i;
    }
    if (PCclose(file)) return 8;
    file = PCopen(name, 2, 0);
    if (file < 0) return 9;
    operation = {};
    gFileMgr.curop = &operation;
    if (writefile(0x02000000 | file, (int)(intptr)&value, 0, 1) ||
        operation.status != 1 || gFileMgr.curop || PCclose(file)) return 10;
    gFileMgr = saved;
    readcmd = saved_read;
    return psx_pc_set_root("DATA", 1) ? 0 : 11;
}

static int host_video_self_test(void)
{
    NFSHS_ConfigurePsyQHost();
    psx_pc_set_root("DATA", 1);
    timerhz = 100;
    initmemadr((int)(intptr)(DRAM + 0x148b0c),PSX_DRAM_SIZE - 0x148b0c);
    int free_before = largestunused();
    char dct[] = "ZZZZVD00.DCT";
    intptr video = VIDEO_create(80, 80, 15 << 16, 0x20000, 16);
    if (!video) return 1;
    VIDEO_spoolfile(video, dct);
    VIDEO_startplayback(video);
    if (VIDEO_state(video) != VIDEOSTATE_PLAYING) {
        VIDEO_destroy(video);
        purgememadr((void *)video);
        return 2;
    }
    unsigned changed = 0;
    for (int i = 0; i < 20; ++i)
    {
        ticks = i * 7;
        changed += VIDEO_updateframexy(video, 512, 0) != 0;
    }
    VIDEO_abortplayback(video);
    int state = VIDEO_state(video);
    VIDEO_destroy(video);
    if (!purgememadr((void *)video) || largestunused() != free_before) return 5;
    if (!changed || state != VIDEOSTATE_IDLE) return 3;
    uint16 first = VRAM[512];
    unsigned varied = 0;
    for (int row = 0; row < 80; ++row)
        for (int column = 0; column < 80; ++column)
            varied += VRAM[row * 1024 + 512 + column] != first;
    if (!varied) return 4;
    FILE *pixels = xport_fopen("../status/video-menu.rgb", "wb");
    if (!pixels) return 10;
    for (int row = 0; row < 80; ++row)
        for (int column = 0; column < 80; ++column) {
            uint16 color = VRAM[row * 1024 + 512 + column];
            uint8 rgb[3] = {(uint8)((color & 31u) * 255u / 31u),
                            (uint8)(((color >> 5) & 31u) * 255u / 31u),
                            (uint8)(((color >> 10) & 31u) * 255u / 31u)};
            if (fwrite(rgb, 1, 3, pixels) != 3) { fclose(pixels); return 11; }
        }
    fclose(pixels);
    char movies[][32] = {"MOVIES/NFS4TITL.XA", "MOVIES/DEMO1AV.XA",
                         "MOVIES/DEMO2AV.XA", "MOVIES/DEMO3AV.XA", "MOVIES/EADOLBY.XA"};
    const uint32 ends[] = {1358, 456, 444, 480, 120};
    for (unsigned movie = 0; movie < 5; ++movie)
    {
        int file = PCopen(movies[movie], 0, 0);
        if (file < 0) return 5;
        std::vector<uint32> ring(16384);
        StSetRing(ring.data(), 32);
        StSetStream(1, 1, ends[movie], NULL, NULL);
        uint32 sector[512], *frame = NULL, *header = NULL;
        int frames = 0, failed = 0;
        unsigned sector_number = 0;
        while (frames < 4 && PCread(file, (char *)sector, sizeof(sector)) == sizeof(sector))
        {
            int fed = stream_feed_sector((uint8 *)sector, NULL);
            if (fed == -2) {
                FILE *log = xport_fopen("../status/video-str-failure.txt", "w");
                if (log) {
                    fprintf(log, "%s STR sector %u: result %d, part %u/%u, frame %u\n",
                            movies[movie], sector_number, fed, sector[1] & 0xffffu,
                            sector[1] >> 16, sector[2]);
                    fclose(log);
                }
                failed = 6; break;
            }
            ++sector_number;
            if (StNextStatus(NULL, NULL) != StCOMPLETE || StGetNext(&frame, &header)) continue;
            StHEADER *info = (StHEADER *)header;
            if (!NfshsVideoDecode(frame, info->width, info->height, true, 0, 256)) failed = 7;
            StFreeRing(frame);
            if (failed) break;
            ++frames;
        }
        StUnSetRing();
        PCclose(file);
        if (failed || frames != 4) return failed ? failed : 8;
    }
    first = VRAM[256 * 1024];
    varied = 0;
    for (int row = 256; row < 496; ++row)
        for (int column = 0; column < 384; ++column)
            varied += VRAM[row * 1024 + column] != first;
    if (!varied) return 9;
    pixels = xport_fopen("../status/video-movie.rgb", "wb");
    if (!pixels) return 12;
    for (int row = 256; row < 496; ++row)
        if (fwrite((uint8 *)(VRAM + row * 1024), 1, 256 * 3, pixels) != 256 * 3) {
            fclose(pixels); return 13;
        }
    fclose(pixels);
    PadInitDirect(&Padglobal[0].nopad, &Padglobal[1].nopad);
    PadStartCom();
    gPadinfo.initialized = 1;
    xport_input_override(1, 0);
    if (play_movie(4) != 0) return 14;
    xport_input_override(1, 0x0800);
    if (play_movie(4) != 1) return 15;
    xport_input_override(0, 0);
    PadStopCom();
    gPadinfo.initialized = 0;
    return 0;
}

extern "C" {
#if defined(__EMSCRIPTEN__)
void NFSHS_HostMainInit(void)
#else
void __main(void)
#endif
{
    if (getenv("NFSHS_HEADLESS")) xport_set_headless(1);
    if (getenv("NFSHS_VIDEO_SELFTEST"))
        ExitProcess((UINT)host_video_self_test());
    if (getenv("NFSHS_PC_FILE_SELFTEST"))
        ExitProcess((UINT)host_pc_file_self_test());
    if (getenv("NFSHS_PC_COMPLETION_SELFTEST"))
        ExitProcess((UINT)host_pc_completion_self_test());
    char allocatorTest[2];
    if (GetEnvironmentVariableA("NFSHS_ALLOCATOR_SELFTEST",allocatorTest,sizeof(allocatorTest)))
        ExitProcess((UINT)host_eac_allocator_self_test());
    char platformMemoryTest[2];
    if (GetEnvironmentVariableA("NFSHS_PLATFORM_MEMORY_SELFTEST",platformMemoryTest,
                                sizeof(platformMemoryTest)))
        ExitProcess((UINT)host_platform_memory_self_test());
    char spuTest[2];
    if (GetEnvironmentVariableA("NFSHS_SPU_SELFTEST",spuTest,sizeof(spuTest))) {
        NFSHS_ConfigurePsyQHost();
        ExitProcess((UINT)host_spu_self_test());
    }
    char gteTrigTest[2];
    if (GetEnvironmentVariableA("NFSHS_GTE_TRIG_SELFTEST",gteTrigTest,sizeof(gteTrigTest)))
        ExitProcess((UINT)host_gte_trig_self_test());
    char padPacketTest[2];
    if (GetEnvironmentVariableA("NFSHS_PAD_PACKET_SELFTEST",padPacketTest,sizeof(padPacketTest)))
        ExitProcess((UINT)host_pad_packet_self_test());

    if (getenv("NFSHS_GTE_MVMVA_SELFTEST"))
        ExitProcess((UINT)host_gte_mvmva_self_test());
    if (getenv("NFSHS_GTE_NORMAL_SELFTEST"))
        ExitProcess((UINT)host_gte_normal_self_test());
    if (getenv("NFSHS_MEMCARD_SELFTEST"))
        ExitProcess((UINT)host_memcard_self_test());
    if (getenv("NFSHS_CD_POSITION_SELFTEST"))
        ExitProcess((UINT)host_cd_position_self_test());
    if (getenv("NFSHS_CALLBACKS_SELFTEST"))
        ExitProcess((UINT)host_callbacks_self_test());
    if (getenv("NFSHS_EVENTS_SELFTEST"))
        ExitProcess((UINT)host_events_self_test());
    if (getenv("NFSHS_LIBC_SELFTEST"))
        ExitProcess((UINT)host_libc_self_test());
    if (getenv("NFSHS_GPU_PACKET_SELFTEST"))
        ExitProcess((UINT)host_gpu_packet_self_test());
    if (getenv("NFSHS_DOUBLE_COMPARE_SELFTEST"))
        ExitProcess((UINT)host_double_compare_self_test());
    if (getenv("NFSHS_SINGLE_MATH_SELFTEST"))
        ExitProcess((UINT)host_single_math_self_test());
    if (getenv("NFSHS_DOUBLE_MATH_SELFTEST"))
        ExitProcess((UINT)host_double_arithmetic_self_test());
    ensure_window();
    NFSHS_ConfigurePsyQHost();
}
void __pure_virtual(void) { ExitProcess(3); }

}
