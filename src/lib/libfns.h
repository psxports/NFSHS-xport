/* lib/libfns.h -- AUTHORITATIVE extern "C" interface for eaclib/syslib functions.
 *   Platform/runtime boundary: same decls satisfied by PSX(PsyQ+eaclib), PC(PsyCross+eaclib), etc.
 *   Canonical signatures harvested from the best existing tree decl per fn (typed > varargs);
 *   the 5 reconstructed defs are pinned. C linkage => stable symbol, no mangling.
 *   NOTE: for syslib/PsyQ SDK fns the REAL header is libgpu.h/libgte.h/... (see disasm-v3 // proto).
 *
 *   PsyQ-SDK split (B-integration): under ccpsx (NFS4_PSYQ_HEADERS, set in nfs4_types.h),
 *   the PsyQ standard-library functions (libgpu/libgte/libetc/libapi/libpad) are supplied by the
 *   REAL PsyQ headers � declaring them here too would clash (return-type / macro / linkage), so they
 *   are gated OFF. Under the modern-gcc pre-gate they stay ON as the varargs boundary decls.
 *   EA eaclib/syslib (FILE_*, SND*, fixed-point, loaders) + libc + libgcc soft-float are ALWAYS on
 *   (no PsyQ header declares them, so no conflict in either toolchain).
 */
#ifndef _LIB_LIBFNS_H_
#define _LIB_LIBFNS_H_
#include "../nfs4_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C"
{
/* =====================================================================
 *  PsyQ SDK functions -- libgpu / libgte / libetc / libapi / libpad.
 *  Gated OFF under ccpsx (real PsyQ headers provide these).
 * ===================================================================== */
#ifndef NFS4_PSYQ_HEADERS
    /* ---- libgpu (graphics) ---- */
    void AddPrim(void *ot, void *p);
    sint32 ClearImage(PSX_RECT *rectangle, uint8 red, uint8 green, uint8 blue);
    uint32 *ClearOTagR(uint32 *ot, sint32 count);
    void DrawOTag(uint32 *ot);
    sint32 DrawSync(sint32 mode);
    uint16 GetClut(sint32 x, sint32 y);
    uint16 GetTPage(sint32 depth, sint32 abr, sint32 x, sint32 y);
    sint32 LoadImagePSX(PSX_RECT *rectangle, uint32 *pixels);
    uint16 LoadTPage(uint32 *pixels, sint32 depth, sint32 abr, sint32 x, sint32 y, sint32 width, sint32 height);
    sint32 MoveImage(PSX_RECT *rectangle, sint32 x, sint32 y);
    DISPENV *PutDispEnv(DISPENV *environment);
    DRAWENV *PutDrawEnv(DRAWENV *environment);
    DISPENV *SetDefDispEnv(DISPENV *environment, sint32 x, sint32 y, sint32 width, sint32 height);
    DRAWENV *SetDefDrawEnv(DRAWENV *environment, sint32 x, sint32 y, sint32 width, sint32 height);
    void SetDispMask(sint32 enabled);
    void SetDrawArea(void *packet, PSX_RECT *rectangle);
    void SetDrawEnv(void *packet, DRAWENV *environment);
    void SetDrawMode(void *packet, int dfe, int dtd, int tpage, PSX_RECT *texture_window);
    void SetDrawStp(void *packet, sint32 enabled);
    void SetPolyF3(void *packet);
    void SetPolyF4(void *packet);
    void SetPolyFT4(void *packet);
    void SetPolyG4(void *packet);
    void SetPolyGT4(void *packet);
    void SetSemiTrans(void *packet, int enabled);
    void SetShadeTex(void *packet, int raw_texture);
    void SetTexWindow(void *packet, PSX_RECT *texture_window);
    sint32 StoreImage(PSX_RECT *rectangle, uint32 *pixels);
    /* ---- libgte (geometry) ---- */
    void InitGeom(void);
    MATRIX *RotMatrix(SVECTOR *rotation, MATRIX *matrix);
    MATRIX *RotMatrixZ(sint32 rotation, MATRIX *matrix);
    void SetFarColor(sint32 red, sint32 green, sint32 blue);
    void SetFogNear(sint32 distance, sint32 projection);
    void SetGeomScreen(sint32 distance);
    sint32 VectorNormal(VECTOR *input, VECTOR *output);
    sint32 VectorNormalS(VECTOR *input, SVECTOR *output);
    /* ---- libetc (callback / vsync / rcnt / video) ---- */
    sint32 GetRCnt(sint32 counter);
    void ResetCallback(void);
    void SetVideoMode(sint32 mode);
    sint32 VSync(sint32 mode);
    void *VSyncCallback(void *callback);
    /* ---- libapi (kernel) ---- */
    void FlushCache(void);
    /* ---- libpad ---- */
    sint32 PadGetState(sint32 port);
    sint32 PadInfoMode(sint32 port, sint32 term, sint32 offset);
    void PadSetAct(sint32 port, const void *actuator, sint32 length);
    sint32 PadSetActAlign(sint32 port, const void *alignment);
    void PadSetMainMode(sint32 port, sint32 mode, sint32 lock);
    void PadStartCom(void);
#endif /* !NFS4_PSYQ_HEADERS */

    /* =====================================================================
 *  EA eaclib / syslib  +  libc  +  libgcc soft-float -- ALWAYS declared.
 *  (No PsyQ header declares these; safe under both toolchains.)
 * ===================================================================== */
    int CdDiskReady(int mode);
    int FILE_addbigsync(char *name, int flags, int priority, int *handle);
    int FILE_closesync(int fd, int priority);
    int FILE_completeop(unsigned int id);
    int FILE_delbigsync(int handle, int priority);
    int FILE_init(int, int, int);
    int FILE_opensync(char *name, int mode, int priority, int *handleOut);
    int FILE_operror(unsigned int id);
    int FILE_opstatus(unsigned int id);
    unsigned int FILE_read(intptr handle, unsigned int offset, intptr dest, int length, unsigned int priority, intptr callbackParam);
    int FILE_readsync(intptr handle, unsigned int offset, intptr dest, int length, int priority);
    int FILE_sizesync(int handle, int priority);
    void PAD_restore(void);
    u_short PAD_state(int port);
    void PAD_update(void);
    int SND3dpos(unsigned int tag, unsigned int pos, int y); /* (u_int tag, u_int x, int y) */
    int SNDSTRM_autovol(int handle, int ticks, int volume);
    int SNDSTRM_create(int *opts, int numRequests, int packetArg, void *buffer, int size);
    int SNDSTRM_destroy(int handle);
    int SNDSTRM_getvol(int tag);
    int SNDSTRM_overhead(int numConsumers, int numReq);
    int SNDSTRM_purge(int handle);
    int SNDSTRM_queuefile(int handle, int priority, char *name, long offset);
    int SNDSTRM_requeststatus(unsigned int req, SNDREQUESTSTATUS *status);
    int SNDSTRM_setgreedylevel(int handle, int level);
    int SNDSTRM_setgreedystate(int handle, int state);
    int SNDSTRM_setpriority(int handle, int prio, int n);
    int SNDSTRM_status(int handle, SNDSTREAMSTATUS *status);
    int SNDSTRM_vol(int handle, int volume);
    void SNDSYS_getopts(void *outOpts);
    void SNDSYS_init(int membase, int memsize);
    void SNDSYS_restore(void); /* Disasm-verified: only call site Audio_DeInitDriver 0xabc9c sets no a0 */
    int SNDSYS_setopts(void *newOpts);
    void SNDSYS_vectortoreal(void);
    int SNDautovol(unsigned int tag, unsigned int rate, int target); /* (void *, int, int) */
    int SNDbankadd(int *bank_out, intptr bankData);
    int SNDbankheadercopy(unsigned char *destination, int bankId);
    int SNDbankheadersize(int bankId);
    void SNDbankremove(int bankId); /* (int) */
    int SNDfxinitbus(int bus, int mode, int arg2, int arg3, int arg4);
    int SNDfxmasterlevel(int bus, int level);
    int SNDgetlimits(int *opts);                           /* (int *opts) */
    int SNDmastervol(int vol);                             /* (int vol) */
    int SNDmemlargestunused(int *out);                     /* (int *buf) */
    unsigned int SNDover(unsigned int tag);                /* (int) */
    int SNDpan(int handle, int pan);                       /* (u_int tag, int pan) */
    int SNDpitchbend(unsigned int tag, int bend);          /* (u_int tag, int bend) */
    int SNDpitchmult(unsigned int tag, unsigned int mult); /* (int tag, u_int mult) */
    int SNDplay(SNDPLAYOPTS *info);                        /* (void *) */
    void SNDplaysetdef(SNDPLAYOPTS *def);                  /* (void *) */
    int SNDsetlimits(int *opts);                           /* (int *opts) */
    int SNDstop(unsigned int tag);                         /* (int handle) */
    int SNDtimeremaining(unsigned int tag);                /* (int handle) */
    int SNDvol(int handle, int vol);                       /* (int handle, int vol) */
    void *SetSp(void *p);                                  /* (void *sp) -- EA, not PsyQ */
    double __adddf3(double a, double b);
    double __divdf3(double a, double b);
    float __divsf3(float a, float b);
    // Explicit single-precision libgcc calls must not use ellipsis: it promotes
    // their operands to double (FRONT.BIN 80012DCC..80012DF8 passes single words).
    double __extendsfdf2(float);
    int __fixsfsi(float a);
    double __floatsidf(int a);
    float __floatsisf(int a);
    int __ltdf2(double a, double b);
#if defined(__EMSCRIPTEN__)
    void NFSHS_HostMainInit(void);
    #define __main NFSHS_HostMainInit
#else
    void __main(void); /* (void) */
#endif
    float __mulsf3(float, float);
    float __truncdfsf2(double a);
    int addsystemtask(intptr taskFn, int period, int delay);
    void addtimer(void (*proc)(void));
    int asyncidle(void); /* nullfunc.asm @0x800F6114: delay slot clears v0 */
    int asyncloadfile(char *name, int memclass);
    int asyncloadfileat(const char *name, intptr dest);
    int asyncloadsegment(int offset, void *destination, int size);
    int bigcount(void *big);
    void blockclear(void *, int);
    void blockfill(void *dst, int size, unsigned char val);
    void blockmove(void *src, void *dst, int size);
    int cancelasyncload(int requestId);
    sint32 ccos(sint32 angle);
    unsigned int crc16(const void *data, int length);
    void crossproduct(int *a, int *b, int *out); /* (coorddef *, coorddef *, coorddef *) */
    sint32 csin(sint32 angle);
    intptr delsystemtask(intptr taskFn);
    void deltimer(void (*proc)(void));
    int fastintcos(int angle); /* (int angle) */
    int fastintsin(int angle); /* (int angle) */
    int filesize(char *name);
    int fixedatan(int y, int x);
    int fixedcos(int angle);    /* (int angle) */
    int fixeddiv(int a, int b); /* (int a, int b) */
    int fixedmult(int a, int b);
    int fixedsin(int angle); /* (int angle) */
    void fixedsincos(int angle, int *s, int *c);
    int fixedsqrt(int x); /* (int x) */
    void fixedxformx(void *m, int angle);
    void fixedxformy(void *m, int angle);
    void fixedxformz(void *m, int angle);
    char *getasyncreadadr(int requestId);
    int getasyncreadstatus(int requestId);
    charactertbl *getcharacter(unsigned int code);
    unsigned int geti(void *p, char nbits);
    int getm(unsigned char *p, int n);
    int gettick(void);
    short *iSNDserveradd100hzclient(void (*cb)(void));
    int iSNDserverremove100hzclient(void (*cb)(void));
    int *iSPCH_EACseedrandom(unsigned int seed); /* (int arg0) */
    int initasync(int, int, int);
    int initjoy(unsigned int);
    void *initlinkmode(void *, int, int);
    int initmemadr(int, int);
    void inittimer(int);
    int intarccos(int x);                            /* (int cosval) */
    int intatan(int y, int x);                       /* (int dx, int dz) */
    void intsincos(int angle, int *psin, int *pcos); /* (int angle, int *psin, int *pcos) -- disasm-verified 3-arg (eaclib isincos.cpp:58 @0x800eadbc); psin/pcos are OUT-ptrs */
    unsigned int isqrt(unsigned int a);              /* (int v) */
    int largestunused(void);
    void *loadbigfileheader(char *name, int memclass);
    void *loadfileadr(char *name, int memclass);
    void *loadfileadrz(char *name, int memclass);
    void *loadfileatadr(char *name, void *address);
    void *loadfileatadrz(char *name, void *address);
    void *loadpackadr(char *name, int memclass);
    void *loadpackadrz(char *name, int memclass);
    void *loadshapeadr(char *name, int memclass);
    char *locatebig(void *buf, const char *name); /* (void *buf, char *name) -- lib-source 2-arg (locatbig.cpp @0x800E6218); callers' 3rd 'from' arg = harmless over-supply */
    char *locatebigentry(void *bigfile, const char *name, int index, int *offsetOut, int *sizeOut);
    char *locatebigentryz(void *buf, const char *name, int index, int *offset, int *size); /* (void *big, char *name, int index, int *offsetOut, int *sizeOut) -- disasm-verified 5-arg (copspeak:539/554/602/629), out-ptrs like locatebigentry */
    void *locateshape(void *shapefile, const void *namekey);
    void *locateshapez(void *shapefile, const void *namekey);
    intptr movfxya(void *shapeData, int x, int y); /* (unsigned char *shape, int x, int y) */
    void padinit(void);
    int purgememadr(void *p);
#if defined(__EMSCRIPTEN__)
    long random(void);
#else
    int random(void);
#endif
    int reorthogonalize(int *M); /* (matrixtdef *m) */
    void *reservememadr(const char *name, int size, int classid);
    void *resizememadr(void *userptr, int newsize);
    void restoregp(unsigned int gp); /* (int arg0) */
    unsigned rinverse(int x);        /* (int x) */
    void savegp(unsigned int *out);  /* (int *arg0) */
    void seedrandom(int seed);       /* (int seed) */
    void setasyncfile(char *name);
    void setdirectory(char *);
    FontDecoder setfont(intptr fontId);
    int settrans(int mode);                                         /* (int on) */
    int shapedepth(const void *shapeData);                          /* (void *shp) */
    void shapename(void *shapefile, unsigned int index, void *dst); /* (void *, int, char *) */
    void *shapepointer(void *shapefile, unsigned int index);
    int shapetoclutid(const void *shapeData); /* (void * shape) */
    extern "C"
    {
        unsigned int systemtask(int taskFlag);
    }
    void timedwait(int ticks);
    int *transform(int *vec, int *mat, int *out);     /* (void *src, void *mtx, void *dst) */
    void transpose(matrixtdef *src, matrixtdef *dst); /* (matrixtdef *, matrixtdef *) */
    int unbtree(unsigned char *src, unsigned char *dst);
    int unhuff(unsigned char *src, unsigned char *dst, int decode);
    int unrefpack(unsigned char *src, unsigned char *dst, int decode);
    void vramfxya(void *shape, short imgX, short imgY, short clutX, short clutY);
    void waitdraw(void);
    int wildcard(char *str, char *pattern);
    void xformy(matrixtdef *out, int angle); /* (matrixtdef *m, int angle) */

} /* extern "C" */

#endif
