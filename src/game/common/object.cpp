/* game/common/object.cpp -- RECONSTRUCTED (track-object collision + custom-object pool +
 *   IMass scene props + ObjectMultiAnim/SignAnim animation classes; C++ TU, 36 fns).
 *   4 anim classes (: ObjectAnim) emitted as free fns (Class_ct/_dt/_Class_Draw) per
 *   track.obj convention (ctors explicitly called on __builtin_new memory).
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "object_externs.h"


/* EXT/STAT data OWNED by object.obj */
Group              *Object_customObjInst;   /* 0x8013d2c8 */
Group              *Object_customSimObjs;   /* 0x8013d2cc */
Group              *Object_customSFXInst;   /* 0x8013d2d0 */
int                 Object_customSliceNum;  /* 0x8013d2d4 */
ObjectAnim         *gSimObjAnims[450];
int                 gNumIMassObjects;
Object_tIMassObjInfo *Object_IMassObjInst;

/* ---- forward decls (VA-order) ---- */
int CalcObjYawAngle(CCOORD16 *pts);
void CalcObjExtentPoints(coorddef *cp,CCOORD16 *pts,coorddef *resultPts,tQuat *quat);
void BuildObjCollisionMatrix(int weight,int objAngle,int impactAngle,matrixtdef *mat);
Trk_SimpleInst * FindObjInstanceFromSerialNum(Group *group,int index);
void Object_InitCollisionCheckLoop(BWorldSm_Pos *slicePos,Object_tSimObjList *objList,int *numObj);
Trk_SimObject * GetSimObj(int objIndex,Object_tSimObjList *objList,int *chunk);
int Object_GetRadiusCollisionData(Object_tSimObjList *objList,int objIndex,coorddef *pos,int *radius);
void Object_GetPointsCollisionData(Object_tSimObjList *objList,int objIndex,int *numPoints,coorddef *resultPoints);
void Object_InitStatus(void);
void Object_KillStatus(void);
ObjectAnim * Object_GetAnim(Trk_SimObject *simObj);
int Object_CheckCollisionResults(Object_tSimObjList *objList,int objIndex,BO_tNewtonObj *N);
void Object_InitCustomObjects(void);
void Object_DeInitCustomObjects(void);
void Object_ClearCustomObjects(void);
void SetCautionSurface(coorddef *pt,BWorldSm_Pos *slicePos);
int Object_AddCustomSimObject(SceneElem *objectData,int serialNum,int instIndex);
int Object_GetObjDefID(int index);
int Object_FindDefWithThisID(int ID);
void Object_AddCustomObject(SceneElem *objectData,int setupSimDataFlag);
void GetObjMaxDimensions(Trk_ObjectDef **pObjDefs,Trk_SimpleInst *objInstance,coorddef *dimensions);
void Object_InitIMassObjectInfo(void);
void Object_DeInitIMassObjectInfo(void);
int Object_GetNumIMassObjects(void);
void Object_GetIMassObjectDimensions(int objIndex,coorddef *dimensions);
void Object_GetIMassObjectMotion(int objIndex,coorddef *cpoint,matrixtdef *orientMat,coorddef *velocity);
int NFS4_VT_THUNK ObjectFinishedMultiAnim_Draw(ObjectFinishedMultiAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset);
ObjectMultiAnim * ObjectMultiAnim_ct(ObjectMultiAnim *pThis,coorddef *impactVel,AnimDef *def, Trk_CollideBoomInst *objCollideInstance,Trk_ObjectDef *objDef,Trk_SimObject *simObj, ObjectFinishedMultiAnim *finishedAnim);
int NFS4_VT_THUNK ObjectMultiAnim_Draw(ObjectMultiAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset);
int NFS4_VT_THUNK ObjectFinishedSignAnim_Draw(ObjectFinishedSignAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset);
ObjectSignAnim * ObjectSignAnim_ct(ObjectSignAnim *pThis,coorddef *impactVel,int impactAngle,AnimDef *def, Trk_CollideBoomInst *objCollideInstance,Trk_ObjectDef *objDef,Trk_SimObject *simObj, coorddef *roadNormal,ObjectFinishedSignAnim *finishedAnim);
int NFS4_VT_THUNK ObjectSignAnim_Draw(ObjectSignAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset);
void NFS4_VT_THUNK ObjectSignAnim_dt(ObjectSignAnim *pThis,int __in_chrg);
void NFS4_VT_THUNK ObjectFinishedSignAnim_dt(ObjectFinishedSignAnim *pThis,int __in_chrg);
void NFS4_VT_THUNK ObjectMultiAnim_dt(ObjectMultiAnim *pThis,int __in_chrg);
void NFS4_VT_THUNK ObjectFinishedMultiAnim_dt(ObjectFinishedMultiAnim *pThis,int __in_chrg);


/* ---- CalcObjYawAngle  [OBJECT.CPP:69-74] SLD-VERIFIED ---- */


int CalcObjYawAngle(CCOORD16 *pts)

{
  int angle;
  
  angle = fixedatan((int)pts[1].x - (int)pts->x,(int)pts[1].z - (int)pts->z);
  return nfs4_mips_sra_s32(nfs4_mips_addu_s32(angle,-0x4000),8);
}



/* ---- CalcObjExtentPoints  [OBJECT.CPP:78-98] SLD-VERIFIED ---- */
void CalcObjExtentPoints(coorddef *cp,CCOORD16 *pts,coorddef *resultPts,tQuat *quat)

{
  int tmpx;
  int cpx;
  int cpz;
  matrixtdef matrix;
  coorddef pt0;
  coorddef pt1;

  cpx = cp->x;
  cpz = cp->z;
  pt0.x = nfs4_mips_sll_s32(pts->x,10);
  pt0.z = nfs4_mips_sll_s32(pts->z,10);
  pt1.x = nfs4_mips_sll_s32(pts[1].x,10);
  pt1.z = nfs4_mips_sll_s32(pts[1].z,10);
  resultPts->x = cpx;
  resultPts->z = cpz;
  Quatern_QuatToMat(quat,&matrix);
  transform(&pt0.x,matrix.m,&resultPts[1].x);
  transform(&pt1.x,matrix.m,&resultPts[2].x);
  resultPts[1].x = nfs4_mips_addu_s32(resultPts[1].x,cpx);
  tmpx = resultPts[2].x;
  resultPts[1].z = nfs4_mips_addu_s32(resultPts[1].z,cpz);
  resultPts[2].x = nfs4_mips_addu_s32(tmpx,cpx);
  resultPts[2].z = nfs4_mips_addu_s32(resultPts[2].z,cpz);
  return;
}

/* ---- BuildObjCollisionMatrix  [OBJECT.CPP:121-140] SLD-VERIFIED ---- */


void BuildObjCollisionMatrix(int weight,int objAngle,int impactAngle,matrixtdef *mat)

{
  int impactComp;
  int objComp;
  matrixtdef impactMat;
  matrixtdef objAngleMat;
  matrixtdef tmpMat;
  
  impactComp = fixedmult(nfs4_mips_negu_s32(impactAngle),nfs4_mips_subu_s32(0x10000,weight));
  objComp = fixedmult(nfs4_mips_negu_s32(objAngle),weight);
  fixedxformy(&objAngleMat,nfs4_mips_addu_s32(impactComp,objComp));
  fixedxformy(&impactMat,impactAngle);
  Math_fasttransmult(&objAngleMat,mat,&tmpMat);
  Math_fasttransmult(&tmpMat,&impactMat,mat);
  return;
}



/* ---- FindObjInstanceFromSerialNum  [OBJECT.CPP:144-176] SLD-VERIFIED ---- */


Trk_SimpleInst *
FindObjInstanceFromSerialNum(Group *group,int index)

{
  int count;
  Group *pThis;
  Trk_SimpleInst *objInstance;
  
  if (1 < index - 0x7eU) {
    if ((index & 0x80U) == 0) {
      count = group->m_num_elements;
    }
    else {
      count = Object_customObjInst->m_num_elements;
      index = index & 0xffffff7f;
      group = Object_customObjInst;
    }
    if (index < count) {
      objInstance = (Trk_SimpleInst *)(group + 1);
      while (index = index - 1, index != 0xffffffff) {
        objInstance = (Trk_SimpleInst *)((u_char *)objInstance + objInstance->size);
      }
      return objInstance;
    }
  }
  return (Trk_SimpleInst *)0x0;
}



/* ---- Object_InitCollisionCheckLoop  [OBJECT.CPP:190-243] SLD-VERIFIED ---- */
void Object_InitCollisionCheckLoop(BWorldSm_Pos *slicePos,Object_tSimObjList *objList,int *numObj)

{
  Group *pThis;
  int altChunk;
  int iVar2;
  int total;

  pThis = Track_chunkList[slicePos->chunk].simObjBuf;
  if (pThis == (Group *)0x0) {
    objList->numObjects = 0;
  }
  else {
    objList->numObjects = pThis->m_num_elements;
  }
  objList->numObjects2 = 0;
  objList->chunk = (int)slicePos->chunk;
  iVar2 = slicePos->slice + 1;
  if (gNumSlices <= iVar2) {
    iVar2 = slicePos->slice - (gNumSlices + -1);
  }
  altChunk = (int)BWorldSm_slices[iVar2].chunkIndex;
  if ((altChunk == slicePos->chunk) || (Track_chunkList[altChunk].simObjBuf == (Group *)0x0)) {
    iVar2 = slicePos->slice + -1;
    if (iVar2 < 0) {
      iVar2 = slicePos->slice + gNumSlices + -1;
    }
    altChunk = (int)BWorldSm_slices[iVar2].chunkIndex;
    if ((altChunk == slicePos->chunk) || (Track_chunkList[altChunk].simObjBuf == (Group *)0x0)) {
      total = objList->numObjects;
    }
    else {
      objList->numObjects2 = Track_chunkList[altChunk].simObjBuf->m_num_elements;
      objList->chunk2 = altChunk;
      total = objList->numObjects + objList->numObjects2;
    }
  }
  else {
    objList->numObjects2 = Track_chunkList[altChunk].simObjBuf->m_num_elements;
    objList->chunk2 = altChunk;
    total = objList->numObjects + objList->numObjects2;
  }
  *numObj = total;
  if (((Object_customSimObjs != (Group *)0x0) && (0 < Object_customSimObjs->m_num_elements)) &&
     (iVar2 = Math_DistXZ((coorddef *)(BWorldSm_slices + Object_customSliceNum),
                          (coorddef *)(BWorldSm_slices + slicePos->slice)), iVar2 < 0xc00000)) {
    *numObj = *numObj + Object_customSimObjs->m_num_elements;
  }
  return;
}

/* ---- GetSimObj  [OBJECT.CPP:256-290] SLD-VERIFIED ---- */


Trk_SimObject *
GetSimObj(int objIndex,Object_tSimObjList *objList,int *chunk)

{
  Group *custom;
  int index;
  Trk_SimObject *simObj;
  
  custom = Object_customSimObjs;
  simObj = (Trk_SimObject *)0x0;
  if (objList->numObjects + objList->numObjects2 <= objIndex) {
    index = objIndex - objList->numObjects - objList->numObjects2;
    *chunk = -1;
    return (Trk_SimObject *)(custom + 1) + index;
  }
  *chunk = objList->chunk;
  if (objList->numObjects <= objIndex) {
    objIndex = objIndex - objList->numObjects;
    *chunk = objList->chunk2;
  }
  if ((Track_chunkList[*chunk].simObjBuf != (Group *)0x0) &&
     (simObj = (Trk_SimObject *)(Track_chunkList[*chunk].simObjBuf + 1) + objIndex,
     simObj->type == '\x10')) {
    simObj = (Trk_SimObject *)0x0;
  }
  return simObj;
}



/* ---- Object_GetRadiusCollisionData  [OBJECT.CPP:304-330] SLD-VERIFIED ---- */


int Object_GetRadiusCollisionData(Object_tSimObjList *objList,int objIndex,coorddef *pos,int *radius)

{
  Trk_SimObject *simObj;
  Trk_SimpleInst *animInst;
  Chunk *pMChunk;
  int iVar1;
  int iVar2;
  int chunk;
  int dummy;
  
  simObj = GetSimObj(objIndex,objList,&chunk);
  if (simObj == (Trk_SimObject *)0x0) {
    *radius = 0;
  }
  else {
    if (((simObj->type & 0x80) != 0) && (gSimObjAnims[simObj->serialNum] == (ObjectAnim *)0x0)) {
      animInst = FindObjInstanceFromSerialNum(Track_chunkList[chunk].objInstanceBuf,(u_int)simObj->instIndex);
      Anim_GetPos((Trk_AnimateInst *)animInst,1,simGlobal.gameTicks,(coorddef *)simObj,&dummy,&dummy);
    }
    iVar1 = simObj->point[1];
    iVar2 = simObj->point[2];
    pos->x = simObj->point[0];
    pos->y = iVar1;
    pos->z = iVar2;
    *radius = nfs4_mips_sll_s32(simObj->radius,7);
  }
  return 0;
}



/* ---- Object_GetPointsCollisionData  [OBJECT.CPP:336-381] SLD-VERIFIED ---- */


void Object_GetPointsCollisionData(Object_tSimObjList *objList,int objIndex,int *numPoints,coorddef *resultPoints)

{
  u_char bVar1;
  Trk_SimObject *simObj;
  Trk_SimpleInst *objInstance;
  Group *group;
  Trk_ObjectDef *objDef;
  int iVar3;
  int iVar4;
  int chunk;
  
  simObj = GetSimObj(objIndex,objList,&chunk);
  if (simObj == (Trk_SimObject *)0x0) {
    *numPoints = 0;
  }
  else {
    if (chunk == -1) {
      bVar1 = simObj->instIndex;
      group = (Group *)0x0;
    }
    else {
      bVar1 = simObj->instIndex;
      group = Track_chunkList[chunk].objInstanceBuf;
    }
    objInstance = FindObjInstanceFromSerialNum(group,(u_int)bVar1);
    if (objInstance == (Trk_SimpleInst *)0x0) {
      *numPoints = 1;
      iVar3 = simObj->point[1];
      iVar4 = simObj->point[2];
      resultPoints->x = simObj->point[0];
      resultPoints->y = iVar3;
      resultPoints->z = iVar4;
    }
    else if ((objInstance->type == '\x05') &&
             (((Trk_CollideBoomInst *)objInstance)->boomIndex == 0)) {
      CalcObjExtentPoints((coorddef *)simObj,(CCOORD16 *)(Track_gObjDefs[objInstance->pad] + 1),resultPoints,
                 (tQuat *)(objInstance + 1));
      *numPoints = 3;
    }
    else {
      iVar3 = simObj->point[1];
      iVar4 = simObj->point[2];
      resultPoints->x = simObj->point[0];
      resultPoints->y = iVar3;
      resultPoints->z = iVar4;
      *numPoints = 1;
    }
  }
  return;
}



/* ---- Object_InitStatus  [OBJECT.CPP:398-404] SLD-VERIFIED ---- */


void Object_InitStatus(void)

{
  ObjectAnim **ppOVar1;
  int i;
  
  i = 0x1c1;
  ppOVar1 = gSimObjAnims + 0x1c1;
  do {
    *ppOVar1 = (ObjectAnim *)0x0;
    i = i + -1;
    ppOVar1 = ppOVar1 + -1;
  } while (-1 < i);
  return;
}



/* ---- Object_KillStatus  [OBJECT.CPP:408-415] SLD-VERIFIED ---- */


void Object_KillStatus(void)

{
  ObjectAnim *pOVar1;
  ObjectAnim **ppOVar2;
  int i;
  
  i = 0;
  ppOVar2 = gSimObjAnims;
  do {
    pOVar1 = *ppOVar2;
    if (pOVar1 != (ObjectAnim *)0x0) {
      __nfs4_vtbl_ptr_t *entry = &(*pOVar1->_vf)[1];
      nfs4_vcall_dtor(entry->pfn,(u_char *)pOVar1 + entry->delta,3);
    }
    i = i + 1;
    ppOVar2 = ppOVar2 + 1;
  } while (i < 0x1c2);
  return;
}



/* ---- Object_GetAnim  [OBJECT.CPP:427-430] SLD-VERIFIED ---- */


ObjectAnim * Object_GetAnim(Trk_SimObject *simObj)

{
  if (simObj != (Trk_SimObject *)0x0) {
    return gSimObjAnims[simObj->serialNum];
  }
  return (ObjectAnim *)0x0;
}



/* ---- Object_CheckCollisionResults  [OBJECT.CPP:455-557] SLD-VERIFIED ---- */
int Object_CheckCollisionResults(Object_tSimObjList *objList,int objIndex,BO_tNewtonObj *N)

{
  int iVar1;
  Trk_SimObject *simObj;
  ObjectAnim *objStatus;
  Trk_CollideBoomInst *objInstance;
  ObjectFinishedMultiAnim *finishedMulti;
  ObjectMultiAnim *multiAnim;
  ObjectSignAnim *signAnim;
  ObjectFinishedSignAnim *finishedSign;
  Chunk *pMChunk;
  int iVar3;
  u_char type;
  u_char boomIndex;
  AnimDef *animDef;
  Trk_ObjectDef *objDef;
  int vel;
  int ret;
  int chunk;

  iVar3 = (N->linearVel).x;
  iVar1 = (N->linearVel).z;
  if (iVar3 < 0) {
    iVar3 = nfs4_mips_negu_s32(iVar3);
  }
  if (iVar1 < 0) {
    iVar1 = nfs4_mips_negu_s32(iVar1);
  }
  simObj = GetSimObj(objIndex,objList,&chunk);
  type = simObj->type & 0xf;
  if (type == 2) {
    objStatus = gSimObjAnims[simObj->serialNum];
    if (objStatus != (ObjectAnim *)0x0) {
      return 0;
    }
    if (-1 < nfs4_mips_sra_s32(nfs4_mips_addu_s32(iVar3,iVar1),0x10)) {
      objInstance = (Trk_CollideBoomInst *)
           FindObjInstanceFromSerialNum(Track_chunkList[chunk].objInstanceBuf,(int)simObj->instIndex);
      if (objInstance->type == '\x06') {
        boomIndex = ((Trk_AnimateBoomInst *)objInstance)->boomIndex;
      }
      else {
        boomIndex = objInstance->boomIndex;
      }
      animDef = gAnimDefs + boomIndex;
      if (gAnimDefs[boomIndex].animIndex == 0) {
        objDef = Track_gObjDefs[objInstance->pad];
      }
      else {
        objDef = (Trk_ObjectDef *)(gPersistObjDef + 1);
      }
      if (animDef->type == 0) {
        finishedSign = (ObjectFinishedSignAnim *)__builtin_new(sizeof(ObjectFinishedSignAnim));
        (finishedSign->_base_ObjectAnim)._vf =
             (__vtbl_ptr_type (*) [3])ObjectFinishedSignAnim_vtable;
        signAnim = (ObjectSignAnim *)__builtin_new(sizeof(ObjectSignAnim));
        vel = fixedatan(nfs4_mips_sra_s32((N->linearVel).x,8),
                        nfs4_mips_sra_s32((N->linearVel).z,8));
        signAnim = ObjectSignAnim_ct(signAnim,&N->linearVel,nfs4_mips_sra_s32(vel,8),animDef,objInstance,objDef,
                                     simObj,(coorddef *)((N->roadMatrix).m + 3),finishedSign);
      }
      else {
        if (animDef->type != 1) {
          return -1;
        }
        finishedMulti = (ObjectFinishedMultiAnim *)__builtin_new(sizeof(ObjectFinishedMultiAnim));
        (finishedMulti->_base_ObjectAnim)._vf =
             (__vtbl_ptr_type (*) [3])ObjectFinishedMultiAnim_vtable;
        multiAnim = (ObjectMultiAnim *)__builtin_new(sizeof(ObjectMultiAnim));
        signAnim = (ObjectSignAnim *)
                   ObjectMultiAnim_ct(multiAnim,&N->linearVel,animDef,objInstance,objDef,simObj,
                                      finishedMulti);
      }
      ret = -1;
      gSimObjAnims[simObj->serialNum] = &signAnim->_base_ObjectAnim;
      return ret;
    }
  }
  else {
    if (2 < type) {
      if (type != 3) {
        return 0;
      }
      return 2;
    }
    if (type != 1) {
      return 0;
    }
  }
  return 1;
}

/* ---- Object_InitCustomObjects  [OBJECT.CPP:581-594] SLD-VERIFIED ---- */


void Object_InitCustomObjects(void)

{
  Group *dst;
  
  Object_customObjInst = (Group *)reservememadr("Custom Objects",0x400,0);
  Object_customObjInst->m_num_elements = 0;
  Object_customSimObjs = (Group *)reservememadr("Custom SimObjects",0x400,0);
  dst = Object_customSimObjs + 1;
  Object_customSimObjs->m_num_elements = 0;
  blockfill(dst,0x3fc,0);
  Object_customSFXInst = (Group *)reservememadr("Custom SimObjects",0x400,0);
  Object_customSFXInst->m_num_elements = 0;
  Object_customSliceNum = 0;
  return;
}



/* ---- Object_DeInitCustomObjects  [OBJECT.CPP:600-610] SLD-VERIFIED ---- */


void Object_DeInitCustomObjects(void)

{
  if (Object_customObjInst != (Group *)0x0) {
    purgememadr(Object_customObjInst);
  }
  if (Object_customSFXInst != (Group *)0x0) {
    purgememadr(Object_customSFXInst);
  }
  if (Object_customSimObjs != (Group *)0x0) {
    purgememadr(Object_customSimObjs);
  }
  Object_customObjInst = (Group *)0x0;
  Object_customSFXInst = (Group *)0x0;
  Object_customSimObjs = (Group *)0x0;
  return;
}



/* ---- Object_ClearCustomObjects  [OBJECT.CPP:616-635] SLD-VERIFIED ---- */


void Object_ClearCustomObjects(void)

{
  int iVar1;
  Group *pGVar2;
  Group *pGVar3;
  Car_tObj **ppCVar4;
  int i;
  
  pGVar3 = Object_customSFXInst;
  pGVar2 = Object_customSimObjs;
  iVar1 = Cars_gNumTrafficCars;
  i = 0;
  Object_customObjInst->m_num_elements = 0;
  pGVar2->m_num_elements = 0;
  pGVar3->m_num_elements = 0;
  if (0 < iVar1) {
    ppCVar4 = Cars_gTrafficCarList;
    do {
      i = i + 1;
      (*ppCVar4)->carFlags = (*ppCVar4)->carFlags & 0xfffffbff;
      ppCVar4 = ppCVar4 + 1;
    } while (i < iVar1);
  }
  iVar1 = Cars_gNumCopCars;
  i = 0;
  if (0 < Cars_gNumCopCars) {
    ppCVar4 = Cars_gCopCarList;
    do {
      i = i + 1;
      (*ppCVar4)->carFlags = (*ppCVar4)->carFlags & 0xfffffbff;
      ppCVar4 = ppCVar4 + 1;
    } while (i < iVar1);
  }
  if (Track_gSaveSurface != (SaveSurface *)0x0) {
    RestoreAll(Track_gSaveSurface);
  }
  return;
}



/* ---- SetCautionSurface  [OBJECT.CPP:648-657] SLD-VERIFIED ---- */
void SetCautionSurface(coorddef *pt,BWorldSm_Pos *slicePos)

{
  Trk_NewSimQuad *simQuad;

  BWorldSm_FindClosestQuadRez(pt,slicePos,1);
  simQuad = slicePos->simQuad;
  if ((simQuad != (Trk_NewSimQuad *)0x0) && ((simQuad->surface & 0x40) == 0)) {
    Save(Track_gSaveSurface,simQuad);
    slicePos->simQuad->surface = slicePos->simQuad->surface | 0x40;
  }
  return;
}

/* ---- Object_AddCustomSimObject  [OBJECT.CPP:668-718] SLD-VERIFIED ---- */


int Object_AddCustomSimObject(SceneElem *objectData,int serialNum,int instIndex)

{
  u_char tu1;
  Group *pThis;
  int iVar1;
  Trk_SimObject *simObj;
  BWorldSm_Pos slicePos;
  coorddef pt;
  
  if (objectData->type == 0) {
    simObj = (Trk_SimObject *)(Object_customSimObjs + 1) +
             Object_customSimObjs->m_num_elements;
    simObj->point[0] = (objectData->cp).x;
    simObj->point[1] = (objectData->cp).y;
    simObj->point[2] = (objectData->cp).z;
    BWorldSm_SetSlice(1,&slicePos);
    pt.x = (objectData->cp).x;
    pt.y = (objectData->cp).y;
    pt.z = (objectData->cp).z;
    SetCautionSurface(&pt,&slicePos);
    pt.x = pt.x + -0x40000;
    SetCautionSurface(&pt,&slicePos);
    pt.x = pt.x + 0x80000;
    SetCautionSurface(&pt,&slicePos);
    pt.x = pt.x + -0x40000;
    pt.z = pt.z + -0x40000;
    SetCautionSurface(&pt,&slicePos);
    pt.z = pt.z + 0x80000;
    SetCautionSurface(&pt,&slicePos);
    Object_customSliceNum = (int)slicePos.slice;
    iVar1 = objectData->scalar2;
    simObj->serialNum = (short)serialNum + 400;
    simObj->radius = (short)(iVar1 >> 9);
    simObj->instIndex = (u_char)(instIndex - 0x80);
    tu1 = 2;
    if (8 < objectData->scalar1) {
      tu1 = 1;
    }
    simObj->type = tu1;
    Object_customSimObjs->m_num_elements = Object_customSimObjs->m_num_elements + 1;
  }
  return Object_customSimObjs->m_num_elements + -1;
}



/* ---- Object_GetObjDefID  [OBJECT.CPP:785-790] SLD-VERIFIED ---- */


int Object_GetObjDefID(int index)

{
  if ((gPersistObjDef != (Group *)0x0) && (index < gPersistObjDef->m_num_elements)) {
    return (int)Track_gObjDefs[index]->id;
  }
  return 0;
}



/* ---- Object_FindDefWithThisID  [OBJECT.CPP:794-800] SLD-VERIFIED ---- */


int Object_FindDefWithThisID(int ID)

{
  Group *pThis;
  Trk_ObjectDef *objDef;
  int i;
  Trk_ObjectDef **ppTVar2;
  
  i = 0;
  ppTVar2 = Track_gObjDefs;
  while( true ) {
    if (gPersistObjDef->m_num_elements <= i) {
      return -1;
    }
    objDef = *ppTVar2;
    ppTVar2 = ppTVar2 + 1;
    if (ID == objDef->id) break;
    i = i + 1;
  }
  return i;
}



/* ---- Object_AddCustomObject  [OBJECT.CPP:808-1002] SLD-VERIFIED ---- */
void Object_AddCustomObject(SceneElem *objectData,int setupSimDataFlag)

{
  short sVar1;
  u_char groupFlag;
  AIHigh_Traffic *aicar;
  Car_tObj *carObj;
  SceneElem *accidentData;
  Group *objDefs;
  Trk_CollideBoomInst *objBoomInstance;
  int newInd;
  int index;
  int iVar3;
  Car_tObj **ppCVar4;
  int i;
  Trk_SFX *sfxInstance;
  Trk_CollideBoomInst *firstCustomInstance;
  Trk_CollideBoomInst *customInstance;
  tQuat quat;

  iVar3 = objectData->type;
  if (iVar3 == 1) {
    i = 0;
    if (((objectData->subType == 0) && (Cars_gNumTrafficCars != 0)) && (0 < Cars_gNumTrafficCars)) {
      ppCVar4 = Cars_gTrafficCarList;
      do {
        if ((((*ppCVar4)->carFlags & 0x400U) == 0) &&
           ((int)((*ppCVar4)->render).currentCarType == objectData->scalar3)) break;
        i = i + 1;
        ppCVar4 = ppCVar4 + 1;
      } while (i < Cars_gNumTrafficCars);
      if (i < Cars_gNumTrafficCars) {
        carObj = Cars_gTrafficCarList[i];
        accidentData = objectData;
        aicar = highLevelAIObjs[carObj->carIndex];
        aicar->accidentData_ = accidentData;
      }
    }
  }
  else if (iVar3 < 2) {
    if (iVar3 == 0) {
      newInd = Object_customObjInst->m_num_elements + -1;
      firstCustomInstance = (Trk_CollideBoomInst *)(Object_customObjInst + 1);
      customInstance = firstCustomInstance;
      if (newInd != -1) {
        do {
          newInd = newInd + -1;
          customInstance = (Trk_CollideBoomInst *)
              ((u_char *)customInstance + firstCustomInstance->size);
        } while (newInd != -1);
      }
      customInstance->size = 0x24;
      groupFlag = 5;
      if (8 < objectData->scalar1) {
        groupFlag = 2;
      }
      customInstance->type = groupFlag;
      customInstance->objectIndex = 3;
      customInstance->zoffset = 0;
      customInstance->x = (objectData->cp).x;
      customInstance->y = (objectData->cp).y;
      iVar3 = (objectData->cp).z;
      customInstance->flags = 0;
      objDefs = gPersistObjDef;
      customInstance->z = iVar3;
      index = objectData->subTypeIndex;
      sVar1 = (short)index;
      customInstance->pad = sVar1;
      if (objDefs->m_num_elements <= (int)sVar1) {
        customInstance->pad = 0;
      }
      if ((objectData->committed != 0) && (objectData->visible != 0)) {
        iVar3 = Object_GetObjDefID((int)customInstance->pad);
        if (iVar3 != objectData->scalar1) {
          Object_FindDefWithThisID(objectData->scalar1);
          iVar3 = Object_FindDefWithThisID(objectData->scalar1);
          if (iVar3 == -1) {
            iVar3 = Object_GetObjDefID((int)customInstance->pad);
            objectData->scalar1 = iVar3;
          }
          else {
            customInstance->pad = (short)iVar3;
            objectData->subTypeIndex = iVar3;
            Object_FindDefWithThisID(objectData->scalar1);
          }
        }
      }
      objBoomInstance = customInstance;
      Quatern_MatToQuat(&objectData->orient,&quat);
      objBoomInstance->qw = quat.w;
      objBoomInstance->qx = quat.x;
      objBoomInstance->qy = quat.y;
      objBoomInstance->sx = 0x100;
      objBoomInstance->sy = 0x100;
      objBoomInstance->sz = 0x100;
      objBoomInstance->qz = quat.z;
      if (setupSimDataFlag == 0) {
        objBoomInstance->simIndex = 0;
        objBoomInstance->boomIndex = 0;
      }
      else {
        iVar3 = Object_AddCustomSimObject(objectData,Object_customObjInst->m_num_elements,
                                          Object_customObjInst->m_num_elements);
        objBoomInstance->simIndex = (u_char)iVar3;
        objBoomInstance->boomIndex = (u_char)objectData->scalar1;
      }
      Object_customObjInst->m_num_elements = Object_customObjInst->m_num_elements + 1;
    }
  }
  else if (iVar3 == 2) {
    sfxInstance = (Trk_SFX *)(Object_customSFXInst + 1) +
                  Object_customSFXInst->m_num_elements;
    sfxInstance->point[0] = (objectData->cp).x;
    sfxInstance->point[1] = (objectData->cp).y;
    sfxInstance->point[2] = (objectData->cp).z;
    iVar3 = objectData->subType;
    sfxInstance->pad = 0;
    sfxInstance->type = (short)iVar3;
    Object_customSFXInst->m_num_elements = Object_customSFXInst->m_num_elements + 1;
  }
  return;
}

/* ---- GetObjMaxDimensions  [OBJECT.CPP:1011-1048] SLD-VERIFIED ---- */
void GetObjMaxDimensions(Trk_ObjectDef **pObjDefs,Trk_SimpleInst *objInstance,coorddef *dimensions)

{
  Trk_ObjectDef *objDef;
  int vertCount;
  CCOORD16 *pts;
  CCOORD16 minDim;
  CCOORD16 maxDim;

  objDef = pObjDefs[objInstance->pad];
  memset(&minDim,0,8);
  memset(&maxDim,0,8);
  vertCount = (int)objDef->vertexCount;
  pts = (CCOORD16 *)(objDef + 1);
  while (vertCount = vertCount + -1, vertCount != -1) {
    if (maxDim.x < pts->x) {
      maxDim.x = pts->x;
    }
    else if (pts->x < minDim.x) {
      minDim.x = pts->x;
    }
    if (maxDim.y < pts->y) {
      maxDim.y = pts->y;
    }
    else if (pts->y < minDim.y) {
      minDim.y = pts->y;
    }
    if (maxDim.z < pts->z) {
      maxDim.z = pts->z;
    }
    else if (pts->z < minDim.z) {
      minDim.z = pts->z;
    }
    pts = pts + 1;
  }
  dimensions->x = ((int)maxDim.x - (int)minDim.x) * 0x200;
  dimensions->y = ((int)maxDim.y - (int)minDim.y) * 0x200;
  dimensions->z = ((int)maxDim.z - (int)minDim.z) * 0x200;
  return;
}

/* ---- Object_InitIMassObjectInfo  [OBJECT.CPP:1055-1088] SLD-VERIFIED ---- */


void Object_InitIMassObjectInfo(void)

{
  Trk_ObjectDef **pObjDefs;
  Object_tIMassObjInfo *pOVar1;
  Trk_SimpleInst *objInst;
  int objIndex;
  
  gNumIMassObjects = 0;
  Object_IMassObjInst = (Object_tIMassObjInfo *)0x0;
  if ((gPersistObjInst != (Group *)0x0) && (gPersistObjDef != (Group *)0x0)) {
    Object_IMassObjInst =
         (Object_tIMassObjInfo *)reservememadr("IMObj info",
                       gPersistObjInst->m_num_elements * sizeof(*Object_IMassObjInst),0)
    ;
    objIndex = 0;
    if ((Object_IMassObjInst != (Object_tIMassObjInfo *)0x0) &&
       (objInst = (Trk_SimpleInst *)(gPersistObjInst + 1), 0 < gPersistObjInst->m_num_elements))
    {
      do {
        pObjDefs = Track_gObjDefs;
        if (objInst->type == '\a') {
          pOVar1 = Object_IMassObjInst + gNumIMassObjects;
          pOVar1->animInst = (Trk_AnimateInst *)objInst;
          GetObjMaxDimensions(pObjDefs,objInst,&pOVar1->dimension);
          pOVar1 = Object_IMassObjInst;
          Object_IMassObjInst[gNumIMassObjects].lastPos.x = 0;
          pOVar1[gNumIMassObjects].lastPos.y = 0;
          pOVar1[gNumIMassObjects].lastPos.z = 0;
          pOVar1[gNumIMassObjects].lastTick = 0;
          gNumIMassObjects = gNumIMassObjects + 1;
        }
        objIndex = objIndex + 1;
        objInst = (Trk_SimpleInst *)((u_char *)objInst + objInst->size);
      } while (objIndex < gPersistObjInst->m_num_elements);
    }
  }
  return;
}



/* ---- Object_DeInitIMassObjectInfo  [OBJECT.CPP:1093-1095] SLD-VERIFIED ---- */


void Object_DeInitIMassObjectInfo(void)

{
  if (Object_IMassObjInst != (Object_tIMassObjInfo *)0x0) {
    purgememadr(Object_IMassObjInst);
  }
  return;
}



/* ---- Object_GetNumIMassObjects  [OBJECT.CPP:1101-1102] SLD-VERIFIED ---- */


int Object_GetNumIMassObjects(void)

{
  return gNumIMassObjects;
}



/* ---- Object_GetIMassObjectDimensions  [OBJECT.CPP:1108-1111] SLD-VERIFIED ---- */


void Object_GetIMassObjectDimensions(int objIndex,coorddef *dimensions)

{
  int iVar1;
  int iVar2;
  
  iVar1 = Object_IMassObjInst[objIndex].dimension.y;
  iVar2 = Object_IMassObjInst[objIndex].dimension.z;
  dimensions->x = Object_IMassObjInst[objIndex].dimension.x;
  dimensions->y = iVar1;
  dimensions->z = iVar2;
  return;
}



/* ---- Object_GetIMassObjectMotion  [OBJECT.CPP:1117-1143] SLD-VERIFIED ---- */
void Object_GetIMassObjectMotion(int objIndex,coorddef *cpoint,matrixtdef *orientMat,coorddef *velocity)

{
  Object_tIMassObjInfo *pOVar1;
  int iVar2;
  int iVar3;
  int objTime;
  int timeDiff;

  objTime = DrawW_GetAnimationTime(Object_IMassObjInst[objIndex].animInst);
  Anim_GetRotPos(Object_IMassObjInst[objIndex].animInst,1,objTime,cpoint,orientMat);
  pOVar1 = Object_IMassObjInst;
  timeDiff = objTime - Object_IMassObjInst[objIndex].lastTick;
  if (timeDiff < 1) {
    velocity->x = 0;
    velocity->y = 0;
    velocity->z = 0;
  }
  else {
    iVar3 = cpoint->x - Object_IMassObjInst[objIndex].lastPos.x;
    velocity->x = nfs4_mips_sll_s32(iVar3 / timeDiff,6);
    iVar3 = cpoint->y - pOVar1[objIndex].lastPos.y;
    velocity->y = nfs4_mips_sll_s32(iVar3 / timeDiff,6);
    iVar3 = cpoint->z - pOVar1[objIndex].lastPos.z;
    velocity->z = nfs4_mips_sll_s32(iVar3 / timeDiff,6);
  }
  pOVar1 = Object_IMassObjInst;
  iVar2 = cpoint->y;
  iVar3 = cpoint->z;
  Object_IMassObjInst[objIndex].lastPos.x = cpoint->x;
  pOVar1[objIndex].lastPos.y = iVar2;
  pOVar1[objIndex].lastPos.z = iVar3;
  pOVar1[objIndex].lastTick = objTime;
  return;
}

/* ---- ObjectFinishedMultiAnim_Draw  [OBJECT.CPP:1160-1161] SLD-VERIFIED ---- */

int NFS4_VT_THUNK ObjectFinishedMultiAnim_Draw(ObjectFinishedMultiAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset)

{
  return 2;
}



/* ---- ObjectMultiAnim_ct  [OBJECT.CPP:1165-1183] SLD-VERIFIED ---- */
ObjectMultiAnim * ObjectMultiAnim_ct(ObjectMultiAnim *pThis,coorddef *impactVel,AnimDef *def,
          Trk_CollideBoomInst *objCollideInstance,Trk_ObjectDef *objDef,Trk_SimObject *simObj,
          ObjectFinishedMultiAnim *finishedAnim)

{
  u_char bVar1;
  int iVar2;
  AnimScript *pAVar3;
  AnimDef *pAVar4;
  
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectMultiAnim_vtable;
  (pThis->impactVel).x = impactVel->x >> 6;
  (pThis->impactVel).y = impactVel->y >> 6;
  iVar2 = impactVel->z;
  pThis->animParms = def;
  pThis->objCollideInstance = objCollideInstance;
  pThis->objDef = objDef;
  pThis->simObj = simObj;
  (pThis->impactVel).z = iVar2 >> 6;
  if (objCollideInstance->type == '\x06') {
    pAVar3 = (AnimScript *)__builtin_new(sizeof(AnimScript));
    pAVar4 = pThis->animParms;
    bVar1 = ((Trk_AnimateBoomInst *)objCollideInstance)->boomIndex;
  }
  else {
    pAVar3 = (AnimScript *)__builtin_new(sizeof(AnimScript));
    pAVar4 = pThis->animParms;
    bVar1 = objCollideInstance->boomIndex;
  }
  pAVar3 = new(pAVar3) AnimScript(gPersistObjInst,8,(u_int)bVar1,pAVar4->numPieces);  /* @placement-ctor (was flat __10AnimScriptP5Groupiii); storage from __builtin_new above */
  pThis->script = pAVar3;
  (pThis->script)->SetAnimAttrib(2);
  pThis->finishedAnim = finishedAnim;
  return pThis;
}



/* ---- ObjectMultiAnim_Draw  [OBJECT.CPP:1188-1296] SLD-VERIFIED ---- */
int NFS4_VT_THUNK ObjectMultiAnim_Draw(ObjectMultiAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset)

{
  int status;
  int ret;
  Trk_AnimateInst *animInst;
  int animIndex;
  int ticks;
  int partCount;
  int i;
  Trk_SimpleInst *objInst;
  ObjectAnim *anim;
  Trk_ObjectDef *pObjDef;
  ObjectFinishedMultiAnim *finishedAnim;
  short serial;
  int sx;
  int sy;
  int sz;
  Trk_CollideBoomInst *oci;
  matrixtdef matrix;
  matrixtdef RSmatrix;
  coorddef animcp;
  coorddef cp;
  coorddef impact;
  tQuat quat;

  status = (pThis->script)->GetTimedAnimPosRot(0, &animcp, &matrix);
  if (status + 1U < 2) {
    finishedAnim = pThis->finishedAnim;
    serial = pThis->simObj->serialNum;
    pThis->finishedAnim = (ObjectFinishedMultiAnim *)0x0;
    anim = gSimObjAnims[serial];
    if (anim != (ObjectAnim *)0x0) {
      __nfs4_vtbl_ptr_t *entry = &(*anim->_vf)[1];
      nfs4_vcall_dtor(entry->pfn,(u_char *)anim + entry->delta,3);
    }
    gSimObjAnims[serial] = &finishedAnim->_base_ObjectAnim;
    __nfs4_vtbl_ptr_t *entry = &(*(finishedAnim->_base_ObjectAnim)._vf)[2];
    ret = NFS4_VCALL_PTR_PTR_INT(entry->pfn,
              (u_char *)finishedAnim + entry->delta,Vi,sd,offset);
  }
  else {
    animInst = *pThis->script->inst;
    ticks = simGlobal.gameTicks - pThis->script->baseTicks;
    partCount = pThis->animParms->numPieces;
    animIndex = (int)animInst->interval * (int)animInst->count >> 1;
    i = 0;
    if (animIndex < ticks) {
      ticks = animIndex;
    }
    impact.x = (pThis->impactVel).x;
    impact.z = (pThis->impactVel).z;
    oci = pThis->objCollideInstance;
    if (oci->type != '\x06') {
      quat.x = oci->qx;
      quat.y = oci->qy;
      quat.z = oci->qz;
      quat.w = oci->qw;
      Quatern_QuatToMat(&quat,&RSmatrix);
      sx = nfs4_mips_sll_s32(oci->sx,8);
      sy = nfs4_mips_sll_s32(oci->sy,8);
      sz = nfs4_mips_sll_s32(oci->sz,8);
      RSmatrix.m[0] = fixedmult(RSmatrix.m[0],sx);
      RSmatrix.m[3] = fixedmult(RSmatrix.m[3],sx);
      RSmatrix.m[6] = fixedmult(RSmatrix.m[6],sx);
      RSmatrix.m[1] = fixedmult(RSmatrix.m[1],sy);
      RSmatrix.m[4] = fixedmult(RSmatrix.m[4],sy);
      RSmatrix.m[7] = fixedmult(RSmatrix.m[7],sy);
      RSmatrix.m[2] = fixedmult(RSmatrix.m[2],sz);
      RSmatrix.m[5] = fixedmult(RSmatrix.m[5],sz);
      RSmatrix.m[8] = fixedmult(RSmatrix.m[8],sz);
    }
    objInst = (Trk_SimpleInst *)(gPersistObjInst + 1);
    if (0 < partCount) {
      do {
        (pThis->script)->GetTimedAnimPosRot(i, &animcp, &matrix);
        if (pThis->objCollideInstance->type != '\x06') {
          Math_fasttransmult(&matrix,&RSmatrix,&matrix);
        }
        cp.x = pThis->simObj->point[0] + animcp.x + impact.x * ticks;
        cp.y = pThis->simObj->point[1] + animcp.y;
        cp.z = pThis->simObj->point[2] + animcp.z + impact.z * ticks;
        while( true ) {
          if (objInst->type == '\b') {
            oci = pThis->objCollideInstance;
            if (((oci->type != '\x05') ||
                 (((Trk_AnimateBoomInst *)objInst)->boomIndex == oci->boomIndex)) &&
                ((oci->type != '\x06') ||
                 (((Trk_AnimateBoomInst *)objInst)->boomIndex ==
                  ((Trk_AnimateBoomInst *)oci)->boomIndex))) break;
          }
          objInst = (Trk_SimpleInst *)((u_char *)objInst + objInst->size);
        }
        pObjDef = Track_gObjDefs[objInst->pad];
        DrawObjectTransform(Vi,sd,&matrix,pObjDef,&cp,offset,-1);
        i = i + 1;
        objInst = (Trk_SimpleInst *)((u_char *)objInst + objInst->size);
      } while (i < partCount);
    }
    ret = 4;
  }
  return ret;
}

/* ---- ObjectFinishedSignAnim_Draw  [OBJECT.CPP:1302-1304] SLD-VERIFIED ---- */

int NFS4_VT_THUNK ObjectFinishedSignAnim_Draw(ObjectFinishedSignAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset)

{
  
  DrawObjectTransform(Vi,sd,&pThis->finalMatrix,pThis->objDef,
             (coorddef *)&pThis->objCollideInstance->x,offset,-1);
  return 2;
}



/* ---- ObjectSignAnim_ct  [OBJECT.CPP:1308-1354] SLD-VERIFIED ---- */
ObjectSignAnim * ObjectSignAnim_ct(ObjectSignAnim *pThis,coorddef *impactVel,int impactAngle,AnimDef *def,
          Trk_CollideBoomInst *objCollideInstance,Trk_ObjectDef *objDef,Trk_SimObject *simObj,
          coorddef *roadNormal,ObjectFinishedSignAnim *finishedAnim)

{
  int iVar1;
  AnimScript *pAVar2;
  int iVar3;
  int iVar4;
  int vel;
  int iVar5;
  coorddef *roty;
  coorddef *rotz;
  coorddef *rotx;
  matrixtdef *m2;
  matrixtdef yawMat;
  matrixtdef objAngleMat;
  matrixtdef tmpMat;
  matrixtdef mat;
  
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectSignAnim_vtable;
  iVar5 = impactVel->x;
  iVar1 = impactVel->z;
  iVar3 = impactVel->y;
  iVar4 = impactVel->z;
  (pThis->impactVel).x = impactVel->x;
  (pThis->impactVel).y = iVar3;
  (pThis->impactVel).z = iVar4;
  pThis->impactAngle = nfs4_mips_sll_s32(impactAngle,8);
  pThis->animParms = def;
  if (iVar5 < 0) {
    iVar5 = nfs4_mips_negu_s32(iVar5);
  }
  if (iVar1 < 0) {
    iVar1 = nfs4_mips_negu_s32(iVar1);
  }
  pThis->objCollideInstance = objCollideInstance;
  pThis->objDef = objDef;
  pThis->simObj = simObj;
  iVar3 = CalcObjYawAngle((CCOORD16 *)(objDef + 1));
  pThis->objectAngle = nfs4_mips_sll_s32(iVar3,8);
  if (nfs4_mips_sra_s32(nfs4_mips_addu_s32(iVar5,iVar1),0x10) < 10) {
    pAVar2 = (AnimScript *)__builtin_new(sizeof(AnimScript));
    iVar5 = pThis->animParms->baseAnim;
    iVar1 = pThis->animParms->numPieces;
  }
  else {
    pAVar2 = (AnimScript *)__builtin_new(sizeof(AnimScript));
    iVar1 = pThis->animParms->numPieces;
    iVar5 = pThis->animParms->baseAnim + 1;
  }
  pAVar2 = new(pAVar2) AnimScript(iVar5,iVar1);  /* @placement-ctor (was flat __10AnimScriptii); storage from __builtin_new above */
  pThis->script = pAVar2;
  (pThis->script)->SetAnimAttrib(2);
  pThis->finishedAnim = finishedAnim;
  iVar5 = roadNormal->y;
  iVar1 = roadNormal->z;
  (finishedAnim->finalMatrix).m[3] = roadNormal->x;
  (finishedAnim->finalMatrix).m[4] = iVar5;
  (finishedAnim->finalMatrix).m[5] = iVar1;
  (finishedAnim->finalMatrix).m[6] = 0;
  (finishedAnim->finalMatrix).m[7] = 0;
  (finishedAnim->finalMatrix).m[8] = 0x10000;
  m2 = &finishedAnim->finalMatrix;
  iVar5 = fixedmult((finishedAnim->finalMatrix).m[4],0x10000);
  iVar1 = fixedmult((finishedAnim->finalMatrix).m[5],(finishedAnim->finalMatrix).m[7]);
  (finishedAnim->finalMatrix).m[0] = iVar5 - iVar1;
  iVar5 = fixedmult((finishedAnim->finalMatrix).m[5],(finishedAnim->finalMatrix).m[6]);
  iVar1 = fixedmult((finishedAnim->finalMatrix).m[3],(finishedAnim->finalMatrix).m[8]);
  (finishedAnim->finalMatrix).m[1] = iVar5 - iVar1;
  iVar5 = fixedmult((finishedAnim->finalMatrix).m[3],(finishedAnim->finalMatrix).m[7]);
  iVar1 = fixedmult((finishedAnim->finalMatrix).m[4],(finishedAnim->finalMatrix).m[6]);
  iVar3 = (finishedAnim->finalMatrix).m[1];
  (finishedAnim->finalMatrix).m[2] = iVar5 - iVar1;
  iVar5 = fixedmult(iVar3,(finishedAnim->finalMatrix).m[5]);
  iVar1 = fixedmult((finishedAnim->finalMatrix).m[2],(finishedAnim->finalMatrix).m[4]);
  (finishedAnim->finalMatrix).m[6] = iVar5 - iVar1;
  iVar5 = fixedmult((finishedAnim->finalMatrix).m[2],(finishedAnim->finalMatrix).m[3]);
  iVar1 = fixedmult((finishedAnim->finalMatrix).m[0],(finishedAnim->finalMatrix).m[5]);
  (finishedAnim->finalMatrix).m[7] = iVar5 - iVar1;
  iVar5 = fixedmult((finishedAnim->finalMatrix).m[0],(finishedAnim->finalMatrix).m[4]);
  iVar1 = fixedmult((finishedAnim->finalMatrix).m[1],(finishedAnim->finalMatrix).m[3]);
  (finishedAnim->finalMatrix).m[8] = iVar5 - iVar1;
  reorthogonalize(m2->m);
  fixedxformx(&mat,0x4000);
  fixedxformy(&objAngleMat,-pThis->objectAngle);
  fixedxformy(&yawMat,pThis->impactAngle);
  Math_fasttransmult(&objAngleMat,&mat,&tmpMat);
  Math_fasttransmult(&tmpMat,&yawMat,&tmpMat);
  Math_fasttransmult(&tmpMat,m2,m2);
  finishedAnim->objDef = objDef;
  finishedAnim->objCollideInstance = objCollideInstance;
  return pThis;
}



/* ---- ObjectSignAnim_Draw  [OBJECT.CPP:1360-1401] SLD-VERIFIED ---- */
int NFS4_VT_THUNK ObjectSignAnim_Draw(ObjectSignAnim *pThis,DRender_tView *Vi,Draw_DCache *sd,int offset)

{
  short i;
  int ret;
  __vtbl_ptr_type (*pa_Var3) [3];
  Trk_CollideBoomInst *pTVar4;
  ObjectAnim *anim;
  Trk_ObjectDef *pObjDef;
  ObjectFinishedSignAnim *finishedAnim;
  matrixtdef matrix;
  coorddef animcp;
  coorddef cp;
  int frame;
  int numFrames;

  ret = (pThis->script)->GetTimedAnimPosRot(0, &animcp, &matrix);
  if (ret + 1U < 2) {
    finishedAnim = pThis->finishedAnim;
    i = pThis->simObj->serialNum;
    pThis->finishedAnim = (ObjectFinishedSignAnim *)0x0;
    anim = gSimObjAnims[i];
    if (anim != (ObjectAnim *)0x0) {
      __nfs4_vtbl_ptr_t *entry = &(*anim->_vf)[1];
      nfs4_vcall_dtor(entry->pfn,(u_char *)anim + entry->delta,3);
    }
    gSimObjAnims[i] = &finishedAnim->_base_ObjectAnim;
    pa_Var3 = (finishedAnim->_base_ObjectAnim)._vf;
    __nfs4_vtbl_ptr_t *entry = &(*pa_Var3)[2];
    ret = NFS4_VCALL_PTR_PTR_INT(entry->pfn,
              (u_char *)finishedAnim + entry->delta,Vi,sd,offset);
  }
  else {
    pObjDef = pThis->objDef;
    (pThis->script)->GetTimedAnimPosRot(0, &animcp, &matrix);
    (pThis->script)->GetAnimFrameInfo(&frame, &numFrames);
    pTVar4 = pThis->objCollideInstance;
    cp.x = pTVar4->x + animcp.x;
    cp.y = pTVar4->y + animcp.y;
    cp.z = pTVar4->z + animcp.z;
    BuildObjCollisionMatrix(nfs4_mips_sll_s32(frame,0x10) / numFrames,pThis->objectAngle,pThis->impactAngle,&matrix);
    DrawObjectTransform(Vi,sd,&matrix,pObjDef,&cp,offset,-1);
    ret = 4;
  }
  return ret;
}

/* ---- ObjectSignAnim_dt  [OBJECT.CPP:?] SLD-FLAG:NO_SLD ---- */

void NFS4_VT_THUNK ObjectSignAnim_dt(ObjectSignAnim *pThis,int __in_chrg)

{
  __vtbl_ptr_type (*pa_Var1) [3];
  ObjectFinishedSignAnim *pOVar2;
  AnimScript *deleteMe;
  
  deleteMe = pThis->script;
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectSignAnim_vtable;
  if (deleteMe != (AnimScript *)0x0) {
    if (deleteMe->inst != (Trk_AnimateInst **)0x0) {
      __builtin_vec_delete(deleteMe->inst);
    }
    __builtin_delete(deleteMe);
  }
  pOVar2 = pThis->finishedAnim;
  if (pOVar2 != (ObjectFinishedSignAnim *)0x0) {
    pa_Var1 = (pOVar2->_base_ObjectAnim)._vf;
    __nfs4_vtbl_ptr_t *entry = &(*pa_Var1)[1];
    nfs4_vcall_dtor(entry->pfn,(u_char *)pOVar2 + entry->delta,3);
  }
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectAnim_vtable;
  if ((__in_chrg & 1U) != 0) {
    __builtin_delete(pThis);
  }
  return;
}



/* ---- ObjectFinishedSignAnim_dt  [OBJECT.CPP:?] SLD-FLAG:NO_SLD ---- */

void NFS4_VT_THUNK ObjectFinishedSignAnim_dt(ObjectFinishedSignAnim *pThis,int __in_chrg)

{
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectAnim_vtable;
  if ((__in_chrg & 1U) != 0) {
    __builtin_delete(pThis);
  }
  return;
}



/* ---- ObjectMultiAnim_dt  [OBJECT.CPP:?] SLD-FLAG:NO_SLD ---- */

/* ---- ObjectAnim_dt  @0x800a6de0  base deleting-dtor (vtable-only ref; not separately
 * reconstructed -- surfaced by #75 bare-VA pass). nfs4-f.exe: if(__in_chrg&1){ _vf=vtable; delete } */
void NFS4_VT_THUNK ObjectAnim_dt(ObjectAnim *pThis,int __in_chrg)
{
  if (__in_chrg & 1) {
    pThis->_vf = (__vtbl_ptr_type (*) [3])ObjectAnim_vtable;
    __builtin_delete(pThis);
  }
}

void NFS4_VT_THUNK ObjectMultiAnim_dt(ObjectMultiAnim *pThis,int __in_chrg)

{
  __vtbl_ptr_type (*pa_Var1) [3];
  ObjectFinishedMultiAnim *pOVar2;
  AnimScript *deleteMe;
  
  deleteMe = pThis->script;
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectMultiAnim_vtable;
  if (deleteMe != (AnimScript *)0x0) {
    if (deleteMe->inst != (Trk_AnimateInst **)0x0) {
      __builtin_vec_delete(deleteMe->inst);
    }
    __builtin_delete(deleteMe);
  }
  pOVar2 = pThis->finishedAnim;
  if (pOVar2 != (ObjectFinishedMultiAnim *)0x0) {
    pa_Var1 = (pOVar2->_base_ObjectAnim)._vf;
    __nfs4_vtbl_ptr_t *entry = &(*pa_Var1)[1];
    nfs4_vcall_dtor(entry->pfn,(u_char *)pOVar2 + entry->delta,3);
  }
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectAnim_vtable;
  if ((__in_chrg & 1U) != 0) {
    __builtin_delete(pThis);
  }
  return;
}



/* ---- ObjectFinishedMultiAnim_dt  [OBJECT.CPP:?] SLD-FLAG:NO_SLD ---- */

void NFS4_VT_THUNK ObjectFinishedMultiAnim_dt(ObjectFinishedMultiAnim *pThis,int __in_chrg)

{
  (pThis->_base_ObjectAnim)._vf = (__vtbl_ptr_type (*) [3])ObjectAnim_vtable;
  if ((__in_chrg & 1U) != 0) {
    __builtin_delete(pThis);
  }
  return;
}



/* end of object.cpp */
