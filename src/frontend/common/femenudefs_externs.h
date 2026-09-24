/* frontend/common/femenudefs_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FEMENUDEFS_EXTERNS_H_
#define _FE_FEMENUDEFS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C" int ticks;
extern "C" extern tfrontEnd frontEnd;
extern tFEApplication *FEApp;
extern tGlobalMenuDefs *menuDefs;
extern "C" extern char *Paths_Paths[];
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
int AddToPinkSlipsList(...);
int AddUpgradesToPinkSlipsList(...);
void AudioCmn_PlayFESFX(int);
long CalcUsedPrice(tCarManager *, short);
long CheapestCarStockPrice(tCarManager *);
extern "C"
{
    void DeInit_Memcard(void);
}
extern "C"
{
    int Decrement(...);
}
extern "C"
{
    int Display(...);
}
extern "C"
{
    int FECheat_IsTheUserACryBabyCheater(...);
}
extern "C"
{
    int GetAwardInformation(...);
}
tCarInfo *GetCarFromID(tCarManager *, short);
void GetGarageCar(tCarManager *, unsigned short, tCarInfo *, int);
short GetNumOwnedCars(tCarManager *, short);
short GetNumTourneyCars(tCarManager *, short);
extern "C"
{
    int GetPinkSlipsCar(...);
}
void GetStockCar(tCarManager *, unsigned short, tCarInfo *);
void GetTrack(tTrackManager *, unsigned short, tTrackInformation *);
extern "C"
{
    int Hide(...);
}
int Increment(...);
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
    int Redraw(...);
}
extern "C"
{
    int Run(...);
}
extern "C"
{
    int SaveGame(...);
}
PinkSlipsErrorCode SavePinkSlipsCarsWithErrorDialogs(short player, short WillLoseCar, short withoutCarInGarageNumber);
int SellCar(...);
void SetCarAvailable(tCarManager *, int, bool);
void SetDimensions(tMenuItemLeftRightSlider *, short, short, short, short);
void SetState(tScreenCarSelect *, int);
int StartNewTournament(...);
extern "C"
{
    int StatChk_ClearNewRecords(...);
}
extern "C"
{
    int StatChk_IsRecordLapTime(...);
}
extern "C"
{
    int StatChk_IsTopTime(...);
}
extern "C"
{
    int StatChk_SaveRecordLapTime(...);
}
extern "C"
{
    int StatChk_SaveTopTime(...);
}
void SwapBackground(tScreenMain *, int);
extern "C"
{
    char *TextSys_Word(int);
}
void __builtin_delete(void *deleteMe);
void tDialogYesNo_ctor(tDialogYesNo *);
tInsideBoxLeftRightSlider *tInsideBoxLeftRightSlider_ctor(...);
tInsideBoxLeftRightSlider *tInsideBoxLeftRightSlider_dtor(...);
tInsideBoxMenu *tInsideBoxMenu_ctor(...);
tInsideBoxMenu *tInsideBoxMenu_dtor(...);
tInsideBoxSongMenu *tInsideBoxSongMenu_ctor(...);
tInsideBoxSongMenu *tInsideBoxSongMenu_dtor(...);
tInsideBoxTwoWaySlider *tInsideBoxTwoWaySlider_ctor(...);
tInsideBoxTwoWaySlider *tInsideBoxTwoWaySlider_dtor(...);
tListIteratorCarColor *tListIteratorCarColor_ctor(...);
tListIteratorCarColor *tListIteratorCarColor_dtor(...);
tListIteratorCar *tListIteratorCar_ctor(...);
tListIteratorCar *tListIteratorCar_dtor(...);
tListIteratorIndexed *tListIteratorIndexed_ctor(...);
tListIteratorIndexed *tListIteratorIndexed_dtor(...);
tListIteratorRangeIndexed *tListIteratorRangeIndexed_ctor(...);
tListIteratorRangeIndexed *tListIteratorRangeIndexed_dtor(...);
tListIteratorRange *tListIteratorRange_ctor(...);
tListIteratorRange *tListIteratorRange_dtor(...);
tListIteratorTournament *tListIteratorTournament_ctor(...);
tListIteratorTournament *tListIteratorTournament_dtor(...);
tListIteratorTrack *tListIteratorTrack_ctor(...);
tListIteratorTrack *tListIteratorTrack_dtor(...);
tListIterator *tListIterator_ctor(...);
extern "C"
{
    tListIterator *tListIterator_dtor(...);
}
tMenuBlank *tMenuBlank_ctor(...);
tMenuBlank *tMenuBlank_dtor(...);
tMenuItemGoToMenuButton *tMenuItemGoToMenuButton_ctor(...);
tMenuItemGoToMenuButton *tMenuItemGoToMenuButton_dtor(...);
tMenuItemGoToMenuNFS4Button *tMenuItemGoToMenuNFS4Button_ctor(...);
tMenuItemGoToMenuNFS4Button *tMenuItemGoToMenuNFS4Button_dtor(...);
tMenuItemLeftRightAudioSlider *tMenuItemLeftRightAudioSlider_ctor(...);
tMenuItemLeftRightAudioSlider *tMenuItemLeftRightAudioSlider_dtor(...);
tMenuItemLeftRightChoice *tMenuItemLeftRightChoice_ctor(...);
tMenuItemLeftRightChoice *tMenuItemLeftRightChoice_dtor(...);
tMenuItemLeftRightFade *tMenuItemLeftRightFade_ctor(...);
tMenuItemNFS4LeftRightChoice *tMenuItemNFS4LeftRightChoice_ctor(...);
tMenuItemNFS4LeftRightChoice *tMenuItemNFS4LeftRightChoice_dtor(...);
tMenuItemSlidingMenu *tMenuItemSlidingMenu_ctor(...);
tMenuItemSlidingMenu *tMenuItemSlidingMenu_dtor(...);
tMenuItem *tMenuItem_dtor(...);
tMenuNFS4Bottom *tMenuNFS4Bottom_ctor(...);
tMenuNFS4Bottom *tMenuNFS4Bottom_dtor(...);
tMenuNFS4TwoPlayer *tMenuNFS4TwoPlayer_ctor(...);
tMenuNFS4TwoPlayer *tMenuNFS4TwoPlayer_dtor(...);
extern "C"
{
    tMenuNFS4 *tMenuNFS4_ctor(...);
}
tMenuNFS4 *tMenuNFS4_dtor(...);
tMenuOptions *tMenuOptions_ctor(...);
tMenuOptions *tMenuOptions_dtor(...);
tOptionsMenu *tOptionsMenu_ctor(...);
tOptionsMenu *tOptionsMenu_dtor(...);
void tScreen_dtor(tScreen *, int);
tUserNameMenuItem *tUserNameMenuItem_ctor(...);
extern "C" int CURRENTLYUSINGMEMCARD;
extern "C" int Cars_gNewCarStatsList;
extern int Cars_gNumRaceCars;
extern "C" extern "C" GameSetup_tData GameSetup_gData;
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
