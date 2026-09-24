/* eaclib/psx/eacpsxz/stream.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 32/32 ***
 *   Source obj : nfs4\eaclib\psx\stream.obj ; archive C:\nfs4\EACLIB\PSX\EACPSXZ.LIB (xlsx col11)
 *   32 fns @[0x800FC2F8 .. 0x800FDCE0].  EA STREAMING ring-buffer manager, layered directly on the
 *   nfile FILE_* op-queue (FILE_open/read/close/callbackop/completeop/priorityop).  Movie/audio/data
 *   are streamed from a file (or memory image) through a circular buffer, parsed into chunks, and
 *   handed to one of N consumers selected by a filter table.
 *
 *   Dual-source reconstruction: Ghidra `C:\Temp\claud\nfs4-f.exe.c` L161640..162970 (primary, bodies)
 *   verified vs disasm-v3 L325990+ (authoritative for register-arg signatures Ghidra dropped).
 *
 *   ===== STREAM object layout (allocated in the caller buffer by STREAM_create) =====
 *     +0x00 magic 'STRM' (0x4D525453)       +0x04 mutex (allocmutex handle)
 *     +0x08 reqArray  (= obj+0xAC)          +0x0C numReq
 *     +0x10 filterArray (= reqArray+numReq*100)   +0x14 numFilters
 *     +0x18 consumerArray (= filterArray+numFilters*0xC)   +0x1C numConsumers
 *     +0x20 bufBase (= consumerArray+numConsumers*0x10)    +0x24 bufEnd (= obj+bufsize)
 *     +0x28 state (0 idle / 1 active / 2 buffer-full-stall)
 *     +0x2C prio1 (0x96)  +0x30 prio2 (0x32)  +0x34 greedylevel  +0x38 greedystate  +0x3C bufusage
 *     +0x40 readptr (oldest live data)  +0x44 writeptr (consumed up to)  +0x48 fillptr (filled up to)
 *     +0x4C queuehead  +0x50 queuecur (request to start next)  +0x54 queuetail  +0x58 freelist
 *     +0x5C name[0x40] (current file)  +0x9C curfilehandle  +0xA0 readaccum  +0xA4 curFILEop  +0xA8 chunklen
 *   REQUEST (100-byte stride):  id@0 (byte0=slot, high=idcounter)  state@4 (1 queued/2 active/3 done/4 cancel)
 *     prev@8  next@0xC  type@0x10 (0 file / 1 mem)  name[?]@0x14  mem@0x54  off@0x58  len@0x5C  startfill@0x60
 *   CONSUMER (0x10):  streamback@0  id@4 (1-based)  count@8 (bytes available)  readcursor@0xC
 *   FILTER (0xC):  mask@0  match@4  value@8 (consumer id, or -1 discard / -2 skip; default 1)
 *   CHUNK in ring buffer:  word0 tag (-1 wrap / -2 free / else stream-header id)  word1 (len | filterValue<<24)
 */
#include "../../../nfs4_types.h"

/* ---- owning-TU defs for link-harness (extern-declared, never defined; BSS) ---- */
/* stream.obj-local counter @0x8013DEDC; not nasync.obj's @0x8013DEB8. */
static unsigned int stream_requestidcounter;

/* ---- nfile op-queue backend (the layer this is built on) ---- */
extern "C" unsigned int FILE_open(char *name, unsigned int mode, unsigned int prio, unsigned int udata); /*@0x800EC...*/
extern "C" unsigned int FILE_close(void *handle, unsigned int prio, unsigned int udata);
extern "C" unsigned int FILE_read(void *handle, unsigned int offset, unsigned int dest, int len, unsigned int a5, unsigned int a6); /*@0x800EC4EC (asm sets a0..a3 only)*/
extern "C" int FILE_completeop(unsigned int id);
extern "C" void FILE_callbackop(unsigned int id, void (*cb)(int, int)); /*@0x800EBE4C*/
extern "C" void FILE_priorityop(unsigned int id, int prio);             /*@0x800EBECC*/
extern "C" int FILE_closesync(int handle, int priority);                /* syncfile.obj */

/* ---- other eaclib helpers ---- */
extern "C" int allocmutex(void); /* callback.obj @0x800FE424 */
extern "C" void freemutex(int mutex);
extern "C" int iscurrentthread(int t); /* threads.obj */
extern "C" void yieldthread(void);
extern "C" void systemtask(int x);                   /* systask.obj */
extern "C" int strcmp(const char *a, const char *b); /* syslib C23 */
extern "C" char *strcpy(char *d, const char *s);     /* syslib C25 */
#ifndef _MSC_VER
extern "C" char *strncpy(char *d, const char *s, int n); /* syslib C26 */
#endif
#ifndef _MSC_VER
extern "C" void *memcpy(void *d, const void *s, int n); /* syslib C42 @0x800EAAC4 */
#endif
#ifndef _MSC_VER
extern "C" void *memset(void *d, int c, int n); /* syslib C43 @0x800E4318 */
#endif

/* shared async request-id counter (also bumped by nasync; high 24 bits, low byte = slot) */

#define STRM_MAGIC 0x4D525453 /* 'STRM' little-endian */

/* ---- cop0 IRQ-disabled critical section (host no-op; faithful intent on the MIPS target) ---- */
#if defined(__mips__)
extern "C" void STREAM_enterCS(void);
extern "C" void STREAM_leaveCS(void);
#else
static inline void STREAM_enterCS(void)
{
}

static inline void STREAM_leaveCS(void)
{
}
#endif

/* Byte-offset accessors.  The address expression is host-width; the accessed
 * STREAM image word remains the retail 32-bit MIPS word. */
#define MI(p, o) (*(int *)((intptr)(p) + (o)))
#define MU(p, o) (*(unsigned int *)((intptr)(p) + (o)))

/* ---- internal forward decls (mutually recursive) ---- */
extern "C" int validatehandle(intptr handle, intptr *out);                         /* @0x800FC2F8 */
extern "C" unsigned int inbetween(unsigned int a, unsigned int b, unsigned int c); /* @0x800FC334 */
extern "C" int decbufferusage(intptr s, int amount);                               /* @0x800FC374 */
extern "C" int *getfreerequest(intptr s);                                          /* @0x800FC400 */
extern "C" intptr queuerequest(intptr s, intptr req);                              /* @0x800FC478 */
static intptr locaterequest(intptr s, unsigned int reqid);                         /* @0x800FC4E4 */
extern "C" intptr freerequest(intptr s, intptr req);                               /* @0x800FC548 */
extern "C" unsigned int filterchunk(intptr s, intptr chunk);                       /* @0x800FC5E4 */
extern "C" int parsechunks(intptr s);                                              /* @0x800FC634 */
extern "C" void opencallback(int a0, int a1, intptr s);                            /* @0x800FC810 */
extern "C" void closecallback(int a0, int a1, intptr s);                           /* @0x800FC850 */
extern "C" int readcallback(int a0, int a1, intptr s);                             /* @0x800FC8A8 */
extern "C" int startnextrequest(intptr s, unsigned int prio, intptr x);            /* @0x800FC9B4 */
extern "C" int restartstream(intptr s);                                            /* @0x800FCB44 */
extern "C" intptr STREAM_get(intptr consumer, void *buf, int len);                 /* @0x800FD9AC */
extern "C" void STREAM_release(intptr s, intptr consumer);                         /* @0x800FDAD0 */
extern "C" void STREAM_kill(intptr s);                                             /* @0x800FD808 */
extern "C" void STREAM_setgreedystate(intptr s, int state);                        /* @0x800FD2B4 */
extern "C" int STREAM_overhead(int numReq, int numFilters, int numConsumers);      /* @0x800FCDE0 */
extern "C" int STREAM_cancelrequest(intptr s, int req);                            /* @0x800FD554 */

/* ====================================================================================== */

/* validatehandle @0x800FC2F8 : check a STREAM/consumer handle.  `handle[0]` points to the stream
 *   object; if that begins with 'STRM' it is valid.  Returns 0 and writes out[0]=streamobj, out[1]=handle
 *   (the asm stores to *a1 and *a2, with a2 == a1+4); returns 1 otherwise. */
extern "C" int validatehandle(intptr handle, intptr *out)
{
    intptr sobj;
    if (handle == 0)
        return 1;
    sobj = (intptr)(unsigned int)MI(handle, 0);
    if (*(int *)sobj == STRM_MAGIC)
    {
        out[1] = handle; /* asm: *a2 = a0 (the handle)                 */
        out[0] = sobj;   /* asm: *a1 = a3 (the stream object), delay slot */
        return 0;
    }
    return 1;
}

/* inbetween @0x800FC334 : is offset `c` inside the (possibly wrapped) ring interval [a, b)? */
extern "C" unsigned int inbetween(unsigned int a, unsigned int b, unsigned int c)
{
    if (a <= b)
    {
        if (a <= c)
            return (c < b) ? 1u : 0u;
        return 0u;
    }
    if (a <= c || c < b)
        return 1u;
    return 0u;
}

/* decbufferusage @0x800FC374 : subtract `amount` bytes from the stream's buffer usage (+0x3C), inside a
 *   critical section.  If usage falls back below the greedy level while the stream is actively reading
 *   (state==1), drop the in-flight read's priority via FILE_priorityop. */
extern "C" int decbufferusage(intptr s, int amount)
{
    int old, neu, ret;
    STREAM_enterCS();
    old = MI(s, 0x3c);
    neu = old - amount;
    MI(s, 0x3c) = neu;
    STREAM_leaveCS();
    ret = (neu < MI(s, 0x34));
    if (MI(s, 0x34) <= old && ret != 0)
    {
        ret = 1;
        MI(s, 0x38) = 1; /* greedy state on */
        if (MI(s, 0x28) == 1)
            FILE_priorityop(MI(s, 0xa4), MI(s, 0x30));
    }
    return ret;
}

/* getfreerequest @0x800FC400 : pop a request slot off the freelist (+0x58), stamp it with a fresh id
 *   (the rolling requestidcounter in the high 24 bits), inside a critical section.  Returns 0 if none. */
extern "C" int *getfreerequest(intptr s)
{
    int *req, *ret;
    STREAM_enterCS();
    req = (int *)(intptr)MU(s, 0x58);
    ret = 0;
    if (req != 0)
    {
        stream_requestidcounter += 0x100;
        MI(s, 0x58) = req[3]; /* freelist head = req->next (+0xC) */
        if (stream_requestidcounter == 0)
            stream_requestidcounter = 0x100;
        req[0] = (int)((unsigned char)req[0] | stream_requestidcounter); /* id = slot | counter */
        ret = req;
    }
    STREAM_leaveCS();
    return ret;
}

/* queuerequest @0x800FC478 : append a request to the active queue (head@0x4C / cur@0x50 / tail@0x54),
 *   inside a critical section.  Returns the previous tail (0 if the queue was empty). */
extern "C" intptr queuerequest(intptr s, intptr req)
{
    intptr ret;
    MI(req, 4) = 1;   /* state = queued */
    MI(req, 0xc) = 0; /* next = 0 */
    STREAM_enterCS();
    if (MI(s, 0x54) == 0)
    { /* empty queue */
        MI(req, 8) = 0;
        MI(s, 0x4c) = req; /* head = cur = req */
        MI(s, 0x50) = req;
        ret = 0;
    }
    else
    {
        MI(req, 8) = MI(s, 0x54); /* prev = old tail */
        ret = MI(s, 0x54);
        MI(ret, 0xc) = req; /* old tail->next = req */
    }
    MI(s, 0x54) = req; /* tail = req */
    STREAM_leaveCS();
    return ret;
}

/* locaterequest @0x800FC4E4 : map a request id back to its slot, validating the slot index (low byte),
 *   the full id, and that the slot is in use.  Returns the request pointer or 0. */
static intptr locaterequest(intptr s, unsigned int reqid)
{
    unsigned int *req;
    if (MI(s, 0xc) <= (int)(reqid & 0xff)) /* slot index out of range */
        return 0;
    req = (unsigned int *)((intptr)(unsigned int)MU(s, 8) + (reqid & 0xff) * 100);
    if (reqid == req[0] && req[1] != 0) /* id matches and slot active */
        return (intptr)req;
    return 0;
}

/* freerequest @0x800FC548 : unlink a request from the active queue and push it onto the freelist.
 *   Returns the new freelist tail. */
extern "C" intptr freerequest(intptr s, intptr req)
{
    intptr ret;
    if (req == MI(s, 0x4c)) /* head */
        MI(s, 0x4c) = MI(req, 0xc);
    else
        MI(MI(req, 8) + 0xc, 0) = MI(req, 0xc); /* prev->next = req->next */

    if (req == MI(s, 0x54)) /* tail */
        MI(s, 0x54) = MI(req, 8);
    else
        MI(MI(req, 0xc) + 8, 0) = MI(req, 8); /* next->prev = req->prev */

    if (req == MI(s, 0x50))
    { /* cur */
        ret = MI(req, 0xc);
        if (ret == 0)
            ret = MI(req, 8);
        MI(s, 0x50) = ret;
    }
    MI(req, 4) = 0; /* state = free */
    ret = MI(s, 0x58);
    MI(req, 0xc) = ret; /* req->next = old freelist */
    MI(s, 0x58) = req;  /* freelist = req */
    return ret;
}

/* filterchunk @0x800FC5E4 : classify a chunk by its first word against the filter table; returns the
 *   matching filter's consumer value, or 0xFFFFFFFE ("skip") if none match. */
extern "C" unsigned int filterchunk(intptr s, intptr chunk)
{
    unsigned int *f;
    int i = 0;
    if (0 < MI(s, 0x14))
    {
        f = (unsigned int *)(intptr)MU(s, 0x10); /* filterArray */
        do
        {
            i++;
            if ((*(unsigned int *)chunk & f[0]) == f[1])
                return f[2];
            f += 3;
        } while (i < MI(s, 0x14));
    }
    return 0xfffffffeu;
}

/* parsechunks @0x800FC634 : walk newly-filled buffer data, splitting it into chunks.  Each chunk header
 *   is {tag, len}; the chunk is classified by filterchunk, tagged with its consumer in the high byte of
 *   word1, and accounted to that consumer.  Stops at a short/invalid header or the end-of-stream id.
 *   Returns 1 if the end-of-stream marker was reached, else 0. */
extern "C" int parsechunks(intptr s)
{
    int bvar1;
    int iVar2, iVar4;
    intptr fillAddress;
    unsigned int uVar3, uVar5;
    int *chunk;
    intptr reqcur;

    fillAddress = (intptr)MU(s, 0x48);  /* fillptr */
    chunk = (int *)(intptr)MU(s, 0x44); /* writeptr */
    reqcur = MI(s, 0x50);               /* current request */
    iVar2 = (int)(fillAddress - (intptr)chunk);

    while (1)
    {
        if (iVar2 < 8 || ((uVar5 = chunk[1], (uVar5 & 0xff000000) != 0)) || fillAddress < (intptr)chunk + uVar5)
            return 0; /* incomplete / malformed chunk */

        uVar3 = filterchunk(s, (intptr)chunk);
        if ((int)uVar3 < 0)
        { /* no consumer (skip) */
            STREAM_enterCS();
            bvar1 = (MI(reqcur, 4) == 4); /* request cancelled? */
            if (!bvar1)
            {
                chunk[0] = -2;        /* mark chunk free */
                MI(s, 0x44) += uVar5; /* advance writeptr */
            }
            STREAM_leaveCS();
        }
        else
        { /* routed to consumer uVar3 */
            chunk[1] = chunk[1] | (uVar3 << 0x18);
            STREAM_enterCS();
            bvar1 = (MI(reqcur, 4) == 4);
            if (!bvar1)
            {
                intptr cons = (intptr)(unsigned int)MU(s, 0x18) + uVar3 * 0x10 - 0x10; /* consumer slot */
                uVar3 = MI(cons, 8) + uVar5;
                MI(cons, 8) = uVar3;                    /* consumer.count += len */
                if (uVar3 == uVar5)                     /* first chunk for this consumer */
                    MI(cons, 0xc) = (int)(intptr)chunk; /* retail 32-bit readcursor field */
                MI(s, 0x44) += uVar5;                   /* advance writeptr */
                iVar2 = MI(s, 0x3c);
                iVar4 = iVar2 + uVar5;
                MI(s, 0x3c) = iVar4; /* bufusage += len */
                if (iVar2 < MI(s, 0x34) && MI(s, 0x34) <= iVar4)
                    MI(s, 0x38) = 0; /* crossed greedy level -> greedy off */
            }
            STREAM_leaveCS();
        }
        if (bvar1)
            break;
        if (chunk[0] == MI(reqcur, 0x5c)) /* reached end-of-stream id */
            return 1;
        fillAddress = (intptr)MU(s, 0x48);
        chunk = (int *)(intptr)MU(s, 0x44);
        iVar2 = (int)(fillAddress - (intptr)chunk);
    }
    return 0;
}

/* opencallback @0x800FC810 : nfile open-op completion (stream object arrives in $a2 = udata).  Stash the
 *   opened file handle (+0x9C); if valid, kick the stream's fill engine. */
extern "C" void opencallback(int a0, int a1, intptr s)
{
    unsigned int h;
    h = FILE_completeop(MU(s, 0xa4));
    MU(s, 0x9c) = h;
    if (h != 0)
        restartstream(s);
}

/* closecallback @0x800FC850 : nfile close-op completion -> immediately open the next file (its name was
 *   already copied to +0x5C) and arm opencallback. */
extern "C" void closecallback(int a0, int a1, intptr s)
{
    unsigned int op;
    FILE_completeop(MU(s, 0xa4));
    op = FILE_open((char *)(s + 0x5c), 1, MU(s, 0x30), (unsigned int)s);
    MU(s, 0xa4) = op;
    if (op != 0)
        FILE_callbackop(op, (void (*)(int, int))opencallback);
}

/* readcallback @0x800FC8A8 : nfile read-op completion (stream object in $a2).  Advances the read
 *   accounting, parses the freshly-filled data into chunks, and either continues filling or, when the
 *   request finishes, marks it done and starts the next queued request. */
extern "C" int readcallback(int a0, int a1, intptr s)
{
    int bvar1;
    int iVar2;
    unsigned int uVar3;
    intptr reqcur;

    reqcur = MI(s, 0x50);
    if (MI(reqcur, 0x10) == 1)
    { /* memory source */
        uVar3 = MU(s, 0xa8);
        bvar1 = (MI(reqcur, 0x58) <= (int)(MI(s, 0xa0) + uVar3));
    }
    else
    { /* file source */
        uVar3 = FILE_completeop(MU(s, 0xa4));
        bvar1 = ((int)uVar3 < MI(s, 0xa8));
    }
    MU(s, 0xa0) += uVar3; /* readaccum += bytes */
    MU(s, 0x48) += uVar3; /* fillptr   += bytes */
    iVar2 = parsechunks(s);
    if (MI(reqcur, 4) != 4)
    { /* not cancelled */
        if (!bvar1 && iVar2 == 0)
            return restartstream(s); /* more to read, no EOS -> keep going */
        STREAM_enterCS();
        MI(reqcur, 4) = 3; /* request done */
        STREAM_leaveCS();
    }
    return startnextrequest(s, MU(s, 0x30), (unsigned int)s);
}

/* startnextrequest @0x800FC9B4 : advance the active queue cursor (+0x50) to the next runnable request,
 *   open/seek its file (or rebind to the memory image), and kick restartstream.  Sets state idle if the
 *   queue drains. */
extern "C" int startnextrequest(intptr s, unsigned int prio, intptr x)
{
    int done;
    int ret = 0;
    intptr cur;
    intptr req;

    STREAM_enterCS();
    cur = MI(s, 0x50);
    done = 1;
    if (cur != 0)
    {
        ret = 1;
        done = 0;
        if (MI(cur, 4) != 1)
        {                       /* current no longer queued */
            ret = MI(cur, 0xc); /* advance to next */
            if (ret == 0)
                done = 1;
            else
                MI(s, 0x50) = ret;
        }
    }
    if (done)
    {
        MI(s, 0x28) = 0; /* state idle */
    }
    else
    {
        req = MI(s, 0x50);
        MI(req, 0x60) = MI(s, 0x44); /* request start fill ptr = writeptr */
        ret = 2;
        MI(req, 4) = 2; /* state = active */
    }
    STREAM_leaveCS();

    if (!done)
    {
        MI(s, 0x48) = MI(s, 0x44); /* fillptr = writeptr */
        if (MI(req, 0x10) == 1)
        { /* memory source */
            MI(s, 0xa0) = 0;
        }
        else
        { /* file source */
            intptr name = s + 0x5c;
            MI(s, 0xa0) = MI(req, 0x58); /* readaccum = request offset */
            if (strcmp((char *)(req + 0x14), (char *)name) != 0)
            { /* different file */
                strcpy((char *)name, (char *)(req + 0x14));
                if (MU(s, 0x9c) != 0)
                { /* close the open file first */
                    unsigned int op = FILE_close((void *)(intptr)MU(s, 0x9c), prio, (unsigned int)s);
                    MU(s, 0xa4) = op;
                    if (op == 0)
                        return 0;
                    FILE_callbackop(op, (void (*)(int, int))closecallback);
                    return op;
                }
                {
                    unsigned int op = FILE_open((char *)name, 1, prio, (unsigned int)s);
                    MU(s, 0xa4) = op;
                    if (op == 0)
                        return 0;
                    FILE_callbackop(op, (void (*)(int, int))opencallback);
                    return op;
                }
            }
        }
        ret = restartstream(s);
    }
    return ret;
}

/* restartstream @0x800FCB44 : the buffer fill engine.  Reclaims free space at the read head, releases
 *   spent requests, wraps the ring when needed, computes the next contiguous fill region, and issues the
 *   next chunk read -- from the memory image (memcpy + readcallback) or via FILE_read + readcallback.
 *   Stalls (state 2) if there is not at least one sector of room. */
extern "C" int restartstream(intptr s)
{
    int iVar1, iVar2;
    intptr uVar3, uVar5;
    intptr request, requestNext;
    int *p;
    int *q;

    /* skip wrap/free markers at the read head (+0x40) up to the writeptr (+0x44) */
    request = (intptr)(unsigned int)MU(s, 0x40);
    while (request != (intptr)(unsigned int)MU(s, 0x44))
    {
        p = (int *)request;
        if (p[0] == -1)
        { /* wrap marker -> jump to bufBase (+0x20) */
            MI(s, 0x40) = MI(s, 0x20);
        }
        else
        {
            if (p[0] != -2) /* a live chunk -> stop */
                break;
            MI(s, 0x40) = (int)((intptr)p + p[1]); /* retail 32-bit readptr field */
        }
        request = (intptr)(unsigned int)MU(s, 0x40);
    }

    /* free finished requests whose data has been fully consumed */
    STREAM_enterCS();
    request = (intptr)(unsigned int)MU(s, 0x4c); /* queue head */
    requestNext = (intptr)(unsigned int)MU(request, 0xc);
    while (requestNext != 0 && MI(requestNext, 4) != 1 && inbetween(MU(s, 0x40), MU(s, 0x48), MI(requestNext, 0x60) - 1) == 0)
    {
        freerequest(s, request);
        request = (intptr)(unsigned int)MU(s, 0x4c);
        requestNext = (intptr)(unsigned int)MU(request, 0xc);
    }
    STREAM_leaveCS();

    /* compute the next contiguous fill region [fillptr .. readptr) */
    uVar3 = (intptr)MU(s, 0x40); /* readptr */
    uVar5 = (intptr)MU(s, 0x48); /* fillptr */
    iVar1 = (int)(uVar3 - uVar5);
    if (uVar3 <= uVar5)
    {
        iVar1 = (MI(s, 0x24) - uVar5) - 8; /* room to bufEnd, less header */
        if (0x1fff < iVar1)
            goto have_room;
        /* not enough tail room -> wrap: move the partial chunk down to bufBase */
        iVar2 = (int)(uVar5 - (intptr)MU(s, 0x44));
        if ((int)(uVar3 - (intptr)MU(s, 0x20)) < iVar2 + 1)
            goto stall;
        memcpy((void *)(intptr)MU(s, 0x20), (void *)(intptr)MU(s, 0x44), iVar2);
        q = (int *)(intptr)MU(s, 0x44);
        q[0] = -1; /* leave a wrap marker behind */
        q[1] = 8;
        iVar2 = MI(s, 0x20) + iVar2;
        iVar1 = MI(s, 0x40) - iVar2;
        MI(s, 0x44) = MI(s, 0x20);
        MI(s, 0x48) = iVar2;
    }
    iVar1 = iVar1 - 1;
    if (iVar1 < 0x2000)
    {
    stall:
        MI(s, 0x28) = 2; /* buffer-full stall */
        return 2;
    }
have_room:
    request = (intptr)(unsigned int)MU(s, 0x50); /* current request */
    if (MI(request, 0x10) == 1)
    { /* memory source -> memcpy a chunk in */
        if (MI(request, 0x58) < MI(s, 0xa0) + iVar1)
            MI(s, 0xa8) = MI(request, 0x58) - MI(s, 0xa0); /* clamp to remaining */
        else
            MI(s, 0xa8) = iVar1;
        memcpy((void *)(intptr)MU(s, 0x48), (void *)(intptr)MU(request, 0x54), MI(s, 0xa8));
        MI(request, 0x54) += MI(s, 0xa8); /* advance mem source ptr */
        return readcallback(0, 0, s);
    }
    /* file source -> issue a sector read */
    MI(s, 0xa8) = 0x2000;
    {
        unsigned int op = FILE_read((void *)(intptr)MU(s, 0x9c), MU(s, 0xa0), (intptr)MU(s, 0x48), MI(s, 0xa8), 0, (intptr)s);
        MU(s, 0xa4) = op;
        if (op == 0)
            return 0;
        FILE_callbackop(op, (void (*)(int, int))readcallback);
        return op;
    }
}

/* STREAM_overhead @0x800FCDE0 : bytes of bookkeeping a stream of this shape needs (excluding the ring). */
extern "C" int STREAM_overhead(int numReq, int numFilters, int numConsumers)
{
    return numReq * 100 + (numFilters * 0xc + 0xac) + numConsumers * 0x10;
}

/* STREAM_create @0x800FCE14 : lay a stream object + its sub-arrays into `objbuf` (size `bufsize`) and
 *   initialise the request freelist, filter table and consumer table.  Validates counts and that at
 *   least 0x6000 bytes remain for the ring.  Returns the consumer-array handle (obj+0x18 value), 0 on
 *   failure. */
extern "C" intptr STREAM_create(int numReq, int numFilters, int numConsumers, void *objbuf, int bufsize)
{
    int over, i, off;
    intptr objaddr = (intptr)objbuf;
    intptr base;

    over = STREAM_overhead(numReq, numFilters, numConsumers);
    if (bufsize - over < 0x6000)
        return 0;
    if (numReq < 2 || numReq >= 0x101)
        return 0;
    if ((unsigned int)(numFilters - 1) > 0xf)
        return 0;
    if (numConsumers <= 0)
        return 0;
    if (numFilters < numConsumers)
        return 0;

    MI(objaddr, 0x00) = STRM_MAGIC;
    MI(objaddr, 0x04) = allocmutex();
    MI(objaddr, 0x08) = (int)(objaddr + 0xac);    /* retail reqArray word */
    MI(objaddr, 0x24) = (int)(objaddr + bufsize); /* retail bufEnd word */
    MI(objaddr, 0x2c) = 0x96;
    MI(objaddr, 0x0c) = numReq;
    MI(objaddr, 0x14) = numFilters;
    MI(objaddr, 0x1c) = numConsumers;
    MI(objaddr, 0x28) = 0;
    MI(objaddr, 0x34) = 0;
    MI(objaddr, 0x38) = 0;
    MI(objaddr, 0x3c) = 0;
    MI(objaddr, 0x4c) = 0;
    MI(objaddr, 0x50) = 0;
    MI(objaddr, 0x54) = 0;
    base = (intptr)(unsigned int)MU(objaddr, 0x08) + numReq * 100;
    MI(objaddr, 0x10) = (int)base; /* retail filterArray word */
    base = base + numFilters * 0xc;
    MI(objaddr, 0x18) = (int)base; /* retail consumerArray word */
    base = base + numConsumers * 0x10;
    MI(objaddr, 0x20) = (int)base; /* retail bufBase word */
    MI(objaddr, 0x30) = 0x32;
    MI(objaddr, 0x40) = (int)base;
    MI(objaddr, 0x44) = (int)base;
    MI(objaddr, 0x48) = (int)base;
    MI(objaddr, 0x58) = MI(objaddr, 0x08);     /* freelist = reqArray[0] */
    memset((void *)(objaddr + 0x5c), 0, 0x40); /* clear name */
    MI(objaddr, 0x9c) = 0;

    /* thread the request freelist */
    i = 0;
    if (numReq > 0)
    {
        int stride = 100, idx = 0;
        do
        {
            int *r = (int *)((intptr)(unsigned int)MU(objaddr, 0x08) + idx);
            idx += 100;
            r[0] = i; /* id = slot index */
            r[1] = 0;
            i++;
            r[3] = MI(objaddr, 0x08) + stride; /* next */
            stride += 100;
        } while (i < numReq);
    }
    MI(numReq * 100 + MI(objaddr, 0x08) - 0x58, 0) = 0; /* last->next = 0 (offset +0xC of last slot) */

    /* clear the filter table */
    i = 0;
    if (numFilters > 0)
    {
        int idx = 0;
        do
        {
            int *f = (int *)((intptr)(unsigned int)MU(objaddr, 0x10) + idx);
            i++;
            f[0] = 0;
            f[1] = 0;
            f[2] = 1;
            idx += 0xc;
        } while (i < numFilters);
    }

    /* init the consumer table (back-pointer + 1-based id) */
    i = 0;
    if (numConsumers > 0)
    {
        do
        {
            int *c;
            i++;
            c = (int *)((intptr)(unsigned int)MU(objaddr, 0x18) + (i - 1) * 0x10);
            c[0] = (int)objaddr; /* retail stream back-pointer word */
            c[1] = i;
            c[2] = 0;
        } while (i < numConsumers);
    }
    return (intptr)(unsigned int)MU(objaddr, 0x18);
}

/* STREAM_setfilter @0x800FD054 : program filter slot `filterIdx` (1-based) with {mask, match, value}.
 *   `value` is the target consumer id (>0), or -1 (discard) / -2 (skip).  The last filter must be the
 *   catch-all (mask==0 && match==0).  Ignored unless the stream is idle (state 0). */
extern "C" void STREAM_setfilter(intptr consumer, int filterIdx, unsigned int mask, unsigned int match, int value)
{
    intptr out[2];
    if (validatehandle(consumer, out) != 0)
        return;
    if (filterIdx <= 0 || filterIdx > MI(out[0], 0x14))
        return;
    if (filterIdx == MI(out[0], 0x14) && !(mask == 0 && match == 0))
        return; /* last slot must be catch-all */
    if (!(value > 0 || value == -1 || value == -2))
        return;
    if (value > MI(out[0], 0x1c))
        return;
    if (MI(out[0], 0x28) != 0) /* must be idle */
        return;
    {
        int *f = (int *)(MI(out[0], 0x10) + filterIdx * 0xc - 0xc);
        f[0] = (int)mask;
        f[1] = (int)match;
        f[2] = value;
    }
}

/* STREAM_destroy @0x800FD144 : kill all requests, wait for the final op to drain, drop the magic, free
 *   the mutex, and close the sync file. */
extern "C" void STREAM_destroy(intptr s)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return;
    STREAM_kill(s);
    while (MI(out[0], 0x28) == 1)
    { /* wait until not actively reading */
        if (iscurrentthread(0) != 0)
            systemtask(0);
        yieldthread();
    }
    MI(out[0], 0) = 0; /* invalidate magic */
    freemutex(MI(out[0], 4));
    FILE_closesync(MI(out[0], 0x9c), 0x64);
}

/* STREAM_setpriority @0x800FD1F8 : set the stream's two priority words (+0x2C, +0x30). */
extern "C" void STREAM_setpriority(intptr s, int prioA, int prioB)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return;
    MI(out[0], 0x2c) = prioA;
    MI(out[0], 0x30) = prioB;
}

/* STREAM_setgreedylevel @0x800FD248 : set the greedy fill threshold (+0x34); if the buffer-usage-vs-level
 *   relation flips, update the greedy state. */
extern "C" void STREAM_setgreedylevel(intptr s, int lvl)
{
    intptr out[2];
    int oldlvl, state;
    if (validatehandle(s, out) != 0)
        return;
    oldlvl = MI(out[0], 0x34);
    state = (MI(out[0], 0x3c) < lvl);
    MI(out[0], 0x34) = lvl;
    if ((MI(out[0], 0x3c) < oldlvl) != state)
        STREAM_setgreedystate(s, state);
}

/* STREAM_setgreedystate @0x800FD2B4 : set the greedy state (+0x38); when turning on while actively
 *   reading, bump the in-flight op back up to the stream's read priority. */
extern "C" void STREAM_setgreedystate(intptr s, int state)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return;
    MI(out[0], 0x38) = state;
    if (state != 0 && MI(out[0], 0x28) == 1)
        FILE_priorityop(MI(out[0], 0xa4), MI(out[0], 0x30));
}

/* STREAM_queuefile @0x800FD314 : queue a read of `len` bytes at `off` from file `name`.  Allocates a
 *   request, fills it, queues it, and -- if the stream was idle -- starts it.  Returns the request id. */
extern "C" unsigned int STREAM_queuefile(intptr s, char *name, int off, int len)
{
    intptr out[2];
    int *req;
    unsigned int id = 0;
    if (validatehandle(s, out) != 0)
        return 0;
    req = getfreerequest(out[0]);
    if (req == 0)
        return 0;
    req[4] = 0;                             /* type = file */
    strncpy((char *)(req + 5), name, 0x40); /* req name @ +0x14 */
    req[0x16] = off;
    req[0x17] = len;
    queuerequest(out[0], (intptr)req);
    {
        int wasidle;
        STREAM_enterCS();
        wasidle = (MI(out[0], 0x28) == 0);
        if (wasidle)
            MI(out[0], 0x28) = 1;
        STREAM_leaveCS();
        if (wasidle)
        {
            unsigned int prio = (MI(out[0], 0x38) == 0) ? MU(out[0], 0x2c) : MU(out[0], 0x30);
            startnextrequest(out[0], prio, id);
        }
    }
    return (unsigned int)req[0];
}

/* STREAM_queuemem @0x800FD428 : queue a read of `len` bytes from a memory image.  If `ptr` is null, the
 *   source is a chained block list walked to the `len`-th node.  Returns the request id. */
extern "C" unsigned int STREAM_queuemem(intptr s, intptr blocklist, void *ptr, int len)
{
    intptr out[2];
    int *req;
    if (validatehandle(s, out) != 0)
        return 0;
    req = getfreerequest(out[0]);
    if (req == 0)
        return 0;
    if (ptr == 0)
    { /* resolve offset by walking the block chain */
        int acc = 0;
        int *p = (int *)blocklist;
        int v = *p;
        while (v != len)
        {
            int blklen = p[1];
            p = (int *)((intptr)p + blklen);
            acc += blklen;
            v = *p;
        }
        ptr = (void *)(acc + p[1]);
    }
    req[4] = 1;                   /* type = memory */
    req[0x15] = (int)blocklist;   /* retail 32-bit mem source base */
    req[0x16] = (int)(intptr)ptr; /* retail 32-bit mem cursor */
    req[0x17] = len;
    queuerequest(out[0], (intptr)req);
    {
        int wasidle;
        STREAM_enterCS();
        wasidle = (MI(out[0], 0x28) == 0);
        if (wasidle)
            MI(out[0], 0x28) = 1;
        STREAM_leaveCS();
        if (wasidle)
            startnextrequest(out[0], 0, 0);
    }
    return (unsigned int)req[0];
}

/* STREAM_cancelrequest @0x800FD554 : cancel an in-flight or queued request and reclaim any of its data
 *   already sitting in the ring buffer (returning consumed chunks via STREAM_get/release, freeing
 *   un-consumed ones).  Returns 0 on success, 1 if it could not be cancelled. */
extern "C" int STREAM_cancelrequest(intptr s, int reqid)
{
    intptr out[2];
    int ret;
    intptr req;
    int *s4, *s6, *s7;

    if (validatehandle(s, out) != 0)
        return 1;
    s = out[0]; /* stream object */

    STREAM_enterCS();
    req = locaterequest(s, reqid);
    if (req != 0 && MI(req, 4) != 4)
    {
        if (MI(req, 4) != 1)
        {                                    /* active (not merely queued) */
            MI(req, 4) = 4;                  /* mark cancelled */
            s7 = (int *)(intptr)MU(s, 0x40); /* readptr */
            s4 = s7;
            if (req != MI(s, 0x4c))
                s4 = (int *)(intptr)MU(req, 0x60); /* this request's start fill */
            {
                int nx = MI(req, 0xc);
                if (nx == 0 || MI(nx, 4) == 1)
                {
                    s6 = (int *)(intptr)MU(s, 0x44); /* writeptr */
                    ret = 0;
                }
                else
                {
                    s6 = (int *)(intptr)MU(nx, 0x60);
                    ret = 0;
                }
            }
            goto reclaim;
        }
        freerequest(s, req); /* queued -> just drop it */
    }
    ret = 1;
reclaim:
    STREAM_leaveCS();
    if (ret != 0)
        return ret;

    /* sweep every consumer, returning or freeing the cancelled request's chunks */
    {
        int nC = MI(s, 0x1c);
        int ci = 0;
        if (nC > 0)
        {
            do
            {
                intptr cons = (intptr)(unsigned int)MU(s, 0x18) + ci * 0x10;
                if (MI(cons, 8) > 0)
                {
                    unsigned int u2 = inbetween((unsigned int)s7, (unsigned int)s4, MU(cons, 0xc));
                    if (u2 == 0)
                    { /* consumer head is before this request -> drain it */
                        unsigned int pos = MU(cons, 0xc);
                        int *p;
                        while ((p = s6, inbetween((unsigned int)s4, (unsigned int)s6, pos) != 0))
                        {
                            ret = STREAM_get(cons, p, pos);
                            STREAM_release(cons, ret);
                            if (MI(cons, 8) < 1)
                                break;
                            pos = MU(cons, 0xc);
                        }
                    }
                    else
                    { /* free this request's own chunks in place */
                        int rstate = MI(cons, 4);
                        int *p = s4;
                        while (p != s6)
                        {
                            if (p[0] == -1)
                            {
                                p = (int *)(intptr)MU(s, 0x20); /* wrap */
                            }
                            else
                            {
                                unsigned int len = p[1] & 0xffffff;
                                if ((unsigned int)(p[1] & 0xff000000) == (unsigned int)(rstate << 0x18))
                                {
                                    STREAM_enterCS();
                                    MI(cons, 8) -= len;
                                    STREAM_leaveCS();
                                    decbufferusage(s, len);
                                    p[0] = -2;
                                    p[1] = len;
                                }
                                p = (int *)((intptr)p + len);
                            }
                        }
                    }
                }
                ci++;
                ret = 0;
            } while (ci < MI(s, 0x1c));
        }
    }
    return ret;
}

/* STREAM_kill @0x800FD808 : cancel every request, free the queue, reset the ring to empty and the state
 *   to idle. */
extern "C" void STREAM_kill(intptr s)
{
    intptr out[2];
    intptr consumer;
    int *q;
    if (validatehandle(s, out) != 0)
        return;
    consumer = out[1];
    s = out[0];
    q = (int *)(intptr)MU(s, 0x54); /* tail */
    if (q == 0)
        return;

    while ((unsigned int)(q[1] - 1) < 2)
    { /* cancel active/done requests */
        STREAM_cancelrequest(consumer, q[0]);
        q = (int *)(intptr)MU(s, 0x54);
    }
    while (MI(s, 0x4c) != MI(s, 0x50)) /* free the rest of the queue */
        freerequest(s, MI(s, 0x4c));
    MI(MI(s, 0x50) + 4, 0) = 4; /* mark last cancelled */

    {
        int i = 0;
        if (MI(s, 0x1c) > 0)
        { /* zero all consumer counts */
            do
            {
                MI(i * 0x10 + MI(s, 0x18) + 8, 0) = 0;
                i++;
            } while (i < MI(s, 0x1c));
        }
    }
    decbufferusage(s, MI(s, 0x3c)); /* zero the buffer usage */

    q = (int *)(intptr)MU(s, 0x40); /* free-mark the whole ring */
    if (q != (int *)(intptr)MU(s, 0x44))
    {
        do
        {
            if (q[0] == -1)
            {
                q = (int *)(intptr)MU(s, 0x20);
            }
            else
            {
                unsigned int len = q[1];
                q[0] = -2;
                q[1] = len & 0xffffff;
                q = (int *)((intptr)q + (len & 0xffffff));
            }
        } while (q != (int *)(intptr)MU(s, 0x44));
    }
    if (MI(s, 0x28) == 2)
        MI(s, 0x28) = 0; /* clear the stall */
}

/* STREAM_get @0x800FD9AC : pop the next available chunk for a consumer, returning a pointer to its data
 *   (or 0 if none).  Advances the consumer's read cursor to the following same-tagged chunk. */
extern "C" intptr STREAM_get(intptr consumer, void *buf, int len)
{
    intptr out[2];
    intptr cons, chunk;
    unsigned int hdr;
    int *p;

    if (validatehandle(consumer, out) != 0)
        return 0;
    cons = out[1];        /* the consumer handle */
    if (MI(cons, 8) == 0) /* no data available */
        return 0;

    chunk = MI(cons, 0xc); /* readcursor */
    hdr = MU(chunk, 4) & 0xffffff;
    MU(chunk, 4) = hdr; /* strip the consumer tag */
    STREAM_enterCS();
    {
        int rem = MI(cons, 8) - hdr;
        MI(cons, 8) = rem; /* count -= len */
        STREAM_leaveCS();
        if (0 < rem)
        { /* advance cursor to next same-tagged chunk */
            p = (int *)(chunk + hdr);
            hdr = p[1];
            while ((hdr & 0xff000000) != (unsigned int)(MI(cons, 4) << 0x18))
            {
                if (p[0] == -1)
                    p = (int *)(intptr)MU(out[0], 0x20); /* wrap */
                else
                    p = (int *)((intptr)p + (p[1] & 0xffffff));
                hdr = p[1];
            }
            MI(cons, 0xc) = (int)(intptr)p; /* retail 32-bit readcursor field */
        }
    }
    return chunk;
}

/* STREAM_release @0x800FDAD0 : release a chunk previously obtained from STREAM_get, freeing its ring
 *   space and, if the stream had stalled (state 2) on a full buffer, re-arming the fill engine. */
extern "C" void STREAM_release(intptr s, intptr chunk)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return;
    if ((unsigned int)chunk < MU(out[0], 0x20)) /* below bufBase */
        return;
    if ((unsigned int)(MI(out[0], 0x24) - 8) < (unsigned int)chunk) /* above bufEnd-8 */
        return;
    if (MI(chunk, 0) == -2) /* already free */
        return;
    decbufferusage(out[0], MI(chunk, 4)); /* account the chunk's bytes back */
    MI(chunk, 0) = -2;                    /* mark free */
    {
        int wasstall;
        STREAM_enterCS();
        wasstall = (MI(out[0], 0x28) == 2);
        if (wasstall)
            MI(out[0], 0x28) = 1;
        STREAM_leaveCS();
        if (wasstall)
            restartstream(out[0]);
    }
}

/* STREAM_gettable @0x800FDBCC : return the stream's consumer-array base (+0x08 reqArray... actually the
 *   "table" pointer at +0x08). */
extern "C" int STREAM_gettable(intptr s)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return 0;
    return MI(out[1], 8);
}

/* STREAM_state @0x800FDC04 : return the stream state word (+0x28). */
extern "C" int STREAM_state(intptr s)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return 0;
    return MI(out[0], 0x28);
}

/* STREAM_isendofstream @0x800FDC3C : true iff the stream is idle (state 0) and the consumer has no data. */
extern "C" int STREAM_isendofstream(intptr s)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return 0;
    if (MI(out[0], 0x28) != 0)
        return 0;
    return (MI(out[1], 8) == 0);
}

/* STREAM_buffersize @0x800FDC98 : the ring buffer size (bufEnd - bufBase). */
extern "C" int STREAM_buffersize(intptr s)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return 0;
    return MI(out[0], 0x24) - MI(out[0], 0x20);
}

/* STREAM_bufferusage @0x800FDCE0 : current bytes of buffered (filled) data (+0x3C). */
extern "C" int STREAM_bufferusage(intptr s)
{
    intptr out[2];
    if (validatehandle(s, out) != 0)
        return 0;
    return MI(out[0], 0x3c);
}
