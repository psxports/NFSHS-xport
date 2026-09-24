/* frontend/common/textpsx.c -- RECONSTRUCTED (NFS4 PSX text-draw hooks; C TU)
 *   3 free fns: fortext4 (text-blit callback; empty stub w/ 8 params), inittextdraw
 *   (installs fortext4 into the active-font fn-ptr slot), restoretextdraw (clears a
 *   font working-state word). Both use currentfont+0x94 in retail MIPS.
 */
#include "../../nfs4_types.h"
#include "textpsx_externs.h"

/* ---- fortext4  [TEXTPSX.C:153-179] SLD-VERIFIED ---- */
void fortext4(int x, int y, void *source, int u, int v, int width, int height, int rowbytes)

{
    return;
}

/* ---- inittextdraw  [TEXTPSX.C:254-270] SLD-VERIFIED ---- */
extern "C" void inittextdraw(void)

{
    currentfont.textDraw = fortext4;
    return;
}

/* ---- restoretextdraw  [TEXTPSX.C:280-289] SLD-VERIFIED ---- */
void restoretextdraw(void)

{
    currentfont.textDraw = (FontTextDraw)0;
    return;
}

/* end of textpsx.c */
