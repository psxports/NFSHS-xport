#include <stdlib.h>
#include "psx.h"
#include "psx_gpu.h"

// CdControlB binding operands from the original 800F7B24 entry
extern "C" const uint32 xport_cd_sync_callback_address = 0x8013BF48u;
extern "C" const uint32 xport_cd_ready_callback_address = 0x8013BF4Cu;
extern "C" const uint32 xport_cd_status_address = 0x8013BF54u;
extern "C" const uint32 xport_cd_setloc_table_address = 0x80136A18u;

// ResetGraph stores the hardware graph type in GEnv's first byte
extern "C" const uint32 xport_gpu_graph_type_address = 0x8012369Cu;

extern "C" void NFSHS_ConfigurePsyQHost(void)
{
    gpu_set_frame_skip(0);
    if (!psx_pc_set_root("DATA", 1))
        abort();
    srandPSX(1u);
    SsInit();
}
