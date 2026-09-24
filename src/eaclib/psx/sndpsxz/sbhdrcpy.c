/* eaclib/psx/sndpsxz/sbhdrcpy.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\sbhdrcpy.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   1 fn @0x800E7BA8.  SNDbankheadercopy -- copy a loaded bank's header into `dst` and rebase its patch
 *   pointers to the new buffer, repointing the bank table at the copy.  Ghidra nfs4-f.exe.c (sbhdrcpy).
 */

#include "../../../nfs4_types.h"
#include "../../../lib/snd.h"
#include "../../../mips_semantics.h"

extern "C" int SNDbankheadersize(int bankId); /* sbhdrsze */
#ifndef _MSC_VER
extern "C" void *memcpy(void *dst, const void *src, int n); /* C42 (BIOS thunk) */
#endif

extern "C" int SNDbankheadercopy(unsigned char *dst, int bankId); /* @0x800E7BA8 */

/* SNDbankheadercopy @0x800E7BA8 : memcpy the bank header to `dst`, relocate each patch pointer (+0x14 for
 *   bank type 4, else +0xc) relative to `dst`, then point the bank table entry at `dst`. */
extern "C" int SNDbankheadercopy(unsigned char *dst, int bankId)
{
    int size, i;

    if ((char)sndgs[0xf] == 0)
        return -10;
    size = SNDbankheadersize(bankId);
    if (size < 0)
        return size;
    unsigned char *bankData = (unsigned char *)SND->banks[bankId].datablk;
    memcpy(dst, bankData, size);
    if (*(unsigned short *)(bankData + 6) != 0)
    {
        intptr oldBase = (intptr)bankData;
        intptr newBase = (intptr)dst;
        i = 0;
        do
        {
            if (bankData[4] == 4)
            {
                int sp = *(int *)(bankData + i * 4 + 0x14);
                if (sp != 0)
                    *(int *)(dst + i * 4 + 0x14) = nfs4_mips_addu_s32((int)newBase, nfs4_mips_subu_s32(sp, (int)oldBase));
            }
            else
            {
                int sp = *(int *)(bankData + i * 4 + 0xc);
                if (sp != 0)
                    *(int *)(dst + i * 4 + 0xc) = nfs4_mips_addu_s32((int)newBase, nfs4_mips_subu_s32(sp, (int)oldBase));
            }
            i++;
        } while (i < (int)*(unsigned short *)(bankData + 6));
    }
    SND->banks[bankId].datablk = dst;
    return 0;
}
