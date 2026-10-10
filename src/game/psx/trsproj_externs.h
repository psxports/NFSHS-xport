#include "../../lib/libfns.h"
/* trsproj_externs.h -- externs referenced by trsproj.cpp (GAME/PSX/TRSPROJ.CPP transform+projection) */
#ifndef TRSPROJ_EXTERNS_H
    #define TRSPROJ_EXTERNS_H

#include "psx_gte.h"

/* ---- globals (SYM Globals.jsonl) ---- */
/* TrsProj_precision (0x8013db9c) is TrsProj.obj-OWNED -> DEFINED in trsproj.cpp (=10), not externed. */
extern long Camera_gGeomScreen[2];          /* 0x8013c7dc; empty format word at +4 */
extern "C" GameSetup_tData GameSetup_gData; /* 0x801131ec */

/* ---- eaclib transform (fixed-point matrix*vector; func_800EAED8) ---- */

#endif /* TRSPROJ_EXTERNS_H */
