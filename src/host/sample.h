#ifndef AUDIO_SAMPLE_H
#define AUDIO_SAMPLE_H

#include "psx.h"

/* Shared host PCM saturation. Former helpers: ima_adpcm.c:clamp_sample and
 * psx_spu.c:audio_sample_clamp. No separate original MIPS function entry. */
static inline sint16 audio_sample_clamp(sint32 value)
{
    if (value < -32768)
        return -32768;
    if (value > 32767)
        return 32767;
    return (sint16)value;
}

#endif
