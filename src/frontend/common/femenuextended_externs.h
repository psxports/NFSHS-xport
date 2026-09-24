/* frontend/common/femenuextended_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_FEMENUEXTENDED_EXTERNS_H_
#define _FE_SCREENS_FEMENUEXTENDED_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;
extern tFEApplication *FEApp;
extern "C" extern tfrontEnd frontEnd;
extern "C" tPadModuleState gPadinfo;
extern "C" int ticks;
extern tGlobalMenuDefs *menuDefs;
/* class vtables (FEMenuExtended.obj-defined subclasses) */
extern __vtbl_ptr_type tMenuItemGoToMenuNFS4Button_vtable[], tMenuItemNFS4LeftRightChoice_vtable[], tMenuItemOptionsLeftRightChoice_vtable[], tMenuItemOptionsTwoItemChoice_vtable[], tMenuNFS4_vtable[], tMenuNFS4TwoPlayer_vtable[], tMenuNFS4Bottom_vtable[], tMenuBlank_vtable[], tMenuOptions_vtable[];
/* engine helpers (shared with FeMenuOptions) */
int CalcFadeVal(int, int);
int CalcFadeVal(int, int, int);
int CalcFadeVal(int, int, int, int);
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
void ScaleShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
void PSXDrawSquare(int, int, int, int, int);
void PSXDrawTransSquare(int, int, int, int, int, short);
void FeDraw_SetABRMode(int);
void Flare_2DHalo(int, int, int, int, int);
extern "C"
{
    int TextSys_WordX(int);
    int TextSys_WordY(int);
    char *TextSys_Word(int);
    int TextSys_WordFlags(int);
}
void AudioCmn_PlayFESFX(int);
void AudioCmn_PlayFESFXVol(int, int);
extern "C" tTexture_ShapeInfo *gHelpShapes;
extern tPlayer gMenu_SubMenuPlayer;
extern "C"
{
    void FETextRender_FullTextRGB(char *, short, short, int, char, short);
}
void FETextRender_Title(short);
extern "C"
{
    void FETextRender_WordWrapTextRGBJustify(char *, PSX_RECT &, int, int, int, bool);
}
extern "C"
{
    int CalcTextFadeSelToHi(...);
    int CalcTextFadeUnselToSel(...);
}
extern "C" char textDefinitions[6][14];
extern int kRGBVals[];
extern "C" int screenheight;
extern "C" int gFlip;
extern "C" int Draw_gPlayer1View;
extern "C"
{
    void *Draw_GetDRAWENV(int, int);
}
/* FEMenuExtended-specific helpers */
extern "C"
{
    void DrawShape_SubtractNFS4RectEdges(...);
    void DrawShape_NFS4RoundRectangle(...);
}
extern "C"
{
    void FETextRender_SetFont(int);
    int textpixels(char *);
    void s_upper(char *);
}
extern "C"
{
    void Font_SetBlitter(...);
    void Font_ReSetBlitter();
    void FontUpsideDownBlit(...);
}
extern "C" void MenuNFS4_SetHelpPos(PSX_RECT *);
extern "C" void CalcOnOffFade(tMenuTextType, short, short, short, int &, int &);
extern "C" int screenwidth;
void FETextRender_MenuTextPositionedJustify(short, short, short, short, tMenuTextState, tMenuTextType);
#endif
