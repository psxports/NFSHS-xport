#include "../../lib/libfns.h"
/* draw_externs.h -- extern decls for game/psx/draw.cpp (NFS4 PSX base render-management). */
#ifndef DRAW_EXTERNS_H
    #define DRAW_EXTERNS_H

/* ---- SYM typedef ---- */
typedef void fn_void(void); /* SYM callback type: void(*)(void) */

/* ---- PsyQ libgpu/libgte/eaclib ---- */
extern "C" int timerhz; /* global tick-rate (used as value: timerhz>>1) */
                        /* DR_ENV pkt + env (2-arg libgpu form) */

/* ---- harvested from sealed *_externs.h ---- */
extern "C" Draw_tView Draw_gView[]; /* @0x8011ec54 */
extern "C" extern GameSetup_tData GameSetup_gData;
extern "C" char *&Render_gPacketEnd;
extern "C" dflip gEnviro[2]; /* @0x8011f424 */
extern "C" int Draw_gPlayer1View, Draw_gPlayer2View;
extern "C" int Draw_gPlayer1View; /* @0x8013d3cc */
extern "C" int Draw_gDoVSync;
extern "C" int Draw_gMidGroundOtz;
extern "C" int Draw_gViewOtSize;
extern "C" int gFlip;
extern int Draw_gPlayer1View;
extern "C" short &Render_gPacketLenLo, &Render_gPacketLenHi;
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;
extern "C" u_char *&Render_gPacketPtr; /* PSX scratchpad 0x1F800004: GPU packet build ptr */

/* ---- SYM Globals (type+dims) + free fns ---- */
extern "C" int Draw_gMaxPrim;
extern "C" int Draw_gNumView;
extern fn_void *Draw_gSyncCallback; /* void(*)(void) drawsync cb */
extern "C" int gLoop;
extern "C" int gTotalMem;
extern "C"
{
    extern void *Platform_ReserveMemory(int, char *);
}
extern void Texture_Vramcf(shapetbl *, int, int, int, int);

extern "C" int &Render_gMenuRenderFlag;

#endif
