/* frontend/psx/mdec_externs.h - reconstructed extern decls (libpress/libgpu + eaclib)
 * referenced by MDEC.CPP. NOT an original header; added for standalone C++ compile. */
#ifndef _FRONTEND_PSX_MDEC_EXTERNS_H_
#define _FRONTEND_PSX_MDEC_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C" int timerhz;
extern "C" int ticks;

extern "C"
{
    /* PsyQ libpress (MDEC) */
    void DecDCTReset(int mode);
    int DecDCToutCallback(void (*cb)(void));
    int DecDCTvlc(uint32 *bs, uint32 *buf);
    void DecDCTin(uint32 *buf, int mode);
    void DecDCTout(uint32 *buf, int size);
    /* PsyQ libgpu */
    /* eaclib */
}
#endif
