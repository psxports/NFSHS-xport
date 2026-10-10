#include "psx.h"
#include <string.h>

/* Game diagnostic snapshots read the shared GTE without owning state */
extern "C" void NFSHS_GTE_DebugState(int *h, int *x, int *y)
{
    PsxGteSnapshot state;
    psx_gte_snapshot(&state);
    if (h) *h = state.h;
    if (x) *x = state.ofx;
    if (y) *y = state.ofy;
}
extern "C" void NFSHS_GTE_DebugTransform(void *matrix, void *translation)
{
    PsxGteSnapshot state;
    psx_gte_snapshot(&state);
    if (matrix) memcpy(matrix, &state.rotation, 20);
    if (translation) memcpy(translation, state.translation, 12);
}

/* tScreen::fSuppressLoadingText single global (was per-TU `static int` in a header). */
int _7tScreen_fSuppressLoadingText;
