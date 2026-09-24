/* game/common/aiperson_externs.h - reconstructed externs. NOT original.
 * Harvested from sibling *_externs.h + *.cpp defs + disasm-v2 (AI/Control demangled). */
#ifndef _GAME_COMMON_CAMERA_EXTERNS_H_
#define _GAME_COMMON_CAMERA_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern Car_tObj *Cars_gHumanRaceCarList[9]; /* cars.obj */
extern Car_tObj *Cars_gList[];
extern "C" extern GameSetup_tData GameSetup_gData;
extern Udff_tInfo *Udff_Opena(char *name, char *mem, int abortFlag);
extern "C" char GameSetup_gPersonalityNames[15][8];
extern int Cars_gNumCopCars;
extern int Cars_gNumCars;
extern "C" extern int Cars_gNumHumanRaceCars;
extern int Cars_gNumAIRaceCars;
extern int Udff_GetInt(Udff_tInfo *handle);
extern void AIScript_Assign(AIScript_t *aiscriptt, AIScript_tReactionDetails (*arg2)[7]);
extern void Udff_Close(Udff_tInfo *handle);
extern void Udff_GetBuffer(Udff_tInfo *handle, char *mem, int size);
extern "C" char *Paths_Paths[]; /* 0x80116468 (paths.obj); [2] = path prefix at +8 */

#endif /* _GAME_COMMON_CAMERA_EXTERNS_H_ */
