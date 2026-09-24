/* frontend/common/fecredits_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FECREDITS_EXTERNS_H_
#define _FE_FECREDITS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ===== globals ===== */
extern "C" int ticks;
extern "C" extern tfrontEnd frontEnd;
extern "C" extern char *Paths_Paths[];
extern "C" tScreenMain *screenMain; /* EXT PTR @0x80051E58 */
extern int CREDFADETICKS;           /* EXT @0x80051AA0 */
static int FECredits_lastFadeTick;  /* STAT 'lasttick' */
/* cheat_MyMomSaysImCool is a tCheatCode enumerator (defined in nfs4_types.h) */

/* ===== file / mem (eaclib) ===== */

/* ===== text / draw ===== */
int CalcFadeVal(int, int);
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
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
    int FETextRender_WordWrapTextRGBJustify(char *, PSX_RECT *, int, int, int, bool);
}
extern "C" void FETextRender_SetFont(int);
extern "C"
{
    char *TextSys_Word(int);
}
extern "C"
{
    int textpixels(char *);
}
void PSXTransDrawBrightEndLine(int, int, int, int, int, int, int, int, int);

/* ===== input / audio / cheat ===== */
int FEInput_GetNoDebounceKey(int, int);
void AudioCmn_PlayFESFX(int);
extern "C"
{
    int FECheat_IsCheatEnabled(tCheatCode);
}

#endif
