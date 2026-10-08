/* eaclib/psx/sndpsxz/splay.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\splay.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x800E7A30 .. 0x800E7A68].  SNDplay -- play a sound described by an SND play-info block.
 *   Ghidra nfs4-f.exe.c (splay) + IDA sigs (the `this` __thiscall is the play-info pointer).
 *
 *   play-info `info`: [0] = patch index, [1] = bank id (byte).
 *   bank @ (bankid*0xc + sndgs[0x26]): +4 type(b), +6 patch count(u16), +0xc/+0x14 patch ptr table.
 */
#include "../../../nfs4_types.h"
#include <stddef.h>

static_assert(sizeof(SNDPLAYOPTS) == 20, "SND play descriptor size");
static_assert(offsetof(SNDPLAYOPTS, bhandle) == 4, "SND bank offset");
static_assert(offsetof(SNDPLAYOPTS, vol) == 8, "SND volume offset");
static_assert(offsetof(SNDPLAYOPTS, azimuth) == 16, "SND azimuth offset");

extern "C" int sndgs[];
extern "C" int iSNDvalidbank(int bankid);                            /* sbvalid */
extern "C" int iSNDplaytaggedpatch(unsigned char *patch, int *info); /* stagpat */

extern "C" int cSNDplay(SNDPLAYOPTS *info); /* @0x800E7A68 */
extern "C" int SNDplay(SNDPLAYOPTS *info);  /* @0x800E7A30 */

/* SNDplay @0x800E7A30 : play `info` if the audio system is up. */
extern "C" int SNDplay(SNDPLAYOPTS *info)
{
    if ((char)sndgs[0xf] != 0)
        return cSNDplay(info);
    return -10;
}

/* cSNDplay @0x800E7A68 : resolve the play-info's (bank, patch) to a tagged patch and play it. */
extern "C" int cSNDplay(SNDPLAYOPTS *info)
{
    int patch, bank;
    intptr pp;
    if (-1 < iSNDvalidbank((int)info->bhandle))
    {
        patch = info->patnum;
        bank = *(int *)(info->bhandle * 0xc + sndgs[0x26]);
        if (patch < 0)
            return -8;
        if (patch < (int)(unsigned)*(unsigned short *)(bank + 6))
        {
            if (*(char *)(bank + 4) == 4)
                pp = *(int *)(bank + patch * 4 + 0x14);
            else
                pp = *(int *)(bank + patch * 4 + 0xc);
            return iSNDplaytaggedpatch((unsigned char *)pp, (int *)info);
        }
    }
    return -8;
}
