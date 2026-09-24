/* eaclib/psx/eacpsxz/textfor.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   obj nfs4\eaclib\psx\textfor.obj ; EACPSXZ.LIB.  2 fns @[0x800F4470 .. 0x800F4510].  Look up a font glyph
 *   record by character code -- direct index then binary search.  Ghidra nfs4-f.exe.c + IDA sigs.
 *   (The shared descriptor supplies the glyph count to the binary search.)
 */
#include "../../../nfs4_types.h"

extern "C" unsigned int geti(void *p, char nbits); /* getm */

extern "C" charactertbl *textbsearch(unsigned int key, charactertbl *base, int count, int stride); /* @0x800F4470 */
extern "C" charactertbl *getcharacter(unsigned int code);                                          /* @0x800F4510 */

/* textbsearch @0x800F4470 : binary-search `count` records (stride `stride`) for the one whose 2-byte key
 *   matches `key`; returns its address, or 0. */
extern "C" charactertbl *textbsearch(unsigned int key, charactertbl *base, int count, int stride)
{
    charactertbl *entry;
    for (;;)
    {
        if (count == 0)
            return (charactertbl *)0;
        entry = (charactertbl *)((unsigned char *)base + (count >> 1) * stride);
        {
            unsigned int v = geti((void *)entry, 2);
            if (key == v)
                break;
            if (0 < (int)(key - v))
            {
                base = (charactertbl *)((unsigned char *)entry + stride);
                count = count - 1;
            }
        }
        count = count >> 1;
    }
    return entry;
}

/* getcharacter @0x800F4510 : glyph record for `code` -- try the direct slot (code-0x20), else binary-search. */
extern "C" charactertbl *getcharacter(unsigned int code)
{
    charactertbl *base = currentfont.glyphTable;
    charactertbl *entry = (charactertbl *)((unsigned char *)base + (int)(code - 0x20) * 0xb);
    unsigned int v = geti((void *)entry, 2);
    if (v != code)
        entry = textbsearch(code, base, currentfont.glyphCount, 0xb);
    return entry;
}
