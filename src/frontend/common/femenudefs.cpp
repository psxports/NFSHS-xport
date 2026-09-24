/* frontend/common/femenudefs.cpp -- RECONSTRUCTED (menu-command callbacks + menu-defs ctor; C++ TU)
 *   66 fns: free MenuExtended_* command callbacks + tGlobalMenuDefs ctor/dtor (menu-defs init)
 *   + TransitionIsFinished button methods. Free fns in ns nfs4::FRONTEND::COMMON::FEMenuDefs.
 */
#include "femenudefs.h"
#include "../../mips_semantics.h"

/* ---- FEMenuDefs.obj-OWNED globals -- DEFINED here (self-contained; .data=real EXE bytes) ---- */
/* tBlankMenuItemGoToMenuNFS4Button_vtable @0x800114d8 + tBlankMenuItemNFS4LeftRightChoice_vtable @0x80011530:
   real __vtbl_ptr_type[11] defs live in game/common/vtables_tmenu.cpp; declared extern via femenudefs_externs.h. */
short        SelectListNull[2];   /* @0x80051970  (bss(zero)) */
short        SelectListOffOn[3] = { 103, 102, 0 };   /* @0x80051974 */
short        SelectListNormal[3] = { 227, 225, 0 };   /* @0x8005197c */
short        SelectListOpponentUpgrades[3] = { 271, 272, 0 };   /* @0x80051984 */
short        SelectListTrackDirection[3] = { 228, 229, 0 };   /* @0x8005198c */
short        SelectListTransmission[3] = { 276, 275, 0 };   /* @0x80051994 */
short        SelectListDisplaySpeed[5] = { 500, 498, 499, 103, 0 };   /* @0x8005199c */
short        SelectListDisplayMap[4] = { 103, 488, 489, 0 };   /* @0x800519a8 */
short        SelectListDisplayOpponentID[4] = { 103, 501, 502, 0 };   /* @0x800519b0 */
short        SelectListSplitTime[4] = { 103, 490, 491, 0 };   /* @0x800519b8 */
short        SelectListSplitDisplay[3] = { 492, 493, 0 };   /* @0x800519c0 */
short        SelectListUpgrades[4] = { 150, 151, 152, 0 };   /* @0x800519c8 */
short        SelectListControllerConfig[4] = { 539, 540, 541, 0 };   /* @0x800519d0 */
short        SelectListAudioMode[4] = { 466, 467, 468, 0 };   /* @0x800519d8 */
int          gCarActivation[6][5] = { 25, 25, 25, 25, 25, 24, 24, 24, 24, 24, 26, 26, 26, 27, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28 };   /* @0x800519e0 */
tGlobalMenuDefs *menuDefs;   /* @0x80051a58  (bss(zero)) */


/* ---- MenuExtended_SetOnePlayer  [FEMENUDEFS.CPP:145-153] ---- */

/* Decoded Phase 83: MenuExtended_SetOnePlayer(tMenuCommand&) - set numPlayers=1 (76 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_SetOnePlayer(tMenuCommand *command)

{
  if (FEApp->fInputPlayer == '\x01') {
    command->type = kMenu_Command_None;
  }
  else {
    frontEnd.gameMode = '\0';
    SwapBackground(screenMain,-1);
  }
  return;
}



/* ---- MenuExtended_SetTwoPlayer  [FEMENUDEFS.CPP:158-167] ---- */

/* Decoded Phase 83: MenuExtended_SetTwoPlayer(tMenuCommand&) - set numPlayers=2 (split-screen) (80
   B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_SetTwoPlayer(tMenuCommand *command)

{
  if (gPadinfo.buf[4].nopad == '\0') {
    frontEnd.gameMode = '\x01';
    frontEnd.oppNumber = '\0';
    SwapBackground(screenMain,-1);
  }
  else {
    command->type = kMenu_Command_None;
  }
  return;
}



/* ---- MenuExtended_SetTestDrive  [FEMENUDEFS.CPP:172-176] ---- */

/* Decoded Phase 83: MenuExtended_SetTestDrive(tMenuCommand&) - set mode=TestDrive (free-roam, no
   race) (28 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetTestDrive(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetTestDrive(tMenuCommand *command)

{
  frontEnd.carListType = '\0';
  frontEnd.oppNumber = '\0';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  return;
}



/* ---- MenuExtended_SetSingleRace  [FEMENUDEFS.CPP:180-184] ---- */

/* Decoded Phase 83: MenuExtended_SetSingleRace(tMenuCommand&) - set raceType=SingleRace (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetSingleRace(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetSingleRace(tMenuCommand *command)

{
  frontEnd.carListType = '\x01';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  SwapBackground(screenMain,-1);
  return;
}



/* ---- MenuExtended_SetTournament  [FEMENUDEFS.CPP:195-200] ---- */

/* Decoded Phase 83: MenuExtended_SetTournament(tMenuCommand&) - set raceType=Tournament (72 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetTournament(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetTournament(tMenuCommand *command)

{
  frontEnd.carListType = '\x01';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.tier = '\0';
  frontEnd.raceType = '\x02';
  SwapBackground(screenMain,-1);
  return;
}



/* ---- MenuExtended_SetSpecialEvent  [FEMENUDEFS.CPP:204-209] ---- */

/* Decoded Phase 83: MenuExtended_SetSpecialEvent(tMenuCommand&) - set raceType=SpecialEvent (72 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetSpecialEvent(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetSpecialEvent(tMenuCommand *command)

{
  frontEnd.carListType = '\x01';
  frontEnd.tier = '\x01';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x02';
  SwapBackground(screenMain,-1);
  return;
}



/* ---- MenuExtended_SetSoloRace  [FEMENUDEFS.CPP:213-217] ---- */

/* Decoded Phase 83: MenuExtended_SetSoloRace(tMenuCommand&) - set raceType=Solo (no opponents) (32
   B)
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name + (body or
   100%-caller-consensus) agree. Generic param names; types int/void* default - refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetSoloRace(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetSoloRace(tMenuCommand *command)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  frontEnd.oppNumber = '\0';
  frontEnd.carListType = '\x01';
  return;
}



/* ---- MenuExtended_GoToTwoPlayerSingleRace  [FEMENUDEFS.CPP:221-245] ---- */

/* Decoded Phase 83: MenuExtended_GoToTwoPlayerSingleRace(tMenuCommand&) - enter 2P single-race flow(276 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToTwoPlayerSingleRace(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  tScreenCarSelect *this_00;
  ushort uVar2;
  short sVar3;
  tDialogYesNoTri *dlgThis;
  union {
    intptr align;
    byte bytes[sizeof(tDialogYesNoTri)];
  } YesNoDialogStorage;
  
  dlgThis = (tDialogYesNoTri *)YesNoDialogStorage.bytes;
  tDialogYesNo_ctor(&dlgThis->_base_tDialogYesNo);
  *(void **)&(dlgThis->_base_tDialogYesNo._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogYesNoTri_vtable;
  uVar2 = (ushort)carManager.GetNumOwnedCars(0);
  if ((int)((uint)uVar2 << 0x10) < 1) {
    dlgThis->_base_tDialogYesNo._base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0x42);
    dlgThis->_base_tDialogYesNo.yesnowords[0] = 0x321;
    dlgThis->_base_tDialogYesNo.yesnowords[1] = 0x322;
    dlgThis->_base_tDialogYesNo._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    sVar3 = dlgThis->_base_tDialogYesNo._base_tDialogInteractive.Run();
    ptVar1 = menuDefs;
    if (sVar3 == 1) {
      frontEnd.raceType = '\0';
      command->type = kMenu_Command_GoToMenu;
      ptVar1->iteratorDealerCar.Decrement(kPlayerBoth);
      menuDefs->iteratorDealerCar.Increment(kPlayerBoth);
      this_00 = screenCarSelect;
      command->nextMenu = (tMenu *)&(menuDefs->menuCarDealer)._base_tMenu;
      this_00->SetState(2);
    }
  }
  else {
    MenuExtended_SetSoloRace(command);
    ptVar1 = menuDefs;
    command->type = kMenu_Command_GoToMenu;
    command->nextMenu = (tMenu *)&(ptVar1->menuSingleTrackSelect)._base_tMenu;
  }
  (((tScreen*)((tScreen *)dlgThis))->~tScreen(), (tScreen*)((tScreen *)dlgThis));
  return;
}



/* ---- MenuExtended_SetDuelRace  [FEMENUDEFS.CPP:247-251] ---- */

/* Decoded Phase 83: MenuExtended_SetDuelRace(tMenuCommand&) - set raceType=Duel (1v1) (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetDuelRace(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetDuelRace(tMenuCommand *command)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  frontEnd.oppNumber = '\x01';
  SwapBackground(screenMain,-1);
  return;
}



/* ---- MenuExtended_SetFullGrid  [FEMENUDEFS.CPP:255-259] ---- */

/* Decoded Phase 83: MenuExtended_SetFullGrid(tMenuCommand&) - set grid size to maximum opponents(64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetFullGrid(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetFullGrid(tMenuCommand *command)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\0';
  frontEnd.oppNumber = '\x02';
  SwapBackground(screenMain,-1);
  return;
}



/* ---- AskTheUserToSaveTheGame  [FEMENUDEFS.CPP:274-290] ---- */

/* Decoded Phase 86: FE-AskTheUserToSaveTheGame (120 B): show "Save game?" Yes/No prompt.
   
   [ghidra-meta] section: front.text
   
   [Locals 2026-05-08] Locals renamed via deep-body inspection. FE-MenuDefs::AskTheUserToSaveTheGame
   - 'Save game?' Yes/No prompt. is_cheater = FECheat_IsTheUserACryBabyCheater (= block save if
   cheater detected); on cheater: return 0 (= No-saving-allowed). Else: build YesNoDialog on stack(168 B); set string=TextSys_Word(0x331)='Save game?'; yesnowords[0]=0x321='YES', [1]=0x322='NO';
   fDefault=0 (= No is default). Run shows the modal dialog and returns user_choice. Destructor on
   dialog. Returns user_choice (1=Yes, 0=No). */

int AskTheUserToSaveTheGame(void)

{
  short user_choice;
  void *is_cheater;
  int answer;
  tDialogMessageString *dlgThis;
  tDialogYesNo YesNoDialog;
  
  is_cheater = (void *)(intptr)FECheat_IsTheUserACryBabyCheater();
  answer = 0;
  if (is_cheater != (void *)0x1) {
    tDialogYesNo_ctor(&YesNoDialog);
    YesNoDialog._base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0x331);
    YesNoDialog.yesnowords[0] = 0x321;
    YesNoDialog.yesnowords[1] = 0x322;
    YesNoDialog._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    user_choice = Run(&YesNoDialog._base_tDialogInteractive);
    answer = (int)user_choice;
    (((tScreen*)((tScreen *)&YesNoDialog))->~tScreen(), (tScreen*)((tScreen *)&YesNoDialog));
  }
  return answer;
}



/* ---- MenuExtended_TransitionFromPostGameToMainMenu  [FEMENUDEFS.CPP:295-297] ---- */

/* Decoded Phase 83: MenuExtended_TransitionFromPostGameToMainMenu(tMenuCommand&) - return to main
   menu without saving (28 B)
   
   [ghidra-meta] section: front.text */

extern "C" void MenuExtended_TransitionFromPostGameToMainMenu(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  
  ptVar1 = menuDefs;
  command->type = kMenu_Command_GoToMenuOneWay;
  command->nextMenu = (tMenu *)&(ptVar1->menuMain)._base_tMenu;
  return;
}



/* ---- MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame  [FEMENUDEFS.CPP:301-308] ---- */

/* Decoded Phase 83: MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame(tMenuCommand&) -
   auto-save then return to main menu (76 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  int iVar2;
  
  iVar2 = AskTheUserToSaveTheGame();
  ptVar1 = menuDefs;
  if (iVar2 == 0) {
    MenuExtended_TransitionFromPostGameToMainMenu(command);
  }
  else {
    command->type = kMenu_Command_GoToMenuOneWay;
    command->nextMenu = (tMenu *)&(ptVar1->menuPostGameSave)._base_tMenu;
  }
  return;
}



/* ---- MenuExtended_GoToCarSelect  [FEMENUDEFS.CPP:313-420] ---- */

/* Decoded Phase 83: MenuExtended_GoToCarSelect(tMenuCommand&) - transition to car-select screen;
   sets up garage car list (916 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToCarSelect(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  ushort uVar2;
  char *pcVar3;
  tMenu *ptVar4;
  tFEApplication *dlgThis;
  tScreenCarSelectDuel *this_00;
  tListIteratorCar *this_01;
  uint state;
  tDialogMessageString *this_02;
  tTrackInformation trackInfo;
  
  ptVar1 = FEApp;
  this_02 = &FEApp->messagePopup;
  GetTrack(&trackManager,(ushort)(byte)frontEnd.track[(byte)frontEnd.pinkSlipsTrackIndex],
             &trackInfo);
  if (trackInfo.fAvailable == '\0') {
    pcVar3 = TextSys_Word(0xeb);
    (ptVar1->messagePopup).string = pcVar3;
    Display(&this_02->_base_tDialogBase);
    return;
  }
  if (frontEnd.gameMode == '\x01') {
    command->type = kMenu_Command_GoToMenuTwoPlayer;
    if (frontEnd.raceType == '\x06') {
      command->nextMenu = (tMenu *)&menuDefs->menuPlayerOnePinkSlipCarSelect;
    }
    else if (frontEnd.carListType == '\0') {
      command->nextMenu = (tMenu *)&menuDefs->menuPlayerOneCarSelect;
    }
    else {
      command->nextMenu = (tMenu *)&menuDefs->menuPlayerOneGarage;
    }
  }
  else {
    if (frontEnd.oppNumber == '\x01') {
      command->type = kMenu_Command_GoToMenu;
      if (frontEnd.raceType == '\x01') {
        ptVar4 = &(menuDefs->menuHPDuelCarSelect)._base_tMenu;
      }
      else {
        ptVar4 = &(menuDefs->menuDuelCarSelect)._base_tMenu;
      }
      command->nextMenu = ptVar4;
      state = 7;
      this_00 = screenCarSelectDuel;
    }
    else {
      command->type = kMenu_Command_GoToMenu;
      this_00 = (tScreenCarSelectDuel *)screenCarSelect;
      if (frontEnd.carListType != '\0') {
        ptVar4 = &(menuDefs->menuCarGarage)._base_tMenu;
      }
      else {
        ptVar4 = &(menuDefs->menuSingleCarSelect)._base_tMenu;
      }
      state = (uint)(frontEnd.carListType != '\0');
      command->nextMenu = ptVar4;
    }
    SetState(&this_00->_base_tScreenCarSelect,state);
  }
  if (frontEnd.raceType == '\x01') {
    if ((frontEnd.oppNumber == '\0') || (frontEnd.gameMode == '\x01')) {
      (menuDefs->iteratorCar1).fCarListFilter = 9;
    }
    else {
      (menuDefs->iteratorCar1).fCarListFilter = 1;
    }
  }
  else if (frontEnd.raceType == '\x06') {
    (menuDefs->iteratorPinkSlipsCar).fCarListFilter = 0x20;
  }
  else if (frontEnd.carListType == '\0') {
    (menuDefs->iteratorCar1).fCarListFilter = 1;
  }
  else if (frontEnd.raceType == '\x02') {
    (menuDefs->iteratorGarageCar).fCarListFilter = 0x40;
  }
  else {
    (menuDefs->iteratorGarageCar).fCarListFilter = 2;
  }
  if (frontEnd.carListType == '\0') {
    menuDefs->iteratorCar1.Decrement(kPlayerOne);
    menuDefs->iteratorCar1.Increment(kPlayerOne);
    menuDefs->iteratorCar1.Decrement(kPlayerTwo);
    this_01 = &menuDefs->iteratorCar1;
MX_GoToCar_iteratorIncP2:
    this_01->Increment(kPlayerTwo);
  }
  else {
    uVar2 = GetNumOwnedCars(&carManager, 0);
    if ((int)((uint)uVar2 << 0x10) < 1) {
      if (frontEnd.raceType == '\x01') {
        if (frontEnd.oppNumber == '\x01') goto MX_GoToCar_oppFilterSetup;
        goto MX_GoToCar_garageIter;
      }
    }
    else {
MX_GoToCar_garageIter:
      menuDefs->iteratorGarageCar.Decrement(kPlayerOne);
      menuDefs->iteratorGarageCar.Increment(kPlayerOne);
      if (frontEnd.gameMode == '\x01') {
        menuDefs->iteratorGarageCar.Decrement(kPlayerTwo);
        this_01 = &menuDefs->iteratorGarageCar;
        goto MX_GoToCar_iteratorIncP2;
      }
    }
  }
  if (frontEnd.oppNumber != '\x01') {
    return;
  }
MX_GoToCar_oppFilterSetup:
  if (frontEnd.raceType != '\x02') {
    menuDefs->iteratorOpponentCar.Decrement(kPlayerBoth);
    menuDefs->iteratorOpponentCar.Increment(kPlayerBoth);
    (menuDefs->iteratorOpponentCar).fCarListFilter = 1;
  }
  return;
}



/* ---- MenuExtended_GoToDealer  [FEMENUDEFS.CPP:423-428] ---- */

/* Decoded Phase 83: MenuExtended_GoToDealer(tMenuCommand&) - transition to buy-car dealer screen(104 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToDealer(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  tScreenCarSelect *dlgThis;
  
  dlgThis = screenCarSelect;
  ptVar1 = menuDefs;
  command->type = 1;
  command->nextMenu = (tMenu *)&ptVar1->menuCarDealer;
  dlgThis->SetState(2);
  menuDefs->iteratorDealerCar.Decrement(kPlayerBoth);
  menuDefs->iteratorDealerCar.Increment(kPlayerBoth);
  return;
}



/* ---- MenuExtended_GoToSeller  [FEMENUDEFS.CPP:432-437] ---- */

/* Decoded Phase 83: MenuExtended_GoToSeller(tMenuCommand&) - transition to sell-car screen (104 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToSeller(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  tScreenCarSelect *dlgThis;
  
  dlgThis = screenCarSelect;
  ptVar1 = menuDefs;
  command->type = 1;
  command->nextMenu = (tMenu *)&ptVar1->menuCarSeller;
  dlgThis->SetState(3);
  menuDefs->iteratorSellerCar.Decrement(kPlayerBoth);
  menuDefs->iteratorSellerCar.Increment(kPlayerBoth);
  return;
}



/* ---- MenuExtended_GoToUpgrades  [FEMENUDEFS.CPP:441-444] ---- */

/* Decoded Phase 83: MenuExtended_GoToUpgrades(tMenuCommand&) - transition to upgrades-purchase
   screen (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToUpgrades(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  
  ptVar1 = menuDefs;
  command->type = kMenu_Command_GoToMenu;
  command->nextMenu = (tMenu *)&(ptVar1->menuCarUpgrades)._base_tMenu;
  SetState(screenCarSelect,4);
  return;
}



/* ---- GenericMenuSaveGame  [FEMENUDEFS.CPP:448-478] ---- */

/* Decoded Phase 86: FE-GenericMenuSaveGame (284 B): execute generic save-game flow from
   menu.
   
   [ghidra-meta] section: front.text */

void * GenericMenuSaveGame(int showdialog)

{
  bool successful;
  tFEApplication *ptVar2;
  tFEApplication *ptVar3;
  char *pcVar4;
  void *pvVar5;
  tScreenMemcard *dlgThis;
  byte uninitafter;
  
  ptVar2 = FEApp;
  screenMemcard->message = 0x27e;
  Redraw(ptVar2);
  ptVar2 = FEApp;
  successful = false;
  if ((MEMCARD_INITIALIZED == 0) || (showdialog != 0)) {
    pcVar4 = TextSys_Word(0x282);
    ptVar3 = FEApp;
    (ptVar2->NoInputMemCardDialog)._base_tDialogMessageString.string = pcVar4;
    Display((tDialogBase *)&ptVar3->NoInputMemCardDialog);
    while ((FEApp->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFullyOpen != 1) {
      Redraw(FEApp);
    }
    Redraw(FEApp);
    if (MEMCARD_INITIALIZED == 0) {
      successful = true;
      Init_Memcard(true,0);
    }
  }
  pvVar5 = (void *)(intptr)SaveGame(0);
  screenMemcard->message = -1;
  if (successful) {
    DeInit_Memcard();
  }
  Hide((tDialogBase *)&FEApp->NoInputMemCardDialog);
  return pvVar5;
}



/* ---- PinkSlipsPreSave  [FEMENUDEFS.CPP:484-504] ---- */

/* Decoded Phase 86: FE-PinkSlipsPreSave (200 B): pre-save hook for Pink Slips mode.
   
   [ghidra-meta] section: front.text */

void * PinkSlipsPreSave(void)

{
  short sVar1;
  void *pvVar2;
  int answer;
  tDialogYesNoTri *dlgThis;
  byte ret;
  void *pvVar3;
  tDialogYesNoTri YesNoDialog;
  
  pvVar2 = (void *)(intptr)FECheat_IsTheUserACryBabyCheater();
  pvVar3 = (void *)0x1;
  if (pvVar2 == (void *)0x1) {
    pvVar3 = (void *)0x1;
  }
  else {
    tDialogYesNo_ctor(&YesNoDialog._base_tDialogYesNo);
    *(void **)&(YesNoDialog._base_tDialogYesNo._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogYesNoTri_vtable;
    YesNoDialog._base_tDialogYesNo._base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0x273);
    YesNoDialog._base_tDialogYesNo.yesnowords[0] = 0x321;
    YesNoDialog._base_tDialogYesNo.yesnowords[1] = 0x322;
    YesNoDialog._base_tDialogYesNo._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    sVar1 = Run(&YesNoDialog._base_tDialogYesNo._base_tDialogInteractive);
    if (sVar1 == 1) {
      pvVar3 = GenericMenuSaveGame(1);
    }
    else if (sVar1 == -1) {
      (((tScreen*)((tScreen *)&YesNoDialog._base_tDialogYesNo))->~tScreen(), (tScreen*)((tScreen *)&YesNoDialog._base_tDialogYesNo));
      return (void *)0x0;
    }
    (((tScreen*)((tScreen *)&YesNoDialog))->~tScreen(), (tScreen*)((tScreen *)&YesNoDialog));
  }
  return pvVar3;
}



/* ---- MenuExtended_GoToBestOfOne  [FEMENUDEFS.CPP:508-519] ---- */

/* Decoded Phase 83: MenuExtended_GoToBestOfOne(tMenuCommand&) - set tournament length to best-of-1
   (92 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToBestOfOne(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  void *pvVar2;
  
  pvVar2 = PinkSlipsPreSave();
  ptVar1 = menuDefs;
  if (pvVar2 == (void *)0x0) {
    command->type = kMenu_Command_None;
  }
  else {
    command->type = kMenu_Command_GoToMenu;
    command->nextMenu = (tMenu *)&(ptVar1->menuSingleTrackSelect)._base_tMenu;
  }
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.pinkSlipsNumTracks = '\x01';
  return;
}



/* ---- MenuExtended_GoToBestOfThree  [FEMENUDEFS.CPP:523-533] ---- */

/* Decoded Phase 83: MenuExtended_GoToBestOfThree(tMenuCommand&) - set tournament length to
   best-of-3 (92 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToBestOfThree(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  void *pvVar2;
  
  pvVar2 = PinkSlipsPreSave();
  ptVar1 = menuDefs;
  if (pvVar2 == (void *)0x0) {
    command->type = kMenu_Command_None;
  }
  else {
    command->type = kMenu_Command_GoToMenu;
    command->nextMenu = (tMenu *)&(ptVar1->menuPinkSlipsBestOfThree)._base_tMenu;
  }
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.pinkSlipsNumTracks = '\x03';
  return;
}



/* ---- MenuExtended_GoToBestOfFive  [FEMENUDEFS.CPP:537-547] ---- */

/* Decoded Phase 83: MenuExtended_GoToBestOfFive(tMenuCommand&) - set tournament length to best-of-5
   (92 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToBestOfFive(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  void *pvVar2;
  
  pvVar2 = PinkSlipsPreSave();
  ptVar1 = menuDefs;
  if (pvVar2 == (void *)0x0) {
    command->type = kMenu_Command_None;
  }
  else {
    command->type = kMenu_Command_GoToMenu;
    command->nextMenu = (tMenu *)&(ptVar1->menuPinkSlipsBestOfFive)._base_tMenu;
  }
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.pinkSlipsNumTracks = '\x05';
  return;
}



/* ---- MenuExtended_GoToRace  [FEMENUDEFS.CPP:551-607] ---- */

/* Decoded Phase 83: MenuExtended_GoToRace(tMenuCommand&) - commit settings and transition into race(calls Front_BuildStream) (348 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToRace(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  ushort uVar2;
  char *pcVar3;
  tFEApplication *dlgThis;
  int wordnum;
  tDialogMessageString *popUp;
  tCarInfo carInfo;
  
  ptVar1 = FEApp;
  command->type = kMenu_Command_StartRace;
  if ((((frontEnd.carListType != '\x01') ||
       (uVar2 = GetNumOwnedCars(&carManager, 0), 0 < (int)((uint)uVar2 << 0x10))) ||
      (frontEnd.raceType == '\x01')) || (wordnum = 0xaa, frontEnd.raceType == '\x06')) {
    if ((frontEnd.raceType == '\x02') &&
       (uVar2 = GetNumTourneyCars(&carManager, 0), (int)((uint)uVar2 << 0x10) < 1)) {
      wordnum = 0xf1;
    }
    else if ((frontEnd.raceType == '\x01') &&
            (GetStockCar(&carManager, (ushort)(byte)frontEnd.playerCar[0],&carInfo),
            carInfo.fPursuitAvailable == '\0')) {
      wordnum = 0xf2;
    }
    else {
      if (frontEnd.carListType != '\0') {
        return;
      }
      GetStockCar(&carManager, (ushort)(byte)frontEnd.playerCar[0],&carInfo);
      wordnum = 0xf3;
      if (carInfo.fAvailable != '\0') {
        return;
      }
    }
  }
  pcVar3 = TextSys_Word(wordnum);
  (ptVar1->messagePopup).string = pcVar3;
  Display(&(ptVar1->messagePopup)._base_tDialogBase);
  command->type = kMenu_Command_None;
  return;
}



/* ---- MenuExtended_GoTo2PlayerRace  [FEMENUDEFS.CPP:610-655] ---- */

/* Decoded Phase 83: MenuExtended_GoTo2PlayerRace(tMenuCommand&) - enter 2-player split-screen race
   setup flow (332 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoTo2PlayerRace(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  ushort uVar2;
  tFEApplication *dlgThis;
  char *pcVar3;
  int wordnum;
  tDialogMessageString *popUp;
  tCarInfo carInfo;
  
  ptVar1 = FEApp;
  command->type = kMenu_Command_Start2PlayerRace;
  if (frontEnd.raceType == '\x06') {
    return;
  }
  if (((frontEnd.carListType != '\x01') ||
      (uVar2 = GetNumOwnedCars(&carManager, 0), 0 < (int)((uint)uVar2 << 0x10))) ||
     (wordnum = 0xaa, frontEnd.raceType == '\x01')) {
    if ((frontEnd.carListType == '\0') &&
       (GetStockCar(&carManager, (ushort)(byte)frontEnd.playerCar[(byte)FEApp->fPlayer],&carInfo),
       carInfo.fAvailable == '\0')) {
      wordnum = 0xf3;
    }
    else {
      if (frontEnd.raceType != '\x01') {
        return;
      }
      GetStockCar(&carManager, (ushort)(byte)frontEnd.playerCar[(byte)FEApp->fPlayer],&carInfo);
      wordnum = 0xf2;
      if (carInfo.fPursuitAvailable != '\0') {
        return;
      }
    }
  }
  pcVar3 = TextSys_Word(wordnum);
  (ptVar1->messagePopup).string = pcVar3;
  Display(&(ptVar1->messagePopup)._base_tDialogBase);
  command->type = kMenu_Command_None;
  return;
}



/* ---- MenuExtended_GoToTournTrackInfo  [FEMENUDEFS.CPP:658-693] ---- */

/* Decoded Phase 83: MenuExtended_GoToTournTrackInfo(tMenuCommand&) - transition to tournament-round
   track info screen (360 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToTournTrackInfo(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  tGlobalMenuDefs *ptVar2;
  tTournamentDefinition *ptVar3;
  short sVar4;
  char *pcVar5;
  long amount;
  int iVar6;
  int iVar7;
  tDialogMessageString *dlgThis;
  tDialogMessageString *this_00;
  tTourneyInfo *tourn;
  tDialogYesNo *popUp;
  union {
    intptr align;
    byte bytes[sizeof(tDialogYesNo)];
  } popUpStorage;
  
  popUp = (tDialogYesNo *)popUpStorage.bytes;
  ptVar3 = tournamentManager.fDefinition;
  ptVar1 = FEApp;
  frontEnd.tier = '\0';
  iVar6 = (uint)(tournamentManager.fDefinition)->fTiers[0].fTournOffset +
          (uint)(byte)frontEnd.tournament;
  iVar7 = (tournamentManager.fDefinition)->fTournaments[iVar6].fEntranceFee;
  if (0 < iVar7) {
    if (tournamentManager.fMoney < iVar7) {
      this_00 = &FEApp->messagePopup;
      pcVar5 = TextSys_Word(0xf6);
      (ptVar1->messagePopup).string = pcVar5;
      this_00->_base_tDialogBase.Display();
      return;
    }
    tDialogYesNo_ctor(popUp);
    popUp->_base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0xf7);
    popUp->yesnowords[0] = 0x322;
    popUp->yesnowords[1] = 0x321;
    popUp->_base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    sVar4 = popUp->_base_tDialogInteractive.Run();
    if (sVar4 == 0) {
      (((tScreen*)((tScreen *)popUp))->~tScreen(), (tScreen*)((tScreen *)popUp));
      return;
    }
    AudioCmn_PlayFESFX(0x1a);
    tournamentManager.fMoney = tournamentManager.fMoney - ptVar3->fTournaments[iVar6].fEntranceFee;
    (((tScreen*)((tScreen *)popUp))->~tScreen(), (tScreen*)((tScreen *)popUp));
  }
  tournamentManager.StartNewTournament(0,(u_char)frontEnd.tournament);
  ptVar2 = menuDefs;
  command->type = kMenu_Command_GoToMenu;
  command->nextMenu = (tMenu *)&(ptVar2->menuTrackInfo)._base_tMenu;
  return;
}



/* ---- MenuExtended_GoToSpecialEventTrackInfo  [FEMENUDEFS.CPP:696-731] ---- */

/* Decoded Phase 83: MenuExtended_GoToSpecialEventTrackInfo(tMenuCommand&) - transition to
   special-event track info screen (364 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToSpecialEventTrackInfo(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  tGlobalMenuDefs *ptVar2;
  tTournamentDefinition *ptVar3;
  short sVar4;
  char *pcVar5;
  long amount;
  int iVar6;
  int iVar7;
  tDialogMessageString *dlgThis;
  tDialogMessageString *this_00;
  tTourneyInfo *tourn;
  tDialogYesNo *popUp;
  union {
    intptr align;
    byte bytes[sizeof(tDialogYesNo)];
  } popUpStorage;
  
  popUp = (tDialogYesNo *)popUpStorage.bytes;
  ptVar3 = tournamentManager.fDefinition;
  ptVar1 = FEApp;
  frontEnd.tier = '\x01';
  iVar6 = (uint)(tournamentManager.fDefinition)->fTiers[1].fTournOffset +
          (uint)(byte)frontEnd.specialevent;
  iVar7 = (tournamentManager.fDefinition)->fTournaments[iVar6].fEntranceFee;
  if (0 < iVar7) {
    if (tournamentManager.fMoney < iVar7) {
      this_00 = &FEApp->messagePopup;
      pcVar5 = TextSys_Word(0xf6);
      (ptVar1->messagePopup).string = pcVar5;
      this_00->_base_tDialogBase.Display();
      return;
    }
    tDialogYesNo_ctor(popUp);
    popUp->_base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0xf7);
    popUp->yesnowords[0] = 0x321;
    popUp->yesnowords[1] = 0x322;
    popUp->_base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    sVar4 = popUp->_base_tDialogInteractive.Run();
    if (sVar4 == 0) {
      (((tScreen*)((tScreen *)popUp))->~tScreen(), (tScreen*)((tScreen *)popUp));
      return;
    }
    AudioCmn_PlayFESFX(0x1a);
    tournamentManager.fMoney = tournamentManager.fMoney - ptVar3->fTournaments[iVar6].fEntranceFee;
    (((tScreen*)((tScreen *)popUp))->~tScreen(), (tScreen*)((tScreen *)popUp));
  }
  tournamentManager.StartNewTournament(1,(u_char)frontEnd.specialevent);
  ptVar2 = menuDefs;
  command->type = kMenu_Command_GoToMenu;
  command->nextMenu = (tMenu *)&(ptVar2->menuTrackInfo)._base_tMenu;
  return;
}



/* ---- MenuExtended_EnterUserName  [FEMENUDEFS.CPP:734-739] ---- */

/* Decoded Phase 83: MenuExtended_EnterUserName(tMenuCommand&) - prompt user-name entry (initial
   profile setup) (100 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_EnterUserName(tMenuCommand *command)

{
  byte bVar1;
  byte bVar2;
  tGlobalMenuDefs *ptVar3;
  tScreenUserName *ptVar4;
  char *data;
  tUserNameMenuItem *dlgThis;
  tOptionsMenu *m;
  
  ptVar3 = menuDefs;
  bVar1 = FEApp->fInputPlayer;
  bVar2 = FEApp->fInputPlayer;
  (menuDefs->menuItemUserName).fMaxStringLength = 7;
  ptVar4 = screenUserName;
  (ptVar3->menuItemUserName).fCurrentRow = 0;
  (ptVar3->menuItemUserName).fCurrentColumn = 0;
  (ptVar3->menuItemUserName).fPlayer = (ushort)bVar1;
  (ptVar3->menuItemUserName).fData = frontEnd.playerNameList[(uint)bVar2];
  ptVar4->callingMenu = &ptVar3->menuUserName;
  command->type = kMenu_Command_GoToMenu;
  command->nextMenu = (tMenu *)&(ptVar3->menuUserName)._base_tMenu;
  return;
}



/* ---- MenuExtended_GoToShowroom  [FEMENUDEFS.CPP:750-753] ---- */

/* Decoded Phase 83: MenuExtended_GoToShowroom(tMenuCommand&) - transition to player's garage 3D
   showroom view (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToShowroom(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  
  ptVar1 = menuDefs;
  command->type = kMenu_Command_GoToMenu;
  command->nextMenu = (tMenu *)&ptVar1->menuShowroom;
  SetState(screenCarSelect,5);
  return;
}



/* ---- MenuExtended_GoToDealerShowroom  [FEMENUDEFS.CPP:757-760] ---- */

/* Decoded Phase 83: MenuExtended_GoToDealerShowroom(tMenuCommand&) - transition to dealer 3D
   showroom view (64 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToDealerShowroom(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  
  ptVar1 = menuDefs;
  command->type = kMenu_Command_GoToMenu;
  command->nextMenu = (tMenu *)&ptVar1->menuShowroom;
  SetState(screenCarSelect,6);
  return;
}



/* ---- MenuExtended_SetHPSoloRace  [FEMENUDEFS.CPP:764-768] ---- */

/* Decoded Phase 83: MenuExtended_SetHPSoloRace(tMenuCommand&) - set raceType=HotPursuit Solo (44 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetHPSoloRace(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetHPSoloRace(tMenuCommand *command)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x01';
  frontEnd.oppNumber = '\0';
  (menuDefs->iteratorCar1).fCarListFilter = 0xb;
  return;
}



/* ---- MenuExtended_SetHPDuelRace  [FEMENUDEFS.CPP:772-776] ---- */

/* Decoded Phase 83: MenuExtended_SetHPDuelRace(tMenuCommand&) - set raceType=HotPursuit Duel (44 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetHPDuelRace(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetHPDuelRace(tMenuCommand *command)

{
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x01';
  frontEnd.oppNumber = '\x01';
  (menuDefs->iteratorCar1).fCarListFilter = 1;
  return;
}



/* ---- MenuExtended_SetHotPursuit  [FEMENUDEFS.CPP:780-788] ---- */

/* Decoded Phase 83: MenuExtended_SetHotPursuit(tMenuCommand&) - set raceType=HotPursuit (cops vs
   perps mode) (80 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetHotPursuit(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetHotPursuit(tMenuCommand *command)

{
  frontEnd.carListType = '\0';
  frontEnd.pinkSlipsTrackIndex = '\0';
  frontEnd.raceType = '\x01';
  if (frontEnd.gameMode == '\x01') {
    (menuDefs->iteratorCar1).fCarListFilter = 9;
  }
  else {
    (menuDefs->iteratorCar1).fCarListFilter = 1;
  }
  frontEnd.oppNumber = '\0';
  return;
}



/* ---- MenuExtended_SellCar  [FEMENUDEFS.CPP:792-814] ---- */

/* Decoded Phase 83: MenuExtended_SellCar(tMenuCommand&) - sell currently-selected garage car for
   cash credit (344 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SellCar(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

void MenuExtended_SellCar(tMenuCommand *command)

{
  bool bVar1;
  tFEApplication *ptVar2;
  short sVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  char *pcVar7;
  long money;
  tDialogMessageString *this_00;
  tDialogMessageString *dlgThis;
  tDialogYesNo *popUp;
  union {
    intptr align;
    byte bytes[sizeof(tDialogYesNo)];
  } popUpStorage;
  
  popUp = (tDialogYesNo *)popUpStorage.bytes;
  lVar6 = tournamentManager.fMoney;
  bVar1 = false;
  lVar4 = carManager.CalcUsedPrice((short)(byte)frontEnd.garageCar[0]);
  sVar3 = carManager.GetNumOwnedCars(0);
  if ((1 < sVar3) ||
     (lVar5 = carManager.CheapestCarStockPrice(),
      lVar5 <= nfs4_mips_addu_s32((int)lVar6,(int)lVar4))) {
    bVar1 = true;
  }
  ptVar2 = FEApp;
  if (bVar1) {
    tDialogYesNo_ctor(popUp);
    popUp->_base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0xa5);
    popUp->yesnowords[0] = 0x321;
    popUp->yesnowords[1] = 0x322;
    popUp->_base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    sVar3 = popUp->_base_tDialogInteractive.Run();
    if (sVar3 != 0) {
      lVar6 = carManager.SellCar((short)(byte)frontEnd.sellerCar,0);
      tournamentManager.fMoney = nfs4_mips_addu_s32(
          tournamentManager.fMoney,(int)lVar6);
      menuDefs->iteratorSellerCar.Decrement(kPlayerOne);
      menuDefs->iteratorSellerCar.Increment(kPlayerOne);
      AudioCmn_PlayFESFX(0x1a);
    }
    (((tScreen*)((tScreen *)popUp))->~tScreen(), (tScreen*)((tScreen *)popUp));
  }
  else {
    this_00 = &FEApp->messagePopup;
    pcVar7 = TextSys_Word(0xa9);
    (ptVar2->messagePopup).string = pcVar7;
    this_00->_base_tDialogBase.Display();
  }
  return;
}



/* ---- MenuExtended_BuyCar  [FEMENUDEFS.CPP:819-849] ---- */

/* Decoded Phase 83: MenuExtended_BuyCar(tMenuCommand&) - purchase highlighted dealer car; debits
   cash, adds to garage (340 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_BuyCar(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

void MenuExtended_BuyCar(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  short sVar2;
  tFEApplication *dlgThis;
  long lVar3;
  char *pcVar4;
  tDialogMessageString *this_00;
  tDialogMessageString *popUp;
  tCarInfo carInfo;
  tDialogYesNo yesNo;
  
  ptVar1 = FEApp;
  this_00 = &FEApp->messagePopup;
  GetStockCar(&carManager, (ushort)(byte)frontEnd.dealerCar,&carInfo);
  sVar2 = GetNumOwnedCars(&carManager, 0);
  if (sVar2 < 0x20) {
    if (carInfo.fPrices[0] <= tournamentManager.fMoney) {
      tDialogYesNo_ctor(&yesNo);
      yesNo._base_tDialogInteractive._base_tDialogMessageString.string =
           TextSys_Word(0xa4);
      yesNo.yesnowords[0] = 0x321;
      yesNo.yesnowords[1] = 0x322;
      yesNo._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
      sVar2 = Run(&yesNo._base_tDialogInteractive);
      if (sVar2 != 0) {
        lVar3 = PurchaseCar(&carManager, (short)carInfo.fCarID,
                           (ushort)(byte)frontEnd.carColors[0][carInfo.fCarID],0);
        tournamentManager.fMoney = tournamentManager.fMoney - lVar3;
        AudioCmn_PlayFESFX(0x1a);
      }
      (((tScreen*)((tScreen *)&yesNo))->~tScreen(), (tScreen*)((tScreen *)&yesNo));
      return;
    }
    AudioCmn_PlayFESFX(10);
    pcVar4 = TextSys_Word(0xa7);
    (ptVar1->messagePopup).string = pcVar4;
  }
  else {
    pcVar4 = TextSys_Word(0x4b);
    (ptVar1->messagePopup).string = pcVar4;
  }
  Display(&this_00->_base_tDialogBase);
  return;
}



/* ---- MenuExtended_PurchaseUpgrade  [FEMENUDEFS.CPP:854-877] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade(int upgradeIdx) - shared core purchase logic
   called by PurchaseUpgrade1/2/3 wrappers (320 B, 3 callers). Validates cash, debits, applies
   upgrade modifier to current car.
   
   [ghidra-meta] section: front.text */

void MenuExtended_PurchaseUpgrade(int upgradeNumber)

{
  tFEApplication *ptVar1;
  short sVar2;
  long lVar3;
  char *pcVar4;
  tDialogMessageString *dlgThis;
  int upgradeFlag;
  uint uVar5;
  tCarInfo carInfo;
  tDialogYesNo *popUp;
  union {
    intptr align;
    byte bytes[sizeof(tDialogYesNo)];
  } popUpStorage;
  
  popUp = (tDialogYesNo *)popUpStorage.bytes;
  uVar5 = 1U << ((u_int)upgradeNumber & 0x1fU);
  carManager.GetGarageCar((short)(byte)frontEnd.garageCar[0],carInfo,0);
  ptVar1 = FEApp;
  if ((carInfo.fUpgrades & uVar5) == 0) {
    if (tournamentManager.fMoney < carInfo.fPrices[upgradeNumber + 1]) {
      dlgThis = &FEApp->messagePopup;
      pcVar4 = TextSys_Word(0xa8);
      (ptVar1->messagePopup).string = pcVar4;
      dlgThis->_base_tDialogBase.Display();
    }
    else {
      tDialogYesNo_ctor(popUp);
      popUp->_base_tDialogInteractive._base_tDialogMessageString.string =
           TextSys_Word(0xa6);
      popUp->yesnowords[0] = 0x321;
      popUp->yesnowords[1] = 0x322;
      popUp->_base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
      sVar2 = popUp->_base_tDialogInteractive.Run();
      if (sVar2 != 0) {
        lVar3 = carManager.PurchaseUpgrade(
            (short)(byte)frontEnd.garageCar[0],(short)uVar5,0);
        tournamentManager.fMoney = nfs4_mips_subu_s32(
            tournamentManager.fMoney,(int)lVar3);
        AudioCmn_PlayFESFX(0x1a);
      }
      (((tScreen*)((tScreen *)popUp))->~tScreen(), (tScreen*)((tScreen *)popUp));
    }
  }
  return;
}



/* ---- MenuExtended_PurchaseUpgrade1  [FEMENUDEFS.CPP:883-884] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade1(tMenuCommand&) - tail-call wrapper for tier-1
   upgrade purchase (32 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_PurchaseUpgrade1(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_PurchaseUpgrade1(tMenuCommand *command)

{
  MenuExtended_PurchaseUpgrade(1);
  return;
}



/* ---- MenuExtended_PurchaseUpgrade2  [FEMENUDEFS.CPP:888-889] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade2(tMenuCommand&) - tail-call wrapper for tier-2
   upgrade purchase (32 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_PurchaseUpgrade2(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_PurchaseUpgrade2(tMenuCommand *command)

{
  MenuExtended_PurchaseUpgrade(2);
  return;
}



/* ---- MenuExtended_PurchaseUpgrade3  [FEMENUDEFS.CPP:893-894] ---- */

/* Decoded Phase 83: MenuExtended_PurchaseUpgrade3(tMenuCommand&) - tail-call wrapper for tier-3
   upgrade purchase (32 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_PurchaseUpgrade3(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_PurchaseUpgrade3(tMenuCommand *command)

{
  MenuExtended_PurchaseUpgrade(0);
  return;
}



/* ---- MenuExtended_SaveGame  [FEMENUDEFS.CPP:898-901] ---- */

/* Decoded Phase 83: MenuExtended_SaveGame(tMenuCommand&) - save game state to memcard (80 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SaveGame(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

void MenuExtended_SaveGame(tMenuCommand *command)

{
  if ((CURRENTLYUSINGMEMCARD == 0) &&
     ((((menuDefs->itemSaveGame)._base_tMenuItemGoToMenuButtonFade._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags ^ 1) & 1) != 0)) {
    GenericMenuSaveGame(0);
  }
  return;
}



/* ---- GenericMenuLoadGame  [FEMENUDEFS.CPP:922-941] ---- */

/* Decoded Phase 86: FE-GenericMenuLoadGame (148 B): execute generic load-game flow from
   menu.
   
   [ghidra-meta] section: front.text */

void GenericMenuLoadGame(int player)

{
  tFEApplication *this_00;
  tScreenMemcard *dlgThis;
  tDialogNoInputMessage *this_01;
  
  this_00 = FEApp;
  if (CURRENTLYUSINGMEMCARD == 0) {
    screenMemcard->message = 0x27d;
    Redraw(this_00);
    LoadGame((short)player,false,1);
    this_01 = &FEApp->NoInputMemCardDialog;
    screenMemcard->message = -1;
    Hide((tDialogBase *)this_01);
  }
  Hide((tDialogBase *)&FEApp->NoInputMemCardDialog);
  return;
}



/* ---- MenuExtended_LoadGame  [FEMENUDEFS.CPP:945-957] ---- */

/* Decoded Phase 83: MenuExtended_LoadGame(tMenuCommand&) - load save from memcard via Front_*;
   populate game state (152 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_LoadGame(int arg0)'.Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern.
    */

void MenuExtended_LoadGame(tMenuCommand *command)

{
  short sVar1;
  tDialogYesNo *dlgThis;
  tDialogYesNo AreYouSure;
  
  if (((menuDefs->itemLoadGame)._base_tMenuItemGoToMenuButtonFade._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags & 1) == 0) {
    tDialogYesNo_ctor(&AreYouSure);
    AreYouSure.yesnowords[0] = 0x321;
    AreYouSure.yesnowords[1] = 0x322;
    AreYouSure._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
    AreYouSure._base_tDialogInteractive._base_tDialogMessageString.string =
         TextSys_Word(0x2c0);
    sVar1 = Run(&AreYouSure._base_tDialogInteractive);
    if (sVar1 != 0) {
      GenericMenuLoadGame((int)screenMemcard->player);
    }
    (((tScreen*)((tScreen *)&AreYouSure))->~tScreen(), (tScreen*)((tScreen *)&AreYouSure));
  }
  return;
}



/* ---- MenuExtended_TierFinished  [FEMENUDEFS.CPP:960-976] ---- */

/* Decoded Phase 83: MenuExtended_TierFinished(tMenuCommand&) - tournament tier complete; advance to
   next tier (128 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_TierFinished(tMenuCommand *command)

{
  int iVar1;
  tMenu *ptVar2;
  tAwardInformation award;
  
  command->type = kMenu_Command_GoToMenuOneWay;
  GetAwardInformation(&tournamentManager,&award);
  if (award.fCompletedTier == 0) {
    iVar1 = AskTheUserToSaveTheGame();
    if (iVar1 == 0) {
      ptVar2 = &(menuDefs->menuMain)._base_tMenu;
    }
    else {
      ptVar2 = &(menuDefs->menuPostGameSave)._base_tMenu;
    }
  }
  else {
    ptVar2 = (tMenu *)&menuDefs->menuTierCompleteCongrats;
  }
  command->nextMenu = ptVar2;
  return;
}



/* ---- MenuExtended_DidUserWinBeTheCop  [FEMENUDEFS.CPP:1011-1036] ---- */

/* Decoded Phase 83: MenuExtended_DidUserWinBeTheCop() - check Behind-The-Cop win condition; returns
   winner status (284 B, 1 caller). Used by PostGameMenu to choose congrats vs failure animation.
   
   [ghidra-meta] section: front.text
   
   [Locals 2026-05-08] Locals renamed via deep-body inspection. Did-user-win-Be-The-Cop check.Returns 1 if user just unlocked a cop car after a successful BTC mission, 0 otherwise.GetStockCar(playerCar[0]) loads carInfo. Conditions: carClass=='\x07' (= cop class) AND
   raceType==1 (= BTC mode) AND gameMode!=1 (= not exhibition) AND numPerps<finalPerpArrests (=
   mission goal met). cop_car = GetCarFromID(gCarActivation[-0x13][country*5 + carID + 4]) looks up
   the unlock-target car. If !fAvailable: SetCarAvailable, store congratsCopCar+congratsCopCountry,
   return 1. activateCar/result are caller-side spills. */

void * MenuExtended_DidUserWinBeTheCop(void)

{
  tCarInfo *cop_car;
  tCarInfo *activateCar;
  byte result;
  void *pvVar1;
  tCarInfo carInfo;
  
  GetStockCar(&carManager, (ushort)(byte)frontEnd.playerCar[0],&carInfo);
  pvVar1 = (void *)0x0;
  if ((((carInfo.fCarClass == '\a') && (pvVar1 = (void *)0x0, frontEnd.raceType == '\x01')) &&
      (pvVar1 = (void *)0x0, frontEnd.gameMode != '\x01')) &&
     (GameSetup_gData.numPerps < GameSetup_gData.finalPerpArrests)) {
    cop_car = (tCarInfo *)(intptr)GetCarFromID(&carManager, (short)gCarActivation[carInfo.fCarID + -0x16]
                                [frontEnd.carCountry[0][carInfo.fCarID]]);
    pvVar1 = (void *)0x0;
    if (cop_car->fAvailable == '\0') {
      SetCarAvailable(&carManager, (int)cop_car->fCarID,true);
      frontEnd.congratsCopCar = cop_car->fCarID;
      frontEnd.congratsCopCountry = frontEnd.carCountry[0][carInfo.fCarID];
      pvVar1 = (void *)0x1;
    }
  }
  return pvVar1;
}



/* ---- MenuExtended_PostGameMenu  [FEMENUDEFS.CPP:1040-1082] ---- */

/* Decoded Phase 83: MenuExtended_PostGameMenu(tMenuCommand&) - show post-game menu(continue/save/restart/quit) (256 B)
   
   [ghidra-meta] section: front.text */

extern "C" void MenuExtended_PostGameMenu(tMenuCommand *command)

{
  short sVar1;
  void *pvVar2;
  tMenu *ptVar3;
  tScreenTournamentStandings *dlgThis;
  tScreenTournamentStandings *ptVar4;
  
  StatChk_ClearNewRecords();
  command->type = kMenu_Command_GoToMenuOneWay;
  if (frontEnd.raceType == '\x02') {
    sVar1 = IsTournamentFinished(&tournamentManager);
    if (sVar1 == 0) {
      command->nextMenu = (tMenu *)&(menuDefs->menuTournamentStandings)._base_tMenu;
      ptVar4 = &screenTournamentStandings3item->_base_tScreenTournamentStandings;
    }
    else {
      command->nextMenu = (tMenu *)&(menuDefs->menuTournamentFinished)._base_tMenu;
      ptVar4 = screenTournamentStandings;
    }
    ptVar4->fDrawMoney = 1;
    return;
  }
  if ((byte)frontEnd.raceType < 3) {
    if ((frontEnd.raceType == '\x01') &&
       (pvVar2 = MenuExtended_DidUserWinBeTheCop(), pvVar2 != (void *)0x0)) {
      ptVar3 = (tMenu *)&menuDefs->menuBeTheCopCongrats;
      goto MXPostGameMenu_setNextMenu;
    }
  }
  else if (frontEnd.raceType == '\x06') {
    ptVar3 = &(menuDefs->menuPinkSlipStandings)._base_tMenu;
    goto MXPostGameMenu_setNextMenu;
  }
  ptVar3 = &(menuDefs->menuMain)._base_tMenu;
MXPostGameMenu_setNextMenu:
  command->nextMenu = ptVar3;
  return;
}



/* ---- MenuExtended_FinishedPlayer1GetName  [FEMENUDEFS.CPP:1090-1120] ---- */

/* Decoded Phase 83: MenuExtended_FinishedPlayer1GetName(tMenuCommand&) - after race, prompt P1 for
   name entry (high score etc) (272 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_FinishedPlayer1GetName(tMenuCommand *command)

{
  tFEApplication *ptVar1;
  tGlobalMenuDefs *ptVar2;
  tScreenUserName *ptVar3;
  short sVar4;
  void *pvVar5;
  tUserNameMenuItem *dlgThis;
  tOptionsMenu *m;
  Car_tStats *dummyCars;
  short nBestCarIndex;
  
  ptVar1 = FEApp;
  command->type = kMenu_Command_GoToMenuOneWay;
  ptVar2 = menuDefs;
  if ((ptVar1->needName[1] == 0) || (ptVar1->gotName[1] != 0)) {
    pvVar5 = (void *)(intptr)StatChk_IsRecordLapTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars,&nBestCarIndex);
    if (pvVar5 != (void *)0x0) {
      StatChk_SaveRecordLapTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars,nBestCarIndex);
    }
    sVar4 = StatChk_IsTopTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars);
    if (sVar4 != 0) {
      StatChk_SaveTopTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars);
    }
    command->nextMenu = (tMenu *)&(menuDefs->menuPostGameTrackRecords)._base_tMenu;
  }
  else {
    (menuDefs->menuItemUserName2).fPlayer = 1;
    (ptVar2->menuItemUserName2).fData = frontEnd.playerNameList[4];
    (ptVar2->menuItemUserName2).fMaxStringLength = 7;
    ptVar3 = screenUserName;
    (ptVar2->menuItemUserName2).fCurrentRow = 0;
    (ptVar2->menuItemUserName2).fCurrentColumn = 0;
    ptVar3->callingMenu = &ptVar2->menuPostGamePlayer2Name;
    command->nextMenu = (tMenu *)&(ptVar2->menuPostGamePlayer2Name)._base_tMenu;
  }
  return;
}



/* ---- MenuExtended_FinishedPlayer2GetName  [FEMENUDEFS.CPP:1125-1142] ---- */

/* Decoded Phase 83: MenuExtended_FinishedPlayer2GetName(tMenuCommand&) - after race, prompt P2 for
   name entry (160 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_FinishedPlayer2GetName(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  short sVar2;
  void *pvVar3;
  Car_tStats *dummyCars;
  short nBestCarIndex;
  
  pvVar3 = (void *)(intptr)StatChk_IsRecordLapTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars,&nBestCarIndex);
  if (pvVar3 != (void *)0x0) {
    StatChk_SaveRecordLapTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars,nBestCarIndex);
  }
  sVar2 = StatChk_IsTopTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars);
  if (sVar2 != 0) {
    StatChk_SaveTopTime(Cars_gNewCarStatsList,(short)Cars_gNumRaceCars);
  }
  ptVar1 = menuDefs;
  command->type = kMenu_Command_GoToMenuOneWay;
  command->nextMenu = (tMenu *)&(ptVar1->menuPostGameTrackRecords)._base_tMenu;
  return;
}



/* ---- MenuExtended_SetPinkSlips  [FEMENUDEFS.CPP:1146-1159] ---- */

/* Decoded Phase 83: MenuExtended_SetPinkSlips(tMenuCommand&) - set raceType=PinkSlips and prepare
   car-select (192 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name + (body or
   100%-caller-consensus) agree. Generic param names; types int/void* default - refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetPinkSlips(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetPinkSlips(tMenuCommand *command)

{
  int iVar1;
  short i;
  int iVar2;
  
  SwapBackground(screenMain,-1);
  iVar2 = 0;
  frontEnd.raceType = '\x06';
  frontEnd.gameMode = '\x01';
  frontEnd.oppNumber = '\0';
  frontEnd.pinkSlipsForfeit = -1;
  frontEnd.pinkSlipsTrackIndex = '\0';
  iVar1 = 0;
  do {
    frontEnd.pinkSlipsWins[iVar1 >> 0x10] = '\0';
    iVar2 = iVar2 + 1;
    iVar1 = iVar2 * 0x10000;
  } while (iVar2 * 0x10000 >> 0x10 < 2);
  iVar1 = 0;
  do {
    frontEnd.pinkSlipsWinner[iVar1] = -1;
    iVar1 = iVar1 + 1;
  } while (iVar1 * 0x10000 >> 0x10 < 5);
  return;
}



/* ---- MenuExtended_AwardPinkSlipsCar  [FEMENUDEFS.CPP:1163-1218] ---- */

/* Decoded Phase 83: MenuExtended_AwardPinkSlipsCar(tMenuCommand&) - award winner the loser's car
   after pinkslips race (552 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_AwardPinkSlipsCar(tMenuCommand *command)

{
  short playerNum;
  char *pcVar4;
  char *pcVar5;
  int player;
  char string [80];
  tCarInfo carInfo;
  tDialogYesNo *retryCancelDialog;
  union {
    intptr align;
    byte bytes[sizeof(tDialogYesNo)];
  } retryCancelDialogStorage;
  
  retryCancelDialog = (tDialogYesNo *)retryCancelDialogStorage.bytes;
  tDialogYesNo_ctor(retryCancelDialog);
  retryCancelDialog->yesnowords[0] = 0x291;
  retryCancelDialog->yesnowords[1] = 0x292;
  retryCancelDialog->_base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 1;
  playerNum = screenPinkSlipCongrats->fWinner;
  player = (int)playerNum;
  pcVar4 = TextSys_Word(0x29a);
  pcVar5 = PlayerName(player);
  sprintf(string,pcVar4,pcVar5,player + 1);
  FEApp->NoInputMemCardDialog._base_tDialogMessageString.string = string;
  FEApp->NoInputMemCardDialog._base_tDialogMessageString._base_tDialogBase.Display();
  while ((FEApp->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFullyOpen != 1) {
    FEApp->Redraw();
  }
  FEApp->Redraw();
  Init_Memcard(false,1);
  carManager.GetPinkSlipsCar((short)(byte)frontEnd.pinkSlipsCar[1 - player],carInfo,
                             (short)nfs4_mips_sign_extend((u_int)(1 - player),16));
  carManager.AddToPinkSlipsList((short)carInfo.fCarID,(short)(byte)carInfo.fColor,playerNum);
  carManager.AddUpgradesToPinkSlipsList((short)(byte)frontEnd.pinkSlipsCar[player],
                                       (short)(byte)carInfo.fUpgrades,playerNum);
  SavePinkSlipsCarsWithErrorDialogs(playerNum,2,-1);
  FEApp->NoInputMemCardDialog._base_tDialogMessageString._base_tDialogBase.Hide();
  command->type = kMenu_Command_GoToMenuOneWay;
  command->nextMenu = (tMenu *)&(menuDefs->menuMain)._base_tMenu;
  pcVar4 = TextSys_Word(0x274);
  FEApp->NoInputMemCardDialog._base_tDialogMessageString.string = pcVar4;
  FEApp->NoInputMemCardDialog._base_tDialogMessageString._base_tDialogBase.Display();
  while ((FEApp->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFullyOpen != 1) {
    FEApp->Redraw();
  }
  FEApp->Redraw();
  GenericMenuLoadGame(0);
  DeInit_Memcard();
  FEApp->NoInputMemCardDialog._base_tDialogMessageString._base_tDialogBase.Hide();
  command->type = kMenu_Command_GoToMenuOneWay;
  command->nextMenu = (tMenu *)&(menuDefs->menuMain)._base_tMenu;
  (((tScreen*)((tScreen *)retryCancelDialog))->~tScreen(), (tScreen*)((tScreen *)retryCancelDialog));
  return;
}



/* ---- MenuExtended_GoToGarage  [FEMENUDEFS.CPP:1222-1231] ---- */

/* Decoded Phase 83: MenuExtended_GoToGarage(tMenuCommand&) - transition to garage screen (168 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_GoToGarage(tMenuCommand *command)

{
  tMenu *ptVar1;
  tListIteratorCar *dlgThis;
  tListIteratorCar *this_00;
  
  frontEnd.carListType = '\x01';
  this_00 = &menuDefs->iteratorGarageCar;
  (menuDefs->iteratorGarageCar).fCarListFilter = 0x40;
  Decrement(this_00,kPlayerBoth);
  menuDefs->iteratorGarageCar.Increment(kPlayerBoth);
  command->type = kMenu_Command_GoToMenu;
  if (tournamentManager.fCurrentTrack == 0) {
    ptVar1 = &(menuDefs->menuCarGarage)._base_tMenu;
  }
  else {
    ptVar1 = &(menuDefs->menuPostCarGarage)._base_tMenu;
  }
  command->nextMenu = ptVar1;
  SetState(screenCarSelect,1);
  return;
}



/* ---- MenuExtended_GoToTournTrophyRoom  [FEMENUDEFS.CPP:1235-1236] ---- */

/* Decoded Phase 83: MenuExtended_GoToTournTrophyRoom(tMenuCommand&) - transition to tournament
   trophy room (12 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int
   MenuExtended_GoToTournTrophyRoom(int arg0)'. Fixed via m2c body (arg0 = struct
   deref) + PCSX runtime (a0 = consistent ptr) + sibling pattern. */

void MenuExtended_GoToTournTrophyRoom(tMenuCommand *command)

{
  frontEnd.tier = '\0';
  return;
}



/* ---- MenuExtended_GoToSETrophyRoom  [FEMENUDEFS.CPP:1240-1241] ---- */

/* Decoded Phase 83: MenuExtended_GoToSETrophyRoom(tMenuCommand&) - transition to special-event
   trophy room (16 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_GoToSETrophyRoom(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_GoToSETrophyRoom(tMenuCommand *command)

{
  frontEnd.tier = '\x01';
  return;
}



/* ---- MenuExtended_SetBeginner  [FEMENUDEFS.CPP:1245-1246] ---- */

/* Decoded Phase 83: MenuExtended_SetBeginner(tMenuCommand&) - set difficulty=Beginner (12 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetBeginner(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetBeginner(tMenuCommand *command)

{
  frontEnd.skillLevel = '\0';
  return;
}



/* ---- MenuExtended_SetIntermediate  [FEMENUDEFS.CPP:1250-1251] ---- */

/* Decoded Phase 83: MenuExtended_SetIntermediate(tMenuCommand&) - set difficulty=Intermediate (16
   B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetIntermediate(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetIntermediate(tMenuCommand *command)

{
  frontEnd.skillLevel = '\x01';
  return;
}



/* ---- MenuExtended_SetExpert  [FEMENUDEFS.CPP:1255-1256] ---- */

/* Decoded Phase 83: MenuExtended_SetExpert(tMenuCommand&) - set difficulty=Expert (16 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text
   
   [Sig-callgraph 2026-05-08] PRIOR-SESSION ARG LOSS: 0->1. Mangled-name authority + vtable-dispatch
   context (body/caller-prep masked by indirect-call pattern). Generic param names; refine later.
   
   [Sig-fix 2026-05-11 PCSX-runtime R4] Was 'int MenuExtended_SetExpert(int
   arg0)'. Fixed via m2c body (arg0 = struct deref) + PCSX runtime (a0 = consistent ptr) + sibling
   pattern. */

void MenuExtended_SetExpert(tMenuCommand *command)

{
  frontEnd.skillLevel = '\x02';
  return;
}



/* ---- MenuExtended_ExitTourney  [FEMENUDEFS.CPP:1260-1271] ---- */

/* Decoded Phase 83: MenuExtended_ExitTourney(tMenuCommand&) - abandon current tournament, return to
   main menu (144 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_ExitTourney(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  short sVar2;
  tDialogYesNo *dlgThis;
  tDialogYesNo AreYouSure;
  
  tDialogYesNo_ctor(&AreYouSure);
  AreYouSure.yesnowords[0] = 0x321;
  AreYouSure.yesnowords[1] = 0x322;
  AreYouSure._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
  AreYouSure._base_tDialogInteractive._base_tDialogMessageString.string =
       TextSys_Word(0x9d);
  sVar2 = Run(&AreYouSure._base_tDialogInteractive);
  ptVar1 = menuDefs;
  if (sVar2 == 0) {
    command->type = kMenu_Command_None;
  }
  else {
    command->type = kMenu_Command_GoToMenuOneWay;
    command->nextMenu = (tMenu *)&(ptVar1->menuMain)._base_tMenu;
  }
  (((tScreen*)((tScreen *)&AreYouSure))->~tScreen(), (tScreen*)((tScreen *)&AreYouSure));
  return;
}



/* ---- MenuExtended_ExitPinkSlipsEarly  [FEMENUDEFS.CPP:1274-1300] ---- */

/* Decoded Phase 83: MenuExtended_ExitPinkSlipsEarly(tMenuCommand&) - allow user to back out of
   pinkslips before commit (304 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_ExitPinkSlipsEarly(tMenuCommand *command)

{
  bool bVar1;
  tGlobalMenuDefs *ptVar2;
  short sVar3;
  char *fmt;
  char *pcVar4;
  tDialogYesNo *dlgThis;
  int iVar5;
  int player;
  int player_00;
  tDialogYesNo AreYouSure;
  char string [80];
  
  tDialogYesNo_ctor(&AreYouSure);
  AreYouSure.yesnowords[0] = 0x321;
  AreYouSure.yesnowords[1] = 0x322;
  AreYouSure._base_tDialogInteractive._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
  AreYouSure._base_tDialogInteractive._base_tDialogMessageString.string =
       TextSys_Word(0x9d);
  sVar3 = Run(&AreYouSure._base_tDialogInteractive);
  if (sVar3 != 0) {
    Init_Memcard(false,1);
    bVar1 = true;
    player_00 = 0;
    while (bVar1) {
      fmt = TextSys_Word(0x297);
      pcVar4 = PlayerName(player_00);
      iVar5 = player_00 + 1;
      sprintf(string,fmt,pcVar4,iVar5);
      (FEApp->NoInputMemCardDialog)._base_tDialogMessageString.string = string;
      SavePinkSlipsCarsWithErrorDialogs((short)player_00,1,-1);
      bVar1 = iVar5 < 2;
      player_00 = iVar5;
    }
    DeInit_Memcard();
    Hide((tDialogBase *)&FEApp->NoInputMemCardDialog);
    ptVar2 = menuDefs;
    command->type = kMenu_Command_GoToMenuOneWay;
    command->nextMenu = (tMenu *)&(ptVar2->menuMain)._base_tMenu;
    frontEnd.raceType = '\0';
  }
  (((tScreen*)((tScreen *)&AreYouSure))->~tScreen(), (tScreen*)((tScreen *)&AreYouSure));
  return;
}



/* ---- MenuExtended_PinkSlipsContinue  [FEMENUDEFS.CPP:1304-1315] ---- */

/* Decoded Phase 83: MenuExtended_PinkSlipsContinue(tMenuCommand&) - after pinkslips win, continue
   to next race (108 B)
   [zero direct xref] Menu command callback - registered via tMenuCommand fn pointer
   
   [ghidra-meta] section: front.text */

void MenuExtended_PinkSlipsContinue(tMenuCommand *command)

{
  tGlobalMenuDefs *ptVar1;
  byte bVar2;
  
  ptVar1 = menuDefs;
  bVar2 = ((byte)frontEnd.pinkSlipsNumTracks >> 1) + 1;
  if (((byte)frontEnd.pinkSlipsWins[0] < bVar2) && ((byte)frontEnd.pinkSlipsWins[1] < bVar2)) {
    frontEnd.pinkSlipsTrackIndex = frontEnd.pinkSlipsTrackIndex + '\x01';
    command->type = kMenu_Command_StartRace;
    return;
  }
  command->type = kMenu_Command_GoToMenuOneWay;
  command->nextMenu = (tMenu *)&ptVar1->menuPinkSlipCongrats;
  return;
}



/* ---- tGlobalMenuDefs::ctor body  [FEMENUDEFS.CPP:1353-2200] ---- */

void tGlobalMenuDefs::ConstructBody()

{
  tFEApplication *ptVar1;
  tScreenTrophyRoom *screenHandler;
  tScreenTrackRecords *ptVar2;
  tScreenDisplay *screenHandler_00;
  tScreenMemcard *ptVar3;
  tMenu *child;
  char *pcVar4;
  tListIteratorIndexed *ptVar5;
  tListIteratorCar *ptVar6;
  tListIterator *ptVar7;
  char *in_v1;
  uint uVar8;
  tMenuNFS4 *ptVar9;
  tMenuNFS4 *this_00;
  tMenuItemNFS4LeftRightChoice *ptVar10;
  tListIteratorCar *this_01;
  tMenuOptions *this_02;
  tListIteratorIndexed *this_03;
  tMenuItemOptionsLeftRightChoice *this_04;
  tMenuItemOptionsLeftRightChoice *this_05;
  tMenuItemOptionsLeftRightChoice *this_06;
  tInsideBoxControllerLeftRightSlider *this_07;
  tInsideBoxTwoWaySlider *this_08;
  tMenuItemNFS4LeftRightChoice *ptVar11;
  tMenuOptions *ptVar12;
  tListIteratorCarColor *this_09;
  tMenuOptions *this_10;
  tMenuItemOptionsLeftRightChoice *this_11;
  tInsideBoxControllerLeftRightSlider *firstItem;
  tListIteratorTrack *this_12;
  tMenuItemNFS4LeftRightChoice *ptVar13;
  tListIteratorIndexed *this_13;
  tMenuItemOptionsLeftRightChoice *this_14;
  tInsideBoxTwoWaySlider *this_15;
  tMenuNFS4 *this_16;
  tMenuItemGoToMenuNFS4Button *ptVar14;
  tMenuItemGoToMenuNFS4Button *ptVar15;
  tMenuItemNFS4LeftRightChoice *this_17;
  tMenuItemOptionsLeftRightChoice *this_18;
  tMemoryCardMenuItem *this_19;
  
  new ((void*)(&this->itemMainOnePlayerRace)) tMenuItemGoToMenuNFS4Button(0x5b, &(this->menuOnePlayer)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetOnePlayer), 0x1e, 10);
  new ((void*)(&this->itemMainTwoPlayerRace)) tMenuItemGoToMenuNFS4Button(0x5c, &(this->menuTwoPlayer)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetTwoPlayer), 0x28, 10);
  new ((void*)(&this->itemMainTrophyRoom)) tMenuItemGoToMenuNFS4Button(0x5e, &(this->menuTrophyRoomSelect)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0x32, 10);
  new ((void*)(&this->itemMainOptions)) tMenuItemGoToMenuNFS4Button(0x5d, &(this->menuOptions)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0x3c, 10);
  tMenuNFS4_ctor(&this->menuMain,0x1014,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,(void *)0x0,
             0xb4,(tMenuItem *)this,&this->itemMainTwoPlayerRace,&this->itemMainOptions,
             &this->itemMainTrophyRoom,0);
  new ((void*)(&this->itemTournTrophyRoom)) tMenuItemGoToMenuNFS4Button(99, (tMenu *)&this->menuTrophyRoom, (void (*)(tMenuCommand &))(MenuExtended_GoToTournTrophyRoom), 0x32, 10);
  new ((void*)(&this->itemSETrophyRoom)) tMenuItemGoToMenuNFS4Button(0x69, (tMenu *)&this->menuTrophyRoom, (void (*)(tMenuCommand &))(MenuExtended_GoToSETrophyRoom), 0x32, 10);
  tMenuNFS4_ctor(&this->menuTrophyRoomSelect,0x1014,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0x5f,(tMenuItem *)&this->itemTournTrophyRoom,&this->itemSETrophyRoom,0);
  new ((void*)(&this->menuTrophyInfo)) tMenuBlank(0x4000, &screenTrophyInfo->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1);
  ptVar9 = &this->menuSingleTrackSelect;
  new ((void*)(&this->itemSkillBeginner)) tMenuItemGoToMenuNFS4Button(0xa1, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetBeginner), 0x8c, 10)
  ;
  new ((void*)(&this->itemSkillIntermediate)) tMenuItemGoToMenuNFS4Button(0xa2, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetIntermediate), 0x96, 10);
  new ((void*)(&this->itemSkillExpert)) tMenuItemGoToMenuNFS4Button(0xa3, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetExpert), 0xa0, 10);
  this_16 = &this->menuSkillLevel;
  tMenuNFS4_ctor(this_16,0x1004,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,(void *)0x0,0xb7,
             (tMenuItem *)&this->itemSkillBeginner,&this->itemSkillIntermediate,
             &this->itemSkillExpert,0);
  this_00 = &this->menuTestDriveTrackSelect;
  new ((void*)(&this->itemOnePlayerTestDrive)) tMenuItemGoToMenuNFS4Button(0x60, &this_00->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetTestDrive), 0xf0, 10);
  new ((void*)(&this->itemOnePlayerSingleRace)) tMenuItemGoToMenuNFS4Button(0x72, &(this->menuSingleRace)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetSingleRace), 0x46, 10);
  new ((void*)(&this->itemOnePlayerPursuit)) tMenuItemGoToMenuNFS4Button(0x71, &(this->menuHotPursuit)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetHotPursuit), 0x50, 10);
  new ((void*)(&this->itemOnePlayerTournament)) tMenuItemGoToMenuNFS4Button(99, &(this->menuTournament)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetTournament), 0x5a, 10);
  new ((void*)(&this->itemOnePlayerSpecialEvents)) tMenuItemGoToMenuNFS4Button(0x69, &(this->menuSpecialEvent)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetSpecialEvent), 100, 10);
  tMenuNFS4_ctor(&this->menuOnePlayer,0x1004,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0xb5,(tMenuItem *)&this->itemOnePlayerTestDrive,
             &this->itemOnePlayerSingleRace,&this->itemOnePlayerPursuit,
             &this->itemOnePlayerTournament,&this->itemOnePlayerSpecialEvents,0);
  new ((void*)(&this->itemSingleRaceSolo)) tMenuItemGoToMenuNFS4Button(0x6c, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetSoloRace), 0x6e, 10)
  ;
  new ((void*)(&this->itemSingleRaceDuel)) tMenuItemGoToMenuNFS4Button(0x6d, &this_16->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetDuelRace), 0x78, 10)
  ;
  new ((void*)(&this->itemSingleRaceFullGrid)) tMenuItemGoToMenuNFS4Button(0x6f, &this_16->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetFullGrid), 0x82, 10)
  ;
  tMenuNFS4_ctor(&this->menuSingleRace,0x1004,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0xb6,(tMenuItem *)&this->itemSingleRaceSolo,&this->itemSingleRaceDuel,
             &this->itemSingleRaceFullGrid,0);
  new ((void*)(&this->itemHotPursuitSolo)) tMenuItemGoToMenuNFS4Button(0x6c, &this_16->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetHPSoloRace), 0x6e, 10);
  new ((void*)(&this->itemHotPursuitDuel)) tMenuItemGoToMenuNFS4Button(0x6d, &this_16->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetHPDuelRace), 0x78, 10);
  pcVar4 = (char *)tMenuNFS4_ctor(&this->menuHotPursuit,0x1004,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
                      (void *)0x0,0xb6,(tMenuItem *)&this->itemHotPursuitSolo,
                      &this->itemHotPursuitDuel,0);
  new ((void*)(&this->iteratorTournament)) tListIteratorTournament(pcVar4, &tournamentManager);
  new ((void*)(&this->itemTournamentContinue)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToTournTrackInfo), 0x22, 10);
  new ((void*)(&this->itemTournamentSelect)) tMenuItemNFS4LeftRightChoice(0x94, &(this->iteratorTournament)._base_tListIterator, 0x2c, 10);
  pcVar4 = (char *)tMenuNFS4_ctor(&this->menuTournament,0x1000,&screenTournSelect->_base_tScreen,(tMenu *)0x0,
                      (tMenu *)0x0,
                      MenuExtended_GoToTournTrackInfo,0x65,
                      (tMenuItem *)&this->itemTournamentContinue,&this->itemTournamentSelect,0);
  new ((void*)(&this->iteratorSpecialEvent)) tListIteratorTournament(pcVar4, &tournamentManager);
  new ((void*)(&this->itemSpecialEventContinue)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToSpecialEventTrackInfo), 0x22, 10);
  new ((void*)(&this->itemSpecialEventSelect)) tMenuItemNFS4LeftRightChoice(0x69, &(this->iteratorSpecialEvent)._base_tListIterator, 0x36, 10)
  ;
  tMenuNFS4_ctor(&this->menuSpecialEvent,0x1000,&screenTournSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             MenuExtended_GoToSpecialEventTrackInfo,100,
             (tMenuItem *)&this->itemSpecialEventContinue,&this->itemSpecialEventSelect,0);
  new ((void*)(&this->itemTwoPlayerTestDrive)) tMenuItemGoToMenuNFS4Button(0x60, &this_00->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetTestDrive), 0xf0, 10);
  new ((void*)(&this->itemTwoPlayerDuel)) tMenuItemGoToMenuNFS4Button(0x72, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToTwoPlayerSingleRace), 0x46, 10);
  new ((void*)(&this->itemTwoPlayerHotPursuit)) tMenuItemGoToMenuNFS4Button(0x71, &this_16->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetHotPursuit), 0x50, 10);
  new ((void*)(&this->itemTwoPlayerPinkSlips)) tMenuItemGoToMenuNFS4Button(0x6a, &(this->menuPinkSlipSelect)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_SetPinkSlips), 0xaa, 10);
  tMenuNFS4_ctor(&this->menuTwoPlayer,0x1004,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0xb5,(tMenuItem *)&this->itemTwoPlayerTestDrive,&this->itemTwoPlayerDuel
             ,&this->itemTwoPlayerHotPursuit,&this->itemTwoPlayerPinkSlips,0);
  new ((void*)(&this->itemBestOfOne)) tMenuItemGoToMenuNFS4Button(0xc0, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_GoToBestOfOne), 0xaa, 10);
  new ((void*)(&this->itemBestOfThree)) tMenuItemGoToMenuNFS4Button(0xc1, &(this->menuPinkSlipsBestOfThree)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_GoToBestOfThree), 0xaa, 10);
  new ((void*)(&this->itemBestOfFive)) tMenuItemGoToMenuNFS4Button(0xc2, &(this->menuPinkSlipsBestOfFive)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_GoToBestOfFive), 0xaa, 10);
  tMenuNFS4_ctor(&this->menuPinkSlipSelect,0x1000,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0xb6,(tMenuItem *)&this->itemBestOfOne,&this->itemBestOfThree,
             &this->itemBestOfFive,0);
  ptVar14 = &this->itemPinkSlipsContinue;
  new ((void*)(ptVar14)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToCarSelect), 0x24, 10);
  ptVar11 = &this->itemTrack1;
  this_12 = &this->iteratorTrack;
  new ((void*)(ptVar11)) tMenuItemNFS4LeftRightChoice(0xc3, (tListIterator *)this_12, 0x2e, 10);
  ptVar10 = &this->itemTrack2;
  new ((void*)(ptVar10)) tMenuItemNFS4LeftRightChoice(0xc4, (tListIterator *)this_12, 0x2e, 10);
  ptVar13 = &this->itemTrack3;
  new ((void*)(ptVar13)) tMenuItemNFS4LeftRightChoice(0xc5, (tListIterator *)this_12, 0x2e, 10);
  new ((void*)(&this->itemTrack4)) tMenuItemNFS4LeftRightChoice(0xc6, (tListIterator *)this_12, 0x2e, 10);
  new ((void*)(&this->itemTrack5)) tMenuItemNFS4LeftRightChoice(199, (tListIterator *)this_12, 0x2e, 10);
  ptVar12 = &this->menuTrackOptions;
  tMenuNFS4_ctor(&this->menuPinkSlipsBestOfThree,0x1400,&screenPinkSlips->_base_tScreen,(tMenu *)0x0,
             (tMenu *)ptVar12,
             MenuExtended_GoToCarSelect,0xbe,
             (tMenuItem *)ptVar14,ptVar11,ptVar10,ptVar13,0);
  pcVar4 = (char *)tMenuNFS4_ctor(&this->menuPinkSlipsBestOfFive,0x1400,&screenPinkSlips->_base_tScreen,(tMenu *)0x0,
                      (tMenu *)ptVar12,
                      MenuExtended_GoToCarSelect,0xbf,(tMenuItem *)ptVar14,ptVar11
                      ,ptVar10,ptVar13,&this->itemTrack4,&this->itemTrack5,0);
  new ((void*)(this_12)) tListIteratorTrack(frontEnd.track, &frontEnd.pinkSlipsTrackIndex, &trackManager);
  ptVar15 = &this->itemTrackContinue;
  new ((void*)(ptVar15)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToCarSelect), 0x1c, 10);
  ptVar10 = &this->itemTrack;
  new ((void*)(ptVar10)) tMenuItemNFS4LeftRightChoice(0x93, (tListIterator *)this_12, 0x26, 10);
  ptVar14 = &this->itemTrackRecords;
  new ((void*)(ptVar14)) tMenuItemGoToMenuNFS4Button(0xd4, &(this->menuTrackRecords)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0x3a, 10);
  tMenuNFS4_ctor(ptVar9,0x1600,&screenTrackSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)ptVar12,
             MenuExtended_GoToCarSelect,200,
             (tMenuItem *)ptVar15,ptVar10,ptVar14,0);
  tMenuNFS4_ctor(this_00,0x1600,&screenTrackSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             MenuExtended_GoToCarSelect,200,
             (tMenuItem *)ptVar15,ptVar10,ptVar14,0);
  new ((void*)(&this->iteratorLaps)) tListIteratorIndexed(SelectListNormal, frontEnd.lapind, &frontEnd.pinkSlipsTrackIndex);
  new ((void*)(&this->iteratorTrackDirection)) tListIteratorIndexed(SelectListTrackDirection, frontEnd.trackdirection, &frontEnd.pinkSlipsTrackIndex);
  new ((void*)(&this->iteratorTrackMirrored)) tListIteratorIndexed(SelectListOffOn, frontEnd.trackmirrored, &frontEnd.pinkSlipsTrackIndex);
  new ((void*)(&this->iteratorTimeOfDay)) tListIteratorIndexed(SelectListOffOn, frontEnd.timeOfDay, &frontEnd.pinkSlipsTrackIndex);
  new ((void*)(&this->iteratorWeather)) tListIteratorIndexed(SelectListOffOn, frontEnd.weather, &frontEnd.pinkSlipsTrackIndex);
  ptVar5 = new ((void*)(&this->iteratorTraffic)) tListIteratorIndexed(SelectListOffOn, frontEnd.traffic, &frontEnd.pinkSlipsTrackIndex);
  new ((void*)(&ptVar5->_base_tListIterator)) tListIterator(SelectListOffOn, &frontEnd.localSpeech);
  new ((void*)(&(this->itemLaps)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xca, &(this->iteratorLaps)._base_tListIterator);
  *(void **)&((this->itemLaps)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&(this->itemTrackDirection)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xcc, &(this->iteratorTrackDirection)._base_tListIterator);
  *(void **)&((this->itemTrackDirection)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&(this->itemTrackMirrored)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xcd, &(this->iteratorTrackMirrored)._base_tListIterator);
  *(void **)&((this->itemTrackMirrored)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsTwoItemChoice_vtable;
  (this->itemTrackMirrored).fOnOffFade = 0x80;
  new ((void*)(&(this->itemTimeOfDay)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xce, &(this->iteratorTimeOfDay)._base_tListIterator);
  *(void **)&((this->itemTimeOfDay)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsTwoItemChoice_vtable;
  (this->itemTimeOfDay).fOnOffFade = 0x80;
  new ((void*)(&(this->itemWeather)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xcf, &(this->iteratorWeather)._base_tListIterator);
  *(void **)&((this->itemWeather)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsTwoItemChoice_vtable;
  (this->itemWeather).fOnOffFade = 0x80;
  new ((void*)(&(this->itemTraffic)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xd0, &(this->iteratorTraffic)._base_tListIterator);
  *(void **)&((this->itemTraffic)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsTwoItemChoice_vtable;
  (this->itemTraffic).fOnOffFade = 0x80;
  new ((void*)(&(this->itemLocalSpeech)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0xd2, &this->iteratorLocalSpeech);
  *(void **)&((this->itemLocalSpeech)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsTwoItemChoice_vtable;
  (this->itemLocalSpeech).fOnOffFade = 0x80;
  new ((void*)(ptVar12)) tMenuOptions(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xb9, -1, (tMenuItem *)&this->itemLaps, &this->itemTrackDirection, &this->itemTrackMirrored, &this->itemTimeOfDay, &this->itemWeather, &this->itemTraffic, &this->itemLocalSpeech, 0);
  new ((void*)(&(this->menuTrackRecordsItem)._base_tMenuItemGoToMenuNFS4Button)) tMenuItemGoToMenuNFS4Button(0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1, -1);
  ptVar2 = screenTrackRecords;
  *(void **)&((this->menuTrackRecordsItem)._base_tMenuItemGoToMenuNFS4Button._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)&tBlankMenuItemGoToMenuNFS4Button_vtable;
  new ((void*)(&this->menuTrackRecords)) tOptionsMenu(0x1000, &ptVar2->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xd4, 1, 10, (tMenuItem *)0x0);
  new ((void*)(&this->itemTrackInfoContinue)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToGarage), 0x21, 10);
  tMenuNFS4_ctor(&this->menuTrackInfo,0x1004,&screenTrackInfo->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0xf9,(tMenuItem *)&this->itemTrackInfoContinue,0);
  this_01 = &this->iteratorCar1;
  ptVar6 = new ((void*)(this_01)) tListIteratorCar(frontEnd.playerCar, &carManager);
  this_09 = &this->iteratorColor;
  new ((void*)(this_09)) tListIteratorCarColor((char *)ptVar6, &FEApp->fPlayer, frontEnd.playerCar, 0x30, &carManager);
  ptVar14 = &this->itemCarSelectRace;
  new ((void*)(ptVar14)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToRace), 0x80, 10);
  ptVar10 = &this->itemCar;
  new ((void*)(ptVar10)) tMenuItemNFS4LeftRightChoice(0x92, &this_01->_base_tListIterator, 0x1c, 10);
  ptVar11 = &this->itemColor;
  new ((void*)(ptVar11)) tMenuItemNFS4LeftRightChoice(0x120, &this_09->_base_tListIterator, 0x26, 10);
  new ((void*)(&this->itemShowcase)) tMenuItemGoToMenuNFS4Button(0x112, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToShowroom), 0x30, 10);
  ptVar12 = &this->menuCarOptions;
  tMenuNFS4_ctor(&this->menuSingleCarSelect,0x1a00,&screenCarSelect->_base_tScreen,(tMenu *)0x0,
             (tMenu *)ptVar12,
             MenuExtended_GoToRace,0xba,
             (tMenuItem *)ptVar14,ptVar10,ptVar11,&this->itemShowcase,0);
  ptVar6 = &this->iteratorGarageCar;
  new ((void*)(ptVar6)) tListIteratorCar(frontEnd.garageCar, &carManager);
  this_17 = &this->itemGarageCar;
  new ((void*)(this_17)) tMenuItemNFS4LeftRightChoice(0x92, &ptVar6->_base_tListIterator, 0x1c, 10);
  new ((void*)(&this->itemCarDealer)) tMenuItemGoToMenuNFS4Button(0x74, &(this->menuGoToCarDealer)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0x3a, 10);
  ptVar15 = &this->itemUpgradeCar;
  new ((void*)(ptVar15)) tMenuItemGoToMenuNFS4Button(0x91, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToUpgrades), 0x44, 10);
  tMenuNFS4_ctor(&this->menuCarGarage,0x1a00,&screenCarSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)ptVar12,
             MenuExtended_GoToRace,0x8f,
             (tMenuItem *)ptVar14,this_17,&this->itemCarDealer,ptVar15,0);
  tMenuNFS4_ctor(&this->menuPostCarGarage,0x1a00,&screenCarSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)ptVar12
             ,MenuExtended_GoToRace,0x8f,
             (tMenuItem *)ptVar14,ptVar15,0);
  new ((void*)(&this->iteratorOpponentCar)) tListIteratorCar(&frontEnd.oppCar, &carManager);
  ptVar14 = &this->itemDuelRace;
  new ((void*)(ptVar14)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToRace), 0x2a, 10);
  new ((void*)(&this->itemCar2)) tMenuItemNFS4LeftRightChoice(0x92, &this_01->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->itemColor2)) tMenuItemNFS4LeftRightChoice(0x120, &this_09->_base_tListIterator, 0x16, 10);
  ptVar9 = &this->menuCarDealer;
  new ((void*)(&this->itemGoToDuelBuyCar)) tMenuItemGoToMenuNFS4Button(0x78, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_GoToDealer), -1, 10);
  ptVar13 = &this->itemOpponentCar;
  new ((void*)(ptVar13)) tMenuItemNFS4LeftRightChoice(0xbc, &(this->iteratorOpponentCar)._base_tListIterator, 0x20, 10);
  tMenuNFS4_ctor(&this->menuDuelCarSelect,0x1800,(tScreen *)screenCarSelectDuel,(tMenu *)0x0,
             (tMenu *)ptVar12,
             MenuExtended_GoToRace,0xba,
             (tMenuItem *)ptVar14,this_17,&this->itemGoToDuelBuyCar,ptVar13,0);
  tMenuNFS4_ctor(&this->menuHPDuelCarSelect,0x1800,(tScreen *)screenCarSelectDuel,(tMenu *)0x0,
             (tMenu *)ptVar12,
             MenuExtended_GoToRace,0xba,
             (tMenuItem *)ptVar14,ptVar10,ptVar11,ptVar13,0);
  ptVar14 = &this->itemPlayerOneRace;
  new ((void*)(ptVar14)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0x2a, 10);
  new ((void*)(&this->itemCarP1)) tMenuItemNFS4LeftRightChoice(0x92, &this_01->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->itemColorP1)) tMenuItemNFS4LeftRightChoice(0x120, &this_09->_base_tListIterator, 0x16, 10);
  this_10 = &this->menuCarOptionsPlayerOne;
  new ((void*)(&this->menuPlayerOneCarSelect)) tMenuNFS4TwoPlayer(0x1008, (tScreen *)screenCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)this_10, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0xba, (tMenuItem *)ptVar14, &this->itemCarP1, &this->itemColorP1, 0);
  new ((void*)(&this->itemPlayerTwoRace)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0x2a, 10);
  new ((void*)(&this->itemCarP2)) tMenuItemNFS4LeftRightChoice(0x92, &this_01->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->itemColorP2)) tMenuItemNFS4LeftRightChoice(0x120, &this_09->_base_tListIterator, 0x16, 10);
  this_02 = &this->menuCarOptionsPlayerTwo;
  new ((void*)(&this->menuPlayerTwoCarSelect)) tMenuNFS4TwoPlayer(0x1008, (tScreen *)screenCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)this_02, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0xba, (tMenuItem *)&this->itemPlayerTwoRace, &this->itemCarP2, &this->itemColorP2, 0);
  new ((void*)(&this->itemPlayerOneGarageRace)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0x2a, 10);
  new ((void*)(&this->itemGarageCarP1)) tMenuItemNFS4LeftRightChoice(0x92, &ptVar6->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->menuPlayerOneGarage)) tMenuNFS4TwoPlayer(0x1008, (tScreen *)screenCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)this_10, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0xba, (tMenuItem *)ptVar14, &this->itemGarageCarP1, 0);
  new ((void*)(&this->itemPlayerTwoGarageRace)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0x2a, 10);
  new ((void*)(&this->itemGarageCarP2)) tMenuItemNFS4LeftRightChoice(0x92, &ptVar6->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->menuPlayerTwoGarage)) tMenuNFS4TwoPlayer(0x1008, (tScreen *)screenCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)this_02, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0xba, (tMenuItem *)&this->itemPlayerTwoGarageRace, &this->itemGarageCarP2, 0);
  ptVar6 = &this->iteratorPinkSlipsCar;
  new ((void*)(ptVar6)) tListIteratorCar(frontEnd.pinkSlipsCar, &carManager);
  new ((void*)(&this->itemPlayerOnePinkSlipRace)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0x2a, 10);
  new ((void*)(&this->itemPinkSlipCarP1)) tMenuItemNFS4LeftRightChoice(0x92, &ptVar6->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->menuPlayerOnePinkSlipCarSelect)) tMenuNFS4TwoPlayer(0x1008, (tScreen *)screenPinkSlipsCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)&this->menuPinkSlipCarOptionsPlayerOne, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0xba, (tMenuItem *)&this->itemPlayerOnePinkSlipRace, &this->itemPinkSlipCarP1, 0);
  new ((void*)(&this->itemPlayerTwoPinkSlipRace)) tMenuItemGoToMenuNFS4Button(0xbd, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0x2a, 10);
  new ((void*)(&this->itemPinkSlipCarP2)) tMenuItemNFS4LeftRightChoice(0x92, &ptVar6->_base_tListIterator, 0xc, 10);
  new ((void*)(&this->menuPlayerTwoPinkSlipCarSelect)) tMenuNFS4TwoPlayer(0x1008, (tScreen *)screenPinkSlipsCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)&this->menuPinkSlipCarOptionsPlayerTwo, (void (*)(tMenuCommand &))(MenuExtended_GoTo2PlayerRace), 0xba, (tMenuItem *)&this->itemPlayerTwoPinkSlipRace, &this->itemPinkSlipCarP2, 0);
  new ((void*)(&this->itemGoToBuyCar)) tMenuItemGoToMenuNFS4Button(0x78, &ptVar9->_base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_GoToDealer), 0x58, 10);
  new ((void*)(&this->itemGoToSellCar)) tMenuItemGoToMenuNFS4Button(0x79, &(this->menuCarSeller)._base_tMenu, (void (*)(tMenuCommand &))(MenuExtended_GoToSeller), 0x4e, 10);
  tMenuNFS4_ctor(&this->menuGoToCarDealer,0x1200,&screenCarSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0x90,(tMenuItem *)&this->itemGoToBuyCar,&this->itemGoToSellCar,0);
  ptVar6 = new ((void*)(&this->iteratorDealerCar)) tListIteratorCar(&frontEnd.dealerCar, &carManager);
  new ((void*)(&this->iteratorDealerColor)) tListIteratorCarColor((char *)ptVar6, &FEApp->fPlayer, &frontEnd.dealerCar, 0x30, &carManager);
  new ((void*)(&this->itemDealerCar)) tMenuItemNFS4LeftRightChoice(0x92, &(this->iteratorDealerCar)._base_tListIterator, 0x1c, 10);
  new ((void*)(&this->itemDealerColor)) tMenuItemNFS4LeftRightChoice(0x120, &(this->iteratorDealerColor)._base_tListIterator, 0x26, 10);
  new ((void*)(&this->itemBuyCar)) tMenuItemGoToMenuNFS4Button(0x75, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_BuyCar), 0x58, 10);
  new ((void*)(&this->itemDealerShowroom)) tMenuItemGoToMenuNFS4Button(0x112, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_GoToDealerShowroom), 0x30, 10);
  tMenuNFS4_ctor(ptVar9,0x2240,&screenCarSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,(void *)0x0,0x90,
             (tMenuItem *)&this->itemDealerCar,&this->itemDealerColor,&this->itemBuyCar,
             &this->itemDealerShowroom,0);
  new ((void*)(&this->iteratorSellerCar)) tListIteratorCar(&frontEnd.sellerCar, &carManager);
  new ((void*)(&this->itemSellerCar)) tMenuItemNFS4LeftRightChoice(0x92, &(this->iteratorSellerCar)._base_tListIterator, 0x1c, 10);
  new ((void*)(&this->itemSellCar)) tMenuItemGoToMenuNFS4Button(0x77, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_SellCar), 0x4e, 10);
  tMenuNFS4_ctor(&this->menuCarSeller,0x2200,&screenCarSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0x90,(tMenuItem *)&this->itemSellerCar,&this->itemSellCar,0);
  new ((void*)(&this->itemPurchaseUpgrade1)) tMenuItemGoToMenuNFS4Button(0x96, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_PurchaseUpgrade1), 0x62, 10);
  new ((void*)(&this->itemPurchaseUpgrade2)) tMenuItemGoToMenuNFS4Button(0x97, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_PurchaseUpgrade2), 0x6c, 10);
  new ((void*)(&this->itemPurchaseUpgrade3)) tMenuItemGoToMenuNFS4Button(0x98, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_PurchaseUpgrade3), 0x76, 10);
  tMenuNFS4_ctor(&this->menuCarUpgrades,0x2200,&screenCarSelect->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,
             (void *)0x0,0x91,(tMenuItem *)&this->itemPurchaseUpgrade1,
             &this->itemPurchaseUpgrade2,&this->itemPurchaseUpgrade3,0);
  this_03 = &this->iteratorTransmission;
  new ((void*)(this_03)) tListIteratorIndexed(SelectListTransmission, frontEnd.transmission, &FEApp->fPlayer);
  this_13 = &this->iteratorABS;
  ptVar5 = new ((void*)(this_13)) tListIteratorIndexed(SelectListOffOn, frontEnd.ABS, &FEApp->fPlayer);
  ptVar7 = new ((void*)(&ptVar5->_base_tListIterator)) tListIterator(SelectListOffOn, &frontEnd.damage);
  new ((void*)(ptVar7)) tListIterator(SelectListOpponentUpgrades, &frontEnd.opponentUpgrades);
  this_11 = &this->itemTransmission;
  new ((void*)(&this_11->_base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x10a, &this_03->_base_tListIterator);
  this_04 = &this->itemABS;
  *(void **)&((this->itemTransmission)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&this_04->_base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x10b, &this_13->_base_tListIterator);
  this_05 = &this->itemDamage;
  *(void **)&((this->itemABS)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&this_05->_base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x111, &this->iteratorDamage);
  this_18 = &this->itemTransmission2;
  *(void **)&((this->itemDamage)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&this_18->_base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x10a, &this_03->_base_tListIterator);
  this_06 = &this->itemABS2;
  *(void **)&((this->itemTransmission2)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&this_06->_base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x10b, &this_13->_base_tListIterator);
  this_14 = &this->itemDamage2;
  *(void **)&((this->itemABS2)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&this_14->_base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x111, &this->iteratorDamage);
  *(void **)&((this->itemDamage2)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(&(this->itemOpponentUpgrades)._base_tMenuItemLeftRightChoice)) tMenuItemLeftRightChoice(0x10e, &this->iteratorOpponentUpgrades);
  *(void **)&((this->itemOpponentUpgrades)._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOptionsLeftRightChoice_vtable;
  new ((void*)(ptVar12)) tMenuOptions(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xbb, -1, (tMenuItem *)this_11, this_04, this_05, &this->itemOpponentUpgrades, 0);
  new ((void*)(this_10)) tMenuOptions(0x1008, (tScreen *)screenCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xbb, 0, (tMenuItem *)this_11, this_04, this_05, 0);
  new ((void*)(this_02)) tMenuOptions(0x1008, (tScreen *)screenCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xbb, 1, (tMenuItem *)this_18, this_06, this_14, 0);
  new ((void*)(&this->menuPinkSlipCarOptionsPlayerOne)) tMenuOptions(0x1008, (tScreen *)screenPinkSlipsCarSelectTwoPlayer, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xbb, 0, (tMenuItem *)this_11, this_04, this_05, 0);
  new ((void*)(&this->menuPinkSlipCarOptionsPlayerTwo)) tMenuOptions(0x1008, (tScreen *)screenPinkSlipsCarSelectPlayerTwo, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xbb, 1, (tMenuItem *)this_18, this_06, this_14, 0);
  new ((void*)(&this->menuShowroom)) tMenuBlank(0x4000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1);
  new ((void*)(&this->itemOptionsAudio)) tMenuItemGoToMenuNFS4Button(0x1c5, &(this->menuAudio)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0xb4, 10);
  new ((void*)(&this->itemOptionsDisplay)) tMenuItemGoToMenuNFS4Button(0x1c6, &(this->menuDisplayOptions)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0xbe, 10);
  new ((void*)(&this->itemOptionsControllers)) tMenuItemGoToMenuNFS4Button(0x1c8, &(this->menuControllerConfig)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 200, 10);
  new ((void*)(&this->itemOptionsMemoryCard)) tMenuItemGoToMenuNFS4Button(0x1c9, &(this->menuMemory)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0xd2, 10);
  new ((void*)(&this->itemOptionsUsername)) tMenuItemGoToMenuNFS4Button(0x1ca, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_EnterUserName), 0xdc, 10);
  new ((void*)(&this->itemOptionsCredits)) tMenuItemGoToMenuNFS4Button(0x1cc, (tMenu *)&this->menuCredits, (void (*)(tMenuCommand &))((void *)0x0), 0xe6, 10);
  tMenuNFS4_ctor(&this->menuOptions,0x1014,&screenMain->_base_tScreen,(tMenu *)0x0,(tMenu *)0x0,(void *)0x0
             ,0x5d,(tMenuItem *)&this->itemOptionsAudio,&this->itemOptionsDisplay,
             &this->itemOptionsControllers,&this->itemOptionsMemoryCard,&this->itemOptionsUsername,
             &this->itemOptionsCredits,0);
  new ((void*)(&this->iteratorMusicVolume)) tListIteratorRange('\0', '\x7f', &frontEnd.musicVolume);
  new ((void*)(&this->iteratorSoundEffectsVolume)) tListIteratorRange('\0', '\x7f', &frontEnd.sfxVolume);
  new ((void*)(&this->iteratorEngineVolume)) tListIteratorRange('\0', '\x7f', &frontEnd.engineVolume);
  new ((void*)(&this->iteratorSpeechVolume)) tListIteratorRange('\0', '\x7f', &frontEnd.narrationVolume);
  ptVar7 = &(new ((void*)(&this->iteratorAmbientVolume)) tListIteratorRange('\0', '\x7f', &frontEnd.ambientVolume))->_base_tListIterator;
  new ((void*)(ptVar7)) tListIterator(SelectListAudioMode, &frontEnd.audioMode);
  new ((void*)(&this->itemMusicVolume)) tMenuItemLeftRightAudioSlider(0x1d5, &(this->iteratorMusicVolume)._base_tListIterator, 0);
  new ((void*)(&this->itemSoundEffectsVolume)) tMenuItemLeftRightAudioSlider(0x1d6, &(this->iteratorSoundEffectsVolume)._base_tListIterator, 1);
  new ((void*)(&this->itemEngineVolume)) tMenuItemLeftRightAudioSlider(0x1d7, &(this->iteratorEngineVolume)._base_tListIterator, 2);
  new ((void*)(&this->itemSpeechVolume)) tMenuItemLeftRightAudioSlider(0x1d8, &(this->iteratorSpeechVolume)._base_tListIterator, 3);
  new ((void*)(&this->itemAmbientVolume)) tMenuItemLeftRightAudioSlider(0x1d9, &(this->iteratorAmbientVolume)._base_tListIterator, 4);
  new ((void*)(&(this->itemAudioMode)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1da, &this->iteratorAudioMode);
  *(void **)&((this->itemAudioMode)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemDisplayLeftRightChoice_vtable;
  new ((void*)(&(this->itemSlidingPlayList)._base_tMenuItemSlidingMenu)) tMenuItemSlidingMenu(0x1db, 0x15e, 0x2b, -0x66, 0xd, false);
  *(void **)&((this->itemSlidingPlayList)._base_tMenuItemSlidingMenu._base_tMenuItem._vf) = (void *)tMenuItemSlidingActivated_vtable;
  new ((void*)(&this->menuPlayListMenu)) tInsideBoxSongMenu(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0, (tMenuItem *)0x0);
  new ((void*)(&this->menuAudio)) tOptionsMenu(0x1010, &screenAudio->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0x263, 0x26, 10, (tMenuItem *)&this->itemMusicVolume, &this->itemSoundEffectsVolume, &this->itemEngineVolume, &this->itemSpeechVolume, &this->itemAmbientVolume, &this->itemAudioMode, &this->itemSlidingPlayList, 0);
  new ((void*)(&this->iteratorDisplaySpeedometer)) tListIteratorIndexed(SelectListDisplaySpeed, frontEnd.displaySpeed, &FEApp->fInputPlayer);
  new ((void*)(&this->iteratorDisplayMap)) tListIteratorIndexed(SelectListDisplayMap, frontEnd.displayMap, &FEApp->fInputPlayer);
  new ((void*)(&this->iteratorDisplayOpponentID)) tListIteratorIndexed(SelectListDisplayOpponentID, frontEnd.displayOpponentID, &FEApp->fInputPlayer);
  new ((void*)(&this->iteratorDisplayTime)) tListIteratorIndexed(SelectListOffOn, frontEnd.displayTime, &FEApp->fInputPlayer);
  new ((void*)(&this->iteratorDisplayPosition)) tListIteratorIndexed(SelectListOffOn, frontEnd.displayPosition, &FEApp->fInputPlayer);
  ptVar5 = new ((void*)(&this->iteratorDisplayLapNumber)) tListIteratorIndexed(SelectListOffOn, frontEnd.displayLapNumber, &FEApp->fInputPlayer);
  new ((void*)(&ptVar5->_base_tListIterator)) tListIterator(SelectListSplitTime, &frontEnd.checkPointType);
  new ((void*)(&this->iteratorDisplaySplitDisplay)) tListIteratorIndexed(SelectListSplitDisplay, frontEnd.checkPointDisplay, &FEApp->fInputPlayer);
  new ((void*)(&(this->itemDisplaySpeedometer)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1df, &(this->iteratorDisplaySpeedometer)._base_tListIterator);
  *(void **)&((this->itemDisplaySpeedometer)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemDisplayLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplayMap)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e1, &(this->iteratorDisplayMap)._base_tListIterator);
  *(void **)&((this->itemDisplayMap)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemDisplayLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplayOpponentID)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e2, &(this->iteratorDisplayOpponentID)._base_tListIterator);
  *(void **)&((this->itemDisplayOpponentID)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemDisplayLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplayTime)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e3, &(this->iteratorDisplayTime)._base_tListIterator);
  *(void **)&((this->itemDisplayTime)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOnOffLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplayPosition)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e6, &(this->iteratorDisplayPosition)._base_tListIterator);
  *(void **)&((this->itemDisplayPosition)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOnOffLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplayLapNumber)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e7, &(this->iteratorDisplayLapNumber)._base_tListIterator);
  *(void **)&((this->itemDisplayLapNumber)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemOnOffLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplaySplitTime)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e4, &this->iteratorDisplaySplitTime);
  *(void **)&((this->itemDisplaySplitTime)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemDisplayLeftRightChoice_vtable;
  new ((void*)(&(this->itemDisplaySplitDisplay)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x1e5, &(this->iteratorDisplaySplitDisplay)._base_tListIterator);
  screenHandler_00 = screenDisplay;
  *(void **)&((this->itemDisplaySplitDisplay)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemDisplayLeftRightChoice_vtable;
  new ((void*)(&this->menuDisplayOptions)) tOptionsMenu(0x1020, &screenHandler_00->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0x1dd, 1, 10, (tMenuItem *)&this->itemDisplaySpeedometer, &this->itemDisplayMap, &this->itemDisplayOpponentID, &this->itemDisplayTime, &this->itemDisplaySplitTime, &this->itemDisplaySplitDisplay, &this->itemDisplayPosition, &this->itemDisplayLapNumber, 0);
  new ((void*)(&this->iteratorControllerConfigSelected)) tListIteratorIndexed(SelectListControllerConfig, frontEnd.controlConfig, &FEApp->fInputPlayer);
  new ((void*)(&(this->itemControllerConfigSelected)._base_tMenuItemLeftRightFade)) tMenuItemLeftRightFade(0x209, &(this->iteratorControllerConfigSelected)._base_tListIterator);
  *(void **)&((this->itemControllerConfigSelected)._base_tMenuItemLeftRightFade._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemControllerLeftRightChoice_vtable;
  new ((void*)(&this->itemControllerSettings)) tMenuItemSlidingMenu(0x20a, 0xac, 0x48, 0, 0xd, true);
  new ((void*)(&this->menuControllerConfig)) tOptionsMenu(0x1020, &screenControllerConfig->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0x208, 0, 10, (tMenuItem *)&this->itemControllerConfigSelected, &this->itemControllerSettings, 0);
  new ((void*)(&this->iteratorControllerShockMode)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.shockMode, &FEApp->fInputPlayer)
  ;
  firstItem = &this->itemControllerShockMode;
  new ((void*)(&firstItem->_base_tInsideBoxLeftRightSlider)) tInsideBoxLeftRightSlider(0x20e, (tListIterator *)&this->iteratorControllerShockMode);
  ptVar1 = FEApp;
  *(void **)&((this->itemControllerShockMode)._base_tInsideBoxLeftRightSlider._base_tMenuItemLeftRightSlider._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tInsideBoxControllerLeftRightSlider_vtable;
  new ((void*)(&this->iteratorControllerShockImpact)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.shockImpact, &ptVar1->fInputPlayer);
  this_07 = &this->itemControllerShockImpact;
  new ((void*)(&this_07->_base_tInsideBoxLeftRightSlider)) tInsideBoxLeftRightSlider(0x20f, (tListIterator *)&this->iteratorControllerShockImpact);
  pcVar4 = &FEApp->fInputPlayer;
  *(void **)&((this->itemControllerShockImpact)._base_tInsideBoxLeftRightSlider._base_tMenuItemLeftRightSlider._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tInsideBoxControllerLeftRightSlider_vtable;
  new ((void*)(&this->iteratorControllerSteeringRange1)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.J1MAX, pcVar4);
  new ((void*)(&this->itemControllerSteeringRange1)) tInsideBoxTwoWaySlider(0x211, (tListIterator *)&this->iteratorControllerSteeringRange1, 0);
  new ((void*)(&this->iteratorControllerDeadSpot1)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.J1MIN, &FEApp->fInputPlayer);
  this_08 = &this->itemControllerDeadSpot1;
  new ((void*)(this_08)) tInsideBoxTwoWaySlider(0x213, (tListIterator *)&this->iteratorControllerDeadSpot1, 1);
  new ((void*)(&this->iteratorControllerSteeringRange2)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.J2MAX, &FEApp->fInputPlayer);
  new ((void*)(&this->itemControllerSteeringRange2)) tInsideBoxTwoWaySlider(0x210, (tListIterator *)&this->iteratorControllerSteeringRange2, 2);
  new ((void*)(&this->iteratorControllerDeadSpot2)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.J2MIN, &FEApp->fInputPlayer);
  this_15 = &this->itemControllerDeadSpot2;
  new ((void*)(this_15)) tInsideBoxTwoWaySlider(0x212, (tListIterator *)&this->iteratorControllerDeadSpot2, 3);
  new ((void*)(&this->iteratorControllerJoyRange)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.steeringRange, &FEApp->fInputPlayer);
  new ((void*)(&this->itemControllerJoyRange)) tInsideBoxTwoWaySlider(0x214, (tListIterator *)&this->iteratorControllerJoyRange, 0);
  new ((void*)(&this->iteratorControllerCenterPoint)) tListIteratorRangeIndexed('\0', '\x7f', frontEnd.deadSpot, &FEApp->fInputPlayer);
  new ((void*)(&this->itemControllerCenterPoint)) tInsideBoxTwoWaySlider(0x215, (tListIterator *)&this->iteratorControllerCenterPoint, 1);
  new ((void*)(&this->iteratorControllerIMax)) tListIteratorRangeIndexed('\0', -1, frontEnd.ImaxRange, &FEApp->fInputPlayer);
  new ((void*)(&this->itemControllerIMax)) tInsideBoxTwoWaySlider(0x216, (tListIterator *)&this->iteratorControllerIMax, 2);
  new ((void*)(&this->iteratorControllerIIMax)) tListIteratorRangeIndexed('\0', -1, frontEnd.IImaxRange, &FEApp->fInputPlayer);
  new ((void*)(&this->itemControllerIIMax)) tInsideBoxTwoWaySlider(0x217, (tListIterator *)&this->iteratorControllerIIMax, 3);
  new ((void*)(&this->menuControllerDualShock)) tInsideBoxMenu(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0, (tMenuItem *)firstItem, this_07, 0);
  new ((void*)(&this->menuControllerAnalog)) tInsideBoxMenu(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0, (tMenuItem *)&this->itemControllerSteeringRange1, this_08, &this->itemControllerSteeringRange2, this_15, 0);
  new ((void*)(&this->menuControllerDualShockAnalog)) tInsideBoxMenu(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0, (tMenuItem *)firstItem, this_07, this_08, this_15, 0);
  new ((void*)(&this->menuControllerNegcon)) tInsideBoxMenu(0x1000, (tScreen *)0x0, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0, (tMenuItem *)&this->itemControllerJoyRange, &this->itemControllerCenterPoint, &this->itemControllerIMax, &this->itemControllerIIMax, 0);
  this_19 = &this->itemSaveGame;
  new ((void*)((tMenuItemGoToMenuButton *)this_19)) tMenuItemGoToMenuButton(0x286, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_SaveGame));
  *(void **)&((this->itemSaveGame)._base_tMenuItemGoToMenuButtonFade._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMemoryCardMenuItem_vtable;
  new ((void*)((tMenuItemGoToMenuButton *)&this->itemLoadGame)) tMenuItemGoToMenuButton(0x287, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_LoadGame));
  ptVar3 = screenMemcard;
  *(void **)&((this->itemLoadGame)._base_tMenuItemGoToMenuButtonFade._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMemoryCardMenuItem_vtable;
  new ((void*)(&this->menuMemory)) tOptionsMenu(0x1020, &ptVar3->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1, 0x2e, 10, (tMenuItem *)&this->itemLoadGame, this_19, 0);
  new ((void*)(&this->menuItemUserName)) tUserNameMenuItem(0x1f8);
  new ((void*)(&this->menuItemUserName1)) tUserNameMenuItem(0x1f8);
  new ((void*)(&this->menuItemUserName2)) tUserNameMenuItem(0x1f8);
  ptVar7 = (tListIterator *)
           new ((void*)(&this->menuUserName)) tOptionsMenu(0x1120, &screenUserName->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1, 0x20, 10, &(this->menuItemUserName)._base_tMenuItem, 0);
  new ((void*)(ptVar7)) tListIterator(screenTrophyRoom->fTrophyList, &screenTrophyRoom->thisisuseless);
  new ((void*)(&(this->itemChangeTrophy)._base_tMenuItemNFS4LeftRightChoice)) tMenuItemNFS4LeftRightChoice(0x5e, &this->iteratorChangeTrophy, -1, 0);
  screenHandler = screenTrophyRoom;
  *(void **)&((this->itemChangeTrophy)._base_tMenuItemNFS4LeftRightChoice._base_tMenuItemLeftRightChoice._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)&tBlankMenuItemNFS4LeftRightChoice_vtable;
  new ((void*)(&this->menuTrophyRoom)) tMenuNFS4Bottom(0x4010, &screenHandler->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1, (tMenuItem *)&this->itemChangeTrophy, 0);
  new ((void*)(&this->itemPinkSlipStandingsForward)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_PinkSlipsContinue), 0, 10);
  new ((void*)(&this->itemPinkSlipStandingsExit)) tMenuItemGoToMenuNFS4Button(0x9c, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_ExitPinkSlipsEarly), 0, 10);
  tMenuNFS4_ctor(&this->menuPinkSlipStandings,0x1004,(tScreen *)screenPinkSlipStandings,(tMenu *)0x0,
             (tMenu *)0x0,(void *)0x0,0x2f4,(tMenuItem *)&this->itemPinkSlipStandingsForward,
             &this->itemPinkSlipStandingsExit,0);
  new ((void*)(&this->itemTournStandingsForward)) tMenuItemGoToMenuNFS4Button(0x5a, &(this->menuTrackInfo)._base_tMenu, (void (*)(tMenuCommand &))((void *)0x0), 0, 10)
  ;
  new ((void*)(&this->itemTournStandingsExit)) tMenuItemGoToMenuNFS4Button(0x9b, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_ExitTourney), 0, 10);
  tMenuNFS4_ctor(&this->menuTournamentStandings,0x1004,(tScreen *)screenTournamentStandings3item,
             (tMenu *)0x0,(tMenu *)0x0,(void *)0x0,0x2f4,
             (tMenuItem *)&this->itemTournStandingsForward,&this->itemTournStandingsExit,0);
  new ((void*)(&this->itemTournamentFinishedHome)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)&this->menuTournamentTrophy, (void (*)(tMenuCommand &))((void *)0x0), 0, 10);
  tMenuNFS4_ctor(&this->menuTournamentFinished,0x1004,&screenTournamentStandings->_base_tScreen,(tMenu *)0x0,
             (tMenu *)0x0,(void *)0x0,0x2f4,(tMenuItem *)&this->itemTournamentFinishedHome,0);
  new ((void*)(&this->menuTournamentTrophy)) tMenuBlank(0x8000, (tScreen *)screenTournamentTrophy, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_TierFinished), -1);
  new ((void*)(&this->menuPostGamePlayer1Name)) tOptionsMenu(0x1040, &screenUserName->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_FinishedPlayer1GetName), -1, 0x20, 10, &(this->menuItemUserName1)._base_tMenuItem, 0);
  new ((void*)(&this->menuPostGamePlayer2Name)) tOptionsMenu(0x1080, &screenUserName->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_FinishedPlayer2GetName), -1, 0x20, 10, &(this->menuItemUserName2)._base_tMenuItem, 0);
  new ((void*)(&(this->itemPostGameTrackRecordsContinue)._base_tMenuItemGoToMenuNFS4Button)) tMenuItemGoToMenuNFS4Button(0x5a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_PostGameMenu), -1, -1)
  ;
  ptVar2 = screenTrackRecords;
  *(void **)&((this->itemPostGameTrackRecordsContinue)._base_tMenuItemGoToMenuNFS4Button._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)&tBlankMenuItemGoToMenuNFS4Button_vtable;
  new ((void*)(&this->menuPostGameTrackRecords)) tOptionsMenu(0x21004, &ptVar2->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), 0xd4, 1, 10, (tMenuItem *)&this->itemPostGameTrackRecordsContinue, 0);
  new ((void*)(&this->menuPinkSlipCongrats)) tMenuBlank(0x8000, (tScreen *)screenPinkSlipCongrats, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_AwardPinkSlipsCar), -1);
  new ((void*)(&this->menuBeTheCopCongrats)) tMenuBlank(0x8000, (tScreen *)screenBeTheCopCongrats, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame), -1);
  new ((void*)(&this->menuTierCompleteCongrats)) tMenuBlank(0x8000, (tScreen *)screenTournamentCongrats, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_TransitionFromPostGameToMainMenuAndSaveGame), -1);
  new ((void*)(&this->menuCredits)) tMenuBlank(0x1010, &screenMain->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1);
  new ((void*)((tMenuItemGoToMenuButton *)&this->itemMemContinue)) tMenuItemGoToMenuButton(0x28a, (tMenu *)0x0, (void (*)(tMenuCommand &))(MenuExtended_TransitionFromPostGameToMainMenu));
  ptVar3 = screenMemcard;
  *(void **)&((this->itemMemContinue)._base_tMenuItemGoToMenuButtonFade._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMemoryCardMenuItem_vtable;
  new ((void*)(&this->menuPostGameSave)) tOptionsMenu(0x1040, &ptVar3->_base_tScreen, (tMenu *)0x0, (tMenu *)0x0, (void (*)(tMenuCommand &))((void *)0x0), -1, 0x2e, 10, (tMenuItem *)&this->itemMemContinue, this_19, 0);
  (this->menuPlayerOneCarSelect)._base_tMenuNFS4._base_tMenu.fChildMenu = (tMenu *)&this->menuPlayerTwoCarSelect
  ;
  (this->menuPlayerOneGarage)._base_tMenuNFS4._base_tMenu.fChildMenu = (tMenu *)&this->menuPlayerTwoGarage;
  (this->menuPlayerOnePinkSlipCarSelect)._base_tMenuNFS4._base_tMenu.fChildMenu =
       (tMenu *)&this->menuPlayerTwoPinkSlipCarSelect;
  SetDimensions(&(this->itemMusicVolume)._base_tMenuItemLeftRightSlider,0,0,0x78,5);
  SetDimensions(&(this->itemSoundEffectsVolume)._base_tMenuItemLeftRightSlider,0,0,0x78,5);
  SetDimensions(&(this->itemEngineVolume)._base_tMenuItemLeftRightSlider,0,0,0x78,5);
  SetDimensions(&(this->itemSpeechVolume)._base_tMenuItemLeftRightSlider,0,0,0x78,5);
  SetDimensions(&(this->itemAmbientVolume)._base_tMenuItemLeftRightSlider,0,0,0x78,5);
  uVar8 = (this->itemTournamentFinishedHome)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags;
  (this->iteratorPinkSlipsCar).fCarListFilter = 0x20;
  (this->iteratorGarageCar).fCarListFilter = 2;
  (this->iteratorDealerCar).fCarListFilter = 1;
  (this->iteratorSellerCar).fCarListFilter = 2;
  (this->menuAudio)._base_tMenu.VertHelp = 0;
  (this->menuDisplayOptions)._base_tMenu.VertHelp = 0;
  (this->menuControllerConfig)._base_tMenu.VertHelp = 1;
  (this->itemTournamentFinishedHome)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags =
       uVar8 | 0x40;
  (this->menuMemory)._base_tMenu.VertHelp = 0;
  (this->menuUserName)._base_tMenu.VertHelp = 0;
  (this->menuTrackRecords)._base_tMenu.VertHelp = 1;
  (this->menuTrophyInfo)._base_tMenuNFS4._base_tMenu.VertHelp = 0;
  return;
}



/* ---- tGlobalMenuDefs::dtor  [FEMENUDEFS.CPP:2204] ---- */

void tGlobalMenuDefs::DestroyBody(int mode)

{
  
  (((tOptionsMenu*)(&this->menuPostGameSave))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuPostGameSave));
  (((tMenuItemGoToMenuButton*)((tMenuItemGoToMenuButton *)&this->itemMemContinue))->~tMenuItemGoToMenuButton(), (tMenuItemGoToMenuButton*)((tMenuItemGoToMenuButton *)&this->itemMemContinue));
  (((tMenuBlank*)(&this->menuCredits))->~tMenuBlank(), (tMenuBlank*)(&this->menuCredits));
  (((tMenuBlank*)(&this->menuTierCompleteCongrats))->~tMenuBlank(), (tMenuBlank*)(&this->menuTierCompleteCongrats));
  (((tMenuBlank*)(&this->menuBeTheCopCongrats))->~tMenuBlank(), (tMenuBlank*)(&this->menuBeTheCopCongrats));
  (((tMenuBlank*)(&this->menuPinkSlipCongrats))->~tMenuBlank(), (tMenuBlank*)(&this->menuPinkSlipCongrats));
  (((tOptionsMenu*)(&this->menuPostGameTrackRecords))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuPostGameTrackRecords));
  (((tMenuItemGoToMenuNFS4Button*)(&(this->itemPostGameTrackRecordsContinue)._base_tMenuItemGoToMenuNFS4Button))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&(this->itemPostGameTrackRecordsContinue)._base_tMenuItemGoToMenuNFS4Button));
  (((tOptionsMenu*)(&this->menuPostGamePlayer2Name))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuPostGamePlayer2Name));
  (((tOptionsMenu*)(&this->menuPostGamePlayer1Name))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuPostGamePlayer1Name));
  (((tMenuBlank*)(&this->menuTournamentTrophy))->~tMenuBlank(), (tMenuBlank*)(&this->menuTournamentTrophy));
  (((tMenuNFS4*)(&this->menuTournamentFinished))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTournamentFinished));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTournamentFinishedHome))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTournamentFinishedHome));
  (((tMenuNFS4*)(&this->menuTournamentStandings))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTournamentStandings));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTournStandingsExit))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTournStandingsExit));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTournStandingsForward))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTournStandingsForward));
  (((tMenuNFS4*)(&this->menuPinkSlipStandings))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuPinkSlipStandings));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPinkSlipStandingsExit))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPinkSlipStandingsExit));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPinkSlipStandingsForward))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPinkSlipStandingsForward));
  (((tMenuNFS4Bottom*)(&this->menuTrophyRoom))->~tMenuNFS4Bottom(), (tMenuNFS4Bottom*)(&this->menuTrophyRoom));
  (((tMenuItemNFS4LeftRightChoice*)(&(this->itemChangeTrophy)._base_tMenuItemNFS4LeftRightChoice))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&(this->itemChangeTrophy)._base_tMenuItemNFS4LeftRightChoice));
  tListIterator_dtor(&this->iteratorChangeTrophy,2);
  (((tOptionsMenu*)(&this->menuUserName))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuUserName));
  (((tMenuItem*)(&(this->menuItemUserName2)._base_tMenuItem))->~tMenuItem(), (tMenuItem*)(&(this->menuItemUserName2)._base_tMenuItem));
  (((tMenuItem*)(&(this->menuItemUserName1)._base_tMenuItem))->~tMenuItem(), (tMenuItem*)(&(this->menuItemUserName1)._base_tMenuItem));
  (((tMenuItem*)(&(this->menuItemUserName)._base_tMenuItem))->~tMenuItem(), (tMenuItem*)(&(this->menuItemUserName)._base_tMenuItem));
  (((tOptionsMenu*)(&this->menuMemory))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuMemory));
  (((tMenuItemGoToMenuButton*)((tMenuItemGoToMenuButton *)&this->itemLoadGame))->~tMenuItemGoToMenuButton(), (tMenuItemGoToMenuButton*)((tMenuItemGoToMenuButton *)&this->itemLoadGame));
  (((tMenuItemGoToMenuButton*)((tMenuItemGoToMenuButton *)&this->itemSaveGame))->~tMenuItemGoToMenuButton(), (tMenuItemGoToMenuButton*)((tMenuItemGoToMenuButton *)&this->itemSaveGame));
  (((tInsideBoxMenu*)(&this->menuControllerNegcon))->~tInsideBoxMenu(), (tInsideBoxMenu*)(&this->menuControllerNegcon));
  (((tInsideBoxMenu*)(&this->menuControllerDualShockAnalog))->~tInsideBoxMenu(), (tInsideBoxMenu*)(&this->menuControllerDualShockAnalog));
  (((tInsideBoxMenu*)(&this->menuControllerAnalog))->~tInsideBoxMenu(), (tInsideBoxMenu*)(&this->menuControllerAnalog));
  (((tInsideBoxMenu*)(&this->menuControllerDualShock))->~tInsideBoxMenu(), (tInsideBoxMenu*)(&this->menuControllerDualShock));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerIIMax))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerIIMax));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerIIMax))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerIIMax));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerIMax))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerIMax));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerIMax))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerIMax));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerCenterPoint))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerCenterPoint));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerCenterPoint))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerCenterPoint));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerJoyRange))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerJoyRange));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerJoyRange))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerJoyRange));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerDeadSpot2))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerDeadSpot2));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerDeadSpot2))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerDeadSpot2));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerSteeringRange2))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerSteeringRange2));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerSteeringRange2))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerSteeringRange2));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerDeadSpot1))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerDeadSpot1));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerDeadSpot1))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerDeadSpot1));
  (((tInsideBoxTwoWaySlider*)(&this->itemControllerSteeringRange1))->~tInsideBoxTwoWaySlider(), (tInsideBoxTwoWaySlider*)(&this->itemControllerSteeringRange1));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerSteeringRange1))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerSteeringRange1));
  (((tInsideBoxLeftRightSlider*)(&(this->itemControllerShockImpact)._base_tInsideBoxLeftRightSlider))->~tInsideBoxLeftRightSlider(), (tInsideBoxLeftRightSlider*)(&(this->itemControllerShockImpact)._base_tInsideBoxLeftRightSlider));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerShockImpact))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerShockImpact));
  (((tInsideBoxLeftRightSlider*)(&(this->itemControllerShockMode)._base_tInsideBoxLeftRightSlider))->~tInsideBoxLeftRightSlider(), (tInsideBoxLeftRightSlider*)(&(this->itemControllerShockMode)._base_tInsideBoxLeftRightSlider));
  (((tListIteratorRangeIndexed*)(&this->iteratorControllerShockMode))->~tListIteratorRangeIndexed(), (tListIteratorRangeIndexed*)(&this->iteratorControllerShockMode));
  (((tOptionsMenu*)(&this->menuControllerConfig))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuControllerConfig));
  (((tMenuItemSlidingMenu*)(&this->itemControllerSettings))->~tMenuItemSlidingMenu(), (tMenuItemSlidingMenu*)(&this->itemControllerSettings));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemControllerConfigSelected))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemControllerConfigSelected));
  (((tListIteratorIndexed*)(&this->iteratorControllerConfigSelected))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorControllerConfigSelected));
  (((tOptionsMenu*)(&this->menuDisplayOptions))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuDisplayOptions));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplaySplitDisplay))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplaySplitDisplay));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplaySplitTime))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplaySplitTime));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayLapNumber))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayLapNumber));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayPosition))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayPosition));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayTime))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayTime));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayOpponentID))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayOpponentID));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayMap))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplayMap));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplaySpeedometer))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemDisplaySpeedometer));
  (((tListIteratorIndexed*)(&this->iteratorDisplaySplitDisplay))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplaySplitDisplay));
  tListIterator_dtor(&this->iteratorDisplaySplitTime,2);
  (((tListIteratorIndexed*)(&this->iteratorDisplayLapNumber))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplayLapNumber));
  (((tListIteratorIndexed*)(&this->iteratorDisplayPosition))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplayPosition));
  (((tListIteratorIndexed*)(&this->iteratorDisplayTime))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplayTime));
  (((tListIteratorIndexed*)(&this->iteratorDisplayOpponentID))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplayOpponentID));
  (((tListIteratorIndexed*)(&this->iteratorDisplayMap))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplayMap));
  (((tListIteratorIndexed*)(&this->iteratorDisplaySpeedometer))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorDisplaySpeedometer));
  (((tOptionsMenu*)(&this->menuAudio))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuAudio));
  (((tInsideBoxSongMenu*)(&this->menuPlayListMenu))->~tInsideBoxSongMenu(), (tInsideBoxSongMenu*)(&this->menuPlayListMenu));
  (((tMenuItemSlidingMenu*)(&(this->itemSlidingPlayList)._base_tMenuItemSlidingMenu))->~tMenuItemSlidingMenu(), (tMenuItemSlidingMenu*)(&(this->itemSlidingPlayList)._base_tMenuItemSlidingMenu));
  (((tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemAudioMode))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)((tMenuItemLeftRightChoice *)&this->itemAudioMode));
  (((tMenuItemLeftRightAudioSlider*)(&this->itemAmbientVolume))->~tMenuItemLeftRightAudioSlider(), (tMenuItemLeftRightAudioSlider*)(&this->itemAmbientVolume));
  (((tMenuItemLeftRightAudioSlider*)(&this->itemSpeechVolume))->~tMenuItemLeftRightAudioSlider(), (tMenuItemLeftRightAudioSlider*)(&this->itemSpeechVolume));
  (((tMenuItemLeftRightAudioSlider*)(&this->itemEngineVolume))->~tMenuItemLeftRightAudioSlider(), (tMenuItemLeftRightAudioSlider*)(&this->itemEngineVolume));
  (((tMenuItemLeftRightAudioSlider*)(&this->itemSoundEffectsVolume))->~tMenuItemLeftRightAudioSlider(), (tMenuItemLeftRightAudioSlider*)(&this->itemSoundEffectsVolume));
  (((tMenuItemLeftRightAudioSlider*)(&this->itemMusicVolume))->~tMenuItemLeftRightAudioSlider(), (tMenuItemLeftRightAudioSlider*)(&this->itemMusicVolume));
  tListIterator_dtor(&this->iteratorAudioMode,2);
  (((tListIteratorRange*)(&this->iteratorAmbientVolume))->~tListIteratorRange(), (tListIteratorRange*)(&this->iteratorAmbientVolume));
  (((tListIteratorRange*)(&this->iteratorSpeechVolume))->~tListIteratorRange(), (tListIteratorRange*)(&this->iteratorSpeechVolume));
  (((tListIteratorRange*)(&this->iteratorEngineVolume))->~tListIteratorRange(), (tListIteratorRange*)(&this->iteratorEngineVolume));
  (((tListIteratorRange*)(&this->iteratorSoundEffectsVolume))->~tListIteratorRange(), (tListIteratorRange*)(&this->iteratorSoundEffectsVolume));
  (((tListIteratorRange*)(&this->iteratorMusicVolume))->~tListIteratorRange(), (tListIteratorRange*)(&this->iteratorMusicVolume));
  (((tMenuNFS4*)(&this->menuOptions))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuOptions));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsCredits))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsCredits));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsUsername))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsUsername));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsMemoryCard))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsMemoryCard));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsControllers))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsControllers));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsDisplay))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsDisplay));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsAudio))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOptionsAudio));
  (((tMenuBlank*)(&this->menuShowroom))->~tMenuBlank(), (tMenuBlank*)(&this->menuShowroom));
  (((tMenuOptions*)(&this->menuPinkSlipCarOptionsPlayerTwo))->~tMenuOptions(), (tMenuOptions*)(&this->menuPinkSlipCarOptionsPlayerTwo));
  (((tMenuOptions*)(&this->menuPinkSlipCarOptionsPlayerOne))->~tMenuOptions(), (tMenuOptions*)(&this->menuPinkSlipCarOptionsPlayerOne));
  (((tMenuOptions*)(&this->menuCarOptionsPlayerTwo))->~tMenuOptions(), (tMenuOptions*)(&this->menuCarOptionsPlayerTwo));
  (((tMenuOptions*)(&this->menuCarOptionsPlayerOne))->~tMenuOptions(), (tMenuOptions*)(&this->menuCarOptionsPlayerOne));
  (((tMenuOptions*)(&this->menuCarOptions))->~tMenuOptions(), (tMenuOptions*)(&this->menuCarOptions));
  (((tMenuItemLeftRightChoice*)(&(this->itemOpponentUpgrades)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemOpponentUpgrades)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemDamage2)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemDamage2)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemABS2)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemABS2)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemTransmission2)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemTransmission2)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemDamage)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemDamage)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemABS)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemABS)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemTransmission)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemTransmission)._base_tMenuItemLeftRightChoice));
  tListIterator_dtor(&this->iteratorOpponentUpgrades,2);
  tListIterator_dtor(&this->iteratorDamage,2);
  (((tListIteratorIndexed*)(&this->iteratorABS))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorABS));
  (((tListIteratorIndexed*)(&this->iteratorTransmission))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorTransmission));
  (((tMenuNFS4*)(&this->menuCarUpgrades))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuCarUpgrades));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPurchaseUpgrade3))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPurchaseUpgrade3));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPurchaseUpgrade2))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPurchaseUpgrade2));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPurchaseUpgrade1))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPurchaseUpgrade1));
  (((tMenuNFS4*)(&this->menuCarSeller))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuCarSeller));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSellCar))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSellCar));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemSellerCar))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemSellerCar));
  (((tListIteratorCar*)(&this->iteratorSellerCar))->~tListIteratorCar(), (tListIteratorCar*)(&this->iteratorSellerCar));
  (((tMenuNFS4*)(&this->menuCarDealer))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuCarDealer));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemDealerShowroom))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemDealerShowroom));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemBuyCar))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemBuyCar));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemDealerColor))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemDealerColor));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemDealerCar))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemDealerCar));
  (((tListIteratorCarColor*)(&this->iteratorDealerColor))->~tListIteratorCarColor(), (tListIteratorCarColor*)(&this->iteratorDealerColor));
  (((tListIteratorCar*)(&this->iteratorDealerCar))->~tListIteratorCar(), (tListIteratorCar*)(&this->iteratorDealerCar));
  (((tMenuNFS4*)(&this->menuGoToCarDealer))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuGoToCarDealer));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemGoToSellCar))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemGoToSellCar));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemGoToBuyCar))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemGoToBuyCar));
  (((tMenuNFS4TwoPlayer*)(&this->menuPlayerTwoPinkSlipCarSelect))->~tMenuNFS4TwoPlayer(), (tMenuNFS4TwoPlayer*)(&this->menuPlayerTwoPinkSlipCarSelect));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemPinkSlipCarP2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemPinkSlipCarP2));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerTwoPinkSlipRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerTwoPinkSlipRace));
  (((tMenuNFS4TwoPlayer*)(&this->menuPlayerOnePinkSlipCarSelect))->~tMenuNFS4TwoPlayer(), (tMenuNFS4TwoPlayer*)(&this->menuPlayerOnePinkSlipCarSelect));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemPinkSlipCarP1))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemPinkSlipCarP1));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerOnePinkSlipRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerOnePinkSlipRace));
  (((tListIteratorCar*)(&this->iteratorPinkSlipsCar))->~tListIteratorCar(), (tListIteratorCar*)(&this->iteratorPinkSlipsCar));
  (((tMenuNFS4TwoPlayer*)(&this->menuPlayerTwoGarage))->~tMenuNFS4TwoPlayer(), (tMenuNFS4TwoPlayer*)(&this->menuPlayerTwoGarage));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemGarageCarP2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemGarageCarP2));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerTwoGarageRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerTwoGarageRace));
  (((tMenuNFS4TwoPlayer*)(&this->menuPlayerOneGarage))->~tMenuNFS4TwoPlayer(), (tMenuNFS4TwoPlayer*)(&this->menuPlayerOneGarage));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemGarageCarP1))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemGarageCarP1));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerOneGarageRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerOneGarageRace));
  (((tMenuNFS4TwoPlayer*)(&this->menuPlayerTwoCarSelect))->~tMenuNFS4TwoPlayer(), (tMenuNFS4TwoPlayer*)(&this->menuPlayerTwoCarSelect));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemColorP2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemColorP2));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemCarP2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemCarP2));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerTwoRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerTwoRace));
  (((tMenuNFS4TwoPlayer*)(&this->menuPlayerOneCarSelect))->~tMenuNFS4TwoPlayer(), (tMenuNFS4TwoPlayer*)(&this->menuPlayerOneCarSelect));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemColorP1))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemColorP1));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemCarP1))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemCarP1));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerOneRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPlayerOneRace));
  (((tMenuNFS4*)(&this->menuHPDuelCarSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuHPDuelCarSelect));
  (((tMenuNFS4*)(&this->menuDuelCarSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuDuelCarSelect));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemOpponentCar))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemOpponentCar));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemGoToDuelBuyCar))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemGoToDuelBuyCar));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemColor2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemColor2));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemCar2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemCar2));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemDuelRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemDuelRace));
  (((tListIteratorCar*)(&this->iteratorOpponentCar))->~tListIteratorCar(), (tListIteratorCar*)(&this->iteratorOpponentCar));
  (((tMenuNFS4*)(&this->menuPostCarGarage))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuPostCarGarage));
  (((tMenuNFS4*)(&this->menuCarGarage))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuCarGarage));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemUpgradeCar))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemUpgradeCar));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemCarDealer))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemCarDealer));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemGarageCar))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemGarageCar));
  (((tListIteratorCar*)(&this->iteratorGarageCar))->~tListIteratorCar(), (tListIteratorCar*)(&this->iteratorGarageCar));
  (((tMenuNFS4*)(&this->menuSingleCarSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuSingleCarSelect));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemShowcase))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemShowcase));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemColor))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemColor));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemCar))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemCar));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemCarSelectRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemCarSelectRace));
  (((tListIteratorCarColor*)(&this->iteratorColor))->~tListIteratorCarColor(), (tListIteratorCarColor*)(&this->iteratorColor));
  (((tListIteratorCar*)(&this->iteratorCar1))->~tListIteratorCar(), (tListIteratorCar*)(&this->iteratorCar1));
  (((tMenuNFS4*)(&this->menuTrackInfo))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTrackInfo));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTrackInfoContinue))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTrackInfoContinue));
  (((tOptionsMenu*)(&this->menuTrackRecords))->~tOptionsMenu(), (tOptionsMenu*)(&this->menuTrackRecords));
  (((tMenuItemGoToMenuNFS4Button*)(&(this->menuTrackRecordsItem)._base_tMenuItemGoToMenuNFS4Button))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&(this->menuTrackRecordsItem)._base_tMenuItemGoToMenuNFS4Button));
  (((tMenuOptions*)(&this->menuTrackOptions))->~tMenuOptions(), (tMenuOptions*)(&this->menuTrackOptions));
  (((tMenuItemLeftRightChoice*)(&(this->itemLocalSpeech)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemLocalSpeech)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemTraffic)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemTraffic)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemWeather)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemWeather)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemTimeOfDay)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemTimeOfDay)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemTrackMirrored)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemTrackMirrored)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemTrackDirection)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemTrackDirection)._base_tMenuItemLeftRightChoice));
  (((tMenuItemLeftRightChoice*)(&(this->itemLaps)._base_tMenuItemLeftRightChoice))->~tMenuItemLeftRightChoice(), (tMenuItemLeftRightChoice*)(&(this->itemLaps)._base_tMenuItemLeftRightChoice));
  tListIterator_dtor(&this->iteratorLocalSpeech,2);
  (((tListIteratorIndexed*)(&this->iteratorTraffic))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorTraffic));
  (((tListIteratorIndexed*)(&this->iteratorWeather))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorWeather));
  (((tListIteratorIndexed*)(&this->iteratorTimeOfDay))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorTimeOfDay));
  (((tListIteratorIndexed*)(&this->iteratorTrackMirrored))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorTrackMirrored));
  (((tListIteratorIndexed*)(&this->iteratorTrackDirection))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorTrackDirection));
  (((tListIteratorIndexed*)(&this->iteratorLaps))->~tListIteratorIndexed(), (tListIteratorIndexed*)(&this->iteratorLaps));
  (((tMenuNFS4*)(&this->menuTestDriveTrackSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTestDriveTrackSelect));
  (((tMenuNFS4*)(&this->menuSingleTrackSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuSingleTrackSelect));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTrackRecords))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTrackRecords));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTrack))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTrack));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTrackContinue))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTrackContinue));
  (((tListIteratorTrack*)(&this->iteratorTrack))->~tListIteratorTrack(), (tListIteratorTrack*)(&this->iteratorTrack));
  (((tMenuNFS4*)(&this->menuPinkSlipsBestOfFive))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuPinkSlipsBestOfFive));
  (((tMenuNFS4*)(&this->menuPinkSlipsBestOfThree))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuPinkSlipsBestOfThree));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTrack5))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTrack5));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTrack4))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTrack4));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTrack3))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTrack3));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTrack2))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTrack2));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTrack1))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTrack1));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemPinkSlipsContinue))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemPinkSlipsContinue));
  (((tMenuNFS4*)(&this->menuPinkSlipSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuPinkSlipSelect));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemBestOfFive))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemBestOfFive));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemBestOfThree))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemBestOfThree));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemBestOfOne))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemBestOfOne));
  (((tMenuNFS4*)(&this->menuTwoPlayer))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTwoPlayer));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerPinkSlips))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerPinkSlips));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerHotPursuit))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerHotPursuit));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerDuel))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerDuel));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerTestDrive))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTwoPlayerTestDrive));
  (((tMenuNFS4*)(&this->menuSpecialEvent))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuSpecialEvent));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemSpecialEventSelect))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemSpecialEventSelect));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSpecialEventContinue))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSpecialEventContinue));
  (((tListIteratorTournament*)(&this->iteratorSpecialEvent))->~tListIteratorTournament(), (tListIteratorTournament*)(&this->iteratorSpecialEvent));
  (((tMenuNFS4*)(&this->menuTournament))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTournament));
  (((tMenuItemNFS4LeftRightChoice*)(&this->itemTournamentSelect))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->itemTournamentSelect));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTournamentContinue))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTournamentContinue));
  (((tListIteratorTournament*)(&this->iteratorTournament))->~tListIteratorTournament(), (tListIteratorTournament*)(&this->iteratorTournament));
  (((tMenuNFS4*)(&this->menuHotPursuit))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuHotPursuit));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemHotPursuitDuel))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemHotPursuitDuel));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemHotPursuitSolo))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemHotPursuitSolo));
  (((tMenuNFS4*)(&this->menuSingleRace))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuSingleRace));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSingleRaceFullGrid))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSingleRaceFullGrid));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSingleRaceDuel))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSingleRaceDuel));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSingleRaceSolo))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSingleRaceSolo));
  (((tMenuNFS4*)(&this->menuOnePlayer))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuOnePlayer));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerSpecialEvents))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerSpecialEvents));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerTournament))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerTournament));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerPursuit))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerPursuit));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerSingleRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerSingleRace));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerTestDrive))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemOnePlayerTestDrive));
  (((tMenuNFS4*)(&this->menuSkillLevel))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuSkillLevel));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSkillExpert))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSkillExpert));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSkillIntermediate))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSkillIntermediate));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSkillBeginner))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSkillBeginner));
  (((tMenuBlank*)(&this->menuTrophyInfo))->~tMenuBlank(), (tMenuBlank*)(&this->menuTrophyInfo));
  (((tMenuNFS4*)(&this->menuTrophyRoomSelect))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuTrophyRoomSelect));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemSETrophyRoom))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemSETrophyRoom));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemTournTrophyRoom))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemTournTrophyRoom));
  (((tMenuNFS4*)(&this->menuMain))->~tMenuNFS4(), (tMenuNFS4*)(&this->menuMain));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemMainOptions))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemMainOptions));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemMainTrophyRoom))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemMainTrophyRoom));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemMainTwoPlayerRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemMainTwoPlayerRace));
  (((tMenuItemGoToMenuNFS4Button*)(&this->itemMainOnePlayerRace))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->itemMainOnePlayerRace));
  if ((mode & 1) != 0) {
    __builtin_delete(this);
  }
  return;
}



/* ---- TransitionIsFinished  [FEMENUDEFS.CPP:?] ---- */
void * tBlankMenuItemGoToMenuNFS4Button::TransitionIsFinished()
{
  return (void *)0x1;
}

/* ---- Draw__32tBlankMenuItemGoToMenuNFS4Buttoniib [@0x800321C8] ---- */
void tBlankMenuItemGoToMenuNFS4Button::Draw(int x,int y,char flags)
{
  return;
}

/* ---- Draw__32tBlankMenuItemGoToMenuNFS4Buttonb [@0x800321D0] ---- */
void tBlankMenuItemGoToMenuNFS4Button::Draw(int arg1)
{
  return;
}

/* ---- tBlankMenuItemGoToMenuNFS4Button::dtor  [FEMENUDEFS.CPP:?] ---- */

tBlankMenuItemGoToMenuNFS4Button::~tBlankMenuItemGoToMenuNFS4Button()

{
  (((tMenuItemGoToMenuNFS4Button*)(&this->_base_tMenuItemGoToMenuNFS4Button))->~tMenuItemGoToMenuNFS4Button(), (tMenuItemGoToMenuNFS4Button*)(&this->_base_tMenuItemGoToMenuNFS4Button));
  return;
}



/* ---- TransitionIsFinished  [FEMENUDEFS.CPP:?] ---- */
void * tBlankMenuItemNFS4LeftRightChoice::TransitionIsFinished()
{
  return (void *)0x1;
}

/* ---- Draw__33tBlankMenuItemNFS4LeftRightChoiceiib [@0x80032200] ---- */
void tBlankMenuItemNFS4LeftRightChoice::Draw(int x,int y,char flags)
{
  return;
}

/* ---- tBlankMenuItemNFS4LeftRightChoice::dtor  [FEMENUDEFS.CPP:?] ---- */

tBlankMenuItemNFS4LeftRightChoice::~tBlankMenuItemNFS4LeftRightChoice()

{
  short i;
  int upgradeFlag;
  int fWinner;
  char string [80];
  tDialogYesNo RetryCancelDialog;
  short nBestCarIndex;
  
  (((tMenuItemNFS4LeftRightChoice*)(&this->_base_tMenuItemNFS4LeftRightChoice))->~tMenuItemNFS4LeftRightChoice(), (tMenuItemNFS4LeftRightChoice*)(&this->_base_tMenuItemNFS4LeftRightChoice));
  return;
}



/* end of femenudefs.cpp */
