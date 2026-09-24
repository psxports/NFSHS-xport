#include "../../../lib/snd.h"

/* eaclib/psx/sndpsxz/sststat.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sststat.obj @0x800E86D8 */
extern "C" int sndgs[];
extern "C" SndStreamState *iSNDstreamgetstreamptr(int tag);    /* sst      */
extern "C" int SNDPKTPLAY_unsafeframesoutstanding(int player); /* spktplay */
extern "C" void iSNDenteraudio(void);                          /* sserver  */
extern "C" void iSNDleaveaudio(void);
extern "C" void trap(unsigned int code);
extern "C" int SNDSTRM_status(int tag, SNDSTREAMSTATUS *status); /* @0x800E86D8 */

/* SNDSTRM_status : fill the 3-int status block `s` (active, bytes, permille) for stream `tag`. */
extern "C" int SNDSTRM_status(int tag, SNDSTREAMSTATUS *status)
{
    SndStreamState *sp;
    unsigned int rate;
    status->timebuffered = 0;
    status->currentrequest = 0;
    status->outstandingrequests = 0;
    if ((char)sndgs[0xf] == 0)
        return -10;
    sp = iSNDstreamgetstreamptr(tag);
    if (sp == 0)
        return -8;
    iSNDenteraudio();
    status->outstandingrequests = sp->requestCount;
    if (sp->requestCount != 0)
    {
        status->currentrequest = sp->requests[0].id;
        rate = (unsigned int)(unsigned short)sp->lockedRate;
        if (rate != 0)
        {
            unsigned int frames = (unsigned int)SNDPKTPLAY_unsafeframesoutstanding(sp->packetPlayer);
            if ((unsigned short)sp->lockedRate == 0)
                trap(0x1c00);
            status->timebuffered = (frames * 1000) / rate;
        }
    }
    iSNDleaveaudio();
    return 0;
}
