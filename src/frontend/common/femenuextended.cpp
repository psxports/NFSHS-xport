/* frontend/common/femenuextended.cpp -- RECONSTRUCTED (NFS4 menu/item widget hierarchy; C++ TU)
 *   56 fns across 9 classes: tMenuNFS4(+TwoPlayer/Bottom) menu containers, tMenuBlank, tMenuOptions,
 *   tMenuItemGoToMenuNFS4Button, tMenuItemNFS4LeftRightChoice, tMenuItemOptions{LeftRightChoice,
 *   TwoItemChoice}, + free MenuNFS4_DrawTextBox. Member defs; base ctors via init-lists; manual _vf.
 */
#include "femenuextended.h"
#include "../../mips_semantics.h"
#include <stdarg.h>

/* ---- FEMenuExtended.obj-OWNED globals -- DEFINED here (self-contained; .bss zero; SYM-typed) ---- */
PSX_RECT         gHelpPos;   /* @0x80052b58  (bss(zero)) */


/* ---- MenuNFS4_DrawTextBox  [FEMENUEXTENDED.CPP:66-137] SLD-VERIFIED ---- */

void MenuNFS4_DrawTextBox(int helpText,PSX_RECT &r,int initialWidth,short drawOffset,short fSelFade,
               bool drawArrows,bool reflected)

{
  char *wordText;
  int textWidth;
  int textLen;
  int col;
  char *wordText2;
  char *sMenuText;
  int textpix;
  int dist;
  DRAWENV *drenv;
  PSX_RECT temp;
  tDrawShapeExtended drawFlags;
  char buffer [64];
  DR_AREA *daprim;
  tTexture_ShapeInfo *shape;

  drenv = (DRAWENV *)Draw_GetDRAWENV(Draw_gPlayer1View,gFlip);
  drawFlags.tint[0] = CalcFadeVal(0xb54200,0xbebe,(int)fSelFade);
  if (reflected != 0) {
    drawFlags.tint[0] = CalcFadeVal(0,drawFlags.tint[0],
        nfs4_mips_subu_s32(0xe0,(int)r.y));
  }
  DrawShape_SubtractNFS4RectEdges(&r);
  if (-1 < helpText) {
    daprim = (DR_AREA *)Render_gPacketPtr;
    temp.x = 0;
    temp.y = drenv->clip.y;
    temp.w = 0x200;
    temp.h = 0xf0;
    AddPrim(Render_gPalettePtr,daprim);
    Render_gPacketPtr = (u_char *)daprim + 0xc;
    SetDrawArea(daprim,&temp);
    FETextRender_SetFont(0);
    wordText = TextSys_Word(helpText);
    sprintf(buffer,"%s",wordText);
    s_upper(buffer);
    textWidth = textpixels(buffer);
    textLen = strlen(buffer);
    textpix = nfs4_mips_subu_s32(textWidth,textLen);
    if (textpix < initialWidth) {
      textpix = initialWidth;
    }
    dist = nfs4_mips_addu_s32(textpix,0x19);
    col = CalcTextFadeSelToHi(textType_FlybyHelp,fSelFade,0);
    if (reflected != 0) {
      col = CalcFadeVal(0,col,nfs4_mips_subu_s32(0xf0,(int)r.y));
    }
    wordText2 = TextSys_Word(helpText);
    FETextRender_FullTextRGB(wordText2,
               (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
                   (int)(u_short)r.x,(int)drawOffset),16),
               (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
                   (int)(u_short)r.y,4),16),col,'\0',0);
    sMenuText = TextSys_Word(helpText);
    FETextRender_FullTextRGB(sMenuText,
               (short)nfs4_mips_sign_extend((u_int)nfs4_mips_subu_s32(
                   nfs4_mips_addu_s32((int)(u_short)r.x,(int)drawOffset),dist),16),
               (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
                   (int)(u_short)r.y,4),16),col,'\0',0);
    if (drawArrows != 0) {
      int ypos = nfs4_mips_addu_s32((int)r.y,
          nfs4_mips_sra_s32(nfs4_mips_sll_s32((int)(u_short)r.h,16),17));
      if (reflected == 0) {
        ypos = nfs4_mips_addu_s32(ypos,2);
      }
      int left = nfs4_mips_addu_s32((int)r.x,(int)drawOffset);
      int right = nfs4_mips_addu_s32(left,textpix);
      int reflectedLeft = nfs4_mips_subu_s32(left,dist);
      DrawShapeExtended(0xa,0x118,nfs4_mips_addu_s32(left,-0xa),ypos,0,0,&drawFlags);
      DrawShapeExtended(0xb,0x118,nfs4_mips_addu_s32(right,8),ypos,0,0,&drawFlags);
      DrawShapeExtended(0xa,0x118,nfs4_mips_addu_s32(reflectedLeft,-0xa),ypos,0,0,&drawFlags);
      DrawShapeExtended(0xb,0x118,nfs4_mips_addu_s32(
          nfs4_mips_addu_s32(reflectedLeft,textpix),8),ypos,0,0,&drawFlags);
    }
    daprim = (DR_AREA *)Render_gPacketPtr;
    nfs4_mips_copy_bytes(&temp, &r, 8);
    temp.y = (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
        (int)(u_short)temp.y,(int)(u_short)drenv->clip.y),16);
    temp.x = (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
        (int)(u_short)temp.x,2),16);
    temp.w = (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
        (int)(u_short)temp.w,-4),16);
    AddPrim(Render_gPalettePtr,daprim);
    Render_gPacketPtr = (u_char *)daprim + 0xc;
    SetDrawArea(daprim,&temp);
  }
  nfs4_mips_copy_bytes(&temp, &r, 8);
  temp.y = (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
      (int)(u_short)temp.y,1),16);
  temp.h = (short)nfs4_mips_sign_extend((u_int)nfs4_mips_addu_s32(
      (int)(u_short)temp.h,-2),16);
  shape = gHelpShapes + 0x1e;
  temp.w = (short)nfs4_mips_sign_extend((u_int)nfs4_mips_subu_s32(
      nfs4_mips_addu_s32((int)(u_short)temp.w,-1),
      nfs4_mips_sra_s32(nfs4_mips_sll_s32((int)(u_short)shape->width,16),17)),16);
  DrawShapeExtended(0x1e,8,(int)temp.x + (int)temp.w,(int)temp.y,0,0,(tDrawShapeExtended *)0x0);
  PSXDrawSquare(0,(int)temp.x,(int)temp.y,(int)temp.w,(int)shape->height);
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::ctor  [FEMENUEXTENDED.CPP:152-160] SLD-FLAG:NONMONO ---- */

tMenuItemGoToMenuNFS4Button::tMenuItemGoToMenuNFS4Button(u_int textDescription,tMenu *newMenu,
              void (*OnButtonPress)(tMenuCommand&),int firstFrame,int numFrames)
  : _base_tMenuItemGoToMenuButton(textDescription,newMenu,OnButtonPress)
{
  
  *(void **)&((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemGoToMenuNFS4Button_vtable;
  this->fOffset = 0xe;
  this->fTransitionVal = 0;
  this->fTransitionSpeed = 0;
  this->fEnabledTransitionVal = 0;
  (this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fNumFrames = numFrames;
  (this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fButtonImage = firstFrame;
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::dtor  [FEMENUEXTENDED.CPP:164-164] SLD-VERIFIED ---- */

tMenuItemGoToMenuNFS4Button::~tMenuItemGoToMenuNFS4Button()

{
  *(void **)&((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemGoToMenuNFS4Button_vtable;
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::Draw  [FEMENUEXTENDED.CPP:168-211] SLD-VERIFIED ---- */

void tMenuItemGoToMenuNFS4Button::Draw(int x,int y,bool selected)

{
  short sVar1;
  char *pcVar2;
  int iVar3;
  u_int uVar4;
  short dist;
  PSX_RECT rect;
  char buffer [64];
  
  if ((selected != 0) || (dist = 0xe, 1 < this->fOffset + -0xe)) {
    FETextRender_SetFont(0);
    pcVar2 = TextSys_Word((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription);
    sprintf(buffer,"%s",pcVar2);
    s_upper(buffer);
    iVar3 = textpixels(buffer);
    uVar4 = strlen(buffer);
    dist = 0xa5;
    if (0x8b < (int)((iVar3 - uVar4) * 0x10000) >> 0x10) {
      dist = (short)(iVar3 - uVar4) + 0x19;
    }
    sVar1 = this->fOffset;
    this->fOffset = sVar1 + -2;
    if (selected == 0) {
      this->fOffset = sVar1 + -4;
    }
    dist = this->fOffset + dist;
    if (-1 < this->fOffset) goto Draw_GoToMenuButtonOffset;
  }
  this->fOffset = dist;
Draw_GoToMenuButtonOffset:
  if ((((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fFlags ^ 1) & 1) == 0) {
    dist = this->fEnabledTransitionVal + -0xc;
  }
  else {
    dist = this->fEnabledTransitionVal + 0xc;
  }
  this->fEnabledTransitionVal = dist;
  if (this->fEnabledTransitionVal < 0) {
    this->fEnabledTransitionVal = 0;
  }
  else if (0x80 < this->fEnabledTransitionVal) {
    this->fEnabledTransitionVal = 0x80;
  }
  rect.h = 0xb;
  dist = this->fTransitionVal;
  if (this->fEnabledTransitionVal < this->fTransitionVal) {
    dist = this->fEnabledTransitionVal;
  }
  iVar3 = dist * 0x73;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x7f;
  }
  rect.w = (short)(iVar3 >> 7);
  rect.x = (short)x;
  rect.y = (short)y;
  MenuNFS4_DrawTextBox((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription,rect,
             0x8c,this->fOffset,
             (this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fSelFade,false,0);
  if (((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fFlags & 0x200) != 0) {
    Font_SetBlitter(FontUpsideDownBlit);
    rect.y = 0x118 - (short)y;
    rect.h = 0xb;
    dist = this->fTransitionVal;
    if (this->fEnabledTransitionVal < this->fTransitionVal) {
      dist = this->fEnabledTransitionVal;
    }
    iVar3 = dist * 0x73;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0x7f;
    }
    rect.w = (short)(iVar3 >> 7);
    rect.x = (short)x;
    MenuNFS4_DrawTextBox((this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription,rect
               ,0x8c,this->fOffset,
               (this->_base_tMenuItemGoToMenuButton)._base_tMenuItemInteractive._base_tMenuItem.fSelFade,false,1);
    Font_ReSetBlitter();
  }
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::TransitionOn  [FEMENUEXTENDED.CPP:216-218] SLD-VERIFIED ---- */

void tMenuItemGoToMenuNFS4Button::TransitionOn()

{
  this->fEnabledTransitionVal = 0;
  this->fTransitionSpeed = 0xc;
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::TransitionOff  [FEMENUEXTENDED.CPP:222-223] SLD-VERIFIED ---- */

void tMenuItemGoToMenuNFS4Button::TransitionOff()

{
  this->fTransitionSpeed = -0xc;
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::TransitionIsFinished  [FEMENUEXTENDED.CPP:227-228] SLD-VERIFIED ---- */

void * tMenuItemGoToMenuNFS4Button::TransitionIsFinished()

{
  return (void *)(u_int)(this->fTransitionSpeed == 0);
}



/* ---- tMenuItemGoToMenuNFS4Button::UpdateTransition  [FEMENUEXTENDED.CPP:232-244] SLD-VERIFIED ---- */

void tMenuItemGoToMenuNFS4Button::UpdateTransition(bool selected)

{
  short sVar1;
  
  sVar1 = this->fTransitionVal + this->fTransitionSpeed;
  this->fTransitionVal = sVar1;
  if (sVar1 < 0) {
    this->fTransitionVal = 0;
  }
  else {
    if (sVar1 < 0x81) goto UpdTrans_callBaseGoToMenu;
    this->fTransitionVal = 0x80;
  }
  this->fTransitionSpeed = 0;
UpdTrans_callBaseGoToMenu:
  ((tMenuItem *)this)->UpdateTransition(selected);
  return;
}



/* ---- tMenuItemNFS4LeftRightChoice::ctor  [FEMENUEXTENDED.CPP:248-254] SLD-VERIFIED ---- */
tMenuItemNFS4LeftRightChoice::tMenuItemNFS4LeftRightChoice(u_int textDescription,tListIterator *dataPtr,
          int firstFrame,int numFrames)
  : _base_tMenuItemLeftRightChoice(textDescription,dataPtr)
{
  
  *(void **)&((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemNFS4LeftRightChoice_vtable;
  (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fButtonImage = firstFrame;
  this->fOffset = 0xe;
  this->fTransitionVal = 0;
  this->fTransitionSpeed = 0;
  (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fNumFrames = numFrames;
  return;
}



/* ---- tMenuItemNFS4LeftRightChoice::dtor  [FEMENUEXTENDED.CPP:258-258] SLD-VERIFIED ---- */

tMenuItemNFS4LeftRightChoice::~tMenuItemNFS4LeftRightChoice()

{
  *(void **)&((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem._vf) = (void *)tMenuItemNFS4LeftRightChoice_vtable;
  return;
}



/* ---- tMenuItemNFS4LeftRightChoice::Draw  [FEMENUEXTENDED.CPP:262-302] SLD-VERIFIED ---- */

void tMenuItemNFS4LeftRightChoice::Draw(int x,int y,bool selected)

{
  short sVar1;
  short dist;
  char *string;
  int iVar2;
  bool bVar3;
  short sVar4;
  int iVar5;
  PSX_RECT rect;
  
  iVar5 = selected;
  if ((iVar5 != 0) || (dist = 0xe, 1 < this->fOffset + -0xe)) {
    FETextRender_SetFont(0);
    string = TextSys_Word((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription);
    iVar2 = textpixels(string);
    dist = 0xa5;
    if (0x8b < (short)iVar2) {
      dist = (short)iVar2 + 0x19;
    }
    sVar1 = this->fOffset;
    this->fOffset = sVar1 + -2;
    if (iVar5 == 0) {
      this->fOffset = sVar1 + -4;
    }
    dist = this->fOffset + dist;
    if (-1 < this->fOffset) goto Draw_LRChoiceTransVal;
  }
  this->fOffset = dist;
Draw_LRChoiceTransVal:
  if ((((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fFlags ^ 1) & 1) == 0) {
    sVar4 = this->fEnabledTransitionVal + -0xc;
  }
  else {
    sVar4 = this->fEnabledTransitionVal + 0xc;
  }
  this->fEnabledTransitionVal = sVar4;
  if (this->fEnabledTransitionVal < 0) {
    this->fEnabledTransitionVal = 0;
  }
  else if (0x80 < this->fEnabledTransitionVal) {
    this->fEnabledTransitionVal = 0x80;
  }
  rect.h = 0xb;
  sVar4 = this->fEnabledTransitionVal;
  if (this->fTransitionVal < this->fEnabledTransitionVal) {
    sVar4 = this->fTransitionVal;
  }
  iVar2 = sVar4 * 0x73;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x7f;
  }
  rect.w = (short)(iVar2 >> 7);
  bVar3 = false;
  if ((iVar5 != 0) || (this->fOffset != 0xe)) {
    bVar3 = true;
  }
  rect.x = (short)x;
  rect.y = (short)y;
  MenuNFS4_DrawTextBox((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription,rect,
             0x8c,this->fOffset,
             (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade,bVar3,0);
  if (((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fFlags & 0x200) != 0) {
    Font_SetBlitter(FontUpsideDownBlit);
    rect.y = 0x118 - (short)y;
    rect.h = 0xb;
    sVar4 = this->fTransitionVal;
    if (this->fEnabledTransitionVal < this->fTransitionVal) {
      sVar4 = this->fEnabledTransitionVal;
    }
    iVar2 = sVar4 * 0x73;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0x7f;
    }
    rect.w = (short)(iVar2 >> 7);
    bVar3 = false;
    if ((iVar5 != 0) || (this->fOffset != 0xe)) {
      bVar3 = true;
    }
    rect.x = (short)x;
    MenuNFS4_DrawTextBox((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription,
               rect,0x8c,this->fOffset,
               (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade,bVar3,1);
    Font_ReSetBlitter();
  }
  return;
}



/* ---- tMenuItemNFS4LeftRightChoice::TransitionOn  [FEMENUEXTENDED.CPP:307-309] SLD-VERIFIED ---- */

void tMenuItemNFS4LeftRightChoice::TransitionOn()

{
  this->fEnabledTransitionVal = 0;
  this->fTransitionSpeed = 0xc;
  return;
}



/* ---- tMenuItemNFS4LeftRightChoice::TransitionOff  [FEMENUEXTENDED.CPP:313-314] SLD-VERIFIED ---- */

void tMenuItemNFS4LeftRightChoice::TransitionOff()

{
  this->fTransitionSpeed = -0xc;
  return;
}



/* ---- tMenuItemNFS4LeftRightChoice::TransitionIsFinished  [FEMENUEXTENDED.CPP:318-319] SLD-VERIFIED ---- */

void * tMenuItemNFS4LeftRightChoice::TransitionIsFinished()

{
  return (void *)(u_int)(this->fTransitionSpeed == 0);
}



/* ---- tMenuItemNFS4LeftRightChoice::UpdateTransition  [FEMENUEXTENDED.CPP:323-335] SLD-VERIFIED ---- */

void tMenuItemNFS4LeftRightChoice::UpdateTransition(bool selected)

{
  short sVar1;
  
  sVar1 = this->fTransitionVal + this->fTransitionSpeed;
  this->fTransitionVal = sVar1;
  if (sVar1 < 0) {
    this->fTransitionVal = 0;
  }
  else {
    if (sVar1 < 0x81) goto UpdTrans_callBaseLRChoice;
    this->fTransitionVal = 0x80;
  }
  this->fTransitionSpeed = 0;
UpdTrans_callBaseLRChoice:
  ((tMenuItem *)this)->UpdateTransition(selected);
  return;
}



/* ---- tMenuItemOptionsLeftRightChoice::Draw  [FEMENUEXTENDED.CPP:346-374] SLD-VERIFIED ---- */

void tMenuItemOptionsLeftRightChoice::Draw(int x,int y,bool selected)

{
  tTexture_ShapeInfo *left;
  short sVar2;
  int col;
  char *pcVar3;
  __vtbl_ptr_type (*pa_Var4) [6];
  tListIterator *ptVar5;
  short y_00;
  int iVar6;
  PSX_RECT r;
  tDrawShapeExtended drawFlags;
  
  left = gHelpShapes;
  iVar6 = selected;
  col = CalcTextFadeSelToHi(textType_Options,
                      (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade,0);
  pcVar3 = TextSys_Word((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription);
  y_00 = (short)((u_int)((y + 3) * 0x10000) >> 0x10);
  FETextRender_FullTextRGB(pcVar3,(short)((u_int)((x + 0x94) * 0x10000) >> 0x10),y_00,col,'\0',1);
  ptVar5 = (this->_base_tMenuItemLeftRightChoice).fData;
  pa_Var4 = ptVar5->_vf;
  sVar2 = NFS4_VCALL_AUTO((*pa_Var4)[3].pfn, (char *)ptVar5 + (int)(*pa_Var4)[3].delta,0xffffffff);
  pcVar3 = TextSys_Word((int)sVar2);
  FETextRender_FullTextRGB(pcVar3,(short)((u_int)((((int)((u_int)(u_short)left[0x29].width << 0x10) >> 0x11) + x +
                                   0xd9) * 0x10000) >> 0x10),y_00,col,'\0',2);
  drawFlags.tint[0] =
       CalcFadeVal(0xb54200,0xbebe,
                  (int)(this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade);
  DrawShapeExtended(0xa,0x118,x + 0xa6,y + 6,0,(u_int)(iVar6 == 0),
             &drawFlags);
  DrawShapeExtended(0xb,0x118,(x - (int)left[0x29].width) + 0x12f,y + 6,0,(u_int)(iVar6 == 0),
             &drawFlags);
  r.x = (short)x;
  r.y = (short)y;
  r.w = 0x129;
  r.h = left[0x29].height;
  DrawShape_NFS4RoundRectangle(-1,&r,(short)iVar6);
  return;
}



/* ---- tMenuItemOptionsTwoItemChoice::TransitionOn  [FEMENUEXTENDED.CPP:378-379] SLD-VERIFIED ---- */

void tMenuItemOptionsTwoItemChoice::TransitionOn()

{
  char cVar1;
  tListIterator *ptVar2;
  __vtbl_ptr_type (*pa_Var3) [6];
  
  ptVar2 = (this->_base_tMenuItemLeftRightChoice).fData;
  pa_Var3 = ptVar2->_vf;
  cVar1 = NFS4_VCALL_AUTO((*pa_Var3)[2].pfn, (char *)ptVar2 + (int)(*pa_Var3)[2].delta,0xffffffff);
  this->fOnOffFade = (u_short)(cVar1 != '\0') << 7;
  return;
}



/* ---- tMenuItemOptionsTwoItemChoice::Draw  [FEMENUEXTENDED.CPP:383-428] SLD-VERIFIED ---- */

void tMenuItemOptionsTwoItemChoice::Draw(int x,int y,bool selected)

{
  tTexture_ShapeInfo *left;
  char cVar2;
  short sVar3;
  tListIterator *ptVar4;
  int Col;
  char *pcVar5;
  short sVar6;
  __vtbl_ptr_type (*pa_Var7) [6];
  int iVar8;
  PSX_RECT r;
  tDrawShapeExtended drawFlags;
  int ColTextOn;
  int ColTextOff;
  
  left = gHelpShapes;
  iVar8 = selected;
  ptVar4 = (this->_base_tMenuItemLeftRightChoice).fData;
  pa_Var7 = ptVar4->_vf;
  cVar2 = NFS4_VCALL_AUTO((*pa_Var7)[2].pfn, (char *)ptVar4 + (int)(*pa_Var7)[2].delta,0xffffffff);
  if (cVar2 == '\0') {
    sVar6 = this->fOnOffFade + -0x40;
  }
  else {
    sVar6 = this->fOnOffFade + 0x40;
  }
  this->fOnOffFade = sVar6;
  sVar6 = this->fOnOffFade;
  if (((sVar6 < 1) || (sVar3 = 0x80, sVar6 < 0x80)) && (sVar3 = this->fOnOffFade, sVar6 < 0)) {
    sVar3 = 0;
  }
  sVar6 = (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade;
  this->fOnOffFade = sVar3;
  Col = CalcTextFadeSelToHi(textType_Options,sVar6,0);
  CalcOnOffFade(textType_Options,this->fOnOffFade,
             (this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade,0,ColTextOn,
             ColTextOff);
  pcVar5 = TextSys_Word((this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fTextDescription);
  sVar6 = (short)((u_int)((y + 3) * 0x10000) >> 0x10);
  FETextRender_FullTextRGB(pcVar5,(short)((u_int)((x + 0x94) * 0x10000) >> 0x10),sVar6,Col,'\0',1);
  pcVar5 = TextSys_Word((int)*((this->_base_tMenuItemLeftRightChoice).fData)->fSelectionList);
  FETextRender_FullTextRGB(pcVar5,(short)((u_int)((x + 0xb0) * 0x10000) >> 0x10),sVar6,ColTextOff,'\0',0);
  pcVar5 = TextSys_Word((int)((this->_base_tMenuItemLeftRightChoice).fData)->fSelectionList[1]);
  FETextRender_FullTextRGB(pcVar5,(short)(((x - (u_int)(u_short)left[0x29].width) + 0x126) * 0x10000 >> 0x10),
             sVar6,ColTextOn,'\0',1);
  drawFlags.tint[0] =
       CalcFadeVal(0xb54200,0xbebe,
                  (int)(this->_base_tMenuItemLeftRightChoice)._base_tMenuItemInteractive._base_tMenuItem.fSelFade);
  DrawShapeExtended(0xa,0x118,x + 0xa6,y + 6,0,(u_int)(iVar8 == 0),
             &drawFlags);
  DrawShapeExtended(0xb,0x118,(x - (int)left[0x29].width) + 0x12f,y + 6,0,(u_int)(iVar8 == 0),
             &drawFlags);
  r.x = (short)x;
  r.y = (short)y;
  r.w = 0x129;
  r.h = left[0x29].height;
  DrawShape_NFS4RoundRectangle(-1,&r,(short)iVar8);
  return;
}



/* ---- tMenuNFS4::ctor  [FEMENUEXTENDED.CPP:439-444] SLD-VERIFIED ---- */

tMenuNFS4::tMenuNFS4(u_int flags,tScreen *screenHandler,tMenu *nextMenu,
                 tMenu *optionsMenu,void (*OnButtonPress)(tMenuCommand&),short title,tMenuItem *firstItem,...)
  : _base_tMenu(flags,screenHandler,nextMenu,optionsMenu,OnButtonPress,title)
{
  va_list ap;

  *(void **)&((this->_base_tMenu)._vf) = (void *)tMenuNFS4_vtable;
  va_start(ap,firstItem);
  this->_base_tMenu.tMenuConstructor(firstItem,ap);
  va_end(ap);
  return;
}



/* ---- tMenuNFS4::ctor  [FEMENUEXTENDED.CPP:454-455] SLD-VERIFIED ---- */

tMenuNFS4::tMenuNFS4(u_int flags,tScreen *screenHandler,tMenu *nextMenu,tMenu *optionsMenu,
              void (*OnButtonPress)(tMenuCommand&),short title)
  : _base_tMenu(flags,screenHandler,nextMenu,optionsMenu,OnButtonPress,title)
{
  
  *(void **)&((this->_base_tMenu)._vf) = (void *)tMenuNFS4_vtable;
  return;
}



/* ---- tMenuNFS4::dtor  [FEMENUEXTENDED.CPP:459-459] SLD-VERIFIED ---- */

tMenuNFS4::~tMenuNFS4()

{
  *(void **)&((this->_base_tMenu)._vf) = (void *)tMenuNFS4_vtable;
  return;
}



/* ---- tMenuNFS4::Initialize  [FEMENUEXTENDED.CPP:463-476] SLD-VERIFIED ---- */

void tMenuNFS4::Initialize()

{
  short item;
  u_char bVar1;
  tMenuItem *ptVar2;
  u_int *puVar3;
  
  this->_base_tMenu.Initialize();
  item = (this->_base_tMenu).fCurrentItem;
  ptVar2 = (this->_base_tMenu).fItemList[0];
  this->fInItemTransition = 0;
  this->fInMenuTransition = 0;
  this->fNumItems = '\0';
  this->fLastItem = (char)item;
  while (ptVar2 != (tMenuItem *)0x0) {
    bVar1 = this->fNumItems + 1;
    this->fNumItems = bVar1;
    ptVar2 = (this->_base_tMenu).fItemList[bVar1];
  }
  item = 0;
  if (((this->_base_tMenu).fFlags & 0x200) != 0) {
    while( true ) {
      puVar3 = *(u_int **)((int)(this->_base_tMenu).fItemList + ((item << 0x10) >> 0xe));
      item = item + 1;
      if (puVar3 == (u_int *)0x0) break;
      *puVar3 = *puVar3 | 0x200;
    }
  }
  return;
}



/* ---- tMenuNFS4::ProcessInput  [FEMENUEXTENDED.CPP:481-482] SLD-VERIFIED ---- */

void tMenuNFS4::ProcessInput(tPlayer fromPlayer,tInputKeyType &keyval,tMenuCommand &command)

{
  this->_base_tMenu.ProcessInput(fromPlayer,keyval,command);
  return;
}



/* ---- tMenuNFS4::TransitionOff  [FEMENUEXTENDED.CPP:490-493] SLD-VERIFIED ---- */

void tMenuNFS4::TransitionOff()

{
  tMenuItem *ptVar1;
  int iVar2;
  int iVar3;
  int i;
  
  i = 0;
  ptVar1 = (this->_base_tMenu).fItemList[0];
  while (ptVar1 != (tMenuItem *)0x0) {
    iVar3 = *(int *)((int)(this->_base_tMenu).fItemList + ((i << 0x10) >> 0xe));
    iVar2 = *(int *)(iVar3 + 0x18);
    NFS4_VCALL0(*(void **)(iVar2 + 0x3c), iVar3 + *(short *)(iVar2 + 0x38));
    i = i + 1;
    ptVar1 = *(tMenuItem **)((int)(this->_base_tMenu).fItemList + (i * 0x10000 >> 0xe));
  }
  return;
}



/* ---- tMenuNFS4::TransitionOn  [FEMENUEXTENDED.CPP:497-500] SLD-VERIFIED ---- */

void tMenuNFS4::TransitionOn()

{
  tMenuItem *ptVar1;
  int iVar2;
  int iVar3;
  int i;
  
  i = 0;
  ptVar1 = (this->_base_tMenu).fItemList[0];
  while (ptVar1 != (tMenuItem *)0x0) {
    iVar3 = *(int *)((int)(this->_base_tMenu).fItemList + ((i << 0x10) >> 0xe));
    iVar2 = *(int *)(iVar3 + 0x18);
    NFS4_VCALL0(*(void **)(iVar2 + 0x44), iVar3 + *(short *)(iVar2 + 0x40));
    i = i + 1;
    ptVar1 = *(tMenuItem **)((int)(this->_base_tMenu).fItemList + (i * 0x10000 >> 0xe));
  }
  return;
}



/* ---- tMenuNFS4::TransitionIsFinished  [FEMENUEXTENDED.CPP:504-511] SLD-VERIFIED ---- */

void * tMenuNFS4::TransitionIsFinished()

{
  tMenuItem *ptVar1;
  int iVar2;
  u_int uVar3;
  int iVar4;
  void *result;
  int i;
  
  result = (void *)0x1;
  i = 0;
  ptVar1 = (this->_base_tMenu).fItemList[0];
  while (ptVar1 != (tMenuItem *)0x0) {
    iVar4 = *(int *)((int)(this->_base_tMenu).fItemList + ((i << 0x10) >> 0xe));
    iVar2 = *(int *)(iVar4 + 0x18);
    uVar3 = NFS4_VCALL0(*(void **)(iVar2 + 0x4c), iVar4 + *(short *)(iVar2 + 0x48));
    result = (void *)(u_int)(((u_int)result & uVar3) != 0);
    i = i + 1;
    ptVar1 = *(tMenuItem **)((int)(this->_base_tMenu).fItemList + (i * 0x10000 >> 0xe));
  }
  return result;
}



/* ---- tMenuNFS4::UpdateTransition  [FEMENUEXTENDED.CPP:515-519] SLD-VERIFIED ---- */

void tMenuNFS4::UpdateTransition()

{
  tMenuItem *ptVar1;
  __vtbl_ptr_type (*pa_Var2) [11];
  int i;
  
  i = 0;
  ptVar1 = (this->_base_tMenu).fItemList[0];
  while (ptVar1 != (tMenuItem *)0x0) {
    ptVar1 = (this->_base_tMenu).fItemList[(short)i];
    pa_Var2 = ptVar1->_vf;
    NFS4_VCALL_AUTO((*pa_Var2)[10].pfn, (char *)ptVar1 + (int)(*pa_Var2)[10].delta,
               (int)(short)i == (this->_base_tMenu).fCurrentItem);
    i = i + 1;
    ptVar1 = *(tMenuItem **)((int)(this->_base_tMenu).fItemList + (i * 0x10000 >> 0xe));
  }
  return;
}



/* ---- tMenuNFS4::DrawItem  [FEMENUEXTENDED.CPP:523-528] SLD-VERIFIED ---- */

void tMenuNFS4::DrawItem(int item)

{
  tMenuItem *ptVar1;
  __vtbl_ptr_type (*pa_Var2) [11];
  
  ptVar1 = (this->_base_tMenu).fItemList[item];
  pa_Var2 = ptVar1->_vf;
  NFS4_VCALL_AUTO((*pa_Var2)[5].pfn, (char *)ptVar1 + (int)(*pa_Var2)[5].delta,10,item * 0x12 + 0x2b,
             item == (this->_base_tMenu).fCurrentItem);
  return;
}



/* ---- tMenuNFS4::Draw  [FEMENUEXTENDED.CPP:534-556] SLD-VERIFIED ---- */

void tMenuNFS4::Draw()

{
  short index;
  tMenuItem *ptVar1;
  __vtbl_ptr_type (*pa_Var2) [11];
  int iVar3;
  short i;
  tDrawShapeExtended drawFlags;
  
  index = (this->_base_tMenu).fTitle;
  if (-1 < index) {
    FETextRender_Title(index);
  }
  this->_base_tMenu.Initialize();
  ptVar1 = (this->_base_tMenu).fItemList[(this->_base_tMenu).fCurrentItem];
  iVar3 = ptVar1->fNumFrames;
  if ((-1 < ptVar1->fButtonImage) && (0 < iVar3)) {
    int yPos = 0x10;
    drawFlags.tint[0] = 0xcec844;
    if (*(int *)(*(int *)&FEApp /* @0x800514c0 */ + 0x22c) != 0) {
      yPos = 0x79;
    }
    DrawShapeExtended(ptVar1->fButtonImage + ((int)(*(int *)&ticks >> 4) % iVar3),0x410,0x10,yPos,0,0,&drawFlags);
  }
  i = 0;
  ptVar1 = (this->_base_tMenu).fItemList[0];
  while (ptVar1 != (tMenuItem *)0x0) {
    pa_Var2 = (this->_base_tMenu)._vf;
    NFS4_VCALL_AUTO(pa_Var2[1][0].pfn, (int)(this->_base_tMenu).fItemList + pa_Var2[1][0].delta + -0x10,(int)(short)i);
    i = i + 1;
    ptVar1 = *(tMenuItem **)((int)(this->_base_tMenu).fItemList + (i * 0x10000 >> 0xe));
  }
  return;
}



/* ---- tMenuNFS4TwoPlayer::ctor  [FEMENUEXTENDED.CPP:566-571] SLD-VERIFIED ---- */

tMenuNFS4TwoPlayer::tMenuNFS4TwoPlayer(u_int flags,tScreen *screenHandler,tMenu *nextMenu,
                 tMenu *optionsMenu,void (*OnButtonPress)(tMenuCommand&),short title,tMenuItem *firstItem,...)
  : _base_tMenuNFS4(flags,screenHandler,nextMenu,optionsMenu,OnButtonPress,title)
{
  va_list ap;

  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuNFS4TwoPlayer_vtable;
  (this->_base_tMenuNFS4)._base_tMenu.fChildMenu = (tMenu *)0x0;
  va_start(ap,firstItem);
  ((tMenu *)this)->tMenuConstructor(firstItem,ap);
  va_end(ap);
  return;
}



/* ---- tMenuNFS4TwoPlayer::dtor  [FEMENUEXTENDED.CPP:575-575] SLD-VERIFIED ---- */

tMenuNFS4TwoPlayer::~tMenuNFS4TwoPlayer()

{
  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuNFS4TwoPlayer_vtable;
  return;
}



/* ---- tMenuNFS4TwoPlayer::DrawItem  [FEMENUEXTENDED.CPP:579-587] SLD-VERIFIED ---- */

void tMenuNFS4TwoPlayer::DrawItem(int item)

{
  tMenuItem *ptVar1;
  __vtbl_ptr_type (*pa_Var2) [11];
  int y;
  
  y = 0x2b;
  if (FEApp->fPlayer == '\x01') {
    y = 0x94;
  }
  ptVar1 = (this->_base_tMenuNFS4)._base_tMenu.fItemList[item];
  pa_Var2 = ptVar1->_vf;
  NFS4_VCALL_AUTO((*pa_Var2)[5].pfn, (char *)ptVar1 + (int)(*pa_Var2)[5].delta,10,y + item * 0x12,
             item == (this->_base_tMenuNFS4)._base_tMenu.fCurrentItem);
  return;
}



/* ---- tMenuNFS4Bottom::ctor  [FEMENUEXTENDED.CPP:607-611] SLD-VERIFIED ---- */

tMenuNFS4Bottom::tMenuNFS4Bottom(u_int flags,tScreen *screenHandler,tMenu *nextMenu,
                 tMenu *optionsMenu,void (*OnButtonPress)(tMenuCommand&),short title,tMenuItem *firstItem,...)
  : _base_tMenuNFS4(flags,screenHandler,nextMenu,optionsMenu,OnButtonPress,title)
{
  va_list ap;

  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuNFS4Bottom_vtable;
  va_start(ap,firstItem);
  ((tMenu *)this)->tMenuConstructor(firstItem,ap);
  va_end(ap);
  return;
}



/* ---- tMenuNFS4Bottom::dtor  [FEMENUEXTENDED.CPP:615-615] SLD-VERIFIED ---- */

tMenuNFS4Bottom::~tMenuNFS4Bottom()

{
  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuNFS4Bottom_vtable;
  return;
}



/* ---- tMenuNFS4Bottom::Draw  [FEMENUEXTENDED.CPP:636-651] SLD-VERIFIED ---- */

void tMenuNFS4Bottom::Draw()

{
  tMenuItem *ptVar1;
  __vtbl_ptr_type (*pa_Var2) [11];
  int i;
  PSX_RECT r;
  
  r.x = 0x39;
  r.y = 0xc6;
  r.w = 0x72;
  r.h = 0xb;
  MenuNFS4_SetHelpPos(&r);
  i = 0;
  ptVar1 = (this->_base_tMenuNFS4)._base_tMenu.fItemList[0];
  while (ptVar1 != (tMenuItem *)0x0) {
    ptVar1 = (this->_base_tMenuNFS4)._base_tMenu.fItemList[(short)i];
    pa_Var2 = ptVar1->_vf;
    NFS4_VCALL_AUTO((*pa_Var2)[5].pfn, (char *)ptVar1 + (int)(*pa_Var2)[5].delta,0,0,
               (int)(short)i == (this->_base_tMenuNFS4)._base_tMenu.fCurrentItem);
    i = i + 1;
    ptVar1 = *(tMenuItem **)((int)(this->_base_tMenuNFS4)._base_tMenu.fItemList + (i * 0x10000 >> 0xe));
  }
  return;
}



/* ---- tMenuBlank::ctor  [FEMENUEXTENDED.CPP:659-663] SLD-VERIFIED ---- */

tMenuBlank::tMenuBlank(u_int flags,tScreen *screenHandler,tMenu *nextMenu,tMenu *optionsMenu
              ,void (*OnButtonPress)(tMenuCommand&),short title)
  : _base_tMenuNFS4(flags,screenHandler,nextMenu,optionsMenu,OnButtonPress,title)
{
  
  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuBlank_vtable;
  (this->_base_tMenuNFS4)._base_tMenu.fNeverAnyEnabled = 1;
  (this->_base_tMenuNFS4)._base_tMenu.VertHelp = 0;
  return;
}



/* ---- tMenuBlank::dtor  [FEMENUEXTENDED.CPP:667-667] SLD-VERIFIED ---- */

tMenuBlank::~tMenuBlank()

{
  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuBlank_vtable;
  return;
}



/* ---- tMenuBlank::Draw  [FEMENUEXTENDED.CPP:671-682] SLD-VERIFIED ---- */

void tMenuBlank::Draw()

{
  __vtbl_ptr_type (*pa_Var1) [11];
  
  if ((this->_base_tMenuNFS4).fInMenuTransition != 0) {
    pa_Var1 = (this->_base_tMenuNFS4)._base_tMenu._vf;
    NFS4_VCALL_AUTO((*pa_Var1)[7].pfn, (int)(this->_base_tMenuNFS4)._base_tMenu.fItemList + (*pa_Var1)[7].delta + -0x10);
    (this->_base_tMenuNFS4).fTransitionVal =
         (this->_base_tMenuNFS4).fTransitionVal + (short)(this->_base_tMenuNFS4).fTransitionDirection;
  }
  return;
}



/* ---- tMenuBlank::ProcessInput  [FEMENUEXTENDED.CPP:688-700] SLD-VERIFIED ---- */

void tMenuBlank::ProcessInput(tPlayer fromPlayer,tInputKeyType &keyval,tMenuCommand &command)

{
  if ((keyval == kInput_KeyType_Up) || (keyval == kInput_KeyType_Down)) {
    keyval = kInput_KeyType_AlreadyProcessed;
  }
  else {
    (this->_base_tMenuNFS4)._base_tMenu.fItemList[0] = (tMenuItem *)0x0;
    ((tMenu *)this)->ProcessInput(fromPlayer,keyval,command);
  }
  return;
}



/* ---- tMenuBlank::Initialize  [FEMENUEXTENDED.CPP:705-706] SLD-VERIFIED ---- */

void tMenuBlank::Initialize()

{
  return;
}



/* ---- tMenuBlank::DebounceKeys  [FEMENUEXTENDED.CPP:720-721] SLD-VERIFIED ---- */

long tMenuBlank::DebounceKeys()

{
  return -1;
}



/* ---- tMenuBlank::TransitionOff  [FEMENUEXTENDED.CPP:728-731] SLD-VERIFIED ---- */

void tMenuBlank::TransitionOff()

{
  (this->_base_tMenuNFS4).fTransitionDirection = '\b';
  (this->_base_tMenuNFS4).fInMenuTransition = 1;
  (this->_base_tMenuNFS4).fTransitionVal = -0x70;
  return;
}



/* ---- tMenuBlank::TransitionOn  [FEMENUEXTENDED.CPP:735-738] SLD-VERIFIED ---- */

void tMenuBlank::TransitionOn()

{
  (this->_base_tMenuNFS4).fTransitionDirection = -8;
  (this->_base_tMenuNFS4).fInMenuTransition = 1;
  (this->_base_tMenuNFS4).fTransitionVal = 0;
  return;
}



/* ---- tMenuBlank::TransitionIsFinished  [FEMENUEXTENDED.CPP:742-751] SLD-VERIFIED ---- */

void * tMenuBlank::TransitionIsFinished()

{
  u_int uVar1;
  
  if ((this->_base_tMenuNFS4).fTransitionDirection < '\x01') {
    uVar1 = (this->_base_tMenuNFS4).fTransitionVal < -0x6f ^ 1;
  }
  else {
    uVar1 = (u_int)(int)(this->_base_tMenuNFS4).fTransitionVal >> 0x1f;
  }
  (this->_base_tMenuNFS4).fInMenuTransition = uVar1;
  return (void *)((this->_base_tMenuNFS4).fInMenuTransition ^ 1);
}



/* ---- tMenuOptions::ctor  [FEMENUEXTENDED.CPP:762-767] SLD-VERIFIED ---- */

tMenuOptions::tMenuOptions(u_int flags,tScreen *screenHandler,tMenu *nextMenu,
              tMenu *optionsMenu,void (*OnButtonPress)(tMenuCommand&),short title,short player,
              tMenuItem *firstItem,...)
  : _base_tMenuNFS4(flags,screenHandler,nextMenu,optionsMenu,OnButtonPress,title)
{
  va_list ap;

  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuOptions_vtable;
  va_start(ap,firstItem);
  ((tMenu *)this)->tMenuConstructor(firstItem,ap);
  va_end(ap);
  this->fPlayer = player;
  return;
}



/* ---- tMenuOptions::dtor  [FEMENUEXTENDED.CPP:771-771] SLD-VERIFIED ---- */

tMenuOptions::~tMenuOptions()

{
  *(void **)&((this->_base_tMenuNFS4)._base_tMenu._vf) = (void *)tMenuOptions_vtable;
  return;
}



/* ---- tMenuOptions::Draw  [FEMENUEXTENDED.CPP:781-852] SLD-VERIFIED ---- */

void tMenuOptions::Draw()

{
  short numItems;
  __vtbl_ptr_type (*pa_Var2) [11];
  u_int deltaTicks;
  int itemY;
  tMenuItem *ptVar5;
  short i;
  int iVar6;
  int y;
  int x;
  u_int h;
  u_int w;
  
  numItems = ((tMenu *)this)->GetNumberEnabledItems();
  w = 0x140;
  pa_Var2 = (this->_base_tMenuNFS4)._base_tMenu._vf;
  NFS4_VCALL_AUTO((*pa_Var2)[7].pfn, (int)(this->_base_tMenuNFS4)._base_tMenu.fItemList + (*pa_Var2)[7].delta + -0x10);
  h = numItems * 0x12;
  if ((this->_base_tMenuNFS4).fInMenuTransition == 0) {
    if ((this->_base_tMenuNFS4).fTransitionDirection < '\0') {
      return;
    }
  }
  else {
    deltaTicks = ticks - this->fMenuEnterTicks;
    if (0x20 < deltaTicks) {
      deltaTicks = 0x20;
      (this->_base_tMenuNFS4).fInMenuTransition = 0;
      if ((this->_base_tMenuNFS4).fTransitionDirection < '\0') {
        return;
      }
    }
    if ((this->_base_tMenuNFS4).fTransitionDirection < '\0') {
      w = 0x140 - (deltaTicks * 0x140 >> 5);
      h = h - (h * deltaTicks >> 5);
    }
    else {
      w = deltaTicks * 0x140 >> 5;
      h = h * deltaTicks >> 5;
    }
  }
  itemY = 0xf0 - (h + 0x12);
  y = itemY >> 1;
  x = (int)(screenwidth - w) >> 1;
  itemY = itemY >> 2;
  if (this->fPlayer == 0) {
    y = y - itemY;
  }
  else if (this->fPlayer == 1) {
    y = y + itemY;
  }
  if ((this->_base_tMenuNFS4).fInMenuTransition == 0) {
    numItems = (this->_base_tMenuNFS4)._base_tMenu.fTitle;
    if (-1 < numItems) {
      FETextRender_MenuTextPositionedJustify(numItems,(short)((u_int)((x + ((int)w >> 1)) * 0x10000) >> 0x10),
                 (short)((u_int)((y + 2) * 0x10000) >> 0x10),2,textState_Hilighted,
                 textType_PopUpTitle);
    }
    i = 0;
    itemY = y + 0x12;
    while( true ) {
      ptVar5 = (this->_base_tMenuNFS4)._base_tMenu.fItemList[i];
      if (ptVar5 == (tMenuItem *)0x0) break;
      iVar6 = itemY;
      if (((ptVar5->fFlags ^ 1) & 1) != 0) {
        iVar6 = itemY + 0x12;
        NFS4_VCALL_AUTO((*ptVar5->_vf)[5].pfn, (char *)ptVar5 + (int)(*ptVar5->_vf)[5].delta,x + 10,itemY,
                   (int)i == (this->_base_tMenuNFS4)._base_tMenu.fCurrentItem);
      }
      i = i + 1;
      itemY = iVar6;
    }
  }
  PSXDrawSquare(0,x,y,w,0xc);
  PSXDrawTransSquare(0,x,y + h,w,-2,1);
  PSXDrawTransSquare(0,x,y,4,h + 4,1);
  PSXDrawTransSquare(0,x + w,y,-4,h + 4,1);
  PSXDrawTransSquare(0,x,y,w,h + 0x12,1);
  FeDraw_SetABRMode(x);
  return;
}



/* ---- tMenuOptions::TransitionOff  [FEMENUEXTENDED.CPP:855-859] SLD-VERIFIED ---- */

void tMenuOptions::TransitionOff()

{
  int iVar1;
  
  (this->_base_tMenuNFS4).fTransitionDirection = -1;
  iVar1 = ticks;
  (this->_base_tMenuNFS4).fInMenuTransition = 1;
  this->fMenuEnterTicks = iVar1;
  AudioCmn_PlayFESFX(0x12);
  return;
}



/* ---- tMenuOptions::TransitionOn  [FEMENUEXTENDED.CPP:863-874] SLD-VERIFIED ---- */

void tMenuOptions::TransitionOn()

{
  int iVar1;
  tMenuItem *ptVar2;
  tMenuOptions *ptVar3;
  
  ptVar3 = this;
  while (ptVar2 = (ptVar3->_base_tMenuNFS4)._base_tMenu.fItemList[0], ptVar2 != (tMenuItem *)0x0) {
    if (((ptVar2->fFlags ^ 1) & 1) != 0) {
      NFS4_VCALL_AUTO((*ptVar2->_vf)[8].pfn, (char *)ptVar2 + (int)(*ptVar2->_vf)[8].delta);
    }
    ptVar3 = (tMenuOptions *)&(ptVar3->_base_tMenuNFS4)._base_tMenu.fTitle;
  }
  (this->_base_tMenuNFS4).fTransitionDirection = '\x01';
  iVar1 = ticks;
  (this->_base_tMenuNFS4).fInMenuTransition = 1;
  this->fMenuEnterTicks = iVar1;
  AudioCmn_PlayFESFX(0xf);
  return;
}



/* ---- tMenuOptions::TransitionIsFinished  [FEMENUEXTENDED.CPP:878-880] SLD-VERIFIED ---- */

void * tMenuOptions::TransitionIsFinished()

{
  u_int uVar1;
  
  uVar1 = (u_int)(ticks - this->fMenuEnterTicks < 0x20);
  (this->_base_tMenuNFS4).fInMenuTransition = uVar1;
  return (void *)(uVar1 ^ 1);
}



/* ---- tMenuOptions::ProcessInput  [FEMENUEXTENDED.CPP:884-889] SLD-VERIFIED ---- */

void tMenuOptions::ProcessInput(tPlayer fromPlayer,tInputKeyType &keyval,tMenuCommand &command)

{
  if (keyval == kInput_KeyType_Square) {
    keyval = kInput_KeyType_Triangle;
  }
  this->_base_tMenuNFS4.ProcessInput(fromPlayer,keyval,command);
  return;
}



/* ---- tMenuOptions::IsSubMenu  [FEMENUEXTENDED.CPP:893-894] SLD-VERIFIED ---- */

void * tMenuOptions::IsSubMenu()

{
  return (void *)0x1;
}



/* ---- tMenuBlank::UpdateTransition  [FEMENUEXTENDED.CPP:?] SLD-FLAG:NO_SLD ---- */

void tMenuBlank::UpdateTransition()

{
  return;
}



/* ---- tMenuItemOptionsTwoItemChoice::dtor  [FEMENUEXTENDED.CPP:?] SLD-FLAG:NO_SLD ---- */

tMenuItemOptionsTwoItemChoice::~tMenuItemOptionsTwoItemChoice()

{
  return;
}



/* ---- tMenuItemOptionsLeftRightChoice::dtor  [FEMENUEXTENDED.CPP:?] SLD-FLAG:NO_SLD ---- */

tMenuItemOptionsLeftRightChoice::~tMenuItemOptionsLeftRightChoice()

{
  return;
}



/* ---- tMenuItemGoToMenuNFS4Button::Draw  [FEMENUEXTENDED.CPP:?] SLD-FLAG:NO_SLD ---- */

void tMenuItemGoToMenuNFS4Button::Draw(bool selected)

{
  u_int deltaTicks;
  short numItems;
  int itemY;
  int ypos;
  int textpix;
  int h;
  int w;
  PSX_RECT temp;
  tDrawShapeExtended drawFlags;
  PSX_RECT rect;
  int ColTextOn;
  int ColTextOff;
  
  return;
}

/* ---- MenuNFS4_SetHelpPos__FR4RECT  [@0x800?] ---- RECONSTRUCTED 2026-06-12 (Ghidra @NFS4.EXE.c:5887).
 *  Skipped from the FEMenuExtended pass; trivial PSX_RECT copy into gHelpPos (defined above @0x80052b58). */
extern "C" void MenuNFS4_SetHelpPos(PSX_RECT *r)
{
  gHelpPos.x = r->x;
  gHelpPos.y = r->y;
  gHelpPos.w = r->w;
  gHelpPos.h = r->h;
}



/* end of femenuextended.cpp */
