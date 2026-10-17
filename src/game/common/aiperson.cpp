/* game/common/aiperson.cpp -- RECONSTRUCTED (NFS4 AI action/reaction scripting; 8 free AIScript_* fns).
 *   Player-action submission + reaction-table processing. SYM-v3 locals; vs disasm-v2.txt.
 *   NOT original source; SYM-faithful, recompilable C++.
 */
#include "../../nfs4_types.h"
#include "aiperson_externs.h"


/* ---- aiperson.obj-owned globals (.bss zero) ---- */
int          AIPerson_blockMaxDistance[4] = { 2293760, 3276800, 5242880, 7864320 };   /* @0x8010d5cc */
int          AIPerson_blockMinDistance[4] = { 2293760, 1310720, 655360, 0 };   /* @0x8010d5dc */
int          AIPerson_oncomingLookAhead[4] = { 5898240, 10485760, 13762560, 16384000 };   /* @0x8010d5ec */
int          AIPerson_laneSwerve[4][4] = { 0, 0, 0, 0, -65536, -32768, 0, 65536, -131072, 0, 65536, 131072, -196608, -98304, 98304, 196608 };   /* @0x8010d5fc */
int          AIPerson_swerveChangeProb[4] = { 400, 100, 40, 10 };   /* @0x8010d63c */
int          AIPerson_brakeMultiplier[4] = { 55705, 65536, 78643, 88473 };   /* @0x8010d64c */
int          AIPerson_attackActivationHits[4] = { 10000, 15, 40, 40 };   /* @0x8010d65c */
int          AIPerson_attackTimes[4] = { 0, 96, 320, 1280 };   /* @0x8010d66c */
int          AIPerson_fishtailAngles[4] = { 35, 40, 45, 50 };   /* @0x8010d67c */
int          AIPerson_gripLossProbPerSecond[4] = { 32768, 32768, 32768, 0 };   /* @0x8010d68c */
int          AIPerson_gripLossMinFactor[4] = { 19660, 26214, 32768, 64880 };   /* @0x8010d69c */
int          AIPerson_gripLossRecoveryPerTick[4] = { 71, 61, 40, 65536 };   /* @0x8010d6ac */
int          AIPerson_minimumWipeOutTicks[5] = { 65536, 4096, 2048, 1024, 1024 };   /* @0x8010d6bc */
int          AIPerson_randomWipeOutTicks[5] = { 65535, 8191, 4095, 2047, 2047 };   /* @0x8010d6d0 */
u_int        AIPerson_rearEndProbMask[4] = { 65535u, 768u, 1792u, 512u };   /* @0x8010d6e4 */
u_int        AIPerson_smackProbMask[4] = { 65535u, 768u, 1792u, 1536u };   /* @0x8010d6f4 */
int          AIPerson_bestLineAbilities[4] = { 19660, 32768, 52428, 65536 };   /* @0x8010d704 */
int          AIPerson_glueTable[21];   /* @0x8010d714  (bss(zero)) */
AIPerson_t   AIPerson_PersonalityData[9];   /* @0x8010d768  (bss(zero)) */
AIScript_tReactionDetails AIPerson_ScriptData[9][7];   /* @0x8010da5c  (bss(zero)) */


/* ---- intra-TU forward declarations ---- */
void AIPerson_LoadGridAndSetPersonalityIndexes(void);
void AIPerson_SetPersonality(Car_tObj *carObj,int personalityIndex);
void AIPerson_SetPersonalityPointers(void);
void AIPerson_LoadPersonalityData(Udff_tInfo *handle);
void AIPerson_LoadScriptData(Udff_tInfo *handle);
void AIPerson_LoadGlue(Udff_tInfo *handle);
void AIPerson_Startup(void);
void AIPerson_Cleanup(void);


/* ---- AIPerson_LoadGridAndSetPersonalityIndexes__Fv  [@0x800689e8] ---- */
void AIPerson_LoadGridAndSetPersonalityIndexes(void)
{
  GameSetup_tCarData *pGVar1;
  int iVar2;
  int iVar3;
  Car_tObj **ppCVar4;
  GameSetup_tData *pGVar5;
  
  iVar2 = Cars_gNumCars;
  iVar3 = 0;
  if (0 < Cars_gNumCars) {
    pGVar5 = &GameSetup_gData;
    ppCVar4 = Cars_gList;
    do {
      pGVar1 = pGVar5->carInfo;
      pGVar5 = (GameSetup_tData *)((pGVar5->controllerData).shockImpact + 1);
      iVar3 = iVar3 + 1;
      (*ppCVar4)->personalityIndex = pGVar1->Personality;
      ppCVar4 = ppCVar4 + 1;
    } while (iVar3 < iVar2);
  }
  return;
}

/* ---- AIPerson_SetPersonality__FP8Car_tObji  [@0x80068a34] ---- */
void AIPerson_SetPersonality(Car_tObj *carObj,int personalityIndex)
{
  int iVar1;
  
  if ((carObj->carFlags & 4U) == 0) {
    strcpy(carObj->carInfo->driver,GameSetup_gPersonalityNames[0] + personalityIndex * 8);
  }
  iVar1 = personalityIndex % 5;
  carObj->personalityIndex = iVar1;
  carObj->personality = AIPerson_PersonalityData + iVar1;
  /* byte-match backport: ScriptData is [9][7]; personality iVar1 selects row iVar1
   * (iVar1*56 bytes). The prior `+ iVar1 * 7` overshot 7x (iVar1*392). */
  AIScript_Assign(&carObj->script,AIPerson_ScriptData + iVar1);
  return;
}

/* ---- AIPerson_SetPersonalityPointers__Fv  [@0x80068afc] ---- */
void AIPerson_SetPersonalityPointers(void)
{
  Car_tObj *carObj;
  Car_tObj **ppCVar1;
  int iVar2;
  
  ppCVar1 = Cars_gList;
  for (iVar2 = 0; iVar2 < Cars_gNumCars; iVar2 = iVar2 + 1) {
    carObj = *ppCVar1;
    ppCVar1 = ppCVar1 + 1;
    AIPerson_SetPersonality(carObj,carObj->personalityIndex);
  }
  return;
}

/* ---- AIPerson_LoadPersonalityData__FP10Udff_tInfo  [@0x80068b60] ---- */
void AIPerson_LoadPersonalityData(Udff_tInfo *handle)
{
  int local_40;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  Udff_GetInt(handle);

  local_40 = 0;
  while (1) {
    if (local_40 >= 9) {
      break;
    }
    iVar1 = Udff_GetInt(handle);
    iVar2 = Udff_GetInt(handle);
    iVar3 = Udff_GetInt(handle);
    iVar4 = Udff_GetInt(handle);
    iVar5 = Udff_GetInt(handle);
    iVar6 = Udff_GetInt(handle);
    iVar7 = Udff_GetInt(handle);
    Udff_GetInt(handle);
    iVar8 = Udff_GetInt(handle);
    iVar9 = Udff_GetInt(handle);
    iVar10 = Udff_GetInt(handle);
    iVar11 = Udff_GetInt(handle);
    iVar12 = Udff_GetInt(handle);
    iVar13 = Udff_GetInt(handle);
    AIPerson_PersonalityData[local_40].blockMaxDistance = AIPerson_blockMaxDistance[iVar1];
    AIPerson_PersonalityData[local_40].blockMinDistance = AIPerson_blockMinDistance[iVar2];
    AIPerson_PersonalityData[local_40].oncomingLookAhead = AIPerson_oncomingLookAhead[iVar3];
    AIPerson_PersonalityData[local_40].laneSwerve[0] = AIPerson_laneSwerve[iVar4][0];
    AIPerson_PersonalityData[local_40].laneSwerve[1] = AIPerson_laneSwerve[iVar4][1];
    AIPerson_PersonalityData[local_40].laneSwerve[2] = AIPerson_laneSwerve[iVar4][2];
    AIPerson_PersonalityData[local_40].laneSwerve[3] = AIPerson_laneSwerve[iVar4][3];
    AIPerson_PersonalityData[local_40].swerveChangeProb = AIPerson_swerveChangeProb[iVar4];
    AIPerson_PersonalityData[local_40].brakeMultiplier = AIPerson_brakeMultiplier[iVar5];
    AIPerson_PersonalityData[local_40].attackActivationHits = AIPerson_attackActivationHits[iVar6];
    AIPerson_PersonalityData[local_40].attackTime = AIPerson_attackTimes[iVar6];
    AIPerson_PersonalityData[local_40].fishtailAngle = AIPerson_fishtailAngles[iVar7];
    AIPerson_PersonalityData[local_40].minimumBetweenWipeoutTicks = AIPerson_minimumWipeOutTicks[iVar8 + GameSetup_gData.Weather];
    AIPerson_PersonalityData[local_40].randomBetweenWipeoutTicks = AIPerson_randomWipeOutTicks[iVar8 + GameSetup_gData.Weather];
    AIPerson_PersonalityData[local_40].gripLossProbPerSecond = AIPerson_gripLossProbPerSecond[iVar9];
    AIPerson_PersonalityData[local_40].gripLossMinFactor = AIPerson_gripLossMinFactor[iVar9];
    AIPerson_PersonalityData[local_40].gripLossRecoveryPerTick = AIPerson_gripLossRecoveryPerTick[iVar9];
    AIPerson_PersonalityData[local_40].bestLineAbility = AIPerson_bestLineAbilities[iVar10];
    AIPerson_PersonalityData[local_40].rearBumpProbMask = AIPerson_rearEndProbMask[iVar11];
    AIPerson_PersonalityData[local_40].smackProbMask = AIPerson_smackProbMask[iVar12];
    AIPerson_PersonalityData[local_40].copCollisionFirmness = iVar13;
    local_40++;
  }
  return;
}

/* ---- AIPerson_LoadScriptData__FP10Udff_tInfo  [@0x80068ea4] ---- */
void AIPerson_LoadScriptData(Udff_tInfo *handle)
{
  int perLoop;
  int actionLoop;
  int reactionLoop;
  int byteOffset;
  int actionMul;
  int byteOff2;
  int scriptBase;
  char *addr;
  int iVar1;

  Udff_GetInt(handle);
  perLoop = 0;
  scriptBase = (int)AIPerson_ScriptData;
  byteOffset = 0;
 loop_1:
  actionLoop = 0;
  if (perLoop < 9) {
    do {                              /* permuter-found while(0) scope: pin-free 100% */
     loop_2:
      reactionLoop = 0;
      if (actionLoop < 7) {
        actionMul = actionLoop * 8;
        byteOff2 = byteOffset;
        do {
          iVar1 = Udff_GetInt(handle);
          addr = (char *)(reactionLoop + actionMul + byteOff2 + scriptBase);
          addr[0] = (char)iVar1;
          addr[4] = (char)Udff_GetInt(handle);
          reactionLoop = reactionLoop + 1;
        } while (reactionLoop < 4);
        actionLoop = actionLoop + 1;
        goto loop_2;
      }
      byteOffset = byteOffset + 0x38;
    } while (0);
    perLoop = perLoop + 1;
    goto loop_1;
  }
  return;
}

/* ---- AIPerson_LoadGlue__FP10Udff_tInfo  [@0x80068f80] ---- */
void AIPerson_LoadGlue(Udff_tInfo *handle)
{
  int iVar1;
  int b;
  int *piVar2;
  int iVar3;
  int cmp;

  Udff_GetInt(handle);
  Udff_GetBuffer(handle,(char *)AIPerson_glueTable,0x54);
  if ((Cars_gNumCopCars != 0) &&
     (((GameSetup_gData.raceType != 1 && (GameSetup_gData.raceType != 5)) ||
      ((((*(int *)((char *)Cars_gHumanRaceCarList[0] + 0x260)) & 0x200) == 0 &&
       ((Cars_gNumHumanRaceCars != 2 || (((*(int *)((char *)Cars_gHumanRaceCarList[1] + 0x260)) & 0x200) == 0)))))))) {
    iVar3 = 0;
    piVar2 = AIPerson_glueTable;
    do {
      iVar1 = *piVar2;
      cmp = 0x10000;
      if (cmp < iVar1) {
        b = 0x12666;
        goto LAB_8006905c;
      }
      cmp = 0xffff;
      if (cmp < iVar1) goto LAB_skip;
      b = 0xd999;
LAB_8006905c:
      iVar1 = fixedmult(iVar1,b);
      *piVar2 = iVar1;
LAB_skip:
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 0x15);
  }
  return;
}

/* ---- AIPerson_Startup__Fv  [@0x8006908c] ---- */
void AIPerson_Startup(void)
{
  Udff_tInfo *pUVar1;
  const char *fmt;
  char acStack_80 [112];
  
  AIPerson_LoadGridAndSetPersonalityIndexes();
  sprintf(acStack_80,"%sprsonal.bin",Paths_Paths[2]);   /* byte-match backport: pass the %s path prefix (was missing) */
  pUVar1 = Udff_Opena(acStack_80,(char *)0x0,1);
  AIPerson_LoadPersonalityData(pUVar1);
  Udff_Close(pUVar1);
  sprintf(acStack_80,"%sscripts.bin",Paths_Paths[2]);
  pUVar1 = Udff_Opena(acStack_80,(char *)0x0,1);
  AIPerson_LoadScriptData(pUVar1);
  Udff_Close(pUVar1);
  if (((GameSetup_gData.raceType == 1) || (GameSetup_gData.raceType == 5)) &&
     ((((*(int *)((char *)Cars_gHumanRaceCarList[0] + 0x260)) & 0x200) != 0 ||
      ((Cars_gNumHumanRaceCars == 2 && (((*(int *)((char *)Cars_gHumanRaceCarList[1] + 0x260)) & 0x200) != 0)))))) {
    fmt = "%sbtcglue.bin";
  }
  else if (((u_int)GameSetup_gData.raceType < 2) && (Cars_gNumAIRaceCars == 1)) {
    fmt = "%shhglue.bin";
  }
  else {
    fmt = "%sglue.bin";
  }
  sprintf(acStack_80,fmt,Paths_Paths[2]);
  pUVar1 = Udff_Opena(acStack_80,(char *)0x0,1);
  AIPerson_LoadGlue(pUVar1);
  Udff_Close(pUVar1);
  AIPerson_SetPersonalityPointers();
  return;
}

/* ---- AIPerson_Cleanup__Fv  [@0x80069230] ---- */
void AIPerson_Cleanup(void)
{
  
  return;
}
