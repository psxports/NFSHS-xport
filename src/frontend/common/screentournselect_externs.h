/* frontend/screens/screentournselect_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENTOURNSELECT_EXTERNS_H_
#define _FE_SCREENS_SCREENTOURNSELECT_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* --- globals --- */
extern "C" extern tfrontEnd frontEnd;
extern tTournamentManager tournamentManager;
extern tGlobalMenuDefs *menuDefs;
extern "C" int ticks;
extern "C" extern char *Paths_Paths[];

/* --- data owned by ScreenTournSelect.obj --- */
tScreenTournSelect *screenTournSelect;              /* EXT @0x8005205c (runtime-set) */
static char trophyTVOrder[4] = {1, 2, 0, 3};        /* STAT @0x80052058 real bytes=01 02 00 03 */
static char gSwapFileName[16];                      /* STAT @0x80052c90 */
extern __vtbl_ptr_type tScreenTournSelect_vtable[]; /* _vt.18tScreenTournSelect @0x80011f08 */

/* --- base tScreen ctor/dtor + helpers --- */
extern "C"
{
    void tScreen_ctor(tScreen *s);
}
void tScreen_dtor(tScreen *s);
void DrawBackgroundImage(tScreen *s, int startShape, int numShapes, tTexture_ShapeInfo *shapes, int flip);
extern "C"
{
    void *IsShapeFileLoaded(tScreen *s, tShapeInformation *shp);
}
extern "C"
{
    void UploadSwapShapes(tScreen *s, int n);
}
void AsyncLoadSwapShapeFile(tScreen *s, char *name);

/* --- PSX video player --- */
intptr VIDEO_create(int w, int h, int a, int b, int c);
extern "C"
{
    int VIDEO_state(intptr h);
}
int VIDEO_updateframexy(intptr h, int x, int y);
void VIDEO_spoolfile(intptr h, char *name);
void VIDEO_startplayback(intptr h);
void VIDEO_destroy(intptr h);

/* --- FETv video-wall tiles --- */
extern "C"
{
    void InitTV(tTVConfig *cfg, tTexture_ShapeInfo *shapes, short n);
}
extern "C"
{
    void TurnOnTV(tTVConfig *cfg);
}
extern "C"
{
    void TurnOffTV(tTVConfig *cfg);
}
extern "C"
{
    void DrawTV(tTVConfig *cfg);
}
extern "C"
{
    void DrawTVLines(tTVConfig *cfg);
}

/* --- FE / game / PsyQ helpers --- */
void GetTrophyName(tTournamentManager *tm, tTourneyInfo *ti, tTrophySize sz, char *buf, int n);
void PSXDrawTransSquare(int col, int x, int y, int w, int h, short op);
void ScaleShapeExtended(int a, int b, int c, int d, int e, int f, tDrawShapeExtended *ext);
void FeDraw_SetABRMode(int abr);
void PSXDrawBrightEndLine(int a, int b, int c, int d, int e, int f, int g, int h);
int CalcFadeVal(int rgb, int amount);
extern "C"
{
    char *TextSys_Word(int id);
}
extern "C"
{
    int TextSys_WordX(int id);
}
extern "C"
{
    int TextSys_WordY(int id);
}
extern "C"
{
    void DrawMoney(int x, int y, int digits, long amount, int rgb1, int rgb2);
}
void FETextRender_MenuTextFade(int fade, short index, tMenuTextState st, tMenuTextType tt);
extern "C"
{
    void FETextRender_FullTextRGB(char *s, short x, short y, int rgb, char a, short b);
}
extern "C"
{
    void FETextRender_WordWrapFade(int fade, short index, PSX_RECT *r, tMenuTextState st, tMenuTextType tt);
}
extern "C"
{
    void FETextRender_WordWrapTextRGB(char *s, PSX_RECT *r, int rgb);
}
extern "C"
{
    short FETextRender_WordWrapHeight(short w, char *s);
}
extern "C"
{
    void FETextRender_MenuTextPositionedJustifyFade(int fade, short index, short x, short y, short j, tMenuTextState st, tMenuTextType tt);
}
short TextValue(tListIteratorTournament *it, tPlayer p);

#endif
