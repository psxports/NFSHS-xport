/* frontend/screens/screenmain_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENMAIN_EXTERNS_H_
#define _FE_SCREENS_SCREENMAIN_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ===== globals ===== */
extern "C" extern tfrontEnd frontEnd;
extern tGlobalMenuDefs *menuDefs;
extern tFEApplication *FEApp;
extern "C" int ticks;
extern "C" extern char *Paths_Paths[];
extern tCreditManager CreditManager;
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;

/* ===== statics owned by ScreenMain.obj ===== */
extern "C" tScreenMain screenMain;                                                /* EXT @0x80051E58 */
static char tvOrder[16] = {5, 14, 3, 8, 6, 0, 11, 13, 2, 15, 4, 10, 1, 12, 7, 9}; /* STAT @0x80051AA8 */
static int tintColors[28] = {                                                     /* STAT @0x80051AB8 */
                             0x216b8e, 0x216b8e, 0x293700, 0x293700, 0x5c2a18, 0x5c2a18, 0x5c2a18, 0x5c2a18, 0x216b8e, 0x216b8e, 0x5c2a18, 0x5c2a18, 0x0c0c4d, 0x0c0c4d, 0x0c0c4d, 0x0c0c4d, 0x293700, 0x293700, 0x694d3e, 0x694d3e, 0x5c2a18, 0x5c2a18, 0x0c0c4d, 0x0c0c4d, 0x694d3e, 0x694d3e, 0x5f4431, 0x5f4431};
static tVertex dropShadow[4][4] = {/* STAT @0x80051B28 */
                                   {{163, 42}, {163, 210}, {183, 52}, {183, 200}},
                                   {{163, 42}, {483, 42}, {183, 52}, {463, 52}},
                                   {{483, 42}, {483, 210}, {463, 52}, {463, 200}},
                                   {{163, 210}, {483, 210}, {183, 200}, {463, 200}}};
static tVertex animLocations[4] = {{163, 42}, {403, 42}, {163, 168}, {403, 168}}; /* STAT @0x80051B68 */
extern tVideoWallConfig videoWallConfigs[24];                                     /* STAT @0x80051C78 (initialized elsewhere) */
static char numberValues[25];                                                     /* STAT @0x80052B90 (rand-filled at init) */
static char gNameBuffer[32];                                                      /* STAT @0x80052BB0 */
static char gPermBuffer[32];                                                      /* STAT @0x80052BD0 */

/* ===== free helpers (member fns rendered free by Ghidra; tScreen* first arg where applicable) ===== */
extern "C"
{
    void *IsShapeFileLoaded(tScreen *, tShapeInformation *);
}
extern "C"
{
    void UploadShapes(tScreen *, tShapeInformation *, short, short, int, int);
}
extern "C"
{
    void UploadSwapShapes(tScreen *, int);
}
void AsyncLoadSwapShapeFile(tScreen *, char *);
void AsyncLoadShapeFile(tScreen *, char *, tShapeInformation *);
void InitializeShapes(tScreen *, tShapeInformation *, unsigned int);
void FreeShapes(tScreen *, tShapeInformation *);
void DrawBackgroundImage(tScreen *, int, int, tTexture_ShapeInfo *, int);

/* drawing / text / TV */
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
void ScaleShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
void PSXDrawTransSquare(int, int, int, int, int, short);
void PSXDrawSquare(int, int, int, int, int);
void FeDraw_SetABRMode(int);
extern "C"
{
    void FETextRender_SetABR(int, bool);
}
extern "C"
{
    void FETextRender_WordWrapTextRGB(char *, PSX_RECT *, int);
}
int CalcFadeVal(int, int);
extern "C"
{
    char *TextSys_Word(int);
}
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

/* credits manager (member fns rendered free by Ghidra) */
void Init(tCreditManager *, u_long);
void DeInit(tCreditManager *);
void Draw(tCreditManager *, int);

/* video / credits / misc */
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
void FeAudio_systemtask(int);

#endif
