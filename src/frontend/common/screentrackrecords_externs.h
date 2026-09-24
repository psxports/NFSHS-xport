/* frontend/screens/screentrackrec_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENTRACKREC_EXTERNS_H_
#define _FE_SCREENS_SCREENTRACKREC_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C" extern tfrontEnd frontEnd;
extern "C" int ticks;
extern int kRGBVals[28];
extern "C" char textDefinitions[14][6];
extern "C" extern tTexture_ShapeInfo *gCurrentShapes;
extern int NewRecords[8];
extern int NewBestLap;
void trap(int code);
extern "C"
{
    int textpixels(char *str);
}
int CalcFadeVal(int col1, int amount); /* 2-arg overload */

/* called game/FE/audio/PsyQ functions (Ghidra-dumped signatures) */
extern "C"
{
    char *TextSys_Word(int wordnum);
}
extern "C"
{
    int TextSys_WordY(int wordnum);
}
extern "C"
{
    void DrawShapeExtended(int index, int flags, int x, int y, int fade, int abr, tDrawShapeExtended *extra);
}
void FETextRender_FullText(char *sMenuText, short x, short y, tMenuTextType textType, tMenuTextState textState, short justify);
void Flare_2DHalo(int x, int y, int scalex, int scaley, int type);
void DrawBackgroundImage(tScreen *thisobj, int startShape, int numShapes, tTexture_ShapeInfo *shapes, int flip_axis);
extern "C"
{
    void StatChk_ClearNewRecords(void);
}
void Stattool_GetRecords(short nShowTrack, tRecordBuffer *TrackRecords);
short Front_GetTrackRaced(void);
void PSXDrawSquare(int col, int x, int y, int w, int h);
void Stattool_ParseTime(int nTime, char *sLapTime);
extern "C"
{
    int TextSys_WordX(int wordnum);
}
int CalcFadeVal(int col1, int col2, int amount);
void PSXDrawBrightEndLine(int col, int x, int y, int w, int h, int side, int fade, int darksides);
extern "C"
{
    void FETextRender_FullTextRGB(char *sMenuText, short x, short y, int col, char size, short justify);
}
int Front_GetLapsForType(void);

#endif