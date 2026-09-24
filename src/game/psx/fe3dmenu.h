/* game/psx/fe3dmenu.h — reconstructed from game/psx/fe3dmenu.cpp (3 fns) */
#ifndef _GAME_PSX_FE3DMENU_H_
#define _GAME_PSX_FE3DMENU_H_
#include "../../nfs4_types.h"

// FRONT.BIN 8003AB2C/8003AB48: camY/camZ each occupy one 32-bit slot.
// An ellipsis here incorrectly promotes float to double on the host ABI.
void Draw_MenuRenderingView(Car_tObj *carObj, DRender_tView *Vi, int posX, int posY, int player, u_long rotation, int camRot, float camY, float camZ, int light, int reflection);

void Fe3D_InitShowroom__Fv(void);                                                                                                                                                                                        /* :76 */
void CameraLookAt__FP10matrixtdefP8coorddef(matrixtdef *mat, coorddef *camPoint);                                                                                                                                        /* :120 */
void Draw_MenuRenderingView__FP8Car_tObjP13DRender_tViewiiiUliffii(Car_tObj *carObj, DRender_tView *Vi, int posX, int posY, int player, u_long rotation, int camRot, float camY, float camZ, int light, int reflection); /* :150 */

#endif /* _GAME_PSX_FE3DMENU_H_ */
