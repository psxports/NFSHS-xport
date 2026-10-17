/* Police speech engine with native Speaker inheritance and virtual dispatch */
#include "../../nfs4_types.h"
#include "speech_externs.h"
#include "../../mips_semantics.h"

/* Native construction mirrors the original inlined base/derived initialization */
Speaker::Speaker() : fSub(0) {}
MobileSpeaker::MobileSpeaker() : fCarObj(0) {}
DispatchSpeaker::DispatchSpeaker() {}

/* ---- speech.obj OWNED globals (EXT; SYM Globals.jsonl tu=Speech.obj, @0x80111a44+) ---- */
Speech_tCarDescription Speech_gCarDescription[15] = {
    {(char *)"BMWZ", (char *)"bmwz3.", (char *)"bmw.", (char *)"z3."},
    {(char *)"HSVT", (char *)"sedan.", (char *)"sedan.", (char *)"sedan."},
    {(char *)"FORD", (char *)"sedan.", (char *)"sedan.", (char *)"sedan."},
    {(char *)"CMRO", (char *)"chvcam.", (char *)"chevro.", (char *)"cam."},
    {(char *)"TRAM", (char *)"pont.", (char *)"pont.", (char *)"pont."},
    {(char *)"ADB7", (char *)"aston.", (char *)"aston.", (char *)"aston."},
    {(char *)"JXKR", (char *)"jag.", (char *)"jag.", (char *)"jag."},
    {(char *)"BMWM", (char *)"bmwm5.", (char *)"bmw.", (char *)"m5."},
    {(char *)"CORV", (char *)"chvcor.", (char *)"chevro.", (char *)"corv."},
    {(char *)"P993", (char *)"por911.", (char *)"porsc.", (char *)"porsc."},
    {(char *)"DIAB", (char *)"lamdia.", (char *)"lamb.", (char *)"dia."},
    {(char *)"MCF1", (char *)"mclar.", (char *)"mclar.", (char *)"mclar."},
    {(char *)"X993", (char *)"por911.", (char *)"porsc.", (char *)"porsc."},
    {(char *)"XCF1", (char *)"chvcor.", (char *)"chevro.", (char *)"corv."},
    {0, (char *)"sport.", (char *)"sport.", (char *)"sport."}
};
Speech_tLocationDescription Speech_gLocationDescription00[13] = {
    {(char *)"cab.", 45, 56},
    {(char *)"cab.", 70, 76},
    {(char *)"baov.", 188, 191},
    {(char *)"tun.", 250, 260},
    {(char *)"scrv.", 304, 340},
    {(char *)"twr.", 480, 483},
    {(char *)"brg.", 588, 600},
    {(char *)"frm.", 660, 666},
    {(char *)"tun.", 690, 699},
    {(char *)"pike.", 794, 847},
    {(char *)"ltun.", 855, 910},
    {(char *)"icec.", 911, 950},
    {0, 0, 0}
};
Speech_tLocationDescription Speech_gLocationDescription02[14] = {
    {(char *)"mar.", 1061, 20},
    {(char *)"bay.", 110, 130},
    {(char *)"rarc.", 185, 188},
    {(char *)"scrv.", 236, 260},
    {(char *)"lth.", 305, 318},
    {(char *)"ruin.", 456, 470},
    {(char *)"spfl.", 616, 618},
    {(char *)"brg.", 632, 638},
    {(char *)"tbrg.", 639, 656},
    {(char *)"brg.", 657, 662},
    {(char *)"ltun.", 806, 839},
    {(char *)"tun.", 959, 975},
    {(char *)"bgdr.", 990, 1025},
    {0, 0, 0}
};
Speech_tLocationDescription Speech_gLocationDescription03[13] = {
    {(char *)"over.", 57, 59},
    {(char *)"over.", 96, 99},
    {(char *)"over.", 139, 142},
    {(char *)"tun.", 156, 165},
    {(char *)"fld.", 222, 260},
    {(char *)"brg.", 264, 274},
    {(char *)"stun.", 365, 416},
    {(char *)"htou.", 545, 551},
    {(char *)"rarc.", 661, 662},
    {(char *)"ruin.", 679, 705},
    {(char *)"tun.", 869, 877},
    {(char *)"ogt.", 914, 929},
    {0, 0, 0}
};
Speech_tLocationDescription Speech_gLocationDescription04[9] = {
    {(char *)"trnx.", 1, 2},
    {(char *)"lsp.", 94, 96},
    {(char *)"cab.", 162, 163},
    {(char *)"hsv.", 170, 300},
    {(char *)"pent.", 305, 309},
    {(char *)"tun.", 465, 474},
    {(char *)"brg.", 575, 593},
    {(char *)"ltun.", 693, 709},
    {0, 0, 0}
};
Speech_tLocationDescription Speech_gLocationDescription05[14] = {
    {(char *)"ogt.", 4, 8},
    {(char *)"wfrm.", 35, 109},
    {(char *)"tun.", 240, 250},
    {(char *)"ruin.", 251, 325},
    {(char *)"tun.", 326, 338},
    {(char *)"fld.", 366, 452},
    {(char *)"owel.", 569, 572},
    {(char *)"over.", 681, 682},
    {(char *)"toll.", 711, 713},
    {(char *)"toll.", 741, 743},
    {(char *)"obwm.", 875, 889},
    {(char *)"vill.", 890, 925},
    {(char *)"over.", 1066, 1069},
    {0, 0, 0}
};
Speech_tLocationDescription Speech_gLocationDescription06[11] = {
    {(char *)"fld.", 17, 45},
    {(char *)"omus.", 118, 120},
    {(char *)"kngm.", 265, 275},
    {(char *)"vill.", 330, 398},
    {(char *)"scrv.", 570, 627},
    {(char *)"stun.", 637, 657},
    {(char *)"hpin.", 705, 742},
    {(char *)"over.", 760, 765},
    {(char *)"arch.", 818, 821},
    {(char *)"ltun.", 940, 1017},
    {0, 0, 0}
};
Speech_tLocationDescription Speech_gLocationDescription07[11] = {
    {(char *)"scrv.", 32, 74},
    {(char *)"over.", 116, 158},
    {(char *)"ltun.", 249, 301},
    {(char *)"over.", 330, 334},
    {(char *)"medi.", 348, 426},
    {(char *)"frm.", 515, 536},
    {(char *)"farm.", 537, 538},
    {(char *)"frm.", 540, 577},
    {(char *)"vill.", 627, 720},
    {(char *)"tun.", 767, 785},
    {0, 0, 0}
};
Speech_tLocationDescription * Speech_gLocationDescription[11] = {
    Speech_gLocationDescription00,
    Speech_gLocationDescription02,
    Speech_gLocationDescription02,
    Speech_gLocationDescription03,
    Speech_gLocationDescription04,
    Speech_gLocationDescription05,
    Speech_gLocationDescription06,
    Speech_gLocationDescription07,
    Speech_gLocationDescription02,
    Speech_gLocationDescription02,
    Speech_gLocationDescription02
};
Speech_tCallSignDescription Speech_gCallSignDescription[1] = {
    {(char *)"all.",
     {(char *)"dis.", (char *)"cen.", (char *)"cont.", (char *)"hq.", (char *)"cou."},
     {(char *)"20.", (char *)"25.", (char *)"31.", (char *)"37.", (char *)"38.", (char *)"43.", (char *)"45.", (char *)"46.", (char *)"52.", (char *)"217.", (char *)"223.", (char *)"316.", (char *)"332.", (char *)"355.", (char *)"371."}}
};
Speech_tMobileVoiceAttr Speech_gCopAttr[9] = {
    {1, 0},
    {2, 0},
    {4, 0},
    {1, 5},
    {2, 5},
    {4, 5},
    {1, -5},
    {2, -5},
    {4, -5}
};
/* Speech::fgSpeech static-member singleton (active engine instance; $gp+0x838=0x8013cd84) */
extern Speech *_6Speech_fgSpeech;
extern Speaker *_6Speech_fgUndefined;
/* Original data snapshot at 0x8013cd88, including adjacent bank-name strings
   The live Speaker pointer is _6Speech_fgUndefined, not the snapshot's first word */
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

/* Free host callbacks and original static entry points */
void *Speech_AllocateRAM(int numBytes,char *message);
void Speech_PurgeRAM(void *memPtr);
void Speech_HandleRequest(sint32 bank,sint32 localoffset,sint32 size,sint32 event);
void Speech_Reset(void);
int Speech_SubmitRequest(int bank,int localoffset,u_int size);
void Speech_Server(void);
intptr Speech_Dispatch(void);
int Speech_GetVoice(Car_tObj *carObj);
intptr Speech_Mobile(Car_tObj *carObj);

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
void Speech_HandleRequest(sint32 bank,sint32 localoffset,sint32 size,sint32 event)

{
  (void)event;
  Speech_SubmitRequest(bank,localoffset,size);
  return;
}

/* ---- SetCar__Q26Speech11CarBankNamei  [SPEECH.CPP:234-246] SLD-VERIFIED ---- */
void CarBankName::SetCar(int carIndex)

{
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
  this->fFull = pSVar4->full;
  this->fMake = pSVar4->make;
  this->fModel = pSVar4->model;
  return;
}

/* ---- Check__Q26Speech7CarBankPciPQ26Speech11CarBankName  [SPEECH.CPP:257-275] SLD-VERIFIED ---- */
bool CarBank::Check(char *name,uint32 id,CarBankName *bankname)

{
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
    this->fFull = id;
  }
  bVar1 = false;
  if (bankname->fMake != 0) {
    lVar2 = strlen(bankname->fMake);
    iVar3 = strncmp(name,bankname->fMake,lVar2);
    bVar1 = iVar3 == 0;
  }
  if (bVar1) {
    this->fMake = id;
    bVar4 = true;
  }
  bVar1 = false;
  if (bankname->fModel != 0) {
    lVar2 = strlen(bankname->fModel);
    iVar3 = strncmp(name,bankname->fModel,lVar2);
    bVar1 = iVar3 == 0;
  }
  if (bVar1) {
    this->fModel = id;
    bVar4 = true;
  }
  return bVar4;
}

/* ---- CheckCarBank__6SpeechPQ26Speech7CarBankPciPQ26Speech11CarBankName  [SPEECH.CPP:281-295] SLD-VERIFIED ---- */
u_int Speech::CheckCarBank(CarBank *carbank,char *name,u_int id,CarBankName *bankname)
{
  int iVar1;
  int iVar2;
  u_int uVar3;
  
  iVar2 = 0;
  uVar3 = 0;
  if (0 < this->fCarCount) {
    do {
      iVar1 = carbank->Check(name,id,bankname);
      if (iVar1 != 0) {
        uVar3 = 1;
      }
      bankname = bankname + 1;
      iVar2 = iVar2 + 1;
      carbank = carbank + 1;
    } while (iVar2 < this->fCarCount);
  }
  return uVar3;
}

/* ---- SetCar__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:301-373] SLD-VERIFIED ---- */
void Speaker::SetCar(Car_tObj *car)
{
  int *piVar1;
  int iVar2;
  u_int uVar3;
  
  uVar3 = 1 << (car->carInfo->SpeechColour & 0x1fU);
  piVar1 = (int *)(this)->GetCarBank(car->carIndex);
  if (*piVar1 == -1) {
    this->fCar = 0;
    (this->fColour).flags = 0;
  }
  else {
    if (_6Speech_fgSpeech->fMultiplePerps == 0) {
      (this->fColour).flags = uVar3 | 0x78020;
    }
    else {
      (this->fColour).flags = uVar3;
    }
    iVar2 = Speech_Dispatch();
    iVar2 = ([&]() -> int {
      DispatchSpeaker *dispatch = (DispatchSpeaker *)(intptr_t)iVar2;

      return (dispatch)->KnownPerp(car) != nullptr;
    }());
    if (iVar2 == 0) {
      piVar1 = (int *)(this)->GetCarBank(car->carIndex);
      this->fCar = *piVar1;
    }
    else {
      this->fCar = this->GetCarBank(car->carIndex)->fModel;
    }
  }
  return;
}

/* ---- CountLocations__6Speech  [SPEECH.CPP:521-534] SLD-VERIFIED ---- */
void Speech::CountLocations()
{
  char *pcVar1;
  Speech_tLocationDescription *pSVar2;
  
  this->fLocationCount = 0;
  pSVar2 = Speech_gLocationDescription[GameSetup_gData.track];
  if (pSVar2 != (Speech_tLocationDescription *)0x0) {
    pcVar1 = pSVar2->name;
    while (pcVar1 != (char *)0x0) {
      pSVar2 = pSVar2 + 1;
      if (0xf < this->fLocationCount) {
        return;
      }
      this->fLocationCount = this->fLocationCount + 1;
      pcVar1 = pSVar2->name;
    }
  }
  return;
}

/* ---- CheckLocationBank__6SpeechPQ26Speech12LocationBankPci  [SPEECH.CPP:539-561] SLD-VERIFIED ---- */
u_int Speech::CheckLocationBank(LocationBank *locationbank,char *name,int id)
{
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
    for (iVar8 = 0; iVar8 < this->fLocationCount; iVar8 = iVar8 + 1) {
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
int LocationBank::Distance(int slice)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = this->fStartSlice;
  iVar2 = this->fEndSlice;
  if (iVar2 < iVar4) {
    if ((iVar4 <= slice) || (iVar1 = nfs4_mips_subu_s32(slice, iVar2), slice <= iVar2)) {
      return 0;
    }
  }
  else {
    if (iVar4 <= slice) {
      iVar3 = nfs4_mips_subu_s32(slice, iVar2);
      if (slice <= iVar2) {
        return 0;
      }
      iVar1 = nfs4_mips_subu_s32(nfs4_mips_addu_s32(iVar4, gNumSlices), slice);
      goto Distance_clampMin;
    }
    iVar1 = nfs4_mips_subu_s32(nfs4_mips_addu_s32(slice, gNumSlices), iVar2);
  }
  iVar3 = nfs4_mips_subu_s32(iVar4, slice);
Distance_clampMin:
  if (iVar3 < iVar1) {
    iVar1 = iVar3;
  }
  return iVar1;
}

/* ---- FindClosestLocationTo__6SpeechPQ26Speech12LocationBanki  [SPEECH.CPP:594-618] SLD-VERIFIED ---- */
void * Speech::FindClosestLocationTo(LocationBank *bank,int slice)
{
  int iVar1;
  LocationBank *this_00;
  int iVar2;
  int iVar3;
  LocationBank *pLVar4;
  
  if (this->fLocationCount == 0) {
    pLVar4 = (LocationBank *)0x0;
  }
  else {
    pLVar4 = (LocationBank *)0x0;
    iVar3 = 10000;
    for (iVar2 = 0; iVar2 < this->fLocationCount; iVar2 = iVar2 + 1) {
      this_00 = bank + iVar2;
      if ((this_00->fBankId != -1) && (iVar1 = this_00->Distance(slice), iVar1 < iVar3)
         ) {
        iVar3 = iVar1;
        pLVar4 = this_00;
      }
    }
  }
  return pLVar4;
}

/* ---- FindLocation__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:624-788] SLD-VERIFIED ---- */
void Speaker::FindLocation(Car_tObj *car)
{
  int carPos_x;
  int loc_x_diff;
  int best_dist;
  LocationBank *this_00;
  int carPos_z;
  int loc_idx;
  int loc_z_diff;
  int loc_radius;
  int iVar1;
  
  carPos_x = fixedmult(car->currentSpeed,0x50000);
  if (carPos_x / 0x60000 < 0) {
    iVar1 = fixedmult(car->currentSpeed,0x50000);
    if (-1 < nfs4_mips_addu_s32((int)(car->N).simRoadInfo.slice, iVar1 / 0x60000)) goto FindLoc_noWrapCalc;
    iVar1 = fixedmult(car->currentSpeed,0x50000);
    iVar1 = nfs4_mips_addu_s32(nfs4_mips_addu_s32((int)(car->N).simRoadInfo.slice, iVar1 / 0x60000), gNumSlices);
  }
  else {
    loc_x_diff = fixedmult(car->currentSpeed,0x50000);
    if (nfs4_mips_addu_s32((int)(car->N).simRoadInfo.slice, loc_x_diff / 0x60000) < gNumSlices) {
FindLoc_noWrapCalc:
      iVar1 = fixedmult(car->currentSpeed,0x50000);
      iVar1 = nfs4_mips_addu_s32((int)(car->N).simRoadInfo.slice, iVar1 / 0x60000);
    }
    else {
      best_dist = fixedmult(car->currentSpeed,0x50000);
      iVar1 = nfs4_mips_subu_s32(nfs4_mips_addu_s32((int)(car->N).simRoadInfo.slice, best_dist / 0x60000), gNumSlices);
    }
  }

  this_00 = this->FindClosestLocationTo(iVar1);
  if (this_00 == (LocationBank *)0x0) {
    (this->fDistance).flags = 0;
    (this->fPosition).flags = 0;
    this->fLocation = nfs4_mips_bits_to_s32((unsigned int)PsyQ_readRam32(8));
    return;
  }
  carPos_z = this_00->Distance((int)(car->N).simRoadInfo.slice);
  iVar1 = this_00->Distance(iVar1);
  loc_idx = 4;
  if (iVar1 == 0) {
    (this->fDistance).flags = 0;
    goto FindLoc_assignIdx;
  }
  loc_z_diff = __ltdf2(__floatsidf(iVar1), psx_double_value(0x4040AAAAAAAAAAABULL));
  if (loc_z_diff < 0) {
    (this->fDistance).flags = 0;
    if (nfs4_mips_addu_s32(iVar1, 2) < carPos_z) {
      (this->fPosition).flags = 9;
    }
    if (nfs4_mips_addu_s32(iVar1, -2) < carPos_z) {
      (this->fPosition).flags = 8;
      goto FindLoc_assignAndReturn;
    }
FindLoc_setIdxDefault:
    loc_idx = 2;
  }
  else {
    if (GameSetup_gData.measurement == 1) {
      if (iVar1 < 0xa6) {
        (this->fDistance).flags = 8;
        if (nfs4_mips_addu_s32(iVar1, -2) < carPos_z) {
          (this->fPosition).flags = 0x10;
          goto FindLoc_assignAndReturn;
        }
      }
      else {
        loc_radius = 0x10;
        (this->fDistance).flags = 0x10;
        if (nfs4_mips_addu_s32(iVar1, -2) < carPos_z) {
FindLoc_setRadiusReturn:
          (this->fPosition).flags = loc_radius;
          goto FindLoc_assignAndReturn;
        }
      }
      goto FindLoc_setIdxDefault;
    }
    if (iVar1 < 0x86) {
      (this->fDistance).flags = 1;
      if (carPos_z <= nfs4_mips_addu_s32(iVar1, -2)) goto FindLoc_setIdxDefault;
      loc_idx = 0x10;
    }
    else {
      loc_radius = 2;
      if (iVar1 < 0x10c) {
        (this->fDistance).flags = 2;
        if (carPos_z <= nfs4_mips_addu_s32(iVar1, -2)) goto FindLoc_setRadiusReturn;
        loc_idx = 0x10;
      }
      else {
        (this->fDistance).flags = 4;
        loc_idx = 0x10;
        if (carPos_z <= nfs4_mips_addu_s32(iVar1, -2)) goto FindLoc_setIdxDefault;
      }
    }
  }
FindLoc_assignIdx:
  (this->fPosition).flags = loc_idx;
FindLoc_assignAndReturn:
  this->fLocation = this_00->fBankId;
  return;
}

/* ---- CheckCallSignBank__6SpeechPQ26Speech12CallSignBankPci  [SPEECH.CPP:852-884] SLD-VERIFIED ---- */
bool Speech::CheckCallSignBank(CallSignBank *bank,char *name,u_int id)
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
u_int Speech::CheckMultiBank(char *name,u_int id,CarBankName *bn)
{
  int iVar1;
  
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2c4),5);
  if (iVar1 == 0) {
    return (this)->CheckCallSignBank(&this->fCallSignBank.Dispatch,name + 5,id);
  }
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2cc),7);
  if (iVar1 == 0) {
    return (this)->CheckCarBank(this->fCarBank.Dispatch,name + 7,id,bn);
  }
  iVar1 = strncmp(name,"j:location\\",0xb);
  if (iVar1 == 0) {
    return (this)->CheckLocationBank(this->fLocationBank.Dispatch,name + 0xb,id);
  }
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2d4),6);
  if (iVar1 == 0) {
    return (this)->CheckCallSignBank(&this->fCallSignBank.Mobile,name + 6,id);
  }
  iVar1 = strncmp(name,"j:ccars\\",8);
  if (iVar1 == 0) {
    return (this)->CheckCarBank(this->fCarBank.Mobile,name + 8,id,bn);
  }
  iVar1 = strncmp(name,"j:clocaton\\",0xb);
  if (iVar1 == 0) {
    return (this)->CheckLocationBank(this->fLocationBank.Mobile,name + 0xb,id);
  }
  iVar1 = strncmp(name,(char *)(Speech_fgUndefined + 0x2dc),7);
  if (iVar1 == 0) {
    this->fBlpClpBank = id;
  }
  else {
    iVar1 = strncmp(name,"j:silenc.",9);
    if (iVar1 != 0) {
      return 1;
    }
    this->fStaticBank = id;
  }
  return 1;
}

/* ---- CalculateBankSize__6SpeechPcPQ26Speech11CarBankNamePlT3  [SPEECH.CPP:931-984] SLD-VERIFIED ---- */
static u_int Speech_ReadBE32(const u_char *bytes)
{
  return ((u_int)bytes[0] << 24) | ((u_int)bytes[1] << 16) |
         ((u_int)bytes[2] << 8) | (u_int)bytes[3];
}

int Speech::CalculateBankSize(char *header,CarBankName *bn,long *hoffset,long *hsize)
{
  int eventOffset;
  int eventSize;
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
        if ((this)->CheckMultiBank(name,bankCount,bn) != 0) {
          bankCount = bankCount + 1;
          totalSize = totalSize + size;
        }
      }
      entry = (u_char *)end + 1;
    }
  }
  this->fBankCount = bankCount;
  return totalSize;
}

/* ---- LoadBankHeaders__6SpeechPcPQ26Speech11CarBankNamell  [SPEECH.CPP:990-1102] SLD-VERIFIED ---- */
void Speech::LoadBankHeaders(char *header,CarBankName *bn,long hoffset,long hsize)
{
  int eventOffset;
  int eventSize;
  int headerBank = 0;
  int nextDataBank = 0;
  u_char *eventData = (u_char *)(this->fBankOffset + this->fBankCount);
  u_int fileCount = Speech_ReadBE32((u_char *)header + 8);
  u_char *entry = (u_char *)header + 0x10;

  locatebigentry(header,"j:eventdat\\event.dat",0,&eventOffset,&eventSize);
  FILE_readsync(this->fFileHandle,eventOffset,(intptr)eventData,eventSize,100);
  SPCH_ResolveData((unsigned short *)eventData);
  u_char *bankData = eventData + eventSize;
  u_char *headerData = (u_char *)reservememadr("spch temp",hsize,0x10);
  FILE_readsync(this->fFileHandle,hoffset,(intptr)headerData,hsize,100);
  char **bankNames = (char **)reservememadr("spch temp",this->fBankCount * sizeof(char *),0x10);
  for (int i = 0; i < this->fBankCount; i = i + 1) {
    bankNames[i] = 0;
    this->fBankOffset[i] = 0;
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
      if (isHeader && (this)->CheckMultiBank(name,headerBank,bn) != 0) {
        headerBank = headerBank + 1;
        memcpy(bankData,headerData + offset - hoffset,size);
        int bankId = SPCH_AddBank((intptr)bankData);
        bankData = bankData + size;
        bankNames[bankId] = name;
      }
      else {
        bool isData = (end[-4] == '.') && (end[-3] == 'd') && (end[-2] == 'a') && (end[-1] == 't');
        if (isData) {
          if ((nextDataBank < this->fBankCount) && (bankNames[nextDataBank] != 0) &&
              (strncmp(name,bankNames[nextDataBank],nameLength - 3) == 0)) {
            this->fBankOffset[nextDataBank] = offset;
            nextDataBank = nextDataBank + 1;
          }
          else {
            for (int i = 0; i < this->fBankCount; i = i + 1) {
              if ((bankNames[i] != 0) && (strncmp(name,bankNames[i],nameLength - 3) == 0)) {
                this->fBankOffset[i] = offset;
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
Speech::Speech()

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
    this->fCarBank.Mobile[iVar8].fFull = -1;
    this->fCarBank.Mobile[iVar8].fMake = -1;
    this->fCarBank.Mobile[iVar8].fModel = -1;
    this->fCarBank.Dispatch[iVar8].fFull = -1;
    this->fCarBank.Dispatch[iVar8].fMake = -1;
    this->fCarBank.Dispatch[iVar8].fModel = -1;
  }
  for (iVar8 = 0; iVar8 < 16; iVar8 = iVar8 + 1) {
    this->fLocationBank.Mobile[iVar8].fBankId = -1;
    this->fLocationBank.Dispatch[iVar8].fBankId = -1;
  }
  dispatch = new(__builtin_new(sizeof(DispatchSpeaker))) DispatchSpeaker();
  this->fDispatch = dispatch;
  for (iVar8 = 0; iVar10 = 0, iVar8 < 4; iVar8 = iVar8 + 1) {
    mobile = new(__builtin_new(sizeof(MobileSpeaker))) MobileSpeaker();
    this->fMobile[iVar8] = mobile;
  }
  iVar9 = 0;
  this->fFileOpen = 0;
  this->fBankOffset = 0;
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
    this->fMultiplePerps = 1;
  }
  else {
    this->fMultiplePerps = 0;
  }
  iVar8 = 0;
  gettick();
  bVar1 = 0 < GameSetup_gData.numCars;
  this->fCarCount = GameSetup_gData.numCars;
  if (bVar1) {
    do {
      bankNames[iVar8].SetCar(iVar8);
      iVar8 = iVar8 + 1;
    } while (iVar8 < this->fCarCount);
  }
  (this)->CountLocations();
  this->fBankCount = 0;
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
    iVar8 = (this)->CalculateBankSize((char *)header,bankNames,&local_20,&local_1c);
  }
  if (0 < iVar8) {
    this->fBankOffset = (long *)reservememadr("spch index",this->fBankCount * sizeof(long) + iVar8,0);
  }
  if (this->fBankOffset != 0) {
    uVar11 = SPCH_GetSampleDataRate(0x2b11,0x10,2);
    SPCH_Init(Speech_HandleRequest,0x12345678,uVar11);
    SPCH_InitBankMem(Speech_AllocateRAM,
               Speech_PurgeRAM,this->fBankCount);
    iVar8 = FILE_opensync(acStack_88,1,100,&this->fFileHandle);
    this->fFileOpen = (u_int)(iVar8 != 0);
    (this)->LoadBankHeaders((char *)header,bankNames,local_20,local_1c);
  }
  if (header != (void *)0x0) {
    purgememadr(header);
  }
  gettick();
  return;
}

/* ---- Reset__6Speech  [SPEECH.CPP:1248-1261] SLD-VERIFIED ---- */
void Speech_Reset(void)

{
  u_int uVar3;
  u_int uVar4;
  int iVar6;
  u_int uVar7;
  
  if (_6Speech_fgSpeech != 0) {
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      _6Speech_fgSpeech->fMobile[iVar6]->fCarObj = 0;
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
    _6Speech_fgSpeech->fCopCount = ((uVar3 & 0xffff00) >> 8) % 9;
    _6Speech_fgSpeech->fSuperCount = ((uVar4 & 0xffff00) >> 8) % 6;
    (_6Speech_fgSpeech->fDispatch)->Activate(uVar7 + ((uVar7 / 7 + ((uVar7 - uVar7 / 7) >> 1)) >> 2) * -7);
  }
  return;
}

/* ---- _._6Speech  [SPEECH.CPP:1267-1283] SLD-VERIFIED ---- */
Speech::~Speech()

{
  int iVar3;
  
  if (this->fBankOffset != 0) {
    SPCH_Deinit();
    purgememadr(this->fBankOffset);
  }
  if (this->fFileOpen != 0) {
    FILE_closesync(this->fFileHandle,100);   /* oracle 0x85b84/b88: a1=0x64 (was dropped) */
  }
  iVar3 = 0;
  __builtin_delete(this->fDispatch);
  do {
    __builtin_delete(this->fMobile[iVar3]);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  return;
}

/* ---- BankPatch__6SpeechlP8Car_tObj  [SPEECH.CPP:1297-1307] SLD-VERIFIED ---- */
u_int Speech::BankPatch(int bank,Car_tObj *car)
{
  u_int uVar1;
  
  if (bank == this->fStaticBank) {
    return 0x15;
  }
  uVar1 = 0xffffffff;
  if ((bank == this->fBlpClpBank) && (uVar1 = 0x13, car != 0)) {
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
  
  if (_6Speech_fgSpeech == 0) {
    offset = 0;
  }
  else {
    _6Speech_fgSpeech->fDispatch->fStatusSub = 0;
    _6Speech_fgSpeech->fDispatch->fStatusCount = 0x200;
    car = _6Speech_fgSpeech->fSpeakerCar;
    patch = (_6Speech_fgSpeech)->BankPatch(bank,car);
    if ((bank < 0) || (_6Speech_fgSpeech->fBankCount <= bank)) {
      offset = 0;
    }
    else {
      offset = _6Speech_fgSpeech->fBankOffset[bank];
    }
    if (patch < 0) {
      if (offset != 0) {
        CopSpeak_DirectRequest(_6Speech_fgSpeech->fFileHandle,offset + localoffset,size,car,0);
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
void Speaker::Report(Car_tObj *cop)
{
  return;
}

/* ---- Deny__Q26Speech7Speaker  [SPEECH.CPP:1363-1367] SLD-VERIFIED ---- */
void Speaker::Deny()
{
  return;
}

/* ---- Grant__Q26Speech7Speaker  [SPEECH.CPP:1371-1375] SLD-VERIFIED ---- */
void Speaker::Grant()
{
  return;
}

/* ---- Ready__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:1379-1383] SLD-VERIFIED ---- */
void Speaker::Ready(Car_tObj *wing)
{
  return;
}

/* ---- Engage__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:1394-1398] SLD-VERIFIED ---- */
void Speaker::Engage(Car_tObj *perp)
{
  return;
}

/* ---- Lose__Q26Speech7Speaker  [SPEECH.CPP:1402-1406] SLD-VERIFIED ---- */
void Speaker::Lose()
{
  return;
}

/* ---- Accident__Q26Speech7Speakeri  [SPEECH.CPP:1410-1414] SLD-VERIFIED ---- */
void Speaker::Accident(int slice)
{
  return;
}

/* ---- Catch__Q26Speech7Speakeri  [SPEECH.CPP:1418-1422] SLD-VERIFIED ---- */
void Speaker::Catch(int ticket)
{
  return;
}

/* ---- RoadBlock__Q26Speech7Speaker  [SPEECH.CPP:1426-1430] SLD-VERIFIED ---- */
void Speaker::RoadBlock()
{
  return;
}

/* ---- SpikeBelt__Q26Speech7Speaker  [SPEECH.CPP:1434-1438] SLD-VERIFIED ---- */
void Speaker::SpikeBelt()
{
  return;
}

/* ---- Backup__Q26Speech7Speaker  [SPEECH.CPP:1442-1446] SLD-VERIFIED ---- */
void Speaker::Backup()
{
  return;
}

/* ---- ReportBlockade__Q26Speech7Speaker  [SPEECH.CPP:1450-1454] SLD-VERIFIED ---- */
void Speaker::ReportBlockade()
{
  return;
}

/* ---- Roger__Q26Speech7Speaker  [SPEECH.CPP:1459-1463] SLD-VERIFIED ---- */
void Speaker::Roger()
{
  return;
}

/* ---- Bullhorn__Q26Speech7Speaker  [SPEECH.CPP:1467-1471] SLD-VERIFIED ---- */
void Speaker::Bullhorn()
{
  return;
}

/* ---- Purge__Q26Speech7Speaker  [SPEECH.CPP:1475-1479] SLD-VERIFIED ---- */
void Speaker::Purge()
{
  return;
}

/* ---- Promote__Q26Speech7Speaker  [SPEECH.CPP:1490-1503] SLD-VERIFIED ---- */
void Speaker::Promote()
{
  Speaker *pSVar1;
  Speaker *dispatch;
  Speaker *pSVar3;
  
  pSVar1 = (Speaker *)Speech_Dispatch();
  do {
    pSVar3 = pSVar1;
    pSVar1 = pSVar3->fSub;
  } while (pSVar1 != (Speaker *)0x0 && pSVar1 != this);
  pSVar3->fSub = this->fSub;
  dispatch = (Speaker *)Speech_Dispatch();
  this->fSub = dispatch->fSub;
  dispatch = (Speaker *)Speech_Dispatch();
  dispatch->fSub = this;
  return;
}

/* ---- Speech_Server__Fv  [SPEECH.CPP:1539-1540] SLD-VERIFIED ---- */
void Speech_Server(void)

{
  Speaker *speaker = (Speaker *)Speech_Dispatch();

  (speaker)->Status();
  return;
}

/* ---- SetDelayedStatus__6SpeechPQ26Speech7Speakeri  [SPEECH.CPP:1546-1548] SLD-VERIFIED ---- */
void Speech::SetDelayedStatus(Speaker *sub,int delay)
{
  _6Speech_fgSpeech->fDispatch->fStatusSub = sub;
  _6Speech_fgSpeech->fDispatch->fStatusCount = delay;
  return;
}

/* ---- Activate__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:1554-1571] SLD-VERIFIED ---- */
void DispatchSpeaker::Activate(u_int seedupdatecount)
{

  CallSignBank *callSign = (CallSignBank *)(this)->CallSign();

  this->fFrom = callSign->fDispatch;
  this->fConfirm.flags = 0xff;
  this->fPerpName.flags = 0xf;
  this->fSub = 0;
  this->fReverse.flags = GameSetup_gData.track & 1;
  this->fPerp[1] = 0;
  this->fPerp[0] = 0;
  this->fStatusCount = 0x200;
  this->fStatusSub = 0;
  this->fUpdateCount = seedupdatecount;
  this->fHavePerp = 0;
  return;
}

/* ---- Dispatch__6Speech  [SPEECH.CPP:1578-1586] SLD-VERIFIED ---- */
intptr Speech_Dispatch(void)

{
  
  if ((_6Speech_fgSpeech != 0) && (_6Speech_fgSpeech->fBankOffset != 0)) {
    return (intptr)_6Speech_fgSpeech->fDispatch;
  }
  return (intptr)_6Speech_fgUndefined;
}

/* ---- Roger__Q26Speech15DispatchSpeaker  [SPEECH.CPP:1592-1629] SLD-VERIFIED ---- */
void DispatchSpeaker::Roger()
{
  Speaker *base = this;
  Speaker *sub;
  Car_tObj *perp;
  CallSignBank *callSign;

  int unit;

  _6Speech_fgSpeech->fSpeakerCar = 0;
  sub = base->fSub;
  if (sub != 0) {

    perp = (Car_tObj *)(sub)->Perp();
  }
  else {
    perp = 0;
  }
  if ((sub == 0) || (perp == 0) || (sub->fBlockade.flags != 0)) {
    SPCHNFS_D_A_CONFIRM(&base->fConfirm);
  }
  else if (sub->fArrest.flags != 0) {

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (sub)->Unit();
    base->fTo = callSign->fMobile[unit];
    SPCHNFS_D_C_PERP_APPREHENSION_REPLY(base->fTo,&base->fConfirm,&base->fPerpName);
  }
  else if (sub->fUpdate.flags == 0) {
    SPCHNFS_D_A_CONFIRM(&base->fConfirm);
    SPCH_PlaySpeech();
    (base)->SetCar(perp);
    SPCHNFS_D_C_PERP_LOST_CONFIRM(&base->fColour,base->fCar);
  }
  else {
    (base)->SetCar(perp);

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (sub)->Unit();
    base->fTo = callSign->fMobile[unit];

    if ((sub)->DistToPerp() < 0x280000) {
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
void DispatchSpeaker::StatusReply()
{
  Speaker *base = this;
  Speaker *sub = base->fSub;
  Speaker *savedSub = 0;

  CallSignBank *callSign;
  Car_tObj *car;
  int unit;
  bool playBlockadeConfirmation = false;

  if (sub == 0) {
    return;
  }

  if ((sub)->Perp() == 0) {
    return;
  }

  _6Speech_fgSpeech->fSpeakerCar = 0;
  if (sub->fBlockade.flags == 0) {

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (sub)->Unit();
    base->fTo = callSign->fMobile[unit];
  }
  else {
    if (_6Speech_fgSpeech->fMultiplePerps != 0) {

      (sub)->ReportBlockade();
      return;
    }
    savedSub = sub->fSub;
    if ((savedSub != 0) && (savedSub->fBlockade.flags != 0)) {

      callSign = (CallSignBank *)(base)->CallSign();

      unit = (sub)->Unit();
      base->fTo = callSign->fMobile[unit];
      sub = savedSub;
    }
    else {

      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fAllUnits;
      savedSub = sub;
    }

    (sub)->ReportBlockade();
    _6Speech_fgSpeech->fSpeakerCar = 0;
    SPCHNFS_D_A_CONFIRM(&base->fConfirm);
    SPCH_PlaySpeech();
  }

  SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  sub = base->fSub;

  car = (Car_tObj *)(sub)->CarObj();
  (base)->FindLocation(car);

  sub = base->fSub;
  if (sub->fBlockade.flags == 1) {

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (savedSub)->Unit();
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

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (nextSub)->Unit();
    base->fWing = callSign->fMobile[unit];
    SPCHNFS_D_C_BKUP_REQUEST_GRANT_REPLY(&base->fDistance,&base->fPosition,
                                         base->fLocation,base->fWing);
    SPCH_PlaySpeech();

    (sub)->Roger();
    this->fStatusCount = 0x140;
    this->fUpdateCount++;
    this->fStatusSub = nextSub;
  }
  if (playBlockadeConfirmation) {
    SPCH_PlaySpeech();
  }

  sub = base->fSub;
  if (savedSub != sub) {

    (sub)->Roger();
  }
  if ((sub->fSub != 0) && (sub->fSub->fBlockade.flags != 0)) {
    sub->fBlockade.flags = 0;
  }
}

/* ---- Status__Q26Speech15DispatchSpeaker  [SPEECH.CPP:1718-1848] SLD-VERIFIED ---- */
void DispatchSpeaker::Status()
{
  Speaker *base = this;
  Speaker *sub = base->fSub;
  Speaker *statusSub;
  Speaker *nextSub;

  Car_tObj *car;
  Car_tObj *perp;
  CallSignBank *callSign;
  int dist;
  int unit;

  if (sub == 0) {
    return;
  }

  perp = (Car_tObj *)(sub)->Perp();
  if (perp == 0) {
    return;
  }


  car = (Car_tObj *)(sub)->CarObj();
  if ((car->carFlags & 0x200) != 0) {

    dist = (sub)->DistToPerp();
    if (sub->fHavePerp == 0) {
      if (dist < 0x640000) {

        perp = (Car_tObj *)(sub)->Perp();

        (sub)->Engage(perp);
      }
    }
    else if (dist > 0x15e0000) {
      sub->fHavePerp = 0;
      sub->fUpdate.flags = 0;

      (sub)->Status();
    }
  }

  if (this->fStatusSub != 0) {
    if (--this->fStatusCount != 0) {
      return;
    }
    statusSub = this->fStatusSub;
    if (statusSub == base) {
      (this)->StatusReply();
      return;
    }
    sub = base->fSub;

    (statusSub)->Status();
    if ((sub != 0) && (statusSub == sub->fSub)) {
      return;
    }
    _6Speech_fgSpeech->fSpeakerCar = 0;

    (base)->Roger();
    return;
  }

  if (0 < this->fStatusCount) {
    this->fStatusCount--;
    return;
  }
  sub = base->fSub;
  if ((sub->fBlockade.flags != 0) || (sub->fArrest.flags != 0)) {
    return;
  }

  nextSub = sub->fSub;
  if (nextSub != 0) {

    car = (Car_tObj *)(nextSub)->Perp();

    perp = (Car_tObj *)(sub)->Perp();
    if (car != perp) {
      (nextSub)->Promote();
    }
  }

  switch (this->fUpdateCount & 3) {
  case 0:
    sub->fUpdate.flags = 0x26;
    break;
  case 1:
    sub->fUpdate.flags = 1;
    break;
  case 2:

    dist = (sub)->DistToPerp();
    if (dist < 0x280000) {

      car = (Car_tObj *)(sub)->CarObj();
      if ((base)->CalcMph(car) > 0x32) {

        perp = (Car_tObj *)(sub)->Perp();
        if ((base)->CalcMph(perp) > 0x32) {
          sub->fUpdate.flags = 8;
          break;
        }
      }
    }
    sub->fUpdate.flags = 0x26;
    break;
  case 3:

    if (((sub)->IsSuper() != 0) &&
        (this->fUpdateCount == 7)) {
      sub->fUpdate.flags = 0;

      (sub)->Status();
      this->fUpdateCount++;
      return;
    }

    dist = (sub)->DistToPerp();
    if (dist < 0x140000) {

      (sub)->Bullhorn();
      this->fUpdateCount++;
      return;
    }
    sub->fUpdate.flags = 1;
    break;
  }

  _6Speech_fgSpeech->fSpeakerCar = 0;

  callSign = (CallSignBank *)(base)->CallSign();

  unit = (sub)->Unit();
  base->fTo = callSign->fMobile[unit];
  SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  SPCHNFS_D_C_IN_PURS_NEAR_PERP(&sub->fUpdate);
  SPCH_PlaySpeech();
  this->fStatusCount = 0x60;
  this->fStatusSub = sub;
  this->fUpdateCount++;
}

/* ---- Status__Q26Speech13MobileSpeaker  [SPEECH.CPP:1853-1948] SLD-VERIFIED ---- */
void MobileSpeaker::Status()
{
  Speaker *base = this;
  Speaker *sub;
  Speaker *savedDispatchSub;
  DispatchSpeaker *dispatch;

  CallSignBank *callSign;
  Car_tObj *car;
  Car_tObj *perp;
  int dist;


  perp = (Car_tObj *)(base)->Perp();
  if (perp == 0) {
    return;
  }

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;
  if (base->fArrest.flags == 1) {

    callSign = (CallSignBank *)(base)->CallSign();
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    SPCHNFS_C_D_PERP_APPREHENSION(&this->fVoice,&base->fPerpName);
  }
  else {

    car = (Car_tObj *)(base)->CarObj();
    if (((car->carFlags & 0x200) != 0) && (base->fUpdate.flags == 0)) {

      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();

      perp = (Car_tObj *)(base)->Perp();
      (base)->SetCar(perp);
      (base)->FindLocation(this->fCarObj);
      SPCHNFS_C_D_PERP_LOST(&this->fVoice,&base->fColour,base->fCar,&base->fPosition,
                            base->fLocation,&base->fDistance,&base->fPerpName);
      SPCH_PlaySpeech();

      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      savedDispatchSub = dispatch->fSub;
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      dispatch->fSub = base;
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

      (dispatch)->Roger();
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      dispatch->fSub = savedDispatchSub; /* PORTABILITY-REVIEWED: SPEECH-DISPATCH-SAVE-RESTORE-01 */
      return;
    }


    sub = base->fSub;
    if (((base)->IsSuper() != 0) &&
        (base->fUpdate.flags == 0) && (sub != 0)) {

      car = (Car_tObj *)(sub)->CarObj();
    }
    else {
      car = 0;
    }
    if ((car != 0) && ((car->carFlags & 0x40) == 0)) {

      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fAllUnits;
      SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      SPCHNFS_S_C_SUPER_COP_CRITICISM(&this->fVoice);
    }
    else {
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
      sub = dispatch->fSub;
      if ((sub != 0) && (sub->fSub == base)) {
        SPCHNFS_C_C_NEW_OFFICER_ENGAGING(&this->fVoice,base->fFrom);
        dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
        sub = dispatch->fSub;

        (sub)->Roger();
        return;
      }


      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();

      perp = (Car_tObj *)(base)->Perp();
      (base)->SetCar(perp);

      car = (Car_tObj *)(base)->CarObj();
      (base)->FindLocation(car);
      (this)->SetSpeed(this->fPerp);

      dist = (base)->DistToPerp();

      if (dist < 0x280000) {

        perp = (Car_tObj *)(base)->Perp();
        if (perp->N.flightTime > 0x40) {
          SPCHNFS_C_D_IN_PURS_PERP_AIRBORN(&this->fVoice);
        }
        else if (base->fUpdate.flags == 1) {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_LOC(&this->fVoice,&base->fPosition,
                                                base->fLocation,&base->fDistance);
        }
        else if (base->fUpdate.flags != 8) {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_STS(&this->fVoice,&base->fColour,
                                                base->fCar,&base->fDistance,
                                                &base->fPosition,base->fLocation);
        }
        else {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(&this->fVoice,this->fSpeed,&this->fSpeedType);
        }
      }
      else if (base->fHavePerp != 0) {
        if (base->fUpdate.flags == 1) {
          SPCHNFS_C_D_IN_PURS_AWAY_PERP_REPLY_LOC(&this->fVoice,&base->fPosition,
                                                  base->fLocation,&base->fDistance,
                                                  &base->fColour,base->fCar,&base->fPerpName);
        }
        else if (base->fUpdate.flags != 8) {
          SPCHNFS_C_D_IN_PURS_AWAY_PERP_REPLY_STS(&this->fVoice,&base->fColour,
                                                  base->fCar,&base->fPosition,
                                                  base->fLocation,&base->fDistance);
        }
        else {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(&this->fVoice,this->fSpeed,&this->fSpeedType);
        }
      }
      else {
        if (base->fUpdate.flags == 1) {
          SPCHNFS_C_D_IN_PURS_LOOK_PERP_REPLY_LOC(&this->fVoice,&base->fPosition,
                                                  base->fLocation,&base->fDistance,
                                                  &base->fColour,base->fCar);
        }
        else if (base->fUpdate.flags == 8) {
          SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(&this->fVoice,this->fSpeed,&this->fSpeedType);
        }
        else {
          SPCHNFS_C_D_IN_PURS_LOOK_PERP_REPLY_STS(&this->fVoice,&base->fColour,
                                                  base->fCar,&base->fPerpName);
        }
      }
    }
  }
  SPCH_PlaySpeech();
}

/* ---- ClearPerp__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1954-1958] SLD-VERIFIED ---- */
void DispatchSpeaker::ClearPerp(Car_tObj *car)
{
  int i;
  
  i = 0;
  do {
    if (this->fPerp[i] == car) {
      this->fPerp[i] = (Car_tObj *)0x0;
    }
    i = i + 1;
  } while (i < 2);
  return;
}

/* ---- KnownPerp__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1964-1969] SLD-VERIFIED ---- */
void * DispatchSpeaker::KnownPerp(Car_tObj *car)
{
  int i;
  
  i = 0;
  do {
    if (this->fPerp[i] == car) {
      return (void *)0x1;
    }
    i = i + 1;
  } while (i < 2);
  return (void *)0x0;
}

/* ---- AddPerp__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1976-1980] SLD-VERIFIED ---- */
void DispatchSpeaker::AddPerp(Car_tObj *car)
{
  int i;
  
  i = 0;
  do {
    if (this->fPerp[i] == (Car_tObj *)0x0) {
      this->fPerp[i] = car;
    }
    i = i + 1;
  } while (i < 2);
  return;
}

/* ---- Report__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:1990-2031] SLD-VERIFIED ---- */
void DispatchSpeaker::Report(Car_tObj *perp)
{
  Speaker *base = this;
  Speaker *sub = base->fSub;

  CallSignBank *callSign;
  int unit;
  bool known;

  _6Speech_fgSpeech->fSpeakerCar = 0;

  known = (base)->KnownPerp(perp) != 0;
  if (known && (sub != 0)) {
    if (_6Speech_fgSpeech->fMultiplePerps == 0) {

      callSign = (CallSignBank *)(base)->CallSign();

      unit = (sub)->Unit();
      base->fTo = callSign->fMobile[unit];
      SPCHNFS_D_C_PERP_SIGHTED_CONFIRM(&base->fConfirm,base->fTo);
      SPCH_PlaySpeech();
    }
  }
  else {
    if (_6Speech_fgSpeech->fMultiplePerps == 0) {

      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fAllUnits;
      SPCHNFS_D_C_INTRO_CALL(base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      (base)->SetCar(perp);
      (base)->FindLocation(perp);
      SPCHNFS_D_C_BEGIN_PURS_REP_SPDR(&base->fColour,base->fCar,&base->fPosition,
                                      base->fLocation,&base->fDistance);
      SPCH_PlaySpeech();
    }
    (this)->AddPerp(perp);
    this->fStatusCount = 0x2a0;
  }
}

/* ---- Accident__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:2039-2043] SLD-VERIFIED ---- */
void DispatchSpeaker::Accident(int slice)
{
  return;
}

/* ---- Deny__Q26Speech15DispatchSpeaker  [SPEECH.CPP:2049-2073] SLD-VERIFIED ---- */
void DispatchSpeaker::Deny()
{
  Speaker *base = this;
  Speaker *sub = base->fSub;

  CallSignBank *callSign;
  int unit;

  if (sub != 0) {
    _6Speech_fgSpeech->fSpeakerCar = 0;

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (sub)->Unit();
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
void DispatchSpeaker::Grant()
{
  Speaker *base = this;
  Speaker *sub = base->fSub;

  /* The second guard is literal MIPS: addiu v0,sub,0x14; beqz v0.
   * It protects the address-of-member expression for the undefined sentinel. */
  if ((sub != 0) && (sub != (Speaker *)(intptr)(intptr)-0x14)) {
    _6Speech_fgSpeech->fSpeakerCar = 0;
    if (_6Speech_fgSpeech->fMultiplePerps == 0) {
      SPCHNFS_D_C_RDBLK_SPBLT_GRANT_REPLY(&sub->fBlockade,&base->fConfirm);
      SPCH_PlaySpeech();
    }
  }
}

/* ---- Ready__Q26Speech15DispatchSpeakerP8Car_tObj  [SPEECH.CPP:2104-2123] SLD-VERIFIED ---- */
void DispatchSpeaker::Ready(Car_tObj *carObj)
{
  Speaker *pSVar1;

  Car_tObj *src_pos;
  Speaker *pSVar3;
  
  pSVar1 = (Speaker *)Speech_Mobile(carObj);
  pSVar3 = this->fSub;
  if (pSVar3 != (Speaker *)0x0 && pSVar1 != pSVar3) {
    (pSVar1->fBlockade).flags = (pSVar3->fBlockade).flags;
    pSVar3 = this->fSub;
    src_pos = pSVar3->Perp();
    pSVar1->Engage(src_pos);
  }
  this->fStatusSub = this;
  this->fStatusCount = 0x80;
  return;
}

/* ---- PickVoice__6SpeechP8Car_tObj  [SPEECH.CPP:2144-2150] SLD-VERIFIED ---- */
int Speech::PickVoice(Car_tObj *carObj)
{
  int iVar1;
  
  if ((carObj->carFlags & 0x40U) != 0) {
    iVar1 = this->fSuperCount;
    this->fSuperCount = (int)((uint32)iVar1 + 1u);
    return iVar1 % 6;
  }
  if ((carObj->carFlags & 0x80U) == 0) {
    iVar1 = this->fCopCount;
    this->fCopCount = (int)((uint32)iVar1 + 1u);
    return iVar1 % 9;
  }
  return 0;
}

/* ---- GetVoice__6SpeechP8Car_tObj  [SPEECH.CPP:2156-2157] SLD-VERIFIED ---- */
int Speech_GetVoice(Car_tObj *carObj)

{
  return (_6Speech_fgSpeech)->PickVoice(carObj);
}

/* ---- Activate__Q26Speech13MobileSpeakerP8Car_tObj  [SPEECH.CPP:2163-2189] SLD-VERIFIED ---- */
void MobileSpeaker::Activate(Car_tObj *carObj)
{
  int reg_v0;
  uint32 uVar1;

  int iVar3;
  
  this->fCarObj = carObj;
  reg_v0 = Speech_GetVoice(carObj);
  this->fUnit = reg_v0;
  if ((carObj->carFlags & 0x40U) == 0) {
    uVar1 = Speech_gCopAttr[reg_v0].voice;
  }
  else {
    this->fUnit = (int)((uint32)reg_v0 + 9u);
    uVar1 = 8;
  }
  (this->fVoice).flags = uVar1;

  iVar3 = (intptr)(this)->CallSign();
  this->fFrom = *(int *)(iVar3 + this->fUnit * 4 + 8);
  iVar3 = GameSetup_gData.track;
  this->fConfirm.flags = 0xff;
  this->fPerpName.flags = 0xf;
  this->fBlockade.flags = 0;
  this->fArrest.flags = 0;
  this->fUpdate.flags = 0;
  this->fPerp = (Car_tObj *)0x0;
  this->fSub = (Speaker *)0x0;
  this->fHavePerp = 0;
  this->fReverse.flags = iVar3 & 1;
  return;
}

/* ---- ReActivate__Q26Speech13MobileSpeaker  [SPEECH.CPP:2199-2212] SLD-VERIFIED ---- */
void MobileSpeaker::ReActivate()
{
  int reg_v0;
  int tu2;

  int iVar2;
  
  reg_v0 = Speech_GetVoice(this->fCarObj);
  this->fUnit = reg_v0;
  if ((this->fCarObj->carFlags & 0x40U) == 0) {
    tu2 = Speech_gCopAttr[reg_v0].voice;
  }
  else {
    this->fUnit = (int)((uint32)reg_v0 + 9u);
    tu2 = 8;
  }
  (this->fVoice).flags = tu2;

  iVar2 = (intptr)(this)->CallSign();
  this->fFrom = *(int *)(iVar2 + this->fUnit * 4 + 8);
  return;
}

/* ---- FindMobile__6SpeechP8Car_tObj  [SPEECH.CPP:2218-2237] SLD-VERIFIED ---- */
Speaker * Speech::FindMobile(Car_tObj *carObj)
{
  int index;

  for (index = 0; index < 4; index = index + 1) {
    if (carObj == this->fMobile[index]->fCarObj) {
      return this->fMobile[index];
    }
  }
  for (index = 0; index < 4; index = index + 1) {
    if (this->fMobile[index]->fCarObj == (Car_tObj *)0x0) {
      (this->fMobile[index])->Activate(carObj);
      return this->fMobile[index];
    }
  }
  return _6Speech_fgUndefined;
}

/* ---- Mobile__6SpeechP8Car_tObj  [SPEECH.CPP:2244-2250] SLD-VERIFIED ---- */
intptr Speech_Mobile(Car_tObj *carObj)

{
  Speaker *pSVar1;
  
  pSVar1 = _6Speech_fgUndefined;
  if ((_6Speech_fgSpeech != 0) && (_6Speech_fgSpeech->fBankOffset != 0)) {
    pSVar1 = (_6Speech_fgSpeech)->FindMobile(carObj);
  }
  return (intptr)pSVar1;
}

/* ---- CalcMph__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:2256-2257] SLD-VERIFIED ---- */
int Speaker::CalcMph(Car_tObj *perp)
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
void MobileSpeaker::SetSpeed(Car_tObj *perp)
{
  int a;
  int iVar1;
  
  if (GameSetup_gData.measurement == 1) {
    (this->fSpeedType).flags = 1;
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
    (this->fSpeedType).flags = 2;
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
  this->fSpeed = iVar1;
  return;
}

/* ---- DistToPerp__Q26Speech13MobileSpeaker  [SPEECH.CPP:2281-2286] SLD-VERIFIED ---- */
int MobileSpeaker::DistToPerp()
{


  int iVar3;
  int iVar4;

  int iVar6;

  iVar3 = (intptr)(this)->CarObj();

  iVar4 = (intptr)(this)->Perp();
  if (*(int *)(iVar3 + 0xa0) - *(int *)(iVar4 + 0xa0) < 1) {

    iVar3 = (intptr)(this)->Perp();

    iVar4 = (intptr)this->CarObj();
  }
  else {

    iVar3 = (intptr)(this)->CarObj();

    iVar4 = (intptr)this->Perp();
  }
  iVar6 = *(int *)(iVar3 + 0xa0) - *(int *)(iVar4 + 0xa0);

  iVar3 = (intptr)(this)->CarObj();

  iVar4 = (intptr)(this)->Perp();
  if (*(int *)(iVar3 + 0xa8) - *(int *)(iVar4 + 0xa8) < 1) {

    iVar3 = (intptr)(this)->Perp();

    iVar4 = (intptr)this->CarObj();
  }
  else {

    iVar3 = (intptr)(this)->CarObj();

    iVar4 = (intptr)this->Perp();
  }
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
void MobileSpeaker::Report(Car_tObj *perp)
{
  Speaker *base = this;
  DispatchSpeaker *dispatch;

  CallSignBank *callSign;

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

  callSign = (CallSignBank *)(base)->CallSign();
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();
  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;
  (base)->SetCar(perp);
  (base)->FindLocation(perp);
  (this)->SetSpeed(perp);
  SPCHNFS_C_D_PERP_SIGHTED(&this->fVoice,&base->fColour,base->fCar,&base->fDistance,
                           &base->fPosition,base->fLocation,&base->fPerpName);
  SPCH_PlaySpeech();
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  dispatch->fSub = base;
}

/* ---- Engage__Q26Speech13MobileSpeakerP8Car_tObj  [SPEECH.CPP:2331-2450] SLD-VERIFIED ---- */
void MobileSpeaker::Engage(Car_tObj *perp)
{
  Speaker *base = this;
  Speaker *previous;
  Speaker *cursor;
  Speaker *dispatchSub;
  Speaker *savedDispatchSub;
  DispatchSpeaker *dispatch;

  CallSignBank *callSign;
  Car_tObj *activePerp;
  Car_tObj *car;
  bool insertAtHead = false;

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;
  base->fHavePerp = 1;

  activePerp = (Car_tObj *)(base)->Perp();

  if (perp == activePerp) {
    if (_6Speech_fgSpeech->fMultiplePerps != 0) {
      return;
    }
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

    if ((dispatch)->StatusCount() >= 0x160) {
      return;
    }
    (base)->SetCar(activePerp);

    callSign = (CallSignBank *)(base)->CallSign();
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();

    activePerp = (Car_tObj *)(base)->Perp();
    (base)->FindLocation(activePerp);
    SPCHNFS_C_C_PERP_REAQUIRED(&this->fVoice,&base->fColour,base->fCar,
                               &base->fPosition,base->fLocation,&base->fDistance);
    goto MobileEngage_playAndReturn;
  }

  this->fPerp = perp;

  activePerp = (Car_tObj *)(base)->Perp();
  (base)->SetCar(activePerp);

  car = (Car_tObj *)(base)->CarObj();
  if ((car->carFlags & 0x200) == 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    previous = dispatch;
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
  if (dispatch->fSub == base) {

    car = (Car_tObj *)(base)->CarObj();
    if ((car->carFlags & 0x200) == 0) {
      return;
    }

    (dispatch)->Report(perp);
    _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

    callSign = (CallSignBank *)(base)->CallSign();
    base->fTo = callSign->fDispatch;

    activePerp = (Car_tObj *)(base)->Perp();
    (base)->FindLocation(activePerp);
    SPCHNFS_C_D_ENGAGE_PURS_REP_SPDR_REPLY(&this->fVoice,base->fTo,&base->fColour,
                                           base->fCar,&base->fDistance,&base->fPosition,
                                           base->fLocation,&base->fConfirm);
    goto MobileEngage_playAndReturn;
  }


  if ((base)->IsSuper() != 0) {

    activePerp = (Car_tObj *)(base)->Perp();
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    dispatchSub = dispatch->fSub;
    if (((activePerp->carFlags & 4) != 0) && (dispatchSub != 0)) {

      car = (Car_tObj *)(dispatchSub)->CarObj();
      insertAtHead = (car->carFlags & 0x40) == 0;
    }
  }

  if (insertAtHead) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    base->fSub = dispatch->fSub;
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    dispatch->fSub = base;
    if (base->fBlockade.flags != 0) {
      return;
    }

    callSign = (CallSignBank *)(base)->CallSign();
    base->fTo = callSign->fAllUnits;
    SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    SPCHNFS_S_C_SUPER_COP_ARRIVAL(&this->fVoice);
    goto MobileEngage_playAndReturn;
  }

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  previous = dispatch;
  dispatchSub = previous->fSub;
  if (dispatchSub != 0) {

    car = (Car_tObj *)(dispatchSub)->Perp();
    if (car != 0) {

      car = (Car_tObj *)(dispatchSub)->Perp();
      if ((car->carFlags & 4) == 0) {

        activePerp = (Car_tObj *)(base)->Perp();
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

  if ((dispatch)->KnownPerp(perp) != 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

    if ((dispatch)->StatusCount() < 0x180) {
      return;
    }
  }


  callSign = (CallSignBank *)(base)->CallSign();
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();

  activePerp = (Car_tObj *)(base)->Perp();
  (base)->FindLocation(activePerp);

  activePerp = (Car_tObj *)(base)->Perp();
  (this)->SetSpeed(activePerp);

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

  if ((dispatch)->KnownPerp(activePerp) == 0) {
    SPCHNFS_C_D_ENGAGE_PURS_REP_SPDR(&this->fVoice,&base->fColour,base->fCar,
                                     &base->fPosition,base->fLocation,&base->fDistance,
                                     this->fSpeed,&this->fSpeedType,&base->fPerpName);
  }
  else {
    SPCHNFS_C_D_PERP_SIGHTED(&this->fVoice,&base->fColour,base->fCar,
                             &base->fDistance,&base->fPosition,base->fLocation,
                             &base->fPerpName);
  }
  SPCH_PlaySpeech();

  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  savedDispatchSub = dispatch->fSub;
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  dispatch->fSub = base;
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

  activePerp = (Car_tObj *)(base)->Perp();

  (dispatch)->Report(activePerp);
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  dispatch->fSub = savedDispatchSub; /* PORTABILITY-REVIEWED: SPEECH-DISPATCH-SAVE-RESTORE-01 */
  return;

MobileEngage_playAndReturn:
  SPCH_PlaySpeech();
}

/* ---- Lose__Q26Speech13MobileSpeaker  [SPEECH.CPP:2463-2538] SLD-VERIFIED ---- */
void MobileSpeaker::Lose()
{
  Speaker *base = this;
  DispatchSpeaker *dispatch;
  Speaker *leader = 0;
  Speaker *savedDispatchSub;

  CallSignBank *callSign;
  Car_tObj *perp;
  Car_tObj *car;
  int unit;


  perp = (Car_tObj *)(base)->Perp();
  if (perp == 0) {
    return;
  }

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  leader = dispatch->fSub;
  if (!((leader != 0) && (leader->fSub == base) &&
        (base->fBlockade.flags == 0) && (base->fArrest.flags == 0))) {
    leader = 0;
  }


  callSign = (CallSignBank *)(base)->CallSign();
  if (leader != 0) {

    unit = (leader)->Unit();
    base->fTo = callSign->fMobile[unit];
  }
  else {
    base->fTo = callSign->fDispatch;
  }

  if (base->fArrest.flags == 0) {
    if ((base->fBlockade.flags == 0) && (leader == 0)) {
      dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

      if ((dispatch)->StatusCount() > 0x160) {
        return;
      }
    }
  }
  else {
    SPCHNFS_C_P_FALSE_ARREST_BULLHORN(&this->fVoice);
    SPCH_PlaySpeech();
  }

  SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();

  perp = (Car_tObj *)(base)->Perp();
  (base)->SetCar(perp);

  perp = (Car_tObj *)(base)->Perp();
  (base)->FindLocation(perp);

  if (base->fArrest.flags == 0) {

    car = (Car_tObj *)(base)->CarObj();
    if ((car->carFlags & 0x200) == 0) {
      if (base->fBlockade.flags == 1) {
        SPCHNFS_C_D_SPBLT_FAILED(&this->fVoice,&base->fColour,base->fCar);
      }
      else if (base->fBlockade.flags == 2) {
        SPCHNFS_C_D_RDBLK_FAILED(&this->fVoice,&base->fColour,base->fCar);
      }
      else if (leader == 0) {
        SPCHNFS_C_D_PERP_LOST(&this->fVoice,&base->fColour,base->fCar,&base->fPosition,
                              base->fLocation,&base->fDistance,&base->fPerpName);
      }
      else {
        SPCHNFS_C_C_IDLE_WINGMAN_DISAPPEARS(&this->fVoice);
      }
    }
    else {
      SPCHNFS_C_D_ENDGAME(&this->fVoice);
    }
  }
  else {
    SPCHNFS_C_D_DURING_FALSE_ARREST(&this->fVoice,&base->fPerpName);
  }
  SPCH_PlaySpeech();
  base->fBlockade.flags = 0;
  base->fArrest.flags = 0;
  base->fUpdate.flags = 0;

  if (leader == 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
    savedDispatchSub = dispatch->fSub;
    dispatch->fSub = base;

    (dispatch)->Roger();
    dispatch->fSub = savedDispatchSub; /* PORTABILITY-REVIEWED: SPEECH-DISPATCH-SAVE-RESTORE-01 */
  }
}

/* ---- Accident__Q26Speech13MobileSpeakeri  [SPEECH.CPP:2544-2548] SLD-VERIFIED ---- */
void MobileSpeaker::Accident(int slice)
{
  return;
}

/* ---- Catch__Q26Speech13MobileSpeakeri  [SPEECH.CPP:2554-2621] SLD-VERIFIED ---- */
void MobileSpeaker::Catch(int ticket)
{
  Speaker *base = this;
  DispatchSpeaker *dispatch;

  CallSignBank *callSign;
  Car_tObj *perp;
  uint32 ambulanceFlags;


  perp = (Car_tObj *)(base)->Perp();
  if (perp == 0) {
    return;
  }

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

  perp = (Car_tObj *)(base)->Perp();
  if (perp->N.orientationToGround.y < 0) {

    callSign = (CallSignBank *)(base)->CallSign();
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();

    perp = (Car_tObj *)(base)->Perp();
    (base)->FindLocation(perp);
    SPCHNFS_C_D_PERP_CRASH_ROLL(&this->fVoice,&base->fPosition,base->fLocation,
                                &base->fDistance,&base->fPerpName);
    SPCH_PlaySpeech();
    ambulanceFlags = 4;
    goto MobileCatch_requestEms;
  }


  perp = (Car_tObj *)(base)->Perp();
  if (perp->collision.smoking == 0) {
    base->fArrest.flags = ticket;
    if (ticket == 1) {
      SPCHNFS_C_P_ARRESTED(&this->fVoice,&base->fArrest);
    }
    else if (ticket == 2) {
      SPCHNFS_C_P_WARNING(&this->fVoice,&base->fArrest);
    }
    else {
      SPCHNFS_C_P_TICKET(&this->fVoice,&base->fArrest);
    }
    SPCH_PlaySpeech();
    if (ticket == 1) {
      (_6Speech_fgSpeech)->SetDelayedStatus(base,0x60);
    }
    goto MobileCatch_dispatchCallback;
  }


  callSign = (CallSignBank *)(base)->CallSign();
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();

  perp = (Car_tObj *)(base)->Perp();
  (base)->SetCar(perp);

  perp = (Car_tObj *)(base)->Perp();
  (base)->FindLocation(perp);
  SPCHNFS_C_D_PERP_CRASH_GEN(&this->fVoice,&base->fPosition,base->fLocation,
                             &base->fColour,base->fCar,&base->fDistance,&base->fPerpName);
  SPCH_PlaySpeech();
  ambulanceFlags = 0x20;

MobileCatch_requestEms:
  base->fAmbulance.flags = ambulanceFlags;
  SPCHNFS_C_D_REQUEST_EMS(&this->fVoice,&base->fAmbulance);
  SPCH_PlaySpeech();

MobileCatch_dispatchCallback:
  dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

  (dispatch)->ClearPerp(this->fPerp);
}

/* ---- RoadBlock__Q26Speech13MobileSpeaker  [SPEECH.CPP:2627-2648] SLD-VERIFIED ---- */
void MobileSpeaker::RoadBlock()
{
  Speaker *base = this;
  DispatchSpeaker *dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  Speaker *sub = dispatch->fSub;

  CallSignBank *callSign;

  if ((sub != 0) && (sub != base)) {

    (sub)->RoadBlock();
  }
  else {
    (base)->Promote();
    if (_6Speech_fgSpeech->fMultiplePerps == 0) {
      _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      SPCHNFS_C_D_REQ_RDBLK(&this->fVoice);
      SPCH_PlaySpeech();
    }
    base->fBlockade.flags = 2;
  }
}

/* ---- SpikeBelt__Q26Speech13MobileSpeaker  [SPEECH.CPP:2656-2677] SLD-VERIFIED ---- */
void MobileSpeaker::SpikeBelt()
{
  Speaker *base = this;
  DispatchSpeaker *dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();
  Speaker *sub = dispatch->fSub;

  CallSignBank *callSign;

  if ((sub != 0) && (sub != base)) {

    (sub)->SpikeBelt();
  }
  else {
    (base)->Promote();
    if (_6Speech_fgSpeech->fMultiplePerps == 0) {
      _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

      callSign = (CallSignBank *)(base)->CallSign();
      base->fTo = callSign->fDispatch;
      SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
      SPCH_PlaySpeech();
      SPCHNFS_C_D_REQ_SPBLT(&this->fVoice);
      SPCH_PlaySpeech();
    }
    base->fBlockade.flags = 1;
  }
}

/* ---- Backup__Q26Speech13MobileSpeaker  [SPEECH.CPP:2685-2705] SLD-VERIFIED ---- */
void MobileSpeaker::Backup()
{
  Speaker *base = this;

  CallSignBank *callSign;
  Car_tObj *car;

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

  callSign = (CallSignBank *)(base)->CallSign();
  base->fTo = callSign->fDispatch;
  SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
  SPCH_PlaySpeech();

  car = (Car_tObj *)(base)->Perp();
  (base)->SetCar(car);

  car = (Car_tObj *)(base)->CarObj();
  (base)->FindLocation(car);
  SPCHNFS_C_D_REQUEST_BKUP(&this->fVoice,&base->fColour,base->fCar,&base->fPosition,
                           base->fLocation,&base->fDistance);
  SPCH_PlaySpeech();
  base->fBlockade.flags = 0;
}

/* ---- Roger__Q26Speech13MobileSpeaker  [SPEECH.CPP:2711-2733] SLD-VERIFIED ---- */
void MobileSpeaker::Roger()
{
  Speaker *base = this;
  Speaker *sub = base->fSub;
  Speaker *statusSub = 0;
  DispatchSpeaker *dispatch;

  CallSignBank *callSign;
  Car_tObj *car;
  int unit;

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;
  if (sub != 0) {
    dispatch = (DispatchSpeaker *)(intptr)Speech_Dispatch();

    statusSub = (Speaker *)(dispatch)->StatusSub();
  }
  if ((sub != 0) && (statusSub == sub)) {
    SPCH_PlaySpeech();

    callSign = (CallSignBank *)(base)->CallSign();

    unit = (sub)->Unit();
    base->fTo = callSign->fMobile[unit];
    SPCHNFS_C_A_CONFIRM(&this->fVoice,base->fTo,&base->fConfirm);
    SPCH_PlaySpeech();

    car = (Car_tObj *)(base)->Perp();
    (base)->SetCar(car);
    SPCHNFS_C_C_IN_PURS_NEAR_PERP(&this->fVoice,&base->fColour,base->fCar);
  }
  else {

    callSign = (CallSignBank *)(base)->CallSign();
    base->fTo = callSign->fDispatch;
    SPCHNFS_C_A_CONFIRM(&this->fVoice,base->fTo,&base->fConfirm);
  }
  SPCH_PlaySpeech();
}

/* ---- Bullhorn__Q26Speech13MobileSpeaker  [SPEECH.CPP:2741-2748] SLD-VERIFIED ---- */
void MobileSpeaker::Bullhorn()
{
  SPCHNFSType_VOICE *VOICE;
  
  VOICE = &this->fVoice;
  *(Car_tObj **)(((int)_6Speech_fgSpeech) + 0x38c) = this->fCarObj;
  SPCHNFS_C_P_BULLHORN_SPEECH(VOICE);
  SPCH_PlaySpeech();
  return;
}

/* ---- Purge__Q26Speech13MobileSpeaker  [SPEECH.CPP:2754-2839] SLD-VERIFIED ---- */
void MobileSpeaker::Purge()
{
  bool bVar1;

  int iVar3;
  Speaker *pMVar4;
  Speaker *pMVar5;
  Car_tObj *car;
  DispatchSpeaker *dispatch;
  
  if (this->fCarObj == (Car_tObj *)0x0) {
    return;
  }

  car = this->CarObj();
  if ((car->carFlags & 0x200) == 0) {
    this->fCarObj = (Car_tObj *)0x0;
    dispatch = (DispatchSpeaker *)Speech_Dispatch();
    pMVar4 = dispatch->StatusSub();
    if (pMVar4 == this) {
      dispatch = (DispatchSpeaker *)Speech_Dispatch();
      dispatch->PurgeStatusSub();
    }
    pMVar4 = (Speaker *)Speech_Dispatch();
    do {
      pMVar5 = pMVar4->fSub;
      if (pMVar5 == this) {
        pMVar4->fSub = this->fSub;
        return;
      }
      pMVar4 = pMVar5;
    } while (pMVar5 != (Speaker *)0x0);
    return;
  }
  CopSpeak_Flush();
  if (CopSpeak_gSpchHandle != -1) {
    if (stackSpeedUpEnbabledFlag == 0) {
      SNDstop(CopSpeak_gSpchHandle);
    }
    else {
      gWSavePtr = (intptr)NFSHS_NativeStackHint((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 0;
      SNDstop(CopSpeak_gSpchHandle);
      gWSavePtr = (intptr)NFSHS_NativeStackHint((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 1;
    }
  }

  bVar1 = false;
  if (this->Perp() != 0) {
    iVar3 = AudioMus_Threshold();
    bVar1 = iVar3 != 0;
  }
  if (bVar1) {
    if (stackSpeedUpEnbabledFlag != 0) {
      gWSavePtr = (intptr)NFSHS_NativeStackHint((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 0;
      AudioMus_StopSong(500);
      AudioMus_PlaySong((char *)0x0);
      gWSavePtr = (intptr)NFSHS_NativeStackHint((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 1;
      this->fBlockade.flags = 0;
      goto Purge_resetSpeakerFields;
    }
    AudioMus_StopSong(500);
    AudioMus_PlaySong((char *)0x0);
  }
  this->fBlockade.flags = 0;
Purge_resetSpeakerFields:
  this->fArrest.flags = 0;
  this->fUpdate.flags = 0;
  this->fPerp = (Car_tObj *)0x0;
  this->fSub = (Speaker *)0x0;
  return;
}

/* ---- ReportBlockade__Q26Speech13MobileSpeaker  [SPEECH.CPP:2843-2861] SLD-VERIFIED ---- */
void MobileSpeaker::ReportBlockade()
{
  Speaker *base = this;

  CallSignBank *callSign;
  Car_tObj *car;

  _6Speech_fgSpeech->fSpeakerCar = this->fCarObj;

  callSign = (CallSignBank *)(base)->CallSign();
  base->fTo = callSign->fDispatch;

  car = (Car_tObj *)(base)->CarObj();
  (base)->FindLocation(car);
  base->fSpikeSide.flags = 4;
  if (base->fBlockade.flags == 2) {
    SPCHNFS_C_A_INTRO(&this->fVoice,base->fTo,base->fFrom,&base->fReverse);
    SPCH_PlaySpeech();
    SPCHNFS_W_D_RDBLK_PLC(&this->fVoice,&base->fPosition,base->fLocation,&base->fDistance);
  }
  else {
    SPCHNFS_W_D_SPBLT_PLC(&this->fVoice,&base->fPosition,&base->fSpikeSide,
                          base->fFrom,base->fLocation,&base->fDistance);
  }
  SPCH_PlaySpeech();
}

/* ---- Perp__Q26Speech13MobileSpeaker  [SPEECH.CPP:147-147] SLD-VERIFIED ---- */
Car_tObj * MobileSpeaker::Perp()
{
  return this->fPerp;
}

/* ---- Unit__Q26Speech13MobileSpeaker  [SPEECH.CPP:134-135] SLD-VERIFIED ---- */
int MobileSpeaker::Unit()
{
  return this->fUnit;
}

/* ---- CallSign__Q26Speech13MobileSpeaker  [SPEECH.CPP:130-135] SLD-FLAG:NONMONO ---- */
CallSignBank * MobileSpeaker::CallSign()
{
  return &_6Speech_fgSpeech->fCallSignBank.Mobile;
}

/* ---- FindClosestLocationTo__Q26Speech13MobileSpeakeri  [SPEECH.CPP:126-131] SLD-FLAG:NONMONO ---- */
LocationBank * MobileSpeaker::FindClosestLocationTo(int slice)
{
  LocationBank *pLVar1;
  (void)this;
  pLVar1 = (LocationBank *)_6Speech_fgSpeech->FindClosestLocationTo(_6Speech_fgSpeech->fLocationBank.Mobile,slice);
  return pLVar1;
}

/* ---- GetCarBank__Q26Speech13MobileSpeakeri  [SPEECH.CPP:122-127] SLD-FLAG:NONMONO ---- */
CarBank * MobileSpeaker::GetCarBank(int carIndex)
{
  return &_6Speech_fgSpeech->fCarBank.Mobile[carIndex];
}

/* ---- CarObj__Q26Speech13MobileSpeaker  [SPEECH.CPP:114-114] SLD-VERIFIED ---- */
Car_tObj * MobileSpeaker::CarObj()
{
  return this->fCarObj;
}

/* ---- IsSuper__Q26Speech13MobileSpeaker  [SPEECH.CPP:106-106] SLD-VERIFIED ---- */
void * MobileSpeaker::IsSuper()
{
  return (void *)((u_int)this->fCarObj->carFlags >> 6 & 1);
}

/* ---- CallSign__Q26Speech15DispatchSpeaker  [SPEECH.CPP:73-74] SLD-VERIFIED ---- */
CallSignBank * DispatchSpeaker::CallSign()
{
  return &_6Speech_fgSpeech->fCallSignBank.Dispatch;
}

/* ---- FindClosestLocationTo__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:69-74] SLD-FLAG:NONMONO ---- */
LocationBank * DispatchSpeaker::FindClosestLocationTo(int slice)
{
  LocationBank *pLVar1;
  (void)this;
  pLVar1 = (LocationBank *)_6Speech_fgSpeech->FindClosestLocationTo(_6Speech_fgSpeech->fLocationBank.Dispatch,slice)
  ;
  return pLVar1;
}

/* ---- GetCarBank__Q26Speech15DispatchSpeakeri  [SPEECH.CPP:65-70] SLD-FLAG:NONMONO ---- */
CarBank * DispatchSpeaker::GetCarBank(int carIndex)
{
  return &_6Speech_fgSpeech->fCarBank.Dispatch[carIndex];
}

/* ---- PurgeStatusSub__Q26Speech15DispatchSpeaker  [SPEECH.CPP:58-66] SLD-FLAG:NONMONO ---- */
void DispatchSpeaker::PurgeStatusSub()
{
  this->fStatusSub = (Speaker *)0x0;
  return;
}

/* ---- StatusSub__Q26Speech15DispatchSpeaker  [SPEECH.CPP:57-58] SLD-VERIFIED ---- */
Speaker * DispatchSpeaker::StatusSub()
{
  return this->fStatusSub;
}

/* ---- StatusCount__Q26Speech15DispatchSpeaker  [SPEECH.CPP:56-57] SLD-VERIFIED ---- */
int DispatchSpeaker::StatusCount()
{
  return this->fStatusCount;
}

/* ---- FindClosestLocationTo__Q26Speech7Speakeri  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
LocationBank * Speaker::FindClosestLocationTo(int slice)
{
  return (LocationBank *)0x0;
}

/* ---- GetCarBank__Q26Speech7Speakeri  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
CarBank * Speaker::GetCarBank(int carIndex)
{
  return (CarBank *)0x0;
}

/* ---- Perp__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
Car_tObj * Speaker::Perp()
{
  return (Car_tObj *)0x0;
}

/* ---- ReActivate__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker::ReActivate()
{
  return;
}

/* ---- CarObj__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
Car_tObj * Speaker::CarObj()
{
  return (Car_tObj *)0x0;
}

/* ---- DistToPerp__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
int Speaker::DistToPerp()
{
  return 0x3e80000;
}

/* ---- PurgeStatusSub__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker::PurgeStatusSub()
{
  return;
}

/* ---- StatusSub__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
Speaker * Speaker::StatusSub()
{
  return (Speaker *)0x0;
}

/* ---- StatusCount__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
int Speaker::StatusCount()
{
  return 0;
}

/* ---- IsSuper__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void * Speaker::IsSuper()
{
  return (void *)0x0;
}

/* ---- ClearPerp__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker::ClearPerp(Car_tObj *car)
{
  return;
}

/* ---- KnownPerp__Q26Speech7SpeakerP8Car_tObj  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void * Speaker::KnownPerp(Car_tObj *car)
{
  return (void *)0x0;
}

/* ---- Unit__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
int Speaker::Unit()
{
  return 0;
}

/* ---- Status__Q26Speech7Speaker  [SPEECH.CPP:?] SLD-FLAG:NO_SLD ---- */
void Speaker::Status()
{
  
  return;
}

/* base Speech::Speaker virtual not separately reconstructed (vtable-only ref, surfaced by #75
 * data-materialization); faithful from nfs4-f.exe @0x80099364 = { jr $ra; addiu $v0,$zero,0 } */
CallSignBank * Speaker::CallSign()
{
  return (CallSignBank *)0;
}
