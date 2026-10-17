/* game/psx/schedule.cpp -- RECONSTRUCTED (NFS4 PSX cooperative scheduler; C++ TU)
 *   6 fns: Sched_ExecuteCheck/CreateNewSchedule/CleanUpSchedule/AddFunction/DeleteFunction/Execute.
 *   GTE-free. Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "schedule_externs.h"

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void Sched_CleanUpSchedule(Sched_tSchedule *schedule);
extern "C" { void Sched_AddFunction(Sched_tSchedule *schedule,void *function,void *var1,int priority); }
extern "C" { void Sched_DeleteFunction(Sched_tSchedule *schedule,void *function,void *var1); }
void Sched_Execute(Sched_tSchedule *schedule);


/* ---- Sched_ExecuteCheck__FiiiiPiN24i  [SCHEDULE.CPP:55-83] SLD-VERIFIED ---- */
extern "C" int Sched_ExecuteCheck(int staggered,int module,int distance,int carId,int *time,int *elapsedTime,int *iTime
              ,int forceNoSimOptz)

{
  u_char bVar1;
  int iVar2;
  
  if (0xf < simGlobal.gameTicks) {
    if (distance < 0) {
      distance = distance + 0xf;
    }
    iVar2 = distance >> 4;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xffff;
    }
    iVar2 = iVar2 >> 0x10;
    if (0x13 < iVar2) {
      iVar2 = 0x13;
    }
    if (forceNoSimOptz != 0) {
      iVar2 = 0;
    }
    bVar1 = Sched_gExecuteInfo[module][iVar2];
    *time = Sched_ExecuteTimes[bVar1];
    *iTime = Sched_ExecuteiTimes[bVar1];
    *elapsedTime = Sched_ExecuteElapsedTimes[bVar1];
    return (u_int)((simGlobal.gameTicks / 2 + carId * staggered & Sched_ExecuteMasks[bVar1]) ==
                 Sched_ExecuteMasks[bVar1]);
  }
  *time = Sched_ExecuteTimes[6];
  *iTime = Sched_ExecuteiTimes[6];
  *elapsedTime = Sched_ExecuteElapsedTimes[6];
  return 1;
}

/* ---- Sched_CreateNewSchedule__FPci  [SCHEDULE.CPP:89-109] SLD-VERIFIED ---- */
Sched_tSchedule *
Sched_CreateNewSchedule(const char *scheduleName,int maxFunctions)

{
  int i;
  Sched_tSchedule *newSchedule;
  int allocationSize;
  
  /* The extra record is the sentinel used at func[numFunctions]. */
  allocationSize = __builtin_offsetof(Sched_tSchedule,func) +
                   (maxFunctions + 1) * sizeof(Sched_tFunctionSchedule);
  newSchedule = (Sched_tSchedule *)reservememadr(scheduleName,allocationSize,0);
  newSchedule->maxNumFunctions = maxFunctions;
  newSchedule->numFunctions = 0;
  for (i = 0; i < maxFunctions; i = i + 1) {
    newSchedule->func[i].priority = 0x7ffe;
    newSchedule->func[i].function = (void *)0x0;
  }
  return newSchedule;
}

/* ---- Sched_CleanUpSchedule__FP15Sched_tSchedule  [SCHEDULE.CPP:113-118] SLD-VERIFIED ---- */
void Sched_CleanUpSchedule(Sched_tSchedule *schedule)

{
  purgememadr(schedule);
  return;
}

/* ---- Sched_AddFunction__FP15Sched_tSchedulePFPv_vPvi  [SCHEDULE.CPP:123-155] SLD-VERIFIED ---- */
extern "C" void Sched_AddFunction(Sched_tSchedule *schedule,void *function,void *var1,int priority)

{
  int j;
  int i;
  
  i = 0;
  schedule->numFunctions = schedule->numFunctions + 1;
  if (0 < schedule->numFunctions) {
    do {
      if (priority < schedule->func[i].priority) {
        for (j = schedule->numFunctions + -1; i < j; j = j + -1) {
          schedule->func[j] = schedule->func[j + -1];
        }
        break;
      }
      i = i + 1;
    } while (i < schedule->numFunctions);
  }
  schedule->func[i].priority = priority;
  schedule->func[i].function = (void *)function;
  schedule->func[i].var1 = var1;
  return;
}

/* ---- Sched_DeleteFunction__FP15Sched_tSchedulePFPv_vPv  [SCHEDULE.CPP:160-183] SLD-VERIFIED ---- */
extern "C" void Sched_DeleteFunction(Sched_tSchedule *schedule,void *function,void *var1)

{
  int iVar1;
  int j;
  int iVar3;
  
  iVar3 = schedule->numFunctions;
  if (iVar3 != 0) {
    iVar1 = 0;
    if (0 < iVar3) {
      do {
        if ((schedule->func[iVar1].function == (void *)function) &&
            (schedule->func[iVar1].var1 == var1))
        {
          if (iVar1 < iVar3 + -1) {
            for (j = iVar1; j < schedule->numFunctions + -1; j = j + 1) {
              schedule->func[j] = schedule->func[j + 1];
            }
          }
          break;
        }
        iVar3 = schedule->numFunctions;
        iVar1 = iVar1 + 1;
      } while (iVar1 < iVar3);
    }
    schedule->func[schedule->numFunctions].priority = 0x7ffe;
    schedule->numFunctions = schedule->numFunctions + -1;
  }
  return;
}

/* ---- Sched_Execute__FP15Sched_tSchedule  [SCHEDULE.CPP:195-206] SLD-VERIFIED ---- */
void Sched_Execute(Sched_tSchedule *schedule)

{
  void *function;
  int iVar2;
  
  iVar2 = 0;
  if (0 < schedule->numFunctions) {
    do {
      function = schedule->func[iVar2].function;
      if (function != (void *)0x0) {
        (*(fn_void *)function)(schedule->func[iVar2].var1);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < schedule->numFunctions);
  }
  return;
}

/* end of schedule.cpp */
