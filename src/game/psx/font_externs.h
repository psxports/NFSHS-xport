#include "../../lib/libfns.h"
/* font_externs.h -- extern decls for game/psx/font.cpp (NFS4 PSX text/font rasterizer).
 * Types come from ../../nfs4_types.h (charactertbl, cluttbl, shapetbl, DR_MODE, PSX_RECT). */
#ifndef FONT_EXTERNS_H
    #define FONT_EXTERNS_H

/* glyph blitter function pointer: (x, y, fontPixmap, w, h, charactertbl*, tpage) -> void */
typedef void fn_void(int, int, void *, int, int, charactertbl *, int);

/* ---- font module state globals (SYM) ---- */
extern "C" int font_clutx;            /* 0x8013d854 */
extern "C" int font_cluty;            /* 0x8013d858 */
extern "C" u_long font_tint;          /* 0x8013d85c */
extern "C" u_long font_abr;           /* 0x8013d860 */
extern "C" u_short gFontClut;         /* 0x8013d864 */
extern "C" u_char gFontSpaceWidth;    /* 0x8013d866 */
extern "C" u_short font_currentTPage; /* 0x8013d868 */
extern fn_void *gCurrentBlitter;      /* 0x8013ddec  (PTR FCN VOID) */
extern "C" cluttbl shpfontclut;       /* 0x8011fdb0  (48 bytes) */
extern "C" long colourRGB[16];        /* 0x8011fd70  (ARY LONG, 64 bytes) */
/* currentfont is the shared typed descriptor declared in nfs4_types.h. */

/* ---- render packet/palette ring (shared) ---- */
extern "C" char *&Render_gPacketPtr;
extern "C" char *&Render_gPalettePtr;

/* ---- PsyQ libgpu ---- */

/* ---- game texture manager ---- */
extern "C"
{
    extern void Texture_GetClutId(int id, int *px, int *py);
}
extern void Texture_MenuReleaseClutId(short id);
extern void Texture_Vramf(shapetbl *s, int x, int y, int w, int h);

/* ---- eaclib (EACPSXZ) text/mem helpers ---- */
/* read n-byte big-endian field */

#endif
