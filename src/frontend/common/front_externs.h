/* frontend/common/front_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FRONT_EXTERNS_H_
#define _FE_FRONT_EXTERNS_H_
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
extern tAllScreens *gAllScreens;

/* ===== auto-generated stubs ===== */
void AddCarToIngameList(tCarManager *, tCarModels *, char *);
short AdvanceToNextTrack(tTournamentManager *);
extern "C"
{
    int AudioMus_GetSongList(...);
}
extern "C"
{
    int AudioMus_SysCleanUp(...);
}
extern "C"
{
    int AudioMus_SysStartUp(...);
}
extern "C"
{
    int AudioMus_Volume(...);
}
extern "C"
{
    int Audio_FECleanUp(...);
}
extern "C"
{
    int CarIO_CleanUpLicense(...);
}
extern "C"
{
    int CarIO_CreateLicense(...);
}
long CheapestCarStockPrice(tCarManager *);
extern "C"
{
    int Controller_SetRamp(...);
}
extern "C"
{
    int DeInit_Memcard(...);
}
extern "C"
{
    int FECheat_IsCheatEnabled(...);
}
extern "C"
{
    int FeAudio_DeInitCommentary(...);
}
extern "C"
{
    int FeAudio_InitCommentary(...);
}
extern "C"
{
    int FeTools_deinit(...);
}
int FindSimilarCar(tCarManager *, tCarModels *, char *, short, tCarModels *);
tCarInfo *GetCarFromID(tCarManager *, short);
short GetClassList(tCarManager *, unsigned int, int, tCarModels *);
void GetGarageCar(tCarManager *, unsigned short, tCarInfo *, int);
short GetLastTrackRaced(tTournamentManager *);
short GetMissionStages(tMissionManager *, short, short, tStageInfo **);
void GetMissionToRace(tMissionManager *, tMissionInfo **);
short GetNumOwnedCars(tCarManager *, short);
extern "C"
{
    int GetPinkSlipsCar(...);
}
void GetStockCar(tCarManager *, unsigned short, tCarInfo *);
void GetTrack(tTrackManager *, unsigned short, tTrackInformation *);
extern "C"
{
    int GetTrackByID(...);
}
extern "C"
{
    int GetTrackToRace(...);
}
extern "C"
{
    int Init_Memcard(...);
}
extern "C"
{
    int Init_PSX_FrontEnd(...);
}
void InitializeIngameCarList(tCarManager *);
extern "C"
{
    int InitializeSpinningCars(...);
}
void *IsCarAnAddedModel(tCarManager *, tCarModels *, char *);
void LoadDescription(tMissionManager *, bool);
short LoadGame(short player, bool PinkSlips, bool WithDialogs);
extern "C"
{
    int MenuExtended_TransitionFromPostGameToMainMenu(...);
}
extern "C"
{
    int PSXExitFrontend(...);
}
extern "C"
{
    int Platform_ResetDCTBuffer(...);
}
extern "C"
{
    char *PlayerName(int);
}
tAppCommand RunFrontEnd(tFEApplication *);
tAppCommand RunPostGame(tFEApplication *);
int Setup(...);
extern "C"
{
    int StatTool_UpperCaseItKeepingInMindThoseBloodySpecialCharacters(...);
}
extern "C"
{
    int Stattool_GetAllDefaultRecords(...);
}
extern "C"
{
    int Stattool_ReturnRecordLapTime(...);
}
extern "C"
{
    int TextSys_UnloadWords(...);
}
extern "C"
{
    int TextSys_Word(...);
}
void UpdateAwardInformation(tTournamentManager *);
void UpdateCarLineup(tTournamentManager *);
void *__builtin_new(unsigned int size);
extern "C"
{
    int s_lower(...);
}
extern "C"
{
    tAllScreens *tAllScreens_ctor(...);
}
extern "C"
{
    tAllScreens *tAllScreens_dtor(...);
}
extern "C"
{
    tFEApplication *tFEApplication_ctor(...);
}
extern "C"
{
    tFEApplication *tFEApplication_dtor(...);
}
extern "C"
{
    tGlobalMenuDefs *tGlobalMenuDefs_ctor(...);
}
extern "C"
{
    tGlobalMenuDefs *tGlobalMenuDefs_dtor(...);
}
tScreenAudio *tScreenAudio_ctor(...);
extern "C"
{
    tScreenCarSelect *tScreenCarSelect_ctor(...);
}
extern "C"
{
    tScreenCarSelect *tScreenCarSelect_dtor(...);
}
tScreenControllerConfig *tScreenControllerConfig_ctor(...);
tScreenMemcard *tScreenMemcard_ctor(...);
tScreenTournSelect *tScreenTournSelect_ctor(...);
tScreenTournSelect *tScreenTournSelect_dtor(...);
tScreenTournamentStandings *tScreenTournamentStandings_ctor(...);
tScreenTrophyRoom *tScreenTrophyRoom_ctor(...);
tScreenTrophyRoom *tScreenTrophyRoom_dtor(...);
extern "C"
{
    tScreen *tScreen_ctor(...);
}
tScreen *tScreen_dtor(...);
extern "C" Car_tStats *Cars_gNewCarStatsList;
/* FETracks.obj/SYM: ARY SHORT at 0x80051610.  OutputDisplaySettings MIPS
   0x80027E00..0x80027E10 indexes by two and loads it with `lh`. */
extern short CountryMeasurement[8];
extern tCreditManager CreditManager;
extern "C" extern "C" GameSetup_tData GameSetup_gData;
extern "C" int MEMCARDFRONTENDISINITTED;
extern "C" tRecordBuffer Stats_gTrackRecords[187];
extern int _7tScreen_fSuppressLoadingText;
extern int _i;
extern int _usePlayerUpgrades;
extern int colourChosen[8];
extern "C" int gCalculateVictory;
extern int gFEBigHandle;
extern "C" int gLargestUnused;
extern "C" extern int gMasterAmbientLevel;
extern "C" int gMasterEngineLevel;
extern "C" int gMasterFENarrationLevel;
extern "C" extern int gMasterMusicLevel;
extern "C" int gMasterSFXLevel;
extern int gPSXMemCardFull;
extern "C" tPadModuleState gPadinfo;
extern int gUseFrontend;
extern "C" int mappings[3][13][3];
extern int memCardReadOK;
extern "C" tMissionManager missionManager;
extern tCarModels regularCopModels[7][5];
extern tScreenAudio *screenAudio;
extern tScreenBeTheCopCongrats *screenBeTheCopCongrats;
extern tScreenCarSelect *screenCarSelect;
extern "C" tScreenCarSelectDuel *screenCarSelectDuel;
extern "C" tScreenCarSelectTwoPlayer *screenCarSelectPlayerTwo;
extern "C" tScreenCarSelectTwoPlayer *screenCarSelectTwoPlayer;
extern tScreenControllerConfig *screenControllerConfig;
extern tScreenDisplay *screenDisplay;
extern "C" tScreenMain *screenMain;
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
extern tScreenUserName *screenUserName;
extern tCarModels superCopModels[7][5];
extern "C" int tDialogBackUpOnly_vtable[];
extern __vtbl_ptr_type tDialogBase_vtable[];
extern __vtbl_ptr_type tDialogMessageString_vtable[];
extern "C" int tScreenBeTheCopCongrats_vtable[];
extern "C" int tScreenCarSelectDuel_vtable[];
extern "C" int tScreenCarSelectTwoPlayer_vtable[];
extern "C" int tScreenDisplay_vtable[];
extern "C" int tScreenMain_vtable[];
extern "C" int tScreenPinkSlipCongrats_vtable[];
extern "C" int tScreenPinkSlipStandings_vtable[];
extern "C" int tScreenPinkSlipsCarSelect_vtable[];
extern "C" int tScreenPinkSlips_vtable[];
extern "C" int tScreenTournamentCongrats_vtable[];
extern "C" int tScreenTournamentStandings3item_vtable[];
extern "C" int tScreenTournamentTrophy_vtable[];
extern "C" int tScreenTrackInfo_vtable[];
extern "C" int tScreenTrackRecords_vtable[];
extern "C" int tScreenTrackSelect_vtable[];
extern "C" int tScreenTrophyInfo_vtable[];
extern "C" int tScreenUserName_vtable[];
#endif
