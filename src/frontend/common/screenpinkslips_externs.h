/* frontend/screens/screenpinkslips_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENPINKSLIPS_EXTERNS_H_
#define _FE_SCREENS_SCREENPINKSLIPS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ===== globals ===== */
extern "C" extern tfrontEnd frontEnd;
extern tTrackManager trackManager;
extern tGlobalMenuDefs *menuDefs;
extern tFEApplication *FEApp;
extern "C" int ticks;
extern "C" extern char *Paths_Paths[];

/* ===== statics owned by ScreenPinkSlips.obj ===== */
tScreenPinkSlips *screenPinkSlips = 0;      /* @0x80051E64 bss(zero), owned here; referenced cross-TU (front.cpp/femenudefs) as pointer */
static char imageTVOrder[4] = {1, 2, 0, 3}; /* STAT @0x80051E60 - TV reveal order */
static char gSwapFileName[20];              /* STAT @0x80052C00 */
static int flareextra_248 = 0;              /* @0x80052bf0 fn-static, real bytes=00000000 (flare ramp counter) */

/* ===== free helpers (member fns rendered free by Ghidra; tScreen* first arg where applicable) ===== */
extern "C"
{
    void *IsShapeFileLoaded(tScreen *, tShapeInformation *);
}
extern "C"
{
    void UploadSwapShapes(tScreen *, int);
}
void AsyncLoadSwapShapeFile(tScreen *, char *);
short TextValue(tListIteratorTrack *, tPlayer);
void Increment(void *, tPlayer);
extern "C"
{
    void Decrement(void *, tPlayer);
}
void GetTrack(tTrackManager *, unsigned short, tTrackInformation *);

/* drawing / text */
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
extern "C"
{
    void DrawShape_NFS4RoundRectangle(int, PSX_RECT *, short);
}
void FETextRender_MenuTextPositionedJustify(short, short, short, short, tMenuTextState, tMenuTextType);
void Flare_2DHalo(int, int, int, int, int);
void PSXDrawTransSquare(int, int, int, int, int, short);
void FeDraw_SetABRMode(int);

/* TV tiles (FETv) */
extern "C"
{
    void DrawTV(tTVConfig *);
}
extern "C"
{
    void InitTV(tTVConfig *, tTexture_ShapeInfo *, short);
}
extern "C"
{
    void TurnOnTV(tTVConfig *);
}
extern "C"
{
    void TurnOffTV(tTVConfig *);
}

/* video (FRONTEND::PSX::video) */
intptr VIDEO_create(int, int, int, int, int);
void VIDEO_spoolfile(intptr, char *);
void VIDEO_startplayback(intptr);
void VIDEO_abortplayback(intptr);
void VIDEO_destroy(intptr);
extern "C"
{
    int VIDEO_state(intptr);
}
int VIDEO_updateframexy(intptr, int, int);

/* libgpu / libc / eaclib */

#endif
