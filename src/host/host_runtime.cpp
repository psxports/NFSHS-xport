/* Native host replacement for the PsyQ surface used by NFSHS.
 *
 * The shared xport platform owns the OS boundary. Game/frontend code is left untouched;
 * STR/MDEC remain out of scope, while timing, input, host files, GPU commands
 * and SPU state have real semantics.
 */
#include "diagnostics.h"
#include "psx.h"
#include "psx_gpu.h"
#include "xport.h"
#include "psx_spu.h"
#include "psx.h"

#undef SetDrawMode
#undef SetPolyF3
#undef SetPolyF4
#undef SetPolyFT4
#undef SetPolyG4
#undef SetPolyGT4
#undef SetSemiTrans
#undef SetShadeTex
#undef SetTexWindow
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

typedef PSX_RECT PsxRect;
typedef DISPENV PsxDispEnv;
typedef DRAWENV PsxDrawEnv;
typedef VECTOR PsxVector;
typedef SVECTOR PsxSVector;
typedef MATRIX PsxMatrix;
struct PsxCdlLoc { unsigned char minute, second, sector, track; };
struct PsxCdlFile { PsxCdlLoc pos; unsigned long size; char name[16]; };

static int g_window;
static void (*g_vsync_callback)(void);
static int g_video_mode;
static int g_geom_screen = 256;
static PsxMatrix g_rotation;
#if NFSHS_DIAGNOSTICS
static int g_host_log_fd = -2;
#endif
static unsigned short g_pad_buttons;
static char g_auto_sequence[256];
static int g_auto_initialized, g_auto_active, g_auto_index;
static DWORD g_auto_stage_start;
static int g_host_race_gas;
static int g_host_race_started;
static unsigned long long g_host_timer_ticks;
static unsigned long long g_host_fast_vsync_count;
static int g_host_fast_test = -1;
static int g_host_test_verbose = -1;
#if defined(AP_WIN) && NFSHS_DIAGNOSTICS
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
extern "C" unsigned int tmrint(void);
extern "C" void NFSHS_HostPadPoll(void);
extern "C" int NFSHS_HostCurrentGameTicks(void);
extern "C" int libticks;
extern "C" int gTicks;
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

static DWORD host_automation_millis(void)
{
    if (host_fast_test_enabled())
        return (DWORD)((g_host_timer_ticks * 1000ULL) / 128ULL);
    return GetTickCount();
}

#ifdef AP_WIN
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
#endif

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

#ifdef AP_WIN
    g_host_duck_replay_run=0;
    g_host_duck_replay_finished=0;
#endif
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
    static unsigned long long lastLogged = 0;
    ensure_window();
    pump_messages();
    if (!host_fast_test_enabled())
        host_pump_audio(0);
    /* The PSX libpad ISR updates the two PadInitDirect buffers asynchronously.
       The native backend owns that hardware boundary, so refresh the same
       buffers here before original timer subscribers (including PAD_update)
       consume them. */
    NFSHS_HostPadPoll();
    unsigned long long wanted;
    if (host_fast_test_enabled()) {
        /* One systemtask pump represents one real PSX root-counter tick.  This
           makes timedwait finish immediately in wall-clock time without
           deleting the callbacks or changing the counter values they see. */
        wanted = g_host_timer_ticks + 1;
    } else {
        wanted = (unsigned long long)(xport_timer_get() * 128u / 1000000u);
    }
    /* Avoid an unbounded catch-up burst after a debugger pause. */
    if (wanted > g_host_timer_ticks + 16) g_host_timer_ticks = wanted - 16;
    while (g_host_timer_ticks < wanted) {
        ++g_host_timer_ticks;
        ++gTicks;
        tmrint();
    }
    if (g_host_timer_ticks >= lastLogged + 128) {
        lastLogged = g_host_timer_ticks;
        NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "host timer=%u libticks=%d gTicks=%d",
                      (unsigned)g_host_timer_ticks,libticks,gTicks); NFSHS_HostLog(nfshsLogLine); }()));
    }
}

#define host_log NFSHS_HostLog

static void ensure_window(void)
{
    static int initialized;
    if (g_window || initialized) return;
    initialized=1;
#if NFSHS_DIAGNOSTICS
    g_host_collect_render_stats=!host_fast_test_enabled() || host_test_verbose_enabled();
#endif
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

static void set_packet(void *packet, unsigned char words, unsigned char opcode)
{
    if (!packet) return;
    ((unsigned char *)packet)[3] = words;
    ((unsigned char *)packet)[7] = opcode;
}

extern "C" {

/* ---- Host lifecycle / timing ------------------------------------------------- */
void FlushCache(void) {}
int ResetCallback(void) { g_vsync_callback = 0; return 0; }
void SetVideoMode(int mode) { g_video_mode = mode; }
int GetVideoMode(void) { return g_video_mode; }
int VSync(int mode)
{
    static int testExitVsyncs = -1;
    ensure_window(); pump_messages();
    if (mode >= 0) {
        if (host_fast_test_enabled()) ++g_host_fast_vsync_count;
        else xport_timer_wait_frame(60);
    }
    if (g_vsync_callback) g_vsync_callback();
    if (mode >= 0)
        host_pump_audio(host_fast_test_enabled());
    if (mode >= 0) {
        if (testExitVsyncs < 0) {
            const char *value = getenv("NFSHS_TEST_EXIT_VSYNCS");
            testExitVsyncs = value ? atoi(value) : 0;
        }
        if (testExitVsyncs && (int)g_host_fast_vsync_count >= testExitVsyncs) {
            printf("audio_metrics submitted=%u nonzero=%u peak=%u overruns=%u\n",
                   (unsigned)g_xport_audio_submitted_buffers,
                   (unsigned)g_xport_audio_nonzero_buffers,
                   (unsigned)g_xport_audio_peak,
                   (unsigned)g_xport_audio_callback_overruns);
            exit(g_xport_audio_nonzero_buffers && g_xport_audio_peak ? 0 : 97);
        }
    }
    if (host_fast_test_enabled())
        return (int)g_host_fast_vsync_count;
    return (int)(xport_timer_get() * 60u / 1000000u);
}
void *VSyncCallback(void *cb) { void *old=(void *)g_vsync_callback; g_vsync_callback=(void(*)(void))cb; return old; }
int GetRCnt(int) { return VSync(-1); }
long StartRCnt(unsigned long) { return 1; }
long OpenEvent(unsigned long, long, long, long (*)()) { return 1; }
long EnableEvent(long) { return 1; }
long DisableEvent(long) { return 1; }
int EnterCriticalSection(void) { return 1; }
void ExitCriticalSection(void) {}
void *DMACallback(int, void *cb) { return cb; }
void *InterruptCallback(int, void *cb) { return cb; }

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
void SetPolyF3(void *p)  { set_packet(p,4,0x20); }
void SetPolyF4(void *p)  { set_packet(p,5,0x28); }
void SetPolyFT4(void *p) { set_packet(p,9,0x2c); }
void SetPolyG4(void *p)  { set_packet(p,8,0x38); }
void SetPolyGT4(void *p) { set_packet(p,12,0x3c); }
void SetSemiTrans(void *p,int on) { if(p) ((unsigned char*)p)[7]=(unsigned char)((((unsigned char*)p)[7]&~2)|(on?2:0)); }
void SetShadeTex(void *p,int on) { if(p) ((unsigned char*)p)[7]=(unsigned char)((((unsigned char*)p)[7]&~1)|(on?1:0)); }
void SetDrawMode(void *p,int dfe,int dtd,int tpage,PsxRect *tw)
{
    set_packet(p,2,0xe1);
    if(!p)return;
    ((unsigned long*)p)[1]=0xe1000000UL|(tpage&0x9ff)|((dtd&1)<<9)|((dfe&1)<<10);
    if(tw) ((unsigned long*)p)[2]=0xe2000000UL|((tw->x>>3&31)<<10)|((tw->y>>3&31)<<15)|(((-tw->w)&255)>>3)|((((-tw->h)&255)>>3)<<5);
    else ((unsigned long*)p)[2]=0;
}
static unsigned int host_draw_area_word(unsigned int command,int x,int y)
{
    /* PsyQ _set_clip_tl/br, 0x800EE898..0x800EE9C4: signed 16-bit
       arguments saturated to the GPU's 1024x512 VRAM, not masked/wrapped. */
    x=(short)x;y=(short)y;
    if(x<0)x=0;if(x>=HOST_VRAM_W)x=HOST_VRAM_W-1;
    if(y<0)y=0;if(y>=HOST_VRAM_H)y=HOST_VRAM_H-1;
    return command|((unsigned int)y<<10)|(unsigned int)x;
}
void SetDrawMove(void *p,PsxRect *,int,int) { set_packet(p,5,0x80); }
void SetTexWindow(void *p,PsxRect *tw)
{
    set_packet(p,2,0xe2);
    if(!p)return;
    ((unsigned long*)p)[1]=tw ? 0xe2000000UL|((tw->x>>3&31)<<10)|((tw->y>>3&31)<<15)|(((-tw->w)&255)>>3)|((((-tw->h)&255)>>3)<<5) : 0xe2000000UL;
    ((unsigned long*)p)[2]=0;
}

/* ---- GTE helpers used by gameplay and packet generation --------------------- */
void NFSHS_GTE_WriteControl(int,int);
void NFSHS_GTE_SetGeomScreen(int);
void NFSHS_HostInitGeom(void) {
    memset(&g_rotation,0,sizeof(g_rotation));
    g_rotation.m[0][0]=g_rotation.m[1][1]=g_rotation.m[2][2]=4096;
    NFSHS_GTE_WriteControl(26,0x3e8);
    NFSHS_GTE_WriteControl(27,-0x1062);
    NFSHS_GTE_WriteControl(28,0x1400000);
    NFSHS_GTE_WriteControl(24,0);
    NFSHS_GTE_WriteControl(25,0);
}
void NFSHS_HostSetGeomScreen(int h) { g_geom_screen=h; NFSHS_GTE_SetGeomScreen(h); }
void InitGeom(void) { NFSHS_HostInitGeom(); }
void SetGeomScreen(int h) { NFSHS_HostSetGeomScreen(h); }
extern void NFSHS_GTE_SetFarColor(int,int,int);
void SetFarColor(int r,int g,int b) { NFSHS_GTE_SetFarColor(r,g,b); }
void SetFogNear(int a,int dvpw) {
    if(dvpw) NFSHS_GTE_WriteControl(27,-(a*320)/dvpw);
    NFSHS_GTE_WriteControl(28,0x1400000);
}
extern "C" const int _rsincos[];
static void host_psyq_sincos(int angle,int *s,int *c)
{
    int packed;
    if(angle<0){packed=_rsincos[-angle&0xfff];*s=-(int)(short)packed;}
    else {packed=_rsincos[angle&0xfff];*s=(int)(short)packed;}
    *c=packed>>16;
}
PsxMatrix *NFSHS_HostRotMatrix(PsxSVector *r,PsxMatrix *m)
{
    int sx,cx,sy,cy,sz,cz;
    host_psyq_sincos(r->vx,&sx,&cx); host_psyq_sincos(r->vy,&sy,&cy); host_psyq_sincos(r->vz,&sz,&cz);
    int nsy=-sy;
    m->m[0][2]=(short)sy;
    m->m[1][2]=(short)(-(cy*sx)>>12);
    m->m[2][2]=(short)(cy*cx>>12);
    m->m[0][0]=(short)(cz*cy>>12);
    m->m[0][1]=(short)(-(sz*cy)>>12);
    int cz_nsy=cz*nsy>>12;
    m->m[1][0]=(short)(sz*cx>>12)-(short)(cz_nsy*sx>>12);
    m->m[2][0]=(short)(sz*sx>>12)+(short)(cz_nsy*cx>>12);
    int sz_nsy=sz*nsy>>12;
    m->m[1][1]=(short)(cz*cx>>12)+(short)(sz_nsy*sx>>12);
    m->m[2][1]=(short)(cz*sx>>12)-(short)(sz_nsy*cx>>12);
    return m;
}
PsxMatrix *RotMatrix(PsxSVector *r,PsxMatrix *m) { return NFSHS_HostRotMatrix(r,m); }
PsxMatrix *MulMatrix2(PsxMatrix *source,PsxMatrix *destination)
{
    short output[3][3];
    int row;
    int column;
    int inner;

    if (!source || !destination)
        return destination;
    for (row = 0; row < 3; ++row) {
        for (column = 0; column < 3; ++column) {
            sint64 sum = 0;
            for (inner = 0; inner < 3; ++inner)
                sum += (sint64)source->m[row][inner] * destination->m[inner][column];
            output[row][column] = (short)(sum >> 12);
        }
    }
    memcpy(destination->m, output, sizeof(output));
    return destination;
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
        DWORD now=host_automation_millis();
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

#ifdef AP_WIN
    /* Replay overrides only the emulated hardware packet.  With the opt-in
       environment variable absent this branch is inert and keyboard handling
       above remains byte-for-byte the normal native-port path. */
    NFSHS_DIAGNOSTIC_CALL(host_duck_replay_keys(NFSHS_HostCurrentGameTicks(),&keys));
#endif
    static unsigned short last_keys=0xffff;
    if(keys!=last_keys){NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "pad keys=%04x",keys); NFSHS_HostLog(nfshsLogLine); }()));last_keys=keys;}
    pad_publish(0,1,keys);
    /* Only one keyboard-backed controller exists.  Advertising the same pad
       on port two made every frontend pulse execute twice, eventually drawing
       an uninitialized player-two car-select screen. */
    pad_publish(1,0,0xffff);
}

/* ---- Host file calls --------------------------------------------------------- */
static void host_path(const char *input,char *out,int cap)
{
    while(*input=='\\' || *input=='/') ++input;
    /* The native executable runs from bin while all extracted disc files live
       below bin\\DATA.  Keep the original game filenames untouched above this
       boundary and add the host data root only at the final file-system call. */
#if defined(_MSC_VER)
    _snprintf(out,cap,"DATA\\%s",input); out[cap-1]=0;
    for(char *p=out;*p;p++){ if(*p=='/')*p='\\'; if(*p==';'){*p=0;break;} }
#else
    snprintf(out,cap,"DATA/%s",input); out[cap-1]=0;
    for(char *p=out;*p;p++){ if(*p=='\\')*p='/'; if(*p==';'){*p=0;break;} }
#endif
    /* Extracted ISO filenames are uppercase, including on case-sensitive hosts */
    for(char *p=out;*p;++p) {
        if(*p>='a' && *p<='z') *p=(char)(*p-'a'+'A');
    }
}
int PCinit(void) { return 0; }
int PCopen(char *name,int mode,int)
{
    char path[520];
    host_path(name,path,sizeof(path));
    FILE *file = xport_fopen(path,mode ? "r+b" : "rb");
    if (!file) return -1;
    /* Retain a descriptor after releasing the unused buffered stream */
    int descriptor = _dup(_fileno(file));
    fclose(file);
    NFSHS_DIAGNOSTIC_CALL(([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "open fd=%d mode=%d path=%s",descriptor,mode,path); NFSHS_HostLog(nfshsLogLine); }()));
    return descriptor;
}
int PCcreat(char *name,int) { char p[520];host_path(name,p,sizeof(p));return _open(p,_O_CREAT|_O_TRUNC|_O_RDWR|_O_BINARY,_S_IREAD|_S_IWRITE); }
int PCclose(int fd) { return _close(fd); }
int PCread(int fd,void *p,int n) { int r=_read(fd,p,n); NFSHS_DIAGNOSTIC_CALL(static int calls; if(calls++<200)([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "read fd=%d dst=%p want=%d got=%d",fd,p,n,r); NFSHS_HostLog(nfshsLogLine); }())); return r; }
int PCwrite(int fd,const void *p,int n) { return _write(fd,p,n); }
long PClseek(int fd,long off,int whence) { long r=_lseek(fd,off,whence); NFSHS_DIAGNOSTIC_CALL(static int calls; if(calls++<200)([&]() { char nfshsLogLine[767] = {}; snprintf(nfshsLogLine, sizeof(nfshsLogLine), "seek fd=%d off=%ld whence=%d -> %ld",fd,off,whence,r); NFSHS_HostLog(nfshsLogLine); }())); return r; }

/* ---- CD surface.  Synchronous command behavior is sufficient for extracted files. */
int CdInit(void) { return 1; } int CdReset(int) { return 1; } int CdSetDebug(int) { return 0; }
int CdSync(int,unsigned char *r) { if(r)memset(r,0,8);return 2; } int CdDataSync(int) { return 0; }
int CdFlush(void) { return 1; } int CdGetDiskType(void) { return 2; }
int CdGetSector(void *,int) { return 0; }
int CdPosToInt(PsxCdlLoc *p) { return ((p->minute*60+p->second)*75+p->sector)-150; }
PsxCdlLoc *CdIntToPos(int i,PsxCdlLoc *p) { i+=150;p->minute=(unsigned char)(i/4500);i%=4500;p->second=(unsigned char)(i/75);p->sector=(unsigned char)(i%75);p->track=0;return p; }
PsxCdlFile *CdSearchFile(PsxCdlFile *,char *) { return 0; }

/* No persistent memory-card image is configured on Windows.  Preserve PsyQ's
 * accepted-command/async-completion contract and let the game's CRC check
 * reject the deterministic blank medium through its normal no-save path. */
static int g_host_memcard_pending;
static long g_host_memcard_command;
static long g_host_memcard_result;
long MemCardInit(long) { g_host_memcard_pending=0; g_host_memcard_command=0; g_host_memcard_result=0; return 1; }
long MemCardStart(void) { return 1; }
long MemCardStop(void) { return 1; } void MemCardEnd(void) {}
long MemCardExist(long) { g_host_memcard_command=1; g_host_memcard_result=0; g_host_memcard_pending=1; return 1; }
long MemCardAccept(long) { return 0; }
long MemCardSync(long mode,long *cmd,long *result)
{
    (void)mode;
    if(!g_host_memcard_pending) return -1;
    g_host_memcard_pending=0;
    if(cmd) *cmd=g_host_memcard_command;
    if(result) *result=g_host_memcard_result;
    return 1;
}
long MemCardFormat(long) { return 0; }
long MemCardCreateFile(long,char *,long) { return -1; } long MemCardDeleteFile(long,char *) { return -1; }
long MemCardReadFile(long channel,char *name,void *data,long offset,long bytes)
{
    (void)channel; (void)name; (void)offset;
    /* No persistent card image is configured yet.  Model a completed virtual
     * read with deterministic blank media; the game's own CRC validation then
     * follows its normal no-save path. */
    if(data && bytes>0) memset(data,0,(size_t)bytes);
    g_host_memcard_command=3; /* PsyQ file I/O command completion. */
    g_host_memcard_result=0;
    g_host_memcard_pending=1;
    return 1;
}
long MemCardWriteFile(long,char *,void *,long,long) { return -1; }
struct DIRENTRY;
long MemCardGetDirentry(long,char *,DIRENTRY *,int *,long,long) { return 0; }

/* ---- Explicitly disabled media ---------------------------------------------- */
void DecDCTReset(int) {}
void DecDCTin(uint32 *,int) {}
int DecDCTinSync(int) { return 0; }
void DecDCTout(uint32 *,int) {}
int DecDCToutCallback(void (*)(void)) { return 0; }
int DecDCTvlc(uint32 *,uint32 *) { return 0; }
int DecDCTvlcSize(int) { return 0; }
void StSetRing(uint32 *,uint32) {}
void StUnSetRing(void) {}
void StSetStream(uint32,uint32,uint32,void (*)(void),void (*)(void)) {}
void StClearRing(void) {}
uint32 StFreeRing(uint32 *) { return 0; }
uint32 StGetNext(uint32 **,uint32 **) { return 0; }
void StCdInterrupt(void) {}
int StCdIntrFlag=0;
uint32 *FntFlush(int) { return 0; }
void *SetSp(void *p) { return p; }

/* Explicit PSX libgcc calls present in the recovered source.  Native x86 can
 * implement them directly; these are not compiler-emitted helper calls. */
double __adddf3(double a,double b) { return a+b; }
double __divdf3(double a,double b) { return a/b; }
float __divsf3(float a,float b) { return a/b; }
double __extendsfdf2(float a) { return (double)a; }
int __fixdfsi(double a) { return (int)a; }
int __fixsfsi(float a) { return (int)a; }
double __floatsidf(int a) { return (double)a; }
float __floatsisf(int a) { return (float)a; }
int __ltdf2(double a,double b) { return a<b ? -1 : (a>b ? 1 : 0); }
double __muldf3(double a,double b) { return a*b; }
float __mulsf3(float a,float b) { return a*b; }
float __truncdfsf2(double a) { return (float)a; }
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
    return 0;
}

extern "C" int initmemadr(int,int);
extern "C" int largestunused(void);
extern "C" int getblocksize(void *);
extern "C" void *reservememadr(const char *,int,int);
extern "C" int purgememadr(void *);
void *__builtin_new(unsigned int);
void __builtin_delete(void *);

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

extern void nfs4_gte_set_rot_matrix(const void *);
extern void nfs4_gte_set_trans_matrix(const void *);
extern void nfs4_gte_rt(void);
extern void nfs4_gte_mvmva_sf1(void);
extern void gte_lwc2(int, int);
extern void gte_swc2(int, void *);

static int host_gte_mvmva_self_test(void)
{
    PsxMatrix matrix = {};
    PsxSVector vector = {1, -2, 3, 0};
    int mac[3] = {};

    matrix.m[0][0] = 4096;
    matrix.m[1][1] = 4096;
    matrix.m[2][2] = 4096;
    nfs4_gte_set_rot_matrix(&matrix);
    nfs4_gte_set_trans_matrix(&matrix);
    gte_lwc2(0, (unsigned short)vector.vx | ((int)(unsigned short)vector.vy << 16));
    gte_lwc2(1, (unsigned short)vector.vz);
    nfs4_gte_rt();
    gte_swc2(25, &mac[0]);
    gte_swc2(26, &mac[1]);
    gte_swc2(27, &mac[2]);
    if (mac[0] != 1 || mac[1] != -2 || mac[2] != 3)
        return 1;
    nfs4_gte_mvmva_sf1();
    gte_swc2(25, &mac[0]);
    gte_swc2(26, &mac[1]);
    gte_swc2(27, &mac[2]);
    return mac[0] == 1 && mac[1] == -2 && mac[2] == 3 ? 0 : 2;
}

static int host_pad_packet_self_test(void)
{
    uint8 first[8];
    uint8 second[8];
    sint32 index;
    PadInitDirect(first, second);
    PadStartCom();
    pad_publish(0, 1, 0xb7de);
    if (first[0] != 0 || first[1] != 0x41 || first[2] != 0xde || first[3] != 0xb7)
        return 1;
    pad_publish(1, 0, 0);
    for (index = 0; index < (sint32)sizeof(second); ++index)
    {
        if (second[index] != 0xff)
            return 2;
    }
    return 0;
}

extern "C" void NFSHS_ConfigurePsyQHost(void);

extern "C" {
#if defined(__EMSCRIPTEN__)
void NFSHS_HostMainInit(void) {
#else
void __main(void) {
#endif
#if NFSHS_DIAGNOSTICS

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

#else

#endif
    if (getenv("NFSHS_GTE_MVMVA_SELFTEST"))
        ExitProcess((UINT)host_gte_mvmva_self_test());
    NFSHS_ConfigurePsyQHost();
}
void __pure_virtual(void) { ExitProcess(3); }

}
