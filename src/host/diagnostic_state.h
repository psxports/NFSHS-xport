#ifndef FF_DIAGNOSTIC_STATE_H
#define FF_DIAGNOSTIC_STATE_H
#include <stdio.h>
#include "psx.h"

/* Same-build native diagnostic checkpoints, never original-game save states.
 * Each block is sized; the runner also pins EXE and checkpoint SHA256. */
static __inline int ff_state_block(FILE *f, void *data, size_t size, int load)
{
    uint32 stored = (uint32)size;
    if (load)
        return fread(&stored, 4, 1, f) == 1 && stored == size && fread(data, 1, size, f) == size;
    return fwrite(&stored, 4, 1, f) == 1 && fwrite(data, 1, size, f) == size;
}

#define FF_STATE(f, v, load) ff_state_block((f), &(v), sizeof(v), (load))
int ff_gpu_state_io(FILE *f, int load);
int ff_audio_state_io(FILE *f, int load);
int psx_state_io(FILE *f, int load);
int spu_state_io(FILE *file, int load);
#endif
