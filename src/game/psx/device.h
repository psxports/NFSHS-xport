/* game/psx/device.h — reconstructed from game/psx/device.cpp (10 fns) */
#ifndef _GAME_PSX_DEVICE_H_
#define _GAME_PSX_DEVICE_H_
#include "../../nfs4_types.h"

int Device_VerifyType__Fi(int port);               /* :51 */
int Device_Fail__Fi(int port);                     /* :72 */
void Device_Update__Fv(void);                      /* :109 */
void Device_StartUp__Fv(void);                     /* :169 */
void Device_SetHardCodedKeys__Fv(void);            /* :195 */
int Device_PSXPad__FUl(uint32 param);              /* :244 */
BOOL Device_ReadPad__FiUl(int port, uint32 param); /* :261 */
int Device_PSXPadMulti__FUl(uint32 param);         /* :306 */
int Device_Analog__FUl(uint32 param);              /* :352 */
int Device_Null__FUl(uint32 param);                /* :393 */

#endif /* _GAME_PSX_DEVICE_H_ */
