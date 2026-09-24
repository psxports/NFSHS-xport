/* eaclib/psx/sndpsxz/sst.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 16/16 ***
 *   Source obj : nfs4\eaclib\psx\sst.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   16 fns @[0x800E8C14 .. 0x800E9970].  EA SCxl STREAMING-AUDIO decoder ("iSNDstream*").
 *   Pulls audio chunks out of the stream.obj ring (STREAM_get) and feeds them to the SNDPKTPLAY
 *   packet player.  Chunk tags (little-endian): 'SChl'=0x6C485343 header / 'SCCl'=0x6C435343 count /
 *   'SCDl'=0x6C445343 data / 'SCEl'=0x6C455343 end.
 *
 *   Dual-source reconstruction: Ghidra `C:\Temp\claud\nfs4-f.exe.c` L145852..146572 (bodies) verified
 *   vs disasm-v3 L299099..300132 (authoritative -- Ghidra mangled 6 fns: lwl/lwr unaligned format
 *   copies in parseheader/service, dropped register args in parsedata/hotrod/create/queue).
 *
 *   ===== stream object S (one slot, sndss[0]) =====
 *     +0x00 packetsArray (request stride 0x2C)   +0x04 STREAM handle (stream.obj)
 *     +0x08 SNDPKTPLAY_start result (-1 idle)    +0x0C SNDPKTPLAY handle
 *     +0x10 request-id counter (+=0x100)         +0x14(b) state (0/1=playing/2=needs-restart)
 *     +0x15(b) maxReq   +0x16(b) curReqCount   +0x17(b) parseIdx   +0x18(b) extStreamFlag
 *     +0x1C..0x37 LOCKED format (rate word @+0x1C, 0x14-byte header @+0x24)
 *     +0x1E(b) numChannels  +0x2F(b) interleaved-flag
 *     +0x20..0x4B CURRENT format (rate @+0x20, header @+0x38)   +0x4C..0x5C priority/params [5 words]
 *   ===== request (0x2C) =====
 *     +0x00 STREAM req id   +0x04 full id (counter|slot)   +0x08 submit-overflow   +0x0C submit handle
 *     +0x10 data rate   +0x14 bytes consumed   +0x18 total size (round-up 0x1C)   +0x1C remaining
 *     +0x20 submitted count   +0x24 num chunks   +0x28(short) name
 */
#include "../../../lib/snd.h"
#include "../../../mips_semantics.h"

/* ---- globals ---- */
extern "C" intptr (&sndss)[1];
extern "C" int sndgs[]; /* SND global state: (char)sndgs[0xf]=init, sndgs[0x22]=destroyall hook */
extern "C" signed char (&sndStreamMap)[4];

/* ---- stream.obj ring (the layer below; already reconstructed) ---- */
extern "C" void STREAM_release(intptr strm, intptr chunk);
extern "C" intptr STREAM_get(intptr consumer, void *buf, int len);
extern "C" int STREAM_gettable(intptr strm);
extern "C" int STREAM_state(intptr strm);
extern "C" int STREAM_buffersize(intptr strm);
extern "C" intptr STREAM_create(int nReq, int nFilt, int nCons, void *objbuf, int bufsize);
extern "C" unsigned int STREAM_queuefile(intptr strm, char *name, int off, int len);
extern "C" unsigned int STREAM_queuemem(intptr strm, intptr blocklist, void *ptr, int len);

/* ---- SNDPKTPLAY packet player (spktplay.obj) ---- */
extern "C" int SNDPKTPLAY_start(int pktplay, intptr rate, intptr fmt, int *params);
extern "C" int SNDPKTPLAY_submit(int pktplay, intptr *desc);
extern "C" int SNDPKTPLAY_submitspace(int pktplay);
extern "C" int SNDPKTPLAY_framesoutstanding(int pktplay);
extern "C" void SNDPKTPLAY_stop(int pktplay);
extern "C" int SNDPKTPLAY_overhead(int arg);
extern "C" int SNDPKTPLAY_create(intptr buf, int size, void (*relcb)(intptr), void (*notifycb)(int, unsigned int));

/* ---- other SND helpers ---- */
extern "C" int iSNDpatchtohdr(short *src, int *rateDst, int *fmtDst, int *outSize); /* spat2hdr */
extern "C" int iSNDplatformcalcdatarate(void *rate);                                /* sdpacket  */
extern "C" void iSNDenteraudio(void);                                               /* sserver   */
extern "C" void iSNDleaveaudio(void);
extern "C" void iSNDserveraddclient(void *cb);             /* ssysserv  */
extern "C" void SNDSTRM_setgreedylevel(int strm, int lvl); /* sstsetgl  */
extern "C" int SNDSTRM_destroy(int s);                     /* spvoices  */
extern "C" void SNDSTRM_purge(int s);
#ifndef _MSC_VER
    #ifndef _MSC_VER
        #ifndef _MSC_VER
extern "C" int memcmp(const void *a, const void *b, int n);
        #endif
    #endif
#endif
#ifndef _MSC_VER
extern "C" void *memcpy(void *d, const void *s, int n);
#endif

/* ---- internal forward decls (mutually recursive) ---- */
extern "C" void iSNDstreamdestroyall(void);                               /* @0x800E8C14 */
extern "C" SndStreamState *iSNDstreamgetstreamptr(int idx);               /* @0x800E8C48 */
extern "C" int iSNDstreamremoverequest(unsigned int reqid);               /* @0x800E8C64 */
extern "C" void iSNDstreamreleasecallback(intptr sample);                 /* @0x800E8D90 */
extern "C" void iSNDstreamnotifycallback(int handle, unsigned int bytes); /* @0x800E8DD4 */
extern "C" int iSNDstreamparseheader(SndStreamState *S, intptr data);     /* @0x800E8E9C */
extern "C" int iSNDstreamparsenumchunks(SndStreamState *S, intptr data);  /* @0x800E9044 */
extern "C" void iSNDstreamparsedata(SndStreamState *S, intptr chunk);     /* @0x800E90AC */
extern "C" int iSNDstreamparseend(SndStreamState *S, intptr chunk);       /* @0x800E9230 */
extern "C" int iSNDstreamparsechunk(SndStreamState *S, intptr chunk);     /* @0x800E9270 */
extern "C" int iSNDstreamisheld(SndStreamState *S);                       /* @0x800E9318 */
extern "C" void iSNDstreamhotroddatachunks(void);                         /* @0x800E9438 */
extern "C" void iSNDstreamservice(void);                                  /* @0x800E9590 */
extern "C" int iSNDstreamnumcreated(void);                                /* @0x800E96F8 */

static SndStreamRequest *stream_request(SndStreamState *stream, int index)
{
    return stream->requests + index;
}

/* ====================================================================================== */

/* iSNDstreamdestroyall @0x800E8C14 : destroy every stream (addexit/shutdown hook). */
extern "C" void iSNDstreamdestroyall(void)
{
    int s = 0;
    do
    {
        SNDSTRM_destroy(s);
        s = s + 1;
    } while (s < 1);
}

/* iSNDstreamgetstreamptr @0x800E8C48 : map a stream index to its object (only index 0 exists). */
extern "C" SndStreamState *iSNDstreamgetstreamptr(int idx)
{
    if (idx == 0)
        return (SndStreamState *)sndss[0];
    return 0;
}

/* iSNDstreamremoverequest @0x800E8C64 : drop the request whose id == `reqid` from a stream's packet
 *   array, compacting the remaining requests down and fixing up parseIdx/curReqCount.  Returns the
 *   (possibly adjusted) parseIdx. */
extern "C" int iSNDstreamremoverequest(unsigned int reqid)
{
    SndStreamState *S = (SndStreamState *)sndss[reqid & 0xff];
    SndStreamRequest *packets = S->requests;
    char newidx = 0; /* write index (compacted) */
    int ret = 0;

    if (S->requestCount > 0)
    {
        int rd = 0, wr = 0, i = 0;
        do
        {
            SndStreamRequest *src = packets + rd;
            if (src->id != reqid)
            {
                if (S->parseIndex == i)
                    S->parseIndex = newidx;
                packets[wr] = *src;
                wr++;
                newidx = newidx + 1;
            }
            rd++;
            i++;
        } while (i < S->requestCount);
    }
    S->requestCount = S->requestCount - 1;
    if (S->requestCount < S->parseIndex)
    {
        ret = S->parseIndex - 1;
        S->parseIndex = (signed char)ret;
    }
    return ret;
}

/* iSNDstreamreleasecallback @0x800E8D90 : SNDPKTPLAY release hook -- a finished sample buffer carries a
 *   back-pointer to its chunk 4 bytes ahead; the chunk's first word holds the request id whose low byte
 *   is the stream slot.  Free the chunk back to that stream's ring. */
extern "C" void iSNDstreamreleasecallback(intptr sample)
{
    /* Retail stores this back-reference in the fixed 32-bit SCxl chunk word
     * immediately before sample data.  It is a serialized PSX boundary, not
     * a native-width field of SndStreamState. */
    intptr chunk = (intptr)(intptr) * (unsigned int *)(sample - 4);
    int slot = *(unsigned char *)chunk;
    SndStreamState *S = (SndStreamState *)sndss[slot];
    STREAM_release(S->streamHandle, chunk);
}

/* iSNDstreamnotifycallback @0x800E8DD4 : SNDPKTPLAY play-progress hook.  `bytes` were just played on
 *   `handle`; credit them to the head request's consumed/remaining counters, and when a request is fully
 *   played out remove it.  Overflow rolls into the next request. */
extern "C" void iSNDstreamnotifycallback(int handle, unsigned int bytes)
{
    SndStreamState *S = (SndStreamState *)sndss[sndStreamMap[handle]];
    do
    {
        SndStreamRequest *req = S->requests;
        unsigned int over = 0;
        if ((unsigned int)req->remaining < bytes)
        {
            over = bytes - req->remaining;
            bytes = bytes - over;
        }
        int byteWord = nfs4_mips_bits_to_s32(bytes);
        req->consumed = nfs4_mips_addu_s32(req->consumed, byteWord);
        req->remaining = nfs4_mips_subu_s32(req->remaining, byteWord);
        if ((unsigned int)req->totalSize <= (unsigned int)req->consumed)
            iSNDstreamremoverequest(req->id);
        bytes = over;
    } while (bytes != 0);
}

/* iSNDstreamparseheader @0x800E8E9C : 'SChl' chunk -- decode the audio header (rate/format) via
 *   iSNDpatchtohdr, compute the data rate, and lock the format on first sight (a mid-stream change errors
 *   to state 2).  Once locked, (re)start the packet player. */
extern "C" int iSNDstreamparseheader(SndStreamState *S, intptr data)
{
    SndStreamRequest *req = stream_request(S, S->parseIndex);
    int outsize;

    iSNDpatchtohdr((short *)(data + 0xc), &S->currentRate, (int *)S->currentHeader, &outsize);
    req->totalSize = outsize;
    STREAM_release(S->streamHandle, data);
    req->totalSize = ((nfs4_mips_addu_s32(req->totalSize, 0x1b)) / 0x1c) * 0x1c;
    req->dataRate = iSNDplatformcalcdatarate(&S->currentRate);

    if (memcmp(&S->lockedRate, &S->currentRate, 4) != 0 || memcmp(S->lockedHeader, S->currentHeader, 0x14) != 0)
    {
        if ((short)S->lockedRate != 0)
        {
            S->state = 2;
            return 0;
        }
        /* lock the current format (asm: lwl/lwr unaligned copies; fields are 4-aligned here) */
        S->lockedRate = S->currentRate;
        memcpy(S->lockedHeader, S->currentHeader, 0x14);
    }
    if (S->state != 1)
    {
        S->playResult = SNDPKTPLAY_start(S->packetPlayer, (intptr)&S->lockedRate, (intptr)S->lockedHeader, S->params);
        S->state = 1;
    }
    return 0;
}

/* iSNDstreamparsenumchunks @0x800E9044 : 'SCCl' chunk -- record the stream's chunk count. */
extern "C" int iSNDstreamparsenumchunks(SndStreamState *S, intptr data)
{
    STREAM_release(S->streamHandle, data);
    SndStreamRequest *req = stream_request(S, S->parseIndex);
    req->numChunks = *(int *)(data + 0xc);
    return 1;
}

/* iSNDstreamparsedata @0x800E90AC : 'SCDl' chunk -- build the per-channel sample descriptor (flat or
 *   interleaved per the format), stamp the chunk with its owning request id (for the release hook), and
 *   submit it to the packet player. */
extern "C" void iSNDstreamparsedata(SndStreamState *S, intptr chunk)
{
    int datalen = *(int *)(chunk + 0xc);
    intptr desc[8];
    int numCh = *((unsigned char *)&S->lockedRate + 2);
    int i;

    /* Retail stores datalen at sp+0x14 and passes sp+0x10 as the frame
     * descriptor, so this is descriptor word +0x04.  The decompiler split
     * those overlapping stack views into unrelated C locals. */
    desc[1] = datalen;

    if (S->lockedHeader[0xb] == 0)
    { /* flat: every channel reads chunk+0x10 */
        for (i = 0; i < numCh; i++)
            desc[3 + i] = chunk + 0x10;
    }
    else
    { /* interleaved: per-channel offset table */
        int *off = (int *)(chunk + 0x10);
        for (i = 0; i < numCh; i++)
            desc[3 + i] = (chunk + 0x10) + off[i] + numCh * 4;
    }

    {
        int rounded = (nfs4_mips_addu_s32(datalen, 0x1b) / 0x1c) * 0x1c;
        SndStreamRequest *req = stream_request(S, S->parseIndex);
        *(unsigned int *)(desc[3] - 4) = (unsigned int)(intptr)chunk;
        *(unsigned int *)chunk = req->id;
        req->remaining = req->remaining + rounded;
        req->submitted = req->submitted + 1;
        req->submitHandle = SNDPKTPLAY_submit(S->packetPlayer, desc);
        if (req->submitOverflow < 0)
            req->submitOverflow = req->submitHandle;
    }
}

/* iSNDstreamparseend @0x800E9230 : 'SCEl' chunk -- end of one queued sound; advance parseIdx. */
extern "C" int iSNDstreamparseend(SndStreamState *S, intptr chunk)
{
    STREAM_release(S->streamHandle, chunk);
    S->parseIndex = S->parseIndex + 1;
    return 1;
}

/* iSNDstreamparsechunk @0x800E9270 : dispatch a chunk by its tag. */
extern "C" int iSNDstreamparsechunk(SndStreamState *S, intptr chunk)
{
    int tag = *(int *)chunk;
    int ret = 1;
    if (tag == 0x6c444353)
    { /* 'SCDl' */
        iSNDstreamparsedata(S, chunk);
    }
    else if (tag == 0x6c484353)
    { /* 'SChl' */
        ret = iSNDstreamparseheader(S, chunk);
    }
    else if (tag == 0x6c454353)
    { /* 'SCEl' */
        ret = iSNDstreamparseend(S, chunk);
    }
    else if (tag == 0x6c434353)
    { /* 'SCCl' */
        ret = iSNDstreamparsenumchunks(S, chunk);
    }
    else
    {
        STREAM_release(S->streamHandle, chunk); /* unknown -> drop */
    }
    return ret;
}

/* iSNDstreamisheld @0x800E9318 : true if the stream should hold (not feed more) because the ring buffer
 *   has run low relative to the data rate -- prevents starving the player on a slow disc. */
extern "C" int iSNDstreamisheld(SndStreamState *S)
{
    SndStreamRequest *req = stream_request(S, S->parseIndex);
    int held = 0;

    if (req->dataRate != 0 && (held = 1, req->name >= 0) && (held = 0, req->name != 0))
    {
        unsigned int avail = STREAM_gettable(S->streamHandle);
        if (4000000 < avail)
            avail = 4000000;
        if ((avail * 1000) / (unsigned int)req->dataRate < (unsigned int)(int)req->name && (held = STREAM_state(S->streamHandle), held != 2))
            return 1;
        req->name = 0;
        held = 0;
    }
    return held;
}

/* iSNDstreamhotroddatachunks @0x800E9438 : opportunistically pull and submit pending data chunks (up to
 *   ~0x4000 bytes total) for any playing, non-held stream that has player space -- keeps the buffer fed
 *   ahead of demand. */
extern "C" void iSNDstreamhotroddatachunks(void)
{
    int total = 0;
    int slot = 0;
    intptr *p = sndss;
    do
    {
        SndStreamState *S = (SndStreamState *)*p;
        if (S != 0 && S->requestCount != 0 && S->state == 1 && iSNDstreamisheld(S) == 0)
        {
            SndStreamRequest *req = stream_request(S, S->parseIndex);
            if (req->numChunks != 0 && req->submitted != 0)
            {
                int avail = req->numChunks - req->submitted;
                int space = SNDPKTPLAY_submitspace(S->packetPlayer);
                int n = (avail < space) ? avail : space;
                if (0 < n)
                {
                    do
                    {
                        n--;
                        intptr chunk = STREAM_get(S->streamHandle, 0, 0);
                        if (chunk != 0)
                        {
                            total += *(int *)(chunk + 4);
                            iSNDstreamparsedata(S, chunk);
                        }
                    } while (0 < n && total < 0x4000);
                }
            }
        }
        slot++;
        p++;
    } while (slot < 1);
}

/* iSNDstreamservice @0x800E9590 : per-tick service.  For each active stream: restart the player if it
 *   flagged a format change (state 2), then, unless held, drain chunks from the ring through
 *   iSNDstreamparsechunk into the player. */
extern "C" void iSNDstreamservice(void)
{
    int slot = 0;
    intptr *p = sndss;
    iSNDenteraudio();
    do
    {
        SndStreamState *S = (SndStreamState *)*p;
        if (S != 0 && S->requestCount != 0)
        {
            if (S->state == 2)
            {
                if (0 < SNDPKTPLAY_framesoutstanding(S->packetPlayer))
                    goto next;
                S->lockedRate = S->currentRate;
                SNDPKTPLAY_stop(S->packetPlayer);
                S->playResult = SNDPKTPLAY_start(S->packetPlayer, (intptr)&S->lockedRate, (intptr)S->lockedHeader, S->params);
                S->state = 1;
            }
            if (iSNDstreamisheld(S) == 0)
            {
                int n, r = 0;
                if (S->state == 1)
                {
                    n = SNDPKTPLAY_submitspace(S->packetPlayer);
                    if (n == 0)
                        goto next;
                }
                else
                {
                    n = 10;
                }
                do
                {
                    n--;
                    intptr chunk = STREAM_get(S->streamHandle, 0, 0);
                    if (chunk != 0)
                        r = iSNDstreamparsechunk(S, chunk);
                    if (r == 0)
                        break;
                } while (0 < n);
            }
        }
    next:
        slot++;
        p++;
    } while (slot < 1);
    iSNDleaveaudio();
}

/* iSNDstreamnumcreated @0x800E96F8 : count the live streams. */
extern "C" int iSNDstreamnumcreated(void)
{
    int count = 0;
    int slot = 0;
    intptr *p = sndss;
    do
    {
        if (*p != 0)
            count++;
        slot++;
        p++;
    } while (slot < 1);
    return count;
}

/* iSNDstreamcreate @0x800E9730 : carve a stream object + its packet array, packet player and (optionally)
 *   its own ring out of `objbuf`/`memsize`, wire up the priority params, and register it.  Returns the
 *   stream slot, or a negative error.  `extFlag` reuses an external STREAM (extHandle) instead of creating
 *   one. */
extern "C" int iSNDstreamcreate(int *priority, int numReq, int pktArg, intptr objbuf, int memsize, int extHandle, int extFlag)
{
    SndStreamState *S;
    unsigned char *alloc;
    int memrem, reqBytes, oh, pktplay;
    intptr pktbuf;
    int slot = 0;

    if ((char)sndgs[0xf] == 0) /* SND not initialised */
        return -10;
    if (sndss[0] != 0) /* no free slot */
        return -9;

    S = (SndStreamState *)objbuf;
    alloc = (unsigned char *)(S + 1);
    memrem = memsize - (int)sizeof(*S);
    reqBytes = numReq * (int)sizeof(SndStreamRequest);
    S->requests = (SndStreamRequest *)alloc;
    alloc += reqBytes;
    memrem -= reqBytes;

    oh = SNDPKTPLAY_overhead(pktArg);
    pktbuf = (intptr)alloc;
    alloc += oh;
    memrem -= oh;
    oh = SNDPKTPLAY_overhead(pktArg);
    pktplay = SNDPKTPLAY_create(pktbuf, oh, iSNDstreamreleasecallback, iSNDstreamnotifycallback);
    S->packetPlayer = pktplay;
    if (pktplay < 0)
        return pktplay;
    sndStreamMap[pktplay] = (signed char)slot; /* handle -> slot (asm: delay slot, always) */

    if (extFlag != 0)
    { /* external ring */
        S->streamHandle = extHandle;
        S->external = 1;
    }
    else
    { /* own ring */
        S->streamHandle = STREAM_create(numReq + 1, 1, 1, alloc, memrem);
        S->external = 0;
        SNDSTRM_setgreedylevel((int)(intptr)S->streamHandle, STREAM_buffersize(S->streamHandle) / 3);
    }
    S->requestCounter = 0;
    S->playResult = -1;
    S->maxRequests = (signed char)numReq;
    S->params[0] = priority[0];
    S->params[1] = priority[1];
    S->params[2] = priority[2];
    S->params[3] = priority[3];
    S->params[4] = priority[4];
    if (iSNDstreamnumcreated() == 0)
    { /* first stream -> register the service hook */
        iSNDserveraddclient((void *)iSNDstreamservice);
        sndgs[0x22] = (int)iSNDstreamdestroyall;
    }
    sndss[slot] = (intptr)S;
    SNDSTRM_purge(slot);
    return slot;
}

/* iSNDstreamqueue @0x800E9970 : queue a sound on a stream -- from a file, a memory image, or an
 *   already-built STREAM request id.  Fills a fresh packet slot, stamps a unique id, and returns it.
 *   `mode`: 0=file (filename/off), 1=memory (filename=block), other=pre-built id (off). */
extern "C" int iSNDstreamqueue(unsigned int s, int name, char *filename, int off, int mode)
{
    SndStreamState *p;
    SndStreamRequest *req;
    int ret;

    if ((char)sndgs[0xf] == 0)
        return -10;
    p = iSNDstreamgetstreamptr(s);
    if (p == 0)
        return -8;

    iSNDenteraudio();
    if (p->requestCount < p->maxRequests)
    {
        req = stream_request(p, p->requestCount);
        if (mode == 0)
            req->streamRequest = STREAM_queuefile(p->streamHandle, filename, off, 0x6c454353);
        else if (mode == 1)
            req->streamRequest = STREAM_queuemem(p->streamHandle, (intptr)filename, 0, 0x6c454353);
        else
            req->streamRequest = off;

        if (req->streamRequest == 0)
        {
            iSNDleaveaudio();
            ret = -1;
        }
        else
        {
            p->requestCounter = nfs4_mips_addu_s32(p->requestCounter, 0x100);
            if (p->requestCounter < 0)
                p->requestCounter = 0;
            req->id = p->requestCounter | (int)s;
            req->name = (short)name;
            p->requestCount = p->requestCount + 1;
            req->dataRate = 0;
            req->submitOverflow = -1;
            req->submitHandle = -1;
            req->consumed = 0;
            req->remaining = 0;
            req->submitted = 0;
            req->numChunks = 0;
            iSNDleaveaudio();
            ret = req->id;
        }
    }
    else
    {
        iSNDleaveaudio();
        ret = -0xd;
    }
    return ret;
}
