/* game/common/speech.cpp -- RECONSTRUCTED (NFS4 PSX cop speech/dispatch engine; C++ TU)
 *   101 fns across 7 classes (Speech + Speaker/MobileSpeaker/DispatchSpeaker hierarchy +
 *   CarBank/CarBankName/LocationBank helpers) + 4 free C entry points (Speech_AllocateRAM/
 *   PurgeRAM/HandleRequest/Server). Methods emitted free-fn-with-explicit-this `Class_method`
 *   (structs carry no member-fn protos). Virtual dispatch via _vf[31]. GTE-free.
 */
#include "../../nfs4_types.h"
#include "speech_externs.h"

/* ---- speech.obj OWNED globals (EXT; SYM Globals.jsonl tu=Speech.obj, @0x80111a44+) ---- */
Speech_tCarDescription      Speech_gCarDescription[15];
Speech_tLocationDescription Speech_gLocationDescription00[13];
Speech_tLocationDescription Speech_gLocationDescription02[14];
Speech_tLocationDescription Speech_gLocationDescription03[13];
Speech_tLocationDescription Speech_gLocationDescription04[9];
Speech_tLocationDescription Speech_gLocationDescription05[14];
Speech_tLocationDescription Speech_gLocationDescription06[11];
Speech_tLocationDescription Speech_gLocationDescription07[11];
Speech_tLocationDescription *Speech_gLocationDescription[11];
Speech_tCallSignDescription Speech_gCallSignDescription[1];
Speech_tMobileVoiceAttr     Speech_gCopAttr[9];
/* Speech::fgSpeech static-member singleton (active engine instance; $gp+0x838=0x8013cd84) */
Speech            *Speech_fgSpeech;
/* Speech::fgUndefined static-member buffer (cfront fn-local static _6Speech.fgUndefined,
   756 B @0x8013cd88). NOT zero scratch -- it is a packed bank-name lookup table: slot[0]
   is a runtime Speaker* (0 in image), followed by 3-/4-char model abbreviations + full names
   compared in Speech_CarBankName (strncmp vs +0x2c4/+0x2cc/+0x2d4/+0x2dc). Bytes verified
   byte-exact vs NFS4.EXE .data. All bytes <=0x7f -> fit signed char, no narrowing. */
char Speech_fgUndefined[756] = {
    0x00,0x00,0x00,0x00,0x42,0x4d,0x57,0x5a,0x00,0x00,0x00,0x00,
    0x62,0x6d,0x77,0x7a,0x33,0x2e,0x00,0x00,0x62,0x6d,0x77,0x2e,
    0x00,0x00,0x00,0x00,0x7a,0x33,0x2e,0x00,0x48,0x53,0x56,0x54,
    0x00,0x00,0x00,0x00,0x73,0x65,0x64,0x61,0x6e,0x2e,0x00,0x00,
    0x46,0x4f,0x52,0x44,0x00,0x00,0x00,0x00,0x43,0x4d,0x52,0x4f,
    0x00,0x00,0x00,0x00,0x63,0x68,0x76,0x63,0x61,0x6d,0x2e,0x00,
    0x63,0x68,0x65,0x76,0x72,0x6f,0x2e,0x00,0x63,0x61,0x6d,0x2e,
    0x00,0x00,0x00,0x00,0x54,0x52,0x41,0x4d,0x00,0x00,0x00,0x00,
    0x70,0x6f,0x6e,0x74,0x2e,0x00,0x00,0x00,0x41,0x44,0x42,0x37,
    0x00,0x00,0x00,0x00,0x61,0x73,0x74,0x6f,0x6e,0x2e,0x00,0x00,
    0x4a,0x58,0x4b,0x52,0x00,0x00,0x00,0x00,0x6a,0x61,0x67,0x2e,
    0x00,0x00,0x00,0x00,0x42,0x4d,0x57,0x4d,0x00,0x00,0x00,0x00,
    0x62,0x6d,0x77,0x6d,0x35,0x2e,0x00,0x00,0x6d,0x35,0x2e,0x00,
    0x43,0x4f,0x52,0x56,0x00,0x00,0x00,0x00,0x63,0x68,0x76,0x63,
    0x6f,0x72,0x2e,0x00,0x63,0x6f,0x72,0x76,0x2e,0x00,0x00,0x00,
    0x50,0x39,0x39,0x33,0x00,0x00,0x00,0x00,0x70,0x6f,0x72,0x39,
    0x31,0x31,0x2e,0x00,0x70,0x6f,0x72,0x73,0x63,0x2e,0x00,0x00,
    0x44,0x49,0x41,0x42,0x00,0x00,0x00,0x00,0x6c,0x61,0x6d,0x64,
    0x69,0x61,0x2e,0x00,0x6c,0x61,0x6d,0x62,0x2e,0x00,0x00,0x00,
    0x64,0x69,0x61,0x2e,0x00,0x00,0x00,0x00,0x4d,0x43,0x46,0x31,
    0x00,0x00,0x00,0x00,0x6d,0x63,0x6c,0x61,0x72,0x2e,0x00,0x00,
    0x58,0x39,0x39,0x33,0x00,0x00,0x00,0x00,0x58,0x43,0x46,0x31,
    0x00,0x00,0x00,0x00,0x73,0x70,0x6f,0x72,0x74,0x2e,0x00,0x00,
    0x63,0x61,0x62,0x2e,0x00,0x00,0x00,0x00,0x62,0x61,0x6f,0x76,
    0x2e,0x00,0x00,0x00,0x74,0x75,0x6e,0x2e,0x00,0x00,0x00,0x00,
    0x73,0x63,0x72,0x76,0x2e,0x00,0x00,0x00,0x74,0x77,0x72,0x2e,
    0x00,0x00,0x00,0x00,0x62,0x72,0x67,0x2e,0x00,0x00,0x00,0x00,
    0x66,0x72,0x6d,0x2e,0x00,0x00,0x00,0x00,0x70,0x69,0x6b,0x65,
    0x2e,0x00,0x00,0x00,0x6c,0x74,0x75,0x6e,0x2e,0x00,0x00,0x00,
    0x69,0x63,0x65,0x63,0x2e,0x00,0x00,0x00,0x6d,0x61,0x72,0x2e,
    0x00,0x00,0x00,0x00,0x62,0x61,0x79,0x2e,0x00,0x00,0x00,0x00,
    0x72,0x61,0x72,0x63,0x2e,0x00,0x00,0x00,0x6c,0x74,0x68,0x2e,
    0x00,0x00,0x00,0x00,0x72,0x75,0x69,0x6e,0x2e,0x00,0x00,0x00,
    0x73,0x70,0x66,0x6c,0x2e,0x00,0x00,0x00,0x74,0x62,0x72,0x67,
    0x2e,0x00,0x00,0x00,0x62,0x67,0x64,0x72,0x2e,0x00,0x00,0x00,
    0x6f,0x76,0x65,0x72,0x2e,0x00,0x00,0x00,0x66,0x6c,0x64,0x2e,
    0x00,0x00,0x00,0x00,0x73,0x74,0x75,0x6e,0x2e,0x00,0x00,0x00,
    0x68,0x74,0x6f,0x75,0x2e,0x00,0x00,0x00,0x6f,0x67,0x74,0x2e,
    0x00,0x00,0x00,0x00,0x74,0x72,0x6e,0x78,0x2e,0x00,0x00,0x00,
    0x6c,0x73,0x70,0x2e,0x00,0x00,0x00,0x00,0x68,0x73,0x76,0x2e,
    0x00,0x00,0x00,0x00,0x70,0x65,0x6e,0x74,0x2e,0x00,0x00,0x00,
    0x77,0x66,0x72,0x6d,0x2e,0x00,0x00,0x00,0x6f,0x77,0x65,0x6c,
    0x2e,0x00,0x00,0x00,0x74,0x6f,0x6c,0x6c,0x2e,0x00,0x00,0x00,
    0x6f,0x62,0x77,0x6d,0x2e,0x00,0x00,0x00,0x76,0x69,0x6c,0x6c,
    0x2e,0x00,0x00,0x00,0x6f,0x6d,0x75,0x73,0x2e,0x00,0x00,0x00,
    0x6b,0x6e,0x67,0x6d,0x2e,0x00,0x00,0x00,0x68,0x70,0x69,0x6e,
    0x2e,0x00,0x00,0x00,0x61,0x72,0x63,0x68,0x2e,0x00,0x00,0x00,
    0x6d,0x65,0x64,0x69,0x2e,0x00,0x00,0x00,0x66,0x61,0x72,0x6d,
    0x2e,0x00,0x00,0x00,0x61,0x6c,0x6c,0x2e,0x00,0x00,0x00,0x00,
    0x64,0x69,0x73,0x2e,0x00,0x00,0x00,0x00,0x63,0x65,0x6e,0x2e,
    0x00,0x00,0x00,0x00,0x63,0x6f,0x6e,0x74,0x2e,0x00,0x00,0x00,
    0x68,0x71,0x2e,0x00,0x63,0x6f,0x75,0x2e,0x00,0x00,0x00,0x00,
    0x32,0x30,0x2e,0x00,0x32,0x35,0x2e,0x00,0x33,0x31,0x2e,0x00,
    0x33,0x37,0x2e,0x00,0x33,0x38,0x2e,0x00,0x34,0x33,0x2e,0x00,
    0x34,0x35,0x2e,0x00,0x34,0x36,0x2e,0x00,0x35,0x32,0x2e,0x00,
    0x32,0x31,0x37,0x2e,0x00,0x00,0x00,0x00,0x32,0x32,0x33,0x2e,
    0x00,0x00,0x00,0x00,0x33,0x31,0x36,0x2e,0x00,0x00,0x00,0x00,
    0x33,0x33,0x32,0x2e,0x00,0x00,0x00,0x00,0x33,0x35,0x35,0x2e,
    0x00,0x00,0x00,0x00,0x33,0x37,0x31,0x2e,0x00,0x00,0x00,0x00,
    0x6a,0x3a,0x69,0x64,0x5c,0x00,0x00,0x00,0x6a,0x3a,0x63,0x61,
    0x72,0x73,0x5c,0x00,0x6a,0x3a,0x63,0x69,0x64,0x5c,0x00,0x00,
    0x6a,0x3a,0x63,0x6c,0x69,0x70,0x2e,0x00,0x66,0x72,0x65,0x00,
    0x67,0x65,0x72,0x00,0x62,0x72,0x74,0x00,0x65,0x6e,0x67,0x00,
};
/* gSpeechBankPool: in-race speech bank pool head (STAT void*, MEMORY-POOL-OVERLAY w/ CF_DVLC) */
void              *gSpeechBankPool;
/* @0x8013d06c: packed language-suffix table (4-byte stride, 3-char codes; bytes verified vs
   NFS4.EXE). Read in StartUp via switch(GameSetup_gData.languageSpeech) -> "%szzzz%s.viv". */
static char        gSpeechLangSuffix[4][4] = { "fre", "ger", "brt", "eng" };

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void *Speech_AllocateRAM(int numBytes,char *message);
void Speech_PurgeRAM(void *memPtr);
void Speech_HandleRequest(long bank,long localoffset,long size,long event);
void CarBankName_SetCar(CarBankName *pThis,int carIndex);
bool CarBank_Check(CarBank *pThis,char *name,u_int id,CarBankName *bankname);
void Speaker_SetCar(Speaker *pThis,Car_tObj *car);
void Speech_CountLocations(Speech *pThis);
u_int Speech_CheckLocationBank(Speech *pThis,LocationBank *locationbank,char *name,int id);
int LocationBank_Distance(LocationBank *pThis,int slice);
void * Speech_FindClosestLocationTo(Speech *pThis,LocationBank *bank,int slice);
void Speaker_FindLocation(Speaker *pThis,Car_tObj *car);
bool Speech_CheckCallSignBank(Speech *pThis,CallSignBank *bank,char *name,u_int id);
u_int Speech_CheckMultiBank(Speech *pThis,char *name,u_int id,CarBankName *bn);
int Speech_CalculateBankSize(Speech *pThis,char *header,CarBankName *bn,long *hoffset,long *hsize);
void Speech_LoadBankHeaders(Speech *pThis,char *header,CarBankName *bn,long hoffset,long hsize);
Speech * Speech_ct(Speech *pThis);
void Speech_Reset(void);
void Speech_dt(Speech *pThis,u_int __in_chrg);
u_int Speech_BankPatch(Speech *pThis,int bank,Car_tObj *car);
int Speech_SubmitRequest(int bank,int localoffset,u_int size);
void Speaker_Report(Speaker *pThis,Car_tObj *cop);
void Speaker_Deny(Speaker *pThis);
void Speaker_Grant(Speaker *pThis);
void Speaker_Ready(Speaker *pThis,Car_tObj *wing);
void Speaker_Engage(Speaker *pThis,Car_tObj *perp);
void Speaker_Lose(Speaker *pThis);
void Speaker_Accident(Speaker *pThis,int slice);
void Speaker_Catch(Speaker *pThis,int ticket);
void Speaker_RoadBlock(Speaker *pThis);
void Speaker_SpikeBelt(Speaker *pThis);
void Speaker_Backup(Speaker *pThis);
void Speaker_ReportBlockade(Speaker *pThis);
void Speaker_Roger(Speaker *pThis);
void Speaker_Bullhorn(Speaker *pThis);
void Speaker_Purge(Speaker *pThis);
void Speaker_Promote(Speaker *pThis);
void Speech_Server(void);
void Speech_SetDelayedStatus(Speech *pThis,Speaker *sub,int delay);
void DispatchSpeaker_Activate(DispatchSpeaker *pThis,u_int seedupdatecount);
intptr Speech_Dispatch(void);
void DispatchSpeaker_Roger(DispatchSpeaker *pThis);
void DispatchSpeaker_StatusReply(DispatchSpeaker *pThis);
void DispatchSpeaker_Status(DispatchSpeaker *pThis);
void MobileSpeaker_Status(MobileSpeaker *pThis);
void DispatchSpeaker_ClearPerp(DispatchSpeaker *pThis,Car_tObj *car);
void * DispatchSpeaker_KnownPerp(DispatchSpeaker *pThis,Car_tObj *car);
void DispatchSpeaker_AddPerp(DispatchSpeaker *pThis,Car_tObj *car);
void DispatchSpeaker_Report(DispatchSpeaker *pThis,Car_tObj *perp);
void DispatchSpeaker_Accident(DispatchSpeaker *pThis,int slice);
void DispatchSpeaker_Deny(DispatchSpeaker *pThis);
void DispatchSpeaker_Grant(DispatchSpeaker *pThis);
void DispatchSpeaker_Ready(DispatchSpeaker *pThis,Car_tObj *carObj);
int Speech_PickVoice(Speech *pThis,Car_tObj *carObj);
void Speech_GetVoice(Car_tObj *carObj);
void MobileSpeaker_Activate(MobileSpeaker *pThis,Car_tObj *carObj);
void MobileSpeaker_ReActivate(MobileSpeaker *pThis);
Speaker * Speech_FindMobile(Speech *pThis,Car_tObj *carObj);
intptr Speech_Mobile(Car_tObj *carObj);
int Speaker_CalcMph(Speaker *pThis,Car_tObj *perp);
void MobileSpeaker_SetSpeed(MobileSpeaker *pThis,Car_tObj *perp);
int MobileSpeaker_DistToPerp(MobileSpeaker *pThis);
void MobileSpeaker_Report(MobileSpeaker *pThis,Car_tObj *perp);
void MobileSpeaker_Engage(MobileSpeaker *pThis,Car_tObj *perp);
void MobileSpeaker_Lose(MobileSpeaker *pThis);
void MobileSpeaker_Accident(MobileSpeaker *pThis,int slice);
void MobileSpeaker_Catch(MobileSpeaker *pThis,int ticket);
void MobileSpeaker_RoadBlock(MobileSpeaker *pThis);
void MobileSpeaker_SpikeBelt(MobileSpeaker *pThis);
void MobileSpeaker_Backup(MobileSpeaker *pThis);
void MobileSpeaker_Roger(MobileSpeaker *pThis);
void MobileSpeaker_Bullhorn(MobileSpeaker *pThis);
void MobileSpeaker_Purge(MobileSpeaker *pThis);
void MobileSpeaker_ReportBlockade(MobileSpeaker *pThis);
Car_tObj * MobileSpeaker_Perp(MobileSpeaker *pThis);
int MobileSpeaker_Unit(MobileSpeaker *pThis);
CallSignBank * MobileSpeaker_CallSign(MobileSpeaker *pThis);
LocationBank * MobileSpeaker_FindClosestLocationTo(MobileSpeaker *pThis,int slice);
CarBank * MobileSpeaker_GetCarBank(MobileSpeaker *pThis,int carIndex);
Car_tObj * MobileSpeaker_CarObj(MobileSpeaker *pThis);
void * MobileSpeaker_IsSuper(MobileSpeaker *pThis);
CallSignBank * DispatchSpeaker_CallSign(DispatchSpeaker *pThis);
LocationBank * DispatchSpeaker_FindClosestLocationTo(DispatchSpeaker *pThis,int slice);
CarBank * DispatchSpeaker_GetCarBank(DispatchSpeaker *pThis,int carIndex);
void DispatchSpeaker_PurgeStatusSub(DispatchSpeaker *pThis);
Speaker * DispatchSpeaker_StatusSub(DispatchSpeaker *pThis);
int DispatchSpeaker_StatusCount(DispatchSpeaker *pThis);
LocationBank * Speaker_FindClosestLocationTo(Speaker *pThis,int slice);
CarBank * Speaker_GetCarBank(Speaker *pThis,int carIndex);
Car_tObj * Speaker_Perp(Speaker *pThis);
void Speaker_ReActivate(Speaker *pThis);
Car_tObj * Speaker_CarObj(Speaker *pThis);
int Speaker_DistToPerp(Speaker *pThis);
void Speaker_PurgeStatusSub(Speaker *pThis);
Speaker * Speaker_StatusSub(Speaker *pThis);
int Speaker_StatusCount(Speaker *pThis);
void * Speaker_IsSuper(Speaker *pThis);
void Speaker_ClearPerp(Speaker *pThis,Car_tObj *car);
void * Speaker_KnownPerp(Speaker *pThis,Car_tObj *car);
int Speaker_Unit(Speaker *pThis);
void Speaker_Status(Speaker *pThis);


/* ---- Speech_AllocateRAM__FlPc  [SPEECH.CPP:169-170] SLD-VERIFIED ---- */
void *Speech_AllocateRAM(int numBytes,char *message)

{
  return reservememadr(message,numBytes,0);
}

/* ---- Speech_PurgeRAM__FPc  [SPEECH.CPP:174-175] SLD-VERIFIED ---- */
void Speech_PurgeRAM(void *memPtr)

{
  purgememadr(memPtr);
  return;
}

/* ---- Speech_HandleRequest__Fllll  [SPEECH.CPP:179-180] SLD-VERIFIED ---- */
void Speech_HandleRequest(long bank,long localoffset,long size,long event)

{
  Speech_SubmitRequest(bank,localoffset,size);
  return;
}

/* ---- SetCar__Q26Speech11CarBankNamei  [SPEECH.CPP:234-246] SLD-VERIFIED ---- */
void CarBankName_SetCar(CarBankName *pThis,int carIndex)

{
  char*game;
  Speech_tCarDescription * d;
  int iVar1;
  int iVar2;
  char *pcVar3;
  Speech_tCarDescription *pSVar4;
  
  pSVar4 = Speech_gCarDescription;
  iVar1 = GameSetup_gData.carInfo[carIndex].carType;
  pcVar3 = Speech_gCarDescription[0].game;
  while ((pcVar3 != (char *)0x0 &&
         (iVar2 = strncmp(GameSetup_gCarNames[iVar1],pSVar4->game,4), iVar2 != 0)
         )) {
    pSVar4 = pSVar4 + 1;
    pcVar3 = pSVar4->game;
  }
  pThis->fFull = pSVar4->full;
  pThis->fMake = pSVar4->make;
  pThis->fModel = pSVar4->model;
  return;
}

/* ---- Check__Q26Speech7CarBankPciPQ26Speech11CarBankName  [SPEECH.CPP:257-275] SLD-VERIFIED ---- */
bool CarBank_Check(CarBank *pThis,char *name,u_int id,CarBankName *bankname)

{
  int match;
  bool bVar1;
  long lVar2;
  int iVar3;
  bool bVar4;
  
  bVar4 = false;
  if (bankname->fFull != 0) {
    lVar2 = strlen(bankname->fFull);
    iVar3 = strncmp(name,bankname->fFull,lVar2);
    bVar4 = iVar3 == 0;
  }
  if (bVar4) {
    pThis->fFull = id;
  }
  bVar1 = false;
  if (bankname->fMake != 0) {
    lVar2 = strlen(bankname->fMake);
    iVar3 = strncmp(name,bankname->fMake,lVar2);
    bVar1 = iVar3 == 0;
  }
  if (bVar1) {
    pThis->fMake = id;
    bVar4 = true;
  }
  bVar1 = false;
  if (bankname->fModel != 0) {
    lVar2 = strlen(bankname->fModel);
    iVar3 = strncmp(name,bankname->fModel,lVar2);
    bVar1 = iVar3 == 0;
  }
  if (bVar1) {
    pThis->fModel = id;
    bVar4 = true;
  }
  return bVar4;
}

/* ---- CheckCarBank__6SpeechPQ26Speech7CarBankPciPQ26Speech11CarBankName  [SPEECH.CPP:281-295] SLD-VERIFIED ---- */
u_int
Speech_CheckCarBank(Speech *pThis,CarBank *carbank,char *name,u_int id,CarBankName *bankname)

{
  int match;
  int i;
  int iVar1;
  int iVar2;
  u_int uVar3;
  
  iVar2 = 0;
  uVar3 = 0;
  if (0 < pThis->fCarCount) {
    do {
      iVar1 = CarBank_Check(carbank,name,id,bankname);
      if (iVar1 != 0) {
        uVar3 = 1;
      }
      bankname = bankname + 1;
      iVar2 = iVar2 + 1;
      carbank = carbank + 1;
    } while (iVar2 < pThis->fCarCount);
  }
  return uVar3;
}

/* ---- SetCar__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:301-373] SLD-VERIFIED ---- */
void Speaker_SetCar(Speaker *pThis,Car_tObj *car)

{
  int carcolour;
  int *piVar1;
  int iVar2;
  int Colour;
  u_int uVar3;
  
  uVar3 = 1 << (car->carInfo->SpeechColour & 0x1fU);
  piVar1 = (int *)NFS4_VCALL_AUTO((*pThis->_vf)[0x1c].pfn, (int)&(pThis->fPosition).flags + (int)(*pThis->_vf)[0x1c].delta,
                             car->carIndex);
  if (*piVar1 == -1) {
    pThis->fCar = 0;
    (pThis->fColour).flags = 0;
  }
  else {
    if (*(int *)(((int)Speech_fgSpeech) + 0x388) == 0) {
      (pThis->fColour).flags = uVar3 | 0x78020;
    }
    else {
      (pThis->fColour).flags = uVar3;
    }
    iVar2 = Speech_Dispatch();
    iVar2 = (**(int (**)(...))(*(int *)(iVar2 + 0x4c) + 0x94))
                      (iVar2 + *(short *)(*(int *)(iVar2 + 0x4c) + 0x90),car);
    if (iVar2 == 0) {
      piVar1 = (int *)NFS4_VCALL_AUTO((*pThis->_vf)[0x1c].pfn, (int)&(pThis->fPosition).flags + (int)(*pThis->_vf)[0x1c].delta,
                                 car->carIndex);
      pThis->fCar = *piVar1;
    }
    else {
      iVar2 = NFS4_VCALL_AUTO((*pThis->_vf)[0x1c].pfn, (int)&(pThis->fPosition).flags + (int)(*pThis->_vf)[0x1c].delta,car->carIndex
                        );
      pThis->fCar = *(int *)(iVar2 + 8);
    }
  }
  return;
}

/* ---- CountLocations__6Speech  [SPEECH.CPP:521-534] SLD-VERIFIED ---- */
void Speech_CountLocations(Speech *pThis)

{
  Speech_tLocationDescription * d;
  char *pcVar1;
  Speech_tLocationDescription *pSVar2;
  
  pThis->fLocationCount = 0;
  pSVar2 = Speech_gLocationDescription[GameSetup_gData.track];
  if (pSVar2 != (Speech_tLocationDescription *)0x0) {
    pcVar1 = pSVar2->name;
    while (pcVar1 != (char *)0x0) {
      pSVar2 = pSVar2 + 1;
      if (0xf < pThis->fLocationCount) {
        return;
      }
      pThis->fLocationCount = pThis->fLocationCount + 1;
      pcVar1 = pSVar2->name;
    }
  }
  return;
}

/* ---- CheckLocationBank__6SpeechPQ26Speech12LocationBankPci  [SPEECH.CPP:539-561] SLD-VERIFIED ---- */
u_int Speech_CheckLocationBank(Speech *pThis,LocationBank *locationbank,char *name,int id)

{
  int match;
  Speech_tLocationDescription * d;
  int i;
  int bankid;
  short sVar1;
  short sVar2;
  long lVar3;
  int iVar4;
  char *pcVar5;
  Speech_tLocationDescription *pSVar6;
  short *psVar7;
  int iVar8;
  u_int uVar9;
  
  pSVar6 = Speech_gLocationDescription[GameSetup_gData.track];
  uVar9 = 0;
  if (pSVar6 == (Speech_tLocationDescription *)0x0) {
    uVar9 = 0;
  }
  else {
    psVar7 = &pSVar6->end;
    for (iVar8 = 0; iVar8 < pThis->fLocationCount; iVar8 = iVar8 + 1) {
      lVar3 = strlen(pSVar6->name);
      iVar4 = strncmp(name,pSVar6->name,lVar3);
      if (iVar4 == 0) {
        sVar1 = psVar7[-1];
        sVar2 = *psVar7;
        pcVar5 = pSVar6->name;
        uVar9 = 1;
        locationbank->fBankId = id;
        locationbank->fStartSlice = (int)sVar1;
        locationbank->fEndSlice = (int)sVar2;
        locationbank->fName = pcVar5;
      }
      psVar7 = psVar7 + 4;
      pSVar6 = pSVar6 + 1;
      locationbank = locationbank + 1;
    }
  }
  return uVar9;
}

/* ---- Distance__Q26Speech12LocationBanki  [SPEECH.CPP:567-587] SLD-VERIFIED ---- */
int LocationBank_Distance(LocationBank *pThis,int slice)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = pThis->fStartSlice;
  iVar2 = pThis->fEndSlice;
  if (iVar2 < iVar4) {
    if ((iVar4 <= slice) || (iVar1 = slice - iVar2, slice <= iVar2)) {
      return 0;
    }
  }
  else {
    if (iVar4 <= slice) {
      iVar3 = slice - iVar2;
      if (slice <= iVar2) {
        return 0;
      }
      iVar1 = (iVar4 + gNumSlices) - slice;
      goto Distance_clampMin;
    }
    iVar1 = (slice + gNumSlices) - iVar2;
  }
  iVar3 = iVar4 - slice;
Distance_clampMin:
  if (iVar3 < iVar1) {
    iVar1 = iVar3;
  }
  return iVar1;
}

/* ---- FindClosestLocationTo__6SpeechPQ26Speech12LocationBanki  [SPEECH.CPP:594-618] SLD-VERIFIED ---- */
void * Speech_FindClosestLocationTo(Speech *pThis,LocationBank *bank,int slice)

{
  int iVar1;
  int distance;
  LocationBank *locationbank;
  LocationBank *this_00;
  int i;
  int iVar2;
  int closestdistance;
  int iVar3;
  LocationBank *closestbank;
  LocationBank *pLVar4;
  
  if (pThis->fLocationCount == 0) {
    pLVar4 = (LocationBank *)0x0;
  }
  else {
    pLVar4 = (LocationBank *)0x0;
    iVar3 = 10000;
    for (iVar2 = 0; iVar2 < pThis->fLocationCount; iVar2 = iVar2 + 1) {
      this_00 = bank + iVar2;
      if ((this_00->fBankId != -1) && (iVar1 = LocationBank_Distance(this_00,slice), iVar1 < iVar3)
         ) {
        iVar3 = iVar1;
        pLVar4 = this_00;
      }
    }
  }
  return pLVar4;
}

/* ---- FindLocation__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:624-788] SLD-VERIFIED ---- */
void Speaker_FindLocation(Speaker *pThis,Car_tObj *car)

{
  int slice;
  int actual;
  int reg_zero;
  int carPos_x;
  int loc_x_diff;
  int best_dist;
  LocationBank *this_00;
  int carPos_z;
  int loc_idx;
  int loc_x;
  int loc_z_diff;
  int loc_z;
  int loc_radius;
  int distance;
  int iVar1;
  LocationBank *location;
  double reg_f12_13;
  double reg_f14_15;
  
  carPos_x = fixedmult(car->currentSpeed,0x50000);
  if (carPos_x / 0x60000 < 0) {
    iVar1 = fixedmult(car->currentSpeed,0x50000);
    if (-1 < (int)(car->N).simRoadInfo.slice + iVar1 / 0x60000) goto FindLoc_noWrapCalc;
    iVar1 = fixedmult(car->currentSpeed,0x50000);
    iVar1 = (int)(car->N).simRoadInfo.slice + iVar1 / 0x60000 + gNumSlices;
  }
  else {
    loc_x_diff = fixedmult(car->currentSpeed,0x50000);
    if ((int)(car->N).simRoadInfo.slice + loc_x_diff / 0x60000 < gNumSlices) {
FindLoc_noWrapCalc:
      iVar1 = fixedmult(car->currentSpeed,0x50000);
      iVar1 = (int)(car->N).simRoadInfo.slice + iVar1 / 0x60000;
    }
    else {
      best_dist = fixedmult(car->currentSpeed,0x50000);
      iVar1 = ((int)(car->N).simRoadInfo.slice + best_dist / 0x60000) - gNumSlices;
    }
  }
  this_00 = (LocationBank *)
            NFS4_VCALL_AUTO((*pThis->_vf)[0x1d].pfn, (int)&(pThis->fPosition).flags + (int)(*pThis->_vf)[0x1d].delta,iVar1);
  if (this_00 == (LocationBank *)0x0) {
    (pThis->fDistance).flags = 0;
    (pThis->fPosition).flags = 0;
    pThis->fLocation = *(int *)(reg_zero + 8);
    return;
  }
  carPos_z = LocationBank_Distance(this_00,(int)(car->N).simRoadInfo.slice);
  iVar1 = LocationBank_Distance(this_00,iVar1);
  loc_idx = 4;
  if (iVar1 == 0) {
    (pThis->fDistance).flags = 0;
    goto FindLoc_assignIdx;
  }
  __floatsidf(iVar1);
  loc_z_diff = __ltdf2(reg_f12_13,reg_f14_15);
  if (loc_z_diff < 0) {
    (pThis->fDistance).flags = 0;
    if (iVar1 + 2 < carPos_z) {
      (pThis->fPosition).flags = 9;
    }
    if (iVar1 + -2 < carPos_z) {
      (pThis->fPosition).flags = 8;
      goto FindLoc_assignAndReturn;
    }
FindLoc_setIdxDefault:
    loc_idx = 2;
  }
  else {
    if (GameSetup_gData.measurement == 1) {
      if (iVar1 < 0xa6) {
        (pThis->fDistance).flags = 8;
        if (iVar1 + -2 < carPos_z) {
          (pThis->fPosition).flags = 0x10;
          goto FindLoc_assignAndReturn;
        }
      }
      else {
        loc_radius = 0x10;
        (pThis->fDistance).flags = 0x10;
        if (iVar1 + -2 < carPos_z) {
FindLoc_setRadiusReturn:
          (pThis->fPosition).flags = loc_radius;
          goto FindLoc_assignAndReturn;
        }
      }
      goto FindLoc_setIdxDefault;
    }
    if (iVar1 < 0x86) {
      (pThis->fDistance).flags = 1;
      if (carPos_z <= iVar1 + -2) goto FindLoc_setIdxDefault;
      loc_idx = 0x10;
    }
    else {
      loc_radius = 2;
      if (iVar1 < 0x10c) {
        (pThis->fDistance).flags = 2;
        if (carPos_z <= iVar1 + -2) goto FindLoc_setRadiusReturn;
        loc_idx = 0x10;
      }
      else {
        (pThis->fDistance).flags = 4;
        loc_idx = 0x10;
        if (carPos_z <= iVar1 + -2) goto FindLoc_setIdxDefault;
      }
    }
  }
FindLoc_assignIdx:
  (pThis->fPosition).flags = loc_idx;
FindLoc_assignAndReturn:
  pThis->fLocation = this_00->fBankId;
  return;
}

/* ---- CheckCallSignBank__6SpeechPQ26Speech12CallSignBankPci  [SPEECH.CPP:852-884] SLD-VERIFIED ---- */
bool Speech_CheckCallSignBank(Speech *pThis,CallSignBank *bank,char *name,u_int id)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  lVar1 = strlen(Speech_gCallSignDescription[0].AllUnits);
  iVar2 = strncmp(name,Speech_gCallSignDescription[0].AllUnits,lVar1);
  if (iVar2 == 0) {
    bank->fAllUnits = id;
  }
  iVar3 = GameSetup_gData.track % 5;
  lVar1 = strlen(Speech_gCallSignDescription[0].Dispatch[iVar3]);
  iVar3 = strncmp(name,Speech_gCallSignDescription[0].Dispatch[iVar3],lVar1);
  iVar4 = 0;
  if (iVar3 == 0) {
    bank->fDispatch = id;
  }
  bVar5 = iVar3 == 0 || iVar2 == 0;
  for (; iVar4 < 0xf; iVar4 = iVar4 + 1) {
    lVar1 = strlen(Speech_gCallSignDescription[0].Mobile[iVar4]);
    iVar2 = strncmp(name,Speech_gCallSignDescription[0].Mobile[iVar4],lVar1);
    if (iVar2 == 0) {
      bank->fMobile[iVar4] = id;
      bVar5 = true;
    }
  }
  return bVar5;
}

/* ---- CheckMultiBank__6SpeechPciPQ26Speech11CarBankName  [SPEECH.CPP:889-924] SLD-VERIFIED ---- */
u_int Speech_CheckMultiBank(Speech *pThis,char *name,u_int id,CarBankName *bn)

{
  int iVar1;
  
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2c4),5);
  if (iVar1 == 0) {
    return Speech_CheckCallSignBank(pThis,&pThis->fCallSignBank.Dispatch,name + 5,id);
  }
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2cc),7);
  if (iVar1 == 0) {
    return Speech_CheckCarBank(pThis,pThis->fCarBank.Dispatch,name + 7,id,bn);
  }
  iVar1 = strncmp(name,"j:location\\",0xb);
  if (iVar1 == 0) {
    return Speech_CheckLocationBank(pThis,pThis->fLocationBank.Dispatch,name + 0xb,id);
  }
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2d4),6);
  if (iVar1 == 0) {
    return Speech_CheckCallSignBank(pThis,&pThis->fCallSignBank.Mobile,name + 6,id);
  }
  iVar1 = strncmp(name,"j:ccars\\",8);
  if (iVar1 == 0) {
    return Speech_CheckCarBank(pThis,pThis->fCarBank.Mobile,name + 8,id,bn);
  }
  iVar1 = strncmp(name,"j:clocaton\\",0xb);
  if (iVar1 == 0) {
    return Speech_CheckLocationBank(pThis,pThis->fLocationBank.Mobile,name + 0xb,id);
  }
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2dc),7);
  if (iVar1 == 0) {
    pThis->fBlpClpBank = id;
  }
  else {
    iVar1 = strncmp(name,"j:silenc.",9);
    if (iVar1 != 0) {
      return 1;
    }
    pThis->fStaticBank = id;
  }
  return 1;
}

/* ---- CalculateBankSize__6SpeechPcPQ26Speech11CarBankNamePlT3  [SPEECH.CPP:931-984] SLD-VERIFIED ---- */
static u_int Speech_ReadBE32(const u_char *bytes)
{
  return ((u_int)bytes[0] << 24) | ((u_int)bytes[1] << 16) |
         ((u_int)bytes[2] << 8) | (u_int)bytes[3];
}

int Speech_CalculateBankSize(Speech *pThis,char *header,CarBankName *bn,long *hoffset,long *hsize)

{
  long eventOffset;
  long eventSize;
  int bankCount = 0;
  int totalSize = 0;
  u_char *entry = (u_char *)header + 0x10;
  u_int fileCount = Speech_ReadBE32((u_char *)header + 8);

  if (locatebigentry(header,"j:eventdat\\event.dat",0,&eventOffset,&eventSize) != 0) {
    totalSize = eventSize;
    for (u_int i = 0; i < fileCount; i = i + 1) {
      long offset = (long)Speech_ReadBE32(entry);
      long size = (long)Speech_ReadBE32(entry + 4);
      char *name = (char *)entry + 8;
      char *end = name;
      while (*end != '\0') {
        end = end + 1;
      }
      if ((end[-4] == '.') && (end[-3] == 'h') && (end[-2] == 'd') && (end[-1] == 'r')) {
        if (*hoffset == 0) {
          *hoffset = offset;
        }
        *hsize = (offset + size) - *hoffset;
        if (Speech_CheckMultiBank(pThis,name,bankCount,bn) != 0) {
          bankCount = bankCount + 1;
          totalSize = totalSize + size;
        }
      }
      entry = (u_char *)end + 1;
    }
  }
  pThis->fBankCount = bankCount;
  return totalSize;
}

/* ---- LoadBankHeaders__6SpeechPcPQ26Speech11CarBankNamell  [SPEECH.CPP:990-1102] SLD-VERIFIED ---- */
void Speech_LoadBankHeaders(Speech *pThis,char *header,CarBankName *bn,long hoffset,long hsize)

{
  long eventOffset;
  long eventSize;
  int headerBank = 0;
  int nextDataBank = 0;
  u_char *eventData = (u_char *)(pThis->fBankOffset + pThis->fBankCount);
  u_int fileCount = Speech_ReadBE32((u_char *)header + 8);
  u_char *entry = (u_char *)header + 0x10;

  locatebigentry(header,"j:eventdat\\event.dat",0,&eventOffset,&eventSize);
  FILE_readsync(pThis->fFileHandle,eventOffset,(intptr)eventData,eventSize,100);
  SPCH_ResolveData((int)(intptr)eventData);
  u_char *bankData = eventData + eventSize;
  u_char *headerData = (u_char *)reservememadr("spch temp",hsize,0x10);
  FILE_readsync(pThis->fFileHandle,hoffset,(intptr)headerData,hsize,100);
  char **bankNames = (char **)reservememadr("spch temp",pThis->fBankCount * sizeof(char *),0x10);
  for (int i = 0; i < pThis->fBankCount; i = i + 1) {
    bankNames[i] = 0;
    pThis->fBankOffset[i] = 0;
  }
  for (u_int file = 0; file < fileCount; file = file + 1) {
    systemtask(0);
    long offset = (long)Speech_ReadBE32(entry);
    long size = (long)Speech_ReadBE32(entry + 4);
    char *name = (char *)entry + 8;
    int nameLength = 0;
    while (name[nameLength] != '\0') {
      nameLength = nameLength + 1;
    }
    char *end = name + nameLength;
    if (4 < nameLength) {
      bool isHeader = (end[-4] == '.') && (end[-3] == 'h') && (end[-2] == 'd') && (end[-1] == 'r');
      if (isHeader && Speech_CheckMultiBank(pThis,name,headerBank,bn) != 0) {
        headerBank = headerBank + 1;
        memcpy(bankData,headerData + offset - hoffset,size);
        int bankId = SPCH_AddBank((intptr)bankData);
        bankData = bankData + size;
        bankNames[bankId] = name;
      }
      else {
        bool isData = (end[-4] == '.') && (end[-3] == 'd') && (end[-2] == 'a') && (end[-1] == 't');
        if (isData) {
          if ((nextDataBank < pThis->fBankCount) && (bankNames[nextDataBank] != 0) &&
              (strncmp(name,bankNames[nextDataBank],nameLength - 3) == 0)) {
            pThis->fBankOffset[nextDataBank] = offset;
            nextDataBank = nextDataBank + 1;
          }
          else {
            for (int i = 0; i < pThis->fBankCount; i = i + 1) {
              if ((bankNames[i] != 0) && (strncmp(name,bankNames[i],nameLength - 3) == 0)) {
                pThis->fBankOffset[i] = offset;
                nextDataBank = i + 1;
              }
            }
          }
        }
      }
    }
    entry = (u_char *)end + 1;
  }
  purgememadr(headerData);
  purgememadr(bankNames);
  return;
}

/* ---- __6Speech  [SPEECH.CPP:1110-1228] SLD-VERIFIED ---- */
Speech * Speech_ct(Speech *pThis)

{
  bool bVar1;
  DispatchSpeaker *dispatch;
  MobileSpeaker *mobile;
  char *SpeechLanguage;
  void *header;
  int iVar6;
  int iVar8;
  int iVar9;
  int iVar10;
  u_int uVar11;
  CarBankName bankNames[9];
  char acStack_88 [104];
  long local_20;
  long local_1c;
  
  for (iVar8 = 0; iVar8 < 9; iVar8 = iVar8 + 1) {
    pThis->fCarBank.Mobile[iVar8].fFull = -1;
    pThis->fCarBank.Mobile[iVar8].fMake = -1;
    pThis->fCarBank.Mobile[iVar8].fModel = -1;
    pThis->fCarBank.Dispatch[iVar8].fFull = -1;
    pThis->fCarBank.Dispatch[iVar8].fMake = -1;
    pThis->fCarBank.Dispatch[iVar8].fModel = -1;
  }
  for (iVar8 = 0; iVar8 < 16; iVar8 = iVar8 + 1) {
    pThis->fLocationBank.Mobile[iVar8].fBankId = -1;
    pThis->fLocationBank.Dispatch[iVar8].fBankId = -1;
  }
  dispatch = (DispatchSpeaker *)__builtin_new(sizeof(DispatchSpeaker));
  dispatch->_base_Speaker._vf = (__vtbl_ptr_type (*)[31])Speaker_vtable;
  dispatch->_base_Speaker.fSub = 0;
  dispatch->_base_Speaker._vf = (__vtbl_ptr_type (*)[31])DispatchSpeaker_vtable;
  pThis->fDispatch = dispatch;
  for (iVar8 = 0; iVar10 = 0, iVar8 < 4; iVar8 = iVar8 + 1) {
    mobile = (MobileSpeaker *)__builtin_new(sizeof(MobileSpeaker));
    mobile->_base_Speaker._vf = (__vtbl_ptr_type (*)[31])Speaker_vtable;
    mobile->_base_Speaker.fSub = 0;
    mobile->_base_Speaker._vf = (__vtbl_ptr_type (*)[31])MobileSpeaker_vtable;
    mobile->fCarObj = 0;
    pThis->fMobile[iVar8] = mobile;
  }
  iVar9 = 0;
  pThis->fFileOpen = 0;
  pThis->fBankOffset = 0;
  iVar8 = 0;
  if (0 < GameSetup_gData.numCars) {
    do {
      iVar6 = GameSetup_gData.carInfo[iVar9].carClass;
      if ((iVar6 == 1) || (iVar6 == 2)) {
        iVar8 = iVar8 + 1;
      }
      else if (iVar6 == 0x41) {
        iVar10 = iVar10 + 1;
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < GameSetup_gData.numCars);
  }
  if ((iVar10 == 0) && (1 < iVar8)) {
    pThis->fMultiplePerps = 1;
  }
  else {
    pThis->fMultiplePerps = 0;
  }
  iVar8 = 0;
  gettick();
  bVar1 = 0 < GameSetup_gData.numCars;
  pThis->fCarCount = GameSetup_gData.numCars;
  if (bVar1) {
    do {
      CarBankName_SetCar(&bankNames[iVar8],iVar8);
      iVar8 = iVar8 + 1;
    } while (iVar8 < pThis->fCarCount);
  }
  Speech_CountLocations(pThis);
  pThis->fBankCount = 0;
  iVar8 = 0;
  if (GameSetup_gData.languageSpeech == 2) {
    SpeechLanguage = gSpeechLangSuffix[0] /* @0x8013d06c "fre" */;
  }
  else if (GameSetup_gData.languageSpeech < 3) {
    if (GameSetup_gData.languageSpeech == 1) {
      SpeechLanguage = gSpeechLangSuffix[1] /* @0x8013d070 "ger" */;
    }
    else {
      SpeechLanguage = gSpeechLangSuffix[3] /* @0x8013d078 "eng" */;
    }
  }
  else if (GameSetup_gData.languageSpeech == 6) {
    SpeechLanguage = gSpeechLangSuffix[2] /* @0x8013d074 "brt" */;
  }
  else {
    SpeechLanguage = gSpeechLangSuffix[3] /* @0x8013d078 "eng" */;
  }
  sprintf(acStack_88,"%szzzz%s.viv",Paths_Paths[0x1d],SpeechLanguage);
  header = (void *)loadbigfileheader(acStack_88,0x10);
  local_20 = 0;
  local_1c = 0;
  if (header != (void *)0x0) {
    iVar8 = Speech_CalculateBankSize(pThis,(char *)header,bankNames,&local_20,&local_1c);
  }
  if (0 < iVar8) {
    pThis->fBankOffset = (long *)reservememadr("spch index",pThis->fBankCount * sizeof(long) + iVar8,0);
  }
  if (pThis->fBankOffset != 0) {
    uVar11 = SPCH_GetSampleDataRate(0x2b11,0x10,2);
    SPCH_Init((intptr)Speech_HandleRequest,0x12345678,uVar11);
    SPCH_InitBankMem((intptr)Speech_AllocateRAM,
               (intptr)Speech_PurgeRAM,pThis->fBankCount);
    iVar8 = FILE_opensync(acStack_88,1,100,&pThis->fFileHandle);
    pThis->fFileOpen = (u_int)(iVar8 != 0);
    Speech_LoadBankHeaders(pThis,(char *)header,bankNames,local_20,local_1c);
  }
  if (header != (void *)0x0) {
    purgememadr(header);
  }
  gettick();
  return pThis;
}

/* ---- Reset__6Speech  [SPEECH.CPP:1248-1261] SLD-VERIFIED ---- */
void Speech_Reset(void)

{
  u_int uVar3;
  u_int uVar4;
  int iVar6;
  u_int uVar7;
  
  if (Speech_fgSpeech != 0) {
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      Speech_fgSpeech->fMobile[iVar6]->fCarObj = 0;
    }
    SPCH_ClearEventQueue();
    randtemp = fastRandom * randSeed;
    fastRandom = randtemp & 0xffff;
    iSPCH_EACseedrandom((randtemp & 0xffff00) >> 8);
    uVar3 = fastRandom * randSeed;
    uVar4 = (uVar3 & 0xffff) * randSeed;
    randtemp = (uVar4 & 0xffff) * randSeed;
    uVar7 = (randtemp & 0xffff00) >> 8;
    fastRandom = randtemp & 0xffff;
    Speech_fgSpeech->fCopCount = ((uVar3 & 0xffff00) >> 8) % 9;
    Speech_fgSpeech->fSuperCount = ((uVar4 & 0xffff00) >> 8) % 6;
    DispatchSpeaker_Activate(Speech_fgSpeech->fDispatch,
               uVar7 + (uVar7 / 7 + (uVar7 - uVar7 / 7 >> 1) >> 2) * -7);
  }
  return;
}

/* ---- _._6Speech  [SPEECH.CPP:1267-1283] SLD-VERIFIED ---- */
void Speech_dt(Speech *pThis,u_int __in_chrg)

{
  int i;
  int iVar3;
  
  if (pThis->fBankOffset != 0) {
    SPCH_Deinit();
    purgememadr(pThis->fBankOffset);
  }
  if (pThis->fFileOpen != 0) {
    FILE_closesync(pThis->fFileHandle,100);   /* oracle 0x85b84/b88: a1=0x64 (was dropped) */
  }
  iVar3 = 0;
  __builtin_delete(pThis->fDispatch);
  do {
    __builtin_delete(pThis->fMobile[iVar3]);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  if ((__in_chrg & 1) != 0) {
    __builtin_delete(pThis);
  }
  return;
}

/* ---- BankPatch__6SpeechlP8Car_tObj  [SPEECH.CPP:1297-1307] SLD-VERIFIED ---- */
u_int Speech_BankPatch(Speech *pThis,int bank,Car_tObj *car)

{
  u_int uVar1;
  
  if (bank == pThis->fStaticBank) {
    return 0x15;
  }
  uVar1 = 0xffffffff;
  if ((bank == pThis->fBlpClpBank) && (uVar1 = 0x13, car != 0)) {
    uVar1 = 0x14;
  }
  return uVar1;
}

/* ---- SubmitRequest__6Speechlll  [SPEECH.CPP:1317-1342] SLD-VERIFIED ---- */
int Speech_SubmitRequest(int bank,int localoffset,u_int size)

{
  Car_tObj *car;
  int patch;
  int offset;
  
  if (Speech_fgSpeech == 0) {
    offset = 0;
  }
  else {
    Speech_fgSpeech->fDispatch->fStatusSub = 0;
    Speech_fgSpeech->fDispatch->fStatusCount = 0x200;
    car = Speech_fgSpeech->fSpeakerCar;
    patch = Speech_BankPatch(Speech_fgSpeech,bank,car);
    if ((bank < 0) || (Speech_fgSpeech->fBankCount <= bank)) {
      offset = 0;
    }
    else {
      offset = Speech_fgSpeech->fBankOffset[bank];
    }
    if (patch < 0) {
      if (offset != 0) {
        CopSpeak_DirectRequest(Speech_fgSpeech->fFileHandle,offset + localoffset,size,car,0);
      }
      offset = offset + localoffset;
    }
    else {
      CopSpeak_GenericBankRequest(patch,car);
      offset = offset + localoffset;
    }
  }
  return offset;
}

/* ---- Report__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:1352-1356] SLD-VERIFIED ---- */
void Speaker_Report(Speaker *pThis,Car_tObj *cop)

{
  return;
}

/* ---- Deny__Q26Speech7Speaker  [SPEECH.CPP:1363-1367] SLD-VERIFIED ---- */
void Speaker_Deny(Speaker *pThis)

{
  return;
}

/* ---- Grant__Q26Speech7Speaker  [SPEECH.CPP:1371-1375] SLD-VERIFIED ---- */
void Speaker_Grant(Speaker *pThis)

{
  return;
}

/* ---- Ready__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:1379-1383] SLD-VERIFIED ---- */
void Speaker_Ready(Speaker *pThis,Car_tObj *wing)

{
  return;
}

/* ---- Engage__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:1394-1398] SLD-VERIFIED ---- */
void Speaker_Engage(Speaker *pThis,Car_tObj *perp)

{
  return;
}

/* ---- Lose__Q26Speech7Speaker  [SPEECH.CPP:1402-1406] SLD-VERIFIED ---- */
void Speaker_Lose(Speaker *pThis)

{
  return;
}

/* ---- Accident__Q26Speech7Speakeri  [SPEECH.CPP:1410-1414] SLD-VERIFIED ---- */
void Speaker_Accident(Speaker *pThis,int slice)

{
  return;
}

/* ---- Catch__Q26Speech7Speakeri  [SPEECH.CPP:1418-1422] SLD-VERIFIED ---- */
void Speaker_Catch(Speaker *pThis,int ticket)

{
  return;
}

/* ---- RoadBlock__Q26Speech7Speaker  [SPEECH.CPP:1426-1430] SLD-VERIFIED ---- */
void Speaker_RoadBlock(Speaker *pThis)

{
  return;
}

/* ---- SpikeBelt__Q26Speech7Speaker  [SPEECH.CPP:1434-1438] SLD-VERIFIED ---- */
void Speaker_SpikeBelt(Speaker *pThis)

{
  return;
}

/* ---- Backup__Q26Speech7Speaker  [SPEECH.CPP:1442-1446] SLD-VERIFIED ---- */
void Speaker_Backup(Speaker *pThis)

{
  return;
}

/* ---- ReportBlockade__Q26Speech7Speaker  [SPEECH.CPP:1450-1454] SLD-VERIFIED ---- */
void Speaker_ReportBlockade(Speaker *pThis)

{
  return;
}

/* ---- Roger__Q26Speech7Speaker  [SPEECH.CPP:1459-1463] SLD-VERIFIED ---- */
void Speaker_Roger(Speaker *pThis)

{
  return;
}

/* ---- Bullhorn__Q26Speech7Speaker  [SPEECH.CPP:1467-1471] SLD-VERIFIED ---- */
void Speaker_Bullhorn(Speaker *pThis)

{
  return;
}

/* ---- Purge__Q26Speech7Speaker  [SPEECH.CPP:1475-1479] SLD-VERIFIED ---- */
void Speaker_Purge(Speaker *pThis)

{
  return;
}

/* ---- Promote__Q26Speech7Speaker  [SPEECH.CPP:1490-1503] SLD-VERIFIED ---- */
void Speaker_Promote(Speaker *pThis)

{
  Speaker * Sub;
  Speaker *pSVar1;
  int iVar2;
  Speaker *Super;
  Speaker *pSVar3;
  
  pSVar1 = (Speaker *)Speech_Dispatch();
  do {
    pSVar3 = pSVar1;
    pSVar1 = pSVar3->fSub;
  } while (pSVar1 != (Speaker *)0x0 && pSVar1 != pThis);
  pSVar3->fSub = pThis->fSub;
  iVar2 = Speech_Dispatch();
  pThis->fSub = *(Speaker **)(iVar2 + 0x48);
  iVar2 = Speech_Dispatch();
  *(Speaker **)(iVar2 + 0x48) = pThis;
  return;
}

/* ---- Speech_Server__Fv  [SPEECH.CPP:1539-1540] SLD-VERIFIED ---- */
void Speech_Server(void)

{
  Speaker *speaker = (Speaker *)Speech_Dispatch();
  __vtbl_ptr_type *entry = &(*speaker->_vf)[2];
  NFS4_VCALL0(entry->pfn,(u_char *)speaker + entry->delta);
  return;
}

/* ---- SetDelayedStatus__6SpeechPQ26Speech7Speakeri  [SPEECH.CPP:1546-1548] SLD-VERIFIED ---- */
void Speech_SetDelayedStatus(Speech *pThis,Speaker *sub,int delay)

{
  Speech_fgSpeech->fDispatch->fStatusSub = sub;
  Speech_fgSpeech->fDispatch->fStatusCount = delay;
  return;
}

/* ---- Activate__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:1554-1571] SLD-VERIFIED ---- */
void DispatchSpeaker_Activate(DispatchSpeaker *pThis,u_int seedupdatecount)

{
  __vtbl_ptr_type *entry = &(*pThis->_base_Speaker._vf)[30];
  CallSignBank *callSign = (CallSignBank *)NFS4_VCALL_PTR0(
      entry->pfn,(u_char *)pThis + entry->delta);

  pThis->_base_Speaker.fFrom = callSign->fDispatch;
  pThis->_base_Speaker.fConfirm.flags = 0xff;
  pThis->_base_Speaker.fPerpName.flags = 0xf;
  pThis->_base_Speaker.fSub = 0;
  pThis->_base_Speaker.fReverse.flags = GameSetup_gData.track & 1;
  pThis->fPerp[1] = 0;
  pThis->fPerp[0] = 0;
  pThis->fStatusCount = 0x200;
  pThis->fStatusSub = 0;
  pThis->fUpdateCount = seedupdatecount;
  pThis->_base_Speaker.fHavePerp = 0;
  return;
}

/* ---- Dispatch__6Speech  [SPEECH.CPP:1578-1586] SLD-VERIFIED ---- */
intptr Speech_Dispatch(void)

{
  Speaker *result;
  
  if ((Speech_fgSpeech != 0) && (Speech_fgSpeech->fBankOffset != 0)) {
    return (intptr)Speech_fgSpeech->fDispatch;
  }
  return (intptr)*(Speaker **)Speech_fgUndefined;
}

/* ---- Roger__Q26Speech15DispatchSpeaker  [SPEECH.CPP:1592-1629] SLD-VERIFIED ---- */
void DispatchSpeaker_Roger(DispatchSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub;
  Car_tObj *perp;
  CallSignBank *callSign;
  __vtbl_ptr_type *entry;
  int unit;

  Speech_fgSpeech->fSpeakerCar = 0;
  sub = base->fSub;
  if (sub != 0) {
    entry = &(*sub->_vf)[27];
    perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
  }
  else {
    perp = 0;
  }
  if ((sub == 0) || (perp == 0) || (sub->fBlockade.flags != 0)) {
    SPCHNFS_D_A_CONFIRM(&base->fConfirm);
  }
  else if (sub->fArrest.flags != 0) {
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*sub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    base->fTo = callSign->fMobile[unit];
    SPCHNFS_D_C_PERP_APPREHENSION_REPLY(base->fTo,&base->fConfirm,&base->fPerpName);
  }
  else if (sub->fUpdate.flags == 0) {
    SPCHNFS_D_A_CONFIRM(&base->fConfirm);
    SPCH_PlaySpeech();
    Speaker_SetCar(base,perp);
    SPCHNFS_D_C_PERP_LOST_CONFIRM(&base->fColour,base->fCar);
  }
  else {
    Speaker_SetCar(base,perp);
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*sub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    base->fTo = callSign->fMobile[unit];
    entry = &(*sub->_vf)[24];
    if (NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta) < 0x280000) {
      SPCHNFS_D_C_IN_PURS_NEAR_PERP_CONFIRM(&base->fColour,base->fCar,base->fTo,
                                            &base->fConfirm,&base->fPerpName);
    }
    else {
      SPCHNFS_D_C_IN_PURS_AWAY_PERP_CONFIRM(&base->fColour,base->fCar,base->fTo,
                                            &base->fConfirm,&base->fPerpName);
    }
  }
  SPCH_PlaySpeech();
  return;
}

/* ---- StatusReply__Q26Speech15DispatchSpeaker  [SPEECH.CPP:1636-1713] SLD-VERIFIED ---- */
void DispatchSpeaker_StatusReply(DispatchSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub = base->fSub;
  Speaker *savedSub = 0;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *car;
  int unit;
  bool playBlockadeConfirmation = false;

  if (sub == 0) {
    return;
  }
  entry = &(*sub->_vf)[27];
  if (NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta) == 0) {
    return;
  }

  Speech_fgSpeech->fSpeakerCar = 0;
  if (sub->fBlockade.flags == 0) {
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*sub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    base->fTo = callSign->fMobile[unit];
  }
  else {
    if (Speech_fgSpeech->fMultiplePerps != 0) {
      entry = &(*sub->_vf)[13];
      NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
      return;
    }
    savedSub = sub->fSub;
    if ((savedSub != 0) && (savedSub->fBlockade.flags != 0)) {
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      entry = &(*sub->_vf)[17];
      unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
      base->fTo = callSign->fMobile[unit];
      sub = savedSub;
    }
    else {
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fAllUnits;
      savedSub = sub;
    }
    entry = &(*sub->_vf)[13];
    NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    Speech_fgSpeech->fSpeakerCar = 0;
    SPCHNFS_D_A_CONFIRM(&base->fConfirm);
    SPCH_PlaySpeech();
  }

  SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  sub = base->fSub;
  entry = &(*sub->_vf)[25];
  car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
  Speaker_FindLocation(base,car);

  sub = base->fSub;
  if (sub->fBlockade.flags == 1) {
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*savedSub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)savedSub + entry->delta);
    base->fWing = callSign->fMobile[unit];
    base->fSpikeSide.flags = 4;
    SPCHNFS_D_C_SPBLT_CONFIRMED(&base->fPosition,base->fLocation,&base->fDistance,
                                base->fWing,&base->fSpikeSide);
    playBlockadeConfirmation = true;
  }
  else if (sub->fBlockade.flags == 2) {
    SPCHNFS_D_C_RDBLK_CONFIRMED(&base->fPosition,base->fLocation,&base->fDistance);
    playBlockadeConfirmation = true;
  }
  else if (sub->fSub != 0) {
    Speaker *nextSub = sub->fSub;
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*nextSub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)nextSub + entry->delta);
    base->fWing = callSign->fMobile[unit];
    SPCHNFS_D_C_BKUP_REQUEST_GRANT_REPLY(&base->fDistance,&base->fPosition,
                                         base->fLocation,base->fWing);
    SPCH_PlaySpeech();
    entry = &(*sub->_vf)[14];
    NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    pThis->fStatusCount = 0x140;
    pThis->fUpdateCount++;
    pThis->fStatusSub = nextSub;
  }
  if (playBlockadeConfirmation) {
    SPCH_PlaySpeech();
  }

  sub = base->fSub;
  if (savedSub != sub) {
    entry = &(*sub->_vf)[14];
    NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
  }
  if ((sub->fSub != 0) && (sub->fSub->fBlockade.flags != 0)) {
    sub->fBlockade.flags = 0;
  }
}

/* ---- Status__Q26Speech15DispatchSpeaker  [SPEECH.CPP:1718-1848] SLD-VERIFIED ---- */
void DispatchSpeaker_Status(DispatchSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub = base->fSub;
  Speaker *statusSub;
  Speaker *nextSub;
  __vtbl_ptr_type *entry;
  Car_tObj *car;
  Car_tObj *perp;
  CallSignBank *callSign;
  int dist;
  int unit;

  if (sub == 0) {
    return;
  }
  entry = &(*sub->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
  if (perp == 0) {
    return;
  }

  entry = &(*sub->_vf)[25];
  car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
  if ((car->carFlags & 0x200) != 0) {
    entry = &(*sub->_vf)[24];
    dist = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    if (sub->fHavePerp == 0) {
      if (dist < 0x640000) {
        entry = &(*sub->_vf)[27];
        perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
        entry = &(*sub->_vf)[6];
        NFS4_VCALL_P1(entry->pfn,(u_char *)sub + entry->delta,perp);
      }
    }
    else if (dist > 0x15e0000) {
      sub->fHavePerp = 0;
      sub->fUpdate.flags = 0;
      entry = &(*sub->_vf)[2];
      NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    }
  }

  if (pThis->fStatusSub != 0) {
    if (--pThis->fStatusCount != 0) {
      return;
    }
    statusSub = pThis->fStatusSub;
    if (statusSub == base) {
      DispatchSpeaker_StatusReply(pThis);
      return;
    }
    sub = base->fSub;
    entry = &(*statusSub->_vf)[2];
    NFS4_VCALL0(entry->pfn,(u_char *)statusSub + entry->delta);
    if ((sub != 0) && (statusSub == sub->fSub)) {
      return;
    }
    Speech_fgSpeech->fSpeakerCar = 0;
    entry = &(*base->_vf)[14];
    NFS4_VCALL0(entry->pfn,(u_char *)base + entry->delta);
    return;
  }

  if (0 < pThis->fStatusCount) {
    pThis->fStatusCount--;
    return;
  }
  sub = base->fSub;
  if ((sub->fBlockade.flags != 0) || (sub->fArrest.flags != 0)) {
    return;
  }

  nextSub = sub->fSub;
  if (nextSub != 0) {
    entry = &(*nextSub->_vf)[27];
    car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)nextSub + entry->delta);
    entry = &(*sub->_vf)[27];
    perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
    if (car != perp) {
      Speaker_Promote(nextSub);
    }
  }

  switch (pThis->fUpdateCount & 3) {
  case 0:
    sub->fUpdate.flags = 0x26;
    break;
  case 1:
    sub->fUpdate.flags = 1;
    break;
  case 2:
    entry = &(*sub->_vf)[24];
    dist = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    if (dist < 0x280000) {
      entry = &(*sub->_vf)[25];
      car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
      if (Speaker_CalcMph(base,car) > 0x32) {
        entry = &(*sub->_vf)[27];
        perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
        if (Speaker_CalcMph(base,perp) > 0x32) {
          sub->fUpdate.flags = 8;
          break;
        }
      }
    }
    sub->fUpdate.flags = 0x26;
    break;
  case 3:
    entry = &(*sub->_vf)[20];
    if ((NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta) != 0) &&
        (pThis->fUpdateCount == 7)) {
      sub->fUpdate.flags = 0;
      entry = &(*sub->_vf)[2];
      NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
      pThis->fUpdateCount++;
      return;
    }
    entry = &(*sub->_vf)[24];
    dist = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    if (dist < 0x140000) {
      entry = &(*sub->_vf)[15];
      NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
      pThis->fUpdateCount++;
      return;
    }
    sub->fUpdate.flags = 1;
    break;
  }

  Speech_fgSpeech->fSpeakerCar = 0;
  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  entry = &(*sub->_vf)[17];
  unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
  base->fTo = callSign->fMobile[unit];
  SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  SPCHNFS_D_C_IN_PURS_NEAR_PERP(&sub->fUpdate);
  SPCH_PlaySpeech();
  pThis->fStatusCount = 0x60;
  pThis->fStatusSub = sub;
  pThis->fUpdateCount++;
}

/* ---- Status__Q26Speech13MobileSpeaker  [SPEECH.CPP:1853-1948] SLD-VERIFIED ---- */
void MobileSpeaker_Status(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub;
  Speaker *savedDispatchSub;
  DispatchSpeaker *dispatch;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *car;
  Car_tObj *perp;
  int dist;

  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if (perp == 0) {
    return;
  }

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  if (base->fArrest.flags == 1) {
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    SPCHNFS_C_D_PERP_APPREHENSION(&pThis->fVoice,&base->fPerpName);
  }
  else {
    entry = &(*base->_vf)[25];
    car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    if (((car->carFlags & 0x200) != 0) && (base->fUpdate.flags == 0)) {
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      entry = &(*base->_vf)[27];
      perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      Speaker_SetCar(base,perp);
      Speaker_FindLocation(base,pThis->fCarObj);
      SPCHNFS_C_D_PERP_LOST(&pThis->fVoice,&base->fColour,base->fCar,&base->fPosition,
                            base->fLocation,&base->fDistance,&base->fPerpName);
      SPCH_PlaySpeech();

      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      savedDispatchSub = dispatch->_base_Speaker.fSub;
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      dispatch->_base_Speaker.fSub = base;
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      entry = &(*dispatch->_base_Speaker._vf)[14];
      NFS4_VCALL0(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta);
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      dispatch->_base_Speaker.fSub = savedDispatchSub; /* PORTABILITY-REVIEWED: SPEECH-DISPATCH-SAVE-RESTORE-01 */
      return;
    }

    entry = &(*base->_vf)[20];
    sub = base->fSub;
    if ((NFS4_VCALL0(entry->pfn,(u_char *)base + entry->delta) != 0) &&
        (base->fUpdate.flags == 0) && (sub != 0)) {
      entry = &(*sub->_vf)[25];
      car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)sub + entry->delta);
    }
    else {
      car = 0;
    }
    if ((car != 0) && ((car->carFlags & 0x40) == 0)) {
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fAllUnits;
      SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      SPCHNFS_S_C_SUPER_COP_CRITICISM(&pThis->fVoice);
    }
    else {
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      sub = dispatch->_base_Speaker.fSub;
      if ((sub != 0) && (sub->fSub == base)) {
        SPCHNFS_C_C_NEW_OFFICER_ENGAGING(&pThis->fVoice,base->fFrom);
        dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
        sub = dispatch->_base_Speaker.fSub;
        entry = &(*sub->_vf)[14];
        NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
        return;
      }

      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      entry = &(*base->_vf)[27];
      perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      Speaker_SetCar(base,perp);
      entry = &(*base->_vf)[25];
      car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      Speaker_FindLocation(base,car);
      MobileSpeaker_SetSpeed(pThis,pThis->fPerp);
      entry = &(*base->_vf)[24];
      dist = NFS4_VCALL0(entry->pfn,(u_char *)base + entry->delta);

      if (dist < 0x280000) {
        entry = &(*base->_vf)[27];
        perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
        if (perp->N.flightTime > 0x40) {
          SPCHNFS_C_D_IN_PURS_PERP_AIRBORN(&pThis->fVoice);
        }
        else if (base->fUpdate.flags == 1) {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_LOC(&pThis->fVoice,&base->fPosition,
                                                base->fLocation,&base->fDistance);
        }
        else if (base->fUpdate.flags != 8) {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_STS(&pThis->fVoice,&base->fColour,
                                                base->fCar,&base->fDistance,
                                                &base->fPosition,base->fLocation);
        }
        else {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(&pThis->fVoice,pThis->fSpeed,&pThis->fSpeedType);
        }
      }
      else if (base->fHavePerp != 0) {
        if (base->fUpdate.flags == 1) {
          SPCHNFS_C_D_IN_PURS_AWAY_PERP_REPLY_LOC(&pThis->fVoice,&base->fPosition,
                                                  base->fLocation,&base->fDistance,
                                                  &base->fColour,base->fCar,&base->fPerpName);
        }
        else if (base->fUpdate.flags != 8) {
          SPCHNFS_C_D_IN_PURS_AWAY_PERP_REPLY_STS(&pThis->fVoice,&base->fColour,
                                                  base->fCar,&base->fPosition,
                                                  base->fLocation,&base->fDistance);
        }
        else {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(&pThis->fVoice,pThis->fSpeed,&pThis->fSpeedType);
        }
      }
      else {
        if (base->fUpdate.flags == 1) {
          SPCHNFS_C_D_IN_PURS_LOOK_PERP_REPLY_LOC(&pThis->fVoice,&base->fPosition,
                                                  base->fLocation,&base->fDistance,
                                                  &base->fColour,base->fCar);
        }
        else if (base->fUpdate.flags == 8) {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(&pThis->fVoice,pThis->fSpeed,&pThis->fSpeedType);
        }
        else {
          SPCHNFS_C_D_IN_PURS_LOOK_PERP_REPLY_STS(&pThis->fVoice,&base->fColour,
                                                  base->fCar,&base->fPerpName);
        }
      }
    }
  }
  SPCH_PlaySpeech();
}

/* ---- ClearPerp__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1954-1958] SLD-VERIFIED ---- */
void DispatchSpeaker_ClearPerp(DispatchSpeaker *pThis,Car_tObj *car)

{
  int i;
  
  i = 0;
  do {
    if (pThis->fPerp[0] == car) {
      pThis->fPerp[0] = (Car_tObj *)0x0;
    }
    i = i + 1;
    pThis = (DispatchSpeaker *)&(pThis->_base_Speaker).fDistance;
  } while (i < 2);
  return;
}

/* ---- KnownPerp__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1964-1969] SLD-VERIFIED ---- */
void * DispatchSpeaker_KnownPerp(DispatchSpeaker *pThis,Car_tObj *car)

{
  int i;
  
  i = 0;
  do {
    i = i + 1;
    if (pThis->fPerp[0] == car) {
      return (void *)0x1;
    }
    pThis = (DispatchSpeaker *)&(pThis->_base_Speaker).fDistance;
  } while (i < 2);
  return (void *)0x0;
}

/* ---- AddPerp__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1976-1980] SLD-VERIFIED ---- */
void DispatchSpeaker_AddPerp(DispatchSpeaker *pThis,Car_tObj *car)

{
  int i;
  
  i = 0;
  do {
    if (pThis->fPerp[0] == (Car_tObj *)0x0) {
      pThis->fPerp[0] = car;
    }
    i = i + 1;
    pThis = (DispatchSpeaker *)&(pThis->_base_Speaker).fDistance;
  } while (i < 2);
  return;
}

/* ---- Report__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1990-2031] SLD-VERIFIED ---- */
void DispatchSpeaker_Report(DispatchSpeaker *pThis,Car_tObj *perp)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub = base->fSub;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  int unit;
  bool known;

  Speech_fgSpeech->fSpeakerCar = 0;
  entry = &(*base->_vf)[18];
  known = NFS4_VCALL_PTR_P1(entry->pfn,(u_char *)base + entry->delta,perp) != 0;
  if (known && (sub != 0)) {
    if (Speech_fgSpeech->fMultiplePerps == 0) {
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      entry = &(*sub->_vf)[17];
      unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
      base->fTo = callSign->fMobile[unit];
      SPCHNFS_D_C_PERP_SIGHTED_CONFIRM(&base->fConfirm,base->fTo);
      SPCH_PlaySpeech();
    }
  }
  else {
    if (Speech_fgSpeech->fMultiplePerps == 0) {
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fAllUnits;
      SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      Speaker_SetCar(base,perp);
      Speaker_FindLocation(base,perp);
      SPCHNFS_D_C_BEGIN_PURS_REP_SPDR(&base->fColour,base->fCar,&base->fPosition,
                                      base->fLocation,&base->fDistance);
      SPCH_PlaySpeech();
    }
    DispatchSpeaker_AddPerp(pThis,perp);
    pThis->fStatusCount = 0x2a0;
  }
}

/* ---- Accident__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:2039-2043] SLD-VERIFIED ---- */
void DispatchSpeaker_Accident(DispatchSpeaker *pThis,int slice)

{
  return;
}

/* ---- Deny__Q26Speech15DispatchSpeaker  [SPEECH.CPP:2049-2073] SLD-VERIFIED ---- */
void DispatchSpeaker_Deny(DispatchSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub = base->fSub;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  int unit;

  if (sub != 0) {
    Speech_fgSpeech->fSpeakerCar = 0;
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*sub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    base->fTo = callSign->fMobile[unit];
    SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    sub = base->fSub;
    if (sub->fBlockade.flags == 0) {
      SPCHNFS_D_C_BKUP_REQUEST_DENIED_REPLY();
    }
    else {
      SPCHNFS_D_C_RDBLK_SPBLT_DENIED_REPLY(&sub->fBlockade);
    }
    SPCH_PlaySpeech();
    base->fSub->fBlockade.flags = 0;
  }
}

/* ---- Grant__Q26Speech15DispatchSpeaker  [SPEECH.CPP:2079-2098] SLD-VERIFIED ---- */
void DispatchSpeaker_Grant(DispatchSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub = base->fSub;

  /* The second guard is literal MIPS: addiu v0,sub,0x14; beqz v0.
   * It protects the address-of-member expression for the undefined sentinel. */
  if ((sub != 0) && (sub != (Speaker *)(intptr)(intptr)-0x14)) {
    Speech_fgSpeech->fSpeakerCar = 0;
    if (Speech_fgSpeech->fMultiplePerps == 0) {
      SPCHNFS_D_C_RDBLK_SPBLT_GRANT_REPLY(&sub->fBlockade,&base->fConfirm);
      SPCH_PlaySpeech();
    }
  }
}

/* ---- Ready__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:2104-2123] SLD-VERIFIED ---- */
void DispatchSpeaker_Ready(DispatchSpeaker *pThis,Car_tObj *carObj)

{
  int Blockade;
  Speaker *pSVar1;
  __vtbl_ptr_type (*pa_Var2) [31];
  int src_pos;
  Speaker *pSVar3;
  Speaker *Wing;
  
  pSVar1 = (Speaker *)Speech_Mobile(carObj);
  pSVar3 = (pThis->_base_Speaker).fSub;
  if (pSVar3 != (Speaker *)0x0 && pSVar1 != pSVar3) {
    (pSVar1->fBlockade).flags = (pSVar3->fBlockade).flags;
    pSVar3 = (pThis->_base_Speaker).fSub;
    pa_Var2 = pSVar3->_vf;
    src_pos = NFS4_VCALL_AUTO((*pa_Var2)[0x1b].pfn, (int)&(pSVar3->fPosition).flags + (int)(*pa_Var2)[0x1b].delta)
    ;
    NFS4_VCALL_AUTO((*pSVar1->_vf)[6].pfn, (int)&(pSVar1->fPosition).flags + (int)(*pSVar1->_vf)[6].delta,src_pos)
    ;
  }
  pThis->fStatusSub = &pThis->_base_Speaker;
  pThis->fStatusCount = 0x80;
  return;
}

/* ---- PickVoice__6SpeechP8Car_tObj  [SPEECH.CPP:2144-2150] SLD-VERIFIED ---- */
int Speech_PickVoice(Speech *pThis,Car_tObj *carObj)

{
  int iVar1;
  
  if ((carObj->carFlags & 0x40U) != 0) {
    iVar1 = pThis->fSuperCount;
    pThis->fSuperCount = iVar1 + 1;
    return iVar1 % 6;
  }
  if ((carObj->carFlags & 0x80U) == 0) {
    iVar1 = pThis->fCopCount;
    pThis->fCopCount = iVar1 + 1;
    return iVar1 % 9;
  }
  return 0;
}

/* ---- GetVoice__6SpeechP8Car_tObj  [SPEECH.CPP:2156-2157] SLD-VERIFIED ---- */
void Speech_GetVoice(Car_tObj *carObj)

{
  Speech_PickVoice((Speech *)((int)Speech_fgSpeech),carObj);
  return;
}

/* ---- Activate__Q26Speech13MobileSpeakerP8Car_tObj  [SPEECH.CPP:2163-2189] SLD-VERIFIED ---- */
void MobileSpeaker_Activate(MobileSpeaker *pThis,Car_tObj *carObj)

{
  Speech_tMobileVoiceAttr * a;
  int reg_v0;
  int Voice;
  u_long uVar1;
  __vtbl_ptr_type (*pa_Var2) [31];
  int iVar3;
  int unit;
  
  pThis->fCarObj = carObj;
  Speech_GetVoice(carObj);
  pThis->fUnit = reg_v0;
  if ((carObj->carFlags & 0x40U) == 0) {
    uVar1 = Speech_gCopAttr[reg_v0].voice;
  }
  else {
    pThis->fUnit = reg_v0 + 9;
    uVar1 = 8;
  }
  (pThis->fVoice).flags = uVar1;
  pa_Var2 = (pThis->_base_Speaker)._vf;
  iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x1e].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x1e].delta);
  (pThis->_base_Speaker).fFrom = *(int *)(iVar3 + pThis->fUnit * 4 + 8);
  iVar3 = GameSetup_gData.track;
  (pThis->_base_Speaker).fConfirm.flags = 0xff;
  (pThis->_base_Speaker).fPerpName.flags = 0xf;
  (pThis->_base_Speaker).fBlockade.flags = 0;
  (pThis->_base_Speaker).fArrest.flags = 0;
  (pThis->_base_Speaker).fUpdate.flags = 0;
  pThis->fPerp = (Car_tObj *)0x0;
  (pThis->_base_Speaker).fSub = (Speaker *)0x0;
  (pThis->_base_Speaker).fHavePerp = 0;
  (pThis->_base_Speaker).fReverse.flags = iVar3 & 1;
  return;
}

/* ---- ReActivate__Q26Speech13MobileSpeaker  [SPEECH.CPP:2199-2212] SLD-VERIFIED ---- */
void MobileSpeaker_ReActivate(MobileSpeaker *pThis)

{
  int reg_v0;
  int Voice;
  int tu2;
  __vtbl_ptr_type (*pa_Var1) [31];
  int iVar2;
  int unit;
  Speech_tMobileVoiceAttr *a;
  
  a = (Speech_tMobileVoiceAttr *)pThis->fCarObj;
  Speech_GetVoice((Car_tObj *)a);
  pThis->fUnit = reg_v0;
  if ((pThis->fCarObj->carFlags & 0x40U) == 0) {
    tu2 = Speech_gCopAttr[reg_v0].voice;
  }
  else {
    pThis->fUnit = reg_v0 + 9;
    tu2 = 8;
  }
  (pThis->fVoice).flags = tu2;
  pa_Var1 = (pThis->_base_Speaker)._vf;
  iVar2 = NFS4_VCALL_AUTO((*pa_Var1)[0x1e].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var1)[0x1e].delta);
  (pThis->_base_Speaker).fFrom = *(int *)(iVar2 + pThis->fUnit * 4 + 8);
  return;
}

/* ---- FindMobile__6SpeechP8Car_tObj  [SPEECH.CPP:2218-2237] SLD-VERIFIED ---- */
Speaker * Speech_FindMobile(Speech *pThis,Car_tObj *carObj)

{
  MobileSpeaker **ppMVar1;
  int iVar2;
  Speech *pSVar3;
  int iVar4;
  int i;
  
  pSVar3 = pThis;
  for (iVar4 = 0; iVar2 = 0, iVar4 < 4; iVar4 = iVar4 + 1) {
    ppMVar1 = pSVar3->fMobile;
    pSVar3 = (Speech *)&(pSVar3->fCarBank).Mobile[0].fMake;
    if (carObj == (*ppMVar1)->fCarObj) {
      return &(*ppMVar1)->_base_Speaker;
    }
  }
  while( true ) {
    if (3 < iVar2) {
      return (Speaker *)(*(int *)&(Speech_fgUndefined));
    }
    if (pThis->fMobile[0]->fCarObj == (Car_tObj *)0x0) break;
    pThis = (Speech *)&(pThis->fCarBank).Mobile[0].fMake;
    iVar2 = iVar2 + 1;
  }
  MobileSpeaker_Activate(pThis->fMobile[0],carObj);
  return &pThis->fMobile[0]->_base_Speaker;
}

/* ---- Mobile__6SpeechP8Car_tObj  [SPEECH.CPP:2244-2250] SLD-VERIFIED ---- */
intptr Speech_Mobile(Car_tObj *carObj)

{
  Speaker *pSVar1;
  
  pSVar1 = *(Speaker **)Speech_fgUndefined;
  if ((Speech_fgSpeech != 0) && (Speech_fgSpeech->fBankOffset != 0)) {
    pSVar1 = Speech_FindMobile(Speech_fgSpeech,carObj);
  }
  return (intptr)pSVar1;
}

/* ---- CalcMph__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:2256-2257] SLD-VERIFIED ---- */
int Speaker_CalcMph(Speaker *pThis,Car_tObj *perp)

{
  int iVar1;
  
  iVar1 = (perp->linearVel_ch).z;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  iVar1 = fixedmult(0x23ca5,iVar1);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0xffff;
  }
  return iVar1 >> 0x10;
}

/* ---- SetSpeed__Q26Speech13MobileSpeakerP8Car_tObj  [SPEECH.CPP:2263-2272] SLD-VERIFIED ---- */
void MobileSpeaker_SetSpeed(MobileSpeaker *pThis,Car_tObj *perp)

{
  int a;
  int iVar1;
  
  if (GameSetup_gData.measurement == 1) {
    (pThis->fSpeedType).flags = 1;
    iVar1 = (perp->linearVel_ch).z;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    iVar1 = fixedmult(0x39999,iVar1);
    if (iVar1 / 0xa0000 + -3 < 0) {
MSSetSpeed_zeroPath:
      iVar1 = 0;
      goto MSSetSpeed_assignReturn;
    }
    iVar1 = (perp->linearVel_ch).z;
    a = 0x39999;
  }
  else {
    (pThis->fSpeedType).flags = 2;
    iVar1 = (perp->linearVel_ch).z;
    if (iVar1 < 0) {
      iVar1 = -iVar1;
    }
    iVar1 = fixedmult(0x23ca5,iVar1);
    if (iVar1 / 0xa0000 + -3 < 0) goto MSSetSpeed_zeroPath;
    iVar1 = (perp->linearVel_ch).z;
    a = 0x23ca5;
  }
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  iVar1 = fixedmult(a,iVar1);
  iVar1 = iVar1 / 0xa0000 + -3;
MSSetSpeed_assignReturn:
  pThis->fSpeed = iVar1;
  return;
}

/* ---- DistToPerp__Q26Speech13MobileSpeaker  [SPEECH.CPP:2281-2286] SLD-VERIFIED ---- */
int MobileSpeaker_DistToPerp(MobileSpeaker *pThis)

{
  short sVar1;
  int d;
  __vtbl_ptr_type (*pa_Var2) [31];
  int iVar3;
  int iVar4;
  int z;
  int (*pcVar5)(...);
  int x;
  int iVar6;
  
  pa_Var2 = (pThis->_base_Speaker)._vf;
  iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x19].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x19].delta);
  pa_Var2 = (pThis->_base_Speaker)._vf;
  iVar4 = NFS4_VCALL_AUTO((*pa_Var2)[0x1b].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x1b].delta);
  if (*(int *)(iVar3 + 0xa0) - *(int *)(iVar4 + 0xa0) < 1) {
    pa_Var2 = (pThis->_base_Speaker)._vf;
    iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x1b].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x1b].delta);
    pa_Var2 = (pThis->_base_Speaker)._vf;
    sVar1 = (*pa_Var2)[0x19].delta;
    pcVar5 = (*pa_Var2)[0x19].pfn;
  }
  else {
    pa_Var2 = (pThis->_base_Speaker)._vf;
    iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x19].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x19].delta);
    pa_Var2 = (pThis->_base_Speaker)._vf;
    sVar1 = (*pa_Var2)[0x1b].delta;
    pcVar5 = (*pa_Var2)[0x1b].pfn;
  }
  iVar4 = (*pcVar5)((int)&(pThis->_base_Speaker).fPosition.flags + (int)sVar1);
  iVar6 = *(int *)(iVar3 + 0xa0) - *(int *)(iVar4 + 0xa0);
  pa_Var2 = (pThis->_base_Speaker)._vf;
  iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x19].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x19].delta);
  pa_Var2 = (pThis->_base_Speaker)._vf;
  iVar4 = NFS4_VCALL_AUTO((*pa_Var2)[0x1b].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x1b].delta);
  if (*(int *)(iVar3 + 0xa8) - *(int *)(iVar4 + 0xa8) < 1) {
    pa_Var2 = (pThis->_base_Speaker)._vf;
    iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x1b].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x1b].delta);
    pa_Var2 = (pThis->_base_Speaker)._vf;
    sVar1 = (*pa_Var2)[0x19].delta;
    pcVar5 = (*pa_Var2)[0x19].pfn;
  }
  else {
    pa_Var2 = (pThis->_base_Speaker)._vf;
    iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x19].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x19].delta);
    pa_Var2 = (pThis->_base_Speaker)._vf;
    sVar1 = (*pa_Var2)[0x1b].delta;
    pcVar5 = (*pa_Var2)[0x1b].pfn;
  }
  iVar4 = (*pcVar5)((int)&(pThis->_base_Speaker).fPosition.flags + (int)sVar1);
  iVar3 = *(int *)(iVar3 + 0xa8) - *(int *)(iVar4 + 0xa8);
  if (iVar3 < iVar6) {
    iVar6 = iVar6 + (iVar3 >> 2);
  }
  else {
    iVar6 = iVar3 + (iVar6 >> 2);
  }
  return iVar6;
}

/* ---- Report__Q26Speech13MobileSpeakerP8Car_tObj  [SPEECH.CPP:2295-2316] SLD-VERIFIED ---- */
void MobileSpeaker_Report(MobileSpeaker *pThis,Car_tObj *perp)

{
  Speaker *base = &pThis->_base_Speaker;
  DispatchSpeaker *dispatch;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  Speaker_SetCar(base,perp);
  Speaker_FindLocation(base,perp);
  MobileSpeaker_SetSpeed(pThis,perp);
  SPCHNFS_C_D_PERP_SIGHTED(&pThis->fVoice,&base->fColour,base->fCar,&base->fDistance,
                           &base->fPosition,base->fLocation,&base->fPerpName);
  SPCH_PlaySpeech();
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  dispatch->_base_Speaker.fSub = base;
}

/* ---- Engage__Q26Speech13MobileSpeakerP8Car_tObj  [SPEECH.CPP:2331-2450] SLD-VERIFIED ---- */
void MobileSpeaker_Engage(MobileSpeaker *pThis,Car_tObj *perp)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *previous;
  Speaker *cursor;
  Speaker *dispatchSub;
  Speaker *savedDispatchSub;
  DispatchSpeaker *dispatch;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *activePerp;
  Car_tObj *car;
  bool insertAtHead = false;

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  base->fHavePerp = 1;
  entry = &(*base->_vf)[27];
  activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);

  if (perp == activePerp) {
    if (Speech_fgSpeech->fMultiplePerps != 0) {
      return;
    }
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    entry = &(*dispatch->_base_Speaker._vf)[21];
    if (NFS4_VCALL0(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta) >= 0x160) {
      return;
    }
    Speaker_SetCar(base,activePerp);
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    entry = &(*base->_vf)[27];
    activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    Speaker_FindLocation(base,activePerp);
    SPCHNFS_C_C_PERP_REAQUIRED(&pThis->fVoice,&base->fColour,base->fCar,
                               &base->fPosition,base->fLocation,&base->fDistance);
    goto MobileEngage_playAndReturn;
  }

  pThis->fPerp = perp;
  entry = &(*base->_vf)[27];
  activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_SetCar(base,activePerp);
  entry = &(*base->_vf)[25];
  car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if ((car->carFlags & 0x200) == 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    previous = &dispatch->_base_Speaker;
    cursor = previous->fSub;
    while ((cursor != 0) && (cursor != base)) {
      previous = cursor;
      cursor = cursor->fSub;
    }
    if (cursor == base) {
      previous->fSub = base->fSub;
      base->fSub = 0;
    }
  }

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  if (dispatch->_base_Speaker.fSub == base) {
    entry = &(*base->_vf)[25];
    car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    if ((car->carFlags & 0x200) == 0) {
      return;
    }
    entry = &(*dispatch->_base_Speaker._vf)[1];
    NFS4_VCALL_P1(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta,perp);
    Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    base->fTo = callSign->fDispatch;
    entry = &(*base->_vf)[27];
    activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    Speaker_FindLocation(base,activePerp);
    SPCHNFS_C_D_ENGAGE_PURS_REP_SPDR_REPLY(&pThis->fVoice,base->fTo,&base->fColour,
                                           base->fCar,&base->fDistance,&base->fPosition,
                                           base->fLocation,&base->fConfirm);
    goto MobileEngage_playAndReturn;
  }

  entry = &(*base->_vf)[20];
  if (NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta) != 0) {
    entry = &(*base->_vf)[27];
    activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    dispatchSub = dispatch->_base_Speaker.fSub;
    if (((activePerp->carFlags & 4) != 0) && (dispatchSub != 0)) {
      entry = &(*dispatchSub->_vf)[25];
      car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)dispatchSub + entry->delta);
      insertAtHead = (car->carFlags & 0x40) == 0;
    }
  }

  if (insertAtHead) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    base->fSub = dispatch->_base_Speaker.fSub;
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    dispatch->_base_Speaker.fSub = base;
    if (base->fBlockade.flags != 0) {
      return;
    }
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    base->fTo = callSign->fAllUnits;
    SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    SPCHNFS_S_C_SUPER_COP_ARRIVAL(&pThis->fVoice);
    goto MobileEngage_playAndReturn;
  }

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  previous = &dispatch->_base_Speaker;
  dispatchSub = previous->fSub;
  if (dispatchSub != 0) {
    entry = &(*dispatchSub->_vf)[27];
    car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)dispatchSub + entry->delta);
    if (car != 0) {
      entry = &(*dispatchSub->_vf)[27];
      car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)dispatchSub + entry->delta);
      if ((car->carFlags & 4) == 0) {
        entry = &(*base->_vf)[27];
        activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
        insertAtHead = (activePerp->carFlags & 4) != 0;
      }
    }
  }
  if (insertAtHead) {
    base->fSub = previous->fSub;
    previous->fSub = base;
  }
  else {
    while (previous->fSub != 0) {
      previous = previous->fSub;
    }
    previous->fSub = base;
  }
  if (base->fBlockade.flags != 0) {
    return;
  }

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  entry = &(*dispatch->_base_Speaker._vf)[18];
  if (NFS4_VCALL_PTR_P1(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta,perp) != 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    entry = &(*dispatch->_base_Speaker._vf)[21];
    if (NFS4_VCALL0(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta) < 0x180) {
      return;
    }
  }

  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  entry = &(*base->_vf)[27];
  activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_FindLocation(base,activePerp);
  entry = &(*base->_vf)[27];
  activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  MobileSpeaker_SetSpeed(pThis,activePerp);

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  entry = &(*dispatch->_base_Speaker._vf)[18];
  if (NFS4_VCALL_PTR_P1(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta,activePerp) == 0) {
    SPCHNFS_C_D_ENGAGE_PURS_REP_SPDR(&pThis->fVoice,&base->fColour,base->fCar,
                                     &base->fPosition,base->fLocation,&base->fDistance,
                                     pThis->fSpeed,&pThis->fSpeedType,&base->fPerpName);
  }
  else {
    SPCHNFS_C_D_PERP_SIGHTED(&pThis->fVoice,&base->fColour,base->fCar,
                             &base->fDistance,&base->fPosition,base->fLocation,
                             &base->fPerpName);
  }
  SPCH_PlaySpeech();

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  savedDispatchSub = dispatch->_base_Speaker.fSub;
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  dispatch->_base_Speaker.fSub = base;
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  entry = &(*base->_vf)[27];
  activePerp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  entry = &(*dispatch->_base_Speaker._vf)[1];
  NFS4_VCALL_P1(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta,activePerp);
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  dispatch->_base_Speaker.fSub = savedDispatchSub; /* PORTABILITY-REVIEWED: SPEECH-DISPATCH-SAVE-RESTORE-01 */
  return;

MobileEngage_playAndReturn:
  SPCH_PlaySpeech();
}

/* ---- Lose__Q26Speech13MobileSpeaker  [SPEECH.CPP:2463-2538] SLD-VERIFIED ---- */
void MobileSpeaker_Lose(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  DispatchSpeaker *dispatch;
  Speaker *leader = 0;
  Speaker *savedDispatchSub;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *perp;
  Car_tObj *car;
  int unit;

  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if (perp == 0) {
    return;
  }

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  leader = dispatch->_base_Speaker.fSub;
  if (!((leader != 0) && (leader->fSub == base) &&
        (base->fBlockade.flags == 0) && (base->fArrest.flags == 0))) {
    leader = 0;
  }

  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if (leader != 0) {
    entry = &(*leader->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)leader + entry->delta);
    base->fTo = callSign->fMobile[unit];
  }
  else {
    base->fTo = callSign->fDispatch;
  }

  if (base->fArrest.flags == 0) {
    if ((base->fBlockade.flags == 0) && (leader == 0)) {
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      entry = &(*dispatch->_base_Speaker._vf)[21];
      if (NFS4_VCALL0(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta) > 0x160) {
        return;
      }
    }
  }
  else {
    SPCHNFS_C_P_FALSE_ARREST_BULLHORN(&pThis->fVoice);
    SPCH_PlaySpeech();
  }

  SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_SetCar(base,perp);
  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_FindLocation(base,perp);

  if (base->fArrest.flags == 0) {
    entry = &(*base->_vf)[25];
    car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    if ((car->carFlags & 0x200) == 0) {
      if (base->fBlockade.flags == 1) {
        SPCHNFS_C_D_SPBLT_FAILED(&pThis->fVoice,&base->fColour,base->fCar);
      }
      else if (base->fBlockade.flags == 2) {
        SPCHNFS_C_D_RDBLK_FAILED(&pThis->fVoice,&base->fColour,base->fCar);
      }
      else if (leader == 0) {
        SPCHNFS_C_D_PERP_LOST(&pThis->fVoice,&base->fColour,base->fCar,&base->fPosition,
                              base->fLocation,&base->fDistance,&base->fPerpName);
      }
      else {
        SPCHNFS_C_C_IDLE_WINGMAN_DISAPPEARS(&pThis->fVoice);
      }
    }
    else {
      SPCHNFS_C_D_ENDGAME(&pThis->fVoice);
    }
  }
  else {
    SPCHNFS_C_D_DURING_FALSE_ARREST(&pThis->fVoice,&base->fPerpName);
  }
  SPCH_PlaySpeech();
  base->fBlockade.flags = 0;
  base->fArrest.flags = 0;
  base->fUpdate.flags = 0;

  if (leader == 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    savedDispatchSub = dispatch->_base_Speaker.fSub;
    dispatch->_base_Speaker.fSub = base;
    entry = &(*dispatch->_base_Speaker._vf)[14];
    NFS4_VCALL0(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta);
    dispatch->_base_Speaker.fSub = savedDispatchSub; /* PORTABILITY-REVIEWED: SPEECH-DISPATCH-SAVE-RESTORE-01 */
  }
}

/* ---- Accident__Q26Speech13MobileSpeakeri  [SPEECH.CPP:2544-2548] SLD-VERIFIED ---- */
void MobileSpeaker_Accident(MobileSpeaker *pThis,int slice)

{
  return;
}

/* ---- Catch__Q26Speech13MobileSpeakeri  [SPEECH.CPP:2554-2621] SLD-VERIFIED ---- */
void MobileSpeaker_Catch(MobileSpeaker *pThis,int ticket)

{
  Speaker *base = &pThis->_base_Speaker;
  DispatchSpeaker *dispatch;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *perp;
  u_long ambulanceFlags;

  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if (perp == 0) {
    return;
  }

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if (perp->N.orientationToGround.y < 0) {
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    entry = &(*base->_vf)[27];
    perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    Speaker_FindLocation(base,perp);
    SPCHNFS_C_D_PERP_CRASH_ROLL(&pThis->fVoice,&base->fPosition,base->fLocation,
                                &base->fDistance,&base->fPerpName);
    SPCH_PlaySpeech();
    ambulanceFlags = 4;
    goto MobileCatch_requestEms;
  }

  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  if (perp->collision.smoking == 0) {
    base->fArrest.flags = ticket;
    if (ticket == 1) {
      SPCHNFS_C_P_ARRESTED(&pThis->fVoice,&base->fArrest);
    }
    else if (ticket == 2) {
      SPCHNFS_C_P_WARNING(&pThis->fVoice,&base->fArrest);
    }
    else {
      SPCHNFS_C_P_TICKET(&pThis->fVoice,&base->fArrest);
    }
    SPCH_PlaySpeech();
    if (ticket == 1) {
      Speech_SetDelayedStatus(Speech_fgSpeech,base,0x60);
    }
    goto MobileCatch_dispatchCallback;
  }

  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_SetCar(base,perp);
  entry = &(*base->_vf)[27];
  perp = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_FindLocation(base,perp);
  SPCHNFS_C_D_PERP_CRASH_GEN(&pThis->fVoice,&base->fPosition,base->fLocation,
                             &base->fColour,base->fCar,&base->fDistance,&base->fPerpName);
  SPCH_PlaySpeech();
  ambulanceFlags = 0x20;

MobileCatch_requestEms:
  base->fAmbulance.flags = ambulanceFlags;
  SPCHNFS_C_D_REQUEST_EMS(&pThis->fVoice,&base->fAmbulance);
  SPCH_PlaySpeech();

MobileCatch_dispatchCallback:
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  entry = &(*dispatch->_base_Speaker._vf)[19];
  NFS4_VCALL_P1(entry->pfn,(u_char *)&dispatch->_base_Speaker + entry->delta,pThis->fPerp);
}

/* ---- RoadBlock__Q26Speech13MobileSpeaker  [SPEECH.CPP:2627-2648] SLD-VERIFIED ---- */
void MobileSpeaker_RoadBlock(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  DispatchSpeaker *dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  Speaker *sub = dispatch->_base_Speaker.fSub;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;

  if ((sub != 0) && (sub != base)) {
    entry = &(*sub->_vf)[10];
    NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
  }
  else {
    Speaker_Promote(base);
    if (Speech_fgSpeech->fMultiplePerps == 0) {
      Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      SPCHNFS_C_D_REQ_RDBLK(&pThis->fVoice);
      SPCH_PlaySpeech();
    }
    base->fBlockade.flags = 2;
  }
}

/* ---- SpikeBelt__Q26Speech13MobileSpeaker  [SPEECH.CPP:2656-2677] SLD-VERIFIED ---- */
void MobileSpeaker_SpikeBelt(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  DispatchSpeaker *dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  Speaker *sub = dispatch->_base_Speaker.fSub;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;

  if ((sub != 0) && (sub != base)) {
    entry = &(*sub->_vf)[11];
    NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
  }
  else {
    Speaker_Promote(base);
    if (Speech_fgSpeech->fMultiplePerps == 0) {
      Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
      entry = &(*base->_vf)[30];
      callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      SPCHNFS_C_D_REQ_SPBLT(&pThis->fVoice);
      SPCH_PlaySpeech();
    }
    base->fBlockade.flags = 1;
  }
}

/* ---- Backup__Q26Speech13MobileSpeaker  [SPEECH.CPP:2685-2705] SLD-VERIFIED ---- */
void MobileSpeaker_Backup(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *car;

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  entry = &(*base->_vf)[27];
  car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_SetCar(base,car);
  entry = &(*base->_vf)[25];
  car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_FindLocation(base,car);
  SPCHNFS_C_D_REQUEST_BKUP(&pThis->fVoice,&base->fColour,base->fCar,&base->fPosition,
                           base->fLocation,&base->fDistance);
  SPCH_PlaySpeech();
  base->fBlockade.flags = 0;
}

/* ---- Roger__Q26Speech13MobileSpeaker  [SPEECH.CPP:2711-2733] SLD-VERIFIED ---- */
void MobileSpeaker_Roger(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  Speaker *sub = base->fSub;
  Speaker *statusSub = 0;
  DispatchSpeaker *dispatch;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *car;
  int unit;

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  if (sub != 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    entry = &(*dispatch->_base_Speaker._vf)[22];
    statusSub = (Speaker *)NFS4_VCALL_PTR0(entry->pfn,
                                           (u_char *)&dispatch->_base_Speaker + entry->delta);
  }
  if ((sub != 0) && (statusSub == sub)) {
    SPCH_PlaySpeech();
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    entry = &(*sub->_vf)[17];
    unit = NFS4_VCALL0(entry->pfn,(u_char *)sub + entry->delta);
    base->fTo = callSign->fMobile[unit];
    SPCHNFS_C_A_CONFIRM(&pThis->fVoice,base->fTo,&base->fConfirm);
    SPCH_PlaySpeech();
    entry = &(*base->_vf)[27];
    car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    Speaker_SetCar(base,car);
    SPCHNFS_C_C_IN_PURS_NEAR_PERP(&pThis->fVoice,&base->fColour,base->fCar);
  }
  else {
    entry = &(*base->_vf)[30];
    callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_CONFIRM(&pThis->fVoice,base->fTo,&base->fConfirm);
  }
  SPCH_PlaySpeech();
}

/* ---- Bullhorn__Q26Speech13MobileSpeaker  [SPEECH.CPP:2741-2748] SLD-VERIFIED ---- */
void MobileSpeaker_Bullhorn(MobileSpeaker *pThis)

{
  Car_tObj *carObj;
  SPCHNFSType_VOICE *VOICE;
  int reg_a1;
  int reg_a2;
  int reg_a3;
  
  VOICE = &pThis->fVoice;
  *(Car_tObj **)(((int)Speech_fgSpeech) + 0x38c) = pThis->fCarObj;
  SPCHNFS_C_P_BULLHORN_SPEECH(VOICE);
  SPCH_PlaySpeech((int)(intptr)VOICE,reg_a1,reg_a2,reg_a3);
  return;
}

/* ---- Purge__Q26Speech13MobileSpeaker  [SPEECH.CPP:2754-2839] SLD-VERIFIED ---- */
void MobileSpeaker_Purge(MobileSpeaker *pThis)

{
  bool bVar1;
  __vtbl_ptr_type (*pa_Var2) [31];
  int iVar3;
  MobileSpeaker *pMVar4;
  MobileSpeaker *pMVar5;
  Speaker *Chain;
  
  if (pThis->fCarObj == (Car_tObj *)0x0) {
    return;
  }
  pa_Var2 = (pThis->_base_Speaker)._vf;
  iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x19].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x19].delta);
  if ((*(u_int *)(iVar3 + 0x260) & 0x200) == 0) {
    pThis->fCarObj = (Car_tObj *)0x0;
    iVar3 = Speech_Dispatch();
    pMVar4 = (MobileSpeaker *)
             (**(int (**)(...))(*(int *)(iVar3 + 0x4c) + 0xb4))
                       (iVar3 + *(short *)(*(int *)(iVar3 + 0x4c) + 0xb0));
    if (pMVar4 == pThis) {
      iVar3 = Speech_Dispatch();
      (**(int (**)(...))(*(int *)(iVar3 + 0x4c) + 0xbc))
                (iVar3 + *(short *)(*(int *)(iVar3 + 0x4c) + 0xb8));
    }
    pMVar4 = (MobileSpeaker *)Speech_Dispatch();
    do {
      pMVar5 = (MobileSpeaker *)(pMVar4->_base_Speaker).fSub;
      if (pMVar5 == pThis) {
        (pMVar4->_base_Speaker).fSub = (pThis->_base_Speaker).fSub;
        return;
      }
      pMVar4 = pMVar5;
    } while (pMVar5 != (MobileSpeaker *)0x0);
    return;
  }
  CopSpeak_Flush();
  if (CopSpeak_gSpchHandle != -1) {
    if (stackSpeedUpEnbabledFlag == 0) {
      SNDstop(CopSpeak_gSpchHandle);
    }
    else {
      gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 0;
      SNDstop(CopSpeak_gSpchHandle);
      gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 1;
    }
  }
  pa_Var2 = (pThis->_base_Speaker)._vf;
  bVar1 = false;
  iVar3 = NFS4_VCALL_AUTO((*pa_Var2)[0x1b].pfn, (int)&(pThis->_base_Speaker).fPosition.flags + (int)(*pa_Var2)[0x1b].delta);
  if (iVar3 != 0) {
    iVar3 = AudioMus_Threshold();
    bVar1 = iVar3 != 0;
  }
  if (bVar1) {
    if (stackSpeedUpEnbabledFlag != 0) {
      gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 0;
      AudioMus_StopSong(500);
      AudioMus_PlaySong((char *)0x0);
      gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 1;
      (pThis->_base_Speaker).fBlockade.flags = 0;
      goto Purge_resetSpeakerFields;
    }
    AudioMus_StopSong(500);
    AudioMus_PlaySong((char *)0x0);
  }
  (pThis->_base_Speaker).fBlockade.flags = 0;
Purge_resetSpeakerFields:
  (pThis->_base_Speaker).fArrest.flags = 0;
  (pThis->_base_Speaker).fUpdate.flags = 0;
  pThis->fPerp = (Car_tObj *)0x0;
  (pThis->_base_Speaker).fSub = (Speaker *)0x0;
  return;
}

/* ---- ReportBlockade__Q26Speech13MobileSpeaker  [SPEECH.CPP:2843-2861] SLD-VERIFIED ---- */
void MobileSpeaker_ReportBlockade(MobileSpeaker *pThis)

{
  Speaker *base = &pThis->_base_Speaker;
  __vtbl_ptr_type *entry;
  CallSignBank *callSign;
  Car_tObj *car;

  Speech_fgSpeech->fSpeakerCar = pThis->fCarObj;
  entry = &(*base->_vf)[30];
  callSign = (CallSignBank *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  base->fTo = callSign->fDispatch;
  entry = &(*base->_vf)[25];
  car = (Car_tObj *)NFS4_VCALL_PTR0(entry->pfn,(u_char *)base + entry->delta);
  Speaker_FindLocation(base,car);
  base->fSpikeSide.flags = 4;
  if (base->fBlockade.flags == 2) {
    SPCHNFS_C_A_INTRO(&pThis->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    SPCHNFS_W_D_RDBLK_PLC(&pThis->fVoice,&base->fPosition,base->fLocation,&base->fDistance);
  }
  else {
    SPCHNFS_W_D_SPBLT_PLC(&pThis->fVoice,&base->fPosition,&base->fSpikeSide,
                          base->fFrom,base->fLocation,&base->fDistance);
  }
  SPCH_PlaySpeech();
}

/* ---- Perp__Q26Speech13MobileSpeaker  [SPEECH.CPP:147-147] SLD-VERIFIED ---- */
Car_tObj * MobileSpeaker_Perp(MobileSpeaker *pThis)

{
  return pThis->fPerp;
}

/* ---- Unit__Q26Speech13MobileSpeaker  [SPEECH.CPP:134-135] SLD-VERIFIED ---- */
int MobileSpeaker_Unit(MobileSpeaker *pThis)

{
  return pThis->fUnit;
}

/* ---- CallSign__Q26Speech13MobileSpeaker  [SPEECH.CPP:130-135] SLD-FLAG:NONMONO ---- */
CallSignBank * MobileSpeaker_CallSign(MobileSpeaker *pThis)

{
  return (CallSignBank *)(((int)Speech_fgSpeech) + 0x2d8);
}

/* ---- FindClosestLocationTo__Q26Speech13MobileSpeakeri  [SPEECH.CPP:126-131] SLD-FLAG:NONMONO ---- */
LocationBank * MobileSpeaker_FindClosestLocationTo(MobileSpeaker *pThis,int slice)

{
  LocationBank *pLVar1;
  int reg_a1;
  
  pLVar1 = (LocationBank *)Speech_FindClosestLocationTo((Speech *)((int)Speech_fgSpeech),(LocationBank *)(((int)Speech_fgSpeech) + 0xd8),reg_a1);
  return pLVar1;
}

/* ---- GetCarBank__Q26Speech13MobileSpeakeri  [SPEECH.CPP:122-127] SLD-FLAG:NONMONO ---- */
CarBank * MobileSpeaker_GetCarBank(MobileSpeaker *pThis,int carIndex)

{
  return (CarBank *)(((int)Speech_fgSpeech) + carIndex * 0xc);
}

/* ---- CarObj__Q26Speech13MobileSpeaker  [SPEECH.CPP:114-114] SLD-VERIFIED ---- */
Car_tObj * MobileSpeaker_CarObj(MobileSpeaker *pThis)

{
  return pThis->fCarObj;
}

/* ---- IsSuper__Q26Speech13MobileSpeaker  [SPEECH.CPP:106-106] SLD-VERIFIED ---- */
void * MobileSpeaker_IsSuper(MobileSpeaker *pThis)

{
  return (void *)((u_int)pThis->fCarObj->carFlags >> 6 & 1);
}

/* ---- CallSign__Q26Speech15DispatchSpeaker  [SPEECH.CPP:73-74] SLD-VERIFIED ---- */
CallSignBank * DispatchSpeaker_CallSign(DispatchSpeaker *pThis)

{
  return (CallSignBank *)(((int)Speech_fgSpeech) + 0x31c);
}

/* ---- FindClosestLocationTo__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:69-74] SLD-FLAG:NONMONO ---- */
LocationBank * DispatchSpeaker_FindClosestLocationTo(DispatchSpeaker *pThis,int slice)

{
  LocationBank *pLVar1;
  int reg_a1;
  
  pLVar1 = (LocationBank *)Speech_FindClosestLocationTo((Speech *)((int)Speech_fgSpeech),(LocationBank *)(((int)Speech_fgSpeech) + 0x1d8),reg_a1)
  ;
  return pLVar1;
}

/* ---- GetCarBank__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:65-70] SLD-FLAG:NONMONO ---- */
CarBank * DispatchSpeaker_GetCarBank(DispatchSpeaker *pThis,int carIndex)

{
  return (CarBank *)(((int)Speech_fgSpeech) + carIndex * 0xc + 0x6c);
}

/* ---- PurgeStatusSub__Q26Speech15DispatchSpeaker  [SPEECH.CPP:58-66] SLD-FLAG:NONMONO ---- */
void DispatchSpeaker_PurgeStatusSub(DispatchSpeaker *pThis)

{
  pThis->fStatusSub = (Speaker *)0x0;
  return;
}

/* ---- StatusSub__Q26Speech15DispatchSpeaker  [SPEECH.CPP:57-58] SLD-VERIFIED ---- */
Speaker * DispatchSpeaker_StatusSub(DispatchSpeaker *pThis)

{
  return pThis->fStatusSub;
}

/* ---- StatusCount__Q26Speech15DispatchSpeaker  [SPEECH.CPP:56-57] SLD-VERIFIED ---- */
int DispatchSpeaker_StatusCount(DispatchSpeaker *pThis)

{
  return pThis->fStatusCount;
}

/* ---- FindClosestLocationTo__Q26Speech7Speakeri  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
LocationBank * Speaker_FindClosestLocationTo(Speaker *pThis,int slice)

{
  return (LocationBank *)0x0;
}

/* ---- GetCarBank__Q26Speech7Speakeri  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
CarBank * Speaker_GetCarBank(Speaker *pThis,int carIndex)

{
  return (CarBank *)0x0;
}

/* ---- Perp__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
Car_tObj * Speaker_Perp(Speaker *pThis)

{
  return (Car_tObj *)0x0;
}

/* ---- ReActivate__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker_ReActivate(Speaker *pThis)

{
  return;
}

/* ---- CarObj__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
Car_tObj * Speaker_CarObj(Speaker *pThis)

{
  return (Car_tObj *)0x0;
}

/* ---- DistToPerp__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
int Speaker_DistToPerp(Speaker *pThis)

{
  return 0x3e80000;
}

/* ---- PurgeStatusSub__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker_PurgeStatusSub(Speaker *pThis)

{
  return;
}

/* ---- StatusSub__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
Speaker * Speaker_StatusSub(Speaker *pThis)

{
  return (Speaker *)0x0;
}

/* ---- StatusCount__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
int Speaker_StatusCount(Speaker *pThis)

{
  return 0;
}

/* ---- IsSuper__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void * Speaker_IsSuper(Speaker *pThis)

{
  return (void *)0x0;
}

/* ---- ClearPerp__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker_ClearPerp(Speaker *pThis,Car_tObj *car)

{
  return;
}

/* ---- KnownPerp__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void * Speaker_KnownPerp(Speaker *pThis,Car_tObj *car)

{
  return (void *)0x0;
}

/* ---- Unit__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
int Speaker_Unit(Speaker *pThis)

{
  return 0;
}

/* ---- Status__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker_Status(Speaker *pThis)

{
  int Voice;
  int numhumancops;
  char *SpeechLanguage;
  int Arrest;
  int banksize;
  int bcount;
  int namelen;
  int bankid;
  char filename [100];
  
  return;
}

/* base Speech::Speaker virtual not separately reconstructed (vtable-only ref, surfaced by #75
 * data-materialization); faithful from nfs4-f.exe @0x80099364 = { jr $ra; addiu $v0,$zero,0 } */
CallSignBank * Speaker_CallSign(Speaker *pThis)   /* @0x80099364  CallSign__Q26Speech7Speaker -> NULL */
{
  return (CallSignBank *)0;
}

/* ---- #75 data-materialization: 3 Speech vtables (nested Speech::<Leaf>, flat <Leaf>_<Method> pfns). ---- */
__vtbl_ptr_type Speaker_vtable[31] = {   /* @0x80055dc4  Speech::Speaker vtable (#75 data-mat; faithful nfs4-f.exe bytes) */
  {0, 0, (int (*)(...))0},                           /* @0x80055dc4  null */
  {0, 0, (int (*)(...))&Speaker_Report},             /* @0x80055dcc  Report__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_Status},             /* @0x80055dd4  Status__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Deny},               /* @0x80055ddc  Deny__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Grant},              /* @0x80055de4  Grant__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Ready},              /* @0x80055dec  Ready__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_Engage},             /* @0x80055df4  Engage__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_Lose},               /* @0x80055dfc  Lose__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Accident},           /* @0x80055e04  Accident__Q26Speech7Speakeri */
  {0, 0, (int (*)(...))&Speaker_Catch},              /* @0x80055e0c  Catch__Q26Speech7Speakeri */
  {0, 0, (int (*)(...))&Speaker_RoadBlock},          /* @0x80055e14  RoadBlock__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_SpikeBelt},          /* @0x80055e1c  SpikeBelt__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Backup},             /* @0x80055e24  Backup__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_ReportBlockade},     /* @0x80055e2c  ReportBlockade__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Roger},              /* @0x80055e34  Roger__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Bullhorn},           /* @0x80055e3c  Bullhorn__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Purge},              /* @0x80055e44  Purge__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Unit},               /* @0x80055e4c  Unit__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_KnownPerp},          /* @0x80055e54  KnownPerp__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_ClearPerp},          /* @0x80055e5c  ClearPerp__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_IsSuper},            /* @0x80055e64  IsSuper__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_StatusCount},        /* @0x80055e6c  StatusCount__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_StatusSub},          /* @0x80055e74  StatusSub__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_PurgeStatusSub},     /* @0x80055e7c  PurgeStatusSub__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_DistToPerp},         /* @0x80055e84  DistToPerp__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_CarObj},             /* @0x80055e8c  CarObj__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_ReActivate},         /* @0x80055e94  ReActivate__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Perp},               /* @0x80055e9c  Perp__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_GetCarBank},         /* @0x80055ea4  GetCarBank__Q26Speech7Speakeri */
  {0, 0, (int (*)(...))&Speaker_FindClosestLocationTo}, /* @0x80055eac  FindClosestLocationTo__Q26Speech7Speakeri */
  {0, 0, (int (*)(...))&Speaker_CallSign},           /* @0x80055eb4  CallSign__Q26Speech7Speaker */
};
__vtbl_ptr_type MobileSpeaker_vtable[31] = {   /* @0x80055bd4  Speech::MobileSpeaker vtable (#75 data-mat; faithful nfs4-f.exe bytes) */
  {0, 0, (int (*)(...))0},                           /* @0x80055bd4  null */
  {0, 0, (int (*)(...))&MobileSpeaker_Report},       /* @0x80055bdc  Report__Q26Speech13MobileSpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&MobileSpeaker_Status},       /* @0x80055be4  Status__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&Speaker_Deny},               /* @0x80055bec  Deny__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Grant},              /* @0x80055bf4  Grant__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Ready},              /* @0x80055bfc  Ready__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&MobileSpeaker_Engage},       /* @0x80055c04  Engage__Q26Speech13MobileSpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&MobileSpeaker_Lose},         /* @0x80055c0c  Lose__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Accident},     /* @0x80055c14  Accident__Q26Speech13MobileSpeakeri */
  {0, 0, (int (*)(...))&MobileSpeaker_Catch},        /* @0x80055c1c  Catch__Q26Speech13MobileSpeakeri */
  {0, 0, (int (*)(...))&MobileSpeaker_RoadBlock},    /* @0x80055c24  RoadBlock__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_SpikeBelt},    /* @0x80055c2c  SpikeBelt__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Backup},       /* @0x80055c34  Backup__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_ReportBlockade}, /* @0x80055c3c  ReportBlockade__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Roger},        /* @0x80055c44  Roger__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Bullhorn},     /* @0x80055c4c  Bullhorn__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Purge},        /* @0x80055c54  Purge__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Unit},         /* @0x80055c5c  Unit__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&Speaker_KnownPerp},          /* @0x80055c64  KnownPerp__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_ClearPerp},          /* @0x80055c6c  ClearPerp__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&MobileSpeaker_IsSuper},      /* @0x80055c74  IsSuper__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&Speaker_StatusCount},        /* @0x80055c7c  StatusCount__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_StatusSub},          /* @0x80055c84  StatusSub__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_PurgeStatusSub},     /* @0x80055c8c  PurgeStatusSub__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&MobileSpeaker_DistToPerp},   /* @0x80055c94  DistToPerp__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_CarObj},       /* @0x80055c9c  CarObj__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_ReActivate},   /* @0x80055ca4  ReActivate__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_Perp},         /* @0x80055cac  Perp__Q26Speech13MobileSpeaker */
  {0, 0, (int (*)(...))&MobileSpeaker_GetCarBank},   /* @0x80055cb4  GetCarBank__Q26Speech13MobileSpeakeri */
  {0, 0, (int (*)(...))&MobileSpeaker_FindClosestLocationTo}, /* @0x80055cbc  FindClosestLocationTo__Q26Speech13MobileSpeakeri */
  {0, 0, (int (*)(...))&MobileSpeaker_CallSign},     /* @0x80055cc4  CallSign__Q26Speech13MobileSpeaker */
};
__vtbl_ptr_type DispatchSpeaker_vtable[31] = {   /* @0x80055ccc  Speech::DispatchSpeaker vtable (#75 data-mat; faithful nfs4-f.exe bytes) */
  {0, 0, (int (*)(...))0},                           /* @0x80055ccc  null */
  {0, 0, (int (*)(...))&DispatchSpeaker_Report},     /* @0x80055cd4  Report__Q26Speech15DispatchSpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&DispatchSpeaker_Status},     /* @0x80055cdc  Status__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_Deny},       /* @0x80055ce4  Deny__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_Grant},      /* @0x80055cec  Grant__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_Ready},      /* @0x80055cf4  Ready__Q26Speech15DispatchSpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_Engage},             /* @0x80055cfc  Engage__Q26Speech7SpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_Lose},               /* @0x80055d04  Lose__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_Accident},   /* @0x80055d0c  Accident__Q26Speech15DispatchSpeakeri */
  {0, 0, (int (*)(...))&Speaker_Catch},              /* @0x80055d14  Catch__Q26Speech7Speakeri */
  {0, 0, (int (*)(...))&Speaker_RoadBlock},          /* @0x80055d1c  RoadBlock__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_SpikeBelt},          /* @0x80055d24  SpikeBelt__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Backup},             /* @0x80055d2c  Backup__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_ReportBlockade},     /* @0x80055d34  ReportBlockade__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_Roger},      /* @0x80055d3c  Roger__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&Speaker_Bullhorn},           /* @0x80055d44  Bullhorn__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Purge},              /* @0x80055d4c  Purge__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Unit},               /* @0x80055d54  Unit__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_KnownPerp},  /* @0x80055d5c  KnownPerp__Q26Speech15DispatchSpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&DispatchSpeaker_ClearPerp},  /* @0x80055d64  ClearPerp__Q26Speech15DispatchSpeakerP8Car_tObj */
  {0, 0, (int (*)(...))&Speaker_IsSuper},            /* @0x80055d6c  IsSuper__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_StatusCount}, /* @0x80055d74  StatusCount__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_StatusSub},  /* @0x80055d7c  StatusSub__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_PurgeStatusSub}, /* @0x80055d84  PurgeStatusSub__Q26Speech15DispatchSpeaker */
  {0, 0, (int (*)(...))&Speaker_DistToPerp},         /* @0x80055d8c  DistToPerp__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_CarObj},             /* @0x80055d94  CarObj__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_ReActivate},         /* @0x80055d9c  ReActivate__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&Speaker_Perp},               /* @0x80055da4  Perp__Q26Speech7Speaker */
  {0, 0, (int (*)(...))&DispatchSpeaker_GetCarBank}, /* @0x80055dac  GetCarBank__Q26Speech15DispatchSpeakeri */
  {0, 0, (int (*)(...))&DispatchSpeaker_FindClosestLocationTo}, /* @0x80055db4  FindClosestLocationTo__Q26Speech15DispatchSpeakeri */
  {0, 0, (int (*)(...))&DispatchSpeaker_CallSign},   /* @0x80055dbc  CallSign__Q26Speech15DispatchSpeaker */
};

/* end of speech.cpp */
