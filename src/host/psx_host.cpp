#include <stdlib.h>
#include "psx.h"

extern "C" void NFSHS_ConfigurePsyQHost(void)
{
    SsInit();
    atexit(SsEnd);
}
