/* eaclib/psx/sndpsxz/sclcptch.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\sclcptch.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x80101900 .. 0x801019BC].  Pitch calculation (cents/detune -> SPU pitch).
 *   Ghidra nfs4-f.exe.c L166180..166251.
 */

#include "../../../mips_semantics.h"

extern "C" int sndgs[];
extern "C" signed char snddefaultenvelope; /* default sweep/envelope bytes @0x801371C4 */
/* Retail sndcents @0x801370C4, materialized byte-exact from NFS4.EXE. */
extern "C" const unsigned char sndcents[256];

extern "C" int iSNDdetunetolinear(int detune); /* @0x80101900 */

/* iSNDdetunetolinear @0x80101900 : convert a detune value in cents (0x4B0 = 1200 cents = one octave) to a
 *   12.12 linear pitch multiplier, octave-folding then interpolating the fractional cents through a curve
 *   table. */
extern "C" int iSNDdetunetolinear(int detune)
{
    int mul = 0x1000;
    int idx;
    for (; 0x4af < detune; detune -= 0x4b0) /* octave up */
        mul = nfs4_mips_sll_s32(mul, 1);
    for (; detune < -0x4af; detune += 0x4b0) /* octave down */
        mul = nfs4_mips_sra_s32(mul, 1);
    idx = nfs4_mips_sra_s32(nfs4_mips_mult_s32(detune, 0x369d), 0x10);
    if (idx < -0xff)
        idx = -0xff;
    if (idx < 0)
        mul = nfs4_mips_sra_s32(nfs4_mips_mult_s32(mul, sndcents[0x100 + idx] + 0x100), 9);
    else
        mul = nfs4_mips_sra_s32(nfs4_mips_mult_s32(mul, sndcents[idx] + 0x100), 8);
    return mul;
}

/* iSNDcalcpitch @0x801019BC : recompute a voice's SPU pitch from its base note + modulation sources
 *   (envelope @+0x4C / LFO @+0x54), caching the linear multiplier at +0x5E and the final SPU pitch at
 *   +0x62. */
extern "C" int iSNDcalcpitch(int note)
{
    int v = sndgs[0x25] + note * 100;
    int pitch;
    char c;

    if (*(short *)(v + 0x5e) == 0)
    { /* not yet cached -> compute the linear multiplier */
        int cents = (int)*(short *)(v + 0x5c);
        if (*(short *)(v + 0x5a) != 0)
        { /* envelope-driven detune */
            if (*(int *)(v + 0x4c) == 0)
                c = *(char *)(v + 0x2f);
            else
                c = *(char *)(*(int *)(v + 0x4c) + (int)*(char *)(v + 0x2f));
            cents += ((c - 0x40) * (int)*(short *)(v + 0x5a) >> 6);
        }
        if (*(int *)(v + 0x54) != 0)
        { /* LFO-driven detune */
            cents += ((*(char *)(*(int *)(v + 0x54) + (unsigned)*(unsigned char *)(v + 0x3b)) - 0x40) * (int)*(short *)(v + 0x58) >> 6);
        }
        pitch = iSNDdetunetolinear(cents);
        *(short *)(v + 0x5e) = (short)pitch;
    }
    pitch = (int)((unsigned)*(unsigned short *)(v + 0x5e) * (unsigned)*(unsigned short *)(v + 0x60)) >> 0xc;
    *(short *)(v + 0x62) = (short)pitch; /* final SPU pitch */
    return pitch;
}
