/* frontend/common/front_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FRONT_EXTERNS_H_
#define _FE_FRONT_EXTERNS_H_
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
extern tAllScreens *gAllScreens;

/* ===== auto-generated stubs ===== */
void AddCarToIngameList(tCarManager *, tCarModels *, char *);
short AdvanceToNextTrack(tTournamentManager *);
extern "C"
{
    AudioMus_tSongList *AudioMus_GetSongList(char *pattern, int memtype);
}
extern "C"
{
    void AudioMus_SysCleanUp(void);
}
extern "C"
{
    void AudioMus_SysStartUp(int buffersize, int spusize, const char *songs);
}
extern "C"
{
    void AudioMus_Volume(int volume);
}
extern "C"
{
    void Audio_FECleanUp(void);
}
extern "C"
{
    void CarIO_CleanUpLicense(int player);
}
extern "C"
{
    void CarIO_CreateLicense(char *text, int carType, int player);
}
long CheapestCarStockPrice(tCarManager *);
extern "C"
{
    void Controller_SetRamp(void);
}
extern "C"
{
    void DeInit_Memcard(void);
}
extern "C"
{
    void *FECheat_IsCheatEnabled(tCheatCode cheat);
}
extern "C"
{
    void FeAudio_DeInitCommentary(void);
}
extern "C"
{
    void FeAudio_InitCommentary(int language, int arg1);
}
extern "C"
{
    void FeTools_deinit(void);
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
    void GetPinkSlipsCar(tCarManager *a0, short a1, tCarInfo *a2, short a3);
}
void GetStockCar(tCarManager *, unsigned short, tCarInfo *);
void GetTrack(tTrackManager *, unsigned short, tTrackInformation *);
extern "C"
{
    tTrackInformation *GetTrackByID(tTrackManager *a0, short a1);
}
extern "C"
{
    void GetTrackToRace(tTournamentManager *a0, tTrackInfo *a1);
}
extern "C"
{
    void Init_Memcard(bool redraw, bool pinkslips);
}
extern "C"
{
    void Init_PSX_FrontEnd(void);
}
void InitializeIngameCarList(tCarManager *);
extern "C"
{
    void InitializeSpinningCars(void);
}
void *IsCarAnAddedModel(tCarManager *, tCarModels *, char *);
void LoadDescription(tMissionManager *, bool);
short LoadGame(short player, bool PinkSlips, bool WithDialogs);
extern "C"
{
    void MenuExtended_TransitionFromPostGameToMainMenu(tMenuCommand *command);
}
extern "C"
{
    void PSXExitFrontend(void);
}
extern "C"
{
    void Platform_ResetDCTBuffer(void);
}
extern "C"
{
    char *PlayerName(int);
}
tAppCommand RunFrontEnd(tFEApplication *);
tAppCommand RunPostGame(tFEApplication *);
extern "C"
{
    void StatTool_UpperCaseItKeepingInMindThoseBloodySpecialCharacters(char *string);
}
extern "C"
{
    void Stattool_GetAllDefaultRecords(tRecordBuffer *TrackRecords, bool cheatones);
}
extern "C"
{
    int Stattool_ReturnRecordLapTime(short nTrack);
}
extern "C"
{
    void TextSys_UnloadWords(void);
}
extern "C"
{
    char *TextSys_Word(int wordnum);
}
void UpdateAwardInformation(tTournamentManager *);
void UpdateCarLineup(tTournamentManager *);
void *__builtin_new(unsigned int size);
extern "C"
{
    void s_lower(char *string);
}
extern "C"
{
    tAllScreens *tAllScreens_ctor(tAllScreens *p);
}
extern "C"
{
    void tAllScreens_dtor(tAllScreens *p, int);
}
extern "C"
{
    tFEApplication *tFEApplication_ctor(tFEApplication *p);
}
extern "C"
{
    void tFEApplication_dtor(tFEApplication *p, int);
}
extern "C"
{
    tGlobalMenuDefs *tGlobalMenuDefs_ctor(tGlobalMenuDefs *p);
}
extern "C"
{
    void tGlobalMenuDefs_dtor(tGlobalMenuDefs *p, int mode);
}
extern "C"
{
    void tScreenCarSelect_ctor(tScreenCarSelect *a0);
}
extern "C"
{
    void tScreenCarSelect_dtor(tScreenCarSelect *a0, int mode);
}
extern "C"
{
    void tScreen_ctor(tScreen *a0);
}
extern "C" Car_tStats Cars_gNewCarStatsList[9];
/* FETracks.obj/SYM: ARY SHORT at 0x80051610.  OutputDisplaySettings MIPS
   0x80027E00..0x80027E10 indexes by two and loads it with `lh`. */
extern short CountryMeasurement[8];
extern tCreditManager CreditManager;
extern "C" GameSetup_tData GameSetup_gData;
extern "C" int MEMCARDFRONTENDISINITTED;
extern "C" tRecordBuffer Stats_gTrackRecords[187];
extern int _7tScreen_fSuppressLoadingText;
extern int _i;
extern int _usePlayerUpgrades;
extern int colourChosen[8];
extern "C" int gCalculateVictory;
extern int gFEBigHandle;
extern "C" int gLargestUnused;
extern "C" int gMasterAmbientLevel;
extern "C" int gMasterEngineLevel;
extern "C" int gMasterFENarrationLevel;
extern "C" int gMasterMusicLevel;
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
