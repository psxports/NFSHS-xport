/* rpause_externs.h -- externs for game/psx/rpause.cpp (NFS4 replay pause-menu buffer mgmt) */
#ifndef _GAME_PSX_RPAUSE_EXTERNS_H_
#define _GAME_PSX_RPAUSE_EXTERNS_H_

#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ---- globals ---- */
extern "C" Draw_tView Draw_gView[]; /* 0x8011ec54 */
extern "C" dflip gEnviro[2];        /* 0x8011f424 */
extern "C" int Draw_gPlayer1View;   /* 0x8013d3cc */
extern PSX_RECT gPauseMenuRect;     /* 0x8013d3d4 */
extern int Render_gPauseMenuView;   /* 0x8013d3e8 */
extern "C" int gFlip;               /* 0x8013d7b4 */

/* ---- PSX::Draw / libgpu / libetc / eaclib helpers ---- */
extern "C"
{
    extern DRAWENV *Draw_GetDRAWENV(int view, int buf);
}
extern void Draw_StartFrameRender(void);
/* syslib libgpu */
/* eaclib EACPSXZ systask */

/* ---- this module ---- */
extern void RPause_CopyBackToFrontBuffer(void);

#endif
