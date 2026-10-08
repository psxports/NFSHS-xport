#include "../../../lib/snd.h"

/* eaclib/psx/sndpsxz/sstgetv.c -- RECONSTRUCTED. NOT original.  *** 1/1 ***  obj sstgetv.obj @0x800E83EC */
extern "C" int sndgs[];
extern "C" SndStreamState *iSNDstreamgetstreamptr(int tag); /* sst */
extern "C" int SNDgetvol(unsigned int tag);                 /* sgetvol */
extern "C" int SNDSTRM_getvol(int tag);                     /* @0x800E83EC */

/* Query the stream volume, preserving the original MIPS error and fallback paths */
extern "C" int SNDSTRM_getvol(int tag)
{
    if ((signed char)sndgs[0xf] == 0)
        return -10;
    SndStreamState *sp = iSNDstreamgetstreamptr(tag);
    if (sp == 0)
        return -8;
    int volume = SNDgetvol((unsigned int)sp->playResult);
    /* MIPS lb at +0x54 reads the signed low byte of params[2] */
    return volume < 0 ? (signed char)(sp->params[2] & 0xff) : volume;
}
