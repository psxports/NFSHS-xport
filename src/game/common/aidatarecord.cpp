/* game/common/aidatarecord.cpp -- RECONSTRUCTED (AI state-machine hierarchy; C++ TU)
 *   52 fns across 11 classes (AIDataRecord_Base + Normal/NonActive/Idle/Chase/Offroad/Purgatory/
 *   RovingTraffic/Donuts/GotoSlice/Cruise) + 3 free AIDataRecord_StartUp/Restart/CleanUp.
 *   Composition-modeled inheritance (_base_ members); manual _vf vtable dispatch (8-byte
 *   __vtbl_ptr_type entries); deleting dtors. Each ctor/dtor installs AIDataRecord_<C>_vtable.
 *   Faithful C++ (option A). NOT original source; SYM-faithful, recompilable. vs disasm-v2.
 */
#include "../../lib/nfs4_new.h"
#include "../../nfs4_types.h"
#include "aidatarecord_externs.h"
#include "new.h"

/* ---- aidatarecord.obj-owned globals (.bss zero) ---- */
AIDataRecord_BestLine_t *AIDataRecord_BestLine;   /* @0x8013c5a0  (bss(zero)) */
AIDataRecord_TrackCurve_t *AIDataRecord_TrackCurve;   /* @0x8013c5a4  (bss(zero)) */
int          AIDataRecord_WhichRecord;   /* @0x8013c5a8  (bss(zero)) */
int          AIDataRecord_RecordMethod;   /* @0x8013c5ac  (bss(zero)) */
AIDataRecord_t *recordCollection[24];   /* @0x8013df64  (bss(zero)) */


/* ---- __14AIDataRecord_t26AIDataRecord_WhichRecord_tPc  AIDataRecord_t::ctor  [AIDATARECORD.CPP:32-52] SLD-VERIFIED ---- */

AIDataRecord_t::AIDataRecord_t(AIDataRecord_WhichRecord_t whichIsThis,char *preBuffer)



{

  this->_vf = (__vtbl_ptr_type (*) [3])AIDataRecord_t_vtable;

  this->AddRecordToCollection();

  this->preAllocatedBuffer_ = preBuffer;

  this->recordMethod_ = 0;

  return;

}








/* ---- _._14AIDataRecord_t  AIDataRecord_t::dtor  [AIDATARECORD.CPP:63-66] SLD-VERIFIED ---- */

AIDataRecord_t::~AIDataRecord_t()



{


  

  this->_vf = (__vtbl_ptr_type (*) [3])AIDataRecord_t_vtable;

  this->SaveAndPurge();

  this->RemoveRecordFromCollection();


  return;

}








/* ---- AddRecordToCollection__14AIDataRecord_t  AIDataRecord_t::AddRecordToCollection  [AIDATARECORD.CPP:77-87] SLD-VERIFIED ---- */

int AIDataRecord_t::AddRecordToCollection()



{
  int recordLoop;

  AIDataRecord_t **ppAVar1;

  int iVar2;

  

  iVar2 = 0;

  ppAVar1 = recordCollection;

  do {

    iVar2 = iVar2 + 1;

    if (*ppAVar1 == (AIDataRecord_t *)0x0) {

      *ppAVar1 = this;

      return 1;

    }

    ppAVar1 = ppAVar1 + 1;

  } while (iVar2 < 0x18);

  return 0;

}








/* ---- RemoveRecordFromCollection__14AIDataRecord_t  AIDataRecord_t::RemoveRecordFromCollection  [AIDATARECORD.CPP:91-100] SLD-VERIFIED ---- */

int AIDataRecord_t::RemoveRecordFromCollection()



{
  int recordLoop;

  AIDataRecord_t **ppAVar1;

  int iVar2;

  

  iVar2 = 0;

  ppAVar1 = recordCollection;

  do {

    iVar2 = iVar2 + 1;

    if (*ppAVar1 == this) {

      *ppAVar1 = (AIDataRecord_t *)0x0;

      return 1;

    }

    ppAVar1 = ppAVar1 + 1;

  } while (iVar2 < 0x18);

  return 0;

}








/* ---- StartUp1__14AIDataRecord_t  AIDataRecord_t::StartUp1  [AIDATARECORD.CPP:104-121] SLD-VERIFIED ---- */

void AIDataRecord_t::StartUp1(void)



{
  int recordLoop;

  AIDataRecord_t **ppAVar1;



  int iVar2;

  

  iVar2 = 0x17;

  ppAVar1 = recordCollection + 0x17;

  AIDataRecord_WhichRecord = 0;

  AIDataRecord_RecordMethod = 0;

  do {

    *ppAVar1 = (AIDataRecord_t *)0x0;

    iVar2 = iVar2 + -1;

    ppAVar1 = ppAVar1 + -1;

  } while (-1 < iVar2);

  AIDataRecord_BestLine = new((AIDataRecord_BestLine_t *)__builtin_new(sizeof(AIDataRecord_BestLine_t)))
      AIDataRecord_BestLine_t((AIDataRecord_WhichRecord_t)5);

  AIDataRecord_TrackCurve = new((AIDataRecord_TrackCurve_t *)__builtin_new(sizeof(AIDataRecord_TrackCurve_t)))
      AIDataRecord_TrackCurve_t((AIDataRecord_WhichRecord_t)6);

  return;

}








/* ---- StartUp2__14AIDataRecord_t  AIDataRecord_t::StartUp2  [AIDATARECORD.CPP:139-148] SLD-VERIFIED ---- */

void AIDataRecord_t::StartUp2(void)



{
  int recordLoop;

  AIDataRecord_t *pAVar1;

  AIDataRecord_t **ppAVar2;

  int iVar3;

  

  iVar3 = 0;

  ppAVar2 = recordCollection;

  do {

    pAVar1 = *ppAVar2;

    if (pAVar1 != (AIDataRecord_t *)0x0) {
#ifdef AP_WIN
      NFS4_VCALL0(pAVar1->_vf[0][2].pfn, pAVar1);
#else
      (**(int (**)(...))(pAVar1->_vf[6] + 2))(pAVar1->name_ + *(short *)(pAVar1->_vf[5] + 1) + -8);
#endif

    }

    iVar3 = iVar3 + 1;

    ppAVar2 = ppAVar2 + 1;

  } while (iVar3 < 0x18);

  return;

}








/* ---- CleanUp1__14AIDataRecord_t  AIDataRecord_t::CleanUp1  [AIDATARECORD.CPP:152-161] SLD-VERIFIED ---- */

void AIDataRecord_t::CleanUp1(void)



{

  __vtbl_ptr_type (*pa_Var1) [3];

  

  if (AIDataRecord_BestLine != (AIDataRecord_BestLine_t *)0x0) {

    pa_Var1 = (AIDataRecord_BestLine->_base_AIDataRecord_t)._vf;

    (**(int (**)(...))(pa_Var1 + 4))

              ((AIDataRecord_BestLine->_base_AIDataRecord_t).name_ + *(short *)(pa_Var1[2] + 2) + -8,3);

    AIDataRecord_BestLine = (AIDataRecord_BestLine_t *)0x0;

  }

  if (AIDataRecord_TrackCurve != (AIDataRecord_TrackCurve_t *)0x0) {

    pa_Var1 = (AIDataRecord_TrackCurve->_base_AIDataRecord_t)._vf;

    (**(int (**)(...))(pa_Var1 + 4))

              ((AIDataRecord_TrackCurve->_base_AIDataRecord_t).name_ + *(short *)(pa_Var1[2] + 2) + -8,3);

    AIDataRecord_TrackCurve = (AIDataRecord_TrackCurve_t *)0x0;

  }

  return;

}








/* ---- CleanUp2__14AIDataRecord_t  AIDataRecord_t::CleanUp2  [AIDATARECORD.CPP:166-167] SLD-VERIFIED ---- */

void AIDataRecord_t::CleanUp2(void)



{

  return;

}








/* ---- Setup__14AIDataRecord_t  AIDataRecord_t::Setup  [AIDATARECORD.CPP:170-204] SLD-VERIFIED ---- */

void AIDataRecord_t::Setup()



{

  char *pcVar1;

  int iVar2;

  

  pcVar1 = this->preAllocatedBuffer_;

  if (pcVar1 != (char *)0x0) {

    this->dataBuffer_ = pcVar1;

    return;

  }

  iVar2 = this->Load();

  if (iVar2 != 0) {

    return;

  }

  this->dataBuffer_ = (char *)reservememadr(this->name_,this->bSize_,0);

  return;

}








/* ---- Load__14AIDataRecord_t  AIDataRecord_t::Load  [AIDATARECORD.CPP:225-239] SLD-VERIFIED ---- */

int AIDataRecord_t::Load()



{

  char *pcVar1;

  

  if (this->recordMethod_ == 0) {

    pcVar1 = (char *)loadpackadrz(this->name_,(void *)0x0);

    this->dataBuffer_ = pcVar1;

  }

  return (u_int)(this->dataBuffer_ != (char *)0x0);

}








/* ---- SaveAndPurge__14AIDataRecord_t  AIDataRecord_t::SaveAndPurge  [AIDATARECORD.CPP:243-270] SLD-VERIFIED ---- */

int AIDataRecord_t::SaveAndPurge()



{

  int iVar1;

  

  iVar1 = 0;

  if (this->dataBuffer_ != (char *)0x0) {

    if (this->preAllocatedBuffer_ == (char *)0x0) {

      purgememadr(this->dataBuffer_);

    }

    this->dataBuffer_ = (char *)0x0;

    iVar1 = 1;

  }

  return iVar1;

}








/* ---- __23AIDataRecord_AccTable_tPci26AIDataRecord_WhichRecord_t  AIDataRecord_AccTable_t::ctor  [AIDATARECORD.CPP:394-399] SLD-VERIFIED ---- */

AIDataRecord_AccTable_t::AIDataRecord_AccTable_t(char *preBuffer,int scale,

          AIDataRecord_WhichRecord_t whichIsThis)
  : AIDataRecord_t(whichIsThis,preBuffer)
{


  this->_vf = (__vtbl_ptr_type (*) [3])AIDataRecord_AccTable_t_vtable;

  this->numElements_ = 0x70;

  this->bSize_ = 0xe0;

  this->scale_ = scale;

  sprintf(this->name_,"%s%s.acc",Paths_Paths[5],(char *)Cars_gHumanRaceCarList[0] + 0x240);

  return;

}








/* ---- Get__23AIDataRecord_AccTable_ti  AIDataRecord_AccTable_t::Get  [AIDATARECORD.CPP:403-404] SLD-VERIFIED ---- */

int AIDataRecord_AccTable_t::Get(int speed)



{

  return (int)*(short *)(this->dataBuffer_ + speed * 2) << 8;

}








/* ---- Setup__23AIDataRecord_AccTable_t  AIDataRecord_AccTable_t::Setup  [AIDATARECORD.CPP:408-418] SLD-VERIFIED ---- */

void AIDataRecord_AccTable_t::Setup()



{
  int loop;

  int iVar1;

  int speed;

  

  this->AIDataRecord_t::Setup();

  for (speed = 0; speed < 0x70; speed = speed + 1) {

    iVar1 = this->Get(speed);

    iVar1 = fixedmult(iVar1,this->scale_);

    *(short *)(this->dataBuffer_ + speed * 2) = (short)((u_int)iVar1 >> 8);

  }

  return;

}








/* ---- __23AIDataRecord_BestLine_t26AIDataRecord_WhichRecord_t  AIDataRecord_BestLine_t::ctor  [AIDATARECORD.CPP:457-464] SLD-VERIFIED ---- */

AIDataRecord_BestLine_t::AIDataRecord_BestLine_t(AIDataRecord_WhichRecord_t whichIsThis)
  : _base_AIDataRecord_t(whichIsThis,(char *)0x0)
{

  int iVar1;


  


  iVar1 = gNumSlices;

  (this->_base_AIDataRecord_t)._vf = (__vtbl_ptr_type (*) [3])AIDataRecord_BestLine_t_vtable;

  (this->_base_AIDataRecord_t).numElements_ = iVar1;

  (this->_base_AIDataRecord_t).bSize_ = iVar1;

  if ((this->_base_AIDataRecord_t).recordMethod_ == 0) {

    sprintf((this->_base_AIDataRecord_t).name_,"%sTr%02d.qbe",Paths_Paths[12],GameSetup_gData.track);

  }

  else {

    sprintf((this->_base_AIDataRecord_t).name_,"%sTr%02d.bes",Paths_Paths[13],GameSetup_gData.track);

  }

  

  return;

}








/* ---- __25AIDataRecord_TrackCurve_t26AIDataRecord_WhichRecord_t  AIDataRecord_TrackCurve_t::ctor  [AIDATARECORD.CPP:535-542] SLD-VERIFIED ---- */

AIDataRecord_TrackCurve_t::AIDataRecord_TrackCurve_t(AIDataRecord_WhichRecord_t whichIsThis)
  : _base_AIDataRecord_t(whichIsThis,(char *)0x0)
{

  int iVar1;


  


  iVar1 = gNumSlices;

  (this->_base_AIDataRecord_t)._vf = (__vtbl_ptr_type (*) [3])AIDataRecord_TrackCurve_t_vtable;

  (this->_base_AIDataRecord_t).numElements_ = iVar1;

  (this->_base_AIDataRecord_t).bSize_ = iVar1 + 1;

  if ((this->_base_AIDataRecord_t).recordMethod_ == 0) {

    sprintf((this->_base_AIDataRecord_t).name_,"%sTr%02d.qcr",Paths_Paths[10],GameSetup_gData.track);

  }

  else {

    sprintf((this->_base_AIDataRecord_t).name_,"%sTr%02d.crv",Paths_Paths[11],GameSetup_gData.track);

  }

  

  return;

}








/* ---- Get__25AIDataRecord_TrackCurve_ti  AIDataRecord_TrackCurve_t::Get  [AIDATARECORD.CPP:546-547] SLD-VERIFIED ---- */

int AIDataRecord_TrackCurve_t::Get(int slice)



{

  return (u_int)(u_char)(this->_base_AIDataRecord_t).dataBuffer_[slice];

}








/* ---- __30AIDataRecord_CurveSpeedTable_tPc26AIDataRecord_WhichRecord_t  AIDataRecord_CurveSpeedTable_t::ctor  [AIDATARECORD.CPP:617-624] SLD-VERIFIED ---- */

AIDataRecord_CurveSpeedTable_t::AIDataRecord_CurveSpeedTable_t(char *carName,AIDataRecord_WhichRecord_t whichIsThis

          )
  : _base_AIDataRecord_t(whichIsThis,(char *)0x0)
{


  


  (this->_base_AIDataRecord_t)._vf = (__vtbl_ptr_type (*) [3])AIDataRecord_CurveSpeedTable_t_vtable;

  (this->_base_AIDataRecord_t).numElements_ = 0x100;

  (this->_base_AIDataRecord_t).bSize_ = 0x100;

  if ((this->_base_AIDataRecord_t).recordMethod_ == 0) {

    sprintf((this->_base_AIDataRecord_t).name_,"%s%s.qcs",Paths_Paths[4],carName);

  }

  else {

    sprintf((this->_base_AIDataRecord_t).name_,"%s%s.csp",Paths_Paths[5],carName);

  }

  

  return;

}








/* ---- Get__30AIDataRecord_CurveSpeedTable_ti  AIDataRecord_CurveSpeedTable_t::Get  [AIDATARECORD.CPP:629-636] SLD-VERIFIED ---- */

int AIDataRecord_CurveSpeedTable_t::Get(int curve)



{

  if (curve < 0) {

    curve = -curve;

  }

  if (0xff < curve) {

    curve = 0xff;

  }

  return (u_int)(u_char)(this->_base_AIDataRecord_t).dataBuffer_[curve] << 0x10;

}








/* ---- Upgrade__30AIDataRecord_CurveSpeedTable_ti  AIDataRecord_CurveSpeedTable_t::Upgrade  [AIDATARECORD.CPP:680-686] SLD-VERIFIED ---- */

void AIDataRecord_CurveSpeedTable_t::Upgrade(int handlingUpgrade)



{
  int curveLoop;

  int iVar1;

  int curve;

  

  for (curve = 0; curve < (this->_base_AIDataRecord_t).numElements_; curve = curve + 1) {

    iVar1 = this->Get(curve);

    iVar1 = fixedmult(iVar1,handlingUpgrade);

    if (iVar1 < 0) {

      iVar1 = iVar1 + 0xffff;

    }

    (this->_base_AIDataRecord_t).dataBuffer_[curve] = (char)((u_int)iVar1 >> 0x10);

  }

  return;

}








/* ---- Get__26AIDataRecord_CarTracking_ti  AIDataRecord_CarTracking_t::Get  [AIDATARECORD.CPP:?] SLD-FLAG:NO_SLD ---- */

int AIDataRecord_CarTracking_t::Get(int slice)



{

  return 0;

}








/* ---- _._26AIDataRecord_CarTracking_t  AIDataRecord_CarTracking_t::dtor  [AIDATARECORD.CPP:?] SLD-FLAG:NO_SLD ---- */

AIDataRecord_CarTracking_t::~AIDataRecord_CarTracking_t()



{


  return;

}








/* ---- _._30AIDataRecord_CurveSpeedTable_t  AIDataRecord_CurveSpeedTable_t::dtor  [AIDATARECORD.CPP:?] SLD-FLAG:NO_SLD ---- */

AIDataRecord_CurveSpeedTable_t::~AIDataRecord_CurveSpeedTable_t()



{


  return;

}








/* ---- _._25AIDataRecord_TrackCurve_t  AIDataRecord_TrackCurve_t::dtor  [AIDATARECORD.CPP:?] SLD-FLAG:NO_SLD ---- */

AIDataRecord_TrackCurve_t::~AIDataRecord_TrackCurve_t()



{


  return;

}








/* ---- _._23AIDataRecord_BestLine_t  AIDataRecord_BestLine_t::dtor  [AIDATARECORD.CPP:?] SLD-FLAG:NO_SLD ---- */

AIDataRecord_BestLine_t::~AIDataRecord_BestLine_t()



{


  return;

}








/* ---- _._23AIDataRecord_AccTable_t  AIDataRecord_AccTable_t::dtor  [AIDATARECORD.CPP:?] SLD-FLAG:NO_SLD ---- */

AIDataRecord_AccTable_t::~AIDataRecord_AccTable_t()



{

  int recordLoop;

  int curveLoop;

  


  return;

}







/* end of aidatarecord.cpp */
