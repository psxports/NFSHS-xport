/* frontend/psx/mmeffect.cpp  --  RECONSTRUCTED  (PSX main-menu effect; C++ TU)
 *   Body: Ghidra decompiler. Line numbers: PsyQ SLD (8c-start, 8e-end).
 *   1 function; C++ linkage (cfront-mangled in SYM: FeDraw_SetABRMode__Fi). VA 0x8004d6d8.
 *   SYM locals: abr (REGPARM int) + dr_mode (REG DR_MODE*). 18 callers.
 *   Externs declared in mmeffect_externs.h (libgpu GetTPage/SetDrawMode + render cursors).
 */
#include "mmeffect.h"
#include "mmeffect_externs.h"

/* lines 1-232: file header, #includes, static data, macros (no symbols emitted) */

/* ---- FeDraw_SetABRMode  (mmeffect.cpp:233, code lines 233-237) ---- */
void FeDraw_SetABRMode(int abr)

{
  short tpage;
  DR_MODE *dr_mode;

  dr_mode = (DR_MODE *)Render_gPacketPtr;
  AddPrim(Render_gPalettePtr,dr_mode);
  Render_gPacketPtr = Render_gPacketPtr + 0xc;
  tpage = GetTPage(2,abr,0,0x100);
  SetDrawMode(dr_mode,0,0,(uint32)(u_short)tpage,(PSX_RECT *)0x0);
  return;
}

/* end of mmeffect.cpp */
