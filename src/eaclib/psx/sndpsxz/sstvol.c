#include "../../../lib/snd.h"

/* eaclib/psx/sndpsxz/sstvol.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstvol.obj @0x800EA0D8 */
extern "C" int sndgs[];
extern "C" SndStreamState *iSNDstreamgetstreamptr(int tag); /* sst */
extern "C" int SNDvol(unsigned int tag, int vol);           /* svol */
extern "C" int SNDSTRM_vol(int tag, int vol);               /* @0x800EA0D8 */

/* SNDSTRM_vol : set a stream's volume (cached at +0x54) and apply it. */
extern "C" int SNDSTRM_vol(int tag, int vol)
{
    SndStreamState *sp;
    if ((char)sndgs[0xf] == 0)
        return -10;
    sp = iSNDstreamgetstreamptr(tag);
    if (sp == 0)
        return -8;
    ((signed char *)sp->params)[8] = (signed char)vol; /* retail byte @stream+0x54 */
    SNDvol((unsigned int)sp->playResult, vol);
    return 0;
}
