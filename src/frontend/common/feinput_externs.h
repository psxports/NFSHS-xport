/* frontend/common/feinput_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_FEINPUT_EXTERNS_H_
#define _FE_SCREENS_FEINPUT_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ===== globals ===== */
extern "C" tPadModuleState gPadinfo;
extern "C" extern tfrontEnd frontEnd;
extern "C" int ticks;
extern "C" int FeTools_gScrollTicksOut;  /* @0x800517d0 */
extern "C" int debounce[];               /* @0x80052b60 */
extern "C" long nextTick;                /* @0x80051738 */
extern tPSXToFEMapping getKeyMappings[]; /* @0x8005173c */

/* ===== input helpers ===== */
extern "C"
{
    void Front_ResetPSXController(int controller, int mode);
}

/* same-TU fns (forward decls so callers earlier in the file resolve) */
void FEInput_VerifyControllerValues(int controller);
int FEInput_GetNoDebounceKey(int key, int controller);
int FEInput_GetDebounceKey(int key, int controller);

#endif
