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

extern "C"
{
/* =====================================================================
 *  PsyQ SDK functions -- libgpu / libgte / libetc / libapi / libpad.
 *  Gated OFF under ccpsx (real PsyQ headers provide these).
 * ===================================================================== */
#ifndef NFS4_PSYQ_HEADERS
    /* ---- libgpu (graphics) ---- */
    void AddPrim(void *ot, void *p);
    int ClearImage(...);           /* (PSX_RECT *rect, u_char r, u_char g, u_char b) */
    u_long *ClearOTagR(...);       /* (u_long *ot, int n) */
    void DrawOTag(...);            /* (u_long *) */
    long DrawSync(...);            /* (long mode) */
    unsigned short GetClut(...);   /* (int,int) */
    int GetTPage(...);             /* (int,int,int,int) */
    int LoadImagePSX(...);         /* (PSX_RECT * recp, u_long * p) */
    unsigned short LoadTPage(...); /* (u_long *pix,int tp,int abr,int x,int y,int w,int h) */
    int MoveImage(...);            /* (PSX_RECT *rect, int x, int y) */
    DISPENV *PutDispEnv(...);      /* (DISPENV *) */
    DRAWENV *PutDrawEnv(...);      /* (DRAWENV *) */
    DISPENV *SetDefDispEnv(...);   /* (DISPENV *, int, int, int, int) */
    DRAWENV *SetDefDrawEnv(...);   /* (DRAWENV *, int, int, int, int) */
    void SetDispMask(...);         /* (int) */
    void SetDrawArea(...);         /* (DR_AREA *p, PSX_RECT *r) */
    void SetDrawEnv(...);          /* (void *, DRAWENV *) */
    void SetDrawMode(...);         /* (void*,int,int,int,PSX_RECT*) */
    void SetDrawStp(...);          /* (void *p,int stp) */
    void SetPolyF3(...);           /* (POLY_F3 *p = 0) */
    void SetPolyF4(...);           /* (void*) */
    void SetPolyFT4(...);          /* (void*) */
    void SetPolyG4(...);           /* (POLY_G4 *p) */
    void SetPolyGT4(...);          /* (POLY_GT4 *p) */
    void SetSemiTrans(...);        /* (void*,int) */
    void SetShadeTex(...);         /* (void*,int) */
    void SetTexWindow(...);        /* (void *prim, PSX_RECT *tw) */
    int StoreImage(...);           /* (PSX_RECT *rect, u_long *p) */
    /* ---- libgte (geometry) ---- */
    void InitGeom(...);      /* (void) */
    MATRIX *RotMatrix(...);  /* (SVECTOR *r,MATRIX *m) */
    MATRIX *RotMatrixZ(...); /* (long r,MATRIX *m) */
    void SetFarColor(...);   /* (int r, int g, int b) */
    void SetFogNear(...);    /* (int a, int otz) */
    void SetGeomScreen(...); /* (int h) */
    int VectorNormal(...);   /* (VECTOR *v0, VECTOR *v1) */
    long VectorNormalS(...); /* (VECTOR *v0, SVECTOR *v1) */
    /* ---- libetc (callback / vsync / rcnt / video) ---- */
    int GetRCnt(...);        /* (int spec) */
    void ResetCallback(...); /* (void) */
    void SetVideoMode(...);  /* (int) */
    int VSync(...);          /* (int) */
    void VSyncCallback(...); /* (void *cb) */
    /* ---- libapi (kernel) ---- */
    void FlushCache(...); /* (void) */
    /* ---- libpad ---- */
    int PadGetState(...); /* (int port) */
    int PadInfoMode(...);
    void PadSetAct(...);     /* (int port, const void *table, int len) */
    int PadSetActAlign(...); /* (int port, const void *table) */
    void PadSetMainMode(...);
    void PadStartCom(...); /* (void) */
#endif                     /* !NFS4_PSYQ_HEADERS */

    /* =====================================================================
 *  EA eaclib / syslib  +  libc  +  libgcc soft-float -- ALWAYS declared.
 *  (No PsyQ header declares these; safe under both toolchains.)
 * ===================================================================== */
    int CdDiskReady(...);     /* (int mode) -- EA wrapper, not PsyQ CdReady */
    int FILE_addbigsync(...); /* (char *name, void *a, int b, int *handle) */
    int FILE_closesync(int fd, int priority);
    int FILE_completeop(...);  /* (int oph) */
    void FILE_delbigsync(...); /* (int a0, int a1) -- lib-source 2-arg (syncfile.cpp); prior 4-arg doc was wrong */
    void FILE_init(...);       /* (int a, int b, int c) */
    int FILE_opensync(...);    /* (char *name, int mode, int prio, int *handleOut) -- disasm-verified a3 = &handle out-ptr */
    int FILE_operror(...);     /* (int oph) */
    int FILE_opstatus(...);    /* (int oph) */
    unsigned int FILE_read(intptr handle, unsigned int offset, intptr dest, int length, unsigned int priority, intptr callbackParam);
    int FILE_readsync(intptr handle, unsigned int offset, intptr dest, int length, int priority);
    int FILE_sizesync(int handle, int priority);
    void PAD_restore(void);
    u_short PAD_state(int port);
    void PAD_update(void);
    int SND3dpos(...);        /* (u_int tag, u_int x, int y) */
    int SNDSTRM_autovol(...); /* (int handle, int ticks, int flag) */
    int SNDSTRM_create(int *opts, int numRequests, int packetArg, void *buffer, int size);
    int SNDSTRM_destroy(...);  /* (int handle) */
    int SNDSTRM_getvol(...);   /* (int handle) */
    int SNDSTRM_overhead(...); /* (int a, int b) */
    void SNDSTRM_purge(...);   /* (int handle) */
    int SNDSTRM_queuefile(int handle, int priority, char *name, long offset);
    int SNDSTRM_requeststatus(unsigned int req, SNDREQUESTSTATUS *status);
    void SNDSTRM_setgreedylevel(...); /* (int handle, int level) */
    void SNDSTRM_setgreedystate(...); /* (int handle, int state) */
    void SNDSTRM_setpriority(...);    /* (int handle, int prio, int n) */
    int SNDSTRM_status(int handle, SNDSTREAMSTATUS *status);
    int SNDSTRM_vol(...);          /* (int handle, int vol) */
    int SNDSYS_getopts(...);       /* (void * outOpts) */
    void SNDSYS_init(...);         /* (int membase, int memsize) -- lib-source 2-arg (ssysinit.cpp) */
    void SNDSYS_restore(...);      /* (void) -- disasm-verified: only call site (Audio_DeInitDriver 0xabc9c) sets no a0 (was mis-doc'd 1-arg) */
    int SNDSYS_setopts(...);       /* (void * newOpts) */
    void SNDSYS_vectortoreal(...); /* (void) */
    void SNDautovol(...);          /* (void *, int, int) */
    int SNDbankadd(int *bank_out, intptr bankData);
    void SNDbankheadercopy(...);  /* (void *, int) */
    int SNDbankheadersize(...);   /* (int) */
    int SNDbankremove(...);       /* (int) */
    int SNDfxinitbus(...);        /* (int bus, int mode, int a2, int a3, int a4) */
    int SNDfxmasterlevel(...);    /* (int bus, int level) */
    int SNDgetlimits(...);        /* (int *opts) */
    int SNDmastervol(...);        /* (int vol) */
    int SNDmemlargestunused(...); /* (int *buf) */
    int SNDover(...);             /* (int) */
    int SNDpan(...);              /* (u_int tag, int pan) */
    int SNDpitchbend(...);        /* (u_int tag, int bend) */
    int SNDpitchmult(...);        /* (int tag, u_int mult) */
    int SNDplay(...);             /* (void *) */
    void SNDplaysetdef(...);      /* (void *) */
    int SNDsetlimits(...);        /* (int *opts) */
    int SNDstop(...);             /* (int handle) */
    int SNDtimeremaining(...);    /* (int handle) */
    void SNDvol(...);             /* (int handle, int vol) */
    void *SetSp(...);             /* (void *sp) -- EA, not PsyQ */
    double __adddf3(...);         /* (double, double) */
    double __divdf3(...);         /* (double, double) */
    float __divsf3(...);          /* (float a, float b) */
    // Explicit single-precision libgcc calls must not use ellipsis: it promotes
    // their operands to double (FRONT.BIN 80012DCC..80012DF8 passes single words).
    double __extendsfdf2(float);
    int __fixsfsi(float a);
    double __floatsidf(...); /* (int) */
    float __floatsisf(...);  /* (int) */
    int __ltdf2(...);        /* (double, double) */
    void __main(...);        /* (void) */
    float __mulsf3(float, float);
    float __truncdfsf2(...); /* (double) */
    int addsystemtask(intptr taskFn, int period, int delay);
    int addtimer(...);                 /* (void (*proc)(void)) */
    int asyncidle(void);               /* nullfunc.asm @0x800F6114: delay slot clears v0 */
    unsigned int asyncloadfile(...);   /* (char*, void*) */
    unsigned int asyncloadfileat(...); /* (char*, char*) */
    int asyncloadsegment(...);         /* (char *, void *, int) */
#if !defined(_MSC_VER)
    int atoi(...); /* (const char *s) */
#endif
    int bigcount(...);         /* (void *big) */
    void blockclear(...);      /* (void*, int) */
    void blockfill(...);       /* (void *dst, int size, int val) */
    void blockmove(...);       /* (void *, void *, int) */
    void cancelasyncload(...); /* (unsigned int) */
    sint32 ccos(sint32 angle);
    unsigned long crc16(...); /* (void*, int) */
    void crossproduct(...);   /* (coorddef *, coorddef *, coorddef *) */
    sint32 csin(sint32 angle);
    intptr delsystemtask(intptr taskFn);
    int deltimer(...);   /* (void (*proc)(void)) */
    int fastintcos(...); /* (int angle) */
    int fastintsin(...); /* (int angle) */
    int filesize(...);   /* (char*) */
    int fixedatan(int y, int x);
    int fixedcos(...); /* (int angle) */
    int fixeddiv(...); /* (int a, int b) */
    int fixedmult(int a, int b);
    int fixedsin(...); /* (int angle) */
    void fixedsincos(int angle, int *s, int *c);
    int fixedsqrt(...); /* (int x) */
    void fixedxformx(void *m, int angle);
    void fixedxformy(void *m, int angle);
    void fixedxformz(void *m, int angle);
    char *getasyncreadadr(...);  /* (int id) -- lib-source 1-arg (nasync.cpp) */
    int getasyncreadstatus(...); /* (unsigned int) */
    charactertbl *getcharacter(unsigned int code);
    int geti(...);  /* (void *p, int n) */
    long getm(...); /* (void *p, int n) */
    int gettick(...);
    short *iSNDserveradd100hzclient(void (*cb)(void));
    int iSNDserverremove100hzclient(void (*cb)(void));
    void iSPCH_EACseedrandom(...); /* (int arg0) */
    void initasync(...);           /* (int reqs, int bufsize, int flag) */
    void initjoy(...);             /* (int mode) */
    void initlinkmode(...);        /* (int a, int count, int c) */
    void initmemadr(...);          /* (void *base, int size) */
    void inittimer(...);           /* (int hz) */
    int intarccos(...);            /* (int cosval) */
    int intatan(...);              /* (int dx, int dz) */
    int intsincos(...);            /* (int angle, int *psin, int *pcos) -- disasm-verified 3-arg (eaclib isincos.cpp:58 @0x800eadbc); psin/pcos are OUT-ptrs */
    int isqrt(...);                /* (int v) */
    int largestunused(...);        /* (void) */
    void *loadbigfileheader(char *name, int memclass);
    void *loadfileadr(char *name, int memclass);
    void *loadfileadrz(char *name, int memclass);
    void *loadfileatadr(char *name, void *address);
    void *loadfileatadrz(char *name, void *address);
    void *loadpackadr(...);     /* (char *name, void *dst) */
    void *loadpackadrz(...);    /* (char *name, void *dst) */
    int loadshapeadr(...);      /* (char *name, void *dst) */
    void *locatebig(...);       /* (void *buf, char *name) -- lib-source 2-arg (locatbig.cpp @0x800E6218); callers' 3rd 'from' arg = harmless over-supply */
    void *locatebigentry(...);  /* (char *bigfile, char *name, int index, long *offsetOut, long *sizeOut) -- disasm-verified a3=&offset stk=&size out-ptrs */
    void *locatebigentryz(...); /* (void *big, char *name, int index, int *offsetOut, int *sizeOut) -- disasm-verified 5-arg (copspeak:539/554/602/629), out-ptrs like locatebigentry */
    void *locateshape(...);     /* (void *base, const char *tag) -- disasm-verified 2-arg (body reads only a0/a1; was 3) */
    void *locateshapez(...);    /* (char *buf, char *name) */
#if !defined(_MSC_VER)
    void *memcpy(...); /* (void *dest, void *src, uint n) */
    void *memset(...); /* (void *, int, int) */
#endif
    intptr movfxya(...); /* (unsigned char *shape, int x, int y) */
    void padinit(void);
    int purgememadr(...); /* (char *p) */
#if !defined(_MSC_VER)
    int puts(...);   /* (const char *s) */
    void qsort(...); /* (void*, int, int, int(*)(char*, char*)) */
    int rand(...);
#endif
    int random(...);           /* (void) */
    void reorthogonalize(...); /* (matrixtdef *m) */
    void *reservememadr(...);  /* (const char *, int, int) */
    void *resizememadr(void *userptr, int newsize);
    void restoregp(...);    /* (int arg0) */
    int rinverse(...);      /* (int x) */
    void savegp(...);       /* (int *arg0) */
    void seedrandom(...);   /* (int seed) */
    void setasyncfile(...); /* (char *) */
    void setdirectory(...); /* (char *path) */
    FontDecoder setfont(intptr fontId);
    void settrans(...);      /* (int on) */
    int shapedepth(...);     /* (void *shp) */
    void shapename(...);     /* (void *, int, char *) */
    void *shapepointer(...); /* (void*, int) */
    int shapetoclutid(...);  /* (void * shape) */
#if !defined(_MSC_VER)
    int sprintf(...);         /* (char *, const char *, ...) */
    char *strcat(...);        /* (char *, const char *) */
    char *strchr(...);        /* (char*, int) */
    int strcmp(...);          /* (char *, char *) */
    char *strcpy(...);        /* (char*, char*) */
    unsigned int strlen(...); /* (char *) */
    int strncmp(...);         /* (const char *, const char *, unsigned) */
    char *strncpy(...);       /* (char *, char *, int) */
    char *strstr(...);        /* (const char *haystack, const char *needle) */
#endif
    extern "C"
    {
        unsigned int systemtask(int taskFlag);
    }
    void timedwait(...); /* (int) */
    void transform(...); /* (void *src, void *mtx, void *dst) */
    void transpose(...); /* (matrixtdef *, matrixtdef *) */
    long unbtree(...);   /* (unsigned char *src, unsigned char *dst) -- lib-source 2-arg (unbtree.cpp) */
    long unhuff(...);    /* (void *src, void *dst, int reverse) */
    long unrefpack(...); /* (void *src, void *dst, int reverse) */
    void vramfxya(...);  /* (void *shape, short imgX, short imgY, short clutX, short clutY) */
    void waitdraw(...);  /* (void) */
    int wildcard(...);   /* (u_char *str, char *pattern) */
    int xformy(...);     /* (matrixtdef *m, int angle) */

} /* extern "C" */

#endif
