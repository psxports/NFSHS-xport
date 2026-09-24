/* psxcontroller_externs.h -- externs for game/psx/psxcontroller.cpp (NFS4 in-game PSX pad mapping) */
#ifndef _GAME_PSX_PSXCONTROLLER_EXTERNS_H_
#define _GAME_PSX_PSXCONTROLLER_EXTERNS_H_

#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ---- globals ---- */
extern int Input_gHandler[];                           /* 0x80113c14  per-control packed input descriptor */
extern "C" extern tfrontEnd frontEnd;                  /* 0x80114600 */
extern "C" int mappings[][13][3];                      /* 0x80120dfc  [config][row][padtype] -> pad value selector */
extern Car_tObj *Cars_gHumanRaceCarList[];             /* 0x8010fa48 */
extern "C" extern int Cars_gNumHumanRaceCars;          /* 0x8013c800 */
extern "C" int Replay_ReplayMode;                      /* 0x8013d3f4 */
extern "C" int hoff[];                                 /* 0x8013dac0  per-player input-handler base offset */
extern "C" tPadModuleState gPadinfo;                   /* 0x8013e89c */
extern "C" extern "C" GameSetup_tData GameSetup_gData; /* 0x801131ec */

/* ---- helpers ---- */
/* eaclib PADPSXZ */

/* ---- this module (forward decls for intra-TU calls) ---- */
extern int InGame_GetPSXPadValue(int value, int player);
extern int InGame_GetDevice(int control);

#endif
