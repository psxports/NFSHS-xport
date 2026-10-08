/* frontend/screens/screencarselect_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENCARSELECT_EXTERNS_H_
#define _FE_SCREENS_SCREENCARSELECT_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
extern int _i, _reflection; /* DrawCar Ghidra phantom locals */

/* ===== globals ===== */
extern "C" tfrontEnd frontEnd;
extern tTournamentManager tournamentManager;
extern tTrackManager trackManager;
extern tGlobalMenuDefs *menuDefs;
extern tFEApplication *FEApp;
extern "C" int ticks;
extern "C" char *Paths_Paths[];
extern int kRGBVals[28];
extern "C" char textDefinitions[14][6];
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;
extern "C" tPadModuleState gPadinfo;
extern "C" int screenheight, showRoomFlag, gFlip, gShowroomLights, gStopCommentaryNow;
extern "C" int gMenuRotate[2];
extern uint32 gCameraRotation;
extern "C" DRender_tView gCView;
extern "C" Car_tObj *gCarObj[2];
extern "C"
{
    char *PlayerName(int player);
}
extern "C" char CURRENTLYUSINGMEMCARD;
extern "C" GameSetup_tData GameSetup_gData;
extern tCarManager carManager;
extern "C"
{
    void DrawC_MenuColorData(int color, Car_tObj *carObj, int player);
}
extern "C" int DrawC_gMenuLights, DrawC_gMenuLightsDirection;

/* ===== statics owned by ScreenCarSelect.obj ===== */
extern "C" PinkSlipsCarSelectState PinkSlipsScreenState[2];
// Initial data from FRONT.BIN, not BSS. CalcSplinePosition indexes these.
static int gKnots[8][5] = {/* STAT @0x80051e78 */
                           {491520, -524288, 17039360, 131072, 0}, {491520, -524288, 17039360, 131072, 0}, {196608, -524288, 17039360, 6684672, 11206656}, {196608, -524288, 17039360, 6684672, 22347776}, {688128, -524288, 17039360, -4718592, 33554432}, {196608, -524288, 17039360, 6684672, 44761088}, {196608, -524288, 17039360, 6684672, 55902208}, {196608, -524288, 17039360, 6684672, 55902208}};
static int gCatmullRom[4][4] = {/* STAT @0x80051f18 */
                                {-65536, 196608, -196608, 65536},
                                {131072, -327680, 262144, -65536},
                                {-65536, 0, 65536, 0},
                                {0, 131072, 0, 0}};
static tCarStatType remap[5];              /* STAT @0x80051f58 */
static short textVals[5], text2PVals[5];   /* STAT @0x80051f6c/f78 */
static short tvOrder[10], tvSplitOrder[5]; /* STAT @0x80051f84/f98 */
static char gStateOverlays[8][4];          /* STAT @0x80051fa4, 8 states x 4 slots */
static const PSX_RECT gOverlayPositions[7][2] = {
    /* STAT @0x80051fc4 */
    {{290, 256, 200, 12}, {290, 200, 200, 12}}, {{213, 256, 288, 41}, {213, 185, 288, 41}}, {{213, 256, 288, 41}, {213, 185, 288, 41}}, {{213, 256, 288, 41}, {213, 185, 288, 41}}, {{325, 5, 162, 24}, {325, 29, 162, 24}}, {{495, 21, 3, 3}, {213, 21, 285, 105}}, {{-120, 136, 130, 77}, {0, 136, 130, 77}},
};
static int gRotateOffset[4];      /* STAT @0x80052c18 */
static char gSwapFileName[2][40]; /* STAT @0x80052c28 */
static char WaitingString[50];    /* STAT @0x80052c58 */
/* vtable data refs (Ghidra _DAT_) + per-class vtables */
extern "C" __vtbl_ptr_type tScreenCarSelect_vtable[], tScreenCarSelectDuel_vtable[], tScreenCarSelectTwoPlayer_vtable[], tScreenPinkSlipsCarSelect_vtable[];
/* singletons (EXT) */
tScreenCarSelect *screenCarSelect;

/* ===== base ctor/dtor helpers ===== */
extern "C"
{
    void tScreen_ctor(tScreen *);
    void tScreen_dtor(tScreen *);
}
extern "C"
{
    void tScreenCarSelect_ctor(tScreenCarSelect *);
    void tScreenCarSelect_dtor(tScreenCarSelect *, int mode);
}
void tScreenCarSelectTwoPlayer_ctor(tScreenCarSelectTwoPlayer *);
void tScreenCarSelectTwoPlayer_dtor(tScreenCarSelectTwoPlayer *);
void tScreenCarSelectDuel_dtor(tScreenCarSelectDuel *);
void tScreenPinkSlipsCarSelect_dtor(tScreenPinkSlipsCarSelect *);

/* ===== tScreen helpers (free-fn form) ===== */
void DrawBackgroundImage(tScreen *, int, int, tTexture_ShapeInfo *, int);
extern "C"
{
    void *IsShapeFileLoaded(tScreen *, tShapeInformation *);
}
extern "C"
{
    void UploadShapes(tScreen *a0, tShapeInformation *a1, short a2, short a3, int a4, int a5);
}
void FreeShapes(tScreen *, tShapeInformation *);
void InitializeShapes(tScreen *, tShapeInformation *, int);
void AsyncLoadSwapShapeFile(tScreen *, char *);
void AsyncLoadShapeFile(tScreen *, char *, tShapeInformation *);
void TransitionOff(tScreen *, tScreen_TransitionType, tMenu *);
void TransitionOn(tScreen *, tScreen_TransitionType, tMenu *);

/* ===== tVideoWall methods (free-fn form) ===== */
void TurnOn(tVideoWall *);
void TurnOff(tVideoWall *);
void TurnOffInstant(tVideoWall *);
void UpdateImages(tVideoWall *);
void UpdateTransition(tVideoWall *);
void Draw(tVideoWall *);
void SetAvailable(tVideoWall *, unsigned short);
void SetAvailableText(tVideoWall *, short, short, short);
void SetAvailableIcon(tVideoWall *, short, short, short, short, tTexture_ShapeInfo *);
void Initialize(tVideoWall *, tTVConfig *, tTexture_ShapeInfo *, short, short, short *, short);

/* ===== FE / game / PsyQ helpers ===== */
int CalcFadeVal(int, int);
extern "C"
{
    char *TextSys_Word(int);
    int TextSys_WordX(int);
    int TextSys_WordY(int);
    int TextSys_WordFlags(int);
}
short TextValue(tListIteratorCar *, tPlayer);
extern "C"
{
    void Decrement(void *, tPlayer);
    void Increment(void *, tPlayer);
}
extern "C"
{
    void DrawMoney(int x, int y, int numplaces, long number, int colfore, int colback);
}
extern "C"
{
    void DrawShapeExtended(int index, int flags, int x, int y, int fade, int abr, tDrawShapeExtended *extra);
}
extern "C"
{
    void DrawShape_NFS4Rectangle(PSX_RECT &position);
    void DrawShape_NFS4RoundRectangle(int, PSX_RECT *, short);
}
extern "C"
{
    void DrawSlider(short value, short min, short max, short fX, short fY, short fWidth, short fHeight, short rectwidth, short rectspace, bool reverse, bool shadow, short fSelFade, short fFadeVal);
}
void PSXDrawSquare(int, int, int, int, int);
extern "C"
{
    void FETextRender_FullTextRGB(char *sMenuText, short x, short y, int col, char size, short justify);
}
void FETextRender_MenuTextPositionedJustify(short, short, short, short, tMenuTextState, tMenuTextType);
void FETextRender_WordWrap(short, PSX_RECT &, tMenuTextState, tMenuTextType);
extern "C"
{
    short FeAudio_AsyncPlaySpeech(int type, int index);
}
extern "C"
{
    void *FECheat_IsCheatEnabled(tCheatCode cheat);
}
short GetNumPinkSlipsCars(tCarManager *, short);
void GetStockCar(tCarManager *, unsigned short, tCarInfo *);
void GetTrack(tTrackManager *, unsigned short, tTrackInformation *);
extern "C"
{
    tTrackInformation *GetTrackByID(tTrackManager *, short);
    void GetTrackToRace(tTournamentManager *, void *);
}
short LoadGame(short player, bool PinkSlips, bool WithDialogs);
extern "C"
{
    int MCRD_handlecardevents(int card);
}
extern "C"
{
    char *Platform_GetDCTBuffer(int size, const char *string);
    void Platform_ResetDCTBuffer();
}
#include "../../game/psx/fe3dmenu.h"
extern "C" int Draw_gPlayer1View;
void SetOffset(tVideoWall *, short, short);
void SetValid(tVideoWall *, short);
extern "C"
{
    void Hide(void *);
    void Display(void *);
    void Redraw(void *);
}

/* re-added (varargs; one per line to avoid shared-line breakage) */
extern "C"
{
    void AudioMus_StopSong(int fadeticks);
    void CleanupSpinningCarsMenu(void);
    void DeInit_Memcard(void);
}
extern "C"
{
    void DrawShape_NFS4TransRectangle(PSX_RECT &r, short opacity);
    void FETextRender_MenuTextPositioned(short index, short x, short y, tMenuTextState textState, tMenuTextType textType);
    void Init_Memcard(bool redraw, bool pinkslips);
}
extern "C" void SetLicensePlate(void);
void TransformVector(int (*vect)[4], int (*transform)[4][4], int (*result)[4]);
extern "C" void UploadSwapShapes(tScreen *, int);
long CalcUsedPrice(tCarManager *, short);
long CheapestCarStockPrice(tCarManager *);
short GetNumOwnedCars(tCarManager *, short);
short GetNumTourneyCars(tCarManager *, short);
extern "C"
{
    CARDINFO_def *MCRD_getcard(int card);
}
extern "C" DRAWENV *Draw_GetDRAWENV(int, int);
void GetGarageCar(tCarManager *, unsigned short, tCarInfo *, int);
void GetPinkSlipsCar(tCarManager *manager, short garageNumber, tCarInfo *carInfo, short playerNum);

void PreLoad(tScreen *);
#endif
