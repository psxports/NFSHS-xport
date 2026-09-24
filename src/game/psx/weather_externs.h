#include "../../lib/libfns.h"
/* weather_externs.h -- externs referenced by weather.cpp (GAME/PSX/WEATHER.CPP particle weather) */
#ifndef WEATHER_EXTERNS_H
    #define WEATHER_EXTERNS_H

    /* ---- PsyQ libgte.h GTE (COP2) inline macros. */
    #ifdef AP_WIN
extern void gte_rtps(void);
extern void gte_rtpt(void);
extern void gte_lwc2(int, int);
extern void gte_swc2(int, void *);
extern void nfs4_gte_set_rot_matrix(const void *);
extern void nfs4_gte_set_trans_matrix(const void *);
extern void nfs4_gte_rt(void);
        #define gte_SetRotMatrix(m) nfs4_gte_set_rot_matrix(m)
        #define gte_SetTransMatrix(m) nfs4_gte_set_trans_matrix(m)
        #define gte_SetRotMatrix_pc(m) nfs4_gte_set_rot_matrix(m)
        #define gte_ldv0(v) \
            do \
            { \
                gte_lwc2(0, *(int *)(v)); \
                gte_lwc2(1, *(short *)((char *)(v) + 4)); \
            } while (0)
        #define gte_ldv1(v) \
            do \
            { \
                gte_lwc2(2, *(int *)(v)); \
                gte_lwc2(3, *(short *)((char *)(v) + 4)); \
            } while (0)
        #define gte_ldv2(v) \
            do \
            { \
                gte_lwc2(4, *(int *)(v)); \
                gte_lwc2(5, *(short *)((char *)(v) + 4)); \
            } while (0)
        #define gte_ldv3(a, b, c) \
            do \
            { \
                gte_ldv0(a); \
                gte_ldv1(b); \
                gte_ldv2(c); \
            } while (0)
        #define gte_rt() nfs4_gte_rt()
        #define gte_stsxy(p) gte_swc2(14, (p))
        #define gte_stsxy3(a, b, c) \
            do \
            { \
                gte_swc2(12, (a)); \
                gte_swc2(13, (b)); \
                gte_swc2(14, (c)); \
            } while (0)
        #define gte_stsz(p) gte_swc2(19, (p))
        #define gte_stlvnl(p) \
            do \
            { \
                gte_swc2(25, (p)); \
                gte_swc2(26, (char *)(p) + 4); \
                gte_swc2(27, (char *)(p) + 8); \
            } while (0)
        #define gte_mvmva(...) nfs4_gte_rt()
    #else
        #define gte_SetRotMatrix(m) ((void)(m))
        #define gte_SetTransMatrix(m) ((void)(m))
        #define gte_SetRotMatrix_pc(m) ((void)(m))
        #define gte_ldv0(v) ((void)(v))
        #define gte_ldv1(v) ((void)(v))
        #define gte_ldv2(v) ((void)(v))
        #define gte_ldv3(v0, v1, v2) ((void)0)
        #define gte_rtps() ((void)0)
        #define gte_rtpt() ((void)0)
        #define gte_rt() ((void)0)
        #define gte_stsxy(p) ((void)(p))
        #define gte_stsxy3(a, b, c) ((void)0)
        #define gte_stsz(p) ((void)(p))
        #define gte_stlvnl(p) ((void)(p))
        #define gte_ctc2(v, r) ((void)0)
        #define gte_lwc2(r, v) ((void)0)
        #define gte_swc2(r, p) ((void)0)
        #define gte_mvmva(...) ((void)0)
    #endif

/* ---- Weather state globals (SYM Globals.jsonl) ---- */
extern "C" int Weather_gDensityTbl[4];                      /* 0x80123384 */
extern "C" int Weather_gIntensityTbl[4];                    /* 0x80123394 */
extern "C" int Weather_gTrackIntensityLimitTbl[16];         /* 0x801233a4 */
extern "C" char Weather_gRandomVelocityVectors[12][3];      /* 0x801233e4 */
extern "C" Weather_tSys Weather_gSys;                       /* 0x80123408  main state struct */
extern "C" char *Weather_gWasDrawn;                         /* 0x8013dba4 */
extern "C" SVECTOR *Weather_gPos;                           /* 0x8013dba8 */
extern "C" Weather_tSplatInfo *Weather_gSplatInfo;          /* 0x8013dbac */
extern "C" DVECTOR *Weather_gPrevPos;                       /* 0x8013dbb0 */
extern "C" CWeatherSpec *Weather_gTrackSpec;                /* 0x8013dbc4 */
extern "C" Weather_tSplatInfo *Weather_gSplatInfoServer[2]; /* 0x8013dbc8 */
extern "C" SVECTOR *Weather_gPServer[2];                    /* 0x8013dbd0 */
extern "C" DVECTOR *Weather_gPrevPServer[2];                /* 0x8013dbd8 */
extern "C" char *Weather_gDrawnServer[2];                   /* 0x8013dbe0 */
extern long Weather_gLastTimeProcessed;                     /* 0x8013dbe8 */
extern "C" int Weather_gType;                               /* 0x8013dbec  enum Weather_tState */
extern "C" int Weather_gDensityGoalState;                   /* 0x8013dbf0 */
extern "C" int Weather_gIntensityGoalState;                 /* 0x8013dbf4 */
extern "C" int Weather_gDensityChangeFactor;                /* 0x8013dbf8 */
extern "C" int Weather_gIntensityChangeFactor;              /* 0x8013dbfc */
extern "C" int Weather_gDensityTimerGoal;                   /* 0x8013dc00 */
extern "C" int Weather_gIntensityTimerGoal;                 /* 0x8013dc04 */
extern "C" int Weather_gSnowTrack;                          /* 0x8013dc08 */
extern "C" int Weather_gTrackIntensityLimit;                /* 0x8013dc0c */
extern "C" int Weather_gLastProcessTime[2];                 /* 0x8013de54 */

/* ---- shared game globals (SYM Globals.jsonl; declared in their owning TUs) ---- */
extern "C" extern GameSetup_tData GameSetup_gData; /* 0x801131ec */
extern "C" Sim_tSimGlobalVar simGlobal;            /* 0x8011e0ac */
extern "C" CTrackSpec TrackSpec_gSpec;             /* 0x8012327c */
extern camera_info Camera_gInfo[2];                /* 0x8010f2ac */
extern "C" coorddef prevCamPos[2];                 /* 0x8012342c */
extern "C" matrixtdef prevCamMat[2];               /* 0x80123444 */
extern "C" int gCurrentNumSplats;                  /* 0x8013dba0 */

/* ---- external subsystems (eaclib + game-side; sigs from call sites) ---- */
/* eaclib EACPSXZ random  */
/* eaclib EACPSXZ memstd  */
/* eaclib EACPSXZ memstd */
extern void Math_NormalizeVector(coorddef *v);                                 /* game math (mangled __FP8coorddef) */
                                                                               /* 16.16 fixed-point multiply */
extern void Math_fasttransmult(matrixtdef *a, matrixtdef *b, matrixtdef *out); /* __FP10matrixtdefN20 */
extern int Camera_GetMode(int player);                                         /* __Fi */
extern void *BWorldSm_TunnelFlagSm(BWorldSm_Pos *slicePos);                    /* __FP12BWorldSm_Pos -> void* */
                                                                               /* PsyQ libgpu */

/* render packet/palette write cursors + per-player weather pixmaps + look-behind input */
extern "C" char *&Render_gPacketPtr;    /* GPU primitive write cursor   */
extern "C" char *&Render_gPalettePtr;   /* shared palette/template word */
extern Draw_tPixMap *gWeatherPixmap[3]; /* 0x80112b7c  snow/rain sprites */
extern int Input_gLookBehind[2];        /* 0x8013d230 */
extern int timechange;                  /* 0x8013de4c */

#endif /* WEATHER_EXTERNS_H */
