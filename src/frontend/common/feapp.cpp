/* frontend/common/feapp.cpp -- RECONSTRUCTED (NFS4 FE application core; C++ TU)
 *   14 fns: tFEApplication ctor/dtor + dialog setup, FE main loop, video/movie cycling.
 *   Member defs; base ctors via init-lists; manual _vf vtable init.
 */
#include "feapp.h"

/* ---- FEApp.obj-OWNED globals -- DEFINED here (self-contained; .bss zero; types match the
   feapp_externs.h decls all FE TUs consume). FEApp = the global FE application pointer. ---- */
int             currentVideo;     /* FE play-movie index (SYM STAT; externed as shared int) */
int             gLargestUnused;   /* @0x800514b8  largest unused heap block (SYM u_long, extern "C" int) */
tFEApplication *FEApp;            /* @0x800514c0  global FE application pointer */


/* ---- tFEApplication::ctor  [FEAPP.CPP:89-95] SLD-VERIFIED ---- */

tFEApplication::tFEApplication()

{
  int i;
  tDialogMessageString *this_tDialogMessageString;
  tDialogMessageStringWithTimeout *this_tDialogMessageStringWithTimeout;
  tDialogHelp *this_tDialogHelp;
  tDialogNoInputMessage *this_tDialogNoInputMessage;
  
  this_tDialogMessageString = &this->messagePopup;
  this_tDialogHelp = &this->helpPopup;
  *(void **)&((this->messagePopup)._base_tDialogBase._base_tScreen._vf) = (void *)tDialogBase_vtable;
  (this->messagePopup)._base_tDialogBase.currentlyOn = 0;
  (this->messagePopup)._base_tDialogBase.reservedheight = 0;
  (this->messagePopup)._base_tDialogBase.MaxH = 0;
  (this->messagePopup)._base_tDialogBase.OffsetY = 0;
  (this->messagePopup)._base_tDialogBase.OffsetX = 0;
  (this->messagePopup)._base_tDialogBase.height = 0;
  (this->messagePopup)._base_tDialogBase.width = 0;
  (this->messagePopup)._base_tDialogBase.top = 0;
  (this->messagePopup)._base_tDialogBase.left = 0;
  (this->messagePopup)._base_tDialogBase.MaxW = 0x120;
  (this->messagePopup)._base_tDialogBase.specificPlayer = -1;
  (this->messagePopup)._base_tDialogBase.fDefault = 0;
  (this->messagePopup)._base_tDialogBase.timeOutTicks = 0;
  *(void **)&((this->messagePopup)._base_tDialogBase._base_tScreen._vf) = (void *)tDialogMessageString_vtable;
  (this->messagePopup).Centerit = 0;
  (this->messagePopup)._base_tDialogBase.fFullyOpen = 0;
  (this->messagePopup)._base_tDialogBase.timeOutTicks = 0;
  (this->messagePopup)._base_tDialogBase.fFadeText = 0x80;
  this_tDialogMessageStringWithTimeout = &this->MemCardDialog;
  *(void **)&((this->helpPopup)._base_tDialogBase._base_tScreen._vf) = (void *)tDialogBase_vtable;
  *(void **)&((this->helpPopup)._base_tDialogBase._base_tScreen._vf) = (void *)tDialogHelp_vtable;
  (this->helpPopup)._base_tDialogBase.currentlyOn = 0;
  (this->helpPopup)._base_tDialogBase.reservedheight = 0;
  (this->helpPopup)._base_tDialogBase.MaxH = 0;
  (this->helpPopup)._base_tDialogBase.OffsetY = 0;
  (this->helpPopup)._base_tDialogBase.OffsetX = 0;
  (this->helpPopup)._base_tDialogBase.height = 0;
  (this->helpPopup)._base_tDialogBase.width = 0;
  (this->helpPopup)._base_tDialogBase.top = 0;
  (this->helpPopup)._base_tDialogBase.left = 0;
  (this->helpPopup)._base_tDialogBase.MaxW = 0x120;
  (this->helpPopup)._base_tDialogBase.specificPlayer = -1;
  (this->helpPopup)._base_tDialogBase.fDefault = 0;
  (this->helpPopup)._base_tDialogBase.timeOutTicks = 0;
  (this->helpPopup).variant = -1;
  (this->helpPopup)._base_tDialogBase.timeOutTicks = 0x578;
  this_tDialogNoInputMessage = &this->NoInputMemCardDialog;
  /* @0x800130B8/BC/C0: three _vf stores to MemCardDialog (this+0x238): tDialogBase, tDialogMessageString,
   * then the FINAL = tDialogMessageStringWithTimeout vtable @0x80010098. The recon mis-decoded the absolute
   * VA 0x80010098 (0x80010000+0x98) as a runtime `bigBuf + 0x98` pointer, leaving _vf pointing at garbage
   * (wrong virtual dispatch). Adversarially verified: the 0x80010550 the audit suggested was helpPopup's
   * tDialogHelp vtable, mis-attributed (M10). */
  *(void **)&((this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogBase_vtable;
  *(void **)&((this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogMessageString_vtable;
  *(void **)&((this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogMessageStringWithTimeout_vtable;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.currentlyOn = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.reservedheight = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.MaxH = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.OffsetY = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.OffsetX = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.height = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.width = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.top = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.left = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.MaxW = 0x120;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.specificPlayer = -1;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.timeOutTicks = 0;
  (this->MemCardDialog)._base_tDialogMessageString.Centerit = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFullyOpen = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.timeOutTicks = 0;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFadeText = 0x80;
  (this->MemCardDialog)._base_tDialogMessageString._base_tDialogBase.timeOutTicks = 0x480;
  i = 0;
  *(void **)&((this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogBase_vtable;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.currentlyOn = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.reservedheight = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.MaxH = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.OffsetY = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.OffsetX = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.height = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.width = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.top = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.left = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.MaxW = 0x120;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.specificPlayer = -1;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fDefault = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.timeOutTicks = 0;
  *(void **)&((this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogMessageString_vtable;
  (this->NoInputMemCardDialog)._base_tDialogMessageString.Centerit = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFullyOpen = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.timeOutTicks = 0;
  (this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFadeText = 0x80;
  *(void **)&((this->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase._base_tScreen._vf) = (void *)tDialogNoInputMessage_vtable;
  i = 0;
  do {
    this->gotName[i] = 0;
    this->needName[i] = 0;
    this->speechToPlay[i] = -1;
    i = i + 1;
  } while (i < 2);
  return;
}



/* ---- tFEApplication::dtor  [FEAPP.CPP:101-102] SLD-VERIFIED ---- */

tFEApplication::~tFEApplication()

{
  
  return;
}



/* ---- tFEApplication::PerformMenuInitialization  [FEAPP.CPP:105-122] SLD-VERIFIED ---- */

void tFEApplication::PerformMenuInitialization()

{
  this->fCurrentMusic = 0;
  AudioMus_Volume((int)((u_int)(u_char)frontEnd.musicVolume * 0x23) >> 6);
  tDialogBase::InitializeClass();
  Clock_SystemStartUp();
  Draw_gDoVSync = 1;
  FETextRender_SetABR(0,false);
  return;
}



/* ---- tFEApplication::PerformMenuDestruction  [FEAPP.CPP:126-145] SLD-VERIFIED ---- */

void tFEApplication::PerformMenuDestruction()

{
  short i;
  tScreen *screen;
  
  Clock_SystemCleanUp();
  i = 0;
  do {
    screen = this->fCurrentScreen[i];
    if (screen != (tScreen *)0x0) {
      NFS4_VCALL0((*screen->_vf)[7].pfn,
                  (u_char *)screen + (*screen->_vf)[7].delta);
    }
    this->fCurrentScreen[i] = (tScreen *)0x0;
    i = i + 1;
  } while (i < 2);
  AudioMus_StopSong(1000);
  Draw_gDoVSync = 0;
  FETextRender_SetABR(0,false);
  return;
}



/* ---- tFEApplication::DrawHelpIcons  [FEAPP.CPP:151-219] SLD-VERIFIED ---- */

void tFEApplication::DrawHelpIcons()

{
  bool bVar1;
  char *pcVar2;
  u_int uVar3;
  tMenu *this_tMenu_l52;
  int iVar4;
  short x;
  int i;
  int y;
  int Col;
  tDrawShapeExtended flags;
  char string [12];
  char string2 [2];
  
  x = 0xe;
  flags.tint[0] = 0x786e14;
  y = screenheight + -0x19;
  if ((this->fCurrentMenu[0] == (tMenu *)0x0) || (this->fCurrentMenu[0]->VertHelp == 0)) {
    if (((gPadinfo.buf[0].nopad == '\0') && (gPadinfo.buf[0].ID != '#')) ||
       ((gPadinfo.buf[4].nopad == '\0' && (gPadinfo.buf[4].ID != '#')))) {
      DrawShapeExtended(0x35,0x18,x,y,0,0,&flags);
      x = 0x1c;
    }
    if ((gPadinfo.buf[0].ID == '#') || (gPadinfo.buf[4].ID == '#')) {
      DrawShapeExtended(0x36,0x18,x,y,0,0,&flags);
      x = x + 0xf;
    }
    this_tMenu_l52 = (tMenu *)TextSys_Word(0xfc);
    FETextRender_FullTextRGB((char *)this_tMenu_l52,x,(short)((u_int)(y * 0x10000) >> 0x10),0x786e14,'\0',0
              );
    pcVar2 = TextSys_Word(0xfc);
    iVar4 = textpixels(pcVar2);
    pcVar2 = TextSys_Word(0xfc);
    uVar3 = strlen(pcVar2);
    x = x + 5 + ((short)iVar4 - (short)uVar3);
    bVar1 = false;
    if ((this->fCurrentMenu[0]->fOptionsMenu != (tMenu *)0x0) ||
       ((this->fCurrentMenu[1] != (tMenu *)0x0 &&
        (this->fCurrentMenu[1]->fOptionsMenu != (tMenu *)0x0)))) {
      bVar1 = true;
    }
    if (bVar1) {
      if (((gPadinfo.buf[0].nopad == '\0') && (gPadinfo.buf[0].ID != '#')) ||
         ((gPadinfo.buf[4].nopad == '\0' && (gPadinfo.buf[4].ID != '#')))) {
        DrawShapeExtended(0x37,0x18,x,y,0,0,&flags);
        x = x + 0xe;
      }
      if ((gPadinfo.buf[0].ID == '#') || (gPadinfo.buf[4].ID == '#')) {
        DrawShapeExtended(0x38,0x18,x,y,0,0,&flags);
        x = x + 0xf;
      }
      pcVar2 = TextSys_Word(0xfd);
      FETextRender_FullTextRGB(pcVar2,x,(short)((u_int)(y * 0x10000) >> 0x10),0x786e14,'\0',0);
    }
  }
  else {
    string2[1] = '\0';
    pcVar2 = TextSys_Word(0xfc);
    sprintf(string,pcVar2);
    i = strlen(string);
    while (i = i - 1, -1 < (int)i) {
      x = (short)y;
      y = y + -8;
      string2[0] = string[i];
      FETextRender_FullTextRGB(string2,0xe,x,0x786e14,'\0',0);
    }
    if (((gPadinfo.buf[0].nopad == '\0') && (gPadinfo.buf[0].ID != '#')) ||
       ((gPadinfo.buf[4].nopad == '\0' && (gPadinfo.buf[4].ID != '#')))) {
      DrawShapeExtended(0x35,0x18,0xe,y,0,0,&flags);
    }
    if ((gPadinfo.buf[0].ID == '#') || (gPadinfo.buf[4].ID == '#')) {
      DrawShapeExtended(0x36,0x18,0xd,y + -9,0,0,&flags);
    }
  }
  return;
}



/* ---- tFEApplication::Redraw  [FEAPP.CPP:225-395] SLD-VERIFIED ---- */

void tFEApplication::Redraw()

{
  int iVar1;
  int musThresh;
  DRAWENV *drenv;
  int ti8;
  int ti2;
  int freeHeap_or_buf;
  __vtbl_ptr_type (*pa_Var2) [11];
  int pkt_addr24_p2;
  tMenuItem *curItem;
  int pkt_addr24_p1;
  tMenu *menu_per_player;
  tMenu *parentMenu;
  tMenu *curMenu;
  tMenu *ptVar2;
  int i;
  short height;
  char buffer [32];
  PSX_RECT r;
  tMenuCommand emptycommand;
  tInputKeyType JustOneToPass;
  tInputKeyType JustOneToPass_l85;
  u_char saveFPlayer;
  u_char bVar2;
  u_char *daprim;
  tGlobalMenuDefs *globalMenuDefs;
  u_char *prev_pkt_p1;
  
  saveFPlayer = this->fPlayer;
  FeAudio_systemtask(0);
  Draw_StartFrameRender();
  Draw_StartRenderingView(Draw_gPlayer1View);
  iVar1 = largestunused();
  sprintf(buffer,(char *)(bigBuf + 0x44),iVar1);
  FETextRender_FullText(buffer,0x100,0xd7,textType_FramedInfo,textState_Selected,0);
  iVar1 = AudioMus_Buffered();
  musThresh = AudioMus_Threshold();
  sprintf(buffer,(char *)(bigBuf + 0x48),iVar1,musThresh);
  FETextRender_FullText(buffer,0x10,0xd7,textType_FramedInfo,textState_Hilighted,0);
  drenv = Draw_GetDRAWENV(Draw_gPlayer1View,gFlip);
  if (this->fCurrentMenu[1] == (tMenu *)0x0) {
    height = (short)screenheight;
  }
  else {
    height = (short)((u_int)(screenheight - (screenheight >> 0x1f)) >> 1);
  }
  tDialogBase::DrawAllDialogs();
  this->DrawHelpIcons();
  globalMenuDefs = menuDefs;
  if ((gPadinfo.buf[0].nopad == '\0') && (gPadinfo.buf[4].nopad == '\0')) {
    (menuDefs->itemMainTwoPlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags
         = (menuDefs->itemMainTwoPlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags & 0xfffffffe;
  }
  else {
    (menuDefs->itemMainTwoPlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags
         = (menuDefs->itemMainTwoPlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags | 1;
    JustOneToPass = kInput_KeyType_Up;
    if ((tMenuItemGoToMenuNFS4Button *)
        this->fCurrentMenu[0]->fItemList[this->fCurrentMenu[0]->fCurrentItem] ==
        &globalMenuDefs->itemMainTwoPlayerRace) {
      (&globalMenuDefs->menuMain)->ProcessInput(kPlayerOne,JustOneToPass,emptycommand);
    }
  }
  globalMenuDefs = menuDefs;
  if (gPadinfo.buf[0].nopad == '\0') {
    (menuDefs->itemMainOnePlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags
         = (menuDefs->itemMainOnePlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags & 0xfffffffe;
  }
  else {
    (menuDefs->itemMainOnePlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags
         = (menuDefs->itemMainOnePlayerRace)._base_tMenuItemGoToMenuButton._base_tMenuItemInteractive._base_tMenuItem.fFlags | 1;
    curItem = this->fCurrentMenu[0]->fItemList[this->fCurrentMenu[0]->fCurrentItem];
    JustOneToPass_l85 = kInput_KeyType_Down;
    if ((tGlobalMenuDefs *)curItem == globalMenuDefs) {
      (&globalMenuDefs->menuMain)->ProcessInput(kPlayerOne,JustOneToPass_l85,emptycommand);
    }
  }
  daprim = Render_gPacketPtr;
  prev_pkt_p1 = Render_gPalettePtr;
  i = 1;
  r.x = 0;
  r.y = drenv->clip.y;
  r.w = 0x200;
  r.h = (short)screenheight;
  *(u_int *)Render_gPacketPtr =
       *(u_int *)Render_gPacketPtr & 0xff000000 | *(u_int *)Render_gPalettePtr & 0xffffff;
  pkt_addr24_p1 = (u_int)((intptr)Render_gPacketPtr & 0xffffffU);
  Render_gPacketPtr = Render_gPacketPtr + 0xc;
  *(u_int *)prev_pkt_p1 = *(u_int *)prev_pkt_p1 & 0xff000000 | pkt_addr24_p1;
  SetDrawArea((DR_AREA *)daprim,&r);
  do {
    this->fPlayer = (char)i;
    this->fYOffset = ((u_short)i & 0xff) * height;
    menu_per_player = this->fCurrentMenu[i & 0xff];
    if (menu_per_player != (tMenu *)0x0) {
      NFS4_VCALL0((*menu_per_player->_vf)[10].pfn,
                  (u_char *)menu_per_player + (*menu_per_player->_vf)[10].delta);
    }
    parentMenu = this->fParentMenu[(u_char)this->fPlayer];
    if (parentMenu != (tMenu *)0x0) {
      NFS4_VCALL0((*parentMenu->_vf)[10].pfn,
                  (u_char *)parentMenu + (*parentMenu->_vf)[10].delta);
    }
    if (this->fCurrentScreen[(u_char)this->fPlayer] != (tScreen *)0x0) {
      (this->fCurrentScreen[(u_char)this->fPlayer])->UpdateTransition();
    }
    curMenu = this->fCurrentMenu[(u_char)this->fPlayer];
    if ((curMenu != (tMenu *)0x0) &&
       (ti8 = NFS4_VCALL0((*curMenu->_vf)[8].pfn,
                          (u_char *)curMenu + (*curMenu->_vf)[8].delta),
       ti8 != 0)) {
      curMenu = this->fCurrentMenu[(u_char)this->fPlayer];
      NFS4_VCALL0((*curMenu->_vf)[9].pfn,
                  (u_char *)curMenu + (*curMenu->_vf)[9].delta);
    }
    if (this->fCurrentScreen[(u_char)this->fPlayer] != (tScreen *)0x0) {
      (this->fCurrentScreen[(u_char)this->fPlayer])->Draw(false);
    }
    ptVar2 = this->fCurrentMenu[(u_char)this->fPlayer];
    if (ptVar2 != (tMenu *)0x0) {
      bVar2 = false;
      if (this->waitingForOtherPlayer[(u_char)this->fPlayer] == 0) {
Redraw_vtableCallback9:
        pa_Var2 = this->fCurrentMenu[(u_char)this->fPlayer]->_vf;
        NFS4_VCALL0((*pa_Var2)[9].pfn,
                    (u_char *)this->fCurrentMenu[(u_char)this->fPlayer] +
                    (*pa_Var2)[9].delta);
      }
      else {
        ti2 = NFS4_VCALL0((*ptVar2->_vf)[7].pfn,
                          (u_char *)ptVar2 + (*ptVar2->_vf)[7].delta);
        if (ti2 == 0) {
          curMenu = this->fCurrentMenu[(u_char)this->fPlayer];
          freeHeap_or_buf =
               NFS4_VCALL0((*curMenu->_vf)[8].pfn,
                           (u_char *)curMenu + (*curMenu->_vf)[8].delta);
          bVar2 = freeHeap_or_buf == 0;
        }
        if ((bool)bVar2) goto Redraw_vtableCallback9;
      }
      ptVar2 = this->fParentMenu[(u_char)this->fPlayer];
      if (ptVar2 != (tMenu *)0x0) {
        NFS4_VCALL0((*ptVar2->_vf)[9].pfn,
                    (u_char *)ptVar2 + (*ptVar2->_vf)[9].delta);
      }
    }
    if (this->fCurrentScreen[(u_char)this->fPlayer] != (tScreen *)0x0) {
      (this->fCurrentScreen[(u_char)this->fPlayer])->Draw(true);
    }
    daprim = Render_gPacketPtr;
    prev_pkt_p1 = Render_gPalettePtr;
    r.x = 0;
    r.y = drenv->clip.y + this->fYOffset;
    r.w = 0x200;
    *(u_int *)Render_gPacketPtr =
         *(u_int *)Render_gPacketPtr & 0xff000000 | *(u_int *)Render_gPalettePtr & 0xffffff;
    pkt_addr24_p2 = (u_int)((intptr)Render_gPacketPtr & 0xffffffU);
    Render_gPacketPtr = Render_gPacketPtr + 0xc;
    *(u_int *)prev_pkt_p1 = *(u_int *)prev_pkt_p1 & 0xff000000 | pkt_addr24_p2;
    r.h = height;
    SetDrawArea((DR_AREA *)daprim,&r);
    i = i - 1;
    if (i * 0x10000 < 0) {
      this->fPlayer = saveFPlayer;
      Draw_StopRenderingView(Draw_gPlayer1View);
      Draw_StopFrameRender();
      return;
    }
  } while( true );
}



/* ---- tFEApplication::UpdateMusic  [FEAPP.CPP:404-417] SLD-VERIFIED ---- */

void tFEApplication::UpdateMusic()

{
  u_int uVar1;
  
  AudioMus_Volume((int)((u_int)(u_char)frontEnd.musicVolume * 0x23) >> 6);
  uVar1 = this->fCurrentMusic;
  if ((uVar1 & 0x1000) == 0) {
    if ((uVar1 & 0x2000) == 0) {
      if ((uVar1 & 0x4000) == 0) {
        if ((uVar1 & 0x8000) == 0) {
          AudioMus_StopSong(1000);
        }
        else {
          AudioMus_PlaySong((char *)(bigBuf + 0x6c))
          ;
        }
      }
      else {
        AudioMus_PlaySong((char *)(bigBuf + 0x60));
      }
    }
    else {
      AudioMus_PlaySong((char *)(bigBuf + 0x58));
    }
  }
  else {
    AudioMus_PlaySong((char *)(bigBuf + 0x50));
  }
  return;
}



/* ---- tFEApplication::SetMenu  [FEAPP.CPP:422-448] SLD-VERIFIED ---- */

void tFEApplication::SetMenu(short i,tMenu *menu)

{
  u_int uVar1;
  int transitionFinished;
  tMenu *currentMenu;
  
  if (menu != this->fCurrentMenu[i]) {
    if ((i == 0) && (uVar1 = menu->fFlags & 0xf000, uVar1 != this->fCurrentMusic)) {
      this->fCurrentMusic = uVar1;
      this->UpdateMusic();
    }
    transitionFinished = NFS4_VCALL0((*menu->_vf)[8].pfn,
                                     (u_char *)menu + (*menu->_vf)[8].delta);
    if (transitionFinished == 1) {
      this->fTransitionToMenu[i] = menu;
    }
    else {
      currentMenu = this->fCurrentMenu[i];
      this->fTransitionToMenu[i] = menu;
      if ((currentMenu != (tMenu *)0x0) && (menu != (tMenu *)0x0)) {
        NFS4_VCALL0((*currentMenu->_vf)[5].pfn,
                    (u_char *)currentMenu + (*currentMenu->_vf)[5].delta);
      }
    }
    this->SetScreen(i,menu->fScreen);
  }
  return;
}



/* ---- tFEApplication::SetScreen  [FEAPP.CPP:453-458] SLD-VERIFIED ---- */

void tFEApplication::SetScreen(short i,tScreen *screen)

{
  tScreen *currentScreen;
  
  currentScreen = this->fCurrentScreen[i];
  if (((screen != currentScreen) &&
      (this->fTransitionToScreen[i] = screen, currentScreen != (tScreen *)0x0))
     && (screen != (tScreen *)0x0)) {
    currentScreen->TransitionOff(kScreen_TransitionTypeScreen,(tMenu *)0x0);
  }
  return;
}



/* ---- tFEApplication::DisplayHelp  [FEAPP.CPP:463-479] SLD-VERIFIED ---- */

void tFEApplication::DisplayHelp(short variant)

{
  tDialogHelp *this_tDialogHelp;
  
  this_tDialogHelp = &this->helpPopup;
  (this->helpPopup).variant = variant;
  (&this_tDialogHelp->_base_tDialogBase)->Display();
  return;
}



/* ---- tFEApplication::RunDemoVideo  [FEAPP.CPP:483-554] SLD-VERIFIED ---- */

void tFEApplication::RunDemoVideo()

{
  bool bVar1;
  __vtbl_ptr_type (*pa_Var2) [11];
  int iVar3;
  __vtbl_ptr_type (*pa_Var4) [10];
  char buffer [40];
  
  if ((tMenuNFS4 *)this->fCurrentMenu[0] == &menuDefs->menuMain) {
    AudioMus_StopSong(0x78);
    FeAudio_systemtask(0);
    pa_Var2 = this->fCurrentMenu[0]->_vf;
    NFS4_VCALL0((*pa_Var2)[5].pfn,
                (u_char *)this->fCurrentMenu[0] + (*pa_Var2)[5].delta);
    (this->fCurrentScreen[0])->TransitionOff(kScreen_TransitionTypeScreen,(tMenu *)0x0);
    while( true ) {
      pa_Var2 = this->fCurrentMenu[0]->_vf;
      bVar1 = false;
      iVar3 = NFS4_VCALL0((*pa_Var2)[7].pfn,
                          (u_char *)this->fCurrentMenu[0] + (*pa_Var2)[7].delta);
      if ((iVar3 == 0) ||
         (pa_Var4 = this->fCurrentScreen[0]->_vf,
         iVar3 = NFS4_VCALL0((*pa_Var4)[8].pfn,
                             (u_char *)this->fCurrentScreen[0] + (*pa_Var4)[8].delta),
         iVar3 == 0)) {
        bVar1 = true;
      }
      if (!bVar1) break;
      this->Redraw();
      FeAudio_systemtask(0);
    }
    pa_Var4 = this->fCurrentScreen[0]->_vf;
    NFS4_VCALL0((*pa_Var4)[7].pfn,
                (u_char *)this->fCurrentScreen[0] + (*pa_Var4)[7].delta);
    Audio_FECleanUp();
    Audio_DeInitDriver();
    PSXFront_FreeDrawMemory();
    FeTools_deinit();
    FreeHelpShapeCluts();
    gLargestUnused = largestunused();
    play_movie((char)currentVideo + 1U);
    gLargestUnused = largestunused();
    PSXFront_AllocateDrawMemory();
    FeTools_init();
    tScreen::DisplayLoadingText();
    Audio_InitDriver(0xd800,0x18000);
    AudioCmn_LoadFESamples();
    LoadAllHelpShapes();
    this->UpdateMusic();
    AudioMus_Volume((int)((u_int)(u_char)frontEnd.musicVolume * 0x23) >> 6);
    gLargestUnused = largestunused();
    pa_Var2 = this->fCurrentMenu[0]->_vf;
    NFS4_VCALL0((*pa_Var2)[2].pfn,
                (u_char *)this->fCurrentMenu[0] + (*pa_Var2)[2].delta);
    pa_Var4 = this->fCurrentScreen[0]->_vf;
    NFS4_VCALL0((*pa_Var4)[6].pfn,
                (u_char *)this->fCurrentScreen[0] + (*pa_Var4)[6].delta);
    pa_Var2 = this->fCurrentMenu[0]->_vf;
    NFS4_VCALL0((*pa_Var2)[6].pfn,
                (u_char *)this->fCurrentMenu[0] + (*pa_Var2)[6].delta);
    (this->fCurrentScreen[0])->TransitionOn(kScreen_TransitionTypeScreen,(tMenu *)0x0);
    currentVideo = (currentVideo + 1) % 3;
  }
  return;
}



/* ---- tFEApplication::MainLoop  [FEAPP.CPP:560-985] SLD-VERIFIED ---- */

tAppCommand tFEApplication::MainLoop(tMenu *newMenu)

{
  bool bVar1;
  bool needToSetChildMenu;
  bool doRedraw;
  int iVar4;
  tFEApplication *ptVar5;
  tFEApplication *ptVar6;
  u_char bVar7;
  char cVar8;
  short sVar9;
  int iVar10;
  __vtbl_ptr_type (*pa_Var11) [11];
  tMenu *this_tMenu_l92;
  __vtbl_ptr_type (*pa_Var12) [10];
  tInputKeyType debounce;
  tInputKeyType tVar13;
  tDialogBase *dialog;
  char *pcVar15;
  char *pcVar16;
  tMenu *ptVar17;
  tScreen *ptVar18;
  tDialogBase *this_tDialogBase_l181;
  tMenu *this_tMenu_l139;
  u_char wasSubMenu;
  tInputKeyType *ptVar19;
  tDialogMessageString *this_tDialogMessageString_l311;
  u_long ticks_l351;
  int player;
  PinkSlipsErrorCode err;
  short i;
  tPlayer inputStartPlayer;
  tPlayer inputEndPlayer;
  u_long ticksAtLastInput [2];
  char string [80];
  tMenuCommand command [2];
  tInputKeyType keyVal [2];
  tCarInfo carInfo;
  short stackBackupPin;
  u_long tick;
  int demoLoopLastInputTick;
  
  stackBackupPin = -1;
  needToSetChildMenu = false;
  memset(ticksAtLastInput,0,8);
  this->fInputPlayer = '\0';
  this->PerformMenuInitialization();
  demoLoopLastInputTick = ticks;
  gFlip = 0;
  this->fPlayer = '\0';
  do {
    this->backDepth[(u_char)this->fPlayer] = 0;
    this->fCurrentMenu[(u_char)this->fPlayer] = (tMenu *)0x0;
    this->fCurrentScreen[(u_char)this->fPlayer] = (tScreen *)0x0;
    this->fTransitionToMenu[(u_char)this->fPlayer] = (tMenu *)0x0;
    this->fTransitionToScreen[(u_char)this->fPlayer] = (tScreen *)0x0;
    this->waitingForOtherPlayer[(u_char)this->fPlayer] = 0;
    this->fLastKeyPressed[(u_char)this->fPlayer] = kInput_KeyType_NoKey;
    this->fParentMenu[(u_char)this->fPlayer] = (tMenu *)0x0;
    bVar7 = this->fPlayer + 1;
    this->fPlayer = bVar7;
  } while (bVar7 < 2);
  this->SetMenu(0,newMenu);
  do {
    iVar4 = ticks;
    doRedraw = true;
    this->fPlayer = '\0';
    while ((u_char)this->fPlayer < 2) {
      if (this->fTransitionToMenu[(u_char)this->fPlayer] != (tMenu *)0x0) {
        ptVar17 = this->fCurrentMenu[(u_char)this->fPlayer];
        wasSubMenu = 0;
        if (ptVar17 != (tMenu *)0x0) {
          iVar10 = NFS4_VCALL0((*ptVar17->_vf)[7].pfn,
                               (u_char *)ptVar17 + (*ptVar17->_vf)[7].delta);
          if ((iVar10 != 0) &&
             (ptVar18 = this->fCurrentScreen[(u_char)this->fPlayer], ptVar18 != (tScreen *)0x0)) {
            iVar10 = NFS4_VCALL0((*ptVar18->_vf)[8].pfn,
                                 (u_char *)ptVar18 + (*ptVar18->_vf)[8].delta);
            wasSubMenu = (u_int)(iVar10 != 0);
          }
          if (wasSubMenu == 0) goto MainLoop_subMenuDetect;
          ptVar17 = this->fCurrentMenu[(u_char)this->fPlayer];
          wasSubMenu = 0;
          if (ptVar17 != (tMenu *)0x0) {
            wasSubMenu =
                 NFS4_VCALL0((*ptVar17->_vf)[8].pfn,
                             (u_char *)ptVar17 + (*ptVar17->_vf)[8].delta);
          }
        }
        pa_Var11 = this->fTransitionToMenu[(u_char)this->fPlayer]->_vf;
        iVar10 = NFS4_VCALL0((*pa_Var11)[8].pfn,
                             (u_char *)this->fTransitionToMenu[(u_char)this->fPlayer] +
                             (*pa_Var11)[8].delta);
        if (iVar10 == 0) {
          this->fParentMenu[(u_char)this->fPlayer] = (tMenu *)0x0;
        }
        else {
          this->fParentMenu[(u_char)this->fPlayer] = this->fCurrentMenu[(u_char)this->fPlayer];
        }
        this->fCurrentMenu[(u_char)this->fPlayer] = this->fTransitionToMenu[(u_char)this->fPlayer];
        pa_Var11 = this->fCurrentMenu[(u_char)this->fPlayer]->_vf;
        NFS4_VCALL0((*pa_Var11)[2].pfn,
                    (u_char *)this->fCurrentMenu[(u_char)this->fPlayer] +
                    (*pa_Var11)[2].delta);
        this->fTransitionToMenu[(u_char)this->fPlayer] = (tMenu *)0x0;
        if ((wasSubMenu == 0) || (this->fTransitionToScreen[0] != (tScreen *)0x0)) {
          pa_Var11 = this->fCurrentMenu[(u_char)this->fPlayer]->_vf;
          NFS4_VCALL0((*pa_Var11)[6].pfn,
                      (u_char *)this->fCurrentMenu[(u_char)this->fPlayer] +
                      (*pa_Var11)[6].delta);
          if (needToSetChildMenu) {
            this_tMenu_l92 = this->fCurrentMenu[(u_char)this->fPlayer];
            needToSetChildMenu = false;
            this->SetMenu(1,this_tMenu_l92->fChildMenu);
          }
        }
        else {
          doRedraw = false;
          this->backDepth[(u_char)this->fPlayer] = this->backDepth[(u_char)this->fPlayer] + -1;
        }
        demoLoopLastInputTick = ticks;
      }
MainLoop_subMenuDetect:
      wasSubMenu = (u_int)(u_char)this->fPlayer;
      if (wasSubMenu == 1) {
        ptVar17 = this->fCurrentMenu[1];
        if ((((ptVar17 != (tMenu *)0x0) &&
             (iVar10 = NFS4_VCALL0((*ptVar17->_vf)[7].pfn,
                                   (u_char *)ptVar17 + (*ptVar17->_vf)[7].delta),
             iVar10 != 0)) && ((int)((u_int)(u_short)stackBackupPin << 0x10) < 0)) &&
           ((ptVar17 = this->fParentMenu[(u_char)this->fPlayer], ptVar17 == (tMenu *)0x0 ||
            (iVar10 = NFS4_VCALL0((*ptVar17->_vf)[7].pfn,
                                  (u_char *)ptVar17 + (*ptVar17->_vf)[7].delta),
            iVar10 != 0)))) {
          this->fCurrentMenu[(u_char)this->fPlayer] = (tMenu *)0x0;
          ptVar18 = this->fCurrentScreen[(u_char)this->fPlayer];
          if (ptVar18 != (tScreen *)0x0) {
            NFS4_VCALL0((*ptVar18->_vf)[7].pfn,
                        (u_char *)ptVar18 + (*ptVar18->_vf)[7].delta);
          }
          this->fCurrentScreen[(u_char)this->fPlayer] = (tScreen *)0x0;
        }
        wasSubMenu = (u_int)(u_char)this->fPlayer;
      }
      if (this->fTransitionToScreen[wasSubMenu] != (tScreen *)0x0) {
        ptVar18 = this->fCurrentScreen[wasSubMenu];
        if (ptVar18 != (tScreen *)0x0) {
          iVar10 = NFS4_VCALL0((*ptVar18->_vf)[8].pfn,
                               (u_char *)ptVar18 + (*ptVar18->_vf)[8].delta);
          if ((iVar10 == 0) || (this->fTransitionToMenu[(u_char)this->fPlayer] != (tMenu *)0x0))
          goto MainLoop_perPlayerFlagCheck;
          ptVar18 = this->fCurrentScreen[(u_char)this->fPlayer];
          if (ptVar18 != (tScreen *)0x0) {
            NFS4_VCALL0((*ptVar18->_vf)[7].pfn,
                        (u_char *)ptVar18 + (*ptVar18->_vf)[7].delta);
          }
        }
        this->fCurrentScreen[(u_char)this->fPlayer] = this->fTransitionToScreen[(u_char)this->fPlayer];
        gLargestUnused = largestunused();
        pa_Var12 = this->fCurrentScreen[(u_char)this->fPlayer]->_vf;
        NFS4_VCALL0((*pa_Var12)[6].pfn,
                    (u_char *)this->fCurrentScreen[(u_char)this->fPlayer] +
                    (*pa_Var12)[6].delta);
        this->fTransitionToScreen[(u_char)this->fPlayer] = (tScreen *)0x0;
        (this->fCurrentScreen[(u_char)this->fPlayer])->TransitionOn(kScreen_TransitionTypeScreen,
                   (tMenu *)0x0);
      }
MainLoop_perPlayerFlagCheck:
      bVar1 = false;
      if (this->fCurrentMenu[(u_char)this->fPlayer] != (tMenu *)0x0) {
        inputStartPlayer = (tPlayer)(u_char)this->fPlayer;
        wasSubMenu = this->fCurrentMenu[(u_char)this->fPlayer]->fFlags;
        if (((wasSubMenu & 0x10) != 0) ||
           ((frontEnd.gameMode == '\x01' && ((wasSubMenu & 8) == 0)))) {
          bVar1 = true;
        }
        inputEndPlayer = inputStartPlayer;
        if (bVar1) {
          inputStartPlayer = kPlayerOne;
          inputEndPlayer = kPlayerTwo;
        }
        this_tMenu_l139 = this->fCurrentMenu[(u_char)this->fPlayer];
        wasSubMenu = this_tMenu_l139->fFlags;
        if ((wasSubMenu & 0x20) != 0) {
          inputStartPlayer = (tPlayer)(u_char)this->fInputPlayer;
          inputEndPlayer = inputStartPlayer;
        }
        if ((wasSubMenu & 0x40) != 0) {
          inputEndPlayer = kPlayerOne;
          inputStartPlayer = kPlayerOne;
        }
        if ((wasSubMenu & 0x80) != 0) {
          inputEndPlayer = kPlayerTwo;
          inputStartPlayer = kPlayerTwo;
        }
        bVar1 = false;
        if (((this_tMenu_l139 != (tMenu *)0x0) &&
            (iVar10 = NFS4_VCALL0((*this_tMenu_l139->_vf)[7].pfn,
                                  (u_char *)this_tMenu_l139 +
                                  (*this_tMenu_l139->_vf)[7].delta), iVar10 != 0)) &&
           (ptVar18 = this->fCurrentScreen[(u_char)this->fPlayer], ptVar18 != (tScreen *)0x0)) {
          iVar10 = NFS4_VCALL0((*ptVar18->_vf)[8].pfn,
                               (u_char *)ptVar18 + (*ptVar18->_vf)[8].delta);
          bVar1 = iVar10 != 0;
        }
        if (bVar1) {
          pa_Var11 = this->fCurrentMenu[(u_char)this->fPlayer]->_vf;
          debounce = (tInputKeyType)NFS4_VCALL0((*pa_Var11)[4].pfn,
                                  (u_char *)this->fCurrentMenu[(u_char)this->fPlayer] +
                                  (*pa_Var11)[4].delta);
i = inputStartPlayer;
          MainLoop_perPlayerInputTop:
          sVar9 = (short)i;
          i = (tPlayer)sVar9;
          if (inputEndPlayer < i) goto MainLoop_nextPlayer;
          command[i].type = kMenu_Command_None;
          tVar13 = FEInput_GetKeyFromPlayer((tPlayer)i,(long)debounce);
          ptVar19 = keyVal + i;
          *ptVar19 = tVar13;
          if (tVar13 != kInput_KeyType_NoKey) {
            this->fInputPlayer = (char)i;
          }
          if ((0xf < ticks - ticksAtLastInput[i]) ||
             ((debounce & *ptVar19) == kInput_KeyType_NoKey)) {
            this->fLastKeyPressed[i] = *ptVar19;
          }
          if (keyVal[i] != kInput_KeyType_NoKey) {
            dialog = tDialogBase::GetTopMostDialog();
            demoLoopLastInputTick = iVar4;
            ticksAtLastInput[i] = iVar4;
            if ((keyVal[i] == kInput_KeyType_Circle) &&
                ((this->helpPopup)._base_tDialogBase.currentlyOn != 0)) {
              keyVal[i] = kInput_KeyType_AlreadyProcessed;
              (&(this->helpPopup)._base_tDialogBase)->Hide();
            }
            if (dialog != (tDialogBase *)0x0) {
              iVar10 = (int)sVar9;
              ptVar19 = keyVal + iVar10;
              if (*ptVar19 != kInput_KeyType_Circle) {
                NFS4_VCALL_INT_PTR_PTR((*dialog->_base_tScreen._vf)[9].pfn,
                          (u_char *)dialog + (*dialog->_base_tScreen._vf)[9].delta,
                          iVar10,ptVar19,command + iVar10);
              }
            }
            ptVar18 = this->fCurrentScreen[(u_char)this->fPlayer];
            if (ptVar18 != (tScreen *)0x0) {
              iVar10 = (int)sVar9;
              NFS4_VCALL_INT_PTR_PTR((*ptVar18->_vf)[9].pfn,
                        (u_char *)ptVar18 + (*ptVar18->_vf)[9].delta,iVar10,
                        keyVal + iVar10,command + iVar10);
            }
            iVar10 = (int)sVar9;
            ptVar19 = keyVal + iVar10;
            if (*ptVar19 != kInput_KeyType_AlreadyProcessed) {
              pa_Var11 = this->fCurrentMenu[(u_char)this->fPlayer]->_vf;
              NFS4_VCALL_INT_PTR_PTR((*pa_Var11)[3].pfn,
                        (u_char *)this->fCurrentMenu[(u_char)this->fPlayer] +
                         (*pa_Var11)[3].delta,iVar10,ptVar19,command + iVar10);
            }
          }
          iVar10 = command[i].type;
          if (iVar10 == 0) goto switchD_80014c34_default;
          switch(iVar10) {
          case 1:
            AudioCmn_PlayFESFX(0);
            wasSubMenu = (u_int)(u_char)this->fPlayer;
            this->backList[wasSubMenu][this->backDepth[wasSubMenu]] =
                 this->fCurrentMenu[wasSubMenu];
            this->backDepth[(u_char)this->fPlayer] = this->backDepth[(u_char)this->fPlayer] + 1;
            goto MainLoop_setMenuAndNext;
          case 2:
            AudioCmn_PlayFESFX(0);
            this->backDepth[(u_char)this->fPlayer] = 0;
MainLoop_setMenuAndNext:
            this->SetMenu((u_short)(u_char)this->fPlayer,
                    command[i].nextMenu);
            i = i + kPlayerTwo;
            goto MainLoop_perPlayerInputTop;
          case 3:
            AudioCmn_PlayFESFX(0);
            wasSubMenu = (u_int)(u_char)this->fPlayer;
            this->backList[wasSubMenu][this->backDepth[wasSubMenu]] =
                 this->fCurrentMenu[wasSubMenu];
            needToSetChildMenu = true;
            this->backDepth[(u_char)this->fPlayer] = this->backDepth[(u_char)this->fPlayer] + 1;
            stackBackupPin = (short)this->backDepth[(u_char)this->fPlayer];
            this->SetMenu((u_short)(u_char)this->fPlayer,
                    command[i].nextMenu);
            this->backDepth[1] = 0;
            break;
          case 4:
            if (((this->fPlayer != '\0') || (this->backDepth[0] <= (int)stackBackupPin)) &&
               ((this->fPlayer != '\x01' || (this->backDepth[(u_char)this->fPlayer] < 1)))) {
              wasSubMenu = (u_int)(u_char)this->fPlayer;
              if (this->waitingForOtherPlayer[wasSubMenu] != 0) {
                this->waitingForOtherPlayer[wasSubMenu] = 0;
                break;
              }
              this->waitingForOtherPlayer[1 - wasSubMenu] = 0;
              this->waitingForOtherPlayer[(u_char)this->fPlayer] = 0;
            }
            cVar8 = this->fPlayer;
            if (cVar8 == '\0') {
              if ((this->backDepth[0] != (int)stackBackupPin) ||
                 (this->fCurrentMenu[1] == (tMenu *)0x0)) {
                cVar8 = this->fPlayer;
                goto MainLoop_backoutPath;
              }
              ptVar17 = this->fParentMenu[0];
              if (ptVar17 != (tMenu *)0x0) {
                NFS4_VCALL0((*ptVar17->_vf)[5].pfn,
                            (u_char *)ptVar17 + (*ptVar17->_vf)[5].delta);
              }
              ptVar17 = this->fParentMenu[1];
              if (ptVar17 != (tMenu *)0x0) {
                NFS4_VCALL0((*ptVar17->_vf)[5].pfn,
                            (u_char *)ptVar17 + (*ptVar17->_vf)[5].delta);
              }
              pa_Var11 = this->fCurrentMenu[1]->_vf;
              stackBackupPin = -1;
              NFS4_VCALL0((*pa_Var11)[5].pfn,
                          (u_char *)this->fCurrentMenu[1] + (*pa_Var11)[5].delta);
              (this->fCurrentScreen[1])->TransitionOff(kScreen_TransitionTypeScreen,(tMenu *)0x0);
              this->backDepth[1] = 0;
MainLoop_backDepthCheck:
              if (this->backDepth[(u_char)this->fPlayer] < 1) {
                if ((u_char)this->fPlayer != 1) break;
                AudioCmn_PlayFESFX(1);
                i = i + kPlayerTwo;
                goto MainLoop_perPlayerInputTop;
              }
            }
            else {
MainLoop_backoutPath:
              if (cVar8 != '\x01') goto MainLoop_backDepthCheck;
              if (this->backDepth[1] < 1) {
                if (this->fCurrentMenu[1] != (tMenu *)0x0) {
                  ptVar17 = this->fCurrentMenu[1];
                  this->backDepth[0] = stackBackupPin + -1;
                  pa_Var11 = ptVar17->_vf;
                  NFS4_VCALL0((*pa_Var11)[5].pfn,
                              (u_char *)ptVar17 + (*pa_Var11)[5].delta);
                  ptVar17 = this->fParentMenu[0];
                  if (ptVar17 != (tMenu *)0x0) {
                    NFS4_VCALL0((*ptVar17->_vf)[5].pfn,
                                (u_char *)ptVar17 + (*ptVar17->_vf)[5].delta);
                  }
                  ptVar17 = this->fParentMenu[1];
                  if (ptVar17 != (tMenu *)0x0) {
                    NFS4_VCALL0((*ptVar17->_vf)[5].pfn,
                                (u_char *)ptVar17 + (*ptVar17->_vf)[5].delta);
                  }
                  stackBackupPin = -1;
                  (this->fCurrentScreen[1])->TransitionOff(kScreen_TransitionTypeScreen,(tMenu *)0x0);
                  this->SetMenu(0,this->backList[0][this->backDepth[0]]);
                }
                goto MainLoop_backDepthCheck;
              }
            }
            AudioCmn_PlayFESFX(1);
            this->backDepth[(u_char)this->fPlayer] = this->backDepth[(u_char)this->fPlayer] + -1;
            bVar7 = this->fPlayer;
            this->SetMenu((u_short)bVar7,this->backList[(u_int)bVar7][this->backDepth[bVar7]]);
            pa_Var11 = this->fCurrentMenu[(u_char)this->fPlayer]->_vf;
            iVar10 = NFS4_VCALL0((*pa_Var11)[8].pfn,
                                 (u_char *)this->fCurrentMenu[(u_char)this->fPlayer] +
                                 (*pa_Var11)[8].delta);
            if (iVar10 != 0) {
              this->backDepth[(u_char)this->fPlayer] = this->backDepth[(u_char)this->fPlayer] + 1;
            }
            break;
          case 5:
          case 7:
MainLoop_carInfoPinkSlips:
            if (frontEnd.raceType == '\x06') {
              carManager.GetPinkSlipsCar((u_short)(u_char)frontEnd.pinkSlipsCar[(u_char)this->fPlayer],
                         carInfo,(u_short)(u_char)this->fPlayer);
              goto MainLoop_carInfoApplied;
            }
MainLoop_carInfoStockGarage:
            if (frontEnd.carListType == '\0') {
              carManager.GetStockCar((u_short)(u_char)frontEnd.playerCar[(u_char)this->fPlayer],carInfo)
              ;
            }
            else {
              carManager.GetGarageCar((u_short)(u_char)frontEnd.garageCar[(u_char)this->fPlayer],carInfo,
                         (u_short)(u_char)this->fPlayer);
            }
MainLoop_carInfoApplied:
            iVar4 = ticks;
            if (carInfo.fEnginePatch != 0) {
              AudioCmn_PlayFESFX((u_int)carInfo.fEnginePatch);
              iVar4 = ticks;
            }
            while ((u_int)(ticks - iVar4) < 0x100) {
              FeAudio_systemtask(0);
            }
            GameSetup_gData.replayMode = 0;
            this->PerformMenuDestruction();
            return kApp_Command_StartRace;
          case 6:
            iVar10 = 1 - (u_int)(u_char)this->fPlayer;
            if (this->waitingForOtherPlayer[iVar10] == 0) {
              this->waitingForOtherPlayer[(u_char)this->fPlayer] = 1;
              break;
            }
            this->waitingForOtherPlayer[iVar10] = 0;
            if (frontEnd.raceType != '\x06') goto MainLoop_carInfoStockGarage;
            AudioMus_StopSong(400);
            Init_Memcard(false,1);
            err = PinkSlipsNoError;
            player = 0;
            bVar1 = true;
            while ((ptVar5 = FEApp, bVar1 && (err == PinkSlipsNoError))) {
              pcVar15 = TextSys_Word(player + 0x295);
              ptVar6 = FEApp;
              (ptVar5->NoInputMemCardDialog)._base_tDialogMessageString.string = pcVar15;
              ((tDialogBase *)&ptVar6->NoInputMemCardDialog)->Display();
              while ((FEApp->NoInputMemCardDialog)._base_tDialogMessageString._base_tDialogBase.fFullyOpen != 1)
              {
                FEApp->Redraw();
              }
              err = SavePinkSlipsCarsWithErrorDialogs((short)player,0,(u_short)(u_char)frontEnd.pinkSlipsCar[player]);
              if ((err != PinkSlipsNoError) && (player == 1)) {
                pcVar15 = TextSys_Word(0x297);
                pcVar16 = PlayerName(0);
                sprintf(string,pcVar15,pcVar16,1);
                (FEApp->NoInputMemCardDialog)._base_tDialogMessageString.string = string;
                SavePinkSlipsCarsWithErrorDialogs(0,1,-1);
              }
              player = player + 1;
              ((tDialogBase *)&FEApp->NoInputMemCardDialog)->Hide();
              bVar1 = player < 2;
            }
            DeInit_Memcard();
            if (err == PinkSlipsNoError) goto MainLoop_carInfoPinkSlips;
            this->UpdateMusic();
            AudioMus_Volume((int)((u_int)(u_char)frontEnd.musicVolume * 0x23) >> 6);
            i = i + kPlayerTwo;
            goto MainLoop_perPlayerInputTop;
          case 8:
            GameSetup_gData.replayMode = 2;
            this->PerformMenuDestruction();
            return kApp_Command_StartReplay;
          }
switchD_80014c34_default:
          i = i + kPlayerTwo;
          goto MainLoop_perPlayerInputTop;
        }
      }
MainLoop_nextPlayer:
      this->fPlayer = this->fPlayer + '\x01';
    }
    if (doRedraw) {
      this->Redraw();
    }
    if (0xf00 < iVar4 - demoLoopLastInputTick) {
      this->RunDemoVideo();
      demoLoopLastInputTick = ticks;
    }
  } while( true );
}



/* ---- tFEApplication::RunPostGame  [FEAPP.CPP:992-1122] SLD-VERIFIED ---- */

tAppCommand tFEApplication::RunPostGame()

{
  tMenuCommand command;
  int ret;
  Car_tStats *dummyCars;
  int i;
  short nBestCarIndex;
  
  if ((frontEnd.raceType != '\x06') &&
     ((frontEnd.raceType != '\0' || (frontEnd.carListType != '\0')))) {
    dummyCars = Cars_gNewCarStatsList;
    StatChk_ClearNewRecords();
    i = 0;
    do {
      Front_ResetPSXController(i,(u_int)(u_char)frontEnd.controlConfig[i]);
      this->gotName[i] = 0;
      this->needName[i] = 0;
      this->speechToPlay[i] = -1;
      i = i + 1;
    } while (i < 2);
    if (StatChk_IsRecordLapTime(dummyCars,(short)Cars_gNumRaceCars,&nBestCarIndex) != 0) {
      if (frontEnd.gameMode == '\x01') {
        this->speechToPlay[nBestCarIndex] = nBestCarIndex ? 8 : 7;
      }
      else {
        this->speechToPlay[nBestCarIndex] = 6;
      }
      this->needName[nBestCarIndex] = 1;
    }
    ret = StatChk_IsTopTime(dummyCars,(short)Cars_gNumRaceCars);
    if (ret != 0) {
      if (frontEnd.gameMode == '\x01') {
        if ((ret & 3) != 0) {
          this->needName[0] = 1;
          if ((this->speechToPlay[0] != -1) && (nBestCarIndex == 0)) {
            if ((ret & 2) != 0) {
              this->speechToPlay[0] = 10;
            }
            else {
              this->speechToPlay[0] = 0xd;
            }
          }
          else {
            if ((ret & 2) != 0) {
              this->speechToPlay[0] = 1;
            }
            else {
              this->speechToPlay[0] = 4;
            }
          }
        }
        if ((ret & 0xc) != 0) {
          this->needName[1] = 1;
          if ((this->speechToPlay[1] != -1) && (nBestCarIndex == 1)) {
            if ((ret & 8) != 0) {
              this->speechToPlay[1] = 0xb;
            }
            else {
              this->speechToPlay[1] = 0xe;
            }
          }
          else {
            if ((ret & 8) != 0) {
              this->speechToPlay[1] = 2;
            }
            else {
              this->speechToPlay[1] = 5;
            }
          }
        }
      }
      else {
        this->needName[0] = 1;
        if (this->speechToPlay[0] != -1) {
          this->speechToPlay[0] = (ret & 2) ? 9 : 0xc;
        }
        else {
          this->speechToPlay[0] = (ret & 2) ? 0 : 3;
        }
      }
    }
    if (this->needName[0] != 0) {
      tUserNameMenuItem *item = &menuDefs->menuItemUserName1;
      tOptionsMenu *menu = &menuDefs->menuPostGamePlayer1Name;
      item->fData = frontEnd.playerNameList[0];
      item->fPlayer = 0;
      item->fMaxStringLength = 7;
      item->fCurrentRow = 0;
      item->fCurrentColumn = 0;
      screenUserName->callingMenu = menu;
      return this->MainLoop((tMenu *)menu);
    }
    if (this->needName[1] != 0) {
      tUserNameMenuItem *item = &menuDefs->menuItemUserName2;
      tOptionsMenu *menu = &menuDefs->menuPostGamePlayer2Name;
      item->fPlayer = 1;
      item->fData = frontEnd.playerNameList[4];
      item->fMaxStringLength = 7;
      item->fCurrentRow = 0;
      item->fCurrentColumn = 0;
      screenUserName->callingMenu = menu;
      return this->MainLoop((tMenu *)menu);
    }
  }
  MenuExtended_PostGameMenu(command);
  return this->MainLoop(command.nextMenu);
}



/* ---- tFEApplication::RunFrontEnd  [FEAPP.CPP:1126-1134] SLD-VERIFIED ---- */

tAppCommand tFEApplication::RunFrontEnd()

{
  tAppCommand tVar1;
  
  tVar1 = this->MainLoop(&(menuDefs->menuMain)._base_tMenu);
  return tVar1;
}

/* ---- FreeHelpShapeCluts__Fv  [@0x80013ff4] ---- RECONSTRUCTED 2026-06-12 (Ghidra @NFS4.EXE.c:2489).
 *  Free fn in FEApp.obj (sits among tFEApplication methods; already called @feapp.cpp:591), skipped
 *  from the original pass. Releases the 0x3b help-shape CLUTs. func_0x800df9a4 = Texture_MenuReleaseClutId. */
extern "C" tTexture_ShapeInfo *gHelpShapes;            /* @0x80052a64 */
void Texture_MenuReleaseClutId(short clutID);      /* @0x800df9a4 */

void FreeHelpShapeCluts(void)
{
  int i;
  for (i = 0; i < 0x3b; i++) {
    if (gHelpShapes[i].clutID != 0) {
      Texture_MenuReleaseClutId((short)gHelpShapes[i].clutID);
      gHelpShapes[i].clutID = 0;
    }
  }
}



/* end of feapp.cpp */
