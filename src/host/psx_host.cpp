#include <stdlib.h>
#include "psx.h"

extern "C" void NFSHS_ConfigurePsyQHost(void)
{
    SsInit();
#if !defined(__EMSCRIPTEN__)
    atexit(SsEnd);
#endif
}
