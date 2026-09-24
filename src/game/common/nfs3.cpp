/* game/common/nfs3.cpp -- RECONSTRUCTED (game boot / module start-up + game entry; C TU, 11 fns) */
#include "../../nfs4_types.h"
#include "nfs3_externs.h"

#ifdef AP_WIN
extern "C" int NFSHS_HostTestRaceRequested(void);
extern "C" int NFSHS_HostTestRaceParam(const char *, int);
extern "C" void srand(unsigned int);
extern "C" int ticks;
#endif

/* ---- owning-TU defs for link-harness (extern-declared, never defined; BSS) ---- */
int *gFileMem; int *gFileHandleTable;

/* ---- nfs3.obj-OWNED globals -- DEFINED here (self-contained; SYM-typed via gen_owned_defs:
   .data = real NFS4.EXE bytes, .bss = zero) ---- */
char         befuddleExtensions[14][4] = { 113, 112, 108, 0, 97, 105, 105, 0, 115, 112, 100, 0, 113, 97, 108, 0, 115, 97, 108, 0, 100, 116, 97, 0, 113, 112, 115, 0, 105, 110, 102, 0, 113, 100, 97, 0, 99, 97, 114, 0, 113, 97, 115, 0, 113, 100, 116, 0, 115, 112, 108, 0, 115, 112, 101, 0 };   /* @0x8011423c */
tCarManager  carManager;   /* @0x80114274  (bss(zero)) */
extern "C" { tfrontEnd    frontEnd; } /* @0x80114600  (bss(zero)) */
tTrackManager trackManager;   /* @0x80114a50  (bss(zero)) */
tTournamentManager tournamentManager;   /* @0x80114ad8  (bss(zero)) */
tCreditManager CreditManager;   /* @0x80114d5c  (bss(zero)) */
extern "C" { tRecordBuffer Stats_gTrackRecords[187]; } /* @0x80114d94  (bss(zero)) */
char         gTournamentFinishOrder[12];   /* @0x80115c30  (bss(zero)) */
char         befuddleTemp[10];   /* @0x80115c3c  (bss(zero)) */
char         gMusicInSimIsOn = 1;   /* @0x8013d270 */
int          gUseFrontend = 1;   /* @0x8013d274 */
#ifdef AP_WIN
extern "C" void NFSHS_HostLog(const char *fmt, ...); /* explicit TEST_DIRECT_RACE boundary */
extern "C" { extern void Front_InitialMemCardCheck(void); }
#endif
extern "C" { u_long       gFECheats; } /* @0x8013d278  (bss(zero)) */
extern "C" { u_long       gFEBonus; } /* @0x8013d27c  (bss(zero)) */
int          gFEBigHandle;   /* @0x8013d280  (bss(zero)) */
extern "C" { int          MEMCARDFRONTENDISINITTED; } /* @0x8013d284  (bss(zero)) */
char         gCheckTotalTime = 1;   /* @0x8013d288 */
char         gCheckLapTime = 1;   /* @0x8013d289 */
char         gUpdateTournamentInfoFlag = 1;   /* @0x8013d28a */
char         gUpdateKnockoutInfoFlag = 1;   /* @0x8013d28b */
char         gKnockOutSpeechFlag = 1;   /* @0x8013d28c */
extern "C" char         gCalculateVictory = 1;   /* @0x8013d28d */
char         gPlayerEnteredNameAlready[2];   /* @0x8013d290  (bss(zero)) */
tNfsSystemInfo nfs_sysInfo;   /* @0x8013d2b4  (bss(zero)) */
extern "C" { tMissionManager missionManager; } /* @0x8013d2b8  (bss(zero)) */
char         finishOrder[8];   /* @0x8013d2c0  (bss(zero)) */


/* ---- Nfs2_SystemNLibStartUp  [NFS3.CPP:118-135] SLD-VERIFIED ---- */


void Nfs2_SystemNLibStartUp(void)

{
  
  Platform_SysStartUp();
  Loading_GetInitialMemory();
  if (_6Speech_fgUndefined == (Speaker *)0x0) {
    _6Speech_fgUndefined = (Speaker *)__builtin_new(sizeof(Speaker));
    _6Speech_fgUndefined->_vf = (__vtbl_ptr_type (*)[31])Speaker_vtable;
    _6Speech_fgUndefined->fSub = (Speaker *)0x0;
  }
  Render_InitLibRender();
  return;
}



/* ---- Nfs2_BefuddleCode  [NFS3.CPP:178-181] SLD-VERIFIED ---- */


void Nfs2_BefuddleCode(void)

{
  char (*src) [4];
  int loop;
  
  loop = 0;
  src = befuddleExtensions;
  do {
    strcpy(befuddleTemp,*src);
    loop = loop + 1;
    src = src + 1;
  } while (loop < 0xe);
  return;
}



/* ---- Nfs2_ResetGame  [NFS3.CPP:186-348] SLD-VERIFIED ---- */


void Nfs2_ResetGame(void)

{
  Replay_ResetReplay();
  BWorld_Restart();
  Sim_Restart();
  Camera_Init();
  Weather_Restart();
  AudioCmn_Reset();
  Speech_Reset();
  AudioClc_StartUp();
  DashHUD_ResetHUD();
  return;
}



/* ---- NFS4_LoadPerps  [NFS3.CPP:247-348] SLD-VERIFIED ---- */


void NFS4_LoadPerps(void)

{
  u_char bVar1;
  int *addr;
  u_int *addr_00;
  u_long numTiers;
  tCarInfo *carCandidate;
  u_long j;
  u_int uVar4;
  char *pcVar6;
  u_char *pbVar7;
  char *data;
  u_char *pbVar8;
  u_long numCars;
  int numMissions;
  u_int uVar9;
  tCarInfo *carData;
  tCarInfo *cars;
  GameSetup_tPerpData *perpInfo;
  GameSetup_tPerpData *pGVar11;
  short i;
  int iVar12;
  char *buffer;
  char filename [64];
  
  if (0 < GameSetup_gData.numPerps) {
    if (GameSetup_gData.commMode == 1) {
      pcVar6 = "zHPurs2.mis";
    }
    else {
      pcVar6 = "zHPurs.mis";
    }
    sprintf(filename,"%s%s",Paths_Paths[0x25],pcVar6);
    addr = (int *)loadfileadr(filename,0x10);
    sprintf(filename,"%s%s",Paths_Paths[0x25],"fecars.car");
    addr_00 = (u_int *)loadfileadr(filename,0x10);
    pGVar11 = GameSetup_gData.perpInfo;
    iVar12 = 0;
    uVar9 = *addr_00;
    pbVar8 = (u_char *)(addr + *addr + (numMissions = addr[1]) * 5 + GameSetup_gData.stageOffset * 0xb + 3);
    if (0 < GameSetup_gData.numPerps) {
      cars = (tCarInfo *)(addr_00 + 1);
      pbVar7 = pbVar8 + 1;
      do {
        uVar4 = 0;
        if (uVar9 == 0) {
NFS4LoadPerps_defaultZero:
          uVar4 = 0;
        }
        else {
          carCandidate = cars;
          do {
            if ((int)carCandidate->fCarID == (u_int)*pbVar8) break;
            uVar4 = uVar4 + 1;
            carCandidate = carCandidate + 1;
          } while (uVar4 < uVar9);
          if (uVar9 <= uVar4) goto NFS4LoadPerps_defaultZero;
        }
        pGVar11->CarType = cars[uVar4].fSimNumber;
        pGVar11->Colour = *pbVar7;
        pGVar11->Personality = pbVar7[1];
        pGVar11->TimeLimit = *(short *)(pbVar7 + 3);
        if (GameSetup_gData.commMode == 1) {
          pGVar11->WingmanTime = -1;
          pGVar11->SpikeBeltTime = -1;
          pGVar11->BlockadeCopTime = -1;
        }
        else {
          pGVar11->WingmanTime = *(short *)(pbVar7 + 5);
          pGVar11->SpikeBeltTime = *(short *)(pbVar7 + 7);
          pGVar11->BlockadeCopTime = *(short *)(pbVar7 + 9);
        }
        pGVar11->Distance = *(u_short *)(pbVar7 + 0xd);
        iVar12 = iVar12 + 1;
        pGVar11->SpeedFactor = *(int *)(pbVar7 + 0xf);
        pGVar11->WeightFactor = *(int *)(pbVar7 + 0x13);
        pGVar11->GlueFactor = *(int *)(pbVar7 + 0x17);
        pGVar11->SpeechColour = cars[uVar4].fSpeechColors[*pbVar7];
        bVar1 = *pbVar7;
        u_long carColor = cars[uVar4].fColorList[bVar1];
        pGVar11->HudColour = (carColor >> 16 & 0xff) | (carColor & 0xff00) |
                              (carColor & 0xff) << 0x10;
        pbVar8 = pbVar8 + 0x2c;
        pbVar7 = pbVar7 + 0x2c;
        pGVar11 = pGVar11 + 1;
      } while (iVar12 * 0x10000 >> 0x10 < GameSetup_gData.numPerps);
    }
    purgememadr(addr);
    purgememadr(addr_00);
  }
  return;
}



/* ---- Nfs2_GameModuleStartUp  [NFS3.CPP:357-460] SLD-VERIFIED ---- */


void Nfs2_GameModuleStartUp(int *FrontEndDataStream)

{
  void *pThis;
  int iVar1;
  int iVar2;
  
  Audio_InitDriver(0,0);
  restoretextdraw();
  Platform_InitMemory();
  Platform_ResetDCTBuffer();
  GameSetup_StartUp(FrontEndDataStream);
  Replay_InitReplay();
  Nfs2_BefuddleCode();
  Loading_DrawLoadingScreen();
  Loading_UpdateLoadingScreen(1);
  NFS4_LoadPerps();
  Loading_UpdateLoadingScreen(2);
  Physics_CheckGamedata();
  Clock_SystemStartUp();
  AudioCmn_LoadGameSamples();
  CopSpeak_StartUp();
  if ((GameSetup_gData.raceType == 1) && (_6Speech_fgSpeech == (Speech *)0x0)) {
    pThis = __builtin_new(0x3a4);
    _6Speech_fgSpeech = Speech_ct((Speech *)pThis);
  }
  Render_InitPauseMenu();
  Render_InitTrackRender();
  Loading_UpdateLoadingScreen(4);
  BWorld_Init();
  Loading_UpdateLoadingScreen(6);
  Hrz_InitHorizon();
  Night_InitNightDriving();
  Weather_Init();
  Loading_UpdateLoadingScreen(7);
  Sim_StartUp();
  Render_InitTrackRenderPostSim();
  Hud_InitMap();
  SimQueue_StartUp();
  iVar1 = largestunused();
  if (GameSetup_gData.commMode == 1) {
    iVar2 = 0x13000;
  }
  else {
    iVar2 = 0xb000;
  }
  if (iVar2 < iVar1) {
    AudioMus_SysStartUp(0x6000,0x14000,"ymus");
  }
  AudioMus_BuildPlayList(GameSetup_gData.userSetting.numplaylistsongs,GameSetup_gData.userSetting.playlist);
  largestunused();
  return;
}



/* ---- Nfs2_CleanUpGameModule  [NFS3.CPP:464-549] SLD-VERIFIED ---- */


void Nfs2_CleanUpGameModule(void)

{
  Car_tObj *pCVar1;
  Car_tStats *pCVar2;
  Car_tStats *pCVar3;
  Car_tObj **ppCVar4;
  int iVar5;
  int k;
  int iVar7;
  int iVar8;
  
  Render_KillTrackRender();
  Render_KillPauseMenu();
  k = 0;
  if (0 < GameSetup_gData.numCars) {
    iVar5 = 0;
    do {
      ppCVar4 = Cars_gList + (iVar5 >> 0x10);
      ((*ppCVar4)->stats).carType = (*ppCVar4)->carInfo->carType;
      ((*ppCVar4)->stats).carClass = (*ppCVar4)->carInfo->carClass;
      ((*ppCVar4)->stats).carNameIndex = (*ppCVar4)->carInfo->carNameIndex;
      ((*ppCVar4)->stats).carFlags = (*ppCVar4)->carFlags;
      pCVar1 = *ppCVar4;
      pCVar3 = Cars_gNewCarStatsList + (iVar5 >> 0x10);
      pCVar2 = &pCVar1->stats;
      do {
        iVar5 = pCVar2->sliceTotal;
        iVar7 = pCVar2->sliceTime;
        iVar8 = pCVar2->slice;
        pCVar3->extractSlice = pCVar2->extractSlice;
        pCVar3->sliceTotal = iVar5;
        pCVar3->sliceTime = iVar7;
        pCVar3->slice = iVar8;
        pCVar2 = (Car_tStats *)&pCVar2->lastSlice;
        pCVar3 = (Car_tStats *)&pCVar3->lastSlice;
      } while (pCVar2 != (Car_tStats *)&pCVar1->crash);
      k = k + 1;
      iVar5 = k * 0x10000;
    } while (k * 0x10000 >> 0x10 < GameSetup_gData.numCars);
  }
  Replay_StoringReplay();
  AudioCmn_DeInit();
  if (_6Speech_fgSpeech != (Speech *)0x0) {
    Speech_dt(_6Speech_fgSpeech,3);
    _6Speech_fgSpeech = (Speech *)0x0;
  }
  CopSpeak_CleanUp();
  Clock_SystemCleanUp();
  GameSetup_CleanUp();
  Sim_CleanUp();
  Hrz_KillHorizon();
  BWorld_DeInit();
  Camera_Kill();
  Weather_DeInit();
  Audio_DeInitDriver();
  return;
}



/* ---- LoadFrontendOverlay  [NFS3.CPP:560-580] SLD-VERIFIED ---- */


void LoadFrontendOverlay(void)

{
  int handle;
  int iVar1;
  
  handle = asyncloadfileat("front.bin",bigBuf);
  while (iVar1 = getasyncreadstatus(handle), iVar1 == 0) {
    systemtask(0);
  }
  return;
}



/* ---- LoadOverlay  [NFS3.CPP:589-596] SLD-VERIFIED ---- */


void LoadOverlay(void)

{
  int handle;
  int iVar1;
  char fname [60];
  
  LoadFrontendOverlay();
  sprintf(fname,"%sDCT.BIN",Paths_Paths[0x20]);
  handle = asyncloadfileat(fname,CF_DVLC);
  while (iVar1 = getasyncreadstatus(handle), iVar1 == 0) {
    systemtask(0);
  }
  return;
}



/* ---- NFS4_LoadingIcon  [NFS3.CPP:626-669] SLD-VERIFIED ---- */


void NFS4_LoadingIcon(void)

{
  void *ldfile;
  shapetbl *shp;
  u_int lang;
  char fname [80];
  PSX_RECT r;
  
  sprintf(fname,"%sldic.psh",Paths_Paths[0x25]);
  ldfile = loadfileadr(fname,0);
  lang = (u_int)(u_char)frontEnd.language;
  if (5 < lang) {
    lang = 0;
  }
  shp = (shapetbl *)shapepointer(ldfile,lang);
  r.w = 0x400;
  r.x = 0;
  r.y = 0;
  r.h = 0x200;
  ClearImage(&r,'\0','\0','\0');
  DrawSync(0);
  initlinkmode(0,100,0);   /* oracle 0x94650: a2=0 (dropped 3rd arg) */
  Draw_DirectSetEnvironment(0,0,0x200,0xf0,1,1,1,0,0,0);
  settrans(0);
  movfxya(shp,0x1e2 - shp->width,0xd2);
  DrawSync(0);
  purgememadr(ldfile);
  initlinkmode(0,1,1);   /* oracle 0x946c0: a2=1 (dropped 3rd arg) */
  return;
}



/* ---- NFS3_CheckForFileOperations  [NFS3.CPP:686-694] SLD-VERIFIED ---- */


void NFS3_CheckForFileOperations(void)

{
  int *p;
  int *piVar1;
  
  for (piVar1 = gFileMem; piVar1 < gFileHandleTable; piVar1 = piVar1 + 1) {
    if (*piVar1 != 0) {
      trap(0x666);
    }
  }
  return;
}



/* ---- main  [NFS3.CPP:703-935] SLD-VERIFIED ---- */

extern "C"
{
// XPORT REVISION: 2026-09-24T13:10:20Z
int xport_main(int argc, char **argv)

{
  u_int uVar1;
  int *setup;
  int iVar2;
  char *pattern;
  short oldReplayMode;
#ifdef AP_WIN
  int hostDirectRace;
#endif

  if (argc < 0 || argv == 0) {
    return 1;
  }
  
  __main();
  oldReplayMode = 0;
  Platform_DebuggerPollHost();
  Nfs2_SystemNLibStartUp();
  Audio_InitDriver(0,0);
  Audio_DeInitDriver();
  SetVideoMode(0);
  frontEnd.language = -1;
  LoadFrontendOverlay();
  ComingIntoTheFrontEndTheVeryFirstTime = 1;
  (&carManager)->Initialize();
  (&carManager)->LoadDescription();
  FECheat_ActivateBonus(cheat_Roadster);
  (&carManager)->SetClassViewable((tCarClassType)0, 1);
  (&carManager)->SetClassViewable((tCarClassType)1, 1);
  (&carManager)->SetClassViewable((tCarClassType)2, 1);
  (&carManager)->SetClassViewable((tCarClassType)3, 1);
  (&carManager)->SetClassViewable((tCarClassType)4, 1);
  (&carManager)->SetClassViewable((tCarClassType)5, 1);
  (&tournamentManager)->Initialize();
  (&missionManager)->Initialize();
  (&trackManager)->Initialize();
  (&tournamentManager)->LoadDescription();
  (&trackManager)->LoadDescription();
#ifdef AP_WIN
  hostDirectRace = NFSHS_HostTestRaceRequested();
  if (hostDirectRace) {
    /* Retail main reaches this initialization through Front_InitGraphics ->
       Init_PSX_FrontEnd -> DoLanguageScreen.  Only the explicit direct-race
       test skips that chain, so initialize the same state before applying the
       test parameters; the normal frontend follows the retail path once. */
    Front_InitialMemCardCheck();
    int track = NFSHS_HostTestRaceParam("track",0);
    int car = NFSHS_HostTestRaceParam("car",0);
    int color = NFSHS_HostTestRaceParam("color",0);
    int opponents = NFSHS_HostTestRaceParam("opponents",0);
    if (track < 0) track = 0; else if (track > 31) track = 31;
    if (car < 0) car = 0; else if (car > 47) car = 47;
    if (color < 0) color = 0; else if (color > 15) color = 15;
    if (opponents < 0) opponents = 0; else if (opponents > 2) opponents = 2;
    frontEnd.gameMode = (char)(NFSHS_HostTestRaceParam("players",1) == 2);
    frontEnd.raceType = (char)NFSHS_HostTestRaceParam("race",0);
    frontEnd.skillLevel = (char)NFSHS_HostTestRaceParam("skill",0);
    frontEnd.track[0] = (char)track;
    frontEnd.playerCar[0] = (char)car;
    frontEnd.carColors[0][car] = (char)color;
    frontEnd.oppNumber = (char)opponents;
    frontEnd.traffic[0] = (char)(NFSHS_HostTestRaceParam("traffic",0) != 0);
    frontEnd.laps = (char)NFSHS_HostTestRaceParam("laps",0);
    frontEnd.catchup = (char)(NFSHS_HostTestRaceParam("catchup",0) != 0);
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostLog("TEST_DIRECT_RACE track=%d car=%d color=%d opponents=%d race=%d skill=%d traffic=%d laps=%d",
                  track,car,color,opponents,(int)frontEnd.raceType,(int)frontEnd.skillLevel,
                  (int)frontEnd.traffic[0],(int)frontEnd.laps));
  }
#endif
  if (gUseFrontend != 0
#ifdef AP_WIN
      && !hostDirectRace
#endif
     )
    Front_InitGraphics();
  if (gUseFrontend != 0
#ifdef AP_WIN
      && !hostDirectRace
#endif
     )
    Front_Menu((tFront_ProcessingType)0);
  do {
    NFS3_CheckForFileOperations();
    setup = (int *)MinFront_ParseOptions();
#ifdef AP_WIN
    if (hostDirectRace) {
      /* Retail Front_BuildStream MIPS 0x8002A7A4..0x8002A7B8 loads ticks,
         sign-extends its low 16 bits, stores frontEnd.randomSeed, and passes
         the same value to seedrandom.  A direct-race test has no menu dwell,
         so replay supplies the seed observed in the reference save state by
         recreating that exact input to the unmodified retail path. */
      int referenceTicks=NFSHS_HostTestRaceParam("seed",-1);
      if (referenceTicks>=0) ticks=referenceTicks;
    }
#endif
    if (gUseFrontend != 0) {
      setup = (int *)Front_BuildStream(setup);
    }
    (&trackManager)->ReleaseDescription();
    (&missionManager)->ReleaseDescription();
    (&tournamentManager)->ReleaseDescription();
    (&carManager)->ReleaseDescription();
    initlinkmode(0,1,1);
    NFS3_CheckForFileOperations();
#ifdef AP_WIN
    if (hostDirectRace) {
      /* Slot-2 PSX RAM[0x9010] is 0x41B234D8 at the simulation boundary.
         BWorld_Init MIPS 0x8007E608/620/668 makes the only three BIOS rand
         calls after this point.  Reversing that documented LCG gives the
         exact pre-BWorld state 0xF75EBDB5.  This opt-in replay input replaces
         only the menu's already-consumed BIOS RNG history. */
      int referenceCRTSeed=NFSHS_HostTestRaceParam("crtseed",0);
      if (referenceCRTSeed!=0) srand((unsigned int)referenceCRTSeed);
    }
#endif
    Nfs2_GameModuleStartUp(setup);
    NFS3_CheckForFileOperations();
    while (simVar.restartGame != 0) {
      simVar.restartGame = 0;
      Nfs2_ResetGame();
      Sim_MainGameLoop();
      if ((GameSetup_gData.replayMode < 2) || (GameSetup_gData.instantReplay != 0)) {
        if ((simVar.restartGame == 0) || (GameSetup_gData.instantReplay != 0)) {
          GameSetup_gData.replayMode = 2;
          if (GameSetup_gData.instantReplay == 0) {
            Replay_ReplayInterface.statsScreen = 1;
            iVar2 = Stats_GetNumOpponents();
            if ((1 < iVar2) &&
               (((GameSetup_gData.raceType != 1 && (GameSetup_gData.raceType != 5)) ||
                (((Cars_gHumanRaceCarList[0]->carFlags & 0x200U) == 0 &&
                 ((Cars_gNumHumanRaceCars != 2 ||
                  ((Cars_gHumanRaceCarList[1]->carFlags & 0x200U) == 0)))))))) {
              if ((Cars_gHumanRaceCarList[0]->stats).finalPosition == 1) {
                pattern = "win*";
              }
              else {
                pattern = "lose*";
              }
              AudioMus_PlaySong(pattern);
            }
          }
          else {
            Replay_ReplayInterface.statsScreen = 0;
          }
          Replay_ReplayMode = 2;
          simVar.restartGame = 1;
          GameSetup_gData.instantReplay = 0;
        }
      }
      else {
        Replay_ReplayInterface.statsScreen = 0;
      }
    }
    Nfs2_CleanUpGameModule();
    NFS4_LoadingIcon();
    LoadOverlay();
    NFS3_CheckForFileOperations();
    Front_InitGraphicsAndDisplayLoading();
    GameSetup_gData.replayMode = (int)oldReplayMode;
    Front_GetInGameVars();
    (&carManager)->LoadDescription();
    (&tournamentManager)->LoadDescription();
    (&trackManager)->LoadDescription();
    uVar1 = 1;
    if (quitType == 1) {
      uVar1 = 2;
    }
    Front_Menu((tFront_ProcessingType)uVar1);
    oldReplayMode = (short)GameSetup_gData.replayMode;
    NFS3_CheckForFileOperations();
  } while( true );
}
}



/* end of nfs3.cpp */

/* owning-TU def (extern-declared, never defined; link-harness) */
Speech *_6Speech_fgSpeech;
Speaker *_6Speech_fgUndefined;
