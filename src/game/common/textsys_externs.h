#include "../../lib/libfns.h"
/* textsys_externs.h -- extern decls for game/psx/textsys.cpp (NFS4 PSX text/word system). */
#ifndef TEXTSYS_EXTERNS_H
    #define TEXTSYS_EXTERNS_H

/* ---- libc + harvested + SYM ---- */
extern "C" extern char *Paths_Paths[];

extern "C" char *wordFile;        /* word-data blob (char*) */
extern "C" char *langFileName[6]; /* per-language filenames (dims 1 6) */

#endif
