/* frontend/psx/movie_externs.h - reconstructed extern decls (libcd/libpress/libgpu/libetc
 * + eaclib) referenced by MOVIE.CPP. NOT an original header; added for standalone C++ compile. */
#ifndef _FRONTEND_PSX_MOVIE_EXTERNS_H_
#define _FRONTEND_PSX_MOVIE_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

typedef void fn_void(void); /* SYM PTR FCN VOID -> fn_void* = void(*)(void) */
typedef long long longlong; /* Ghidra 64-bit helper types */
typedef unsigned long long ulonglong;

extern "C" int gMasterMusicLevel; /* game audio global */

extern "C"
{
    extern int StCdIntrFlag; /* PsyQ libcd interrupt flag */
    int CD_Restart(int startSector);
    CdlCB CdDataCallback(CdlCB func);
    sint32 CdRead2(sint32 mode);
    void *CdSearchFile(void *fp, char *name);
    void DecDCTReset(int mode);
    void DecDCTin(uint32 *runlevel, int mode);
    int DecDCTinSync(int mode);
    void DecDCTout(uint32 *cell, int size);
    int DecDCToutCallback(void (*func)(void));
    int DecDCTvlc(uint32 *bs, uint32 *buf);
    int DecDCTvlcSize(int size);
    uint32 *FntFlush(int id); /* match real PsyQ libgpu.h proto (int, not long) */
    extern "C"
    {
        void Platform_ResetDCTBuffer(void);
    }
    int SNDcdvol(int vol);
    void StCdInterrupt(void);
    void StClearRing(void);
    uint32 StFreeRing(uint32 *base);
    uint32 StGetNext(uint32 **addr, uint32 **header);
    void StSetRing(uint32 *ring_addr, uint32 ring_size);
    void StSetStream(uint32 mode, uint32 start_frame, uint32 end_frame, void (*func1)(void), void (*func2)(void));
    void StUnSetRing(void);
    int Triangle(); /* sig unknown */
    void trap(int code);
}
#endif
