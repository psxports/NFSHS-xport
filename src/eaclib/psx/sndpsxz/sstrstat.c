#include "../../../lib/snd.h"

/* eaclib/psx/sndpsxz/sstrstat.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstrstat.obj @0x800E87D0 */
extern "C" int sndgs[];
extern "C" SndStreamState *iSNDstreamgetstreamptr(int tag);             /* sst      */
extern "C" SndStreamRequest *iSNDstreamgetrequestptr(unsigned int tag); /* sstgetrp */
extern "C" void iSNDmulu64(int *out, unsigned int a, unsigned int b);   /* smath64 */
extern "C" int iSNDdivu64(int lo, int hi, unsigned int div);            /* smath64 */
extern "C" void iSNDenteraudio(void);                                   /* sserver */
extern "C" void iSNDleaveaudio(void);
extern "C" void trap(unsigned int code);
extern "C" int SNDSTRM_requeststatus(unsigned int reqTag, SNDREQUESTSTATUS *status); /* @0x800E87D0 */

/* SNDSTRM_requeststatus : fill the 4-int request-status block `s` (state, played, remaining, permille). */
extern "C" int SNDSTRM_requeststatus(unsigned int reqTag, SNDREQUESTSTATUS *status)
{
    SndStreamState *sp;
    SndStreamRequest *rp;
    unsigned int div;
    int q[2];
    status->state = 0;
    status->currenttime = 0;
    status->timetoend = 0;
    status->timebuffered = 0;
    if ((char)sndgs[0xf] == 0)
        return -10;
    if (-1 >= (int)reqTag)
        return -8;
    sp = iSNDstreamgetstreamptr((int)(reqTag & 0xff));
    if (sp == 0)
        return -8;
    iSNDenteraudio();
    rp = iSNDstreamgetrequestptr(reqTag);
    if (rp == 0)
    {
        status->state = 3;
    }
    else if (rp->submitOverflow < 0)
    {
        status->state = 0;
    }
    else
    {
        unsigned short u;
        if (sp->requests == rp)
        {
            status->state = 2;
            u = (unsigned short)sp->lockedRate;
        }
        else
        {
            status->state = 1;
            u = (unsigned short)sp->currentRate;
        }
        div = (unsigned int)u;
        iSNDmulu64(q, (unsigned int)rp->consumed, 1000);
        status->currenttime = iSNDdivu64(q[0], q[1], div);
        iSNDmulu64(q, (unsigned int)(rp->totalSize - rp->consumed), 1000);
        status->timetoend = iSNDdivu64(q[0], q[1], div);
        if (div == 0)
            trap(0x1c00);
        status->timebuffered = ((unsigned int)rp->remaining * 1000U) / div;
    }
    iSNDleaveaudio();
    return 0;
}
