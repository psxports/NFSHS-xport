/* frontend/common/fevideowall_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FEVIDEOWALL_EXTERNS_H_
#define _FE_FEVIDEOWALL_EXTERNS_H_
#include "../../nfs4_types.h"

extern "C" int ticks;

/* TV tiles (FETv) */
extern "C"
{
    void InitTV(tTVConfig *, tTexture_ShapeInfo *, short);
}
extern "C"
{
    void DrawTV(tTVConfig *);
}
extern "C"
{
    void DrawTVLines(tTVConfig *);
}
extern "C"
{
    void TurnOnTV(tTVConfig *);
}
extern "C"
{
    void TurnOffTV(tTVConfig *);
}

/* drawing / text */
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
int CalcFadeVal(int, int);
extern "C"
{
    void FETextRender_SetABR(int, bool);
}
extern "C"
{
    void FETextRender_FullTextRGB(char *, short, short, int, char, short);
}
extern "C"
{
    char *TextSys_Word(int);
}

#endif
