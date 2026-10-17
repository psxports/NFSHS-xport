#ifndef NFSHS_SPCHSAMP_H
#define NFSHS_SPCHSAMP_H

#include "psx.h"

extern "C" {
void iSPCH_InitSample(int *out);
int iSPCH_UnPackSample(intptr bank, unsigned int sampleIdx, int *out);
}

#endif
