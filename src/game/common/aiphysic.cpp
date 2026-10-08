/* game/common/aiphysic.cpp -- RECONSTRUCTED (NFS4 AI action/reaction scripting; 8 free AIScript_* fns).
 *   Player-action submission + reaction-table processing. SYM-v3 locals; vs disasm-v2.txt.
 *   NOT original source; SYM-faithful, recompilable C++.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "aiphysic_externs.h"


/* ---- aiphysic.obj-owned globals (.bss zero) ---- */
AIPhysic_Config_t AIPhysicConfig;   /* @0x8010dc74  (bss(zero)) */
int          AIPhysic_iTime;   /* @0x8013c594  (bss(zero)) */
int          AIPhysic_time;   /* @0x8013c598  (bss(zero)) */
int          AIPhysic_elapsedTime;   /* @0x8013c59c  (bss(zero)) */


/* ---- intra-TU forward declarations ---- */
void AIPhysic_StopCar(Car_tObj *carObj,int velScale,int rotScale);
void AIPhysic_RevEngine(Car_tObj *carObj);
void AIPhysic_HandleShifting(Car_tObj *carObj);
Gear_t AIPhysic_CalculateGear(Car_tObj *carObj);
int AIPhysic_GearInvSpeedRange(Car_tObj *carObj,Gear_t gear);
int AIPhysic_GearTopSpeed(Car_tObj *carObj,Gear_t gear);
int AIPhysic_GearBottomSpeed(Car_tObj *carObj,Gear_t gear);
int AIPhysic_CalcAcceleration(Car_tObj *carObj,int speed);
int AIPhysic_ModifyAccelerationAccordingToScript(Car_tObj *carObj,int acc);
int AIPhysic_CalcDeceleration(Car_tObj *carObj);
void AIPhysic_CheckDesiredDirection(Car_tObj *carObj);
void AIPhysic_HandleSignalling(Car_tObj *carObj);
void AIPhysic_HandleWipeoutTimer(Car_tObj *carObj);
void AIPhysic_Main(Car_tObj *carObj);
void AIPhysic_CheckForBadPosition(Car_tObj *carObj);
int AIPhysics_UseCoolPhysics(Car_tObj *carObj);
void AIPhysic_SimplePhysics(Car_tObj *carObj);
void AIPhysic_SimplePhysics_LongVel(Car_tObj *carObj);
void AIPhysic_SimplePhysics_LatVel(Car_tObj *carObj);
void AIPhysic_CoolPhysics(Car_tObj *carObj);
void AIPhysic_HandleDirection(Car_tObj *carObj);
void AIPhysic_Preperation(Car_tObj *carObj);
int AIPhysic_CalculateRoadPosition(coorddef *pos,int slice);
void AIPhysic_GetDesiredVector(Car_tObj *carObj);
void AIPhysic_TargetedGetDesiredVector(Car_tObj *carObj);
int AIPhysic_CheckIfOutOfControl(Car_tObj *carObj);
void AIPhysic_OutOfControlPhysics(Car_tObj *carObj);
int AIPhysic_GetRearEndDamageFactor(Car_tObj *carObj);
void AIPhysic_InControlPhysics(Car_tObj *carObj);
void AIPhysic_FinishUp(Car_tObj *carObj);
void AIPhysic_CalculateRampedDesiredLatPos(Car_tObj *carObj,eRampType rampType);
int AIPhysic_HitWallCheck(Car_tObj *carObj);
void AIPhysic_ProcessBarrierCollision(Car_tObj *carObj);
void AIPhysic_ProcessCollision(Car_tObj *carObj);
void AIPhysic_ChangeDirection(Car_tObj *carObj,int time);
void AIPhysic_CheckForGripReduction(Car_tObj *carObj);
void AIPhysic_StartUp(void);
void AIPhysic_CleanUp(void);
void AIPhysic_Reset(void);
void AIPhysic_ResetCar(Car_tObj *carObj);
void AIPhysic_InitCar(Car_tObj *carObj);
void AIPhysic_DeInitCar(Car_tObj *carObj);


/* ---- AIPhysic_StopCar__FP8Car_tObjii  [@0x80069238] ---- */
void AIPhysic_StopCar(Car_tObj *carObj,int velScale,int rotScale)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  (carObj->angularAcc).z = 0;
  (carObj->angularAcc).y = 0;
  (carObj->angularAcc).x = 0;
  (carObj->linearAcc_ch).z = 0;
  (carObj->linearAcc_ch).y = 0;
  (carObj->linearAcc_ch).x = 0;
  (carObj->linearAcc_rh).z = 0;
  (carObj->linearAcc_rh).y = 0;
  (carObj->linearAcc_rh).x = 0;
  if (velScale < 0) {
    velScale = velScale + 0xff;
  }
  iVar3 = velScale >> 8;
  iVar1 = iVar3 * (carObj->N).linearVel.x;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  iVar2 = iVar3 * (carObj->N).linearVel.y;
  (carObj->N).linearVel.x = iVar1 >> 8;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  (carObj->N).linearVel.y = iVar2 >> 8;
  iVar3 = iVar3 * (carObj->N).linearVel.z;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar1 = (carObj->N).angularVel.y;
  (carObj->N).linearVel.z = iVar3 >> 8;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  if (rotScale < 0) {
    rotScale = rotScale + 0xff;
  }
  (carObj->N).angularVel.y = (iVar1 >> 8) * (rotScale >> 8);
  return;
}

/* ---- AIPhysic_RevEngine__FP8Car_tObj  [@0x800692fc] ---- */
void AIPhysic_RevEngine(Car_tObj *carObj)
{
  int increase;
  int redLine;
  int iVar1;
  int iVar2;
  
  iVar2 = carObj->redLine;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xffff;
  }
  iVar1 = carObj->flywheelRpm;
  /* H30: was a self-assign no-op; restore the rev increase (oracle 0x80069314-0x8006938C):
     increase = ((carIndex%2)+1)*AIPhysic_elapsedTime*0x8C; if flywheelRpm is odd, increase = -(increase>>1)
     rounded down to even.  flywheelRpm += increase (then the existing redline/0x1F5 clamps). */
  increase = (((*(int *)((char *)carObj + 596) % 2) + 1) * AIPhysic_elapsedTime) * 0x8C;
  if ((iVar1 & 1) != 0) {                                /* 0x80069354-7C */
    increase = -(increase >> 1);
    if ((increase & 1) != 0) increase = increase - 1;
  }
  iVar1 = iVar1 + increase;                              /* 0x80069388 flywheelRpm += increase */
  carObj->flywheelRpm = iVar1;                           /* 0x8006938C */
  if (iVar2 >> 0x10 < iVar1) {
    carObj->flywheelRpm = (((iVar2 >> 0x10) - (iVar2 >> 0x1f)) >> 1) | 1;
  }
  if (carObj->flywheelRpm < 0x1f5) {
    carObj->flywheelRpm = 500;
  }
  return;
}

/* ---- AIPhysic_HandleShifting__FP8Car_tObj  [@0x800693cc] ---- */
void AIPhysic_HandleShifting(Car_tObj *carObj)
{
  int desiredRPM;
  int speed;
  int speedDiff;
  int baseRPM;
  int invGearSpeedRange;
  Gear_t gear;
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 3000;
  if (carObj->aiShiftTimer < 1) {
    gear = AIPhysic_CalculateGear(carObj);
    iVar1 = carObj->currentSpeed;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    iVar3 = 0;
    iVar2 = AIPhysic_GearBottomSpeed(carObj,gear);
    iVar1 = iVar1 - iVar2;
    if (2 < (int)gear) {
      iVar3 = 0xfa00000;
    }
    iVar2 = AIPhysic_GearInvSpeedRange(carObj,gear);
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xff;
    }
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar1 = (iVar1 >> 8) * (iVar2 >> 8);
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xff;
    }
    iVar2 = carObj->redLine - iVar3;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar3 = iVar3 + (iVar1 >> 8) * (iVar2 >> 8);
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xffff;
    }
    iVar3 = iVar3 >> 0x10;
    (carObj->control).gear = (char)gear;
  }
  else {
    /* @0x800693F8-69408: aiShiftTimer -= AIPhysic_elapsedTime. m2c folded the subtraction into a
     * self-assign (aiShiftTimer = aiShiftTimer), so the AI gear-shift timer never counted down (M20). */
    carObj->aiShiftTimer = carObj->aiShiftTimer - AIPhysic_elapsedTime;
  }
  iVar2 = carObj->flywheelRpm;
  iVar1 = iVar3 - iVar2;
  if (iVar2 < iVar3) {
    if (iVar1 < 0) {
      iVar1 = iVar1 + 7;
    }
    iVar1 = iVar1 >> 3;
  }
  else {
    iVar1 = iVar2 - iVar3;
    if (iVar2 <= iVar3) {
      return;
    }
    if (iVar1 < 0) {
      iVar1 = iVar1 + 7;
    }
    iVar1 = -(iVar1 >> 3);
  }
  carObj->flywheelRpm = iVar2 + iVar1;
  return;
}

/* ---- AIPhysic_CalculateGear__FP8Car_tObj  [@0x80069534] ---- */
Gear_t AIPhysic_CalculateGear(Car_tObj *carObj)
{
  int hi;
  int speed;
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  Gear_t gear;
  
  iVar4 = carObj->currentSpeed;
  if (iVar4 < 0) {
    iVar4 = -iVar4;
  }
  if (iVar4 < 0x20000) {
    gear = (Gear_t)1;
  }
  else {
    gear = (Gear_t)(u_int)(u_char)(carObj->control).gear;
    if (carObj->driveDirection == -1) {
      gear = (Gear_t)0;
    }
    else {
      while( true ) {
        bVar1 = false;
        iVar2 = AIPhysic_GearTopSpeed(carObj,gear);
        if ((iVar2 < iVar4) ||
           (iVar3 = AIPhysic_GearBottomSpeed(carObj,gear), iVar4 < iVar3)) {
          bVar1 = true;
        }
        if (!bVar1) break;
        if (iVar2 < iVar4) {
          iVar2 = AIPhysic_GearTopSpeed(carObj,(Gear_t)(gear + 1));
          if (iVar2 == 0) {
            return gear;
          }
          carObj->aiShiftTimer = carObj->aiShiftDuration;
          gear = (Gear_t)(gear + 1);
        }
        else {
          gear = (Gear_t)(gear - 1);
          carObj->aiShiftTimer = carObj->aiShiftDuration;
        }
      }
    }
  }
  return gear;
}

/* ---- AIPhysic_GearInvSpeedRange__FP8Car_tObj6Gear_t  [@0x80069638] ---- */
int AIPhysic_GearInvSpeedRange(Car_tObj *carObj,Gear_t gear)
{
  int convertedGear;
  while ((int)gear < 2) {
    gear = (Gear_t)2;
  }
  return carObj->topSpeeds[gear + 5];
}

/* ---- AIPhysic_GearTopSpeed__FP8Car_tObj6Gear_t  [@0x80069660] ---- */
int AIPhysic_GearTopSpeed(Car_tObj *carObj,Gear_t gear)
{
  int convertedGear;
  while ((int)gear < 2) {
    gear = (Gear_t)2;
  }
  return carObj->topSpeeds[gear - 2];
}

/* ---- AIPhysic_GearBottomSpeed__FP8Car_tObj6Gear_t  [@0x80069688] ---- */
int AIPhysic_GearBottomSpeed(Car_tObj *carObj,Gear_t gear)
{
  if (2 < (int)gear) {
    return carObj->topSpeeds[gear - 3];
  }
  return 0;
}

/* ---- AIPhysic_CalcAcceleration__FP8Car_tObji  [@0x800696b0] ---- */
int AIPhysic_CalcAcceleration(Car_tObj *carObj,int speed)
{
  int accelEntry;
  int acceleration;
  int absSpeed;
  int speedUpAcc;
  int normalTopCap;
  int upgradeTopCap;
  int iVar1;
  int iVar2;
  int a;
  
  if (speed < 0) {
    speed = -speed;
  }
  iVar1 = 0;
  if (carObj->aiShiftTimer < 1) {
    iVar1 = carObj->carInfo->carType;
    if (iVar1 < 0x16) {
      a = Cars_topSpeedCap[iVar1];
      iVar1 = fixedmult(a,carObj->topSpeedUpgradeMult);
      iVar2 = fixedmult(iVar1,carObj->aiGlue);
      if (iVar2 < speed) {
        return 0;
      }
      if (iVar1 < speed) {
        return 0;
      }
      if (a < speed) {
        speed = a + -0x238e3;
      }
    }
    if (speed < 0) {
      speed = speed + 0xffff;
    }
    iVar1 = speed >> 0x10;
    if (0x6f < iVar1) {
      iVar1 = 0x6f;
    }
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    iVar1 = (carObj->accelerationRecord)->Get(iVar1);
    iVar2 = carObj->accNitrous;
    if (iVar2 != 0x10000) {
      if (iVar1 < 0) {
        iVar1 = iVar1 + 0xff;
      }
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xff;
      }
      iVar1 = (iVar1 >> 8) * (iVar2 >> 8);
    }
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xff;
    }
    iVar2 = carObj->accUpgradeMult;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar1 = (iVar1 >> 8) * (iVar2 >> 8);
    if (0 < GameSetup_gData.Weather) {
      if (iVar1 < 0) {
        iVar1 = iVar1 + 0xff;
      }
      iVar1 = (iVar1 >> 8) * 0xe6;
    }
    if ((carObj->carFlags & 0x20U) != 0) {
      if (iVar1 < 0) {
        iVar1 = iVar1 + 0xff;
      }
      iVar2 = carObj->copAccMult;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xff;
      }
      iVar1 = (iVar1 >> 8) * (iVar2 >> 8);
    }
    if ((((GameSetup_gData.raceType == 1) || (GameSetup_gData.raceType == 5)) &&
        ((((*(int *)((char *)Cars_gHumanRaceCarList[0] + 0x260)) & 0x200) != 0 ||
         ((Cars_gNumHumanRaceCars == 2 && (((*(int *)((char *)Cars_gHumanRaceCarList[1] + 0x260)) & 0x200) != 0)))))) &&
       ((carObj->carFlags & 8U) != 0)) {
      if (iVar1 < 0) {
        iVar1 = iVar1 + 0xff;
      }
      iVar2 = AITune_BTCPerpAccMults[GameSetup_gData.skill];
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xff;
      }
      iVar1 = (iVar1 >> 8) * (iVar2 >> 8);
    }
    iVar1 = AIPhysic_ModifyAccelerationAccordingToScript(carObj,iVar1);
    iVar2 = AISpeeds_SuperDuperSpeedUpTheCarsAtTheStartBecauseWeCannotActuallyHandleRenderingTheseCars(carObj);
    if (iVar2 != 0x10000) {
      iVar1 = fixedmult(iVar1,iVar2);
    }
  }
  return iVar1;
}

/* ---- AIPhysic_ModifyAccelerationAccordingToScript__FP8Car_tObji  [@0x80069990] ---- */
int AIPhysic_ModifyAccelerationAccordingToScript(Car_tObj *carObj,int acc)
{
  int iVar1;
  
  iVar1 = AIScript_DoReAction(&carObj->script,(AIScript_tAIReaction)(4));
  if (iVar1 != -1) {
    if (acc < 0) {
      acc = acc + 0xff;
    }
    acc = (acc >> 8) * 0x180;
  }
  return acc;
}

/* ---- AIPhysic_CalcDeceleration__FP8Car_tObj  [@0x800699e8] ---- */
int AIPhysic_CalcDeceleration(Car_tObj *carObj)
{
  int d;
  int iVar1;
  int iVar2;
  
  iVar2 = carObj->aiGlue;
  iVar1 = carObj->brakeInfo->deceleration_;
  if (0x10000 < iVar2) {
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xff;
    }
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar1 = (iVar1 >> 8) * (iVar2 >> 8);
  }
  return iVar1;
}

/* ---- AIPhysic_CheckDesiredDirection__FP8Car_tObj  [@0x80069a34] ---- */
void AIPhysic_CheckDesiredDirection(Car_tObj *carObj)
{
  int turnAroundSpeed;
  if (carObj->speed < 0x8e38e) {
    carObj->direction = carObj->desiredDirection;
  }
  return;
}

/* ---- AIPhysic_HandleSignalling__FP8Car_tObj  [@0x80069a7c] ---- */
void AIPhysic_HandleSignalling(Car_tObj *carObj)
{
  int lDes;
  int lPos;
  u_short uVar1;
  
  if ((carObj->carFlags & 0x10U) != 0) {
    if (carObj->desiredLatPos < carObj->roadPosition + -0x40000) {
      uVar1 = (carObj->render).signalLight[0];
      (carObj->render).signalLight[1] = 0;
      (carObj->render).signalLight[0] = uVar1 | 0x80;
      return;
    }
    if (carObj->roadPosition + 0x40000 < carObj->desiredLatPos) {
      uVar1 = (carObj->render).signalLight[1];
      (carObj->render).signalLight[0] = 0;
      (carObj->render).signalLight[1] = uVar1 | 0x80;
      return;
    }
    (carObj->render).signalLight[0] = 0;
    (carObj->render).signalLight[1] = 0;
  }
  return;
}

/* ---- AIPhysic_HandleWipeoutTimer__FP8Car_tObj  [@0x80069af0] ---- */
void AIPhysic_HandleWipeoutTimer(Car_tObj *carObj)
{
  if (((carObj->carFlags & 8U) != 0) && (carObj->wipeOutStartTick < simGlobal.gameTicks)) {
    randtemp = fastRandom * randSeed;
    fastRandom = randtemp & 0xffff;
    carObj->wipeOutStartTick =
         simGlobal.gameTicks + carObj->personality->minimumBetweenWipeoutTicks +
         (randtemp >> 8 & 0xffff & carObj->personality->randomBetweenWipeoutTicks);
  }
  return;
}

/* ---- AIPhysic_Main__FP8Car_tObj  [@0x80069b84] ---- */
void AIPhysic_Main(Car_tObj *carObj)
{
  char useCoolPhysics;
  int iVar1;
  u_int uVar2;
  
  iVar1 = Sched_ExecuteCheck(1,1,(carObj->N).distToPlayer,(carObj->N).objID,&AIPhysic_time,
                     &AIPhysic_elapsedTime,&AIPhysic_iTime,carObj->forceNoSimOptz);
  if (iVar1 == 0) {
    return;
  }
  if ((carObj->carFlags & 2U) != 0) {
    AIWorld_CalcSpeed(carObj);
  }
  AIPhysic_CheckDesiredDirection(carObj);
  AIPhysic_CheckForGripReduction(carObj);
  AIPhysic_HandleSignalling(carObj);
  iVar1 = AIWorld_CalcLateralVelocity(carObj);
  carObj->lateralVelocity = iVar1;
  uVar2 = AIPhysics_UseCoolPhysics(carObj);
  AIPhysic_CalculateRampedDesiredLatPos(carObj,(eRampType)(u_int)((uVar2 & 0xff) != 0));
  if ((carObj->AIFlags & 4U) != 0) {
    return;
  }
  if ((carObj->N).active == '\0') {
    return;
  }
  if (simGlobal.gameStarted != 1) {
    AIPhysic_RevEngine(carObj);
    return;
  }
  AIPhysic_HandleShifting(carObj);
  if ((carObj->N).flightTime != 0) {
    iVar1 = 0xfae1;
    if ((carObj->carFlags & 0x400U) == 0) {
      return;
    }
    goto LAB_80069dc0;
  }
  if (carObj->speed < 0x40000) {
    (carObj->linearVel_ch).z = 0;
    carObj->rearSkid = 0;
    carObj->frontSkid = 0;
  }
  if (((carObj->N).flightTime != 0) || (0x4ccb < (carObj->N).orientMat.m[4])) {
    if (carObj->blowout != 0) {
      iVar1 = 0xfd70;
      goto LAB_80069dc0;
    }
    if (carObj->pullOver != 0) {
      if (carObj->speed < 0x238e3) {
        AIPhysic_StopCar(carObj,0xe666,0xe666);
        return;
      }
      if (carObj->speed < 0x8e38e) {
        iVar1 = 0xf5c2;
        goto LAB_80069dc0;
      }
    }
    if (((carObj->carFlags & 1U) != 0) && ((carObj->stats).finishType == 2)) {
      iVar1 = carObj->currentSpeed;
      if (iVar1 < 0) {
        iVar1 = -iVar1;
      }
      if (iVar1 < 0x20000) goto LAB_80069dbc;
    }
    if (carObj->desiredSpeed != 0) {
      if ((uVar2 & 0xff) == 0) {
        AIPhysic_SimplePhysics(carObj);
      }
      else {
        AIPhysic_CoolPhysics(carObj);
      }
      AIPhysic_CheckForBadPosition(carObj);
      AIPhysic_HandleWipeoutTimer(carObj);
      return;
    }
  }
LAB_80069dbc:
  iVar1 = 0xf0a3;
LAB_80069dc0:
  AIPhysic_StopCar(carObj,iVar1,0xfae1);
  return;
}

/* ---- AIPhysic_CheckForBadPosition__FP8Car_tObj  [@0x80069e14] ---- */
void AIPhysic_CheckForBadPosition(Car_tObj *carObj)
{
  int badSpeed;
  int badRoadPos;
  bool bVar1;
  bool bVar2;
  int iVar3;
  
  bVar1 = false;
  bVar2 = false;
  if (((0x730000 < (carObj->N).linearVel.z) || (0x730000 < (carObj->N).linearVel.x)) ||
     ((0x730000 < (carObj->N).speedXZ && ((carObj->N).simOptz == '\0')))) {
    bVar1 = true;
  }
  iVar3 = (carObj->N).simRoadInfo.slice * 0x20 + (int)BWorldSm_slices;
  if ((carObj->roadPosition < *(short *)(iVar3 + 0x18) * -0x100 + -0x230000) ||
     (*(short *)(iVar3 + 0x1a) * 0x100 + 0x230000 < carObj->roadPosition)) {
    bVar2 = true;
  }
  if ((bVar1) || (bVar2)) {
    Cars_ResetCollidedCars(carObj,1,0);
  }
  return;
}

/* ---- AIPhysics_UseCoolPhysics__FP8Car_tObj  [@0x80069eec] ---- */
int AIPhysics_UseCoolPhysics(Car_tObj *carObj)
{
  u_char bVar1;
  
  if ((carObj->carFlags & 0x800U) == 0) {
    bVar1 = (carObj->N).simOptz;
    if ((bVar1 != 0) && (((carObj->carFlags & 0x20U) == 0 || (1 < bVar1)))) {
      return 0;
    }
  }
  return 1;
}

/* ---- AIPhysic_SimplePhysics__FP8Car_tObj  [@0x80069f30] ---- */
void AIPhysic_SimplePhysics(Car_tObj *carObj)
{
  coorddef forward;
  coorddef right;
  int speed;
  int sliceLookAhead;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if ((carObj->AIFlags & 0x10U) != 0) {
    carObj->rampDesiredLatPos = carObj->roadPosition;
    carObj->AIFlags = carObj->AIFlags & 0xffffffef;
  }
  if (((((carObj->carFlags & 8U) != 0) && (carObj->wipeOutStartTick < simGlobal.gameTicks)) &&
      (iVar1 = AIDataRecord_TrackCurve->Get((int)(carObj->N).simRoadInfo.slice), 0x1e < iVar1)
      ) && (0x1638e3 < carObj->speed)) {
    carObj->wipeOutEndTick = simGlobal.gameTicks + 0x180;
  }
  AIPhysic_SimplePhysics_LongVel(carObj);
  AIPhysic_SimplePhysics_LatVel(carObj);
  iVar1 = (carObj->N).orientMat.m[6];
  iVar4 = (carObj->N).orientMat.m[7];
  iVar6 = (carObj->N).orientMat.m[8];
  iVar5 = (carObj->N).roadMatrix.m[1];
  iVar7 = (carObj->N).roadMatrix.m[2];
  iVar2 = fixedmult(carObj->laneChangeSpeed,(carObj->N).roadMatrix.m[0]);
  iVar5 = fixedmult(carObj->laneChangeSpeed,iVar5);
  iVar7 = fixedmult(carObj->laneChangeSpeed,iVar7);
  iVar3 = fixedmult(carObj->currentSpeed * carObj->direction,iVar1);
  iVar4 = fixedmult(carObj->currentSpeed * carObj->direction,iVar4);
  iVar6 = fixedmult(carObj->currentSpeed * carObj->direction,iVar6);
  iVar1 = carObj->laneChangeSpeed * carObj->direction;
  (carObj->N).linearVel.x = iVar3 + iVar2;
  iVar2 = carObj->speed;
  (carObj->N).linearVel.y = iVar4 + iVar5;
  (carObj->linearVel_ch).z = iVar2;
  (carObj->N).linearVel.z = iVar6 + iVar7;
  iVar2 = iVar1;
  if (iVar1 < 0) {
    iVar2 = -iVar1;
  }
  (carObj->linearVel_ch).x = iVar1;
  iVar1 = iVar2;
  if (iVar2 < 0) {
    iVar1 = iVar2 + 0xff;
  }
  if ((iVar1 >> 8) * 0x19 < iVar2) {
    carObj->slide = 0x8000;
  }
  else {
    carObj->slide = 0;
  }
  iVar1 = carObj->speed;
  (carObj->N).angularVel.x = 0;
  (carObj->N).angularVel.y = 0;
  (carObj->N).angularVel.z = 0;
  if (0x30000 < iVar1) {
    Newton_CopyRoadMatrixToOrientMat(&carObj->N,(u_int)(carObj->direction == -1));
  }
  iVar1 = carObj->currentSpeed;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  iVar2 = iVar1 / 0x60000;
  if (-1 < iVar2) {
    if ((iVar2 < AIPhysicConfig.min_lookahead / 6) && (-1 < iVar1)) {
      iVar2 = AIPhysicConfig.min_lookahead / 6;
    }
  }
  if (AIPhysicConfig.max_lookahead / 6 < iVar2) {
    iVar2 = AIPhysicConfig.max_lookahead / 6;
  }
  iVar2 = iVar2 * carObj->direction;
  if (iVar2 < 0) {
    iVar2 = (carObj->N).simRoadInfo.slice + iVar2;
    if (iVar2 < 0) {
      iVar2 = iVar2 + gNumSlices;
    }
  }
  else {
    iVar2 = (carObj->N).simRoadInfo.slice + iVar2;
    if (gNumSlices <= iVar2) {
      iVar2 = iVar2 - gNumSlices;
    }
  }
  carObj->lookAheadSlice = iVar2;
  return;
}

/* ---- AIPhysic_SimplePhysics_LongVel__FP8Car_tObj  [@0x8006a29c] ---- */
void AIPhysic_SimplePhysics_LongVel(Car_tObj *carObj)
{
  int acceleration;
  int deceleration;
  u_char bVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int brakeRamp;
  
  iVar4 = AIPhysic_CalcAcceleration(carObj,carObj->currentSpeed);
  iVar5 = AIPhysic_CalcDeceleration(carObj);
  if (carObj->pullOver != 0) {
    carObj->desiredSpeed = 0;
  }
  if (simGlobal.gameTicks < carObj->wipeOutEndTick) {
    iVar6 = carObj->desiredSpeed;
    if (iVar6 < 0) {
      iVar6 = iVar6 + 3;
    }
    carObj->desiredSpeed = iVar6 >> 2;
  }
  if (carObj->direction == -1) {
    if ((carObj->currentSpeed < carObj->desiredSpeed) || (carObj->desiredDirection != -1)) {
      iVar6 = (u_char)(carObj->control).brakeLevel + AIPhysic_elapsedTime * 4;
      (carObj->linearAcc_ch).z = iVar5;
      if (iVar6 < 0xff) {
        (carObj->control).brakeLevel = (u_char)iVar6;
      }
      else {
        (carObj->control).brakeLevel = -1;
      }
      if (3 < (u_char)(carObj->control).brakeLevel) {
        (carObj->control).desiredBrakeLevel = '\x01';
      }
      iVar4 = carObj->currentSpeed;
      iVar6 = iVar5;
      if (iVar6 < 0) iVar6 = iVar6 + 0xff;
      iVar4 = AIPhysic_iTime;
      if (iVar4 < 0) iVar4 = iVar4 + 0xff;
      iVar4 = carObj->currentSpeed + (iVar6 >> 8) * (iVar4 >> 8);
      carObj->currentSpeed = iVar4;
      if (carObj->direction != carObj->desiredDirection) {
        return;
      }
      iVar5 = carObj->desiredSpeed;
      if (iVar4 <= carObj->desiredSpeed) {
        iVar5 = iVar4;
      }
      goto LAB_8006a5dc;
    }
    brakeRamp = (u_char)(carObj->control).brakeLevel;
    iVar6 = iVar4;
    if (iVar6 < 0) iVar6 = iVar6 + 0xff;
    iVar5 = AIPhysic_iTime;
    if (iVar5 < 0) iVar5 = iVar5 + 0xff;
    carObj->currentSpeed = carObj->currentSpeed - (iVar6 >> 8) * (iVar5 >> 8);
    if (brakeRamp <= AIPhysic_elapsedTime) {
      (carObj->control).brakeLevel = '\0';
    }
    else {
      (carObj->control).brakeLevel = (u_char)(brakeRamp - AIPhysic_elapsedTime);
    }
    if ((carObj->control).brakeLevel == '\0') {
      (carObj->control).desiredBrakeLevel = '\0';
    }
    iVar6 = carObj->currentSpeed;
    iVar5 = carObj->desiredSpeed;
    (carObj->linearAcc_ch).z = iVar4;
    bVar3 = iVar6 < iVar5;
  }
  else {
    if ((carObj->desiredSpeed < carObj->currentSpeed) ||
       (carObj->direction != carObj->desiredDirection)) {
      iVar6 = (u_char)(carObj->control).brakeLevel + AIPhysic_elapsedTime * 4;
      (carObj->linearAcc_ch).z = iVar5;
      if (iVar6 < 0xff) {
        (carObj->control).brakeLevel = (u_char)iVar6;
      }
      else {
        (carObj->control).brakeLevel = -1;
      }
      if (3 < (u_char)(carObj->control).brakeLevel) {
        (carObj->control).desiredBrakeLevel = '\x01';
      }
      iVar4 = carObj->currentSpeed;
      iVar6 = iVar5;
      if (iVar6 < 0) iVar6 = iVar6 + 0xff;
      iVar4 = AIPhysic_iTime;
      if (iVar4 < 0) iVar4 = iVar4 + 0xff;
      iVar4 = carObj->currentSpeed - (iVar6 >> 8) * (iVar4 >> 8);
      carObj->currentSpeed = iVar4;
      if (carObj->direction != carObj->desiredDirection) {
        return;
      }
      iVar5 = carObj->desiredSpeed;
      if (carObj->desiredSpeed < iVar4) {
        iVar5 = iVar4;
      }
      goto LAB_8006a5dc;
    }
    brakeRamp = (u_char)(carObj->control).brakeLevel;
    iVar6 = iVar4;
    if (iVar6 < 0) iVar6 = iVar6 + 0xff;
    iVar5 = AIPhysic_iTime;
    if (iVar5 < 0) iVar5 = iVar5 + 0xff;
    carObj->currentSpeed = carObj->currentSpeed + (iVar6 >> 8) * (iVar5 >> 8);
    if (brakeRamp <= AIPhysic_elapsedTime) {
      (carObj->control).brakeLevel = '\0';
    }
    else {
      (carObj->control).brakeLevel = (u_char)(brakeRamp - AIPhysic_elapsedTime);
    }
    if ((carObj->control).brakeLevel == '\0') {
      (carObj->control).desiredBrakeLevel = '\0';
    }
    iVar6 = carObj->currentSpeed;
    iVar5 = carObj->desiredSpeed;
    (carObj->linearAcc_ch).z = iVar4;
    bVar3 = iVar5 < iVar6;
  }
  if (!bVar3) {
    return;
  }
LAB_8006a5dc:
  carObj->currentSpeed = iVar5;
  return;
}

/* ---- AIPhysic_SimplePhysics_LatVel__FP8Car_tObj  [@0x8006a5f4] ---- */
void AIPhysic_SimplePhysics_LatVel(Car_tObj *carObj)
{
  int off;
  coorddef right;
  int carSpeed;
  int iVar1;
  int iVar2;
  int b;
  int iVar3;
  
  iVar1 = carObj->speed;
  iVar3 = 0;
  if (0x30000 < iVar1) {
    iVar3 = carObj->rampDesiredLatPos - carObj->roadPosition;
    iVar1 = carObj->speed;
  }
  if (iVar1 < 0x190001) {
    iVar1 = carObj->currentSpeed;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    carObj->laneChangeSpeed = iVar3;
    if (iVar3 < -iVar1) {
      carObj->laneChangeSpeed = -iVar1;
    }
    else if (iVar1 < iVar3) {
      carObj->laneChangeSpeed = iVar1;
    }
  }
  else {
    iVar2 = (carObj->N).roadMatrix.m[1];
    b = (carObj->N).roadMatrix.m[2];
    iVar1 = fixedmult(iVar3,(carObj->N).roadMatrix.m[0]);
    iVar2 = fixedmult(iVar3,iVar2);
    iVar3 = fixedmult(iVar3,b);
    (carObj->N).position.x = (carObj->N).position.x + iVar1;
    (carObj->N).position.y = (carObj->N).position.y + iVar2;
    iVar1 = (carObj->N).position.z;
    carObj->laneChangeSpeed = 0;
    (carObj->N).position.z = iVar1 + iVar3;
  }
  return;
}

/* ---- AIPhysic_CoolPhysics__FP8Car_tObj  [@0x8006a718] ---- */
void AIPhysic_CoolPhysics(Car_tObj *carObj)
{
  int iVar1;
  
  carObj->AIFlags = carObj->AIFlags | 0x10;
  AIPhysic_HandleDirection(carObj);
  if ((carObj->direction * carObj->currentSpeed < 0) && (carObj->driveDirection != -1)) {
    carObj->rampDesiredLatPos = 0;
  }
  iVar1 = AIPhysic_HitWallCheck(carObj);
  if (iVar1 != 0) {
    AIPhysic_ChangeDirection(carObj,0x40);
  }
  AIPhysic_Preperation(carObj);
  iVar1 = AIPhysic_CheckIfOutOfControl(carObj);
  if (iVar1 == 0) {
    AIPhysic_InControlPhysics(carObj);
  }
  else {
    AIPhysic_OutOfControlPhysics(carObj);
  }
  AIPhysic_FinishUp(carObj);
  return;
}

/* ---- AIPhysic_HandleDirection__FP8Car_tObj  [@0x8006a7cc] ---- */
void AIPhysic_HandleDirection(Car_tObj *carObj)
{
  if (carObj->driveDirection == -1) {
    if (((carObj->roadPosition < carObj->rampDesiredLatPos + -0xa0000) &&
        (0 < carObj->lateralVelocity)) ||
       ((carObj->rampDesiredLatPos + 0xa0000 < carObj->roadPosition && (carObj->lateralVelocity < 0)
        ))) {
      carObj->driveDirectionTimer = simGlobal.gameTicks + -0x18;
    }
    if (carObj->driveDirectionReverseTime < simGlobal.gameTicks - carObj->driveDirectionTimer) {
      carObj->driveDirection = 1;
      carObj->driveDirectionTimer = simGlobal.gameTicks;
    }
    if (0x140000 < carObj->desiredSpeed) {
      carObj->desiredSpeed = 0x140000;
    }
    if (0x140000 < -carObj->desiredSpeed) {
      carObj->desiredSpeed = -0x140000;
    }
    carObj->rampDesiredLatPos = 0;
  }
  return;
}

/* ---- AIPhysic_Preperation__FP8Car_tObj  [@0x8006a8b4] ---- */
void AIPhysic_Preperation(Car_tObj *carObj)
{
  coorddef forward;
  int aCar;
  int aCarWRTDesired;
  int aDesired;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = fixedmult((carObj->N).linearVel.x,(carObj->N).orientMat.m[0]);
  iVar2 = fixedmult((carObj->N).linearVel.y,(carObj->N).orientMat.m[1]);
  iVar3 = fixedmult((carObj->N).linearVel.z,(carObj->N).orientMat.m[2]);
  iVar4 = (carObj->N).linearVel.x;
  iVar5 = (carObj->N).orientMat.m[3];
  (carObj->linearVel_ch).x = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar4,iVar5);
  iVar2 = fixedmult((carObj->N).linearVel.y,(carObj->N).orientMat.m[4]);
  iVar3 = fixedmult((carObj->N).linearVel.z,(carObj->N).orientMat.m[5]);
  iVar4 = (carObj->N).linearVel.x;
  iVar5 = (carObj->N).orientMat.m[6];
  (carObj->linearVel_ch).y = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar4,iVar5);
  iVar2 = fixedmult((carObj->N).linearVel.y,(carObj->N).orientMat.m[7]);
  iVar3 = fixedmult((carObj->N).linearVel.z,(carObj->N).orientMat.m[8]);
  iVar4 = (carObj->N).angularVel.x;
  iVar5 = (carObj->N).orientMat.m[0];
  (carObj->linearVel_ch).z = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar4,iVar5);
  iVar2 = fixedmult((carObj->N).angularVel.y,(carObj->N).orientMat.m[1]);
  iVar3 = fixedmult((carObj->N).angularVel.z,(carObj->N).orientMat.m[2]);
  iVar4 = (carObj->N).angularVel.x;
  iVar5 = (carObj->N).orientMat.m[3];
  (carObj->angularVel_ch).x = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar4,iVar5);
  iVar2 = fixedmult((carObj->N).angularVel.y,(carObj->N).orientMat.m[4]);
  iVar3 = fixedmult((carObj->N).angularVel.z,(carObj->N).orientMat.m[5]);
  iVar4 = (carObj->N).angularVel.x;
  iVar5 = (carObj->N).orientMat.m[6];
  (carObj->angularVel_ch).y = iVar1 + iVar2 + iVar3;
  iVar2 = fixedmult(iVar4,iVar5);
  iVar3 = fixedmult((carObj->N).angularVel.y,(carObj->N).orientMat.m[7]);
  iVar4 = fixedmult((carObj->N).angularVel.z,(carObj->N).orientMat.m[8]);
  iVar1 = (carObj->linearVel_ch).x;
  (carObj->angularVel_ch).z = iVar2 + iVar3 + iVar4;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  iVar2 = iVar1;
  if (iVar1 < 0) {
    iVar2 = iVar1 + 0xff;
  }
  if ((iVar2 >> 8) * 0x19 < iVar1) {
    carObj->slide = 0x8000;
  }
  else {
    carObj->slide = 0;
  }
  iVar1 = (carObj->N).orientMat.m[6];
  iVar2 = (carObj->N).orientMat.m[8];
  if (carObj->driveDirection != 1) {
    iVar1 = -iVar1;
    iVar2 = -iVar2;
  }
  iVar1 = intatan(iVar1,iVar2);
  carObj->aCar = iVar1;
  AIPhysic_GetDesiredVector(carObj);
  iVar2 = intatan((carObj->desiredVector).x,(carObj->desiredVector).z);
  iVar1 = iVar1 - iVar2;
  iVar3 = iVar1 + 0x400;
  if (-0x201 < iVar1) {
    carObj->aCarWRTDesired = iVar1;
    if (iVar1 < 0x201) goto LAB_8006ab00;
    iVar3 = iVar1 + -0x400;
  }
  carObj->aCarWRTDesired = iVar3;
LAB_8006ab00:
  carObj->aDesired = iVar2;
  return;
}

/* ---- AIPhysic_CalculateRoadPosition__FP8coorddefi  [@0x8006ab1c] ---- */
int AIPhysic_CalculateRoadPosition(coorddef *pos,int slice)
{
  coorddef centerBack;
  coorddef carRelative;
  coorddef right;
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  piVar1 = (int *)(slice * 0x20 + (int)BWorldSm_slices);
  iVar5 = pos->x - *piVar1;
  iVar6 = pos->y - piVar1[1];
  iVar7 = pos->z - piVar1[2];
  iVar4 = slice * 0x20 + (int)BWorldSm_slices;
  iVar2 = *(char *)(iVar4 + 0x12) * 0x200;
  iVar3 = *(char *)(iVar4 + 0x13) * 0x200;
  iVar4 = *(char *)(iVar4 + 0x14) * 0x200;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  return (iVar2 >> 8) * (iVar5 >> 8) + (iVar3 >> 8) * (iVar6 >> 8) + (iVar4 >> 8) * (iVar7 >> 8);
}

/* ---- AIPhysic_GetDesiredVector__FP8Car_tObj  [@0x8006ac3c] ---- */
void AIPhysic_GetDesiredVector(Car_tObj *carObj)
{
  int speed;
  int roadWidth;
  int sliceLookAhead;
  int dirCorrectedSliceLookAhead;
  coorddef fCPoint;
  coorddef fPoint;
  coorddef right;
  int futureBend;
  int futureRoadPosition;
  int numReductions;
  int goodVector;
  int thisSlice;
  int checkSide;
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int slice;
  int iVar7;
  coorddef local_38;
  int local_28;
  int local_24;
  int local_20;
  
  slice = (int)(carObj->N).simRoadInfo.slice;
  iVar7 = 0;
  if ((((carObj->targetPos).x != 0) || ((carObj->targetPos).y != 0)) || ((carObj->targetPos).z != 0)
     ) {
    AIPhysic_TargetedGetDesiredVector(carObj);
    return;
  }
  iVar2 = carObj->currentSpeed;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  iVar3 = fixedmult(iVar2,0xb333);
  iVar3 = (iVar3 + 0x30000) / 0x60000;
  if (((-1 < iVar3) && (iVar3 < AIPhysicConfig.min_lookahead / 6)) && (-1 < iVar2)) {
    iVar3 = AIPhysicConfig.min_lookahead / 6;
  }
  if (AIPhysicConfig.max_lookahead / 6 < iVar3) {
    iVar3 = AIPhysicConfig.max_lookahead / 6;
  }
  iVar2 = iVar3 * carObj->driveDirection * carObj->direction;
  iVar5 = slice + iVar2;
  if (iVar2 < 0) {
    if (iVar5 < 0) {
      iVar5 = iVar5 + gNumSlices;
    }
  }
  else if (gNumSlices <= iVar5) {
    iVar5 = iVar5 - gNumSlices;
  }
  carObj->lookAheadSlice = iVar5;
  iVar2 = AIWorld_CalcRoadBend(carObj,iVar2);
  iVar5 = carObj->lookAheadSlice * 0x20 + (int)BWorldSm_slices;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if ((u_int)*(u_char *)(iVar5 + 0x1e) * 0x8000 * (u_int)(*(u_char *)(iVar5 + 0x1d) >> 4) +
      (u_int)*(u_char *)(iVar5 + 0x1f) * 0x8000 * (*(u_char *)(iVar5 + 0x1d) & 0xf) < 0x120000) {
    if (0xf333 < iVar2) {
      iVar5 = iVar3 * 0xca3d;
      iVar3 = iVar5 >> 0x10;
      if (iVar5 < 0) {
        iVar3 = (iVar5 + 0xffff) >> 0x10;
      }
    }
    if (iVar2 < 0xe667) {
      if (iVar2 < 0xcccd) {
        if (iVar2 < 0xc001) goto LAB_8006af18;
        iVar2 = iVar3 * 0xf333;
      }
      else {
        iVar2 = iVar3 * 0xe666;
      }
    }
    else {
      iVar2 = iVar3 * 0xd70a;
    }
    iVar3 = iVar2 >> 0x10;
    if (iVar2 < 0) {
      iVar3 = (iVar2 + 0xffff) >> 0x10;
    }
  }
LAB_8006af18:
  do {
    iVar2 = iVar3 * carObj->driveDirection * carObj->direction;
    if (iVar2 < 0) {
      iVar2 = slice + iVar2;
      if (iVar2 < 0) {
        iVar2 = iVar2 + gNumSlices;
      }
    }
    else {
      iVar2 = slice + iVar2;
      if (gNumSlices <= iVar2) {
        iVar2 = iVar2 - gNumSlices;
      }
    }
    carObj->lookAheadSlice = iVar2;
    piVar4 = (int *)(carObj->lookAheadSlice * 0x20 + (int)BWorldSm_slices);
    iVar2 = *piVar4;
    iVar5 = piVar4[1];
    iVar6 = piVar4[2];
    local_28 = (int)*(char *)(carObj->lookAheadSlice * 0x20 + (int)BWorldSm_slices + 0x12) << 9;
    local_24 = (int)*(char *)(carObj->lookAheadSlice * 0x20 + (int)BWorldSm_slices + 0x13) << 9;
    local_20 = (int)*(char *)(carObj->lookAheadSlice * 0x20 + (int)BWorldSm_slices + 0x14) << 9;
    local_38.x = fixedmult(carObj->rampDesiredLatPos,local_28);
    local_38.y = fixedmult(carObj->rampDesiredLatPos,local_24);
    local_38.z = fixedmult(carObj->rampDesiredLatPos,local_20);
    local_38.x = local_38.x + iVar2;
    local_38.z = local_38.z + iVar6;
    local_38.y = local_38.y + iVar5;
    iVar2 = AIPhysic_CalculateRoadPosition(&local_38,slice);
    iVar5 = slice * 0x20 + (int)BWorldSm_slices;
    if ((((int)((u_int)*(u_char *)(iVar5 + 0x1f) * 0x8000 * (*(u_char *)(iVar5 + 0x1d) & 0xf)) < iVar2)
        && (carObj->roadPosition < iVar2)) ||
       ((iVar2 < (int)-((u_int)*(u_char *)(iVar5 + 0x1e) * 0x8000 *
                       (u_int)(*(u_char *)(iVar5 + 0x1d) >> 4)) && (iVar2 < carObj->roadPosition)))) {
      iVar5 = 1;
      if (iVar2 < carObj->roadPosition) {
        iVar5 = -1;
      }
      iVar2 = AIWorld_LaneIndex(slice,carObj->roadPosition + iVar5 * 0x80000);
      iVar2 = AIWorld_IsDriveableLane(slice,iVar2);
      if (iVar2 == 0) {
        bVar1 = false;
      }
      else {
        iVar2 = AIWorld_LaneIndex(slice,carObj->roadPosition + iVar5 * 0x40000);
        iVar2 = AIWorld_IsDriveableLane(slice,iVar2);
        bVar1 = iVar2 != 0;
      }
    }
    else {
      bVar1 = true;
    }
    iVar7 = iVar7 + 1;
    iVar2 = iVar3 * 0xcccc;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xffff;
    }
    iVar3 = 4;
    if (3 < iVar2 >> 0x10) {
      iVar3 = iVar2 >> 0x10;
    }
  } while ((iVar7 < 5) && (!bVar1));
  (carObj->desiredVector).x = local_38.x - (carObj->N).position.x;
  (carObj->desiredVector).y = local_38.y - (carObj->N).position.y;
  (carObj->desiredVector).z = local_38.z - (carObj->N).position.z;
  return;
}

/* ---- AIPhysic_TargetedGetDesiredVector__FP8Car_tObj  [@0x8006b224] ---- */
void AIPhysic_TargetedGetDesiredVector(Car_tObj *carObj)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (carObj->targetPos).y;
  iVar3 = (carObj->N).position.y;
  (carObj->desiredVector).x = (carObj->targetPos).x - (carObj->N).position.x;
  iVar1 = (carObj->targetPos).z;
  (carObj->desiredVector).y = iVar2 - iVar3;
  iVar2 = carObj->targetLatPos;
  (carObj->desiredVector).z = iVar1 - (carObj->N).position.z;
  carObj->rampDesiredLatPos = iVar2;
  return;
}

/* ---- AIPhysic_CheckIfOutOfControl__FP8Car_tObj  [@0x8006b260] ---- */
int AIPhysic_CheckIfOutOfControl(Car_tObj *carObj)
{
  int futureBend;
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = AIWorld_CalcRoadBend(carObj,carObj->direction << 3);
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (simGlobal.gameTicks < carObj->wipeOutEndTick) {
    iVar1 = carObj->currentSpeed;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    return (0x2ffff < iVar1) ^ 1;
  }
  iVar2 = carObj->aCarWRTDesired;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if ((iVar2 < 0x74) && (carObj->driveDirection != -1)) {
    iVar2 = carObj->currentSpeed;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if (iVar2 < AIPhysicConfig.OOCModel.vel_limit_range + -0x30000) {
      return 1;
    }
    iVar3 = (carObj->N).simRoadInfo.slice * 0x20 + (int)BWorldSm_slices;
    if (carObj->roadPosition <
        (int)-((u_int)*(u_char *)(iVar3 + 0x1e) * 0x8000 * (u_int)(*(u_char *)(iVar3 + 0x1d) >> 4))) {
      return 1;
    }
    if ((int)((u_int)*(u_char *)(iVar3 + 0x1f) * 0x8000 * (*(u_char *)(iVar3 + 0x1d) & 0xf)) <
        carObj->roadPosition) {
      return 1;
    }
    if (0xcccc < iVar1) {
      return 1;
    }
    iVar1 = (carObj->linearVel_ch).x;
    iVar3 = carObj->speed;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    if (iVar1 <= (iVar3 >> 8) * 0x66) {
      return 0;
    }
    if (0xeffff < iVar2) {
      return 0;
    }
  }
  return 1;
}

/* ---- AIPhysic_OutOfControlPhysics__FP8Car_tObj  [@0x8006b400] ---- */
void AIPhysic_OutOfControlPhysics(Car_tObj *carObj)
{
  int desiredAngVel;
  int desiredLatVel;
  int currentAngAcc;
  int currentLatAcc;
  int currentLongAcc;
  int maxLatVel;
  int maxAngVel;
  int skid;
  int dir;
  int currentLatVel;
  int latVelLimit;
  int targetVel;
  int uTurn;
  int currentVel;
  char cVar1;
  u_char bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int brakeRamp;
  
  carObj->drag = 0;
  bVar3 = false;
  iVar4 = AIWorld_CalcFutureLateralVel(carObj,nfs4_mips_mult_s32(carObj->direction,AIPhysicConfig.latvelcalc_lookahead));
  if (nfs4_mips_mult_s32(carObj->direction,carObj->currentSpeed) < 0) {
    bVar3 = carObj->driveDirection != -1;
  }
  carObj->wipeOutEndTick = simGlobal.gameTicks;
  iVar5 = fixedmult(0x80,AIPhysicConfig.OOCModel.dangle_to_dav);
  iVar5 = nfs4_mips_mult_s32(nfs4_mips_negu_s32(carObj->aCarWRTDesired),iVar5);
  iVar6 = AIPhysicConfig.OOCModel.max_dav;
  if (iVar5 < AIPhysicConfig.OOCModel.max_dav) {
    iVar6 = iVar5;
  }
  iVar5 = nfs4_mips_negu_s32(AIPhysicConfig.OOCModel.max_dav);
  if (nfs4_mips_negu_s32(AIPhysicConfig.OOCModel.max_dav) < iVar6) {
    iVar5 = iVar6;
  }
  iVar6 = iVar5;
  if (iVar5 < 0) {
    iVar6 = iVar5 + 0xff;
  }
  iVar8 = nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar6,8),0xa00);
  iVar6 = AIPhysicConfig.OOCModel.max_dlvel;
  if (iVar8 < AIPhysicConfig.OOCModel.max_dlvel) {
    iVar6 = iVar8;
  }
  iVar8 = nfs4_mips_negu_s32(AIPhysicConfig.OOCModel.max_dlvel);
  if (nfs4_mips_negu_s32(AIPhysicConfig.OOCModel.max_dlvel) < iVar6) {
    iVar8 = iVar6;
  }
  iVar6 = carObj->speed;
  if (iVar8 < carObj->speed) {
    iVar6 = iVar8;
  }
  iVar9 = carObj->speed;
  iVar8 = nfs4_mips_negu_s32(iVar9);
  if (nfs4_mips_negu_s32(iVar9) < iVar6) {
    iVar8 = iVar6;
  }
  if ((nfs4_mips_negu_s32(AIPhysicConfig.OOCModel.vel_limit_range) < carObj->currentSpeed) &&
     (carObj->currentSpeed < AIPhysicConfig.OOCModel.vel_limit_range)) {
    if (iVar9 < 0) {
      iVar9 = iVar9 + 0xff;
    }
    iVar6 = AIPhysicConfig.OOCModel.lat_vel_limit_factor;
    if (AIPhysicConfig.OOCModel.lat_vel_limit_factor < 0) {
      iVar6 = AIPhysicConfig.OOCModel.lat_vel_limit_factor + 0xff;
    }
    iVar6 = nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar9,8),nfs4_mips_sra_s32(iVar6,8));
    if (iVar6 < 0) {
      iVar6 = nfs4_mips_negu_s32(iVar6);
    }
    iVar7 = iVar6;
    if (iVar8 < iVar6) {
      iVar7 = iVar8;
    }
    iVar8 = nfs4_mips_negu_s32(iVar6);
    if (nfs4_mips_negu_s32(iVar6) < iVar7) {
      iVar8 = iVar7;
    }
    iVar6 = AIPhysicConfig.OOCModel.ang_vel_limit_factor;
    if (AIPhysicConfig.OOCModel.ang_vel_limit_factor < 0) {
      iVar6 = AIPhysicConfig.OOCModel.ang_vel_limit_factor + 0xff;
    }
    iVar6 = nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar9,8),nfs4_mips_sra_s32(iVar6,8));
    if (iVar6 < 0) {
      iVar6 = nfs4_mips_negu_s32(iVar6);
    }
    iVar9 = iVar6;
    if (iVar5 < iVar6) {
      iVar9 = iVar5;
    }
    iVar5 = nfs4_mips_negu_s32(iVar6);
    if (nfs4_mips_negu_s32(iVar6) < iVar9) {
      iVar5 = iVar9;
    }
  }
  if (carObj->donutMode == 2) {
    iVar5 = nfs4_mips_addu_s32(iVar5,nfs4_mips_sll_s32(iVar5,2));
  }
  iVar5 = nfs4_mips_subu_s32((carObj->angularVel_ch).y,iVar5);
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  iVar6 = AIPhysicConfig.OOCModel.dav_to_aa;
  if (AIPhysicConfig.OOCModel.dav_to_aa < 0) {
    iVar6 = AIPhysicConfig.OOCModel.dav_to_aa + 0xff;
  }
  iVar9 = carObj->currentSpeed;
  if (iVar9 < 0) {
    iVar9 = nfs4_mips_negu_s32(iVar9);
  }
  iVar5 = nfs4_mips_negu_s32(nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar5,8),nfs4_mips_sra_s32(iVar6,8)));
  if (0x120000 < iVar9) {
    iVar5 = iVar5 / 2;
  }
  iVar6 = carObj->max_aa;
  if (iVar5 < carObj->max_aa) {
    iVar6 = iVar5;
  }
  iVar5 = nfs4_mips_negu_s32(carObj->max_aa);
  if (nfs4_mips_negu_s32(carObj->max_aa) < iVar6) {
    iVar5 = iVar6;
  }
  iVar8 = nfs4_mips_subu_s32((carObj->linearVel_ch).x,iVar8);
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0xff;
  }
  iVar6 = AIPhysicConfig.OOCModel.dlvel_to_clacc;
  if (AIPhysicConfig.OOCModel.dlvel_to_clacc < 0) {
    iVar6 = AIPhysicConfig.OOCModel.dlvel_to_clacc + 0xff;
  }
  iVar6 = nfs4_mips_negu_s32(nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar8,8),nfs4_mips_sra_s32(iVar6,8)));
  iVar8 = carObj->max_clacc;
  if (iVar6 < carObj->max_clacc) {
    iVar8 = iVar6;
  }
  iVar6 = nfs4_mips_negu_s32(carObj->max_clacc);
  if (nfs4_mips_negu_s32(carObj->max_clacc) < iVar8) {
    iVar6 = iVar8;
  }
  iVar8 = (carObj->linearVel_ch).z;
  if ((((carObj->driveDirection == -1) && ((carObj->targetPos).x == 0)) &&
      ((carObj->targetPos).y == 0)) && ((carObj->targetPos).z == 0)) {
    iVar9 = nfs4_mips_negu_s32(AIPhysicConfig.OOCModel.vel_limit_range);
  }
  else {
    iVar9 = nfs4_mips_mult_s32(nfs4_mips_mult_s32(carObj->desiredSpeed,carObj->direction),carObj->driveDirection);
  }
  if (carObj->pullOver == 0) {
    if (iVar9 < 0) {
      if ((iVar9 <= iVar8) && (iVar8 < 0x20001)) goto LAB_8006b814;
    }
    else if ((-0x20001 < iVar8) && (iVar8 <= iVar9)) {
LAB_8006b814:
      if (carObj->desiredDirection == carObj->direction) {
        iVar8 = AIPhysic_CalcAcceleration(carObj,(carObj->linearVel_ch).z);
        iVar8 = nfs4_mips_mult_s32(iVar8,carObj->driveDirection);
        brakeRamp = (u_char)(carObj->control).brakeLevel;
        if (brakeRamp <= AIPhysic_elapsedTime) {
          (carObj->control).brakeLevel = '\0';
        }
        else {
          (carObj->control).brakeLevel = (u_char)nfs4_mips_subu_s32(brakeRamp,AIPhysic_elapsedTime);
        }
        if ((carObj->control).brakeLevel == '\0') {
          (carObj->control).desiredBrakeLevel = '\0';
        }
        goto LAB_8006b908;
      }
    }
  }
  iVar9 = (carObj->linearVel_ch).z;
  if (iVar9 < 0) {
    iVar9 = nfs4_mips_negu_s32(iVar9);
  }
  iVar8 = 0;
  if (0 < iVar9) {
    iVar9 = AIPhysic_CalcDeceleration(carObj);
    brakeRamp = nfs4_mips_addu_s32((u_char)(carObj->control).brakeLevel,nfs4_mips_sll_s32(AIPhysic_elapsedTime,2));
    if (brakeRamp < 0xff) {
      (carObj->control).brakeLevel = (u_char)brakeRamp;
    }
    else {
      (carObj->control).brakeLevel = -1;
    }
    if (3 < (u_char)(carObj->control).brakeLevel) {
      (carObj->control).desiredBrakeLevel = '\x01';
    }
    iVar8 = nfs4_mips_negu_s32(iVar9);
    if ((carObj->linearVel_ch).z < 0) {
      iVar8 = iVar9;
    }
  }
LAB_8006b908:
  if (bVar3) {
    if (carObj->speed - 0x140001U < 0x1dffff) {
      if (iVar5 < 0) {
        iVar5 = iVar5 + 3;
      }
      iVar5 = nfs4_mips_sra_s32(iVar5,2);
      if (iVar8 < 0) {
        iVar8 = iVar8 + 3;
      }
      iVar8 = nfs4_mips_sra_s32(iVar8,2);
    }
    else {
      iVar5 = fixedmult(iVar5,0xc000);
      iVar9 = iVar8 / 2;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 3;
      }
      iVar8 = nfs4_mips_addu_s32(iVar9,nfs4_mips_sra_s32(iVar8,2));
    }
    iVar9 = iVar6;
    if (iVar6 < 0) {
      iVar9 = iVar6 + 3;
    }
    if (iVar6 < 0) {
      iVar6 = iVar6 + 7;
    }
    iVar6 = nfs4_mips_addu_s32(nfs4_mips_sra_s32(iVar9,2),nfs4_mips_sra_s32(iVar6,3));
  }
  if (iVar4 < 0) {
    iVar4 = nfs4_mips_negu_s32(iVar4);
  }
  iVar4 = nfs4_mips_subu_s32(iVar4,AIPhysicConfig.skid_value);
  if (((nfs4_mips_mult_s32(carObj->direction,carObj->currentSpeed) < 0) && (0x38e38 < carObj->speed)) ||
     (carObj->donutMode != 0)) {
    carObj->frontSkid = 0xa0000;
    carObj->rearSkid = 0xa0000;
  }
  else if (iVar4 < 1) {
    carObj->rearSkid = 0;
    carObj->frontSkid = 0;
  }
  else {
    carObj->frontSkid = iVar4;
    carObj->rearSkid = iVar4;
  }
  (carObj->linearAcc_ch).x = iVar6;
  (carObj->linearAcc_ch).y = 0;
  (carObj->linearAcc_ch).z = iVar8;
  (carObj->linearAcc_rh).x = 0;
  (carObj->linearAcc_rh).y = 0;
  (carObj->linearAcc_rh).z = 0;
  (carObj->angularAcc).x = 0;
  (carObj->angularAcc).y = iVar5;
  (carObj->angularAcc).z = 0;
  return;
}

/* ---- AIPhysic_GetRearEndDamageFactor__FP8Car_tObj  [@0x8006ba70] ---- */
int AIPhysic_GetRearEndDamageFactor(Car_tObj *carObj)
{
  int totalDamage;
  int iVar1;
  int iVar2;
  
  iVar1 = fixedmult((carObj->N).damage[4] + (carObj->N).damage[5] + (carObj->N).damage[6] +
                     (carObj->N).damage[9],0x147);
  iVar2 = 0x10000;
  if (iVar1 < 0x10001) {
    iVar2 = iVar1;
  }
  return iVar2;
}

/* ---- AIPhysic_InControlPhysics__FP8Car_tObj  [@0x8006bac8] ---- */
void AIPhysic_InControlPhysics(Car_tObj *carObj)
{
  /* SYM statics: BSS @0x8013C590 and data @0x8010DC54/0x8010DC64.
   * The data initializers are the exact four little-endian words in NFS4.EXE. */
  static char copCollisionReactionTime[4] = {0,0,0,0};
  static int copCollisionGripLoss[4] = {0x4ccc,0x8000,0x8000,0x10000};
  static int copCollisionSlowDown[4] = {0x90000,0x84000,0x70000,0x5c000};
  int currentLatVel;
  int currentLatPos;
  int desiredLatPos;
  int deltaLatPos;
  int desiredAngVel;
  int currentAngAcc;
  int desiredLatVel;
  int currentLatAcc;
  int currentLongAcc;
  int maxAngularAcceleration;
  int angleWRTdesired;
  int skid;
  int dir;
  int gripMultiplier;
  int maxLateralAcceleration;
  int dlvel_to_clacc;
  int desiredSpeed;
  int justBumped;
  coorddef unitDesiredVector;
  coorddef unitDesiredVectorRight;
  int lastCollisionTickDiff;
  int copCollisionFirmness;
  int vely;
  int fishtailtick;
  int signAngle;
  int maxLatVel;
  int maxAngVel;
  char cVar1;
  u_char bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  BO_tNewtonObj *pBVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int brakeRamp;
  coorddef local_60;
  int local_50;
  int local_4c;
  int local_48;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  
  local_38 = carObj->direction;
  carObj->drag = 0;
  local_60.x = (carObj->desiredVector).x;
  local_60.y = (carObj->desiredVector).y;
  local_60.z = (carObj->desiredVector).z;
  Math_QDNormalizeVector(&local_60);
  local_30 = 0;
  local_48 = -local_60.x;
  local_50 = local_60.z;
  local_4c = local_60.y;
  iVar11 = 0;
  iVar3 = fixedmult((carObj->N).linearVel.x,local_60.z);
  iVar4 = fixedmult((carObj->N).linearVel.y,local_4c);
  iVar5 = fixedmult((carObj->N).linearVel.z,local_48);
  local_40 = (iVar3 + iVar4 + iVar5) * carObj->direction;
  iVar4 = carObj->max_aa;
  local_3c = carObj->roadPosition - carObj->rampDesiredLatPos;
  iVar3 = fixedmult((carObj->linearVel_ch).z,0x62);
  iVar3 = fixedmult(iVar3 + 0x10000,carObj->gripFactor);
  if (((carObj->carFlags & 8U) != 0) && (carObj->wipeOutStartTick < simGlobal.gameTicks)) {
    iVar5 = (carObj->N).angularVel.y;
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }
    if ((1000 < iVar5) && (0x1638e3 < carObj->speed)) {
      carObj->wipeOutEndTick = simGlobal.gameTicks + 0x180;
    }
  }
  iVar10 = simGlobal.gameTicks - (carObj->N).collision.lastTime;
  iVar5 = AIScript_DoReAction(&carObj->script,(AIScript_tAIReaction)(0x800));
  if ((iVar5 != -1) || (simGlobal.gameTicks < carObj->wipeOutEndTick)) {
    iVar4 = 0;
    if (simGlobal.gameTicks - (carObj->N).collision.lastTime < 0x40) {
      carObj->wipeOutEndTick = simGlobal.gameTicks;
    }
    iVar11 = (carObj->N).angularVel.y;
    iVar3 = 0;
    if (iVar11 < 0) {
      iVar11 = -iVar11;
    }
    iVar11 = iVar11 + 0x1ca;
    if (0x3333 < iVar11) {
      iVar11 = 0x3333;
    }
    if ((carObj->N).angularVel.y < 1) {
      (carObj->N).angularVel.y = -iVar11;
    }
    else {
      (carObj->N).angularVel.y = iVar11;
    }
    iVar11 = 0xa0000;
  }
  iVar5 = GameSetup_gData.skill;
  if (iVar10 < 0x10) {
    carObj->wipeOutStartTick = carObj->wipeOutStartTick + -0x14;
  }
  if (((iVar10 < (int)(u_int)(u_char)copCollisionReactionTime[iVar5]) &&
      (pBVar6 = (carObj->N).collision.lastOtherObj, pBVar6 != (BO_tNewtonObj *)0x0)) &&
     ((((Car_tObj *)pBVar6)->carFlags & 0x200U) != 0)) {
    iVar4 = 0;
    local_30 = 1;
    iVar3 = fixedmult(iVar3,copCollisionGripLoss[iVar5]);
  }
  iVar10 = carObj->max_clacc;
  if (iVar10 < 0) {
    iVar10 = iVar10 + 0xff;
  }
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar10 = (iVar10 >> 8) * (iVar3 >> 8);
  iVar7 = AIPhysicConfig.ICModel.dlvel_to_clacc;
  if (AIPhysicConfig.ICModel.dlvel_to_clacc < 0) {
    iVar7 = AIPhysicConfig.ICModel.dlvel_to_clacc + 0xff;
  }
  iVar3 = (iVar7 >> 8) * (iVar3 >> 8);
  iVar7 = carObj->aiGlue;
  if (0x10000 < iVar7) {
    if (iVar7 < 0) {
      iVar7 = iVar7 + 0xff;
    }
    if (iVar10 < 0) {
      iVar10 = iVar10 + 0xff;
    }
    iVar10 = (iVar7 >> 8) * (iVar10 >> 8);
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    iVar3 = (iVar7 >> 8) * (iVar3 >> 8);
  }
  iVar7 = carObj->aCarWRTDesired;
  local_34 = carObj->desiredSpeed;
  if (simGlobal.gameTicks < carObj->AIFishtailEndTick) {
    iVar9 = 1;
    iVar8 = carObj->AIFishtailEndTick - simGlobal.gameTicks;
    if ((simGlobal.gameTicks / 0x28 & 1U) != 0) {
      iVar9 = -1;
    }
    if (0x96 - iVar8 < 0x32) {
      iVar9 = (iVar9 * 0x1e * (0x96 - iVar8)) / 0x32;
    }
    else {
      iVar9 = iVar9 * (iVar8 / 7 + 10);
    }
    iVar7 = iVar7 + iVar9;
    if (0x32 < iVar8) {
      iVar11 = (iVar8 * 0x140000) / 0x32;
    }
  }
  else {
    iVar9 = iVar7;
    if (iVar7 < 0) {
      iVar9 = -iVar7;
    }
    if (((carObj->personality->fishtailAngle < iVar9) && (0 < iVar7 * (carObj->angularAcc).y)) &&
       (iVar8 = AIPhysic_GetRearEndDamageFactor(carObj),
       (0x10000 - iVar8) * 0x14 + (carObj->personality->fishtailAngle + -0x14) * 0x10000 <
       iVar9 << 0x10)) {
      carObj->AIFishtailEndTick = simGlobal.gameTicks + 0x96;
    }
  }
  iVar8 = fixedmult(0x80,AIPhysicConfig.ICModel.dangle_to_dav);
  iVar9 = AIPhysicConfig.ICModel.max_dav;
  if (-iVar7 * iVar8 < AIPhysicConfig.ICModel.max_dav) {
    iVar9 = -iVar7 * iVar8;
  }
  iVar7 = -AIPhysicConfig.ICModel.max_dav;
  if (-AIPhysicConfig.ICModel.max_dav < iVar9) {
    iVar7 = iVar9;
  }
  iVar9 = carObj->speed;
  if ((-AIPhysicConfig.ICModel.vel_limit_range < carObj->currentSpeed) &&
     (carObj->currentSpeed < AIPhysicConfig.ICModel.vel_limit_range)) {
    if (iVar9 < 0) {
      iVar9 = iVar9 + 0xff;
    }
    iVar8 = AIPhysicConfig.ICModel.ang_vel_limit_factor;
    if (AIPhysicConfig.ICModel.ang_vel_limit_factor < 0) {
      iVar8 = AIPhysicConfig.ICModel.ang_vel_limit_factor + 0xff;
    }
    iVar9 = (iVar9 >> 8) * (iVar8 >> 8);
    if (iVar9 < 0) {
      iVar9 = -iVar9;
    }
    iVar8 = iVar9;
    if (iVar7 < iVar9) {
      iVar8 = iVar7;
    }
    iVar7 = -iVar9;
    if (-iVar9 < iVar8) {
      iVar7 = iVar8;
    }
  }
  iVar9 = fixedmult((carObj->angularVel_ch).y - iVar7,AIPhysicConfig.ICModel.dav_to_aa);
  iVar7 = iVar4;
  if (-iVar9 < iVar4) {
    iVar7 = -iVar9;
  }
  iVar9 = -iVar4;
  if (-iVar4 < iVar7) {
    iVar9 = iVar7;
  }
  iVar4 = fixedmult(local_40,iVar3);
  iVar3 = iVar10;
  if (-local_38 * iVar4 < iVar10) {
    iVar3 = -local_38 * iVar4;
  }
  iVar4 = -iVar10;
  if (-iVar10 < iVar3) {
    iVar4 = iVar3;
  }
  if (((carObj->currentSpeed * local_38 < local_34 * local_38) && (carObj->pullOver == 0)) &&
     (carObj->desiredDirection == carObj->direction)) {
    iVar10 = AIPhysic_CalcAcceleration(carObj,carObj->currentSpeed);
    brakeRamp = (u_char)(carObj->control).brakeLevel;
    if (brakeRamp <= AIPhysic_elapsedTime) {
      (carObj->control).brakeLevel = '\0';
    }
    else {
      (carObj->control).brakeLevel = (u_char)(brakeRamp - AIPhysic_elapsedTime);
    }
    if ((carObj->control).brakeLevel == '\0') {
      (carObj->control).desiredBrakeLevel = '\0';
    }
  }
  else {
    iVar3 = AIPhysic_CalcDeceleration(carObj);
    brakeRamp = (u_char)(carObj->control).brakeLevel + AIPhysic_elapsedTime * 4;
    if (brakeRamp < 0xff) {
      (carObj->control).brakeLevel = (u_char)brakeRamp;
    }
    else {
      (carObj->control).brakeLevel = -1;
    }
    if (3 < (u_char)(carObj->control).brakeLevel) {
      (carObj->control).desiredBrakeLevel = '\x01';
    }
    iVar10 = -iVar3;
    if ((carObj->linearVel_ch).z < 0) {
      iVar10 = iVar3;
    }
  }
  if (local_30 != 0) {
    iVar10 = -copCollisionSlowDown[iVar5];
  }
  if (iVar11 == 0) {
    if (local_40 < 0) {
      local_40 = -local_40;
    }
    iVar11 = local_40 - AIPhysicConfig.skid_value;
  }
  if (iVar11 < 1) {
    carObj->rearSkid = 0;
    carObj->frontSkid = 0;
  }
  else {
    carObj->rearSkid = iVar11;
    carObj->frontSkid = iVar11;
  }
  (carObj->linearAcc_ch).x = iVar4;
  (carObj->linearAcc_ch).y = 0;
  (carObj->linearAcc_ch).z = iVar10;
  (carObj->linearAcc_rh).x = 0;
  (carObj->linearAcc_rh).y = 0;
  (carObj->linearAcc_rh).z = 0;
  (carObj->angularAcc).x = 0;
  (carObj->angularAcc).y = iVar9;
  (carObj->angularAcc).z = 0;
  return;
}

/* ---- AIPhysic_FinishUp__FP8Car_tObj  [@0x8006c37c] ---- */
void AIPhysic_FinishUp(Car_tObj *carObj)
{
  coorddef angAcc;
  matrixtdef transOrientMat;
  matrixtdef transRoadMat;
  int tickLoop;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int angularStep;
  int angularStepTime;
  (carObj->linearAcc_ch).z = (carObj->linearAcc_ch).z + (carObj->linearAcc_rh).z;
  Cars_DoGravityEffectsOnAcc(carObj,0);
  (carObj->linearAcc_ch).z = (carObj->linearAcc_ch).z - (carObj->linearAcc_rh).z;
  transpose(&(carObj->N).orientMat,&transOrientMat);
  transpose(&(carObj->N).roadMatrix,&transRoadMat);
  iVar1 = fixedmult((carObj->linearAcc_ch).x,transOrientMat.m[0]);
  iVar2 = fixedmult((carObj->linearAcc_ch).y,transOrientMat.m[1]);
  iVar3 = fixedmult((carObj->linearAcc_ch).z,transOrientMat.m[2]);
  (carObj->linearAcc).x = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult((carObj->linearAcc_ch).x,transOrientMat.m[3]);
  iVar2 = fixedmult((carObj->linearAcc_ch).y,transOrientMat.m[4]);
  iVar3 = fixedmult((carObj->linearAcc_ch).z,transOrientMat.m[5]);
  iVar9 = (carObj->linearAcc_ch).x;
  (carObj->linearAcc).y = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar9,transOrientMat.m[6]);
  iVar2 = fixedmult((carObj->linearAcc_ch).y,transOrientMat.m[7]);
  iVar3 = fixedmult((carObj->linearAcc_ch).z,transOrientMat.m[8]);
  iVar9 = (carObj->linearAcc_rh).x;
  (carObj->linearAcc).z = iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar9,transRoadMat.m[0]);
  iVar2 = fixedmult((carObj->linearAcc_rh).y,transRoadMat.m[1]);
  iVar3 = fixedmult((carObj->linearAcc_rh).z,transRoadMat.m[2]);
  (carObj->linearAcc).x = (carObj->linearAcc).x + iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult((carObj->linearAcc_rh).x,transRoadMat.m[3]);
  iVar2 = fixedmult((carObj->linearAcc_rh).y,transRoadMat.m[4]);
  iVar3 = fixedmult((carObj->linearAcc_rh).z,transRoadMat.m[5]);
  iVar9 = (carObj->linearAcc_rh).x;
  (carObj->linearAcc).y = (carObj->linearAcc).y + iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar9,transRoadMat.m[6]);
  iVar2 = fixedmult((carObj->linearAcc_rh).y,transRoadMat.m[7]);
  iVar3 = fixedmult((carObj->linearAcc_rh).z,transRoadMat.m[8]);
  iVar9 = (carObj->angularAcc).x;
  (carObj->linearAcc).z = (carObj->linearAcc).z + iVar1 + iVar2 + iVar3;
  iVar1 = fixedmult(iVar9,transOrientMat.m[0]);
  iVar2 = fixedmult((carObj->angularAcc).y,transOrientMat.m[1]);
  iVar3 = fixedmult((carObj->angularAcc).z,transOrientMat.m[2]);
  iVar9 = fixedmult((carObj->angularAcc).x,transOrientMat.m[3]);
  iVar4 = fixedmult((carObj->angularAcc).y,transOrientMat.m[4]);
  iVar5 = fixedmult((carObj->angularAcc).z,transOrientMat.m[5]);
  iVar6 = fixedmult((carObj->angularAcc).x,transOrientMat.m[6]);
  iVar7 = fixedmult((carObj->angularAcc).y,transOrientMat.m[7]);
  iVar8 = fixedmult((carObj->angularAcc).z,transOrientMat.m[8]);
  (carObj->angularAcc).x = iVar1 + iVar2 + iVar3;
  (carObj->angularAcc).y = iVar9 + iVar4 + iVar5;
  (carObj->angularAcc).z = iVar6 + iVar7 + iVar8;
  iVar1 = fixedmult((carObj->linearAcc).x,AIPhysic_iTime);   /* H31: 2nd arg was 0 (oracle 0x8006C624 $a1=AIPhysic_iTime); 0 nullified accel->vel integration */
  iVar2 = (carObj->linearAcc).y;
  (carObj->N).linearVel.x = (carObj->N).linearVel.x + iVar1;
  iVar1 = fixedmult(iVar2,AIPhysic_iTime);   /* H31: 2nd arg was 0 (oracle AIPhysic_iTime) */
  iVar2 = (carObj->linearAcc).z;
  (carObj->N).linearVel.y = (carObj->N).linearVel.y + iVar1;
  iVar1 = fixedmult(iVar2,AIPhysic_iTime);   /* H31: 2nd arg was 0 (oracle AIPhysic_iTime) */
  iVar2 = carObj->drag;
  (carObj->N).linearVel.z = (carObj->N).linearVel.z + iVar1;
  for (iVar1 = 0; (iVar2 != 0 && (iVar1 < AIPhysic_elapsedTime)); iVar1 = iVar1 + 1) {   /* H32: bound was literal 0 (dead loop); oracle 0x8006C67C counter < AIPhysic_elapsedTime */
    iVar2 = fixedmult((carObj->N).linearVel.x,carObj->drag);
    iVar3 = (carObj->N).linearVel.y;
    iVar9 = carObj->drag;
    (carObj->N).linearVel.x = iVar2;
    iVar2 = fixedmult(iVar3,iVar9);
    iVar3 = (carObj->N).linearVel.z;
    iVar9 = carObj->drag;
    (carObj->N).linearVel.y = iVar2;
    iVar3 = fixedmult(iVar3,iVar9);
    iVar2 = carObj->drag;
    (carObj->N).linearVel.z = iVar3;
  }
  /* H33: oracle 0x8006C6C8-74C truncates both operands toward zero by 8 bits,
     then multiplies the shortened values.  This is intentionally not fixedmult. */
  angularStepTime = AIPhysic_iTime;
  if (angularStepTime < 0) {
    angularStepTime = nfs4_mips_addu_s32(angularStepTime,0xff);
  }
  angularStepTime = nfs4_mips_sra_s32(angularStepTime,8);
  angularStep = (carObj->angularAcc).x;
  if (angularStep < 0) {
    angularStep = nfs4_mips_addu_s32(angularStep,0xff);
  }
  angularStep = nfs4_mips_sra_s32(angularStep,8);
  (carObj->N).angularVel.x = nfs4_mips_addu_s32(
      (carObj->N).angularVel.x,nfs4_mips_mult_s32(angularStep,angularStepTime));
  angularStep = (carObj->angularAcc).y;
  if (angularStep < 0) {
    angularStep = nfs4_mips_addu_s32(angularStep,0xff);
  }
  angularStep = nfs4_mips_sra_s32(angularStep,8);
  (carObj->N).angularVel.y = nfs4_mips_addu_s32(
      (carObj->N).angularVel.y,nfs4_mips_mult_s32(angularStep,angularStepTime));
  angularStep = (carObj->angularAcc).z;
  if (angularStep < 0) {
    angularStep = nfs4_mips_addu_s32(angularStep,0xff);
  }
  angularStep = nfs4_mips_sra_s32(angularStep,8);
  (carObj->N).angularVel.z = nfs4_mips_addu_s32(
      (carObj->N).angularVel.z,nfs4_mips_mult_s32(angularStep,angularStepTime));
  return;
}

/* ---- AIPhysic_CalculateRampedDesiredLatPos__FP8Car_tObj9eRampType  [@0x8006c768] ---- */
void AIPhysic_CalculateRampedDesiredLatPos(Car_tObj *carObj,eRampType rampType)
{
  int rampSpeed;
  bool bVar1;
  int iVar2;
  int iVar3;
  
  if (rampType == 1) {
    carObj->rampDesiredLatPos = carObj->desiredLatPos;
  }
  else {
    AIWorld_CalculateDeltaRoadYaw(carObj);
    rampSpeed = AIPhysic_elapsedTime * 0x3333;
    iVar3 = carObj->roadPosition;
    if ((carObj->desiredLatPos < iVar3) && (iVar3 < carObj->rampDesiredLatPos + -0x10000)) {
      carObj->rampDesiredLatPos = iVar3;
    }
    else {
      iVar3 = carObj->roadPosition;
      if ((carObj->rampDesiredLatPos + 0x10000 < iVar3) && (iVar3 < carObj->desiredLatPos)) {
        carObj->rampDesiredLatPos = iVar3;
      }
    }
    iVar3 = carObj->rampDesiredLatPos;
    iVar2 = carObj->desiredLatPos;
    if (iVar3 < iVar2) {
      iVar3 = iVar3 + rampSpeed;
      carObj->rampDesiredLatPos = iVar3;
      bVar1 = iVar2 < iVar3;
    }
    else {
      if (iVar3 <= iVar2) {
        return;
      }
      iVar2 = carObj->desiredLatPos;
      iVar3 = iVar3 - rampSpeed;
      carObj->rampDesiredLatPos = iVar3;
      bVar1 = iVar3 < iVar2;
    }
    if (bVar1) {
      carObj->rampDesiredLatPos = iVar2;
    }
  }
  return;
}

/* ---- AIPhysic_HitWallCheck__FP8Car_tObj  [@0x8006c870] ---- */
int AIPhysic_HitWallCheck(Car_tObj *carObj)
{
  int onRoad;
  u_char bVar1;
  
  bVar1 = *(u_char *)((carObj->N).simRoadInfo.slice * 0x20 + (int)BWorldSm_slices + 0x1d);
  if ((int)(7 - (u_int)(bVar1 >> 4)) <= carObj->laneIndex &&
      carObj->laneIndex <= (int)((bVar1 & 0xf) + 6)) {
    return 0;
  }
  if (carObj->driveDirection == -1) {
    /* @0x8006C8D4-E8: timeOffRoad += AIPhysic_elapsedTime. m2c folded the addition into a self-assign,
     * so timeOffRoad never accumulated -> the if(timeOffRoad < 9) check always took the on-road path
     * and the AI never reacted to being stuck off-road (M21). */
    carObj->timeOffRoad = carObj->timeOffRoad + AIPhysic_elapsedTime;
  }
  else {
    carObj->timeOffRoad = 0;
  }
  if (carObj->timeOffRoad < 9) {
    return (0xd999 < (carObj->N).roadMatrix.m[4]) ^ 1;
  }
  return 1;
}

/* ---- AIPhysic_ProcessBarrierCollision__FP8Car_tObj  [@0x8006c920] ---- */
void AIPhysic_ProcessBarrierCollision(Car_tObj *carObj)
{
  int iVar1;
  
  if ((carObj->carFlags & 4U) == 0) {
    iVar1 = carObj->currentSpeed;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    if (iVar1 < 0xa0000) {
      AIPhysic_ChangeDirection(carObj,0x60);
    }
  }
  return;
}

/* ---- AIPhysic_ProcessCollision__FP8Car_tObj  [@0x8006c974] ---- */
void AIPhysic_ProcessCollision(Car_tObj *carObj)
{
  int reverseTime;
  int iVar1;
  
  if ((0xd999 < (carObj->N).collision.impulse) &&
     ((carObj->N).collision.otherObj != (BO_tNewtonObj *)0x0)) {
    iVar1 = carObj->currentSpeed;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    if (iVar1 < 0xa0000) {
      iVar1 = 0x60;
      if ((carObj->carFlags & 0x10U) != 0) {
        iVar1 = 0xa0;
      }
      AIPhysic_ChangeDirection(carObj,iVar1);
    }
  }
  return;
}

/* ---- AIPhysic_ChangeDirection__FP8Car_tObji  [@0x8006c9f0] ---- */
void AIPhysic_ChangeDirection(Car_tObj *carObj,int time)
{
  int iVar1;
  int iVar2;
  
  iVar2 = carObj->driveDirection;
  if (iVar2 == -1) {
    iVar2 = 1;
    if (carObj->driveDirectionReverseTime / 2 < simGlobal.gameTicks - carObj->driveDirectionTimer)
    goto LAB_8006ca90;
    iVar2 = carObj->driveDirection;
  }
  if (iVar2 != 1) {
    return;
  }
  if (simGlobal.gameTicks - carObj->driveDirectionTimer <= carObj->driveDirectionReverseTime / 2) {
    return;
  }
  iVar1 = carObj->currentSpeed;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  iVar2 = -1;
  if (0x13ffff < iVar1) {
    return;
  }
LAB_8006ca90:
  carObj->driveDirection = iVar2;
  iVar2 = simGlobal.gameTicks;
  carObj->driveDirectionReverseTime = time;
  carObj->driveDirectionTimer = iVar2;
  return;
}

/* ---- AIPhysic_CheckForGripReduction__FP8Car_tObj  [@0x8006caa8] ---- */
void AIPhysic_CheckForGripReduction(Car_tObj *carObj)
{
  int randVal;
  int perTickProb;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = carObj->gripFactor;
  if (iVar4 < 0x10000) {
    iVar4 = iVar4 + AIPhysic_elapsedTime * carObj->personality->gripLossRecoveryPerTick;
    iVar2 = (carObj->N).collision.lastTime;
    carObj->gripFactor = iVar4;
    if ((simGlobal.gameTicks - iVar2 < 0x40) &&
       ((carObj->N).collision.lastOtherObj == (BO_tNewtonObj *)0x0)) {
      carObj->gripFactor = 0x10000;
    }
    else {
      iVar3 = carObj->personality->gripLossMinFactor;
      iVar2 = -iVar3;
      iVar1 = iVar2 + 0x10000;
      if (iVar1 < 0) {
        iVar1 = iVar2 + 0x10003;
      }
      if (iVar3 + (iVar1 >> 2) < iVar4) {
        carObj->gripFactor = 0x10000;
      }
    }
  }
  else if (((carObj->N).simOptz == '\0') && ((carObj->carFlags & 0x28U) != 0)) {
    iVar4 = AIWorld_CalcRoadBend(carObj,1);
    if (iVar4 < 1) {
      iVar4 = AIWorld_CalcRoadBend(carObj,1);
      iVar4 = -iVar4;
    }
    else {
      iVar4 = AIWorld_CalcRoadBend(carObj,1);
    }
    if (2000 < iVar4) {
      perTickProb = AIPhysic_elapsedTime * carObj->personality->gripLossProbPerSecond;
      randtemp = fastRandom * randSeed;
      randVal = (int)((randtemp >> 8) & 0xffff);
      fastRandom = randtemp & 0xffff;
      if (randVal < perTickProb / 32) {
        carObj->gripFactor = carObj->personality->gripLossMinFactor;
      }
    }
  }
  return;
}

/* ---- AIPhysic_StartUp__Fv  [@0x8006cc3c] ---- */
void AIPhysic_StartUp(void)
{
  return;
}

/* ---- AIPhysic_CleanUp__Fv  [@0x8006cc44] ---- */
void AIPhysic_CleanUp(void)
{
  return;
}

/* ---- AIPhysic_Reset__Fv  [@0x8006cc4c] ---- */
void AIPhysic_Reset(void)
{
  return;
}

/* ---- AIPhysic_ResetCar__FP8Car_tObj  [@0x8006cc54] ---- */
void AIPhysic_ResetCar(Car_tObj *carObj)
{
  carObj->pullOver = 0;
  carObj->blowout = 0;
  return;
}

/* ---- AIPhysic_InitCar__FP8Car_tObj  [@0x8006cc60] ---- */
void AIPhysic_InitCar(Car_tObj *carObj)
{
  int d;
  int deceleration;
  int invDeceleration;
  int brakeTableLoop;
  int brakeDistanceMeters;
  int distance;
  int sIndex;
  AIPhysic_BrakeInfo *pAVar1;
  int iVar2;
  int iVar3;
  u_int uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = carObj->carFlags;
  if ((uVar4 & 2) != 0) {
    iVar5 = 0xc0000;
    if ((uVar4 & 0x28) != 0) {
      iVar5 = 0xb0000;
    }
    iVar3 = carObj->personality->brakeMultiplier;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    iVar5 = (iVar3 >> 8) * (iVar5 >> 8);
    if ((uVar4 & 8) != 0) {
      iVar3 = AISpeeds_GetUpgradeBrakeMult(carObj->carIndex);
      if (iVar5 < 0) {
        iVar5 = iVar5 + 0xff;
      }
      if (iVar3 < 0) {
        iVar3 = iVar3 + 0xff;
      }
      iVar5 = (iVar5 >> 8) * (iVar3 >> 8);
    }
    pAVar1 = (AIPhysic_BrakeInfo *)__builtin_new(0x84);
    pAVar1->deceleration_ = iVar5;
    iVar5 = fixeddiv(0x10000,iVar5);
    for (iVar3 = 0; uVar4 = iVar3 << 0x10, iVar3 < 0x80; iVar3 = iVar3 + 1) {
      iVar2 = fixedmult(uVar4,iVar5);
      iVar2 = fixedmult(iVar2,uVar4);
      iVar2 = iVar2 / 2;
      if ((int)uVar4 < 0) {
        uVar4 = uVar4 | 0xffff;
      }
      iVar6 = (int)uVar4 >> 0x10;
      if (iVar6 < 0) {
        iVar6 = -iVar6;
      }
      if (0x7f < iVar6) {
        iVar6 = 0x80;
      }
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0x1ffff;
      }
      pAVar1->brakeTable_[iVar6] = (u_char)(iVar2 >> 0x11);
    }
    carObj->brakeInfo = pAVar1;
  }
  return;
}

/* ---- AIPhysic_DeInitCar__FP8Car_tObj  [@0x8006cdd4] ---- */
void AIPhysic_DeInitCar(Car_tObj *carObj)
{
  int dir;
  int totalDamage;
  int currentVel;
  int desiredAngVel;
  int desiredLatVel;
  int badSpeed;
  int badRoadPos;
  int currentLongAcc;
  char useCoolPhysics;
  int currentAngAcc;
  int currentLatAcc;
  int uTurn;
  int currentLatVel;
  coorddef fCPoint;
  coorddef fPoint;
  coorddef carRelative;
  
  if (((carObj->carFlags & 2U) != 0) && (carObj->brakeInfo != (AIPhysic_BrakeInfo *)0x0)) {
    __builtin_delete(carObj->brakeInfo);
    carObj->brakeInfo = (AIPhysic_BrakeInfo *)0x0;
  }
  return;
}
