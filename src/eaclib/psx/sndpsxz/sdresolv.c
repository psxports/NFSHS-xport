/* eaclib/psx/sndpsxz/sdresolv.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\sdresolv.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x8010B75C .. 0x8010B958].  Resolve/release a bank patch's SPU sample data: DMA the sample
 *   into SPU RAM and record the SPU address (or free it).  Ghidra nfs4-f.exe.c (sdresolv) + IDA sigs.
 *
 *   Tags consumed while scanning a patch's resolve header (until 0xfe): 0x88 = sample offset, 0x82 =
 *   channel count, 0x85 = sample byte size, 0x8a = the field that receives the resolved SPU address.
 *   PATCH RESOLVE TABLE (the `patch`/scratch arg): {ramOffset, spuAddr}[] terminated by -1.
 */
#include "../../../nfs4_types.h"

extern "C" int iSNDgettag(intptr *cursor, unsigned int *outId, int *outVal, intptr *outPtr); /* sgettag */
extern "C" int iSNDpsxmalloc(int size);                                                      /* sdmemman */
extern "C" void iSNDpsxfree(void *p);                                                        /* sdmemman */
extern "C" int iSNDdmqueuesplit(intptr srcRam, int dstSpu, int len, unsigned char prio);     /* sdma */
extern "C" int iSNDdmcomplete(int handle);                                                   /* sdma */

extern "C" int iSNDplatformresolve(intptr cursor, intptr bank, int *patch); /* @0x8010B75C */
extern "C" int iSNDplatformremove(intptr cursor, int *patch);               /* @0x8010B958 */

/* iSNDplatformresolve @0x8010B75C : load a patch's sample into SPU RAM (unless already resolved), recording
 *   the SPU address in the 0x8a field and the resolve table.  Returns 7 / -6 (out of SPU memory). */
extern "C" int iSNDplatformresolve(intptr cursor, intptr bank, int *patch)
{
    intptr tagCursor;
    unsigned int id;
    int val;
    intptr ptr;
    int offset = 0, count = 1, size = 0;
    int *spuField = 0; /* the 0x8a field that receives the SPU address */
    int idx = 0, blocks, need, buf, dma;
    int *e;

    tagCursor = cursor;
    while ((id = 0, iSNDgettag(&tagCursor, &id, &val, &ptr) != 0) && id != 0xfe)
    {
        if (id == 0x88)
            offset = val;
        else if (id == 0x82)
            count = val;
        else if (id == 0x85)
            size = val;
        else if (id == 0x8a)
            spuField = (int *)ptr;
    }
    if (bank != 0)
    {
        e = patch; /* find an existing resolve for this offset */
        while (*e != -1)
        {
            if (*e == offset)
            {
                *spuField = e[1];
                break;
            }
            idx++;
            e = e + 2;
        }
        if (*spuField != 0)
            return 7; /* already resolved */
        blocks = size / 0x1c;
        if (size != blocks * 0x1c)
            blocks = blocks + 1;
        need = blocks * count * 0x10;
        buf = iSNDpsxmalloc(need);
        if (buf == 0)
            return -6;
        dma = iSNDdmqueuesplit(bank + offset, buf, need, 1);
        e = patch + idx * 2;
        *spuField = buf;
        e[0] = offset;
        e[1] = buf;
        do
        {
        } while (iSNDdmcomplete(dma) == 0);
    }
    return 7;
}

/* iSNDplatformremove @0x8010B958 : release a patch's resolved SPU data -- record it in the remove table and
 *   free the SPU block. */
extern "C" int iSNDplatformremove(intptr cursor, int *patch)
{
    intptr tagCursor;
    unsigned int id;
    int val;
    intptr ptr;
    int *spuField = 0;
    int i = 0;
    int *e;

    tagCursor = cursor;
    while ((id = 0, iSNDgettag(&tagCursor, &id, &val, &ptr) != 0) && id != 0xfe)
    {
        if (id == 0x8a)
            spuField = (int *)ptr;
    }
    if (*patch != -1)
    {
        e = patch;
        do
        {
            e = e + 2;
            if (*spuField == patch[i * 2]) /* already removed */
                return 0;
            i++;
        } while (*e != -1);
    }
    patch[i * 2] = *spuField;
    if (*spuField != 0)
        iSNDpsxfree((void *)*spuField);
    return 0;
}
