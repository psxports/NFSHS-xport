/* eaclib/psx/sndpsxz/spvoices.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 4/4 ***
 *   Source obj : nfs4\eaclib\psx\spvoices.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   4 fns @[0x800E9B44 .. 0x800E9C58].  The PUBLIC SNDSTRM_* streaming-voice API -- a thin wrapper over
 *   the sst.obj internals (iSNDstream*).  Dual-source: Ghidra nfs4-f.exe.c L146576..146684 + disasm-v3
 *   L300275+ (for the dropped forwarder args).
 */
#include "../../../lib/snd.h"

/* ---- sst.obj internals (the layer below) + stream/pktplay/ssysserv backends ---- */
extern "C" int iSNDstreamcreate(int *priority, int numReq, int pktArg, intptr objbuf, int memsize, int extHandle, int extFlag); /* @0x800E9730 */
extern "C" SndStreamState *iSNDstreamgetstreamptr(int idx);                                                                     /* @0x800E8C48 */
extern "C" int iSNDstreamnumcreated(void);                                                                                      /* @0x800E96F8 */
extern "C" int iSNDstreamqueue(unsigned int s, int name, char *filename, int off, int mode);                                    /* @0x800E9970 */
extern "C" void iSNDstreamservice(void);                                                                                        /* @0x800E9590 (serve hook) */
extern "C" void SNDPKTPLAY_destroy(int pktplay);                                                                                /* spktplay */
extern "C" void SNDPKTPLAY_stop(int pktplay);
extern "C" void STREAM_destroy(intptr strm); /* stream.obj */
extern "C" void STREAM_kill(intptr strm);
extern "C" void iSNDserverremoveclient(void *cb); /* ssysserv */
#ifndef _MSC_VER
extern "C" void *memset(void *d, int c, int n);
#endif

extern "C" intptr (&sndss)[1];
extern "C" int sndgs[]; /* (char)sndgs[0xf] = init flag, sndgs[0x22] = destroyall hook */

extern "C" void SNDSTRM_purge(int s); /* @0x800E9C58 (fwd: destroy calls it) */

/* SNDSTRM_create @0x800E9B44 : create a streaming voice with its OWN ring (extHandle/extFlag forced 0).
 *   Returns the stream slot or a negative error. */
extern "C" int SNDSTRM_create(int *priority, int numReq, int pktArg, void *objbuf, int memsize)
{
    return iSNDstreamcreate(priority, numReq, pktArg, (intptr)objbuf, memsize, 0, 0);
}

/* SNDSTRM_destroy @0x800E9B70 : purge and tear down a streaming voice; when the last one goes, unhook the
 *   audio-server service callback.  Frees the packet player and (if owned) the ring. */
extern "C" int SNDSTRM_destroy(int s)
{
    SndStreamState *S;
    if ((char)sndgs[0xf] == 0)
        return -10;
    S = iSNDstreamgetstreamptr(s);
    if (S == 0)
        return -8;

    SNDSTRM_purge(s);
    if (iSNDstreamnumcreated() == 1)
    { /* this is the last live stream */
        iSNDserverremoveclient((void *)iSNDstreamservice);
        sndgs[0x22] = 0;
    }
    SNDPKTPLAY_destroy(S->packetPlayer);
    if (S->external == 0)
        STREAM_destroy(S->streamHandle);
    sndss[s] = 0;
    return 0;
}

/* SNDSTRM_queuefile @0x800E9C38 : queue a sound from a file (mode 0). */
extern "C" int SNDSTRM_queuefile(int s, int name, char *filename, long off)
{
    return iSNDstreamqueue(s, name, filename, off, 0);
}

/* SNDSTRM_purge @0x800E9C58 : stop playback, flush the ring, and reset the voice to an empty idle state
 *   (counters, parse index, and both format slots cleared) -- ready to be re-queued. */
extern "C" void SNDSTRM_purge(int s)
{
    SndStreamState *S;
    if ((char)sndgs[0xf] != 0 && (S = iSNDstreamgetstreamptr(s)) != 0)
    {
        if (-1 < S->playResult)
            SNDPKTPLAY_stop(S->packetPlayer);
        S->playResult = -1;
        if (S->external == 0)
            STREAM_kill(S->streamHandle);
        S->requestCount = 0;
        S->parseIndex = 0;
        S->state = 0;
        S->lockedRate = 0;
        S->currentRate = 0;
        memset(S->lockedHeader, 0, sizeof(S->lockedHeader));
        memset(S->currentHeader, 0, sizeof(S->currentHeader));
    }
}
