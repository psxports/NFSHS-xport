/* eaclib/psx/sndpsxz/sdmemlu.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\sdmemlu.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   1 fn @0x800E7CEC.  SNDmemlargestunused -- find the largest free SPU-RAM gap; returns its byte size and
 *   writes its byte start to *out (both << 6 from block units).  Ghidra nfs4-f.exe.c (sdmemlu).
 *   Same SPU alloc table as sdmemman: snd_spu_alloc_count entries of {block,size} @DAT_80147e38.
 */

extern "C" unsigned short snd_spu_reverb_mode, snd_spu_block_total, snd_spu_alloc_count;
unsigned short snd_spu_reverb_mode, snd_spu_block_total, snd_spu_alloc_count; /* defs (owning TU; BSS) */
extern "C" unsigned short &DAT_80147e38;                                      /* {block,size}[] SPU alloc table */

struct SNDSpuAllocLookup
{
    unsigned short block;
    unsigned short size;
};

extern "C" int SNDmemlargestunused(int *out); /* @0x800E7CEC */

/* SNDmemlargestunused @0x800E7CEC : scan the gaps between SPU allocations for the biggest, in 64-byte
 *   blocks; report start (*out) and size, both converted to bytes (<<6). */
extern "C" int SNDmemlargestunused(int *out)
{
    SNDSpuAllocLookup *alloc = (SNDSpuAllocLookup *)&DAT_80147e38;
    int best = 0, gap, i;
    int start;

    start = 0x41;
    *out = start;
    i = 0;
    while (i < (int)(unsigned)snd_spu_alloc_count)
    {
        gap = (int)(unsigned)alloc[i].block - start;
        if (best < gap)
        {
            best = gap;
            *out = start;
        }
        start = (int)(unsigned)alloc[i].block + (int)(unsigned)alloc[i].size;
        i++;
    }
    gap = (int)(unsigned)snd_spu_reverb_mode - start;
    if (best < gap)
    {
        best = gap;
        *out = start;
    }
    *out = *out << 6;
    return best << 6;
}
