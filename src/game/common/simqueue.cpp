/* game/psx/simqueue.cpp -- RECONSTRUCTED (NFS4 PSX sim input queue; C++ TU)
 *   8 fns: SimQueue_StartUp/Reset/CleanUp/Put/SetCurrentInput/GetCurrentInput/SetLag/IsBlocking.
 *   GTE-free. Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "simqueue_externs.h"

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
extern "C" { void SimQueue_StartUp(void); }
void SimQueue_Reset(void);
void SimQueue_CleanUp(void);
int SimQueue_Put(int pIndex,Input_tResults *val);
void SimQueue_SetCurrentInput(int time);
void SimQueue_GetCurrentInput(int pIndex,Input_tResults *out);
void SimQueue_SetLag(void);
int SimQueue_IsBlocking(int pIndex);


/* ---- SimQueue_StartUp__Fv  [SIMQUEUE.CPP:93-101] SLD-VERIFIED ---- */
extern "C" void SimQueue_StartUp(void)

{
  gSimQueue_BlockSelf = 1;
  gSimQueue_BlockOther = 1;
  SimQueue_SetLag();
  return;
}

/* ---- SimQueue_Reset__Fv  [SIMQUEUE.CPP:115-155] SLD-VERIFIED ---- */
void SimQueue_Reset(void)

{
  int p;
  int t;
  gSimQueue_BlockSelf = 1;
  gSimQueue_BlockOther = 1;
  for (p = 0; p < 2; ++p) {
    for (t = 0; t < 32; ++t) {
      inputQueue.Validity[p][t] = (t < 4) ? kVALID : kINVALID;
      inputQueue.Buffer[p][t].steering = 0;
      inputQueue.Buffer[p][t].gas = 0;
      inputQueue.Buffer[p][t].brake = 0;
      inputQueue.Buffer[p][t].flags = 0;
    }
    inputQueue.TailTime[p] = 4;
  }
  inputQueue.HeadTime = 0;
  gSimQueue_Ticker = 3;
  gSimQueue_BlockOther = 0;
  gSimQueue_BlockSelf = 0;
  return;
}

/* ---- SimQueue_CleanUp__Fv  [SIMQUEUE.CPP:169-174] SLD-VERIFIED ---- */
void SimQueue_CleanUp(void)

{
  gSimQueue_BlockSelf = 1;
  gSimQueue_BlockOther = 1;
  return;
}

/* ---- SimQueue_Put__FiP14Input_tResults  [SIMQUEUE.CPP:201-249] SLD-VERIFIED ---- */
int SimQueue_Put(int pIndex,Input_tResults *val)

{
  unsigned slot = (unsigned)inputQueue.TailTime[pIndex] & 0x1f;
  if (SimQueue_IsBlocking(pIndex) != 0)
    return 0;
  if (inputQueue.Validity[pIndex][slot] != kINVALID)
    return 0;
  nfs4_mips_copy_bytes(&inputQueue.Buffer[pIndex][slot],val,4);
  inputQueue.Validity[pIndex][slot] = kVALID;
  inputQueue.TailTime[pIndex]++;
  if (GameSetup_gData.commMode == 0) {
    if (GameSetup_gData.numPlayerRaceCars > 1 && pIndex == 0)
      return 1;
  } else if (GameSetup_gData.commMode != 1 || pIndex == 0) {
    return 1;
  }
  gSimQueue_Ticker++;
  return 1;
}

/* ---- SimQueue_SetCurrentInput__Fi  [SIMQUEUE.CPP:271-290] SLD-VERIFIED ---- */
void SimQueue_SetCurrentInput(int time)

{
  int p;
  unsigned slot = (unsigned)time & 0x1f;
  for (p = 0; p < GameSetup_gData.numPlayerRaceCars; ++p) {
    nfs4_mips_copy_bytes(&output[p],&inputQueue.Buffer[p][slot],4);
  }
  for (p = 0; p < GameSetup_gData.numPlayerRaceCars; ++p) {
    inputQueue.Validity[p][slot] = kINVALID;
  }
  inputQueue.HeadTime++;
  return;
}

/* ---- SimQueue_GetCurrentInput__FiP14Input_tResults  [SIMQUEUE.CPP:295-407] SLD-VERIFIED ---- */
void SimQueue_GetCurrentInput(int pIndex,Input_tResults *out)

{
  nfs4_mips_copy_bytes(out,&output[pIndex],4);
  return;
}

/* ---- SimQueue_SetLag__Fv  [SIMQUEUE.CPP:326-407] SLD-VERIFIED ---- */
void SimQueue_SetLag(void)

{
  if ((GameSetup_gData.commMode == 0) || (GameSetup_gData.commMode == 1)) {
    maxTicksPerFrame = 4;
  }
  return;
}

/* ---- SimQueue_IsBlocking__Fi  [SIMQUEUE.CPP:382-407] SLD-VERIFIED ---- */
int SimQueue_IsBlocking(int pIndex)

{
  
  if (pIndex != 0) {
    return 0;
  }
  if ((GameSetup_gData.commMode != 0) && (GameSetup_gData.commMode != 1)) {
    return 0;
  }
  return (inputQueue.TailTime[0] <
          nfs4_mips_addu_s32(inputQueue.HeadTime,maxTicksPerFrame)) ^ 1;
}

/* end of simqueue.cpp */

/* owning-TU def (extern-declared, never defined; link-harness) */
int maxTicksPerFrame;
