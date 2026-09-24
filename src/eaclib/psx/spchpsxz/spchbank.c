/* eaclib/psx/spchpsxz/spchbank.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 8/8 ***
 *   Source obj : nfs4\eaclib\psx\spchbank.obj ; archive C:\nfs4\EACLIB\PSX\SPCHPSXZ.LIB (xlsx col12 / SYM v3)
 *   8 fns @[0x800EB1E0 .. 0x800EB520].  The speech bank table -- allocate/free the gVoxBanks[] pointer array,
 *   find a free or matching slot, test sub-bank bounds, and assign cycle bits for a game/race number.
 *   Ghidra nfs4-f.exe.c (spchbank) + disasm-v3 + IDA sigs.
 *
 *   Ghidra-isms resolved: iSPCH_GetFreeBank / iSPCH_FindBank were void-typed but RETURN an int index (their
 *   callers read v0; FindBank's return = the loop index set in the branch delay slot, -1 if no match;
 *   FindBank's `this` is the search key).  SetCycleBits' 2nd param and SPCH_AddBank's `in_a1` are a phantom
 *   uninitialised register (IDA: SetCycleBits is 1-arg) -> dropped.
 */

#include "../../../nfs4_types.h"

extern "C" intptr *gVoxBanks; /* @0x801370B4 : bank pointer array */
extern "C" int gNumBanks;     /* @0x801370B8  : number of bank slots */
extern "C" int gGameNum;      /* shared game global : current game/race number (cycle-bit hash key) */

extern "C" intptr iSPCH_MemAlloc(int numBytes, char *message); /* spchinit */
extern "C" void iSPCH_MemFree(void *mem);                      /* spchinit */
extern "C" intptr iSPCH_GetBankBits(intptr bank);              /* spchpick */
extern "C" void trap(unsigned int code);

extern "C" void iSPCH_InitBanks(void);                                    /* @0x800EB1E0 */
extern "C" void iSPCH_DisposeBanks(void);                                 /* @0x800EB1F4 */
extern "C" intptr iSPCH_BankMemAlloc(unsigned int numBanks);              /* @0x800EB234 */
extern "C" int iSPCH_GetFreeBank(void);                                   /* @0x800EB2B8 */
extern "C" int iSPCH_FindBank(int key);                                   /* @0x800EB310 */
extern "C" unsigned int iSPCH_TestSubBankBounds(int bankIdx, int subIdx); /* @0x800EB37C */
extern "C" void iSPCH_SetCycleBits(intptr p);                             /* @0x800EB3C8 */
extern "C" int SPCH_AddBank(intptr bank);                                 /* @0x800EB520 */

/* iSPCH_InitBanks @0x800EB1E0 : clear the bank table (no allocation yet). */
extern "C" void iSPCH_InitBanks(void)
{
    gVoxBanks = 0;
    gNumBanks = 0;
}

/* iSPCH_DisposeBanks @0x800EB1F4 : free the bank array (if any) and clear the table. */
extern "C" void iSPCH_DisposeBanks(void)
{
    if (gVoxBanks != 0)
        iSPCH_MemFree(gVoxBanks);
    gVoxBanks = 0;
    gNumBanks = 0;
}

/* iSPCH_BankMemAlloc @0x800EB234 : allocate gVoxBanks[numBanks] (once) and zero it.  Returns gVoxBanks. */
extern "C" intptr iSPCH_BankMemAlloc(unsigned int numBanks)
{
    if (gVoxBanks == 0)
    {
        gNumBanks = (int)numBanks;
        gVoxBanks = (intptr *)iSPCH_MemAlloc((int)(numBanks * sizeof(intptr)), (char *)"spch banks");
        if (gVoxBanks != 0 && 0 < gNumBanks)
        {
            int i = 0;
            intptr *p = gVoxBanks;
            unsigned int n = (unsigned int)gNumBanks;
            do
            {
                *p = 0;
                i++;
                p++;
            } while (i < (int)n);
        }
    }
    return (intptr)gVoxBanks;
}

/* iSPCH_GetFreeBank @0x800EB2B8 : index of the first empty (NULL) bank slot, or -1 if none/no table. */
extern "C" int iSPCH_GetFreeBank(void)
{
    int result = -1;
    if (0 < gNumBanks)
    {
        int i = 0;
        intptr *p = gVoxBanks;
        do
        {
            if (*p == 0)
            {
                result = i;
                break;
            }
            i++;
            p++;
        } while (i < gNumBanks);
    }
    return result;
}

/* iSPCH_FindBank @0x800EB310 : index of the bank whose id (first u16 of its data) matches `key & 0xffff`,
 *   or -1 if not found. */
extern "C" int iSPCH_FindBank(int key)
{
    if (gVoxBanks != 0 && 0 < gNumBanks)
    {
        int i = 0;
        intptr *p = gVoxBanks;
        key = key & 0xffff;
        do
        {
            intptr bankPtr = *p;
            if (bankPtr != 0 && (unsigned int)*(unsigned short *)bankPtr == (unsigned int)key)
                return i;
            i++;
            p++;
        } while (i < gNumBanks);
    }
    return -1;
}

/* iSPCH_TestSubBankBounds @0x800EB37C : 1 if sub-index `subIdx` is in range [0, count) for bank `bankIdx`
 *   (where count = the bank's u16 at +6, and != 0xffff), else 0. */
extern "C" unsigned int iSPCH_TestSubBankBounds(int bankIdx, int subIdx)
{
    unsigned int result = 0;
    unsigned int count;
    if (gVoxBanks != 0 && -1 < bankIdx && (count = (unsigned int)*(unsigned short *)(gVoxBanks[bankIdx] + 6), count != 0xffff) && -1 < subIdx)
    {
        result = (unsigned int)(subIdx < (int)count);
    }
    return result;
}

/* iSPCH_SetCycleBits @0x800EB3C8 : for bank `p`, set the run of cycle bits that this game number (gGameNum)
 *   maps to within the bank's GetBankBits() array.  The (n==0)/(n==-1 && dividend==INT_MIN) checks are the
 *   compiler's signed-division traps.  Retail does not define or consume a return value. */
extern "C" void iSPCH_SetCycleBits(intptr p)
{
    unsigned char *bits;
    unsigned int nGroups;
    int startBit, count, byteIdx, bitInByte;
    int t, i;

    bits = (unsigned char *)iSPCH_GetBankBits(p);
    nGroups = (unsigned int)*bits;
    if (nGroups != 0)
    {
        if (nGroups == 0)
            trap(0x1c00);
        if (nGroups == 0xffffffff && gGameNum == (int)0x80000000)
            trap(0x1800);
        t = ((int)gGameNum % (int)nGroups) * (int)(unsigned int)*(unsigned char *)(p + 3);
        startBit = t / (int)nGroups;
        if (nGroups == 0)
            trap(0x1c00);
        if (nGroups == 0xffffffff && t == (int)0x80000000)
            trap(0x1800);
        t = ((int)gGameNum % (int)nGroups + 1) * (int)(unsigned int)*(unsigned char *)(p + 3);
        if (nGroups == 0)
            trap(0x1c00);
        if (nGroups == 0xffffffff && t == (int)0x80000000)
            trap(0x1800);
        count = t / (int)nGroups - startBit;
        t = startBit;
        if (startBit < 0)
            t = startBit + 7;
        t = t >> 3;
        byteIdx = t + 1;
        bitInByte = startBit + t * -8;
        i = 0;
        if (0 < count)
        {
            do
            {
                unsigned int b = (unsigned int)bitInByte & 0x1f;
                bitInByte = bitInByte + 1;
                bits[byteIdx] = bits[byteIdx] | (unsigned char)(1 << b);
                if (bitInByte == 8)
                {
                    bitInByte = 0;
                    byteIdx = byteIdx + 1;
                }
                i = i + 1;
            } while (i < count);
        }
    }
}

/* SPCH_AddBank @0x800EB520 : place bank `bank` into the first free slot (setting its cycle bits first if the
 *   bank's flags byte +2 has any high nibble).  Returns the slot index, or -1 if the table is full/uninit. */
extern "C" int SPCH_AddBank(intptr bank)
{
    int slot = -1;
    if (gVoxBanks != 0)
    {
        slot = iSPCH_GetFreeBank();
        if (-1 < slot)
        {
            if ((*(unsigned char *)(bank + 2) & 0xf0) != 0)
                iSPCH_SetCycleBits(bank);
            gVoxBanks[slot] = bank;
        }
    }
    return slot;
}
