/* frontend/screens/screentrophyroom_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENTROPHYROOM_EXTERNS_H_
#define _FE_SCREENS_SCREENTROPHYROOM_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* --- globals --- */
extern "C" extern tfrontEnd frontEnd;
extern tTournamentManager tournamentManager;
extern tGlobalMenuDefs *menuDefs;
extern "C" int ticks;
extern "C" extern tTexture_ShapeInfo *gCurrentShapes;
extern "C" tPadModuleState gPadinfo;

/* --- data owned by ScreenTrophyRoom.obj (EXT linkage) --- */
tScreenTrophyRoom *screenTrophyRoom;               /* EXT @0x80052060 (runtime-set) */
char gSwapFileName[16];                            /* EXT @0x80052064 */
extern __vtbl_ptr_type tScreenTrophyRoom_vtable[]; /* _vt.17tScreenTrophyRoom @0x80011e28 */

/* --- base tScreen ctor/dtor (name==class -> rendered as free helpers) --- */
extern "C"
{
    void tScreen_ctor(tScreen *s);
}
void tScreen_dtor(tScreen *s);

/* --- tScreen helpers (base passed explicitly) --- */
void DrawBackgroundImage(tScreen *s, int startShape, int numShapes, tTexture_ShapeInfo *shapes, int flip);
extern "C"
{
    void *IsShapeFileLoaded(tScreen *s, tShapeInformation *shp);
}
extern "C"
{
    void UploadSwapShapes(tScreen *s, int n);
}
void InitializeShapes(tScreen *s, tShapeInformation *shp, int n);
void AsyncLoadShapeFile(tScreen *s, char *name, tShapeInformation *shp);
void AsyncLoadSwapShapeFile(tScreen *s, char *name);
void FreeShapes(tScreen *s, tShapeInformation *shp);
void PreLoad(tScreen *s);
void ProcessInput(tScreen *s, tPlayer p, tInputKeyType &k, tMenuCommand &c);

/* --- FE / game / PsyQ helpers (de-namespaced) --- */
void GetTrophyName(tTournamentManager *tm, tTourneyInfo *ti, tTrophySize sz, char *buf, int n);
void AudioCmn_PlayFESFX(int sfx);
void FETexture_LoadPmxAtOffset(char *file, int off, tTexture_ShapeInfo *shapes, int a, int b);
extern "C"
{
    void DrawShapeExtended(int a, int b, int c, int d, int e, int f, tDrawShapeExtended *ext);
}
void ScaleShapeExtended(int a, int b, int c, int d, int e, int f, tDrawShapeExtended *ext);
void PSXDrawBrightEndLine(int a, int b, int c, int d, int e, int f, int g, int h);
extern "C"
{
    void FETextRender_MenuTextPositionedJustifyFade(int fade, int index, short x, short y, short j, tMenuTextState st, tMenuTextType tt);
}
extern "C"
{
    char *TextSys_Word(int id);
}
int CalcFadeVal(int rgb, int amount);
extern "C"
{
    void FETextRender_FullTextRGB(char *s, short x, short y, int rgb, char a, short b);
}

#endif
