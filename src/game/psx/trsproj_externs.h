#include "../../lib/libfns.h"
/* trsproj_externs.h -- externs referenced by trsproj.cpp (GAME/PSX/TRSPROJ.CPP transform+projection) */
#ifndef TRSPROJ_EXTERNS_H
    #define TRSPROJ_EXTERNS_H

    /* ---- PsyQ libgte.h GTE (COP2) inline macros (mirror <libgte.h>; no-op for the host syntax check) ---- */
    #ifdef AP_WIN
extern "C" void NFSHS_GTE_SetRotMatrix(const void *m);
extern "C" void NFSHS_GTE_SetTransMatrix(const void *m);
extern "C" void NFSHS_GTE_LoadV0(const void *v);
extern "C" void NFSHS_GTE_MVMVA(void);
extern "C" void NFSHS_GTE_StoreLVNL(void *v);
extern "C" void NFSHS_GTE_SetGeomScreen(int h);
extern "C" void NFSHS_GTE_SetGeomOffset(int x, int y);
extern "C" void NFSHS_GTE_WriteControl(int reg, int value);
        #define gte_SetRotMatrix(m) NFSHS_GTE_SetRotMatrix(m)
        #define gte_SetTransMatrix(m) NFSHS_GTE_SetTransMatrix(m)
        #define gte_SetGeomScreen(h) NFSHS_GTE_SetGeomScreen(h)
        #define SetGeomScreen(h) gte_SetGeomScreen(h)
        #define gte_SetGeomOffset(x, y) NFSHS_GTE_SetGeomOffset((x), (y))
    #else
        #define gte_SetRotMatrix(m) ((void)(m))
        #define gte_SetTransMatrix(m) ((void)(m))
        #define gte_SetGeomScreen(h) ((void)(h))
        #define SetGeomScreen(h) gte_SetGeomScreen(h)
        #define gte_SetGeomOffset(x, y) ((void)0)
    #endif
    #ifdef AP_WIN
        #define gte_ldv0(v) NFSHS_GTE_LoadV0(v)
        #define gte_mvmva(...) NFSHS_GTE_MVMVA()
        #define gte_stlvnl(p) NFSHS_GTE_StoreLVNL(p)
    #else
        #define gte_ldv0(v) ((void)(v))
        #define gte_mvmva(...) ((void)0)
        #define gte_stlvnl(p) ((void)(p))
    #endif
    #ifdef AP_WIN
        #define gte_ctc2(v, r) NFSHS_GTE_WriteControl((r), (v))
    #else
        #define gte_ctc2(v, r) __asm__ volatile("ctc2 %0,$%1" : : "r"(v), "i"(r))
    #endif

/* ---- globals (SYM Globals.jsonl) ---- */
/* TrsProj_precision (0x8013db9c) is TrsProj.obj-OWNED -> DEFINED in trsproj.cpp (=10), not externed. */
extern long Camera_gGeomScreen[2];                 /* 0x8013c7dc; empty format word at +4 */
extern "C" extern GameSetup_tData GameSetup_gData; /* 0x801131ec */

/* ---- eaclib transform (fixed-point matrix*vector; func_800EAED8) ---- */

#endif /* TRSPROJ_EXTERNS_H */
