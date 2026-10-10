#include "psx.h"

/* Observation-only access to the shared BIOS random state */
extern "C" unsigned int NFSHS_HostPSXRandSeed(void)
{
    return r_u32(0xA0009010u);
}
