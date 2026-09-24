/* eaclib/psx/eacpsxz/shpclut.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   obj nfs4\eaclib\psx\shpclut.obj ; EACPSXZ.LIB.  2 fns @[0x800F6C3C .. 0x800F6C94].  Walk a shape's
 *   sub-chunk list to its CLUT chunk and resolve the GPU clut id.  Ghidra nfs4-f.exe.c (shpclut) + IDA sigs.
 */
#include "../../../nfs4_types.h"
#include "../../../mips_semantics.h"

#ifndef AP_WIN
extern "C" short GetClut(int x, int y); /* syslib P01 */
#endif

extern "C" u_char *getshapeclut(shapetbl *shape);  /* @0x800F6C3C */
extern "C" int shapetoclutid(unsigned int *shape); /* @0x800F6C94 */

/* getshapeclut : follow the chunk chain (tag low byte == '#'/0x23) to the CLUT chunk; 0 if none. */
extern "C" u_char *getshapeclut(shapetbl *shape)
{
    u_char *cursor = (u_char *)shape;
    for (;;)
    {
        int header;
        if (cursor == 0)
            return 0;
        if ((char)*(unsigned int *)cursor == '#')
            break;
        header = *(int *)cursor;
        if (((unsigned int)header & 0xffffff00U) == 0)
            cursor = 0;
        else
            cursor = cursor + nfs4_mips_sra_s32(header, 8);
    }
    return cursor;
}

/* shapetoclutid : like getshapeclut but returns the GPU clut id (GetClut of the chunk's packed x/y). */
extern "C" int shapetoclutid(unsigned int *shape)
{
    for (;;)
    {
        if (shape == 0)
            return 0;
        if ((*shape & 0xf7) == 0x23)
            break;
        if ((*shape & 0xffffff00) == 0)
            shape = 0;
        else
            shape = (unsigned int *)((u_char *)shape + nfs4_mips_sra_s32((int)*shape, 8));
    }
    return (int)GetClut((int)(shape[3] << 0x14) >> 0x14, (int)(shape[3] << 4) >> 0x14);
}
