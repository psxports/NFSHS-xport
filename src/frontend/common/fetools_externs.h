/* frontend/common/fetools_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FETOOLS_EXTERNS_H_
#define _FE_FETOOLS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ---- globals ---- */
extern "C" extern "C" char *Paths_Paths[];
extern char *font12;
extern char *font18;
extern char *fontTitle;
extern short currentSize; /* SYM short (was wrongly int); fetextrender_externs.h agrees */

/* ---- libc / psyq ---- */

/* ---- engine / front-end helpers ---- */
extern "C"
{
    int DrawShapeExtended(int shape, int a, int x, int y, int e, int f, tDrawShapeExtended *flags);
}
extern "C"
{
    int Font_ExitFromGame(void);
}
extern "C"
{
    int Font_LoadFont(char *data, int a, int b, char c);
}
extern "C"
{
    int Font_DeInit(void);
}
extern "C"
{
    char *TextSys_Word(int id);
}

#endif
