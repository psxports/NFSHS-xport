/* game/common/aitriger.cpp -- RECONSTRUCTED from Ghidra 12.0.4 decompile + PsyQ SYM v3.
 *   anim.obj = 18 fns: AnimScript C++ class (3 ctors + SetAnimAttrib/GetAnimFrameInfo/
 *   GetTimedAnimPosRot[x2 overload]/GetStatus) + 10 free Anim_* fns. AnimScript non-virtual
 *   (20 B, declared in nfs4_types.h). Faithful C++: `new AnimScript(..)`, obj->Method(..).
 *   Verified vs disasm-v2.txt. NOT original source; SYM-faithful, recompilable C++.
 */
#include "../../nfs4_types.h"
#include "aitriger_externs.h"


/* ---- anim.obj-owned globals (SYM-typed; .data=real EXE bytes, .bss=zero) ---- */
AITrigger_TriggerManager *triggerManagerCops;   /* @0x8013c5e8  (bss(zero)) */
AITrigger_TriggerManager *triggerManagerTraffic;   /* @0x8013c5ec  (bss(zero)) */


/* ---- AITrigger_TriggerManager::Init  [@0x8007286c] ---- */
void AITrigger_TriggerManager::Init(char *rawTriggers)
{
  int iVar1;
  int iVar3;
  trigger_t *trigger;
  
  iVar3 = 99;
  this->numTriggers_ = 0;
  this->invNumTriggers_ = 0;
  do {
    this->checkTime_[iVar3] = -0xa00;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  iVar3 = 8;
  do {
    this->lastTriggerChecked_[iVar3] = 0;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  if (rawTriggers != (char *)0x0) {
    trigger = (trigger_t *)(rawTriggers + 4);
    iVar3 = 0;
    if (0 < *(int *)rawTriggers) {
      do {
        iVar1 = this->InsertTrigger(trigger,(void *)0x1);
        trigger = (trigger_t *)((char *)trigger + iVar1);
        iVar3 = iVar3 + 1;
      } while (iVar3 < *(int *)rawTriggers);
    }
    this->Sort();
    if (this->numTriggers_ != 0) {
      iVar3 = fixeddiv(0x10000,this->numTriggers_ << 0x10);
      this->invNumTriggers_ = iVar3;
    }
  }
  return;
}

/* ---- AITrigger_TriggerManager::InsertTrigger  [@0x80072948] ---- */
int AITrigger_TriggerManager::InsertTrigger(trigger_t *trigger,bool fromFile)
{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  this->DescribeTrigger(trigger);
  iVar1 = trigger->any.type;
  if (iVar1 == 5) {
    if (fromFile) {   /* @0x80072984: if(fromFile) bool test (disasm-v3) */
      trigger->trafficPath.path = (trigger_pathPosition_t *)((char *)trigger + 0x40);
    }
    this->triggers_[this->numTriggers_] = trigger;
    iVar2 = trigger->trafficPath.numPoints * 0x14 + 0x40;
    goto LAB_80072a14;
  }
  if (iVar1 == 2) {
LAB_800729f4:
    iVar2 = 0x14;
  }
  else if (iVar1 < 3) {
    if (iVar1 == 1) goto LAB_800729f4;
  }
  else if (iVar1 == 3) {
    iVar2 = 0x48;
  }
  this->triggers_[this->numTriggers_] = trigger;
LAB_80072a14:
  this->numTriggers_ = this->numTriggers_ + 1;
  return iVar2;
}

/* ---- AITrigger_TriggerManager::GetNextTrigger  [@0x80072a44] ---- */
trigger_t *
AITrigger_TriggerManager::GetNextTrigger(int car)
{
  int iVar1;
  
  if (this->numTriggers_ == 0) {
    return (trigger_t *)0x0;
  }
  iVar1 = this->lastTriggerChecked_[car] + 1;
  this->lastTriggerChecked_[car] = iVar1;
  if (iVar1 == this->numTriggers_) {
    this->lastTriggerChecked_[car] = 0;
  }
  if (this->lastTriggerChecked_[car] < this->numTriggers_) {
    return this->triggers_[this->lastTriggerChecked_[car]];
  }
  return (trigger_t *)0x0;
}

/* ---- AITrigger_TriggerManager::GetPrevTrigger  [@0x80072ab4] ---- */
trigger_t *
AITrigger_TriggerManager::GetPrevTrigger(int car)
{
  int iVar1;
  
  if (this->numTriggers_ == 0) {
    return (trigger_t *)0x0;
  }
  iVar1 = this->lastTriggerChecked_[car] + -1;
  this->lastTriggerChecked_[car] = iVar1;
  if (iVar1 == -1) {
    this->lastTriggerChecked_[car] = this->numTriggers_ + -1;
  }
  if (this->lastTriggerChecked_[car] < this->numTriggers_) {
    return this->triggers_[this->lastTriggerChecked_[car]];
  }
  return (trigger_t *)0x0;
}

/* ---- AITrigger_TriggerManager::CheckForTriggerAtSlice  [@0x80072b24] ---- */
int AITrigger_TriggerManager::CheckForTriggerAtSlice(int car,int slice)
{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = -1;
  if (this->numTriggers_ != 0) {
    piVar3 = this->lastTriggerChecked_ + car;
    if ((this->triggers_[*piVar3]->any.slice < slice) && (1 < this->numTriggers_)) {
      do {
        if (*piVar3 == this->numTriggers_ + -1) break;
        this->GetNextTrigger(car);
      } while (this->triggers_[*piVar3]->any.slice < slice);
    }
    else {
      iVar1 = *piVar3;
      if ((slice < this->triggers_[iVar1]->any.slice) && (1 < this->numTriggers_)) {
        do {
          if (iVar1 == 0) break;
          this->GetPrevTrigger(car);
          iVar1 = *piVar3;
        } while (slice < this->triggers_[iVar1]->any.slice);
      }
    }
    iVar2 = *piVar3;
    iVar1 = -1;
    if (((this->triggers_[iVar2]->any.slice == slice) &&
        (0xa00 < simGlobal.gameTicks - this->checkTime_[iVar2])) &&
       (this->triggers_[iVar2]->any.type != 2)) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}

/* ---- AITrigger_TriggerManager::GetTrigger  [@0x80072cd8] ---- */
trigger_t *
AITrigger_TriggerManager::GetTrigger(int trigger,int *used)
{
  trigger_t *ptVar1;
  
  if (simGlobal.gameTicks - this->checkTime_[trigger] < 0xa01) {
    *used = 1;
  }
  else {
    *used = 0;
  }
  this->checkTime_[trigger] = simGlobal.gameTicks;
  ptVar1 = (trigger_t *)0x0;
  if (trigger < this->numTriggers_) {
    ptVar1 = this->triggers_[trigger];
  }
  return ptVar1;
}

/* ---- AITrigger_TriggerManager::CheckForClosestTriggerOfType  [@0x80072d40] ---- */
int AITrigger_TriggerManager::CheckForClosestTriggerOfType(int slice,triggerType type,int direction)
{
  int *piVar1;
  int iVar2;
  trigger_t *ptVar3;
  int iVar4;
  trigger_t *ptVar5;
  trigger_t *ptVar6;
  trigger_t *ptVar7;
  int iVar8;
  int iVar9;
  
  ptVar7 = (trigger_t *)0x0;
  piVar1 = &this->numTriggers_;
  iVar9 = -1;
  if (*piVar1 == 0) {
    return -1;
  }
  iVar4 = 0;
  ptVar5 = (trigger_t *)0x0;
  iVar2 = -1;
  do {
    if (*piVar1 <= iVar4) {
      if (((ptVar5 == (trigger_t *)0x0) || (-1 < direction)) && (iVar2 = iVar9, direction < 1)) {
        iVar2 = -1;
      }
      return iVar2;
    }
    ptVar3 = this->triggers_[iVar4];
    ptVar6 = ptVar5;
    iVar8 = iVar2;
    if (ptVar3->any.type == type) {
      if (ptVar7 == (trigger_t *)0x0) {
        ptVar7 = ptVar3;
        iVar9 = iVar4;
      }
      if (ptVar3->any.slice == slice) {
        return iVar4;
      }
      ptVar6 = ptVar3;
      iVar8 = iVar4;
      if (slice < ptVar3->any.slice) {
        if (0 < direction) {
          return iVar4;
        }
        if ((direction < 0) && (ptVar5 != (trigger_t *)0x0)) {
          return iVar2;
        }
      }
    }
    iVar4 = iVar4 + 1;
    ptVar5 = ptVar6;
    iVar2 = iVar8;
  } while( true );
}

/* ---- AITrigger_TriggerManager::DescribeTrigger  [@0x80072e10] ---- */
void AITrigger_TriggerManager::DescribeTrigger(trigger_t *trigger)
{
  return;
}

/* ---- AITrigger_Compare  [@0x80072e18] ---- */
int AITrigger_Compare(const void *op1,const void *op2)
{
  const uint32 *ta = (const uint32 *)(uintptr_t)*(const uint32 *)op1;
  const uint32 *tb = (const uint32 *)(uintptr_t)*(const uint32 *)op2;
  return (sint32)(ta[1] - tb[1]);
}

/* ---- AITrigger_TriggerManager::Sort  [@0x80072e30] ---- */
void AITrigger_TriggerManager::Sort()
{
  
  if (this->numTriggers_ != 0) {
    qsortPSX(this->triggers_,this->numTriggers_,4,AITrigger_Compare);
  }
  return;
}
