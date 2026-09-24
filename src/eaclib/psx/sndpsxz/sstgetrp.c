#include "../../../lib/snd.h"

/* eaclib/psx/sndpsxz/sstgetrp.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstgetrp.obj @0x80103508 */
extern "C" SndStreamState *iSNDstreamgetstreamptr(int tag); /* sst */

extern "C" SndStreamRequest *iSNDstreamgetrequestptr(unsigned int idx); /* @0x80103508 */

/* iSNDstreamgetrequestptr @0x80103508 : resolve a stream-request tag to its request struct -- find the
 *   stream (idx low byte), then scan its request array (0x2c stride, +4 == tag) for a match.  Returns the
 *   request ptr, or 0. */
extern "C" SndStreamRequest *iSNDstreamgetrequestptr(unsigned int idx)
{
    SndStreamState *sp;
    SndStreamRequest *rq;
    int i;
    if (-1 >= (int)idx)
        return 0;
    sp = iSNDstreamgetstreamptr((int)(idx & 0xff));
    if (sp == 0)
        return 0;
    i = 0;
    if (sp->requestCount > 0)
    {
        rq = sp->requests;
        do
        {
            if (rq->id == idx)
                return rq;
            rq++;
            i++;
        } while (i < sp->requestCount);
    }
    return 0;
}
