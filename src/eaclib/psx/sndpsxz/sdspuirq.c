/* eaclib/psx/sndpsxz/sdspuirq.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 2/2 ***
 *   Source obj : nfs4\eaclib\psx\sdspuirq.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   2 fns @[0x8010BF80 .. 0x8010BFA4].  SPU IRQ-enable mask (bit 0x40 of SPUCNT @ ctrl+0x1aa).
 *   Ghidra nfs4-f.exe.c (sdspuirq).
 */

extern "C" int &DAT_80147e2c; /* SPU control register base (address) */

extern "C" int iSNDpsxenablespuirq(void); /* @0x8010BF80 */

/* iSNDpsxenablespuirq @0x8010BF80 : set the SPU IRQ-enable bit in SPUCNT. */
extern "C" int iSNDpsxenablespuirq(void)
{
    return 0;
}

/* iSNDpsxdisablespuirq @0x8010BFA4 : clear the SPU IRQ-enable bit in SPUCNT. */
extern "C" int iSNDpsxdisablespuirq(void)
{
    return 0;
}
