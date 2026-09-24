/* frontend/common/fescreen_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_FESCREEN_EXTERNS_H_
#define _FE_SCREENS_FESCREEN_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ===== globals ===== */
extern "C" int ticks;
extern "C" extern char *Paths_Paths[];
extern "C" int Draw_gPlayer1View;   /* @0x8013d3cc */
extern "C" Draw_tView Draw_gView[]; /* @0x8011ec54 */
extern "C" dflip gEnviro[2];        /* @0x8011f424 */
extern "C" int screenheight;
extern "C" extern tTexture_ShapeInfo *gCurrentShapes; /* @0x800517cc */
extern __vtbl_ptr_type tScreen_vtable[];              /* _vt.7tScreen */

/* ===== statics owned by FEScreen.obj ===== */
extern int _7tScreen_fSuppressLoadingText; /* def in host/link_runtime.cpp */ /* @0x800517C8 */

/* ===== rendering / view ===== */
void Draw_StartFrameRender();
void Draw_StartRenderingView(int view);
void Draw_StopRenderingView(int view);
void Draw_StopFrameRender();
void GoNonInterlaced();
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
void PSXDrawSquare(int, int, int, int, int);

/* ===== text ===== */
void FETextRender_MenuTextPositionedJustify(short, short, short, short, tMenuTextState, tMenuTextType);
extern "C"
{
    char *TextSys_Word(int);
}
extern "C"
{
    int textpixels(char *);
}

/* ===== async shape I/O (eaclib) ===== */

/* ===== texture / draw helpers ===== */
void Texture_MenuReleaseClutId(short);
void FETexture_LoadPmxAtOffset(char *, int, tTexture_ShapeInfo *, int, int);
void FeAudio_systemtask(int);

/* ===== libc / libgpu / libetc ===== */

#endif
