#include "../../lib/libfns.h"
/* fe3dmenu_externs.h -- externs for fe3dmenu.cpp (3D showroom/car render; PsyQ math + soft-float) */
#ifndef FE3DMENU_EXTERNS_H
    #define FE3DMENU_EXTERNS_H

/* globals (SYM Globals.jsonl) */
extern "C" COORD16 Fe3D_lightsVertex[64]; /* 0x80051334  ARY STRUCT COORD16 x64 */
extern "C" COORD16 Fe3D_spotVertex[33];   /* 0x8005126c  ARY STRUCT COORD16 x33 */
extern "C" char bigBuf[];
extern "C" int gMenuRotate[2];
extern "C" extern int R3DCar_Clock, R3DCar_ClockLast, R3DCar_InMenu;
extern "C" int &Render_gMenuRenderFlag, &gScratchLastWord, generic128HzClock, stackSpeedUpEnbabledFlag, showRoomFlag;
extern intptr gWSavePtr;

/* PsyQ / EA fixed-point + matrix math */
void Math_NormalizeVector(coorddef *);
void Math_fasttransmult(matrixtdef *, matrixtdef *, matrixtdef *);

/* 3D car / texture / projection render */
void Texture_LoadMenuTexture(void);
void TrsProj_ResetTransPrecision(void);
void TrsProj_SetMenuProjection(int, int, int, int);
void R3DCar_InsertCarFacetMenu(Car_tObj *, DRender_tView *);
void R3DCar_InsertCarFacetMenuII(Car_tObj *, int);
void R3DCar_Showroom(DRender_tView *);

/* GCC soft-float intrinsics (PSX has no FPU) */
long long CONCAT44(unsigned int, unsigned int);

#endif
