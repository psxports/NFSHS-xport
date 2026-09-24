/* game/common/newton.cpp -- RECONSTRUCTED (NFS4 PSX Newton physics integrator; C++ TU)
 *   32 fns: ground elevation/normal ray-cast, road geometry, slice orientation, rot/vel
 *   integration @32/64Hz, ground-shadow matrices, barrier/spike collision, gravity.
 *   GTE-free (fixed-point + eaclib math). Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "newton_externs.h"

/* ---- newton.obj file-statics.  The first three are initialized .data, not
 * BSS: the exact image bytes live at 0x8011401C..0x80114133.  In particular,
 * Newton_FindGroundElevationAndNormal MIPS 0x800A071C..0x800A07C8 indexes
 * wheel impactCompression through swap[].  dummy_124/dummy_133 are cfront
 * struct-pass scratch temporaries (coorddef out-params). ---- */
static int divTable[50] = {
  65536,66052,66576,67108,67650,68200,68759,69327,69905,70492,
  71089,71697,72315,72944,73584,74235,74898,75573,76260,76959,
  77672,78398,79137,79891,80659,81442,82241,83055,83886,84733,
  85598,86480,87381,88301,89240,90200,91180,92182,93206,94254,
  95325,96420,97541,98689,99864,101067,102300,103563,104857,106184
};
static short fudgeTable[32] = {
  0,20,36,44,30,44,52,46,36,20,6,-20,-30,-16,0,18,
  26,38,52,40,30,15,0,-20,-32,-16,-8,8,16,20,16,8
};
static int swap[4] = {0,1,2,3};
static BWorldSm_Pos testSimRoadInfo;
static BWorldSm_Pos newtestSimRoadInfo;
static coorddef     dummy_124;
static coorddef     dummy_133;

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void Newton_AddDamageZone(BO_tNewtonObj *newtonObj,int impulse,int zone,int type);
void Newton_FindClosestQuad(BO_tNewtonObj *n);
int Newton_CalculateSliceYaw(int slice);
void Newton_UpdateRoadGeometry(BO_tNewtonObj *n);
int Newton_FindGroundElevationGeneral(coorddef *point,coorddef *normal,coorddef *pointOnQuad);
int Newton_FindGroundElevationRough(coorddef *point,coorddef *normal,coorddef *pointOnQuad);
int Newton_FindGroundElevationAndNormalFast(BO_tNewtonObj *newtonObj,coorddef *normal);
int Newton_FindGroundElevationAndNormal(BO_tNewtonObj *newtonObj,coorddef *normal);
void Newton_LimitCarsToDrivableDist(BO_tNewtonObj *newtonObj);
int Newton_CalcPerpenHeightOfLowestPointFromGround(BO_tNewtonObj *newtonObj,coorddef *normal,coorddef *samplePoint);
int Newton_CalcPerpenHeightOfCenterPointFromGround(BO_tNewtonObj *newtonObj,coorddef *normal,coorddef *samplePoint);
void Newton_CalcDistToClosestPlayerCar(BO_tNewtonObj *n);
void Newton_UpdateRoadInfo(BO_tNewtonObj *n);
void Newton_CopyRoadMatrixToOrientMat(BO_tNewtonObj *n,int backwards);
void Newton_CopyRoadMatrixToShadowMat(BO_tNewtonObj *n,int backwards);
void Newton_SetInitialSlicePositionOrientationEtc(BO_tNewtonObj *n,int slice,coorddef *offset,int direction);
void Newton_QDUpdateVel(BO_tNewtonObj *newtonObj);
void Newton_QDUpdateRot64Hz(BO_tNewtonObj *newtonObj);
void Newton_QDUpdateRot32Hz(BO_tNewtonObj *newtonObj);
void Newton_CalculateGroundShadowMatrix(BO_tNewtonObj *newtonObj,coorddef *normal,int orientToGround);
void Newton_CalcRealShadowCoordinates(Car_tObj *carObj,int currentTick);
void Newton_CheckForSpikeBelts(BO_tNewtonObj *newtonObj);
void Newton_DoPostBarrierCollisionHandling(BO_tNewtonObj *newtonObj,coorddef normal);
void Newton_GenerateVector(int type,coorddef *vector,BWorldSm_Pos *testSimRoadInfo);
void Newton_TestForUndrivableSurfaces(BO_tNewtonObj *newtonObj);
void Newton_LimitAngularVelocity(BO_tNewtonObj *newtonObj);
void Newton_ApplyTheLawOfGravity(Car_tObj *newtonObj);
int Newton_CalculateRoadPositionFromSliceAndPosition(int slice,coorddef *position,matrixtdef *matrix);
int Newton_CalculateRoadPosition(BO_tNewtonObj *newtonObj);


/* ---- Newton_AddDamageZone__FP13BO_tNewtonObjiii  [NEWTON.CPP:50-216] SLD-VERIFIED ---- */
void Newton_AddDamageZone(BO_tNewtonObj *newtonObj,int impulse,int zone,int type)

{
  Car_tObj *carObj = (Car_tObj *)newtonObj;
  int temp;
  int iVar1;
  int iVar2;
  void *pvVar3;
  u_int uVar4;
  u_int uVar5;
  int iVar6;
  int imp;
  int iVar7;
  int iVar8;
  int iVar9;
  u_int uVar10;
  int intensity;
  int zMult;
  u_int uVar11;
  int yMult;
  u_int b;
  int xMult;
  u_int uVar12;
  matrixtdef transposeMat;
  
  iVar1 = Force_IsForceOn((Car_tObj *)newtonObj);
  if (iVar1 != 0) {
    Force_HitWall((newtonObj->collision).impulse);
  }
  if (GameSetup_gData.Damage != 0) {
    iVar1 = 0x640000;
    if (impulse / 2 < 0x640001) {
      iVar1 = impulse / 2;
    }
    if ((carObj->carFlags & 0x200U) != 0) {
      iVar1 = iVar1 / 2;
    }
    if (iVar1 < newtonObj->damage[zone]) {
      iVar1 = newtonObj->damage[zone];
    }
    newtonObj->damage[zone] = iVar1;
    if (zone < 8) {
      if (zone == 0) {
        iVar1 = (newtonObj->damage[0] + newtonObj->damage[2]) / 2;
        if (iVar1 < newtonObj->damage[1]) {
          iVar1 = newtonObj->damage[1];
        }
        iVar2 = newtonObj->damage[0];
        iVar7 = newtonObj->damage[6];
        newtonObj->damage[1] = iVar1;
      }
      else {
        if (zone == 1) {
          iVar1 = (newtonObj->damage[7] + newtonObj->damage[1]) / 2;
          if (iVar1 < newtonObj->damage[0]) {
            iVar1 = newtonObj->damage[0];
          }
          iVar2 = newtonObj->damage[1];
          iVar7 = newtonObj->damage[3];
          newtonObj->damage[0] = iVar1;
          iVar1 = (iVar2 + iVar7) / 2;
          if (iVar1 < newtonObj->damage[2]) {
            iVar1 = newtonObj->damage[2];
          }
          newtonObj->damage[2] = iVar1;
          goto Newton_AddDmgZ_typeSet;
        }
        if (zone != 6) {
          if (zone == 7) {
            iVar1 = (newtonObj->damage[7] + newtonObj->damage[1]) / 2;
            if (iVar1 < newtonObj->damage[0]) {
              iVar1 = newtonObj->damage[0];
            }
            iVar2 = newtonObj->damage[5];
            iVar7 = newtonObj->damage[7];
            newtonObj->damage[0] = iVar1;
            iVar1 = (iVar2 + iVar7) / 2;
            if (iVar1 < newtonObj->damage[6]) {
              iVar1 = newtonObj->damage[6];
            }
            newtonObj->damage[6] = iVar1;
          }
          else {
            iVar1 = (iVar1 + newtonObj->damage[zone + 2]) / 2;
            if (iVar1 < newtonObj->damage[zone + 1]) {
              iVar1 = newtonObj->damage[zone + 1];
            }
            newtonObj->damage[zone + 1] = iVar1;
            iVar1 = (newtonObj->damage[zone] + newtonObj->damage[zone + -2]) / 2;
            if (iVar1 < newtonObj->damage[zone + -1]) {
              iVar1 = newtonObj->damage[zone + -1];
            }
            newtonObj->damage[zone + -1] = iVar1;
          }
          goto Newton_AddDmgZ_typeSet;
        }
        iVar1 = (newtonObj->damage[4] + newtonObj->damage[6]) / 2;
        if (iVar1 < newtonObj->damage[5]) {
          iVar1 = newtonObj->damage[5];
        }
        iVar2 = newtonObj->damage[0];
        iVar7 = newtonObj->damage[6];
        newtonObj->damage[5] = iVar1;
      }
      iVar1 = (iVar2 + iVar7) / 2;
      if (iVar1 < newtonObj->damage[7]) {
        iVar1 = newtonObj->damage[7];
      }
      newtonObj->damage[7] = iVar1;
    }
  }
Newton_AddDmgZ_typeSet:
  uVar12 = 0x20000;
  if (type != 0) {
    b = 0;
    uVar11 = 0x20000;
    if (impulse < 0x5a0001) {
      if (impulse < 0) {
        impulse = impulse + 0x3f;
      }
      iVar1 = impulse >> 6;
      if (0x8000 < iVar1) {
        iVar1 = 0x8000;
      }
    }
    else {
      if (impulse < 0) {
        impulse = impulse + 3;
      }
      iVar2 = impulse >> 2;
      iVar1 = newtonObj->objAltitude;
      newtonObj->flightTime = 1;
      (newtonObj->collision).lastCollision = 0;
      carObj->collision.smoking = 1;
      if (iVar1 < 0x20000) {
        (newtonObj->position).y = (newtonObj->position).y + 0x10000;
      }
      iVar7 = (newtonObj->linearVel).y + iVar2 / 3;
      iVar1 = 0xc0000;
      if (iVar7 < 0xc0001) {
        iVar1 = iVar7;
      }
      (newtonObj->linearVel).y = iVar1;
      iVar1 = iVar2;
      if (iVar2 < 0) {
        iVar1 = iVar2 + 0x1f;
      }
      iVar1 = iVar1 >> 5;
      if (0x9999 < iVar1) {
        iVar1 = 0x9999;
      }
      pvVar3 = BWorldSm_TunnelFlagSm(&newtonObj->simRoadInfo);
      if ((pvVar3 != (void *)0x0) && (0x90000 < (newtonObj->linearVel).y)) {
        (newtonObj->linearVel).y = 0x90000;
      }
      if (0x140000 < iVar2) {
        uVar12 = (fastRandom * randSeed & 0xffff) * randSeed;
        uVar11 = (uVar12 & 0xffff) * randSeed;
        uVar10 = (fastRandom * randSeed & 0xffff00) >> 8;
        randtemp = (uVar11 & 0xffff) * randSeed;
        uVar4 = (uVar12 & 0xffff00) >> 8;
        b = uVar4 * 3;
        uVar5 = (uVar11 & 0xffff00) >> 8;
        uVar11 = uVar5 * 3;
        fastRandom = randtemp & 0xffff;
        uVar12 = uVar10 * 4;
        if ((randtemp & 0xffff00) >> 8 < 0x3333) {
          iVar1 = -iVar1;
        }
        if (uVar12 + b + uVar11 < 0x40000) {
          if (uVar12 < 0x10000) {
            uVar12 = uVar10 << 3;
          }
          if (b < 0x10000) {
            b = uVar4 * 6;
          }
          if (uVar11 < 0x10000) {
            uVar11 = uVar5 * 6;
          }
        }
      }
      if (type == 2) {
        uVar12 = uVar12 << 1;
        b = b << 1;
        uVar11 = uVar11 << 1;
      }
    }
    iVar2 = fixedmult((newtonObj->angularVel).x,(newtonObj->orientMat).m[0]);
    iVar7 = fixedmult((newtonObj->angularVel).y,(newtonObj->orientMat).m[1]);
    iVar6 = fixedmult((newtonObj->angularVel).z,(newtonObj->orientMat).m[2]);
    iVar8 = (newtonObj->angularVel).x;
    iVar9 = (newtonObj->orientMat).m[3];
    carObj->angularVel_ch.x = iVar2 + iVar7 + iVar6;
    iVar2 = fixedmult(iVar8,iVar9);
    iVar7 = fixedmult((newtonObj->angularVel).y,(newtonObj->orientMat).m[4]);
    iVar6 = fixedmult((newtonObj->angularVel).z,(newtonObj->orientMat).m[5]);
    iVar8 = (newtonObj->angularVel).x;
    iVar9 = (newtonObj->orientMat).m[6];
    carObj->angularVel_ch.y = iVar2 + iVar7 + iVar6;
    iVar2 = fixedmult(iVar8,iVar9);
    iVar7 = fixedmult((newtonObj->angularVel).y,(newtonObj->orientMat).m[7]);
    iVar6 = fixedmult((newtonObj->angularVel).z,(newtonObj->orientMat).m[8]);
    carObj->angularVel_ch.z = iVar2 + iVar7 + iVar6;
    if ((u_int)zone < 3) {
      iVar2 = fixedmult(iVar1,uVar12);
      iVar2 = carObj->angularVel_ch.x - iVar2 / 2;
    }
    else {
      iVar2 = fixedmult(iVar1,uVar12);
      iVar2 = carObj->angularVel_ch.x + iVar2 / 2;
    }
    carObj->angularVel_ch.x = iVar2;
    if (zone - 2U < 3) {
      iVar2 = fixedmult(iVar1,b);
      carObj->angularVel_ch.y = carObj->angularVel_ch.y + iVar2 / 2;
      iVar1 = fixedmult(iVar1,uVar11);
      iVar1 = carObj->angularVel_ch.z + iVar1 / 2;
    }
    else {
      iVar2 = fixedmult(iVar1,b);
      carObj->angularVel_ch.y = carObj->angularVel_ch.y - iVar2 / 2;
      iVar1 = fixedmult(iVar1,uVar11);
      iVar1 = carObj->angularVel_ch.z - iVar1 / 2;
    }
    carObj->angularVel_ch.z = iVar1;
    transpose(&newtonObj->orientMat,&transposeMat);
    iVar1 = fixedmult(carObj->angularVel_ch.x,transposeMat.m[0]);
    iVar2 = fixedmult(carObj->angularVel_ch.y,transposeMat.m[1]);
    iVar7 = fixedmult(carObj->angularVel_ch.z,transposeMat.m[2]);
    iVar6 = carObj->angularVel_ch.x;
    (newtonObj->angularVel).x = iVar1 + iVar2 + iVar7;
    iVar1 = fixedmult(iVar6,transposeMat.m[3]);
    iVar2 = fixedmult(carObj->angularVel_ch.y,transposeMat.m[4]);
    iVar7 = fixedmult(carObj->angularVel_ch.z,transposeMat.m[5]);
    iVar6 = carObj->angularVel_ch.x;
    (newtonObj->angularVel).y = iVar1 + iVar2 + iVar7;
    iVar1 = fixedmult(iVar6,transposeMat.m[6]);
    iVar2 = fixedmult(carObj->angularVel_ch.y,transposeMat.m[7]);
    iVar7 = fixedmult(carObj->angularVel_ch.z,transposeMat.m[8]);
    (newtonObj->angularVel).z = iVar1 + iVar2 + iVar7;
  }
  return;
}

/* ---- Newton_FindClosestQuad__FP13BO_tNewtonObj  [NEWTON.CPP:221-227] SLD-VERIFIED ---- */
void Newton_FindClosestQuad(BO_tNewtonObj *n)

{
  BWorldSm_FindClosestQuadRez(&n->position,&n->simRoadInfo,1)
  ;
  return;
}

/* ---- Newton_CalculateSliceYaw__Fi  [NEWTON.CPP:235-244] SLD-VERIFIED ---- */
int Newton_CalculateSliceYaw(int slice)

{
  int z2;
  int x2;
  int iVar1;
  int x1;
  int z1;
  int s;
  
  iVar1 = slice + 1;
  if (gNumSlices <= iVar1) {
    iVar1 = slice - (gNumSlices + -1);
  }
  iVar1 = intatan(BWorldSm_slices[iVar1].center[0] - BWorldSm_slices[slice].center[0],
                     BWorldSm_slices[iVar1].center[2] - BWorldSm_slices[slice].center[2]);
  return iVar1;
}

/* ---- Newton_UpdateRoadGeometry__FP13BO_tNewtonObj  [NEWTON.CPP:248-354] SLD-VERIFIED ---- */
void Newton_UpdateRoadGeometry(BO_tNewtonObj *n)

{
  int hiRez;
  int i;
  char cVar1;
  char cVar2;
  bool bVar3;
  int z2;
  Trk_NewSlice *pTVar4;
  coorddef *pcVar5;
  int x2;
  BO_tNewtonObj *pBVar6;
  int iVar7;
  int z1;
  int iVar8;
  int s;
  int r3;
  int a;
  int r5;
  int b;
  int r1;
  int a_00;
  int r6;
  int b_00;
  int r4;
  int b_01;
  int r2;
  int a_01;
  int x1;
  int slice;
  int iVar9;
  coorddef temp;
  
  if (n->active != '\0') {
    iVar9 = (int)(n->simRoadInfo).slice;
    bVar3 = 1 < n->simOptz;
    iVar8 = 0;
    if (bVar3) {
      if ((n->simRoadInfo).simQuad == (Trk_NewSimQuad *)0x0) {
        pTVar4 = BWorldSm_slices + iVar9;
        iVar8 = pTVar4->center[1];
        iVar7 = pTVar4->center[2];
        (n->roadCenterPoint).x = pTVar4->center[0];
        (n->roadCenterPoint).y = iVar8;
        (n->roadCenterPoint).z = iVar7;
      }
      else {
        iVar8 = (n->simRoadInfo).quadPts[0].y;
        iVar7 = (n->simRoadInfo).quadPts[0].z;
        (n->roadCenterPoint).x = (n->simRoadInfo).quadPts[0].x;
        (n->roadCenterPoint).y = iVar8;
        (n->roadCenterPoint).z = iVar7;
      }
    }
    else {
      (n->roadCenterPoint).z = 0;
      (n->roadCenterPoint).y = 0;
      (n->roadCenterPoint).x = 0;
      pBVar6 = n;
      for (; iVar8 < 4; iVar8 = iVar8 + 1) {
        if ((n->simRoadInfo).simQuad == (Trk_NewSimQuad *)0x0) {
          pTVar4 = BWorldSm_slices + (n->simRoadInfo).slice;
          temp.x = pTVar4->center[0];
          temp.y = pTVar4->center[1];
          temp.z = pTVar4->center[2];
        }
        else {
          temp.x = (pBVar6->simRoadInfo).quadPts[0].x;
          temp.y = (pBVar6->simRoadInfo).quadPts[0].y;
          temp.z = (pBVar6->simRoadInfo).quadPts[0].z;
        }
        (n->roadCenterPoint).x = (n->roadCenterPoint).x + temp.x;
        pBVar6 = (BO_tNewtonObj *)&(pBVar6->simRoadInfo).simRotFlag;
        (n->roadCenterPoint).y = (n->roadCenterPoint).y + temp.y;
        (n->roadCenterPoint).z = (n->roadCenterPoint).z + temp.z;
      }
      iVar8 = (n->roadCenterPoint).x;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 3;
      }
      iVar7 = (n->roadCenterPoint).y;
      (n->roadCenterPoint).x = iVar8 >> 2;
      if (iVar7 < 0) {
        iVar7 = iVar7 + 3;
      }
      iVar8 = (n->roadCenterPoint).z;
      (n->roadCenterPoint).y = iVar7 >> 2;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 3;
      }
      (n->roadCenterPoint).z = iVar8 >> 2;
    }
    pTVar4 = BWorldSm_slices;
    if (bVar3) {
      cVar1 = BWorldSm_slices[iVar9].right[2];
      cVar2 = BWorldSm_slices[iVar9].right[1];
      (n->roadMatrix).m[0] = (int)BWorldSm_slices[iVar9].right[0] << 9;
      (n->roadMatrix).m[2] = (int)cVar1 << 9;
      (n->roadMatrix).m[1] = (int)cVar2 << 9;
      cVar1 = pTVar4[iVar9].normal[2];
      cVar2 = pTVar4[iVar9].normal[1];
      (n->roadMatrix).m[3] = (int)pTVar4[iVar9].normal[0] << 9;
      (n->roadMatrix).m[5] = (int)cVar1 << 9;
      (n->roadMatrix).m[4] = (int)cVar2 << 9;
      cVar1 = pTVar4[iVar9].forward[1];
      cVar2 = pTVar4[iVar9].forward[2];
      (n->roadMatrix).m[6] = (int)pTVar4[iVar9].forward[0] << 9;
      (n->roadMatrix).m[7] = (int)cVar1 << 9;
      (n->roadMatrix).m[8] = (int)cVar2 << 9;
    }
    else if ((n->simRoadInfo).quadChanged != '\0') {
      pcVar5 = (coorddef *)BWorldSm_UNormal(&n->simRoadInfo);
      iVar8 = pcVar5->y;
      iVar7 = pcVar5->z;
      (n->roadMatrix).m[3] = pcVar5->x;
      (n->roadMatrix).m[4] = iVar8;
      (n->roadMatrix).m[5] = iVar7;
      pcVar5 = (coorddef *)BWorldSm_UForward(&n->simRoadInfo);
      iVar8 = pcVar5->y;
      iVar7 = pcVar5->z;
      (n->roadMatrix).m[6] = pcVar5->x;
      (n->roadMatrix).m[7] = iVar8;
      (n->roadMatrix).m[8] = iVar7;
      a_01 = (n->roadMatrix).m[4];
      b_00 = (n->roadMatrix).m[8];
      a_00 = (n->roadMatrix).m[3];
      a = (n->roadMatrix).m[5];
      b_01 = (n->roadMatrix).m[6];
      b = (n->roadMatrix).m[7];
      iVar8 = fixedmult(a_01,b_00);
      iVar7 = fixedmult(a,b);
      (n->roadMatrix).m[0] = iVar8 - iVar7;
      iVar8 = fixedmult(a,b_01);
      iVar7 = fixedmult(a_00,b_00);
      (n->roadMatrix).m[1] = iVar8 - iVar7;
      iVar8 = fixedmult(a_00,b);
      iVar7 = fixedmult(a_01,b_01);
      (n->roadMatrix).m[2] = iVar8 - iVar7;
    }
    iVar8 = iVar9 + 1;
    if (gNumSlices <= iVar8) {
      iVar8 = iVar9 - (gNumSlices + -1);
    }
    iVar8 = intatan(BWorldSm_slices[iVar8].center[0] - BWorldSm_slices[iVar9].center[0],
                       BWorldSm_slices[iVar8].center[2] - BWorldSm_slices[iVar9].center[2]);
    n->roadYaw = iVar8;
  }
  return;
}

/* ---- Newton_FindGroundElevationGeneral__FP8coorddefN20  [NEWTON.CPP:445-463] SLD-VERIFIED ---- */
int Newton_FindGroundElevationGeneral(coorddef *point,coorddef *normal,coorddef *pointOnQuad)

{
  int result;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int index;
  
  iVar5 = normal->y;
  if (iVar5 < 0x9eb9) {
    iVar4 = normal->x;
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xff;
    }
    iVar1 = *((int *)point) - pointOnQuad->x;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xff;
    }
    iVar3 = normal->z;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    iVar2 = ((int *)point)[2] - pointOnQuad->z;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar5 = fixeddiv(-((iVar3 >> 8) * (iVar2 >> 8)) - (iVar4 >> 8) * (iVar1 >> 8),iVar5);
  }
  else {
    iVar4 = normal->x;
    if (iVar4 < 0) {
      iVar4 = iVar4 + 0xff;
    }
    iVar1 = *((int *)point) - pointOnQuad->x;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0xff;
    }
    iVar3 = normal->z;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    iVar2 = ((int *)point)[2] - pointOnQuad->z;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar5 = fixedmult(-((iVar3 >> 8) * (iVar2 >> 8)) - (iVar4 >> 8) * (iVar1 >> 8),
                       divTable[0x10000 - iVar5 >> 9]);
  }
  return iVar5 + pointOnQuad->y;
}

/* ---- Newton_FindGroundElevationRough__FP8coorddefN20  [NEWTON.CPP:475-506] SLD-VERIFIED ---- */
int Newton_FindGroundElevationRough(coorddef *point,coorddef *normal,coorddef *pointOnQuad)

{
  int result;
  int fudgeIndex;
  int index;
  int iVar1;
  int iVar2;
  int fudgeDist;
  int iVar3;
  int iVar4;
  int i;
  int iVar5;
  int numerator;
  int fudgeHeight;
  int iVar6;
  
  iVar3 = normal->x;
  iVar6 = 0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar1 = point->x - pointOnQuad->x;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  iVar4 = normal->z;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  iVar2 = point->z - pointOnQuad->z;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  iVar5 = 0;
  iVar3 = -((iVar4 >> 8) * (iVar2 >> 8)) - (iVar3 >> 8) * (iVar1 >> 8);
  do {
    if (iVar5 == 0) {
      iVar1 = point->x;
      if (iVar1 < 0) {
        iVar1 = -iVar1;
      }
      iVar4 = point->z >> 1;
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (iVar4 < iVar1) goto FindGERough_iterReduceA;
FindGERough_iterReduceB:
      iVar4 = iVar4 + (iVar1 >> 2);
    }
    else {
      iVar4 = point->z;
      iVar1 = point->x >> 2;
      if (iVar1 < 0) {
        iVar1 = -iVar1;
      }
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if (iVar1 <= iVar4) goto FindGERough_iterReduceB;
FindGERough_iterReduceA:
      iVar4 = iVar1 + (iVar4 >> 2);
    }
    iVar4 = iVar4 >> 0xf;
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    iVar1 = iVar4;
    if (iVar4 < 0) {
      iVar1 = iVar4 + 0x1f;
    }
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + fudgeTable[iVar4 + (iVar1 >> 5) * -0x20] * 0x80;
    if (1 < iVar5) {
      iVar1 = normal->y;
      if (iVar1 < 0x9eb9) {
        iVar3 = fixeddiv(iVar3,iVar1);
      }
      else {
        iVar3 = fixedmult(iVar3,divTable[0x10000 - iVar1 >> 9]);
      }
      return iVar3 + pointOnQuad->y + iVar6;
    }
  } while( true );
}

/* ---- Newton_FindGroundElevationAndNormalFast__FP13BO_tNewtonObjP8coorddef  [NEWTON.CPP:515-599] SLD-VERIFIED ---- */
int Newton_FindGroundElevationAndNormalFast(BO_tNewtonObj *newtonObj,coorddef *normal)

{
  int elevation;
  int r1;
  int r2;
  int r3;
  int surfaceType;
  int r4;
  int iVar1;
  int iVar2;
  int iVar3;
  u_int uVar4;
  u_int uVar5;
  int iVar6;
  
  Car_tObj *carObj = (Car_tObj *)newtonObj;
  iVar1 = newtonObj->roadMatrix.m[4];
  iVar2 = newtonObj->roadMatrix.m[3];
  iVar3 = newtonObj->roadMatrix.m[5];
  normal->y = iVar1;
  normal->x = iVar2;
  normal->z = iVar3;
  if (iVar1 < 0x199a) {
    iVar1 = -0x7d000000;
  }
  else {
    iVar1 = Newton_FindGroundElevationGeneral(&newtonObj->position,normal,
                                               &newtonObj->roadCenterPoint);
    uVar4 = newtonObj->position.x;
    uVar5 = newtonObj->position.z;
    iVar3 = normal->x;
    iVar6 = normal->y;
    iVar2 = normal->z;
    for (int wheel = 0; wheel < 4; wheel = wheel + 1) {
      carObj->wheel[wheel].wheelInAir = 0;
      carObj->wheel[wheel].rebound = 0;
      carObj->wheel[wheel].currentPos.x = uVar4;
      carObj->wheel[wheel].currentPos.y = iVar1;
      carObj->wheel[wheel].currentPos.z = uVar5;
      carObj->wheel[wheel].actualHeight = iVar1;
      carObj->wheel[wheel].roadSurfaceType = 1;
      carObj->wheel[wheel].roadNormal.x = iVar3;
      carObj->wheel[wheel].roadNormal.y = iVar6;
      carObj->wheel[wheel].roadNormal.z = iVar2;
    }
  }
  return iVar1;
}

/* ---- Newton_FindGroundElevationAndNormal__FP13BO_tNewtonObjP8coorddef  [NEWTON.CPP:610-1057] SLD-VERIFIED ---- */
int Newton_FindGroundElevationAndNormal(BO_tNewtonObj *newtonObj,coorddef *normal)

{
  Car_tObj *carObj = (Car_tObj *)newtonObj;
  coorddef roadCenterPoint;
  int r2;
  int r3;
  int r4;
  coorddef lengthVector;
  coorddef widthVector;
  coorddef carGroundCoord;
  int v1;
  int r1;
  coorddef roadNormal;
  int roadSurfaceType;
  coorddef wheelVec;
  int limit;
  int wheelBounce;
  int speed;
  int ratio;
  int groundY_ratio;
  int tstr3;
  int tpi4;
  u_int tu1;
  int ti5;
  int ti1;
  int ti4;
  int frontGroundY;
  int wheelGround_y;
  int compressDelta;
  int iVar20;
  u_int tu21;
  int rightGroundY;
  u_int uVar1;
  u_int uVar2;
  int iVar3;
  int desiredCompression;
  int iVar5;
  int ti8;
  int tstr9;
  int i;
  int ti9;
  coorddef *point;
  int iVar24;
  int rearGroundY;
  int tireMagic;
  int tireMagic2;
  int leftGroundY;
  int roll;
  int wheelData_p;
  int pitch;
  int pt;
  int tpi11;
  int newtonData_p;
  int tpi12;
  int wheelInst_p;
  int bounce;
  int bounce_iter;
  int wheel_idx;
  int ti17;
  int wheelsInAir;
  int wheelsInAir_n;
  int ti15;
  int ti18;
  int ti16;
  coorddef elevation;
  coorddef tireCoord [4];
  coorddef carNormal;
  coorddef wheelHeight [4];
  coorddef vecOffset;
  BWorldSm_Pos testSimRoadInfo;
  coorddef tempVecX;
  coorddef tempVecY;
  int compressionValue [4];
  coorddef tempVecZ;
  matrixtdef transposeMat;
  int count;
  
  wheelGround_y = (newtonObj->orientMat).m[4];
  elevation.x = 0;
  elevation.y = 0;
  elevation.z = 0;
  tireMagic = (newtonObj->dimension).z * 0xd >> 0xc;
  wheelHeight[0].x = tireMagic * ((newtonObj->orientMat).m[6] >> 8);
  wheelHeight[0].y = tireMagic * ((newtonObj->orientMat).m[7] >> 8);
  wheelHeight[0].z = tireMagic * ((newtonObj->orientMat).m[8] >> 8);
  tireMagic2 = (newtonObj->dimension).x * 7 >> 0xb;
  wheelHeight[1].y = tireMagic2 * ((newtonObj->orientMat).m[0] >> 8);
  wheelHeight[1].z = tireMagic2 * ((newtonObj->orientMat).m[1] >> 8);
  wheelHeight[2].x = tireMagic2 * ((newtonObj->orientMat).m[2] >> 8);
  desiredCompression = (newtonObj->orientMat).m[3];
  compressDelta = -(newtonObj->dimension).y >> 8;
  wheelsInAir_n = 0;
  bounce_iter = 0;
  ti8 = (newtonObj->position).x + compressDelta * (desiredCompression >> 8);
  ti9 = (newtonObj->position).y + compressDelta * ((newtonObj->orientMat).m[4] >> 8);
  wheelHeight[3].y = (newtonObj->position).z + compressDelta * ((newtonObj->orientMat).m[5] >> 8);
  wheelHeight[2].z = ti8;
  tireCoord[0].x = (ti8 + wheelHeight[0].x) - wheelHeight[1].y;
  tireCoord[0].y = (ti9 + wheelHeight[0].y) - wheelHeight[1].z;
  tireCoord[0].z = (wheelHeight[3].y + wheelHeight[0].z) - wheelHeight[2].x;
  wheelHeight[3].x = ti9;
  tireCoord[2].x = (ti8 - wheelHeight[0].x) - wheelHeight[1].y;
  tireCoord[2].y = (ti9 - wheelHeight[0].y) - wheelHeight[1].z;
  iVar20 = (wheelHeight[3].y - wheelHeight[0].z) + wheelHeight[2].x;
  tireCoord[1].x = ti8 + wheelHeight[0].x + wheelHeight[1].y;
  tireCoord[1].y = ti9 + wheelHeight[0].y + wheelHeight[1].z;
  tireCoord[1].z = wheelHeight[3].y + wheelHeight[0].z + wheelHeight[2].x;
  tireCoord[2].z = (wheelHeight[3].y - wheelHeight[0].z) - wheelHeight[2].x;
  tireCoord[3].x = (ti8 - wheelHeight[0].x) + wheelHeight[1].y;
  tireCoord[3].y = (ti9 - wheelHeight[0].y) + wheelHeight[1].z;
  tireCoord[3].z = iVar20;
  testSimRoadInfo = newtonObj->simRoadInfo;
  for (i = 0; i < 4; i = i + 1) {
    Car_tWheel *wheel = &carObj->wheel[i];
    coorddef *tirePoint = &tireCoord[i];
    coorddef *groundPoint = &wheelHeight[i];
    coorddef *surfaceNormal;

    *groundPoint = *tirePoint;
    wheel->actualHeight = tirePoint->y;
    BWorldSm_FindClosestTriangleRez(tirePoint,&testSimRoadInfo,1);
    surfaceNormal = (coorddef *)BWorldSm_UNormal(&testSimRoadInfo);
    tempVecX = *surfaceNormal;
    uVar1 = 0xe;
    if (testSimRoadInfo.simQuad != (Trk_NewSimQuad *)0x0) {
      uVar1 = (u_int)(testSimRoadInfo.simQuad)->surface;
    }
    wheel->roadSurfaceType = uVar1;
    uVar1 = uVar1 & 0xf;
    if (((tempVecX.y < 0x1999) || (uVar1 == 0xe)) || (uVar1 == 0)) {
      tempVecX.y = 0x10000;
      tempVecX.x = 0;
      tempVecX.z = 0;
      elevation.x = elevation.x + tirePoint->x;
      elevation.y = elevation.y + tirePoint->y - newtonObj->objAltitude;
      elevation.z = elevation.z + tirePoint->z;
    }
    else {
      if (testSimRoadInfo.simQuad == (Trk_NewSimQuad *)0x0) {
        tempVecY.x = BWorldSm_slices[testSimRoadInfo.slice].center[0];
        tempVecY.y = BWorldSm_slices[testSimRoadInfo.slice].center[1];
        tempVecY.z = BWorldSm_slices[testSimRoadInfo.slice].center[2];
      }
      else {
        tempVecY.x = testSimRoadInfo.quadPts[0].x;
        tempVecY.y = testSimRoadInfo.quadPts[0].y;
        tempVecY.z = testSimRoadInfo.quadPts[0].z;
      }
      if (uVar1 - 2 < 2) {
        iVar20 = Newton_FindGroundElevationRough(tirePoint,&tempVecX,&tempVecY)
        ;
        groundPoint->y = iVar20;
      }
      else {
        /* Ghidra turned the current wheel-coordinate pointer into a cast of
           tireCoord[3].z.  The rough-surface branch immediately above and the
           original loop dataflow both use the current tire point (`pt`). */
        iVar20 = Newton_FindGroundElevationGeneral(tirePoint,&tempVecX,&tempVecY);
        groundPoint->y = iVar20;
      }
      wheel->actualHeight = groundPoint->y;
      if (0x20000 < groundPoint->y - tirePoint->y) {
        tempVecX.x = 0;
        tempVecX.y = 0x10000;
        tempVecX.z = 0;
        groundPoint->y = tirePoint->y;
        elevation.x = elevation.x + tirePoint->x;
        elevation.y = elevation.y + tirePoint->y;
        elevation.z = elevation.z + tirePoint->z;
      }
      else {
        elevation.x = elevation.x + groundPoint->x;
        elevation.y = elevation.y + groundPoint->y;
        elevation.z = elevation.z + groundPoint->z;
      }
    }
    wheel->currentPos = *groundPoint;
    wheel->roadNormal = tempVecX;
  }
  iVar24 = 0;
  count = 0;
  tempVecX.x = 0;
  tempVecX.z = 0;
  for (iVar20 = 0; iVar20 < 4; iVar20 = iVar20 + 1) {
    Car_tWheel *wheel = &carObj->wheel[iVar20];
    tempVecX.y = (wheel->currentPos.y - tireCoord[iVar20].y) / 2;
    wheel->rebound = 0;
    if (tempVecX.y < -0x2665) {
      wheel->wheelInAir = 1;
      wheelsInAir_n = wheelsInAir_n + 1;
    }
    else if (wheel->wheelInAir == 1) {
      if (tempVecX.y < 1) {
        if (((newtonObj->objAltitude < 0x3333) && (-0x1999 < (newtonObj->linearVel).y)) &&
           (0xf333 < (newtonObj->orientationToGround).y)) {
          wheel->wheelInAir = 0;
        }
      }
      else {
        bounce_iter = bounce_iter + 1;
        wheel->wheelInAir = 0;
        wheel->rebound = 1;
      }
    }
    iVar3 = -0x3333;
    if (0x358000 < newtonObj->speedXZ) {
      iVar3 = -0x2666;
    }
    if (tempVecX.y < iVar3) {
      tempVecX.y = iVar3;
    }
    iVar3 = tempVecX.y;
    if (tempVecX.y < 0) {
      iVar3 = tempVecX.y + 0xff;
    }
    ti5 = wheelGround_y;
    if (wheelGround_y < 0) {
      ti5 = wheelGround_y + 0xff;
    }
    iVar3 = (iVar3 >> 8) * (ti5 >> 8);
    compressionValue[iVar20] = iVar3;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    ti1 = carObj->specs->suspensionStiffness;
    if (ti1 < 0) {
      ti1 = ti1 + 0xff;
    }
    iVar3 = (iVar3 >> 8) * (ti1 >> 8);
    wheel->wheelAcc = iVar3;
    if (carObj->carInfo->WeightTransfer == 1) {
      wheel->wheelAcc = iVar3 * 2;
    }
    iVar24 = iVar24 + 0xc;
  }
  iVar20 = 0;
  if (bounce_iter != 0) {
    count = carObj->wheel[0].rebound + carObj->wheel[1].rebound +
            carObj->wheel[2].rebound + carObj->wheel[3].rebound;
  }
  for (; iVar20 < 4; iVar20 = iVar20 + 1) {
    Car_tWheel *wheel = &carObj->wheel[iVar20];
    if (bounce_iter == 0) {
      if ((wheel->wheelAcc < 0) &&
         (iVar3 = wheel->wheelAcc >> 1, 0xdc28 < (newtonObj->orientationToGround).y)) {
Newton_FindGE_bounceFirst:
        wheel->wheelAcc = iVar3;
      }
    }
    else if ((wheel->rebound != 0) && (iVar24 = (newtonObj->linearVel).y, iVar24 < 0)) {
      if (iVar24 < 0) {
        iVar24 = -iVar24;
      }
      iVar24 = iVar24 + newtonObj->groundVel;
      if (-1 < iVar24) {
        if (count == 0) {
          trap(0x1c00);
        }
        if ((count == -1) && (iVar24 == -0x80000000)) {
          trap(0x1800);
        }
        iVar3 = iVar24 / count >> 1;
        if (iVar24 < 0x100000) {
          ti4 = fixedmult(iVar24,0x1000);
          if (ti4 < 0x4ccd) {
            iVar24 = 0x4ccc;
          }
          else {
            iVar24 = fixedmult(iVar24,0x1000);
          }
          iVar3 = fixedmult(iVar24,iVar3);
        }
        iVar3 = wheel->wheelAcc + iVar3;
        goto Newton_FindGE_bounceFirst;
      }
    }
  }
  iVar24 = 0;
  iVar20 = 0;
  do {
    if (3 < iVar24) {
      elevation.x = elevation.x >> 2;
      elevation.z = elevation.z >> 2;
      elevation.y = elevation.y >> 2;
      tempVecZ.x = (wheelHeight[0].x + wheelHeight[1].x) - (wheelHeight[2].x + wheelHeight[3].x) >>
                   1;
      tempVecZ.y = (wheelHeight[0].y + wheelHeight[1].y) - (wheelHeight[2].y + wheelHeight[3].y) >>
                   1;
      tempVecZ.z = (wheelHeight[0].z + wheelHeight[1].z) - (wheelHeight[2].z + wheelHeight[3].z) >>
                   1;
      Math_NormalizeShortVector(&tempVecZ);
      tempVecX.x = (wheelHeight[1].x + wheelHeight[3].x) - (wheelHeight[0].x + wheelHeight[2].x) >>
                   1;
      tempVecX.y = (wheelHeight[1].y + wheelHeight[3].y) - (wheelHeight[0].y + wheelHeight[2].y) >>
                   1;
      tempVecX.z = (wheelHeight[1].z + wheelHeight[3].z) - (wheelHeight[0].z + wheelHeight[2].z) >>
                   1;
      Math_NormalizeShortVector(&tempVecX);
      iVar20 = fixedmult(tempVecZ.y,tempVecX.z);
      iVar24 = fixedmult(tempVecZ.z,tempVecX.y);
      tempVecY.x = iVar20 - iVar24;
      iVar20 = fixedmult(tempVecZ.z,tempVecX.x);
      iVar24 = fixedmult(tempVecZ.x,tempVecX.z);
      tempVecY.y = iVar20 - iVar24;
      iVar20 = fixedmult(tempVecZ.x,tempVecX.y);
      iVar24 = fixedmult(tempVecZ.y,tempVecX.x);
      tempVecY.z = iVar20 - iVar24;
      Math_NormalizeShortVector(&tempVecY);
      if (tempVecY.y < 0) {
        wheelsInAir_n = 4;
        normal->x = 0;
        normal->y = 0x10000;
        normal->z = 0;
      }
      else {
        normal->x = tempVecY.x;
        normal->y = tempVecY.y;
        normal->z = tempVecY.z;
        if (tempVecY.y < 0x8000) {
          wheelsInAir_n = 4;
        }
      }
      if ((newtonObj->orientationToGround).y < -0xe666) {
        iVar20 = (newtonObj->angularVel).x * 0xfd;
        if (iVar20 < 0) {
          iVar20 = iVar20 + 0xff;
        }
        (newtonObj->angularVel).x = iVar20 >> 8;
        iVar20 = (newtonObj->angularVel).y * 0xfd;
        if (iVar20 < 0) {
          iVar20 = iVar20 + 0xff;
        }
        (newtonObj->angularVel).y = iVar20 >> 8;
        iVar20 = (newtonObj->angularVel).z * 0xfd;
        if (iVar20 < 0) {
          iVar20 = iVar20 + 0xff;
        }
        (newtonObj->angularVel).z = iVar20 >> 8;
      }
      else if (wheelsInAir_n < 4) {
        iVar20 = fixedmult((newtonObj->angularVel).x,(newtonObj->orientMat).m[0]);
        iVar24 = fixedmult((newtonObj->angularVel).y,(newtonObj->orientMat).m[1]);
        iVar3 = fixedmult((newtonObj->angularVel).z,(newtonObj->orientMat).m[2]);
        ti4 = (newtonObj->angularVel).x;
        iVar5 = (newtonObj->orientMat).m[3];
        carObj->angularVel_ch.x = iVar20 + iVar24 + iVar3;
        iVar20 = fixedmult(ti4,iVar5);
        iVar24 = fixedmult((newtonObj->angularVel).y,(newtonObj->orientMat).m[4]);
        iVar3 = fixedmult((newtonObj->angularVel).z,(newtonObj->orientMat).m[5]);
        ti4 = (newtonObj->angularVel).x;
        iVar5 = (newtonObj->orientMat).m[6];
        carObj->angularVel_ch.y = iVar20 + iVar24 + iVar3;
        iVar20 = fixedmult(ti4,iVar5);
        iVar24 = fixedmult((newtonObj->angularVel).y,(newtonObj->orientMat).m[7]);
        iVar3 = fixedmult((newtonObj->angularVel).z,(newtonObj->orientMat).m[8]);
        ti4 = (carObj->wheel[2].wheelAcc + carObj->wheel[3].wheelAcc) -
              (carObj->wheel[0].wheelAcc + carObj->wheel[1].wheelAcc) >> 2;
        carObj->angularVel_ch.z = iVar20 + iVar24 + iVar3;
        if (ti4 < 1) {
          iVar20 = -carObj->specs->pitchAngularVelCap;
          if (iVar20 < ti4) {
            iVar20 = ti4;
          }
        }
        else {
          iVar20 = carObj->specs->pitchAngularVelCap;
          if (ti4 <= iVar20) {
            iVar20 = ti4;
          }
        }
        iVar24 = (carObj->wheel[0].wheelAcc + carObj->wheel[2].wheelAcc) -
                 (carObj->wheel[1].wheelAcc + carObj->wheel[3].wheelAcc) >> 2;
        if (iVar24 < 1) {
          iVar3 = -carObj->specs->rollAngularVelCap;
          if (iVar3 < iVar24) {
            iVar3 = iVar24;
          }
        }
        else {
          iVar3 = carObj->specs->rollAngularVelCap;
          if (iVar24 <= iVar3) {
            iVar3 = iVar24;
          }
        }
        ti4 = carObj->angularVel_ch.x;
        iVar24 = ti4;
        if (ti4 < 0) {
          iVar24 = -ti4;
        }
        iVar5 = 0xd999;
        if (iVar24 < 0x13333) {
          iVar5 = carObj->specs->dampingPitchRate;
        }
        iVar24 = fixedmult(ti4,iVar5);
        carObj->angularVel_ch.x = iVar24;
        iVar24 = carObj->angularVel_ch.z;
        carObj->angularVel_ch.x = carObj->angularVel_ch.x + iVar20;
        iVar20 = iVar24;
        if (iVar24 < 0) {
          iVar20 = -iVar24;
        }
        ti4 = 0xd999;
        if (iVar20 < 0x13333) {
          ti4 = carObj->specs->dampingRollRate;
        }
        iVar20 = fixedmult(iVar24,ti4);
        carObj->angularVel_ch.z = iVar20;
        carObj->angularVel_ch.z = carObj->angularVel_ch.z - iVar3;
        transpose(&newtonObj->orientMat,&transposeMat);
        iVar20 = fixedmult(carObj->angularVel_ch.x,transposeMat.m[0])
        ;
        iVar24 = fixedmult(carObj->angularVel_ch.y,transposeMat.m[1]);
        iVar3 = fixedmult(carObj->angularVel_ch.z,transposeMat.m[2]);
        ti4 = carObj->angularVel_ch.x;
        (newtonObj->angularVel).x = iVar20 + iVar24 + iVar3;
        iVar20 = fixedmult(ti4,transposeMat.m[3]);
        iVar24 = fixedmult(carObj->angularVel_ch.y,transposeMat.m[4]);
        iVar3 = fixedmult(carObj->angularVel_ch.z,transposeMat.m[5]);
        ti4 = carObj->angularVel_ch.x;
        (newtonObj->angularVel).y = iVar20 + iVar24 + iVar3;
        iVar20 = fixedmult(ti4,transposeMat.m[6]);
        iVar24 = fixedmult(carObj->angularVel_ch.y,transposeMat.m[7]);
        iVar3 = fixedmult(carObj->angularVel_ch.z,transposeMat.m[8]);
        (newtonObj->angularVel).z = iVar20 + iVar24 + iVar3;
      }
      coorddef *samplePoint = simGlobal.gameTicks < 0x40 ? &newtonObj->roadCenterPoint : &elevation;
      iVar20 = Newton_CalcPerpenHeightOfCenterPointFromGround(newtonObj,normal,samplePoint);
      newtonObj->objAltitude = iVar20;
      return elevation.y;
    }
    iVar3 = fixedmult((tireCoord[iVar24].y - wheelHeight[iVar24].y) >> 1,
                      (newtonObj->orientMat).m[4]);
    if (iVar3 < 1) {
      ti4 = -carObj->specs->tireRange;
      if (iVar3 < ti4) goto Newton_FindGE_minTangent;
    }
    else {
      ti4 = carObj->specs->tireRange;
      if (ti4 <= iVar3) {
Newton_FindGE_minTangent:
        iVar3 = ti4;
      }
    }
    ti4 = swap[iVar24];
    iVar20 = iVar20 + 0xc;
    iVar24 = iVar24 + 1;
    carObj->wheel[ti4].impactCompression = iVar3;
  } while( true );
}

/* ---- Newton_LimitCarsToDrivableDist__FP13BO_tNewtonObj  [NEWTON.CPP:1062-1068] SLD-VERIFIED ---- */
void Newton_LimitCarsToDrivableDist(BO_tNewtonObj *newtonObj)

{
  int iVar1;
  
  iVar1 = Physics_DoBarrierCheck((Car_tObj *)newtonObj);
  if (iVar1 != 0) {
    (newtonObj->collision).impulse = 0;
    (newtonObj->collision).otherObj = (BO_tNewtonObj *)0x0;
    Newton_FindClosestQuad(newtonObj);
    Newton_UpdateRoadGeometry(newtonObj);
  }
  return;
}

/* ---- Newton_CalcPerpenHeightOfLowestPointFromGround__FP13BO_tNewtonObjP8coorddefT1  [NEWTON.CPP:1079-1102] SLD-VERIFIED ---- */
int Newton_CalcPerpenHeightOfLowestPointFromGround(BO_tNewtonObj *newtonObj,coorddef *normal,coorddef *samplePoint)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int relativeDot;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int zDir;
  int yDir;
  int xDir;
  coorddef basisDots;
  coorddef relativePos;
  
  relativeDot = normal->x;
  if (relativeDot < 0) {
    relativeDot = relativeDot + 0xff;
  }
  iVar1 = (newtonObj->orientMat).m[0];
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  iVar6 = normal->y;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  iVar2 = (newtonObj->orientMat).m[1];
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  iVar7 = normal->z;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  iVar3 = (newtonObj->orientMat).m[2];
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar1 = (relativeDot >> 8) * (iVar1 >> 8) + (iVar6 >> 8) * (iVar2 >> 8) +
          (iVar7 >> 8) * (iVar3 >> 8);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  iVar6 = (newtonObj->dimension).x;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  iVar1 = (iVar1 >> 8) * (iVar6 >> 8);
  iVar6 = normal->x;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  iVar2 = (newtonObj->orientMat).m[3];
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  iVar7 = normal->y;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  iVar3 = (newtonObj->orientMat).m[4];
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar8 = normal->z;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0xff;
  }
  iVar4 = (newtonObj->orientMat).m[5];
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  iVar6 = (iVar6 >> 8) * (iVar2 >> 8) + (iVar7 >> 8) * (iVar3 >> 8) + (iVar8 >> 8) * (iVar4 >> 8);
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  iVar2 = (newtonObj->dimension).y;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  iVar6 = (iVar6 >> 8) * (iVar2 >> 8);
  iVar2 = normal->x;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  iVar7 = (newtonObj->orientMat).m[6];
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  iVar3 = normal->y;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar8 = (newtonObj->orientMat).m[7];
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0xff;
  }
  iVar4 = normal->z;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  iVar5 = (newtonObj->orientMat).m[8];
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  iVar2 = (iVar2 >> 8) * (iVar7 >> 8) + (iVar3 >> 8) * (iVar8 >> 8) + (iVar4 >> 8) * (iVar5 >> 8);
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  iVar7 = (newtonObj->dimension).z;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  iVar2 = (iVar2 >> 8) * (iVar7 >> 8);
  iVar7 = -1;
  if (iVar1 < 0) {
    iVar7 = 1;
  }
  iVar3 = -1;
  if (iVar6 < 0) {
    iVar3 = 1;
  }
  iVar8 = -1;
  if (iVar2 < 0) {
    iVar8 = 1;
  }
  iVar4 = (newtonObj->position).x - samplePoint->x;
  iVar5 = (newtonObj->position).y - samplePoint->y;
  iVar12 = (newtonObj->position).z - samplePoint->z;
  iVar9 = normal->x;
  if (iVar9 < 0) {
    iVar9 = iVar9 + 0xff;
  }
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  iVar10 = normal->y;
  if (iVar10 < 0) {
    iVar10 = iVar10 + 0xff;
  }
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  iVar11 = normal->z;
  if (iVar11 < 0) {
    iVar11 = iVar11 + 0xff;
  }
  if (iVar12 < 0) {
    iVar12 = iVar12 + 0xff;
  }
  return iVar7 * iVar1 + iVar3 * iVar6 + iVar8 * iVar2 +
         (iVar9 >> 8) * (iVar4 >> 8) + (iVar10 >> 8) * (iVar5 >> 8) + (iVar11 >> 8) * (iVar12 >> 8);
}

/* ---- Newton_CalcPerpenHeightOfCenterPointFromGround__FP13BO_tNewtonObjP8coorddefT1  [NEWTON.CPP:1110-1118] SLD-VERIFIED ---- */
int Newton_CalcPerpenHeightOfCenterPointFromGround(BO_tNewtonObj *newtonObj,coorddef *normal,coorddef *samplePoint)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int relativeDot;
  coorddef relativePos;
  
  iVar1 = (newtonObj->position).y;
  iVar4 = samplePoint->y;
  iVar2 = (newtonObj->position).z;
  iVar5 = samplePoint->z;
  iVar3 = fixedmult(normal->x,(newtonObj->position).x - samplePoint->x);
  iVar4 = fixedmult(normal->y,iVar1 - iVar4);
  iVar2 = fixedmult(normal->z,iVar2 - iVar5);
  iVar1 = (newtonObj->orientationToGround).y;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (iVar1 < 0xb334) {
    iVar1 = (newtonObj->dimension).x;
  }
  else {
    iVar1 = (newtonObj->dimension).y;
  }
  return (iVar3 + iVar4 + iVar2) - iVar1;
}

/* ---- Newton_CalcDistToClosestPlayerCar__FP13BO_tNewtonObj  [NEWTON.CPP:1123-1215] SLD-VERIFIED ---- */
void Newton_CalcDistToClosestPlayerCar(BO_tNewtonObj *n)

{
  int x;
  static coorddef dummy;
  int dist;
  u_char bVar1;
  intptr uVar2;
  int z;
  int iVar3;
  int oldOptz;
  int iVar4;
  int iVar5;
  int iVar6;
  int whichPlayer;
  int forcedSimOptz;
  
  whichPlayer = 0;
  iVar4 = (n->position).x;
  iVar3 = (Cars_gHumanRaceCarList[GameSetup_gData.localCar]->N).position.x;
  oldOptz = iVar4 - iVar3;
  if (oldOptz < 1) {
    oldOptz = iVar3 - iVar4;
  }
  iVar5 = (n->position).z;
  iVar3 = (Cars_gHumanRaceCarList[GameSetup_gData.localCar]->N).position.z;
  iVar4 = iVar5 - iVar3;
  if (iVar4 < 1) {
    iVar4 = iVar3 - iVar5;
  }
  if (iVar4 < oldOptz) {
    iVar4 = oldOptz + (iVar4 >> 2);
  }
  else {
    iVar4 = iVar4 + (oldOptz >> 2);
  }
  n->distToPlayer = iVar4;
  if (Cars_gNumHumanRaceCars == 2) {
    iVar5 = (n->position).x;
    iVar3 = (Cars_gHumanRaceCarList[1 - GameSetup_gData.localCar]->N).position.x;
    iVar4 = iVar5 - iVar3;
    if (iVar4 < 1) {
      iVar4 = iVar3 - iVar5;
    }
    iVar6 = (n->position).z;
    iVar3 = (Cars_gHumanRaceCarList[1 - GameSetup_gData.localCar]->N).position.z;
    iVar5 = iVar6 - iVar3;
    if (iVar5 < 1) {
      iVar5 = iVar3 - iVar6;
    }
    if (iVar5 < iVar4) {
      iVar4 = iVar4 + (iVar5 >> 2);
    }
    else {
      iVar4 = iVar5 + (iVar4 >> 2);
    }
    if (iVar4 < n->distToPlayer) {
      whichPlayer = 1;
      n->distToPlayer = iVar4;
    }
  }
  if (n->distToPlayer < 0x600001) {
    iVar3 = BWorld_CheckChunkVisible(&(Cars_gHumanRaceCarList[whichPlayer]->N).simRoadInfo,&n->simRoadInfo);
    if ((n->distToPlayer < 0x600001) && (iVar3 != 0)) goto NewtonClosestPlr_simOptz;
  }
  if ((((Car_tObj *)n)->forceNoSimOptz == 0) || (simGlobal.gameTicks < 3)) {
    if (n->simOptz != '\x02') {
      n->groundSurfaceType = 1;
      n->driveSurfaceType = 1;
    }
    n->simOptz = '\x02';
    (n->angularVel).x = 0;
    (n->angularVel).z = 0;
    return;
  }
NewtonClosestPlr_simOptz:
  bVar1 = n->simOptz;
  if (((((Car_tObj *)n)->carFlags & 0x30U) == 0) &&
     (((((Car_tObj *)n)->forceNoSimOptz == 0 || (simGlobal.gameTicks < 3)) &&
       (0x480000 < n->distToPlayer)))) {
    n->simOptz = '\x01';
  }
  else {
    n->simOptz = '\0';
  }
  if (1 < bVar1) {
    Cars_SetCarUpForHiRezSim((Car_tObj *)n);
    Newton_FindClosestQuad(n);
    Newton_UpdateRoadGeometry(n);
    Newton_LimitCarsToDrivableDist(n);
    if (stackSpeedUpEnbabledFlag == 0) {
      iVar3 = Newton_FindGroundElevationAndNormal(n,&dummy_124);
      n->groundElevation = iVar3;
    }
    else {
      gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 0;
      iVar3 = Newton_FindGroundElevationAndNormal(n,&dummy_124);
      uVar2 = gWSavePtr;
      n->groundElevation = iVar3;
      gWSavePtr = (intptr)SetSp((void *)uVar2);
      stackSpeedUpEnbabledFlag = 1;
    }
    iVar3 = n->groundElevation;
    iVar4 = (n->dimension).y;
    n->groundSurfaceType = 1;
    n->driveSurfaceType = 1;
    n->groundVel = 0;
    (n->collision).impulse = 0;
    (n->collision).otherObj = (BO_tNewtonObj *)0x0;
    n->objAltitude = 0;
    (n->position).y = iVar3 + iVar4;
  }
  return;
}

/* ---- Newton_UpdateRoadInfo__FP13BO_tNewtonObj  [NEWTON.CPP:1227-1261] SLD-VERIFIED ---- */
void Newton_UpdateRoadInfo(BO_tNewtonObj *n)

{
  u_int uVar1;
  Trk_NewSimQuad *pTVar2;
  
  if (n->active != '\0') {
    Newton_CalcDistToClosestPlayerCar(n);
    Newton_FindClosestQuad(n);
    if ((n->simRoadInfo).quadChanged != '\0') {
      Newton_UpdateRoadGeometry(n);
    }
    if (n->simOptz == '\0') {
      pTVar2 = (n->simRoadInfo).simQuad;
      uVar1 = 0xe;
      if (pTVar2 != (Trk_NewSimQuad *)0x0) {
        uVar1 = (u_int)pTVar2->surface;
      }
      n->groundSurfaceType = uVar1;
      n->driveSurfaceType = uVar1 & 0xf;
    }
  }
  return;
}

/* ---- Newton_CopyRoadMatrixToOrientMat__FP13BO_tNewtonObji  [NEWTON.CPP:1264-1281] SLD-VERIFIED ---- */
void Newton_CopyRoadMatrixToOrientMat(BO_tNewtonObj *n,int backwards)

{
  matrixtdef *pmVar1;
  matrixtdef *road;
  matrixtdef *ori;
  matrixtdef *pmVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (backwards == 0) {
    pmVar2 = &n->orientMat;
    pmVar1 = &n->roadMatrix;
    do {
      iVar3 = pmVar1->m[1];
      iVar4 = pmVar1->m[2];
      iVar5 = pmVar1->m[3];
      pmVar2->m[0] = pmVar1->m[0];
      pmVar2->m[1] = iVar3;
      pmVar2->m[2] = iVar4;
      pmVar2->m[3] = iVar5;
      pmVar1 = (matrixtdef *)(pmVar1->m + 4);
      pmVar2 = (matrixtdef *)(pmVar2->m + 4);
    } while (pmVar1 != (matrixtdef *)((n->roadMatrix).m + 8));
    pmVar2->m[0] = pmVar1->m[0];
    return;
  }
  (n->orientMat).m[0] = -(n->roadMatrix).m[0];
  (n->orientMat).m[1] = -(n->roadMatrix).m[1];
  (n->orientMat).m[2] = -(n->roadMatrix).m[2];
  (n->orientMat).m[3] = (n->roadMatrix).m[3];
  (n->orientMat).m[4] = (n->roadMatrix).m[4];
  (n->orientMat).m[5] = (n->roadMatrix).m[5];
  (n->orientMat).m[6] = -(n->roadMatrix).m[6];
  (n->orientMat).m[7] = -(n->roadMatrix).m[7];
  (n->orientMat).m[8] = -(n->roadMatrix).m[8];
  return;
}

/* ---- Newton_CopyRoadMatrixToShadowMat__FP13BO_tNewtonObji  [NEWTON.CPP:1285-1302] SLD-VERIFIED ---- */
void Newton_CopyRoadMatrixToShadowMat(BO_tNewtonObj *n,int backwards)

{
  matrixtdef *pmVar1;
  matrixtdef *road;
  matrixtdef *shad;
  matrixtdef *pmVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (backwards == 0) {
    pmVar2 = &n->shadowMat;
    pmVar1 = &n->roadMatrix;
    do {
      iVar3 = pmVar1->m[1];
      iVar4 = pmVar1->m[2];
      iVar5 = pmVar1->m[3];
      pmVar2->m[0] = pmVar1->m[0];
      pmVar2->m[1] = iVar3;
      pmVar2->m[2] = iVar4;
      pmVar2->m[3] = iVar5;
      pmVar1 = (matrixtdef *)(pmVar1->m + 4);
      pmVar2 = (matrixtdef *)(pmVar2->m + 4);
    } while (pmVar1 != (matrixtdef *)((n->roadMatrix).m + 8));
    pmVar2->m[0] = pmVar1->m[0];
    return;
  }
  (n->shadowMat).m[0] = -(n->roadMatrix).m[0];
  (n->shadowMat).m[1] = -(n->roadMatrix).m[1];
  (n->shadowMat).m[2] = -(n->roadMatrix).m[2];
  (n->shadowMat).m[3] = (n->roadMatrix).m[3];
  (n->shadowMat).m[4] = (n->roadMatrix).m[4];
  (n->shadowMat).m[5] = (n->roadMatrix).m[5];
  (n->shadowMat).m[6] = -(n->roadMatrix).m[6];
  (n->shadowMat).m[7] = -(n->roadMatrix).m[7];
  (n->shadowMat).m[8] = -(n->roadMatrix).m[8];
  return;
}

/* ---- Newton_SetInitialSlicePositionOrientationEtc__FP13BO_tNewtonObjiP8coorddefi  [NEWTON.CPP:1307-1415] SLD-VERIFIED ---- */
void Newton_SetInitialSlicePositionOrientationEtc(BO_tNewtonObj *n,int slice,coorddef *offset,int direction)

{
  static coorddef dummy;
  u_char uVar1;
  intptr uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  u_int uVar12;
  Trk_NewSimQuad *pTVar13;
  int quadCenterY;
  BO_tNewtonObj *pBVar14;
  int i;
  Trk_NewSlice *pTVar15;
  int backwards;
  u_int backwards_00;
  coorddef rOffset;
  matrixtdef transposeMat;
  coorddef temp;
  
  backwards_00 = (u_int)(direction != 1);
  BWorldSm_SetSlice(slice,&n->simRoadInfo);
  pTVar15 = BWorldSm_slices;
  n->totalSlice = (u_short)slice;
  (n->roadMatrix).m[0] = (int)pTVar15[slice].right[0] << 9;
  (n->roadMatrix).m[1] = (int)pTVar15[slice].right[1] << 9;
  (n->roadMatrix).m[2] = (int)pTVar15[slice].right[2] << 9;
  (n->roadMatrix).m[3] = (int)pTVar15[slice].normal[0] << 9;
  (n->roadMatrix).m[4] = (int)pTVar15[slice].normal[1] << 9;
  (n->roadMatrix).m[5] = (int)pTVar15[slice].normal[2] << 9;
  (n->roadMatrix).m[6] = (int)pTVar15[slice].forward[0] << 9;
  (n->roadMatrix).m[7] = (int)pTVar15[slice].forward[1] << 9;
  (n->roadMatrix).m[8] = (int)pTVar15[slice].forward[2] << 9;
  Math_NormalizeShortVector((coorddef *)&n->roadMatrix);
  Math_NormalizeShortVector((coorddef *)((n->roadMatrix).m + 3));
  Math_NormalizeShortVector((coorddef *)((n->roadMatrix).m + 6));
  transpose(&n->roadMatrix,&transposeMat);
  Newton_CopyRoadMatrixToOrientMat(n,backwards_00);
  Newton_CopyRoadMatrixToShadowMat(n,backwards_00);
  iVar3 = fixedmult(offset->x,transposeMat.m[0]);
  iVar4 = fixedmult(offset->y,transposeMat.m[1]);
  iVar5 = fixedmult(offset->z,transposeMat.m[2]);
  iVar6 = fixedmult(offset->x,transposeMat.m[3]);
  iVar7 = fixedmult(offset->y,transposeMat.m[4]);
  iVar8 = fixedmult(offset->z,transposeMat.m[5]);
  iVar9 = fixedmult(offset->x,transposeMat.m[6]);
  iVar10 = fixedmult(offset->y,transposeMat.m[7]);
  iVar11 = fixedmult(offset->z,transposeMat.m[8]);
  pTVar15 = BWorldSm_slices + slice;
  (n->position).x = iVar3 + iVar4 + iVar5 + pTVar15->center[0];
  (n->position).y = iVar6 + iVar7 + iVar8 + pTVar15->center[1];
  uVar12 = ((Car_tObj *)n)->carFlags;
  (n->position).z = iVar9 + iVar10 + iVar11 + pTVar15->center[2];
  if ((uVar12 & 4) == 0) {
    n->simOptz = '\x02';
  }
  else {
    n->simOptz = '\0';
  }
  Newton_FindClosestQuad(n);
  Newton_UpdateRoadInfo(n);
  Newton_UpdateRoadGeometry(n);
  Newton_CopyRoadMatrixToOrientMat(n,backwards_00);
  Newton_CopyRoadMatrixToShadowMat(n,backwards_00);
  if (n->simOptz == '\x02') {
    n->groundElevation = BWorldSm_slices[slice].center[1];
  }
  else {
    iVar3 = 0;
    if (n->simOptz == '\x01') {
      pBVar14 = n;
      for (i = 0; i < 4; i = i + 1) {
        if ((n->simRoadInfo).simQuad == (Trk_NewSimQuad *)0x0) {
          temp.y = BWorldSm_slices[(n->simRoadInfo).slice].center[1];
        }
        else {
          temp.y = (pBVar14->simRoadInfo).quadPts[0].y;
        }
        pBVar14 = (BO_tNewtonObj *)&(pBVar14->simRoadInfo).simRotFlag;
        iVar3 = iVar3 + temp.y;
      }
      if (iVar3 < 0) {
        iVar3 = iVar3 + 3;
      }
      n->groundElevation = iVar3 >> 2;
    }
    else {
      if (stackSpeedUpEnbabledFlag == 0) {
        iVar3 = Newton_FindGroundElevationAndNormal(n,&dummy_133);
        n->groundElevation = iVar3;
      }
      else {
        gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
        stackSpeedUpEnbabledFlag = 0;
        iVar3 = Newton_FindGroundElevationAndNormal(n,&dummy_133);
        uVar2 = gWSavePtr;
        n->groundElevation = iVar3;
        gWSavePtr = (intptr)SetSp((void *)uVar2);
        stackSpeedUpEnbabledFlag = 1;
      }
      (n->position).y = n->groundElevation + (n->dimension).y;
    }
  }
  iVar3 = Newton_CalcPerpenHeightOfLowestPointFromGround(n,(coorddef *)((n->roadMatrix).m + 3),&n->roadCenterPoint);
  iVar4 = (n->position).y;
  uVar1 = n->simOptz;
  n->objAltitude = iVar3;
  n->objAltitude = 0;
  (n->position).y = iVar4 - iVar3;
  if (uVar1 == '\0') {
    pTVar13 = (n->simRoadInfo).simQuad;
    iVar3 = 0xe;
    if (pTVar13 != (Trk_NewSimQuad *)0x0) {
      n->groundSurfaceType = (u_int)pTVar13->surface;
      goto NewtonSetInitSlice_setDriveSurf;
    }
  }
  else {
    iVar3 = 1;
  }
  n->groundSurfaceType = iVar3;
NewtonSetInitSlice_setDriveSurf:
  n->driveSurfaceType = n->groundSurfaceType & 0xf;
  return;
}

/* ---- Newton_InitBaseNewtonObj__FP13BO_tNewtonObjiiiiii  [NEWTON.CPP:1420-1512] SLD-VERIFIED ---- */
void Newton_InitBaseNewtonObj(BO_tNewtonObj *newtonObj,u_int index,int mass,u_int moInertia,int dimX,
               int dimY,int dimZ)

{
  int i;
  int iVar1;
  u_int *puVar2;
  int iVar3;
  
  u_int *rawWords = (u_int *)newtonObj;
  newtonObj->objID = index;
  newtonObj->simRoadInfo.simSlice = (Trk_NewSimSlice *)0x0;
  newtonObj->simOptz = 0;
  newtonObj->position.x = 0;
  newtonObj->position.y = 0;
  newtonObj->position.z = 0;
  newtonObj->linearVel.x = 0;
  newtonObj->linearVel.y = 0;
  newtonObj->linearVel.z = 0;
  newtonObj->mass = mass;
  if (((GameSetup_gData.sgge & 2U) != 0) && ((rawWords[0x98] & 4) != 0)) {
    newtonObj->mass = mass * 5;
  }
  if ((rawWords[0x98] & 0x20) != 0) {
    if ((GameSetup_gData.commMode == 1) &&
       ((Cars_gHumanRaceCarList[0]->carInfo->carType < 0x16 ||
        (Cars_gHumanRaceCarList[1]->carInfo->carType < 0x16)))) {
      newtonObj->mass = newtonObj->mass << 1;
    }
    else {
      newtonObj->mass = (newtonObj->mass * 3) / 2;
    }
  }
  iVar1 = fixeddiv(0x10000,newtonObj->mass);
  newtonObj->massInv = iVar1;
  newtonObj->moInertia = newtonObj->mass << 3;
  iVar1 = fixeddiv(0x10000,newtonObj->mass << 3);
  newtonObj->moInertiaInv = iVar1;
  newtonObj->angularVel.x = 0;
  newtonObj->angularVel.y = 0;
  newtonObj->angularVel.z = 0;
  newtonObj->orientationToGround.x = 0;
  newtonObj->orientationToGround.y = 0x10000;
  newtonObj->orientationToGround.z = 0;
  newtonObj->dimension.x = dimX;
  newtonObj->dimension.y = dimY;
  newtonObj->dimension.z = dimZ;
  if (dimX < 0) {
    dimX = dimX + 0xff;
  }
  if (dimY < 0) {
    dimY = dimY + 0xff;
  }
  iVar1 = fixedsqrt((dimX >> 8) * (dimX >> 8) + (dimY >> 8) * (dimY >> 8));
  newtonObj->dimensionRadius = iVar1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  if (dimZ < 0) {
    dimZ = dimZ + 0xff;
  }
  iVar1 = fixedsqrt((iVar1 >> 8) * (iVar1 >> 8) + (dimZ >> 8) * (dimZ >> 8));
  iVar3 = 9;
  newtonObj->dimensionRadius = iVar1;
  newtonObj->flightTime = 0;
  newtonObj->groundSurfaceType = 1;
  newtonObj->driveSurfaceType = 1;
  newtonObj->groundVel = 0;
  newtonObj->objAltitude = 0;
  newtonObj->gravityMult = 0x10000;
  newtonObj->xRelRoadCenter = 0;
  newtonObj->roadGravityModifier = 0;
  newtonObj->collision.collided = 0;
  newtonObj->collision.impulse = 0;
  newtonObj->collision.otherObj = (BO_tNewtonObj *)0x0;
  newtonObj->collision.sfxType = 0;
  newtonObj->collision.disableCollisionTimer = 0;
  newtonObj->collision.lastOtherObj = (BO_tNewtonObj *)0x0;
  newtonObj->collision.lastImpulse = 0;
  newtonObj->collision.lastTime = 0;
  for (iVar3 = 9; -1 < iVar3; iVar3 = iVar3 + -1) {
    newtonObj->damage[iVar3] = 0;
  }
  newtonObj->reOrthoCounter = 0;
  newtonObj->deadTimer = 0;
  newtonObj->active = 1;
  newtonObj->cumulatedRot = 0;
  return;
}

/* ---- Newton_QDUpdateVel__FP13BO_tNewtonObj  [NEWTON.CPP:1516-1558] SLD-VERIFIED ---- */
void Newton_QDUpdateVel(BO_tNewtonObj *newtonObj)

{
  int t1;
  int t2;
  int t3;
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (newtonObj->active != '\0') {
    if ((GameSetup_gData.sgge & 4U) == 0) {
      newtonObj->position.x = newtonObj->position.x + (newtonObj->linearVel.x >> 6);
      newtonObj->position.y = newtonObj->position.y + (newtonObj->linearVel.y >> 6);
      newtonObj->position.z = newtonObj->position.z + (newtonObj->linearVel.z >> 6);
    }
    else {
      iVar3 = newtonObj->linearVel.y;
      iVar2 = newtonObj->linearVel.z;
      iVar1 = fixedmult(newtonObj->linearVel.x >> 6,0xcccc);
      iVar2 = fixedmult(iVar2 >> 6,0xcccc);
      newtonObj->position.x = newtonObj->position.x + iVar1;
      newtonObj->position.z = newtonObj->position.z + iVar2;
      newtonObj->position.y = newtonObj->position.y + (iVar3 >> 6);
    }
  }
  return;
}

/* ---- Newton_OptzRotxform__FP10matrixtdefiiiPiiT4  [NEWTON.CPP:1569-1617] SLD-VERIFIED ---- */
bool Newton_OptzRotxform(int *m,int ax,int ay,int az,u_int *reOrthoNeeded,
               u_int reOrthoLimit,int *cumulatedRot)

{
  matrixtdef rx, ry, rz, temp;
  int absx = ax < 0 ? -ax : ax;
  int absy = ay < 0 ? -ay : ay;
  int absz = az < 0 ? -az : az;
  bool changed = (0x13 < absy);

  *reOrthoNeeded = 0;
  *cumulatedRot += absx + absy + absz;

  fixedxformy((int *)&ry,ay);
  if (absx < 0xe) {
    temp = ry;
  }
  else {
    fixedxformx((int *)&rx,ax);
    Math_fasttransmult(&rx,&ry,&temp);
    changed = true;
  }
  if (absz < 0xe) {
    *(matrixtdef *)m = temp;
  }
  else {
    fixedxformz((int *)&rz,az);
    Math_fasttransmult(&temp,&rz,(matrixtdef *)m);
    changed = true;
  }
  return changed;
}

/* ---- Newton_QDUpdateRot64Hz__FP13BO_tNewtonObj  [NEWTON.CPP:1621-1667] SLD-VERIFIED ---- */
void Newton_QDUpdateRot64Hz(BO_tNewtonObj *newtonObj)

{
  matrixtdef m;
  int reOrthoNeeded;
  coorddef angularVel;
  char cVar1;
  int iVar2;
  matrixtdef *m1;
  matrixtdef mStack_50;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  u_int aiStack_18 [2];
  
  if (newtonObj->active != '\0') {
    iStack_28 = newtonObj->angularVel.x;
    if (iStack_28 < 0) {
      iStack_28 = iStack_28 + 0x3f;
    }
    iStack_28 = iStack_28 >> 6;
    iStack_24 = newtonObj->angularVel.y;
    if (iStack_24 < 0) {
      iStack_24 = iStack_24 + 0x3f;
    }
    iStack_24 = iStack_24 >> 6;
    iStack_20 = newtonObj->angularVel.z;
    if (iStack_20 < 0) {
      iStack_20 = iStack_20 + 0x3f;
    }
    iStack_20 = iStack_20 >> 6;
    iVar2 = Newton_OptzRotxform((int *)&mStack_50,iStack_28,iStack_24,iStack_20,
                                aiStack_18,0x1000,&newtonObj->cumulatedRot);
    m1 = &newtonObj->orientMat;
    if (iVar2 != 0) {
      Math_fasttransmult(m1,&mStack_50,m1);
      cVar1 = newtonObj->reOrthoCounter + -1;
      newtonObj->reOrthoCounter = cVar1;
      if ((cVar1 == '\0') || (aiStack_18[0] != 0)) {
        reorthogonalize(m1);
        newtonObj->reOrthoCounter = 0x20;
        newtonObj->cumulatedRot = 0;
      }
    }
  }
  return;
}

/* ---- Newton_QDUpdateRot32Hz__FP13BO_tNewtonObj  [NEWTON.CPP:1670-1722] SLD-VERIFIED ---- */
void Newton_QDUpdateRot32Hz(BO_tNewtonObj *newtonObj)

{
  matrixtdef m;
  int reOrthoNeeded;
  coorddef angularVel;
  char cVar1;
  int iVar2;
  matrixtdef *m1;
  matrixtdef mStack_50;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  u_int aiStack_18 [2];
  
  if ((newtonObj->active != '\0') && (newtonObj->simOptz == '\0')) {
    iStack_28 = newtonObj->angularVel.x;
    if (iStack_28 < 0) {
      iStack_28 = iStack_28 + 0xf;
    }
    iStack_28 = iStack_28 >> 4;
    iStack_24 = newtonObj->angularVel.y;
    if (iStack_24 < 0) {
      iStack_24 = iStack_24 + 0xf;
    }
    iStack_24 = iStack_24 >> 4;
    iStack_20 = newtonObj->angularVel.z;
    if (iStack_20 < 0) {
      iStack_20 = iStack_20 + 0xf;
    }
    iStack_20 = iStack_20 >> 4;
    iVar2 = Newton_OptzRotxform((int *)&mStack_50,iStack_28,iStack_24,iStack_20,
                                aiStack_18,0x2000,&newtonObj->cumulatedRot);
    m1 = &newtonObj->orientMat;
    if ((iVar2 != 0) &&
       ((Math_fasttransmult(m1,&mStack_50,m1), aiStack_18[0] != 0 ||
        (cVar1 = newtonObj->reOrthoCounter + -1,
         newtonObj->reOrthoCounter = cVar1, cVar1 == '\0')))
       ) {
      reorthogonalize(m1);
      newtonObj->reOrthoCounter = 0x40;
      newtonObj->cumulatedRot = 0;
    }
  }
  return;
}

/* ---- Newton_CalculateGroundShadowMatrix__FP13BO_tNewtonObjP8coorddefi  [NEWTON.CPP:1730-1807] SLD-VERIFIED ---- */
void Newton_CalculateGroundShadowMatrix(BO_tNewtonObj *newtonObj,coorddef *normal,int orientToGround)

{
  int r1;
  int r2;
  int r3;
  u_int *puVar1;
  int iVar2;
  int iVar3;
  u_int *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  coorddef *v;
  u_int uVar9;
  u_int uVar10;
  u_int uVar11;
  
  if (((((Car_tObj *)newtonObj)->carFlags & 4) == 0) && 0xe666 < orientToGround) {
    newtonObj->shadowMat = newtonObj->orientMat;
    iVar5 = normal->y;
    iVar8 = normal->z;
    newtonObj->shadowMat.m[3] = normal->x;
    newtonObj->shadowMat.m[4] = iVar5;
    newtonObj->shadowMat.m[5] = iVar8;
    return;
  }
  iVar5 = normal->y;
  iVar8 = normal->z;
  newtonObj->shadowMat.m[3] = normal->x;
  newtonObj->shadowMat.m[4] = iVar5;
  newtonObj->shadowMat.m[5] = iVar8;
  if (orientToGround < 0x8000) {
    iVar5 = newtonObj->orientMat.m[0];
    if (iVar5 < 0) {
      iVar5 = iVar5 + 0xff;
    }
    iVar8 = normal->x;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 0xff;
    }
    iVar6 = newtonObj->orientMat.m[1];
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0xff;
    }
    iVar2 = normal->y;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
    iVar7 = newtonObj->orientMat.m[2];
    if (iVar7 < 0) {
      iVar7 = iVar7 + 0xff;
    }
    iVar3 = normal->z;
    iVar7 = iVar7 >> 8;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0xff;
    }
    iVar3 = iVar3 >> 8;
    iVar5 = (iVar5 >> 8) * (iVar8 >> 8) + (iVar6 >> 8) * (iVar2 >> 8) + iVar7 * iVar3;
    if (iVar5 < 0) {
      iVar5 = -iVar5;
    }
    if (0.5 < (double)iVar5) {
      iVar5 = fixedmult(newtonObj->shadowMat.m[4],newtonObj->orientMat.m[8]);
      iVar8 = fixedmult(newtonObj->shadowMat.m[5],newtonObj->orientMat.m[7]);
      newtonObj->shadowMat.m[0] = iVar5 - iVar8;
      iVar5 = fixedmult(newtonObj->shadowMat.m[5],newtonObj->orientMat.m[6]);
      iVar8 = fixedmult(newtonObj->shadowMat.m[3],newtonObj->orientMat.m[8]);
      newtonObj->shadowMat.m[1] = iVar5 - iVar8;
      iVar5 = fixedmult(newtonObj->shadowMat.m[3],newtonObj->orientMat.m[7]);
      iVar8 = fixedmult(newtonObj->shadowMat.m[4],newtonObj->orientMat.m[6]);
      newtonObj->shadowMat.m[2] = iVar5 - iVar8;
      Math_NormalizeShortVector((coorddef *)&newtonObj->shadowMat.m[0]);
      iVar5 = fixedmult(newtonObj->shadowMat.m[1],newtonObj->shadowMat.m[5]);
      iVar8 = fixedmult(newtonObj->shadowMat.m[2],newtonObj->shadowMat.m[4]);
      newtonObj->shadowMat.m[6] = iVar5 - iVar8;
      iVar5 = fixedmult(newtonObj->shadowMat.m[2],newtonObj->shadowMat.m[3]);
      iVar8 = fixedmult(newtonObj->shadowMat.m[0],newtonObj->shadowMat.m[5]);
      newtonObj->shadowMat.m[7] = iVar5 - iVar8;
      iVar5 = fixedmult(newtonObj->shadowMat.m[0],newtonObj->shadowMat.m[4]);
      iVar8 = fixedmult(newtonObj->shadowMat.m[1],newtonObj->shadowMat.m[3]);
      v = (coorddef *)&newtonObj->shadowMat.m[6];
      newtonObj->shadowMat.m[8] = iVar5 - iVar8;
      goto NewtonGroundShadow_normalizeV;
    }
  }
  iVar5 = fixedmult(newtonObj->orientMat.m[1],newtonObj->shadowMat.m[5]);
  iVar8 = fixedmult(newtonObj->orientMat.m[2],newtonObj->shadowMat.m[4]);
  newtonObj->shadowMat.m[6] = iVar5 - iVar8;
  iVar5 = fixedmult(newtonObj->orientMat.m[2],newtonObj->shadowMat.m[3]);
  iVar8 = fixedmult(newtonObj->orientMat.m[0],newtonObj->shadowMat.m[5]);
  newtonObj->shadowMat.m[7] = iVar5 - iVar8;
  iVar5 = fixedmult(newtonObj->orientMat.m[0],newtonObj->shadowMat.m[4]);
  iVar8 = fixedmult(newtonObj->orientMat.m[1],newtonObj->shadowMat.m[3]);
  newtonObj->shadowMat.m[8] = iVar5 - iVar8;
  Math_NormalizeShortVector((coorddef *)&newtonObj->shadowMat.m[6]);
  iVar5 = fixedmult(newtonObj->shadowMat.m[4],newtonObj->shadowMat.m[8]);
  iVar8 = fixedmult(newtonObj->shadowMat.m[5],newtonObj->shadowMat.m[7]);
  newtonObj->shadowMat.m[0] = iVar5 - iVar8;
  iVar5 = fixedmult(newtonObj->shadowMat.m[5],newtonObj->shadowMat.m[6]);
  iVar8 = fixedmult(newtonObj->shadowMat.m[3],newtonObj->shadowMat.m[8]);
  newtonObj->shadowMat.m[1] = iVar5 - iVar8;
  iVar5 = fixedmult(newtonObj->shadowMat.m[3],newtonObj->shadowMat.m[7]);
  iVar8 = fixedmult(newtonObj->shadowMat.m[4],newtonObj->shadowMat.m[6]);
  v = (coorddef *)&newtonObj->shadowMat.m[0];
  newtonObj->shadowMat.m[2] = iVar5 - iVar8;
NewtonGroundShadow_normalizeV:
  Math_NormalizeShortVector(v);
  return;
}

/* ---- Newton_CalcRealShadowCoordinates__FP8Car_tObji  [NEWTON.CPP:1830-1880] SLD-VERIFIED ---- */
void Newton_CalcRealShadowCoordinates(Car_tObj *carObj,int currentTick)

{
  coorddef lengthVector;
  coorddef widthVector;
  coorddef frontWidthVector;
  coorddef carGroundCoord;
  coorddef temp;
  coorddef vecOffset;
  int diff;
  coorddef dimension;
  int front;
  int i;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int local_60;
  int local_5c;
  int local_58;
  int local_50;
  int local_4c;
  int local_48;
  
  iVar7 = carObj->N.lastUpdated;
  iVar9 = carObj->N.dimension.y;
  iVar1 = carObj->N.dimension.x + 0xccc;
  iVar8 = carObj->N.dimension.z + 0xccc;
  iVar2 = fixedmult(iVar8,carObj->N.orientMat.m[6]);
  iVar3 = fixedmult(iVar8,carObj->N.orientMat.m[7]);
  iVar8 = fixedmult(iVar8,carObj->N.orientMat.m[8]);
  iVar4 = fixedmult(iVar1,carObj->N.orientMat.m[0]);
  iVar5 = fixedmult(iVar1,carObj->N.orientMat.m[1]);
  iVar6 = fixedmult(iVar1,carObj->N.orientMat.m[2]);
  local_60 = iVar4;
  local_5c = iVar5;
  local_58 = iVar6;
  if (carObj->render.currentCarType == 0x14) {
    iVar1 = iVar1 * 0xc0 >> 8;
    local_60 = fixedmult(iVar1,carObj->N.orientMat.m[0]);
    local_5c = fixedmult(iVar1,carObj->N.orientMat.m[1]);
    local_58 = fixedmult(iVar1,carObj->N.orientMat.m[2]);
  }
  if (carObj->N.orientationToGround.y < 0xe667) {
    local_50 = carObj->N.position.x;
    local_48 = carObj->N.position.z;
    local_4c = carObj->N.groundElevation;
  }
  else {
    local_50 = fixedmult(-carObj->N.objAltitude - iVar9,carObj->N.roadMatrix.m[3]);
    local_4c = fixedmult(-carObj->N.objAltitude - iVar9,carObj->N.roadMatrix.m[4]);
    local_48 = fixedmult(-carObj->N.objAltitude - iVar9,carObj->N.roadMatrix.m[5]);
    local_50 = carObj->N.position.x + local_50;
    local_4c = carObj->N.position.y + local_4c;
    local_48 = carObj->N.position.z + local_48;
  }
  carObj->N.shadowCoord[0].x = (local_50 + iVar2) - local_60;
  carObj->N.shadowCoord[0].y = (local_4c + iVar3) - local_5c;
  carObj->N.shadowCoord[0].z = (local_48 + iVar8) - local_58;
  carObj->N.shadowCoord[1].x = local_50 + iVar2 + local_60;
  carObj->N.shadowCoord[1].y = local_4c + iVar3 + local_5c;
  carObj->N.shadowCoord[1].z = local_48 + iVar8 + local_58;
  carObj->N.shadowCoord[2].x = (local_50 - iVar2) - iVar4;
  carObj->N.shadowCoord[2].y = (local_4c - iVar3) - iVar5;
  carObj->N.shadowCoord[2].z = (local_48 - iVar8) - iVar6;
  carObj->N.shadowCoord[3].x = (local_50 - iVar2) + iVar4;
  carObj->N.shadowCoord[3].y = (local_4c - iVar3) + iVar5;
  carObj->N.shadowCoord[3].z = (local_48 - iVar8) + iVar6;
  for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
    iVar8 = carObj->wheel[iVar9].currentPos.y;
    carObj->N.shadowCoord[iVar9].y = iVar8;
    /* 0x800A29D8 loads car+0xb0 = N.linearVel.y (not z at +0xb4).
       Extrapolate the wheel's vertical position between physics updates. */
    iVar3 = carObj->N.linearVel.y;
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0x3f;
    }
    carObj->N.shadowCoord[iVar9].y = iVar8 + (iVar3 >> 6) * (currentTick - iVar7);
  }
  return;
}

/* ---- Newton_CheckForSpikeBelts__FP13BO_tNewtonObj  [NEWTON.CPP:1885-1916] SLD-VERIFIED ---- */
void Newton_CheckForSpikeBelts(BO_tNewtonObj *newtonObj)

{
  int slice;
  int leftLatPos;
  int rightLatPos;
  int latPos;
  int iVar1;
  Car_tObj *carObj = (Car_tObj *)newtonObj;
  
  if (AICop_spikeBelt.active_ != 0) {
    if ((((AICop_spikeBelt.active_ != 0) &&
          (newtonObj->simRoadInfo.slice == AICop_spikeBelt.slice_)) &&
         ((carObj->carFlags & 0x230) == 0)) &&
        (((AICop_spikeBelt.leftLatPos_ < carObj->roadPosition &&
           (carObj->roadPosition < AICop_spikeBelt.rightLatPos_)) &&
          (iVar1 = carObj->blowout + 1, carObj->blowout = iVar1, iVar1 == 1)))) {
      newtonObj->collision.impulse = 0xf0000;
      newtonObj->collision.sfxType = 0x50007;
      newtonObj->collision.collisionPoint = newtonObj->position;
    }
  }
  return;
}

/* ---- Newton_DoPostBarrierCollisionHandling__FP13BO_tNewtonObjG8coorddef  [NEWTON.CPP:1922-1956] SLD-VERIFIED ---- */
void Newton_DoPostBarrierCollisionHandling(BO_tNewtonObj *newtonObj,coorddef normal)

{
  coorddef barrierVec;
  int impactVel;
  int distRetreat;
  coorddef upVec;
  matrixtdef islandMatrix;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  matrixtdef local_38;
  
  iVar1 = normal.z;
  if (normal.z < 0) {
    iVar1 = nfs4_mips_addu_s32(normal.z,0xff);
  }
  local_38.m[6] = nfs4_mips_negu_s32(
      nfs4_mips_sll_s32(nfs4_mips_sra_s32(iVar1,8),8));
  iVar1 = normal.x;
  if (normal.x < 0) {
    iVar1 = nfs4_mips_addu_s32(normal.x,0xff);
  }
  local_38.m[8] = nfs4_mips_sll_s32(nfs4_mips_sra_s32(iVar1,8),8);
  iVar2 = normal.y;
  if (normal.y < 0) {
    iVar2 = nfs4_mips_addu_s32(normal.y,0xff);
  }
  iVar3 = newtonObj->linearVel.x;
  if (iVar3 < 0) {
    iVar3 = nfs4_mips_addu_s32(iVar3,0xff);
  }
  iVar4 = newtonObj->linearVel.y;
  if (iVar4 < 0) {
    iVar4 = nfs4_mips_addu_s32(iVar4,0xff);
  }
  iVar6 = normal.z;
  if (normal.z < 0) {
    iVar6 = nfs4_mips_addu_s32(normal.z,0xff);
  }
  iVar5 = newtonObj->linearVel.z;
  if (iVar5 < 0) {
    iVar5 = nfs4_mips_addu_s32(iVar5,0xff);
  }
  iVar1 = nfs4_mips_addu_s32(
      nfs4_mips_addu_s32(
          nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar1,8),nfs4_mips_sra_s32(iVar3,8)),
          nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar2,8),nfs4_mips_sra_s32(iVar4,8))),
      nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar6,8),nfs4_mips_sra_s32(iVar5,8)));
  if (iVar1 < 0) {
    iVar1 = nfs4_mips_negu_s32(iVar1);
  }
  iVar1 = nfs4_mips_negu_s32(iVar1);
  if (iVar1 < 0) {
    iVar1 = nfs4_mips_addu_s32(iVar1,0xf);
  }
  iVar2 = -0x7ae;
  if (nfs4_mips_sra_s32(iVar1,4) < -0x7ad) {
    iVar2 = nfs4_mips_sra_s32(iVar1,4);
  }
  local_38.m[3] = 0;
  local_38.m[4] = 0x10000;
  local_38.m[5] = 0;
  local_38.m[7] = 0;
  local_38.m[0] = normal.x;
  local_38.m[1] = normal.y;
  local_38.m[2] = normal.z;
  iVar1 = Physics_AttenuateVelocity((Car_tObj *)newtonObj,iVar2,&local_38);
  Physics_SetCurrentWallType(4);
  Physics_CorrectPostCollisionYaw((Car_tObj *)newtonObj,iVar1,normal);
  return;
}

/* ---- Newton_GenerateVector__FiP8coorddefP12BWorldSm_Pos  [NEWTON.CPP:2107-2140] SLD-VERIFIED ---- */
void Newton_GenerateVector(int type,coorddef *vector,BWorldSm_Pos *testSimRoadInfo)

{
  coorddef fwdVec;
  coorddef upVec;
  coorddef result;
  int iVar1;
  int iVar2;
  coorddef local_40;
  int local_30;
  int local_2c;
  int local_28;
  int local_20;
  int local_1c;
  
  local_2c = 0x10000;
  local_28 = 0;
  local_30 = 0;
  local_40.y = 0;
  if (type == 1) {
    local_40.z = testSimRoadInfo->quadPts[3].z - testSimRoadInfo->quadPts[2].z;
    local_40.x = testSimRoadInfo->quadPts[3].x - testSimRoadInfo->quadPts[2].x;
  }
  else if (type == 4) {
    local_40.z = testSimRoadInfo->quadPts[2].z - testSimRoadInfo->quadPts[1].z;
    local_40.x = testSimRoadInfo->quadPts[2].x - testSimRoadInfo->quadPts[1].x;
  }
  else if (type == 2) {
    local_40.z = testSimRoadInfo->quadPts[1].z - testSimRoadInfo->quadPts[0].z;
    local_40.x = testSimRoadInfo->quadPts[1].x - testSimRoadInfo->quadPts[0].x;
  }
  else if (type == 8) {
    local_40.z = testSimRoadInfo->quadPts[0].z - testSimRoadInfo->quadPts[3].z;
    local_40.x = testSimRoadInfo->quadPts[0].x - testSimRoadInfo->quadPts[3].x;
  }
  Math_NormalizeShortVector(&local_40);
  iVar1 = fixedmult(local_40.y,local_28);
  local_20 = fixedmult(local_40.z,local_2c);
  local_20 = iVar1 - local_20;
  iVar1 = fixedmult(local_40.z,local_30);
  local_1c = fixedmult(local_40.x,local_28);
  local_1c = iVar1 - local_1c;
  iVar1 = fixedmult(local_40.x,local_2c);
  iVar2 = fixedmult(local_40.y,local_30);
  vector->x = local_20;
  vector->y = local_1c;
  vector->z = iVar1 - iVar2;
  return;
}

/* ---- Netwon_CheckForBadQuad__FP13BO_tNewtonObjP12BWorldSm_Posi  [NEWTON.CPP:2144-2157] SLD-VERIFIED ---- */
u_int
Netwon_CheckForBadQuad(BO_tNewtonObj *newtonObj,BWorldSm_Pos *testSimRoadInfo,int wheel)

{
  Car_tObj *carObj = (Car_tObj *)newtonObj;
  u_int uVar1;
  
  uVar1 = 0;
  if (((testSimRoadInfo->simQuad != (Trk_NewSimQuad *)0x0) &&
       ((testSimRoadInfo->simQuad->surface & 0xf) == 0)) ||
      (0x20000 < carObj->wheel[wheel].actualHeight - carObj->wheel[wheel].currentPos.y)) {
    uVar1 = 1;
  }
  return uVar1;
}

/* ---- Newton_TestForUndrivableSurfaces__FP13BO_tNewtonObj  [NEWTON.CPP:2161-2361] SLD-VERIFIED ---- */
void Newton_TestForUndrivableSurfaces(BO_tNewtonObj *newtonObj)

{
  Car_tObj *carObj = (Car_tObj *)newtonObj;
  int impulse;
  int i;
  int collision_type;
  int newHeight;
  coorddef normal;
  coorddef cautionaryCenter;
  coorddef undrivableCenter;
  coorddef speedVec;
  coorddef testPoint;
  coorddef newTestPoint;
  int check;
  int j;
  coorddef temp;
  int zone;
  short sVar1;
  short sVar2;
  u_short uVar3;
  BWorldSm_Pos *pBVar4;
  u_int uVar5;
  u_int uVar6;
  Trk_NewSlice *pTVar7;
  BWorldSm_Pos *pBVar8;
  coorddef *pcVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar14;
  coorddef local_a0;
  int local_90;
  int local_8c;
  int local_88;
  int local_80;
  int local_7c;
  int local_78;
  coorddef local_60;
  coorddef local_50;
  int local_40;
  int local_3c;
  int local_38;
  u_int local_30;
  int local_2c;
  
  iVar14 = 0;
  local_30 = 0;
  local_90 = (newtonObj->roadCenterPoint).x;
  local_8c = (newtonObj->roadCenterPoint).y;
  local_88 = (newtonObj->roadCenterPoint).z;
  memset((u_char *)&speedVec,'\0',sizeof(speedVec));
  pBVar4 = &testSimRoadInfo;
  pBVar8 = &newtonObj->simRoadInfo;
  do {
    sVar1 = pBVar8->stripQuadInd;
    sVar2 = pBVar8->simRotFlag;
    uVar3 = *(u_short *)((char *)(pBVar8) + 0x6);
    iVar10 = pBVar8->quadPts[0].x;
    iVar12 = pBVar8->quadPts[0].y;
    pBVar4->slice = pBVar8->slice;
    pBVar4->stripQuadInd = sVar1;
    pBVar4->simRotFlag = sVar2;
    *(u_short *)((char *)(pBVar4) + 0x6) = uVar3;
    pBVar4->quadPts[0].x = iVar10;
    pBVar4->quadPts[0].y = iVar12;
    pBVar8 = (BWorldSm_Pos *)&pBVar8->quadPts[0].z;
    pBVar4 = (BWorldSm_Pos *)&pBVar4->quadPts[0].z;
  } while (pBVar8 != (BWorldSm_Pos *)&(newtonObj->simRoadInfo).simSlice);
  *(int *)pBVar4 = *(int *)pBVar8;
  if (0x280000 < newtonObj->speedXZ) {
    speedVec.x = nfs4_mips_addu_s32(nfs4_mips_sll_s32((newtonObj->linearVel).x,2),
                                     (newtonObj->linearVel).x);
    if (speedVec.x < 0) {
      speedVec.x = nfs4_mips_addu_s32(speedVec.x,0xff);
    }
    speedVec.x = nfs4_mips_sra_s32(speedVec.x,8);
    speedVec.y = nfs4_mips_addu_s32(nfs4_mips_sll_s32((newtonObj->linearVel).y,2),
                                     (newtonObj->linearVel).y);
    if (speedVec.y < 0) {
      speedVec.y = nfs4_mips_addu_s32(speedVec.y,0xff);
    }
    speedVec.y = nfs4_mips_sra_s32(speedVec.y,8);
    speedVec.z = nfs4_mips_addu_s32(nfs4_mips_sll_s32((newtonObj->linearVel).z,2),
                                     (newtonObj->linearVel).z);
    if (speedVec.z < 0) {
      speedVec.z = nfs4_mips_addu_s32(speedVec.z,0xff);
    }
    speedVec.z = nfs4_mips_sra_s32(speedVec.z,8);
  }
  iVar10 = 0;
  local_2c = 0;
  do {
    if (3 < iVar10) {
      return;
    }
    local_60.x = carObj->wheel[iVar10].currentPos.x + speedVec.x;
    local_60.y = carObj->wheel[iVar10].currentPos.y + speedVec.y;
    local_60.z = carObj->wheel[iVar10].currentPos.z + speedVec.z;
    BWorldSm_FindClosestQuadRez(&local_60,&testSimRoadInfo,1)
    ;
    if (testSimRoadInfo.offEdge == 0) {
      iVar12 = Netwon_CheckForBadQuad(newtonObj,&testSimRoadInfo,iVar10);
      if (iVar12 != 0) {
        pBVar8 = &newtestSimRoadInfo;
        pBVar4 = &testSimRoadInfo;
        do {
          sVar1 = pBVar4->stripQuadInd;
          sVar2 = pBVar4->simRotFlag;
          uVar3 = *(u_short *)((char *)(pBVar4) + 0x6);
          iVar14 = pBVar4->quadPts[0].x;
          iVar12 = pBVar4->quadPts[0].y;
          pBVar8->slice = pBVar4->slice;
          pBVar8->stripQuadInd = sVar1;
          pBVar8->simRotFlag = sVar2;
          *(u_short *)((char *)(pBVar8) + 0x6) = uVar3;
          pBVar8->quadPts[0].x = iVar14;
          pBVar8->quadPts[0].y = iVar12;
          pBVar4 = (BWorldSm_Pos *)&pBVar4->quadPts[0].z;
          pBVar8 = (BWorldSm_Pos *)&pBVar8->quadPts[0].z;
        } while (pBVar4 != (BWorldSm_Pos *)&testSimRoadInfo.simSlice);
        *(Trk_NewSimSlice **)pBVar8 = testSimRoadInfo.simSlice;
        local_50.x = local_60.x;
        local_50.y = local_60.y;
        local_50.z = local_60.z;
        uVar5 = BWorldSm_FindEdgeOff(&local_60,&newtonObj->simRoadInfo,&testSimRoadInfo,(int *)&local_30);
        uVar6 = 1;
        iVar14 = 2;
        if (uVar5 == 1) {
NewtonTestUndrv_genVecRay1:
          Newton_GenerateVector(uVar6,&local_a0,&newtonObj->simRoadInfo);
        }
        else {
          if (uVar5 == 2) {
            uVar6 = 2;
            goto NewtonTestUndrv_genVecRay1;
          }
          uVar6 = 4;
          if ((uVar5 == 4) || (uVar6 = 8, uVar5 == 8)) goto NewtonTestUndrv_genVecRay1;
        }
        if ((uVar5 & 3) != 0) {
          uVar6 = 1;
          if (((uVar5 & 1) != 0) || (uVar6 = 2, (uVar5 & 2) != 0)) {
            Newton_GenerateVector(uVar6,&local_a0,&newtonObj->simRoadInfo);
          }
          local_50.x = local_50.x + local_a0.x;
          local_50.y = local_50.y + local_a0.y;
          local_50.z = local_50.z + local_a0.z;
          BWorldSm_FindClosestQuadRez(&local_50,&newtestSimRoadInfo,1);
          iVar12 = Netwon_CheckForBadQuad(newtonObj,&newtestSimRoadInfo,iVar10);
          if (iVar12 != 0) {
            if ((uVar5 & 0xc) == 0) {
              pcVar9 = testSimRoadInfo.quadPts;
              local_78 = 0;
              local_7c = 0;
              local_80 = 0;
              for (iVar12 = 0; iVar12 < 4; iVar12 = iVar12 + 1) {
                if (testSimRoadInfo.simQuad == (Trk_NewSimQuad *)0x0) {
                  pTVar7 = BWorldSm_slices + testSimRoadInfo.slice;
                  local_40 = pTVar7->center[0];
                  local_3c = pTVar7->center[1];
                  local_38 = pTVar7->center[2];
                }
                else {
                  local_40 = pcVar9->x;
                  local_3c = pcVar9->y;
                  local_38 = pcVar9->z;
                }
                pcVar9 = pcVar9 + 1;
                local_80 = local_80 + local_40;
                local_7c = local_7c + local_3c;
                local_78 = local_78 + local_38;
              }
              if (local_80 < 0) {
                local_80 = local_80 + 3;
              }
              local_80 = local_80 >> 2;
              if (local_7c < 0) {
                local_7c = local_7c + 3;
              }
              local_7c = local_7c >> 2;
              if (local_78 < 0) {
                local_78 = local_78 + 3;
              }
              local_78 = local_78 >> 2;
              local_a0.x = (newtonObj->position).x - local_80;
              local_a0.z = (newtonObj->position).z - local_78;
            }
            else {
              uVar6 = 4;
              if (((uVar5 & 4) != 0) || (uVar6 = 8, (uVar5 & 8) != 0)) {
                Newton_GenerateVector(uVar6,&local_a0,&newtonObj->simRoadInfo);
              }
              pBVar8 = &newtestSimRoadInfo;
              pBVar4 = &testSimRoadInfo;
              do {
                sVar1 = pBVar4->stripQuadInd;
                sVar2 = pBVar4->simRotFlag;
                uVar3 = *(u_short *)((char *)(pBVar4) + 0x6);
                iVar12 = pBVar4->quadPts[0].x;
                iVar11 = pBVar4->quadPts[0].y;
                pBVar8->slice = pBVar4->slice;
                pBVar8->stripQuadInd = sVar1;
                pBVar8->simRotFlag = sVar2;
                *(u_short *)((char *)(pBVar8) + 0x6) = uVar3;
                pBVar8->quadPts[0].x = iVar12;
                pBVar8->quadPts[0].y = iVar11;
                pBVar4 = (BWorldSm_Pos *)&pBVar4->quadPts[0].z;
                pBVar8 = (BWorldSm_Pos *)&pBVar8->quadPts[0].z;
              } while (pBVar4 != (BWorldSm_Pos *)&testSimRoadInfo.simSlice);
              *(Trk_NewSimSlice **)pBVar8 = testSimRoadInfo.simSlice;
              local_50.x = local_60.x + local_a0.x;
              local_50.y = local_60.y + local_a0.y;
              local_50.z = local_60.z + local_a0.z;
              BWorldSm_FindClosestQuadRez(&local_50,&newtestSimRoadInfo,1);
              iVar12 = Netwon_CheckForBadQuad(newtonObj,&newtestSimRoadInfo,iVar10);
              iVar11 = 0;
              if (iVar12 != 0) {
                pcVar9 = testSimRoadInfo.quadPts;
                local_78 = 0;
                local_7c = 0;
                local_80 = 0;
                for (; iVar11 < 4; iVar11 = iVar11 + 1) {
                  if (testSimRoadInfo.simQuad == (Trk_NewSimQuad *)0x0) {
                    pTVar7 = BWorldSm_slices + testSimRoadInfo.slice;
                    local_40 = pTVar7->center[0];
                    local_3c = pTVar7->center[1];
                    local_38 = pTVar7->center[2];
                  }
                  else {
                    local_40 = pcVar9->x;
                    local_3c = pcVar9->y;
                    local_38 = pcVar9->z;
                  }
                  pcVar9 = pcVar9 + 1;
                  local_80 = local_80 + local_40;
                  local_7c = local_7c + local_3c;
                  local_78 = local_78 + local_38;
                }
                if (local_80 < 0) {
                  local_80 = local_80 + 3;
                }
                local_80 = local_80 >> 2;
                if (local_7c < 0) {
                  local_7c = local_7c + 3;
                }
                local_7c = local_7c >> 2;
                if (local_78 < 0) {
                  local_78 = local_78 + 3;
                }
                local_78 = local_78 >> 2;
                local_a0.x = local_90 - local_80;
                local_a0.z = local_88 - local_78;
              }
            }
          }
        }
        local_a0.y = 0;
        Math_NormalizeShortVector(&local_a0);
      }
    }
    else {
      Newton_GenerateVector((int)testSimRoadInfo.offEdge,&local_a0,&newtonObj->simRoadInfo);
      local_a0.y = 0;
      Math_NormalizeShortVector(&local_a0);
      iVar14 = 1;
    }
    if (iVar14 != 0) {
      Newton_DoPostBarrierCollisionHandling(newtonObj,local_a0);
      iVar12 = carObj->wheel[iVar10].currentPos.y;
      iVar14 = carObj->wheel[iVar10].currentPos.z;
      (newtonObj->collision).collisionPoint.x = carObj->wheel[iVar10].currentPos.x;
      (newtonObj->collision).collisionPoint.y = iVar12;
      (newtonObj->collision).collisionPoint.z = iVar14;
      AIPhysic_ProcessBarrierCollision((Car_tObj *)newtonObj);
      if ((((Car_tObj *)newtonObj)->carFlags & 4U) != 0) {
        Physics_FixEngineRpm((Car_tObj *)newtonObj);
      }
      iVar14 = (newtonObj->collision).impulse;
      if (iVar14 < 0xa0001) {
        return;
      }
      iVar12 = 6;
      if ((iVar10 != 2) && (iVar12 = local_2c, iVar10 == 3)) {
        iVar12 = 4;
      }
      Newton_AddDamageZone(newtonObj,iVar14,iVar12,1);
      return;
    }
    iVar10 = iVar10 + 1;
    local_2c = local_2c + 2;
  } while( true );
}

/* ---- Newton_LimitAngularVelocity__FP13BO_tNewtonObj  [NEWTON.CPP:2440-2456] SLD-VERIFIED ---- */
void Newton_LimitAngularVelocity(BO_tNewtonObj *newtonObj)

{
  u_int uVar1;
  
  uVar1 = 0x18000;
  if ((0x18000 < newtonObj->angularVel.x) ||
     (uVar1 = 0xfffe8000, newtonObj->angularVel.x < -0x18000)) {
    newtonObj->angularVel.x = uVar1;
  }
  uVar1 = 0x18000;
  if ((0x18000 < newtonObj->angularVel.y) ||
     (uVar1 = 0xfffe8000, newtonObj->angularVel.y < -0x18000)) {
    newtonObj->angularVel.y = uVar1;
  }
  uVar1 = 0x18000;
  if ((0x18000 < newtonObj->angularVel.z) ||
     (uVar1 = 0xfffe8000, newtonObj->angularVel.z < -0x18000)) {
    newtonObj->angularVel.z = uVar1;
  }
  return;
}

/* ---- Newton_ApplyTheLawOfGravity__FP13BO_tNewtonObj  [NEWTON.CPP:2466-2733] SLD-VERIFIED ---- */
void Newton_ApplyTheLawOfGravity(Car_tObj *newtonObj)

{
  int objAltitude;
  int groundVel;
  coorddef collisionPoint;
  int elevationOfGround;
  int relativeClosingVelocity;
  coorddef normal;
  coorddef shadowNormal;
  int timeCount;
  int elapsedTime;
  int iTimeCount;
  int modifiedGravity;
  int bounceVel;
  int k;
  int scale;
  int iVar1;
  int iVar2;
  void *pvVar3;
  u_int uVar4;
  int iVar5;
  Car_tObj *pCVar6;
  int iVar7;
  int iVar8;
  coorddef cStack_60;
  coorddef cStack_50;
  coorddef cStack_40;
  int iStack_30;
  int iStack_2c;
  u_char auStack_28 [8];
  
  if (((newtonObj->N).active != '\0') &&
     (iVar1 = Sched_ExecuteCheck(1,3,(newtonObj->N).distToPlayer,(newtonObj->N).objID,&iStack_30,&iStack_2c,
       (char *)                         auStack_28,newtonObj->forceNoSimOptz), iVar1 != 0)) {
    if ((newtonObj->N).simOptz < 2) {
      iVar1 = Newton_FindGroundElevationAndNormal(&newtonObj->N,&cStack_60);
      cStack_50 = cStack_60;
      iVar7 = (newtonObj->N).groundElevation;
      (newtonObj->N).groundElevation = iVar1;
      iVar1 = (iVar1 - iVar7) * iStack_30;
      iVar8 = (newtonObj->N).objAltitude;
      iVar7 = fixedmult(iStack_2c * 0x4800,(newtonObj->N).gravityMult);
      iVar5 = (newtonObj->N).orientMat.m[3];
      (newtonObj->N).linearVel.y = (newtonObj->N).linearVel.y - iVar7;
      iVar7 = fixedmult(iVar5,cStack_60.x);
      iVar5 = fixedmult((newtonObj->N).orientMat.m[4],cStack_60.y);
      iVar2 = fixedmult((newtonObj->N).orientMat.m[5],cStack_60.z);
      (newtonObj->N).orientationToGround.y = iVar7 + iVar5 + iVar2;
      Newton_CalculateGroundShadowMatrix(&newtonObj->N,&cStack_50,
                                         (newtonObj->N).orientationToGround.y);
      iVar7 = (newtonObj->N).linearVel.x;
      iVar5 = (newtonObj->N).linearVel.z;
      if (iVar7 < 0) {
        iVar7 = -iVar7;
      }
      if (iVar5 < 0) {
        iVar5 = -iVar5;
      }
      iVar7 = Math_BetterDist(iVar7,iVar5);
      (newtonObj->N).speedXZ = iVar7;
      iVar7 = (newtonObj->N).roadGravityModifier * 7 + (iVar1 - (newtonObj->N).groundVel);
      if (iVar7 < 0) {
        iVar7 = iVar7 + 7;
      }
      (newtonObj->N).roadGravityModifier = iVar7 >> 3;
      (newtonObj->N).groundVel = iVar1;
      if (iVar8 < 0x3333) {
        if ((newtonObj->N).flightTime == 0) {
      Newton_CheckForSpikeBelts(&newtonObj->N);
        }
        else {
          if ((newtonObj->carFlags & 4U) != 0) {
            Physics_FixEngineRpm(newtonObj);
          }
          iVar5 = (newtonObj->N).linearVel.y;
          iVar7 = 0;
          if ((newtonObj->N).orientationToGround.y < 0xb334) {
            cStack_40.x = (newtonObj->N).roadCenterPoint.x;
            cStack_40.z = (newtonObj->N).roadCenterPoint.z;
            cStack_40.y = (newtonObj->N).roadCenterPoint.y + -0x1999;
            Collide_TestWithPlane(&newtonObj->N,&cStack_60,&cStack_40);
            iVar7 = (newtonObj->N).collision.impulse;
            if (0x50000 < iVar7) {
              iVar5 = 0x140000;
              if (0x13ffff < iVar7) {
                iVar5 = iVar7;
              }
              (newtonObj->N).collision.impulse = iVar5;
            }
            if ((newtonObj->N).orientationToGround.y < 0x3333) {
              (newtonObj->collision).smoking = 1;
            }
          }
          else {
            iVar2 = 0;
            pCVar6 = newtonObj;
            do {
              iVar2 = iVar2 + 1;
              iVar7 = iVar7 + pCVar6->wheel[0].wheelAcc;
              pCVar6 = (Car_tObj *)&(pCVar6->N).simRoadInfo.quadPts[2].z;
            } while (iVar2 < 4);
            if (0 < iVar7) {
              iVar7 = iVar7 * 3;
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              iVar2 = (newtonObj->N).position.y;
              (newtonObj->N).linearVel.y = iVar1 + (iVar7 >> 2);
              iVar7 = (iVar1 - iVar5) * 2;
              (newtonObj->N).collision.impulse = iVar7;
              (newtonObj->N).flightTime = 0;
              iVar2 = iVar2 - iVar8;
              iVar8 = 0xccc;
              (newtonObj->N).position.y = iVar2;
              (newtonObj->N).objAltitude = 0xccc;
              if (0x140000 < iVar7) {
                (newtonObj->N).collision.sfxType = 0x10000;
                (newtonObj->N).collision.otherObj = (BO_tNewtonObj *)0x0;
                iVar7 = (newtonObj->N).position.y;
                iVar5 = (newtonObj->N).position.z;
                (newtonObj->N).collision.collisionPoint.x = (newtonObj->N).position.x;
                (newtonObj->N).collision.collisionPoint.y = iVar7;
                (newtonObj->N).collision.collisionPoint.z = iVar5;
                Newton_AddDamageZone(&newtonObj->N,(newtonObj->N).collision.impulse,9,0);
              }
              iVar7 = Force_IsForceOn(newtonObj);
              if (iVar7 != 0) {
                Force_HitWall((newtonObj->N).collision.impulse);
              }
            }
          }
          Newton_LimitAngularVelocity(&newtonObj->N);
        }
        if (iVar8 < 0xa3d) {
          iVar7 = (newtonObj->N).position.y;
          uVar4 = newtonObj->carFlags;
          (newtonObj->N).objAltitude = 0;
          (newtonObj->N).position.y = iVar7 - iVar8;
          if (((uVar4 & 0x400) == 0) && (0xe666 < (newtonObj->N).orientationToGround.y)) {
            (newtonObj->N).flightTime = 0;
          }
          if (0x5ffff < iVar1) {
            iVar7 = 0xffdf;
            if (0xc0000 < iVar1) {
              iVar7 = 0xffbe;
            }
            iVar5 = fixedmult((newtonObj->N).linearVel.x,iVar7);
            iVar2 = (newtonObj->N).linearVel.z;
            (newtonObj->N).linearVel.x = iVar5;
            iVar7 = fixedmult(iVar2,iVar7);
            (newtonObj->N).linearVel.z = iVar7;
          }
          iVar7 = (newtonObj->N).speedXZ;
          if (iVar7 < 0x50000) {
            if (iVar1 < 0) {
              iVar1 = iVar1 + 3;
            }
            (newtonObj->N).linearVel.y = iVar1 >> 2;
          }
          else if (iVar7 < 0xa0000) {
            (newtonObj->N).linearVel.y = iVar1 / 2;
          }
          else {
            (newtonObj->N).linearVel.y = iVar1;
          }
        }
      }
      else {
        (newtonObj->N).roadGravityModifier = 0;
        (newtonObj->N).flightTime = (newtonObj->N).flightTime + (short)iStack_2c;
        iVar1 = fixedmult(iStack_2c * 0x4800,(newtonObj->N).gravityMult);
        (newtonObj->N).linearVel.y = (newtonObj->N).linearVel.y - iVar1;
      }
      (newtonObj->N).lastUpdated = simGlobal.gameTicks;
      pvVar3 = BWorldSm_TunnelFlagSm(&(newtonObj->N).simRoadInfo);
      if (((pvVar3 != (void *)0x0) && (iVar1 = (newtonObj->N).linearVel.y, 0 < iVar1)) &&
         (0x80000 < (newtonObj->N).position.y - (newtonObj->N).roadCenterPoint.y)) {
        (newtonObj->N).linearVel.y = -iVar1;
      }
    }
    else {
      (newtonObj->N).linearVel.y = 0;
      (newtonObj->N).flightTime = 0;
      iVar1 = Newton_FindGroundElevationAndNormalFast(&newtonObj->N,&cStack_60);
      (newtonObj->N).position.y = iVar1 + (newtonObj->N).dimension.y;
    }
  }
  return;
}

/* ---- Newton_CalculateRoadPositionFromSliceAndPosition__FiP8coorddefP10matrixtdef  [NEWTON.CPP:2736-2745] SLD-VERIFIED ---- */
int Newton_CalculateRoadPositionFromSliceAndPosition(int slice,coorddef *position,matrixtdef *matrix)

{
  int iVar1;
  Trk_NewSlice *pTVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  coorddef centerBack;
  coorddef carRelative;
  
  pTVar2 = BWorldSm_slices + slice;
  iVar6 = position->x - pTVar2->center[0];
  iVar7 = position->y - pTVar2->center[1];
  iVar1 = position->z - pTVar2->center[2];
  iVar3 = matrix->m[0];
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  iVar4 = matrix->m[1];
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  iVar5 = matrix->m[2];
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xff;
  }
  return (iVar3 >> 8) * (iVar6 >> 8) + (iVar4 >> 8) * (iVar7 >> 8) + (iVar5 >> 8) * (iVar1 >> 8);
}

/* ---- Newton_CalculateRoadPosition__FP13BO_tNewtonObj  [NEWTON.CPP:2762-2773] SLD-VERIFIED ---- */
int Newton_CalculateRoadPosition(BO_tNewtonObj *newtonObj)

{
  int ratio;
  Trk_NewSlice *pTVar1;
  int z;
  int iVar2;
  int oldOptz;
  int iVar3;
  int iVar4;
  int desiredCompression;
  int iVar5;
  int whichPlayer;
  int iVar6;
  int index;
  int iVar7;
  int v1;
  int zDir;
  int yDir;
  int xDir;
  int roll;
  int pitch;
  int forcedSimOptz;
  int r6;
  int r4;
  int bounce;
  int xMult;
  int wheelsInAir;
  coorddef tireCoord [4];
  coorddef carNormal;
  coorddef wheelHeight [4];
  coorddef vecOffset;
  BWorldSm_Pos testSimRoadInfo;
  coorddef tempVecX;
  coorddef tempVecY;
  int compressionValue [4];
  coorddef tempVecZ;
  coorddef centerBack;
  coorddef carRelative;
  coorddef carPos;
  
  pTVar1 = BWorldSm_slices + newtonObj->simRoadInfo.slice;
  iVar7 = newtonObj->position.x - pTVar1->center[0];
  iVar3 = newtonObj->position.y - pTVar1->center[1];
  iVar5 = newtonObj->position.z - pTVar1->center[2];
  iVar6 = newtonObj->roadMatrix.m[0];
  if (iVar6 < 0) {
    iVar6 = iVar6 + 0xff;
  }
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xff;
  }
  iVar2 = newtonObj->roadMatrix.m[1];
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0xff;
  }
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xff;
  }
  iVar4 = newtonObj->roadMatrix.m[2];
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0xff;
  }
  if (iVar5 < 0) {
    iVar5 = iVar5 + 0xff;
  }
  return (iVar6 >> 8) * (iVar7 >> 8) + (iVar2 >> 8) * (iVar3 >> 8) + (iVar4 >> 8) * (iVar5 >> 8);
}

/* end of newton.cpp */
