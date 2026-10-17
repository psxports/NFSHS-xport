/* game/common/mpause.cpp -- RECONSTRUCTED (NFS4 PSX mini/in-race pause menu; C++ TU)
 *   10 fns: class tPauseMenuDefs (ctor/dtor as free _ct/_dt) + 8 free MPause_* (music/
 *   controller/logic/render/init/start/end/kill). GTE-free. Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "mpause_externs.h"

/* ---- mpause.obj OWNED globals (Ghidra left $gp-relative; SYM names via disasm-proto,
 *   $gp base 0x8013C54C). EXT = external linkage (other TUs extern these); STAT = file-static.
 *   wasActive..lastplaytick are MPause_MusicLogic-private statics (laid out in this block). */
tPauseMenuDefs *gPauseMenuDefs;              /* EXT 0x8013d268 [$gp+0xd1c] */
extern "C" { int   gMPauseUpdate; } /* EXT 0x8013d264 [$gp+0xd18] */
extern "C" { int   gMPauseUpdateNextTime; } /* EXT 0x8013d240 [$gp+0xcf4] */
short InGameSelectListAudioMode[4];          /* EXT 0x8013d244 */
short SelectListConfig[4];                   /* EXT 0x8013d24c */
static tPMenu *gPauseCurrentMenu;            /* STAT 0x8013ddc0 [$gp+0x1874] */
static short  kMovingHighlight;              /* STAT 0x8013ddb8 [$gp+0x186c] */
static short  kMovingHighlightDir;           /* STAT 0x8013ddba [$gp+0x186e] */
static int    gBackDepth;                    /* STAT 0x8013ddbc [$gp+0x1870] */
static tPMenu *gBackList[6];                 /* STAT 0x8013e0c0 */
static char   wasActive, testSFX, playingSFX;   /* STAT MusicLogic statics 0x14/0x15/0x16 */
static int    vol, SFXHandle, lastplaytick;     /* STAT MusicLogic statics 0x18/0x1c/0x20 */

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void MPause_MusicLogic(char active);
void MPause_ControllerLogic(void);
extern "C" { u_int MPause_Logic(void); }
void MPause_Render(void);
void MPause_InitMPause(void);
void MPause_StartPauseMenu(void);
void MPause_EndPauseMenu(void);
void MPause_KillMPause(void);


/* ---- tPauseMenuDefs  [MPAUSE.CPP:172-264] SLD-VERIFIED ---- */
tPauseMenuDefs *tPauseMenuDefs_ct(tPauseMenuDefs *pThis)

{
  new ((void*)(&pThis->itemGamePaused)) tPMenuItemNonInteractiveText(0);
  new ((void*)(&pThis->itemContinue)) tPMenuItemCommandButton(1, (tPMenuCommandType)1);
  new ((void*)(&pThis->itemRestart)) tPMenuItemCommandButton(2, (tPMenuCommandType)2);
  new ((void*)(&pThis->itemOptions)) tPMenuItemGoToMenuButton(3, &pThis->menuOptions, (void (*)(tPMenuCommand&))0);
  new ((void*)(&pThis->itemQuitRace)) tPMenuItemCommandButton(4, (tPMenuCommandType)4);
  new ((void*)(&pThis->itemForfeitRace)) tPMenuItemCommandButton(5, (tPMenuCommandType)5);
  new ((void*)(&pThis->menuPause)) tPMenu(&pThis->itemGamePaused._base_tPMenuItem, {&pThis->itemContinue._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemRestart._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemOptions._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemQuitRace._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemForfeitRace._base_tPMenuItemInteractive._base_tPMenuItem, nullptr});
  new ((void*)(&pThis->itemOptionsTitle)) tPMenuItemNonInteractiveText(6);
  new ((void*)(&pThis->itemAudioSettings)) tPMenuItemGoToMenuButton(7, &pThis->menuAudioSettings, (void (*)(tPMenuCommand&))0);
  new ((void*)(&pThis->itemControllerSettings)) tPMenuItemGoToMenuButton(8, &pThis->menuControllerConfig, (void (*)(tPMenuCommand&))0);
  new ((void*)(&pThis->menuOptions)) tPMenu(&pThis->itemOptionsTitle._base_tPMenuItem, {&pThis->itemAudioSettings._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemControllerSettings._base_tPMenuItemInteractive._base_tPMenuItem, nullptr});
  new ((void*)(&pThis->itemAudioSettingsTitle)) tPMenuItemNonInteractiveText(10);
  new ((void*)(&pThis->iteratorAudioMode)) tPListIterator(InGameSelectListAudioMode, (int *)((char *)&GameSetup_gData + 0xec));
  new ((void*)(&pThis->itemAudioSettingsAudioMode)) tPMenuItemLeftRightChoice(0xb, &pThis->iteratorAudioMode);
  new ((void*)(&pThis->itemAudioSettingsMusicVolume)) tPMenuItemLeftRightSlider(0xc, &gMasterMusicLevel, 0x7f);
  new ((void*)(&pThis->itemAudioSettingsFXVolume)) tPMenuItemLeftRightSlider(0xd, &gMasterSFXLevel, 0x7f);
  new ((void*)(&pThis->itemAudioSettingsSpeechVolume)) tPMenuItemLeftRightSlider(0xe, &gMasterFENarrationLevel, 0x7f);
  new ((void*)(&pThis->itemAudioSettingsEngineVolume)) tPMenuItemLeftRightSlider(0xf, &gMasterEngineLevel, 0x7f);
  new ((void*)(&pThis->itemAudioSettingsAmbientVolume)) tPMenuItemLeftRightSlider(0x10, &gMasterAmbientLevel, 0x7f);
  new ((void*)(&pThis->menuAudioSettings)) tPMenu(&pThis->itemAudioSettingsTitle._base_tPMenuItem, {&pThis->itemAudioSettingsAudioMode._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemAudioSettingsMusicVolume._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemAudioSettingsFXVolume._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemAudioSettingsSpeechVolume._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemAudioSettingsEngineVolume._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemAudioSettingsAmbientVolume._base_tPMenuItemInteractive._base_tPMenuItem, nullptr});
  new ((void*)(&pThis->iteratorConfig)) tPListIteratorIndexed(SelectListConfig, (int *)((char *)&GameSetup_gData + 0x60), &Device_gPausePortIndex);
  new ((void*)(&pThis->itemControllerSettingsTitle)) tPMenuItemNonInteractiveText(0x14);
  new ((void*)(&pThis->itemControllerConfig)) tPMenuItemLeftRightChoice(0x15, (tPListIterator *)&pThis->iteratorConfig);
  new ((void*)(&pThis->itemControllerShockMode)) tPMenuItemLeftRightSliderIndexed(0x1b, (int *)((char *)&GameSetup_gData + 0xa8), 0x7f, &Device_gPausePortIndex);
  new ((void*)(&pThis->itemControllerShockImpact)) tPMenuItemLeftRightSliderIndexed(0x1c, (int *)((char *)&GameSetup_gData + 0xb0), 0x7f, &Device_gPausePortIndex);
  new ((void*)(&pThis->menuControllerConfig)) tPMenu(&pThis->itemControllerSettingsTitle._base_tPMenuItem, {&pThis->itemControllerConfig._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemControllerShockMode._base_tPMenuItemLeftRightSlider._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemControllerShockImpact._base_tPMenuItemLeftRightSlider._base_tPMenuItemInteractive._base_tPMenuItem, nullptr});
  new ((void*)(&pThis->itemConfirmTitle)) tPMenuItemNonInteractiveText(4);
  new ((void*)(&pThis->itemConfirmAreYouSure)) tPMenuItemNonInteractiveText(0x24);
  new ((void*)(&pThis->itemConfirmNo)) tPMenuItemCommandButton(0x26, (tPMenuCommandType)7);
  new ((void*)(&pThis->itemConfirmYes)) tPMenuItemCommandButton(0x25, (tPMenuCommandType)7);
  new ((void*)(&pThis->menuConfirmYesNo)) tPMenu(&pThis->itemConfirmTitle._base_tPMenuItem, {&pThis->itemConfirmAreYouSure._base_tPMenuItem, &pThis->itemConfirmNo._base_tPMenuItemInteractive._base_tPMenuItem, &pThis->itemConfirmYes._base_tPMenuItemInteractive._base_tPMenuItem, nullptr});
  return pThis;
}

/* ---- ~tPauseMenuDefs  [MPAUSE.CPP:268-268] SLD-VERIFIED ---- */
void tPauseMenuDefs_dt(tPauseMenuDefs *pThis, u_int __in_chrg)

{
  ((tPMenu*)(&pThis->menuConfirmYesNo))->~tPMenu();
  ((tPMenuItemCommandButton*)(&pThis->itemConfirmYes))->~tPMenuItemCommandButton();
  ((tPMenuItemCommandButton*)(&pThis->itemConfirmNo))->~tPMenuItemCommandButton();
  ((tPMenuItemNonInteractiveText*)(&pThis->itemConfirmAreYouSure))->~tPMenuItemNonInteractiveText();
  ((tPMenuItemNonInteractiveText*)(&pThis->itemConfirmTitle))->~tPMenuItemNonInteractiveText();
  ((tPMenu*)(&pThis->menuControllerConfig))->~tPMenu();
  ((tPMenuItemLeftRightSliderIndexed*)(&pThis->itemControllerShockImpact))->~tPMenuItemLeftRightSliderIndexed();
  ((tPMenuItemLeftRightSliderIndexed*)(&pThis->itemControllerShockMode))->~tPMenuItemLeftRightSliderIndexed();
  ((tPMenuItemLeftRightChoice*)(&pThis->itemControllerConfig))->~tPMenuItemLeftRightChoice();
  ((tPMenuItemNonInteractiveText*)(&pThis->itemControllerSettingsTitle))->~tPMenuItemNonInteractiveText();
  ((tPListIteratorIndexed*)(&pThis->iteratorConfig))->~tPListIteratorIndexed();
  ((tPMenu*)(&pThis->menuAudioSettings))->~tPMenu();
  ((tPMenuItemLeftRightSlider*)(&pThis->itemAudioSettingsAmbientVolume))->~tPMenuItemLeftRightSlider();
  ((tPMenuItemLeftRightSlider*)(&pThis->itemAudioSettingsEngineVolume))->~tPMenuItemLeftRightSlider();
  ((tPMenuItemLeftRightSlider*)(&pThis->itemAudioSettingsSpeechVolume))->~tPMenuItemLeftRightSlider();
  ((tPMenuItemLeftRightSlider*)(&pThis->itemAudioSettingsFXVolume))->~tPMenuItemLeftRightSlider();
  ((tPMenuItemLeftRightSlider*)(&pThis->itemAudioSettingsMusicVolume))->~tPMenuItemLeftRightSlider();
  ((tPMenuItemLeftRightChoice*)(&pThis->itemAudioSettingsAudioMode))->~tPMenuItemLeftRightChoice();
  ((tPListIterator*)(&pThis->iteratorAudioMode))->~tPListIterator();
  ((tPMenuItemNonInteractiveText*)(&pThis->itemAudioSettingsTitle))->~tPMenuItemNonInteractiveText();
  ((tPMenu*)(&pThis->menuOptions))->~tPMenu();
  ((tPMenuItemGoToMenuButton*)(&pThis->itemControllerSettings))->~tPMenuItemGoToMenuButton();
  ((tPMenuItemGoToMenuButton*)(&pThis->itemAudioSettings))->~tPMenuItemGoToMenuButton();
  ((tPMenuItemNonInteractiveText*)(&pThis->itemOptionsTitle))->~tPMenuItemNonInteractiveText();
  ((tPMenu*)(&pThis->menuPause))->~tPMenu();
  ((tPMenuItemCommandButton*)(&pThis->itemForfeitRace))->~tPMenuItemCommandButton();
  ((tPMenuItemCommandButton*)(&pThis->itemQuitRace))->~tPMenuItemCommandButton();
  ((tPMenuItemGoToMenuButton*)(&pThis->itemOptions))->~tPMenuItemGoToMenuButton();
  ((tPMenuItemCommandButton*)(&pThis->itemRestart))->~tPMenuItemCommandButton();
  ((tPMenuItemCommandButton*)(&pThis->itemContinue))->~tPMenuItemCommandButton();
  ((tPMenuItemNonInteractiveText*)(&pThis->itemGamePaused))->~tPMenuItemNonInteractiveText();
  if ((__in_chrg & 1) != 0) {
    __builtin_delete(pThis);
  }
}

/* ---- MPause_MusicLogic__Fc  [MPAUSE.CPP:290-371] SLD-VERIFIED ---- */
void MPause_MusicLogic(char active)

{
    /* folded receiver temp (SYM REG `this`) */
  bool bVar1;
  u_int uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 1;
  if (GameSetup_gData.userSetting.audioMode == 1) {
    gStereoMode = 0;
    Audio_direct3davail = 0;
  }
  else if (GameSetup_gData.userSetting.audioMode < 2) {
    if (GameSetup_gData.userSetting.audioMode == 0) {
      gStereoMode = 1;
      Audio_direct3davail = 0;
    }
  }
  else if (GameSetup_gData.userSetting.audioMode == 2) {
    gStereoMode = 1;
    Audio_direct3davail = 1;
  }
  if (active == '\0') {
    if (wasActive != '\0') {
      SNDstop(SFXHandle);
      AudioMus_AutoVolume(500,0);
    }
  }
  else {
    if (wasActive == '\0') {
      uVar2 = AudioCmn_MusicLevel(gMasterMusicLevel);
      AudioMus_AutoVolume(500,uVar2);
    }
    bVar1 = false;
    if ((gPauseCurrentMenu->fCurrentItem == 1) || (gPauseCurrentMenu->fCurrentItem == 2)) {
      bVar1 = true;
    }
    if (bVar1) {
      iVar3 = AudioCmn_MusicLevel(gMasterMusicLevel);
      AudioMus_Volume(iVar3);
    }
    if (gPauseCurrentMenu->fCurrentItem == 3) {
      vol = gMasterSFXLevel;
    }
    iVar3 = gPauseCurrentMenu->fCurrentItem;
    bVar1 = iVar3 == 4;
    if (bVar1) {
      vol = gMasterFENarrationLevel;
      iVar3 = gPauseCurrentMenu->fCurrentItem;
    }
    testSFX = bVar1 || gPauseCurrentMenu->fCurrentItem == 3;
    if (iVar3 == 5) {
      testSFX = true;
      vol = gMasterEngineLevel;
    }
    if (gPauseCurrentMenu->fCurrentItem == 6) {
      testSFX = true;
      vol = gMasterAmbientLevel;
    }
    if ((bool)testSFX == false) {
      if (playingSFX == '\x01') {
        SNDstop(SFXHandle);
        playingSFX = '\0';
      }
    }
    else {
      if (playingSFX == '\0') {
        playingSFX = '\x01';
      }
      else {
        iVar4 = SNDover(SFXHandle);
      }
      if ((iVar4 != 0) && (0xc0 < ticks - lastplaytick)) {
        lastplaytick = ticks;
        SFXHandle = AudioCmn_PlaySound(gSndBnk[3].bnkID,0x10,0,vol,0x40)
        ;
      }
    }
  }
  wasActive = active;
  return;
}

/* ---- MPause_ControllerLogic__Fv  [MPAUSE.CPP:376-385] SLD-VERIFIED ---- */
void MPause_ControllerLogic(void)

{
  tPMenuItem *shockMode = (tPMenuItem *)&gPauseMenuDefs->itemControllerShockMode;
  tPMenuItem *shockImpact = (tPMenuItem *)&gPauseMenuDefs->itemControllerShockImpact;
  int iVar1;
  
  iVar1 = PadGetState((u_int)(Device_gPausePortIndex != '\0') << 4);
  if (iVar1 == 2) {
    if (IsEnabled(shockMode) != 0) {
      ChangedEnabling = 1;
      shockMode->fFlags |= 1;
    }
    if (IsEnabled(shockImpact) == 0) {
      return;
    }
    shockImpact->fFlags |= 1;
  }
  else {
    if (IsDisabled(shockMode) != 0) {
      ChangedEnabling = 1;
      shockMode->fFlags &= ~1U;
    }
    if (IsDisabled(shockImpact) == 0) {
      return;
    }
    shockImpact->fFlags &= ~1U;
  }
  ChangedEnabling = 1;
}

/* ---- MPause_Logic__Fv  [MPAUSE.CPP:390-486] SLD-VERIFIED ---- */
extern "C" u_int MPause_Logic(void)

{
    /* folded receiver temp (SYM REG `this`) */
  int iVar1;
  int iVar2;
  int iVar3;
  __vtbl_ptr_type *entry;
  tPMenuCommand command;
  int local_18 [2];
  
  local_18[0] = 0;
  iVar1 = Debounce(gPauseCurrentMenu);
  iVar2 = Input_Interface(5,1);
  iVar3 = 2;
  if (iVar2 == 0) {
    iVar2 = Input_Interface(1,1);
    iVar3 = 0x200;
    if (iVar2 != 0) goto MPauseLogic_keyValJoin;
    iVar2 = Input_Interface(2,1);
    iVar3 = 0x400;
    if (iVar2 != 0) goto MPauseLogic_keyValJoin;
    iVar2 = Input_Interface(3,iVar1);
    iVar3 = 0x800;
    if (iVar2 != 0) goto MPauseLogic_keyValJoin;
    iVar1 = Input_Interface(4,iVar1);
    iVar3 = 0x1000;
    if (iVar1 != 0) goto MPauseLogic_keyValJoin;
    iVar1 = Input_Interface(6,1);
    iVar3 = 0x2000;
    if (iVar1 != 0) goto MPauseLogic_keyValJoin;
    iVar1 = Input_Interface(0x18,1);
    iVar3 = 0x10;
    if (iVar1 != 0) goto MPauseLogic_keyValJoin;
  }
  else {
MPauseLogic_keyValJoin:
    local_18[0] = iVar3;
  }
  command.type = 0;
  if (kMovingHighlight == 0) {
    if (local_18[0] != 0) {
      gMPauseUpdate = 1;
      iVar1 = gPauseCurrentMenu->fCurrentItem;
      entry = &(*gPauseCurrentMenu->_vf)[3];
      NFS4_VCALL_P2(entry->pfn,(u_char *)gPauseCurrentMenu + entry->delta,local_18,&command);
      iVar2 = (int)(short)gPauseCurrentMenu->fCurrentItem;
      if ((short)iVar1 != iVar2) {
        iVar1 = ItemEnabledNum(gPauseCurrentMenu,(short)iVar1);
        iVar3 = iVar1 * 0xd + 0x6a;
        iVar1 = ItemEnabledNum(gPauseCurrentMenu,iVar2);
        iVar1 = iVar1 * 0xd + 0x6a;
        kMovingHighlight = (short)iVar3 - (short)iVar1;
        kMovingHighlightDir = (u_short)((iVar1 - iVar3) / 10);
      }
      goto MPauseLogic_cmdProcess;
    }
    if (ChangedEnabling == 0) {
      if (gMPauseUpdateNextTime == 0) {
        gMPauseUpdate = 0;
      }
      else {
        gMPauseUpdate = 1;
        gMPauseUpdateNextTime = 0;
      }
      goto MPauseLogic_cmdProcess;
    }
  }
  gMPauseUpdate = 1;
MPauseLogic_cmdProcess:
  if (command.type != 0) {
    if ((command.type & 0x100) != 0) {
      gPauseMenuDefs->itemConfirmTitle._base_tPMenuItem.fTextDescription =
          gPauseCurrentMenu->fItemList[gPauseCurrentMenu->fCurrentItem]->fTextDescription;
      gPauseMenuDefs->menuConfirmYesNo.fCurrentItem = 0;
      gPauseMenuDefs->itemConfirmYes.fCommand = command.type & 0xff;
      command.nextMenu = &gPauseMenuDefs->menuConfirmYesNo;
      command.type = 6;
    }
    if (command.type == 6) {
      gBackList[gBackDepth] = gPauseCurrentMenu;
      iVar1 = gBackDepth + 1;
      gPauseCurrentMenu = command.nextMenu;
    }
    else {
      if (command.type != 7) {
        return command.type;
      }
      iVar1 = gBackDepth + -1;
      if (gBackDepth < 1) {
        return 1;
      }
      gPauseCurrentMenu = gBackList[iVar1];
    }
    gBackDepth = iVar1;
    entry = &(*gPauseCurrentMenu->_vf)[2];
    NFS4_VCALL0(entry->pfn,(u_char *)gPauseCurrentMenu + entry->delta);
  }
  MPause_MusicLogic(gPauseCurrentMenu == &gPauseMenuDefs->menuAudioSettings);
  MPause_ControllerLogic();
  return 0;
}

/* ---- MPause_Render__Fv  [MPAUSE.CPP:490-530] SLD-VERIFIED ---- */
void MPause_Render(void)

{
  __vtbl_ptr_type *entry;
  int iVar1;
  int iVar2;
  
  ChangedEnabling = 0;
  if ((short)kMovingHighlight < 1) {
    if ((-1 < (short)kMovingHighlight) ||
       (kMovingHighlight = kMovingHighlight + kMovingHighlightDir, (int)((u_int)kMovingHighlight << 0x10) < 1))
    goto MPauseRender_setHighlight;
  }
  else {
    kMovingHighlight = kMovingHighlight + kMovingHighlightDir;
    if (-1 < (int)((u_int)kMovingHighlight << 0x10)) goto MPauseRender_setHighlight;
  }
  kMovingHighlight = 0;
MPauseRender_setHighlight:
  if (kMovingHighlight == 0) {
    gPauseCurrentMenu->fHighlight = 1;
  }
  else {
    gPauseCurrentMenu->fHighlight = 0;
  }
  entry = &(*gPauseCurrentMenu->_vf)[4];
  NFS4_VCALL0(entry->pfn,(u_char *)gPauseCurrentMenu + entry->delta);
  iVar1 = NumEnabledItems(gPauseCurrentMenu);
  if (kMovingHighlight == 0) {
    iVar2 = ItemEnabledNum(gPauseCurrentMenu,gPauseCurrentMenu->fCurrentItem);
    iVar2 = iVar2 * 0xd + 0x6a;
  }
  else {
    iVar2 = ItemEnabledNum(gPauseCurrentMenu,gPauseCurrentMenu->fCurrentItem);
    iVar2 = iVar2 * 0xd + (short)kMovingHighlight + 0x6a;
  }
  Hud_FBuildF4(1,0x50,iVar2,0xa0,0xd,0,'\0','\0');
  Hud_RenderPauseBox(0x50,100,0xa0,(iVar1 + 1) * 0xd + 0x14);
  return;
}

/* ---- MPause_InitMPause__Fv  [MPAUSE.CPP:540-544] SLD-VERIFIED ---- */
void MPause_InitMPause(void)

{
  void *pvVar1;
  
  TextSys_LoadInGame(GameSetup_gData.userSetting.language);
  pvVar1 = __builtin_new(0x358);
  gPauseMenuDefs = tPauseMenuDefs_ct((tPauseMenuDefs *)pvVar1);
  return;
}

/* ---- MPause_StartPauseMenu__Fv  [MPAUSE.CPP:548-593] SLD-VERIFIED ---- */
void MPause_StartPauseMenu(void)

{
  tPMenuItem *restart = (tPMenuItem *)&gPauseMenuDefs->itemRestart;
  tPMenuItem *quitRace = (tPMenuItem *)&gPauseMenuDefs->itemQuitRace;
  tPMenuItem *forfeitRace = (tPMenuItem *)&gPauseMenuDefs->itemForfeitRace;
  tPMenuItem *musicVolume = (tPMenuItem *)&gPauseMenuDefs->itemAudioSettingsMusicVolume;
  __vtbl_ptr_type *entry;

  gPauseCurrentMenu = &gPauseMenuDefs->menuPause;
  entry = &(*gPauseCurrentMenu->_vf)[2];
  NFS4_VCALL0(entry->pfn,(u_char *)gPauseCurrentMenu + entry->delta);
  gBackDepth = 0;
  if ((GameSetup_gData.raceType == 6) || (GameSetup_gData.raceType == 2)) {
    if (IsEnabled(restart) != 0) {
      ChangedEnabling = 1;
      restart->fFlags |= 1;
    }
  }
  else {
    if (IsDisabled(restart) != 0) {
      ChangedEnabling = 1;
      restart->fFlags &= ~1U;
    }
  }
  if (GameSetup_gData.raceType == 6) {
    if (IsDisabled(forfeitRace) != 0) {
      ChangedEnabling = 1;
      forfeitRace->fFlags &= ~1U;
    }
    if (IsEnabled(quitRace) != 0) {
      ChangedEnabling = 1;
      quitRace->fFlags |= 1;
    }
  }
  else {
    if (IsEnabled(forfeitRace) != 0) {
      ChangedEnabling = 1;
      forfeitRace->fFlags |= 1;
    }
    if (IsDisabled(quitRace) != 0) {
      ChangedEnabling = 1;
      quitRace->fFlags &= ~1U;
    }
  }
  if (IsDisabled(musicVolume) != 0) {
    ChangedEnabling = 1;
    musicVolume->fFlags &= ~1U;
  }
  if (Replay_ReplayMode < 2) {
    gPauseMenuDefs->itemQuitRace.fCommand |= 0x100;
    gPauseMenuDefs->itemRestart.fCommand |= 0x100;
    gPauseMenuDefs->itemForfeitRace.fCommand |= 0x100;
  }
  else {
    gPauseMenuDefs->itemQuitRace.fCommand &= ~0x100;
    gPauseMenuDefs->itemRestart.fCommand &= ~0x100;
    gPauseMenuDefs->itemForfeitRace.fCommand &= ~0x100;
  }
}

/* ---- MPause_EndPauseMenu__Fv  [MPAUSE.CPP:598-600] SLD-VERIFIED ---- */
void MPause_EndPauseMenu(void)

{
  InGame_ResetPSXController((u_int)(u_char)Device_gPausePortIndex,
             GameSetup_gData.controllerData.controllerConfig[(u_char)Device_gPausePortIndex]);
  return;
}

/* ---- MPause_KillMPause__Fv  [MPAUSE.CPP:605-610] SLD-VERIFIED ---- */
void MPause_KillMPause(void)

{
  DrawSync(0);
  if (gPauseMenuDefs != 0) {
    ((tPauseMenuDefs*)(gPauseMenuDefs))->~tPauseMenuDefs();
  }
  TextSys_UnloadWords();
  return;
}

/* end of mpause.cpp */
