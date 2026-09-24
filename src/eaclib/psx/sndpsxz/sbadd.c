/* eaclib/psx/sndpsxz/sbadd.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\sbadd.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   1 fn @0x800E7DEC.  SNDbankadd -- register a new sound bank: allocate a slot, record its data pointer
 *   in the bank table, install the exit-time bank-remove hook, and download it to SPU.
 *   Ghidra nfs4-f.exe.c (sbadd) + disasm: a2 is the bank DATA pointer (passed twice to iSNDdownloadbank),
 *   a1 is the output slot pointer; iSNDbankalloc returns the slot (Ghidra void-typed it).
 */

#include "../../../nfs4_types.h"

extern "C" int sndgs[];
extern "C" int iSNDbankalloc(void);                                 /* sballoc */
extern "C" void SNDbankremove(void);                                /* sbremove (the @0x80147860[0x1f] exit hook) */
extern "C" int iSNDdownloadbank(intptr bankData, intptr bankData2); /* sbdload */

extern "C" int SNDbankadd(int *bank_out, intptr bankData); /* @0x800E7DEC */

/* SNDbankadd @0x800E7DEC : add the bank at `bankData`, writing its slot id to *bank_out.  Returns the
 *   download result, or -10 if audio is down. */
extern "C" int SNDbankadd(int *bank_out, intptr bankData)
{
    int slot;
    int *e;
    if ((char)sndgs[0xf] == 0)
        return -10;
    slot = iSNDbankalloc();
    *bank_out = slot;
    e = (int *)(sndgs[0x26] + slot * 0xc);
    e[0] = (int)bankData;                     /* PORTABILITY-REVIEWED: 32-bit PSX sound-bank table word */
    e[1] = (int)bankData;                     /* PORTABILITY-REVIEWED: 32-bit PSX sound-bank table word */
    sndgs[0x1f] = (int)(intptr)SNDbankremove; /* PORTABILITY-REVIEWED: 32-bit PSX hook word */
    return iSNDdownloadbank(bankData, bankData);
}
