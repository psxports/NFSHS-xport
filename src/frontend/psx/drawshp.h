/* frontend/psx/drawshp.h - reconstructed declarations for DRAWSHP.CPP (C++ TU) */
#ifndef _FRONTEND_PSX_DRAWSHP_H_
#define _FRONTEND_PSX_DRAWSHP_H_
#include "../../nfs4_types.h"
#include "drawshp_externs.h"

/* DRAWSHP.CPP is C++ (cfront-mangled in SYM) -> normal C++ linkage. */
extern "C"
{
    void DrawShape_SubtractNFS4RectEdges(PSX_RECT &rect);
}
extern "C"
{
    void DrawShape_NFS4RoundRectangle(int textID, PSX_RECT &position, short selected);
}
extern "C"
{
    void DrawShape_NFS4Rectangle(PSX_RECT &position);
}
extern "C"
{
    void DrawShape_NFS4TransRectangle(PSX_RECT &r, short opacity);
}

extern int kNoColor; /* 0x800529d0 (EXT, defined in drawshp.cpp) */

#endif