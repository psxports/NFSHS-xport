/* frontend/common/femenuoptions_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_FEMENUOPTIONS_EXTERNS_H_
#define _FE_SCREENS_FEMENUOPTIONS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;
extern tFEApplication *FEApp;
extern "C" extern tfrontEnd frontEnd;
extern "C" tPadModuleState gPadinfo;
extern "C" int ticks;
extern short MENUUSERNAME_STARTY; /* @0x800529b2 ScreenUserName.obj-owned (cross-TU) */
extern "C" extern "C" char *Paths_Paths[];
extern tGlobalMenuDefs *menuDefs;
/* class vtables (FeMenuOptions.obj-defined subclasses) */
extern __vtbl_ptr_type tMenuItemGoToMenuButtonFade_vtable[], tMenuItemLeftRightFade_vtable[], tOptionsMenu_vtable[], tInsideBoxMenu_vtable[], tMenuItemSlidingMenu_vtable[], tMenuItemSlidingActivated_vtable[], tMenuItemDisplayLeftRightChoice_vtable[], tMenuItemOnOffLeftRightChoice_vtable[], tMenuItemLeftRightAudioSlider_vtable[], tInsideBoxSongMenu_vtable[], tMenuItemControllerLeftRightChoice_vtable[], tInsideBoxLeftRightSlider_vtable[], tInsideBoxTwoWaySlider_vtable[], tUserNameMenuItem_vtable[], tMemoryCardMenuItem_vtable[], tInsideBoxControllerLeftRightSlider_vtable[];
/* engine helpers */
int CalcFadeVal(int, int);
int CalcFadeVal3(int, int, int);
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
    void FETextRender_MenuTextPositioned(short, short, short, tMenuTextState, tMenuTextType);
}
void FETextRender_MenuTextPositionedJustify(short, short, short, short, tMenuTextState, tMenuTextType);
extern "C"
{
    int TextSys_WordX(int);
    int TextSys_WordY(int);
    char *TextSys_Word(int);
    int textpixels(char *);
}
void AudioCmn_PlayFESFX(int);
void AudioCmn_PlayFESFXVol(int, int);
/* batch externs */
extern tScreenAudio *screenAudio;
extern tScreenControllerConfig *screenControllerConfig;
extern "C" tTexture_ShapeInfo *gHelpShapes;
extern tPlayer gMenu_SubMenuPlayer;
extern "C" int menu_kUserNameRows;
int CalcFadeVal(int, int, int);
int CalcFadeVal(int, int, int, int);
extern "C"
{
    void FETextRender_FullTextRGB(char *, short, short, int, char, short);
}
void FETextRender_FullText(char *, short, short, tMenuTextType, tMenuTextState, short);
extern "C"
{
    void FETextRender_Title(short);
    void FETextRender_SetABR(int, bool);
}
extern "C"
{
    void FETextRender_WordWrapTextRGBJustify(char *, PSX_RECT &, int, int, int, bool);
}
extern "C"
{
    int CalcTextFadeSelToHi(...);
    int CalcTextFadeUnselToSel(...);
}
extern "C"
{
    void DrawSlider(short, short, short, short, short, short, short, short, short, bool, bool, short, short);
}
extern "C"
{
    void AudioMus_SysStartUp(...);
    void AudioMus_SysCleanUp(...);
    void AudioMus_StopSong(...);
    void AudioMus_PlaySong(...);
}
extern "C"
{
    int AudioMus_GetSongList(...);
    void AudioMus_Volume(int);
}
extern "C"
{
    int FECheat_ActivateCheat(char *);
    void s_lower(char *);
    void s_upper(char *);
}
void FeTools_DrawPSXButton(u_char, u_short, int, int);
void Font_TextColor(int);
void Font_TextTint(int);
void Font_TextXY(char *, int, int);
void DrawShapeFlat(int, int, int, int, int);
extern "C" char textDefinitions[6][14];
extern int kRGBVals[];
extern "C" int screenheight;
int GetHelpText(tScreenControllerConfig *);
extern "C" SPEECHINFO ginfo;
extern "C" int gFlip;
extern "C" int Draw_gPlayer1View;
extern "C"
{
    void *Draw_GetDRAWENV(int, int);
}
extern "C"
{
    int TextSys_WordFlags(int);
}
void Stattool_SamNelsonsUpperLowerStringConverterForRecords(char *);
extern short _UNK_80010a02, _UNK_80010a06, _UNK_80010a0a;
extern "C"
{
    void FeMenuOptions_drawLeftFlareOut(int, int, int);
    void FeAudio_AsyncPlaySpeech(...);
}
extern "C"
{
    int FECheat_ActivateBonusByCode(char *);
    void CalcOnOffFade(tMenuTextType, short, short, short, int &, int &);
}
#endif
