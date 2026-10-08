/* frontend/common/femenudefs_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FEMENUDEFS_EXTERNS_H_
#define _FE_FEMENUDEFS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C" int ticks;
extern "C" tfrontEnd frontEnd;
extern tFEApplication *FEApp;
extern tGlobalMenuDefs *menuDefs;
extern "C" char *Paths_Paths[];
extern tCarManager carManager;
extern tTournamentManager tournamentManager;
extern tTrackManager trackManager;
/* screen pointer globals */
extern "C" tScreenMain *screenMain;
extern tScreenCarSelect *screenCarSelect;
extern tScreenUserName *screenUserName;
extern tAllScreens *gAllScreens;
/* menu-option select lists */
extern short SelectListNull[2], SelectListOffOn[3], SelectListTrackDirection[3], SelectListNormal[3];
extern short SelectListOpponentUpgrades[3], SelectListTransmission[3], SelectListDisplaySpeed[5];
extern short SelectListDisplayMap[4], SelectListDisplayOpponentID[4], SelectListSplitTime[4];
extern short SelectListSplitDisplay[3], SelectListUpgrades[4], SelectListControllerConfig[4], SelectListAudioMode[4];

/* ===== auto-generated stubs ===== */
void AudioCmn_PlayFESFX(int);
long CalcUsedPrice(tCarManager *, short);
long CheapestCarStockPrice(tCarManager *);
extern "C"
{
    void DeInit_Memcard(void);
}
extern "C"
{
    void Display(tDialogBase *dialog);
}
extern "C"
{
    void *FECheat_IsTheUserACryBabyCheater(void);
}
extern "C"
{
    void GetAwardInformation(tTournamentManager *manager, tAwardInformation *info);
}
tCarInfo *GetCarFromID(tCarManager *, short);
void GetGarageCar(tCarManager *, unsigned short, tCarInfo *, int);
short GetNumOwnedCars(tCarManager *, short);
short GetNumTourneyCars(tCarManager *, short);
extern "C"
{
    void GetPinkSlipsCar(tCarManager *manager, short garageNumber, tCarInfo *carInfo, short playerNum);
}
void GetStockCar(tCarManager *, unsigned short, tCarInfo *);
void GetTrack(tTrackManager *, unsigned short, tTrackInformation *);
extern "C"
{
    void Hide(tDialogBase *dialog);
}
extern "C"
{
    void Init_Memcard(bool redraw, bool pinkslips);
}
short IsTournamentFinished(tTournamentManager *);
short LoadGame(short player, bool PinkSlips, bool WithDialogs);
extern "C"
{
    char *PlayerName(int player);
}
long PurchaseCar(tCarManager *, short, short, short);
long PurchaseUpgrade(tCarManager *, short, short, short);
extern "C"
{
    void Redraw(tFEApplication *application);
}
extern "C"
{
    short Run(tDialogInteractive *dialog);
}
extern "C"
{
    void *SaveGame(short player);
}
PinkSlipsErrorCode SavePinkSlipsCarsWithErrorDialogs(short player, short WillLoseCar, short withoutCarInGarageNumber);
void SetCarAvailable(tCarManager *, int, bool);
void SetDimensions(tMenuItemLeftRightSlider *, short, short, short, short);
void SetState(tScreenCarSelect *, int);
extern "C"
{
    void StatChk_ClearNewRecords(void);
}
extern "C"
{
    void *StatChk_IsRecordLapTime(Car_tStats *cars, short count, short *bestCar);
}
extern "C"
{
    short StatChk_IsTopTime(Car_tStats *cars, short count);
}
extern "C"
{
    void StatChk_SaveRecordLapTime(Car_tStats *cars, short count, short bestCar);
}
extern "C"
{
    void StatChk_SaveTopTime(Car_tStats *cars, short count);
}
void SwapBackground(tScreenMain *, int);
extern "C"
{
    char *TextSys_Word(int);
}
void __builtin_delete(void *deleteMe);
void tDialogYesNo_ctor(tDialogYesNo *);
extern "C"
{
    void tListIterator_dtor(tListIterator *iterator, int mode);
}
extern "C"
{
    tMenuNFS4 *tMenuNFS4_ctor(tMenuNFS4 *menu, u_int flags, tScreen *screen, tMenu *next, tMenu *options, void (*onPress)(tMenuCommand &), short title, tMenuItem *first, std::initializer_list<tMenuItem *> items);
}
void tScreen_dtor(tScreen *, int);
extern "C" int CURRENTLYUSINGMEMCARD;
extern "C" Car_tStats Cars_gNewCarStatsList[9];
extern int Cars_gNumRaceCars;
extern "C" GameSetup_tData GameSetup_gData;
extern "C" int MEMCARD_INITIALIZED;

extern int gCarActivation[6][5];
extern "C" tPadModuleState gPadinfo;
extern tScreenAudio *screenAudio;
extern tScreenBeTheCopCongrats *screenBeTheCopCongrats;
extern "C" tScreenCarSelectDuel *screenCarSelectDuel;
extern "C" tScreenCarSelectTwoPlayer *screenCarSelectPlayerTwo;
extern "C" tScreenCarSelectTwoPlayer *screenCarSelectTwoPlayer;
extern tScreenControllerConfig *screenControllerConfig;
extern tScreenDisplay *screenDisplay;
extern "C" tScreenMemcard *screenMemcard;
extern tScreenPinkSlipCongrats *screenPinkSlipCongrats;
extern tScreenPinkSlipStandings *screenPinkSlipStandings;
extern tScreenPinkSlips *screenPinkSlips;
extern "C" tScreenPinkSlipsCarSelect *screenPinkSlipsCarSelectPlayerTwo;
extern "C" tScreenPinkSlipsCarSelect *screenPinkSlipsCarSelectTwoPlayer;
extern tScreenTournSelect *screenTournSelect;
extern tScreenTournamentCongrats *screenTournamentCongrats;
extern tScreenTournamentStandings *screenTournamentStandings;
extern tScreenTournamentStandings3item *screenTournamentStandings3item;
extern tScreenTournamentTrophy *screenTournamentTrophy;
extern tScreenTrackInfo *screenTrackInfo;
extern "C" tScreenTrackRecords *screenTrackRecords;
extern tScreenTrackSelect *screenTrackSelect;
extern tScreenTrophyInfo *screenTrophyInfo;
extern tScreenTrophyRoom *screenTrophyRoom;
extern __vtbl_ptr_type tBlankMenuItemGoToMenuNFS4Button_vtable[];  /* real def in game/common/vtables_tmenu.cpp */
extern __vtbl_ptr_type tBlankMenuItemNFS4LeftRightChoice_vtable[]; /* real def in game/common/vtables_tmenu.cpp */
extern __vtbl_ptr_type tDialogYesNoTri_vtable[12];
extern "C" int tInsideBoxControllerLeftRightSlider_vtable;
extern "C" int tMemoryCardMenuItem_vtable;
extern "C" int tMenuItemControllerLeftRightChoice_vtable;
extern "C" int tMenuItemDisplayLeftRightChoice_vtable;
extern "C" int tMenuItemOnOffLeftRightChoice_vtable;
extern "C" int tMenuItemOptionsLeftRightChoice_vtable;
extern "C" int tMenuItemOptionsTwoItemChoice_vtable;
extern "C" int tMenuItemSlidingActivated_vtable;
#endif
