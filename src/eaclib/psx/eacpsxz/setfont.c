/* eaclib/psx/eacpsxz/setfont.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   obj nfs4\eaclib\psx\textset.obj ; EACPSXZ.LIB (xlsx col12 / SYM v3 FILE record line 359149).
 *   1 fn @0x800F2E94 (400 B).  setfont -- install `fontId` (a font-header pointer) as the current text font:
 *   copies its glyph metrics into the global current-font descriptor (a flat struct based at 0x80135BA0),
 *   measures the bitmap depth/stride via shapedepth, selects the per-glyph decoder (ANSI vs Shift-JIS), then
 *   clears the blit state and re-inits the text draw lists.  Returns the chosen decoder fn pointer.
 *   Ghidra nfs4-f.exe.c (setfont) + disasm-v3 (delay-slot field stores, the two shapedepth calls,
 *   blockclear(&0x80135BD4,0x40)) + IDA sig.  Plain C (unmangled symbol) -> free function; the
 *   DAT_* globals are the shared current-font descriptor (the same ones textfor/textcrnt/textcode reference).
 *
 *   Font header layout read (offsets into `fontId`):
 *     +0x0a u16 glyphCount   +0x0e u16 flags(&3==2 => Shift-JIS)   +0x10..0x13 i8 metrics(ascent/descent...)
 *     +0x14 i32 glyphTblOff  +0x1c i32 shapeOff   +0x20 encoded-data start (probed by geti)
 */
#include "../../../nfs4_types.h"

extern "C" unsigned int geti(void *p, char nbits);     /* getm */
extern "C" int shapedepth(unsigned char *shape);       /* shpdepth */
extern "C" int decodeansi(unsigned char **cursor);     /* textcode */
extern "C" int decodeshiftjis(unsigned char **cursor); /* isqrttbl (obj name misnomer) */
extern "C" void blockclear(void *dst, int n);          /* blkfill */
extern "C" void inittextdraw(void);                    /* textpsx (game) */

extern "C" FontDecoder setfont(intptr fontId); /* @0x800F2E94 */

/* setfont @0x800F2E94 : install font header `fontId` as the current text font; returns its glyph decoder. */
extern "C" FontDecoder setfont(intptr fontId)
{
    unsigned char *font = (unsigned char *)fontId;
    unsigned char *shape;
    FontDecoder decode;
    int depth;

    currentfont.defaultMetric = 100;
    currentfont.metric10 = (int)*(signed char *)(font + 0x10);
    currentfont.metric11 = (int)*(signed char *)(font + 0x11);
    currentfont.metric12 = (int)*(signed char *)(font + 0x12);
    currentfont.metric13 = (int)*(signed char *)(font + 0x13);
    currentfont.metricSum24 = (int)*(signed char *)(font + 0x13) + (int)*(signed char *)(font + 0x12);
    shape = font + *(int *)(font + 0x1c);
    currentfont.metricSum28 = (int)*(signed char *)(font + 0x13) + (int)*(signed char *)(font + 0x12);
    currentfont.glyphCount = (int)*(unsigned short *)(font + 10);
    currentfont.active = 1;
    currentfont.stateB0 = 0;
    currentfont.stateAC = 0;
    currentfont.glyphTable = (charactertbl *)(font + *(int *)(font + 0x14));
    currentfont.fontHeader = font;
    currentfont.shape = shape;
    currentfont.bitmapDepth = shapedepth(shape);
    depth = shapedepth(shape);
    currentfont.bitmapRowStride = (int)((unsigned int)(*(short *)(shape + 4) * depth + 0x1f) & 0xffffffe0) >> 3;

    if ((*(unsigned short *)(font + 0xe) & 3) == 2)
    {
        decode = decodeshiftjis; /* explicit Shift-JIS flag */
    }
    else if (currentfont.glyphCount < 0x100)
    {
        /* small glyph table: probe the encoded stream -- ANSI if the first code is < 0x100 */
        if (geti((void *)(font + 0x20), 2) < 0x100)
            decode = decodeansi;
        else
            decode = decodeshiftjis;
    }
    else
    {
        decode = decodeshiftjis; /* large table => multi-byte */
    }

    currentfont.state2C = 0;
    currentfont.state30 = 0;
    currentfont.stateB4 = 0;
    currentfont.decoder = decode;
    blockclear(currentfont.blitState, 0x40); /* currentfont+0x34 */
    inittextdraw();
    currentfont.stateA4 = 0;
    return decode;
}
