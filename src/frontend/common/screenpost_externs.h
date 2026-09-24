#ifndef SCREENPOST_EXTERNS_H
#define SCREENPOST_EXTERNS_H
/* frontend/screens/screencarselect_externs.h - reconstructed externs. NOT original. */
#define _FE_SCREENS_SCREENCARSELECT_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
typedef int code(...);      /* Ghidra fn-ptr type for vtable dispatch */
extern int _i, _reflection; /* DrawCar Ghidra phantom locals */

/* ===== globals ===== */
extern "C" extern tfrontEnd frontEnd;
extern tTournamentManager tournamentManager;
extern tTrackManager trackManager;
extern tGlobalMenuDefs *menuDefs;
extern tFEApplication *FEApp;
extern "C" int ticks;
extern "C" extern char *Paths_Paths[];
extern int kRGBVals[28];
extern "C" char textDefinitions[14][6];
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;
extern "C" tPadModuleState gPadinfo;
extern "C" int screenheight, showRoomFlag, gFlip, gShowroomLights, gStopCommentaryNow;
extern "C" int gMenuRotate[2];
extern u_long gCameraRotation;
extern "C" extern DRender_tView gCView;
extern "C" Car_tObj *gCarObj[2];
extern "C"
{
    char *PlayerName(int player);
}
extern "C" char CURRENTLYUSINGMEMCARD;
extern "C" extern "C" GameSetup_tData GameSetup_gData;
extern tCarManager carManager;
extern "C"
{
    void DrawC_MenuColorData(...);
}
extern "C" int DrawC_gMenuLights, DrawC_gMenuLightsDirection;

/* ===== statics owned by ScreenCarSelect.obj ===== */
extern "C" PinkSlipsCarSelectState PinkSlipsScreenState[2];
static int gKnots[8][5];                   /* STAT @0x80051e78 spline knots */
static int gCatmullRom[4][4];              /* STAT @0x80051f18 */
static tCarStatType remap[5];              /* STAT @0x80051f58 */
static short textVals[5], text2PVals[5];   /* STAT @0x80051f6c/f78 */
static short tvOrder[10], tvSplitOrder[5]; /* STAT @0x80051f84/f98 */
static char gStateOverlays[1][32];         /* STAT @0x80051fa4 */
static char gOverlayPositions[1][112];     /* STAT @0x80051fc4 */
static int gRotateOffset[4];               /* STAT @0x80052c18 */
static char gSwapFileName[2][40];          /* STAT @0x80052c28 */
static char WaitingString[50];             /* STAT @0x80052c58 */
/* vtable data refs (Ghidra _DAT_) + per-class vtables */
extern "C" __vtbl_ptr_type tScreenCarSelect_vtable[], tScreenCarSelectDuel_vtable[], tScreenCarSelectTwoPlayer_vtable[], tScreenPinkSlipStandings_vtable[];
/* singletons (EXT) */
extern tScreenCarSelect *screenCarSelect; /* def in screencarselect.cpp */

/* ===== base ctor/dtor helpers ===== */
extern "C"
{
    void tScreen_ctor(tScreen *);
    void tScreen_dtor(tScreen *);
}
extern "C"
{
    void tScreenCarSelect_ctor(tScreenCarSelect *);
    void tScreenCarSelect_dtor(tScreenCarSelect *);
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
    void UploadShapes(...);
}
void FreeShapes(tScreen *, tShapeInformation *);
void InitializeShapes(tScreen *, tShapeInformation *, int);
void AsyncLoadSwapShapeFile(tScreen *, char *);
void AsyncLoadShapeFile(tScreen *, char *, tShapeInformation *);
void TransitionOff(...);
void TransitionOn(...);

/* ===== tVideoWall methods (free-fn form) ===== */
void TurnOn(tVideoWall *);
void TurnOff(tVideoWall *);
void TurnOffInstant(tVideoWall *);
void UpdateImages(tVideoWall *);
void UpdateTransition(tVideoWall *);
void Draw(tVideoWall *);
void SetAvailable(tVideoWall *, unsigned short);
void SetAvailableText(tVideoWall *, short, short, short);
void SetAvailableIcon(...);
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
extern "C"
{
    short TextValue(void *, tPlayer);
    void Decrement(void *, tPlayer);
    void Increment(void *, tPlayer);
}
extern "C"
{
    void DrawMoney(int x, int y, int numplaces, long number, int colfore, int colback);
}
extern "C" void DrawShapeExtended(int index, int flags, int x, int y, int fade, int abr, tDrawShapeExtended *extra);
extern "C"
{
    void DrawShape_NFS4Rectangle(...);
    void DrawShape_NFS4RoundRectangle(int, PSX_RECT *, short);
}
extern "C"
{
    void DrawSlider(...);
}
void PSXDrawSquare(int, int, int, int, int);
void FETextRender_MenuTextPositionedJustify(short, short, short, short, tMenuTextState, tMenuTextType);
void FETextRender_WordWrap(...);
extern "C"
{
    void FeAudio_AsyncPlaySpeech(...);
}
extern "C"
{
    void *FECheat_IsCheatEnabled(...);
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
    void MCRD_handlecardevents(...);
}
extern "C"
{
    char *Platform_GetDCTBuffer(...);
    void Platform_ResetDCTBuffer();
}
#include "../../game/psx/fe3dmenu.h"
extern "C" int Draw_gPlayer1View;
void SetOffset(...);
extern "C"
{
    void SetValid(...);
    void Hide(void *);
    void Display(void *);
    void Redraw(void *);
}

/* re-added (varargs; one per line to avoid shared-line breakage) */
extern "C"
{
    void AudioMus_StopSong(...);
    void CleanupSpinningCarsMenu(...);
    void DeInit_Memcard(...);
}
extern "C"
{
    void DrawShape_NFS4TransRectangle(...);
    void FETextRender_MenuTextPositioned(...);
    void Init_Memcard(...);
}
void SetLicensePlate(...);
void TransformVector(...);
void UploadSwapShapes(...);
long CalcUsedPrice(tCarManager *, short);
long CheapestCarStockPrice(tCarManager *);
short GetNumOwnedCars(tCarManager *, short);
short GetNumTourneyCars(tCarManager *, short);
extern "C"
{
    CARDINFO_def *MCRD_getcard(...);
}
extern "C" DRAWENV *Draw_GetDRAWENV(int, int);
void GetGarageCar(tCarManager *, unsigned short, tCarInfo *, int);
void *GetPinkSlipsCar(...);

void PreLoad(tScreen *);

/* --- ScreenPost.obj-specific externs --- */
extern "C"
{
    int FeTools_FormatMoney(char *out, long amount);
}
extern "C"
{
    int FETextRender_FullTextRGB(char *s, short x, short y, int col, char a, int b);
}
void FETextRender_FullTextFade(int fade, char *text, short x, short y, tMenuTextType type, tMenuTextState state, short justify);
extern "C" void FETextRender_MenuTextPositionedJustifyFade(int fade, short index, short x, short y, short justify, tMenuTextState state, tMenuTextType type);
void AudioCmn_PlayFESFX(int sfx);
void CalcTrackFinishDamageBill(tTournamentManager *, bool, long *, long *);
short Front_GetTrackRaced(void);
extern "C"
{
    int GetAwardInformation(...);
}
void PSXDrawBrightEndLine(int col, int x, int y, int w, int h, int side, int fade, int darksides);
char *Stattool_GetAINameFromPersonality(tPersonalities personality);
extern "C"
{
    int textpixels(char *text);
}
int tScreen_ProcessInput(tScreen *, tPlayer, tInputKeyType &, tMenuCommand &);
extern "C" extern tTexture_ShapeInfo *gCurrentShapes;
extern "C" __nfs4_vtbl_ptr_t tScreenTournamentStandings_vtable[10], tScreenTournamentStandings3item_vtable[10], tScreenPinkSlipStandings_vtable[10];

/* ===== singletons owned by ScreenPost.obj (.bss zero, referenced cross-TU: front.cpp/femenudefs) ===== */
tScreenTournamentStandings *screenTournamentStandings = 0;           /* @0x80051e68 bss(zero) */
tScreenTournamentStandings3item *screenTournamentStandings3item = 0; /* @0x80051e6c bss(zero) */
tScreenPinkSlipStandings *screenPinkSlipStandings = 0;               /* @0x80051e70 bss(zero) */

#endif
