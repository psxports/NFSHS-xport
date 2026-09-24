/* game/common/aiphysic_externs.h - reconstructed externs. NOT original.
 * Harvested from sibling *_externs.h + *.cpp defs + disasm-v2 (AI/Control demangled). */
#ifndef _GAME_COMMON_CAMERA_EXTERNS_H_
#define _GAME_COMMON_CAMERA_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

extern "C"
{
    CARDINFO_def *MCRD_getcard(...);
}
extern AIDataRecord_TrackCurve_t AIDataRecord_TrackCurve[];
extern AIScript_tReactionDetails AIPerson_ScriptData[];
extern Car_tObj *Cars_gHumanRaceCarList[9]; /* cars.obj */
extern "C" extern GameSetup_tData GameSetup_gData;
extern "C" Sim_tSimGlobalVar simGlobal; /* Sim.obj   (.gameTicks) */
extern Trk_NewSlice *BWorldSm_slices;
extern int AIInit_forceHumanHandBrake;
extern int gNumSlices;
extern "C" extern int Cars_gNumHumanRaceCars;
extern int AIWorld_IsDriveableLane(int slice, int lane);
extern int Cars_topSpeedCap[22]; /* [carType] */
extern int AIScript_DoReAction(AIScript_t *script, AIScript_tAIReaction testReaction);
extern int AISpeeds_GetUpgradeBrakeMult(int carIndex);
extern int AISpeeds_SuperDuperSpeedUpTheCarsAtTheStartBecauseWeCannotActuallyHandleRenderingTheseCars(Car_tObj *carObj);
extern int AITune_BTCPerpAccMults[];
extern int AIWorld_CalcFutureLateralVel(Car_tObj *carObj, int slicesAhead);
extern int AIWorld_CalcLateralVelocity(Car_tObj *carObj);
extern int AIWorld_CalcRoadBend(Car_tObj *carObj, int lookAhead);
extern int AIWorld_CalculateDeltaRoadYaw(Car_tObj *carObj);
extern int AIWorld_LaneIndex(int slice, int position);
extern u_int fastRandom, randSeed, randtemp; /* fastrand.obj PRNG state */
extern void Cars_DoGravityEffectsOnAcc(Car_tObj *car, int n);
extern void AIWorld_CalcSpeed(Car_tObj *carObj);
extern void Cars_ResetCollidedCars(Car_tObj *carObj, int forceReset, int forceParkAtSide);
extern void Math_QDNormalizeVector(coorddef *v);
extern void Newton_CopyRoadMatrixToOrientMat(BO_tNewtonObj *n, int backwards);
/* AIDataRecord_AccTable_t::Get / AIDataRecord_TrackCurve_t::Get now called as C++ members (aidatarecord.obj) -- flat externs removed */
extern "C"
{
    int Sched_ExecuteCheck(int a, int b, int c, int d, int *e, int *f, int *g, int h);
}
void __builtin_delete(void *deleteMe);
void *__builtin_new(unsigned int size);

#endif /* _GAME_COMMON_CAMERA_EXTERNS_H_ */
