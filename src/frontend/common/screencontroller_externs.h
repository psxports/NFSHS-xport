/* frontend/common/screencontroller_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENCONTROLLER_EXTERNS_H_
#define _FE_SCREENS_SCREENCONTROLLER_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C" extern tfrontEnd frontEnd;
extern "C" int ticks;
extern tGlobalMenuDefs *menuDefs;
extern int kRGBVals[28];
extern "C" char textDefinitions[14][6];
int CalcFadeVal(int col1, int amount);               /* 2-arg overload */
int CalcFadeVal(int col1, int col2, int f1, int f2); /* 4-arg overload */
void trap(int code);
extern "C"
{
    int textpixels(char *str);
}
extern tFEApplication *FEApp;
extern "C" tPadModuleState gPadinfo; /* pad-info (84B, SYM anon .63fake tag = tPadModuleState) */
extern "C" int mappings[3][13][3];   /* PSX->FE key mappings */
/* menu helpers + Pad actuator (dumped overloads wrong-class/const; real call types per this TU) */
void SetMenu(tMenuItemSlidingMenu *thisobj, short i, void *menu);
void *TransitionIsFinished(tOptionsMenu *thisobj);
/* libmath soft-float runtime (REAL SYM fns @0x800f####; variadic: Ghidra splits doubles into int pairs) */
extern "C"
{
    double __muldf3(double, double);
    int __fixdfsi(double);
}

/* called game/FE/audio/PsyQ functions (Ghidra-dumped signatures) */
extern "C"
{
    void FETextRender_SetABR(int abr, bool trans);
}
void Flare_2DHalo(int x, int y, int scalex, int scaley, int type);
extern "C"
{
    void Controller_SetRamp(void);
}
extern "C"
{
    void Front_ResetPSXController(int player, int config);
}
extern "C"
{
    void UploadSwapShapes(tScreen *thisobj, int numSwapShapes);
}
int GetPSXPadValue(int value, int player);
void PSXDrawSquare(int col, int x, int y, int w, int h);
int CalcFadeVal(int col1, int col2, int amount);
extern "C"
{
    void FETextRender_FullTextRGB(char *sMenuText, short x, short y, int col, char size, short justify);
}
int InGame_GetDevice(int control);
extern "C"
{
    char *TextSys_Word(int wordnum);
}
void AsyncLoadSwapShapeFile(tScreen *thisobj, char *fileName);
void ScaleShapeExtended(int index, int flags, int x, int y, int fade, int abr, tDrawShapeExtended *extra);
extern "C"
{
    void DrawShapeExtended(int index, int flags, int x, int y, int fade, int abr, tDrawShapeExtended *extra);
}
extern "C"
{
    short Run(tDialogInteractive *thisobj);
}
void PSXDrawTransSquare(int col, int x, int y, int w, int h, short opacity);
void AudioCmn_PlayFESFX(int SFXnum);
void FeDraw_SetABRMode(int abr);
extern "C"
{
    void *IsShapeFileLoaded(tScreen *thisobj, tShapeInformation *shapes);
}
extern "C" void FETextRender_SetFont(int size);

#endif