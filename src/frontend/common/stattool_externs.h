/* frontend/common/stattool_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_COMMON_STATTOOL_EXTERNS_H_
#define _FE_COMMON_STATTOOL_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C" extern tfrontEnd frontEnd;
extern "C" extern char *Paths_Paths[50];
extern "C" tRecordBuffer Stats_gTrackRecords[187];
extern "C" extern GameSetup_tData GameSetup_gData;
extern "C" char GameSetup_gPersonalityNames[15][8];

/* game C++ helpers + PsyQ/eaclib (cfront-mangled / C; normal C++ linkage) */
extern "C"
{
    void s_lower(char *string);
}
extern "C"
{
    char *TextSys_Word(int wordnum);
}
extern "C"
{
}

#endif