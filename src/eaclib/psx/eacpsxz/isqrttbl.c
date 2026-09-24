/* eaclib/psx/eacpsxz/isqrttbl.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   obj nfs4\eaclib\psx\isqrttbl.obj ; EACPSXZ.LIB.  2 fns @[0x801069C4 .. 0x801069EC].  Shift-JIS text
 *   decode (the obj name is a misnomer -- it holds the SJIS remap, not an isqrt table).
 *   Ghidra nfs4-f.exe.c + IDA sigs.
 */
extern "C" unsigned short DAT_8013bd50[0x60]; /* @0x8013BD50 : ASCII(0x20..0x7f)->SJIS [0x60] */

extern "C" unsigned int remapshiftjiscode(unsigned int c); /* @0x801069C4 */
extern "C" int decodeshiftjis(unsigned char **cursor);     /* @0x801069EC */

/* remapshiftjiscode : map a 1-byte ASCII code (0x20..0x7f) to its full-width SJIS code. */
extern "C" unsigned int remapshiftjiscode(unsigned int c)
{
    if (c - 0x20 < 0x60)
        c = (unsigned int)DAT_8013bd50[c - 0x20]; /* 0x801069D8: index << 1, then lhu */
    return c;
}

/* decodeshiftjis : next SJIS char from a cursor -- 1 byte (remapped) if high bit clear, else a 2-byte code. */
extern "C" int decodeshiftjis(unsigned char **cursor)
{
    unsigned char *p = *cursor;
    unsigned char b1 = *p;
    unsigned char *next = p + 1;
    unsigned int code;
    if ((b1 & 0x80) == 0)
    {
        code = remapshiftjiscode((unsigned int)b1);
    }
    else
    {
        unsigned char b2 = *next;
        next = p + 2;
        code = ((unsigned int)b1 << 8) | b2;
    }
    *cursor = next;
    return (int)(code & 0xffff);
}
