/* eaclib/psx/sndpsxz/scdvol.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\scdvol.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col12 / SYM v3)
 *   1 fn @0x800FAA44.  SNDcdvol -- public CD-audio volume/pan setter; caches the master-scaled level and
 *   forwards (pan,vol) to the platform layer.  Ghidra nfs4-f.exe.c (scdvol) + IDA sig.
 *   Leak v9.0 MIPS 0x800FAA44..0x800FAAA8: one input, cached pan, integer zero result
 */
extern "C" int sndgs[]; /* (signed char)sndgs[0xf] byte1 (@+0x3d) = master volume */
/* CD pan/level cache -- MATERIALIZED from nfs4-f.exe @0x80136CAC (.data, NOT bss): raw 40 00 7f 00
 * -> pan=64 (center), level=127 (max). pan written by SNDcdpan, level by SNDcdvol below. extern "C"
 * so a future SNDcdpan TU resolves the same symbol; no other TU currently references either. */
extern "C"
{
    short DAT_80136cac = 64;  /* @0x80136CAC : cached CD pan */
    short DAT_80136cae = 127; /* @0x80136CAE : master-scaled CD level cache */
}
extern "C" void iSNDplatformcdpanvol(int pan, int vol); /* sdcdvol */

extern "C" int SNDcdvol(int vol_l); /* @0x800FAA44 */

/* SNDcdvol @0x800FAA44 : cache (vol_l * masterVol)/0x7f and apply the CD pan/volume. */
extern "C" int SNDcdvol(int vol_l)
{
    DAT_80136cae = (short)((vol_l * (int)*((signed char *)sndgs + 0x3d)) / 0x7f);
    /* @0x800FAA90/94: iSNDplatformcdpanvol(*(short*)0x80136CAC = cached pan, (int)(short)level). The
     * recon passed the raw caller args (vol_l, vol_r) -- but the oracle passes the cached pan and the
     * just-computed master-scaled level; vol_r is in fact unused (IDA typed 1 arg) (M06). */
    iSNDplatformcdpanvol((int)DAT_80136cac, (int)DAT_80136cae);
    return 0;
}
