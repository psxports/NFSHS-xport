/* game/psx/replay.cpp -- RECONSTRUCTED (NFS4 PSX replay record/playback system; C++ TU)
 *   6 fns: Scene_Init/DeInit/PurgeScene/BuildCustomSceneList/LoadSceneFile + GetPlaneY.
 *   GTE-free. Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "replay_externs.h"

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
char * Replay_Compress(char *uncompressed_data);
char * Replay_Decompress(char *compressed_data);
extern "C" { void Replay_InitReplay(void); }
extern "C" { void Replay_ResetReplay(void); }
extern "C" { void Replay_StoringReplay(void); }
void Replay_StoringControllerData(tControllerData controllerdata);
tControllerData Replay_RetreivingControllerData(void);
void Replay_SaveInput(int car);
void Replay_GetInput(int car);
void Replay_SaveReplay(void);
void Replay_LoadReplay(void);
void Replay_DoReplay(Car_tObj *carObj);
void Replay_GetInterfaceKey(void);
void Replay_LoadCameraFile(void);
void Replay_ReplayChooseCamera(int player,int slice);
void Replay_ReplayFindClosestCamera(int player,int slice);


/* ---- Replay_Compress__FPc  [REPLAY.CPP:72-121] SLD-VERIFIED ---- */
char * Replay_Compress(char *uncompressed_data)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int c_pointer;
  char *pcVar6;
  
  bVar2 = false;
  c_pointer = 1;
  pcVar5 = compressed_data + 1;
  pcVar6 = uncompressed_data + 0x20;
  do {
    cVar1 = *uncompressed_data;
    iVar4 = 0;
    do {
      uncompressed_data = uncompressed_data + 1;
      iVar4 = iVar4 + 1;
      if (*uncompressed_data != cVar1) break;
    } while (uncompressed_data < pcVar6);
    if (iVar4 < 3) {
      iVar3 = 0;
      if (0 < iVar4) {
        do {
          *pcVar5 = cVar1;
          pcVar5 = pcVar5 + 1;
          iVar3 = iVar3 + 1;
          c_pointer = c_pointer + 1;
        } while (iVar3 < iVar4);
      }
    }
    else {
      *pcVar5 = -1;
      pcVar5 = pcVar5 + 3;
      compressed_data[c_pointer + 1] = (char)iVar4;
      compressed_data[c_pointer + 2] = cVar1;
      c_pointer = c_pointer + 3;
    }
    if (pcVar6 <= uncompressed_data) {
      bVar2 = true;
    }
    if (bVar2) {
      compressed_data[0] = (char)c_pointer;
      compressed_data[c_pointer] = '\0';
      return compressed_data;
    }
  } while( true );
}

/* ---- Replay_Decompress__FPc  [REPLAY.CPP:127-161] SLD-VERIFIED ---- */
char * Replay_Decompress(char *compressed_data)

{
  u_char bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int data_size;
  
  data_size = (int)(u_char)*compressed_data;
  iVar5 = 1;
  if (1 < (u_int)data_size) {
    pcVar3 = compressed_data + 1;
    pcVar4 = uncompressed_data;
    do {
      if (*pcVar3 == -1) {
        bVar1 = pcVar3[1];
        iVar2 = 0;
        if (bVar1 != 0) {
          do {
            iVar2 = iVar2 + 1;
            *pcVar4 = pcVar3[2];
            pcVar4 = pcVar4 + 1;
          } while (iVar2 < (int)(u_int)bVar1);
        }
        pcVar3 = pcVar3 + 3;
        iVar5 = iVar5 + 3;
      }
      else {
        *pcVar4 = *pcVar3;
        pcVar4 = pcVar4 + 1;
        pcVar3 = pcVar3 + 1;
        iVar5 = iVar5 + 1;
      }
    } while (iVar5 < data_size);
  }
  return uncompressed_data;
}

/* ---- Replay_InitReplay__Fv  [REPLAY.CPP:169-194] SLD-VERIFIED ---- */
extern "C" void Replay_InitReplay(void)

{
  GameSetup_tUserSetting *pGVar1;
  GameSetup_tData *pGVar2;
  tReplayBuffer *ptVar3;
  tReplayBuffer *ptVar4;
  GameSetup_tUserSetting *pGVar5;
  GameSetup_tData *pGVar6;
  GameSetup_tUserSetting *pGVar7;
  GameSetup_tUserSetting *pGVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  GameSetup_tUserSetting temp;
  
  Replay_ReplayMode = GameSetup_gData.replayMode;
  Replay_LoadCameraFile();
  if (Replay_ReplayMode == 2) {
    pGVar1 = &GameSetup_gData.userSetting;
    pGVar8 = &temp;
    do {
      pGVar7 = pGVar8;
      pGVar5 = pGVar1;
      iVar9 = pGVar5->display;
      iVar10 = pGVar5->bestlap;
      iVar11 = pGVar5->audioMode;
      pGVar7->language = pGVar5->language;
      pGVar7->display = iVar9;
      pGVar7->bestlap = iVar10;
      pGVar7->audioMode = iVar11;
      pGVar1 = (GameSetup_tUserSetting *)&pGVar5->musicLevel;
      pGVar8 = (GameSetup_tUserSetting *)&pGVar7->musicLevel;
    } while (&pGVar5->musicLevel != GameSetup_gData.userSetting.playlist + 0x25);
    iVar9 = pGVar5->sfxLevel;
    iVar10 = pGVar5->engineLevel;
    pGVar7->musicLevel = GameSetup_gData.userSetting.playlist[0x25];
    pGVar7->sfxLevel = iVar9;
    pGVar7->engineLevel = iVar10;
    Replay_LoadReplay();
    ptVar4 = &Replay_ReplayBuffer;
    pGVar2 = &GameSetup_gData;
    do {
      pGVar6 = pGVar2;
      ptVar3 = ptVar4;
      iVar9 = (ptVar3->gameSetup).numLaps;
      iVar10 = (ptVar3->gameSetup).skill;
      iVar11 = (ptVar3->gameSetup).commMode;
      pGVar6->raceType = (ptVar3->gameSetup).raceType;
      pGVar6->numLaps = iVar9;
      pGVar6->skill = iVar10;
      pGVar6->commMode = iVar11;
      ptVar4 = (tReplayBuffer *)&(ptVar3->gameSetup).tournamentMultiplier;
      pGVar2 = (GameSetup_tData *)&pGVar6->tournamentMultiplier;
    } while (ptVar4 != (tReplayBuffer *)(Replay_ReplayBuffer.gameSetup.carInfo[8].Camera + 2));
    iVar9 = (ptVar3->gameSetup).cops;
    pGVar6->tournamentMultiplier = Replay_ReplayBuffer.gameSetup.carInfo[8].Camera[2];
    pGVar6->cops = iVar9;
    pGVar1 = &GameSetup_gData.userSetting;
    pGVar8 = &temp;
    do {
      pGVar7 = pGVar8;
      pGVar5 = pGVar1;
      iVar9 = pGVar7->display;
      iVar10 = pGVar7->bestlap;
      iVar11 = pGVar7->audioMode;
      pGVar5->language = pGVar7->language;
      pGVar5->display = iVar9;
      pGVar5->bestlap = iVar10;
      pGVar5->audioMode = iVar11;
      pGVar8 = (GameSetup_tUserSetting *)&pGVar7->musicLevel;
      pGVar1 = (GameSetup_tUserSetting *)&pGVar5->musicLevel;
    } while (pGVar8 != (GameSetup_tUserSetting *)(temp.playlist + 0x25));
    iVar9 = pGVar7->sfxLevel;
    iVar10 = pGVar7->engineLevel;
    pGVar5->musicLevel = *(int *)pGVar8;
    pGVar5->sfxLevel = iVar9;
    pGVar5->engineLevel = iVar10;
    Replay_ReplayGetPtr = 0;
    Replay_Size = Replay_ReplayBuffer.size;
  }
  else {
    pGVar2 = &GameSetup_gData;
    ptVar4 = &Replay_ReplayBuffer;
    do {
      ptVar3 = ptVar4;
      pGVar6 = pGVar2;
      iVar9 = pGVar6->numLaps;
      iVar10 = pGVar6->skill;
      iVar11 = pGVar6->commMode;
      (ptVar3->gameSetup).raceType = pGVar6->raceType;
      (ptVar3->gameSetup).numLaps = iVar9;
      (ptVar3->gameSetup).skill = iVar10;
      (ptVar3->gameSetup).commMode = iVar11;
      ptVar4 = (tReplayBuffer *)&(ptVar3->gameSetup).tournamentMultiplier;
      pGVar2 = (GameSetup_tData *)&pGVar6->tournamentMultiplier;
    } while (&pGVar6->tournamentMultiplier != GameSetup_gData.carInfo[8].Camera + 2);
    iVar9 = pGVar6->cops;
    *(int *)ptVar4 = GameSetup_gData.carInfo[8].Camera[2];
    (ptVar3->gameSetup).cops = iVar9;
  }
  return;
}

/* ---- Replay_ResetReplay__Fv  [REPLAY.CPP:202-264] SLD-VERIFIED ---- */
extern "C" void Replay_ResetReplay(void)

{
  int iVar1;
  int *piVar2;
  int cam_idx;
  int iVar3;
  tReplayCameraModes *cam_walk;
  Car_tObj **car_walk;
  
  if ((u_int)Replay_ReplayMode < 2) {
    cam_idx = 0x5fff;
    do {
      Replay_ReplayBuffer.buffer[cam_idx] = 0;
      cam_idx = cam_idx + -1;
    } while (-1 < cam_idx);
    Replay_ReplayStorePtr = 0;
    Replay_ReplayGetPtr = 0;
  }
  else if (1 < Replay_ReplayMode) {
    iVar3 = 0;
    cam_walk = Replay_ReplayCamera;
    car_walk = Cars_gHumanRaceCarList;
    Replay_ReplayInterface.pause = 0;
    Replay_ReplayInterface.speed = 2;
    Replay_ReplayGetPtr = 0;
    Replay_ReplayInterface.end = 0;
    Replay_ReplayInterface.camera = 0;
    Replay_ReplayInterface.selection = 4;
    Replay_ReplayInterface.depressed = 0;
    Replay_ReplayInterface.changeCamera = 0;
    do {
      if (numValidCams == 0) {
        iVar1 = 4;
      }
      else {
        if ((GameSetup_gData.commMode == 1) || (iVar3 == 0)) {
          Replay_ReplayFindClosestCamera(iVar3,(int)((*car_walk)->N).simRoadInfo.slice);
        }
        iVar1 = 0x13;
      }
      cam_walk->cameraMode = iVar1;
      cam_walk->cutToNextCamera = 0;
      cam_walk = cam_walk + 1;
      iVar3 = iVar3 + 1;
      car_walk = car_walk + 1;
    } while (iVar3 < 2);
  }
  iVar3 = 1;
  piVar2 = Replay_ReplayCounter + 1;
  do {
    *piVar2 = 0;
    iVar3 = iVar3 + -1;
    piVar2 = piVar2 + -1;
  } while (-1 < iVar3);
  StatsTimer[0] = 0;
  StatsTimer[1] = 0;
  return;
}

/* ---- Replay_StoringReplay__Fv  [REPLAY.CPP:270-275] SLD-VERIFIED ---- */
extern "C" void Replay_StoringReplay(void)

{
  Replay_SaveReplay();
  numValidCams = 0;
  return;
}

/* ---- Replay_StoringControllerData__FG15tControllerData  [REPLAY.CPP:283-307] SLD-VERIFIED ---- */
void Replay_StoringControllerData(tControllerData controllerdata)

{
  char packeddata[33];
  char *compressed;

  if (Replay_ReplayStorePtr + 0x80 < 0x6000) {
    compressed = Replay_Compress(controllerdata.steering);
    nfs4_mips_copy_bytes(packeddata,compressed,33);
    memcpy(Replay_ReplayBuffer.buffer + Replay_ReplayStorePtr,packeddata,
           (u_int)(u_char)packeddata[0]);
    Replay_ReplayStorePtr += (u_int)(u_char)packeddata[0];

    compressed = Replay_Compress((char *)controllerdata.gas);
    nfs4_mips_copy_bytes(packeddata,compressed,33);
    memcpy(Replay_ReplayBuffer.buffer + Replay_ReplayStorePtr,packeddata,
           (u_int)(u_char)packeddata[0]);
    Replay_ReplayStorePtr += (u_int)(u_char)packeddata[0];

    compressed = Replay_Compress((char *)controllerdata.brake);
    nfs4_mips_copy_bytes(packeddata,compressed,33);
    memcpy(Replay_ReplayBuffer.buffer + Replay_ReplayStorePtr,packeddata,
           (u_int)(u_char)packeddata[0]);
    Replay_ReplayStorePtr += (u_int)(u_char)packeddata[0];

    compressed = Replay_Compress((char *)controllerdata.states);
    nfs4_mips_copy_bytes(packeddata,compressed,33);
    memcpy(Replay_ReplayBuffer.buffer + Replay_ReplayStorePtr,packeddata,
           (u_int)(u_char)packeddata[0]);
    Replay_ReplayStorePtr += (u_int)(u_char)packeddata[0];
  }
  else {
    Replay_ReplayMode = 1;
    Replay_Size = simGlobal.gameTicks;
  }
  return;
}

/* ---- Replay_RetreivingControllerData__Fv  [REPLAY.CPP:314-335] SLD-VERIFIED ---- */
tControllerData Replay_RetreivingControllerData(void)

{
  tControllerData controllerdata;
  char packeddata[33];
  char *decompressed;

  memcpy(packeddata,Replay_ReplayBuffer.buffer + Replay_ReplayGetPtr,
         (u_int)(u_char)Replay_ReplayBuffer.buffer[Replay_ReplayGetPtr]);
  decompressed = Replay_Decompress(packeddata);
  nfs4_mips_copy_bytes(controllerdata.steering,decompressed,32);
  Replay_ReplayGetPtr += (u_int)(u_char)packeddata[0];

  memcpy(packeddata,Replay_ReplayBuffer.buffer + Replay_ReplayGetPtr,
         (u_int)(u_char)Replay_ReplayBuffer.buffer[Replay_ReplayGetPtr]);
  decompressed = Replay_Decompress(packeddata);
  nfs4_mips_copy_bytes(controllerdata.gas,decompressed,32);
  Replay_ReplayGetPtr += (u_int)(u_char)packeddata[0];

  memcpy(packeddata,Replay_ReplayBuffer.buffer + Replay_ReplayGetPtr,
         (u_int)(u_char)Replay_ReplayBuffer.buffer[Replay_ReplayGetPtr]);
  decompressed = Replay_Decompress(packeddata);
  nfs4_mips_copy_bytes(controllerdata.brake,decompressed,32);
  Replay_ReplayGetPtr += (u_int)(u_char)packeddata[0];

  memcpy(packeddata,Replay_ReplayBuffer.buffer + Replay_ReplayGetPtr,
         (u_int)(u_char)Replay_ReplayBuffer.buffer[Replay_ReplayGetPtr]);
  decompressed = Replay_Decompress(packeddata);
  nfs4_mips_copy_bytes(controllerdata.states,decompressed,32);
  Replay_ReplayGetPtr += (u_int)(u_char)packeddata[0];
  return controllerdata;
}

/* ---- Replay_SaveInput__Fi  [REPLAY.CPP:342-364] SLD-VERIFIED ---- */
void Replay_SaveInput(int car)

{
  int iVar1;
  int steer_q;
  int *ctr_ptr;
  Car_tObj **car_walk;
  
  Input_Fetch(car);
  ctr_ptr = Replay_ReplayCounter + car;
  steer_q = (int)Input_gSim.steering;
  if (steer_q < 0) {
    steer_q = steer_q + 3;
  }
  controlData[car].steering[*ctr_ptr] = (char)(steer_q >> 2) + '@';
  controlData[car].gas[*ctr_ptr] = Input_gSim.gas >> 3;
  controlData[car].brake[*ctr_ptr] = Input_gSim.brake >> 3;
  controlData[car].states[*ctr_ptr] = Input_gSim.flags;
  car_walk = Cars_gHumanRaceCarList + car;
  if ((*car_walk)->carInfo->RampSteering != 0) {
    controlData[car].steering[*ctr_ptr] = controlData[car].steering[*ctr_ptr] | 0x80;
  }
  if ((*car_walk)->carInfo->RampGas != 0) {
    controlData[car].gas[*ctr_ptr] = controlData[car].gas[*ctr_ptr] | 0x80;
  }
  if ((*car_walk)->carInfo->RampBrake != 0) {
    controlData[car].brake[*ctr_ptr] = controlData[car].brake[*ctr_ptr] | 0x80;
  }
  iVar1 = *ctr_ptr;
  *ctr_ptr = iVar1 + 1;
  if (iVar1 + 1 == 0x20) {
    *ctr_ptr = 0;
    Replay_StoringControllerData(controlData[car]);
  }
  return;
}

/* ---- Replay_GetInput__Fi  [REPLAY.CPP:371-441] SLD-VERIFIED ---- */
void Replay_GetInput(int car)

{
  bool bVar1;
  int *piVar2;
  
  Input_Fetch(car);
  if (Replay_ReplayCounter[car] == 0) {
    if (Replay_ReplayBuffer.buffer[Replay_ReplayGetPtr] == '\0') {
      Replay_ReplayMode = 3;
    }
    else {
      controlData[car] = Replay_RetreivingControllerData();
    }
  }
  if (Replay_ReplayMode == 2) {
    if (((int)controlData[car].steering[Replay_ReplayCounter[car]] & 0x80U) == 0) {
      Cars_gHumanRaceCarList[car]->carInfo->RampSteering = 0;
    }
    else {
      Cars_gHumanRaceCarList[car]->carInfo->RampSteering = 1;
    }
    if ((controlData[car].gas[Replay_ReplayCounter[car]] & 0x80) == 0) {
      Cars_gHumanRaceCarList[car]->carInfo->RampGas = 0;
    }
    else {
      Cars_gHumanRaceCarList[car]->carInfo->RampGas = 1;
    }
    if ((controlData[car].brake[Replay_ReplayCounter[car]] & 0x80) == 0) {
      Cars_gHumanRaceCarList[car]->carInfo->RampBrake = 0;
    }
    else {
      Cars_gHumanRaceCarList[car]->carInfo->RampBrake = 1;
    }
    piVar2 = Replay_ReplayCounter + car;
    controlData[car].steering[*piVar2] = controlData[car].steering[*piVar2] & 0x7f;
    controlData[car].gas[*piVar2] = controlData[car].gas[*piVar2] & 0x7f;
    controlData[car].brake[*piVar2] = controlData[car].brake[*piVar2] & 0x7f;
    Input_gSim.steering = controlData[car].steering[*piVar2] * '\x04';
    Input_gSim.gas = controlData[car].gas[*piVar2] << 3;
    Input_gSim.brake = controlData[car].brake[*piVar2] << 3;
    Input_gSim.flags = controlData[car].states[*piVar2];
  }
  else if (Replay_ReplayMode == 3) {
    Input_gSim.steering = '\0';
    Input_gSim.gas = '\0';
    Input_gSim.brake = '\0';
    Input_gSim.flags = '\0';
  }
  bVar1 = numValidCams != 0;
  Replay_ReplayCounter[car] = Replay_ReplayCounter[car] + 1;
  if (((bVar1) && (Replay_ReplayCamera[car].cameraMode == 0x13)) && (simGlobal.gameStarted != 0)) {
    Replay_ReplayChooseCamera(car,(int)(Cars_gHumanRaceCarList[car]->N).simRoadInfo.slice);
  }
  if (Replay_ReplayCounter[car] == 0x20) {
    Replay_ReplayCounter[car] = 0;
  }
  return;
}

/* ---- Replay_SaveReplay__Fv  [REPLAY.CPP:447-453] SLD-VERIFIED ---- */
void Replay_SaveReplay(void)

{
  GameSetup_tData *pGVar1;
  GameSetup_tData *pGVar2;
  tReplayBuffer *ptVar3;
  tReplayBuffer *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if (Replay_ReplayMode == 0) {
    Replay_Size = simGlobal.gameTicks;
  }
  pGVar1 = &GameSetup_gData;
  ptVar4 = &Replay_ReplayBuffer;
  do {
    ptVar3 = ptVar4;
    pGVar2 = pGVar1;
    iVar5 = pGVar2->numLaps;
    iVar6 = pGVar2->skill;
    iVar7 = pGVar2->commMode;
    (ptVar3->gameSetup).raceType = pGVar2->raceType;
    (ptVar3->gameSetup).numLaps = iVar5;
    (ptVar3->gameSetup).skill = iVar6;
    (ptVar3->gameSetup).commMode = iVar7;
    ptVar4 = (tReplayBuffer *)&(ptVar3->gameSetup).tournamentMultiplier;
    pGVar1 = (GameSetup_tData *)&pGVar2->tournamentMultiplier;
  } while (&pGVar2->tournamentMultiplier != GameSetup_gData.carInfo[8].Camera + 2);
  iVar5 = pGVar2->cops;
  *(int *)ptVar4 = GameSetup_gData.carInfo[8].Camera[2];
  (ptVar3->gameSetup).cops = iVar5;
  Replay_ReplayBuffer.gameSetup.replayMode = 2;
  Replay_ReplayBuffer.size = Replay_Size;
  return;
}

/* ---- Replay_LoadReplay__Fv  [REPLAY.CPP:469-492] SLD-VERIFIED ---- */
void Replay_LoadReplay(void)

{
  return;
}

/* ---- Replay_DoReplay__FP8Car_tObj  [REPLAY.CPP:498-506] SLD-VERIFIED ---- */
void Replay_DoReplay(Car_tObj *carObj)

{
  if ((u_int)Replay_ReplayMode < 2) {
    Replay_SaveInput(carObj->humanIndex);
  }
  else {
    Replay_GetInput(carObj->humanIndex);
  }
  return;
}

/* ---- Replay_GetInterfaceKey__Fv  [REPLAY.CPP:516-647] SLD-VERIFIED ---- */
void Replay_GetInterfaceKey(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Car_tObj **ppCVar4;
  camera_info *pcVar5;
  tReplayCameraModes *ptVar6;
  int iVar7;
  
  iVar7 = 1;
  if (GameSetup_gData.commMode == 1) {
    iVar7 = 2;
  }
  Replay_ReplayInterface.changeCamera = 0;
  if (Replay_ReplayInterface.depressed < 1) {
    if (Replay_ReplayInterface.statsScreen == 0) {
      iVar2 = Input_Interface(3,1);
      if (iVar2 == 0) {
        iVar2 = Input_Interface(4,1);
        if (iVar2 == 0) {
          iVar2 = Input_Interface(5,1);
          if (iVar2 == 0) {
            iVar7 = Input_Interface(6,1);
            if (iVar7 == 0) {
              iVar7 = Input_Interface(0x19,1);
              if (iVar7 != 0) {
                StatsTimer[0] = 0;
                StatsTimer[1] = 0;
                Replay_ReplayInterface.statsScreen = 1;
                AudioCmn_PlayPauseSound(4);
              }
            }
            else {
              Replay_ReplayInterface.depressed = 8;
              Replay_ReplayInterface.end = 1;
            }
          }
          else {
            AudioCmn_PlayPauseSound(4);
            Replay_ReplayInterface.depressed = 8;
            switch(Replay_ReplayInterface.selection) {
            case 0:
              Replay_ReplayInterface.end = 1;
              GameSetup_gData.instantReplay = 1;
              break;
            case 1:
              Replay_ReplayInterface.end = 1;
              break;
            case 2:
              Replay_ReplayInterface.pause = Replay_ReplayInterface.pause ^ 1;
              break;
            case 3:
              if (GameSetup_gData.commMode == 1) {
                Replay_ReplayInterface.speed = (Replay_ReplayInterface.speed + 1) % 3;
              }
              else {
                iVar2 = Replay_ReplayInterface.speed + 1;
                iVar7 = iVar2;
                if (iVar2 < 0) {
                  iVar7 = Replay_ReplayInterface.speed + 4;
                }
                Replay_ReplayInterface.speed = iVar2 + (iVar7 >> 2) * -4;
              }
              break;
            case 4:
              Replay_ReplayInterface.changeCamera = 1;
              Replay_ReplayInterface.camera = (Replay_ReplayInterface.camera + 1) % 9;
              if (ReplayCameraList[Replay_ReplayInterface.camera] == 0x13) {
                iVar2 = 0;
                if (iVar7 != 0) {
                  ptVar6 = Replay_ReplayCamera;
                  ppCVar4 = Cars_gHumanRaceCarList;
                  pcVar5 = Camera_gInfo;
                  do {
                    if (numValidCams == 0) {
                      Camera_SetMode(iVar2,10);
                    }
                    else {
                      pcVar5->anchor = &(*ppCVar4)->N;
                      pcVar5->target = &(*ppCVar4)->N;
                      Replay_ReplayFindClosestCamera(iVar2,(int)((*ppCVar4)->N).simRoadInfo.slice);
                      ptVar6->cameraMode = 0x13;
                    }
                    ptVar6 = ptVar6 + 1;
                    ppCVar4 = ppCVar4 + 1;
                    iVar2 = iVar2 + 1;
                    pcVar5 = pcVar5 + 1;
                  } while (iVar2 < iVar7);
                }
              }
              else if (iVar7 != 0) {
                ppCVar4 = Cars_gHumanRaceCarList;
                pcVar5 = Camera_gInfo;
                ptVar6 = Replay_ReplayCamera;
                iVar2 = 0;
                do {
                  ptVar6->defaultCamera = 0;
                  pcVar5->twist = 0;
                  pcVar5->anchor = &(*ppCVar4)->N;
                  pcVar5->target = &(*ppCVar4)->N;
                  iVar3 = iVar2 + 1;
                  Camera_SetMode(iVar2,ReplayCameraList[Replay_ReplayInterface.camera])
                  ;
                  ppCVar4 = ppCVar4 + 1;
                  pcVar5 = pcVar5 + 1;
                  ptVar6->cameraMode = ReplayCameraList[Replay_ReplayInterface.camera];
                  ptVar6 = ptVar6 + 1;
                  iVar2 = iVar3;
                } while (iVar3 < iVar7);
              }
            }
          }
        }
        else {
          AudioCmn_PlayPauseSound(3);
          Replay_ReplayInterface.selection = (Replay_ReplayInterface.selection + 1) % 5;
        }
      }
      else {
        AudioCmn_PlayPauseSound(3);
        bVar1 = Replay_ReplayInterface.selection == 0;
        Replay_ReplayInterface.selection = Replay_ReplayInterface.selection + -1;
        if (bVar1) {
          Replay_ReplayInterface.selection = 4;
        }
      }
    }
    else {
      bVar1 = false;
      iVar7 = Input_Interface(5,1);
      if ((iVar7 != 0) || (iVar7 = Input_Interface(6,1), iVar7 != 0)) {
        bVar1 = true;
      }
      if (bVar1) {
        Replay_ReplayInterface.depressed = 0x18;
        Replay_ReplayInterface.end = 1;
      }
      else {
        iVar7 = Input_Interface(0x19,1);
        if (iVar7 != 0) {
          AudioCmn_PlayPauseSound(4);
          Replay_ReplayInterface.statsScreen = 0;
        }
      }
    }
  }
  else {
    Replay_ReplayInterface.depressed = Replay_ReplayInterface.depressed + -1;
  }
  if (simVar.quickPauseSim != 0) {
    Camera_Update();
  }
  return;
}

/* ---- Replay_LoadCameraFile__Fv  [REPLAY.CPP:665-785] SLD-VERIFIED ---- */
void Replay_LoadCameraFile(void)

{
  short sVar1;
  short sVar2;
  int *addr;
  u_int uVar3;
  Camera_tCamSlot *pCVar4;
  int *piVar5;
  int iVar6;
  const char *fmt;
  int tu7;
  int tu8;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int tu14;
  int iVar13;
  int tu16;
  int iVar14;
  int iVar15;
  int tu19;
  int iVar16;
  int tu21;
  char fname [80];
  int bigFile;
  
  if (numValidCams == 0) {
    bigFile = 0;
    sprintf(fname,"%scamera.viv",Paths_Paths[8]);
    piVar5 = &bigFile;
    FILE_addbigsync(fname,0x10,100,piVar5);
    if (GameSetup_gData.reverseTrack == 0) {
      fmt = "tr%02d.rho";
    }
    else {
      fmt = "tr%02dr.rho";
    }
    iVar6 = GameSetup_gData.track;
    sprintf(fname,fmt,GameSetup_gData.track);
    addr = (int *)loadfileadrz(fname,0);
    numValidCams = 0;
    FILE_delbigsync(bigFile,0x64);
    iVar6 = 0;
    pCVar4 = gReplayCameraSlots;
    do {
      pCVar4->mode = '\x02';
      ((u_char *)&(uVar3))[0] = pCVar4->mode;
      ((u_char *)&(uVar3))[1] = ((char *)(pCVar4))[0x1];
      (*(u_short *)((u_char *)&(uVar3) + 2)) = pCVar4->fov;
      iVar6 = iVar6 + 1;
      pCVar4->slice = -1;
      uVar3 = uVar3 & 0xfffff9ff;
      pCVar4->mode = (char)uVar3;
      ((char *)(pCVar4))[0x1] = (char)(uVar3 >> 8);
      pCVar4->fov = (short)(uVar3 >> 0x10);
      pCVar4 = pCVar4 + 1;
    } while (iVar6 < 0x20);
    if (addr != (int *)0x0) {
      pCVar4 = gReplayCameraSlots;
      piVar5 = addr;
      do {
        tu7 = *piVar5;
        iVar6 = piVar5[1];
        iVar11 = piVar5[2];
        iVar14 = piVar5[3];
        pCVar4->mode = (char)tu7;
        ((char *)(pCVar4))[0x1] = (char)((u_int)tu7 >> 8);
        pCVar4->fov = (short)((u_int)tu7 >> 0x10);
        (pCVar4->pos).x = iVar6;
        (pCVar4->pos).y = iVar11;
        (pCVar4->pos).z = iVar14;
        piVar5 = piVar5 + 4;
        pCVar4 = (Camera_tCamSlot *)&pCVar4->height;
      } while (piVar5 != addr + 0x100);
      iVar6 = 0;
      pCVar4 = gReplayCameraSlots;
      do {
        if (pCVar4->fov == 0) {
          pCVar4->slice = -1;
        }
        else {
          numValidCams = numValidCams + 1;
        }
        pCVar4 = pCVar4 + 1;
        iVar6 = iVar6 + 1;
      } while (iVar6 < 0x20);
      purgememadr(addr);
      for (iVar6 = 0; iVar11 = 0, iVar6 < 0x1f; iVar6 = iVar6 + 1) {
        iVar14 = 0x20;
        pCVar4 = gReplayCameraSlots;
        for (; iVar11 < 0x1f; iVar11 = iVar11 + 1) {
          sVar1 = *(short *)((int)&gReplayCameraSlots[0].slice + iVar14);
          if (((sVar1 < pCVar4->slice) || (pCVar4->slice < 0)) && (-1 < sVar1)) {
            tu8 = *(int *)pCVar4;
            iVar8 = (pCVar4->pos).x;
            iVar12 = (pCVar4->pos).y;
            iVar15 = (pCVar4->pos).z;
            iVar7 = pCVar4->height;
            iVar9 = pCVar4->splineOffset;
            tu14 = *(int *)&pCVar4->euler;
            tu19 = *(int *)&(pCVar4->euler).z;
            iVar10 = *(int *)((int)&gReplayCameraSlots[0].pos.x + iVar14);
            iVar13 = *(int *)((int)&gReplayCameraSlots[0].pos.y + iVar14);
            iVar16 = *(int *)((int)&gReplayCameraSlots[0].pos.z + iVar14);
            *(u_int *)pCVar4 = *(u_int *)(&gReplayCameraSlots[0].mode + iVar14);
            (pCVar4->pos).x = iVar10;
            (pCVar4->pos).y = iVar13;
            (pCVar4->pos).z = iVar16;
            iVar10 = *(int *)((int)&gReplayCameraSlots[0].splineOffset + iVar14);
            tu16 = *(int *)((int)&gReplayCameraSlots[0].euler.x + iVar14);
            tu21 = *(int *)((int)&gReplayCameraSlots[0].euler.z + iVar14);
            pCVar4->height = *(int *)((int)&gReplayCameraSlots[0].height + iVar14);
            pCVar4->splineOffset = iVar10;
            (pCVar4->euler).x = (short)tu16;
            (pCVar4->euler).y = (short)((u_int)tu16 >> 0x10);
            *(int *)&(pCVar4->euler).z = tu21;
            *(int *)(&gReplayCameraSlots[0].mode + iVar14) = tu8;
            *(int *)((int)&gReplayCameraSlots[0].pos.x + iVar14) = iVar8;
            *(int *)((int)&gReplayCameraSlots[0].pos.y + iVar14) = iVar12;
            *(int *)((int)&gReplayCameraSlots[0].pos.z + iVar14) = iVar15;
            *(int *)((int)&gReplayCameraSlots[0].height + iVar14) = iVar7;
            *(int *)((int)&gReplayCameraSlots[0].splineOffset + iVar14) = iVar9;
            *(int *)((int)&gReplayCameraSlots[0].euler.x + iVar14) = tu14;
            *(int *)((int)&gReplayCameraSlots[0].euler.z + iVar14) = tu19;
          }
          pCVar4 = pCVar4 + 1;
          iVar14 = iVar14 + 0x20;
        }
      }
      if (GameSetup_gData.reverseTrack != 0) {
        iVar6 = numValidCams + -1;
        pCVar4 = gReplayCameraSlots + iVar6;
        sVar1 = gReplayCameraSlots[iVar6].slice;
        iVar11 = iVar6 * 0x20;
        for (; -1 < iVar6; iVar6 = iVar6 + -1) {
          sVar2 = sVar1;
          if (iVar6 != 0) {
            pCVar4->slice = *(short *)(uncompressed_data + iVar11 + 0x1e);
            sVar2 = gReplayCameraSlots[0].slice;
          }
          gReplayCameraSlots[0].slice = sVar2;
          pCVar4 = pCVar4 + -1;
          iVar11 = iVar11 + -0x20;
        }
      }
      iVar6 = numValidCams;
      iVar11 = 0;
      if (0 < numValidCams) {
        pCVar4 = gReplayCameraSlots;
        do {
          iVar11 = iVar11 + 1;
          (pCVar4->pos).x = (pCVar4->pos).x << 6;
          (pCVar4->pos).z = (pCVar4->pos).z << 6;
          (pCVar4->pos).y = (pCVar4->pos).y << 6;
          pCVar4 = pCVar4 + 1;
        } while (iVar11 < iVar6);
      }
    }
  }
  return;
}

/* ---- Replay_ReplayChooseCamera__Fii  [REPLAY.CPP:797-833] SLD-VERIFIED ---- */
void Replay_ReplayChooseCamera(int player,int slice)

{
  int iVar1;
  Camera_tCamSlot *pCVar2;
  u_int uVar3;
  u_int uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar9 = Replay_ReplayCamera[player].cutToNextCamera;
  iVar7 = iVar9 + -1;
  if (iVar7 < 0) {
    iVar7 = numValidCams + -1;
  }
  iVar8 = 0;
  if (iVar9 + 1 < numValidCams) {
    iVar8 = iVar9 + 1;
  }
  iVar6 = (int)gReplayCameraSlots[iVar9].slice;
  iVar5 = (int)gReplayCameraSlots[iVar8].slice;
  iVar1 = slice - iVar6;
  if (slice < iVar6) {
    if (iVar1 < 1) {
      iVar1 = iVar6 - slice;
    }
    if (iVar1 < 200) {
      Replay_ReplayCamera[player].cutToNextCamera = iVar7;
      goto ReplayChooseCam_cutCheck;
    }
  }
  if (iVar5 <= slice) {
    iVar7 = slice - iVar5;
    if (iVar7 < 1) {
      iVar7 = iVar5 - slice;
    }
    if (iVar7 < 200) {
      Replay_ReplayCamera[player].cutToNextCamera = iVar8;
    }
  }
ReplayChooseCam_cutCheck:
  if (Replay_ReplayCamera[player].cutToNextCamera != iVar9) {
    if (((((GameSetup_gData.raceType == 1) || (GameSetup_gData.raceType == 5)) &&
         (((Cars_gHumanRaceCarList[0]->carFlags & 0x200U) != 0 ||
          ((Cars_gNumHumanRaceCars == 2 && ((Cars_gHumanRaceCarList[1]->carFlags & 0x200U) != 0)))))
         ) || (Cars_gHumanRaceCarList[player]->wrongway != 0)) &&
       (gReplayCameraSlots[Replay_ReplayCamera[player].cutToNextCamera].mode == '\v')) {
      iVar7 = Replay_ReplayCamera[player].cutToNextCamera;
      Replay_ReplayCamera[player].defaultCamera = 0;
      pCVar2 = gReplayCameraSlots + iVar7;
      ((u_char *)&(uVar3))[0] = pCVar2->mode;
      ((u_char *)&(uVar3))[1] = ((char *)(pCVar2))[0x1];
      (*(u_short *)((u_char *)&(uVar3) + 2)) = pCVar2->fov;
      *(u_int *)((char *)&(Camera_gInfo[player]) + 0x74) =
           *(u_int *)((char *)&(Camera_gInfo[player]) + 0x74) & 0xf9ffffff | (uVar3 >> 9 & 3) << 0x19;
      pCVar2 = gReplayCameraSlots + Replay_ReplayCamera[player].cutToNextCamera;
      ((u_char *)&(uVar4))[0] = pCVar2->mode;
      ((u_char *)&(uVar4))[1] = ((char *)(pCVar2))[0x1];
      (*(u_short *)((u_char *)&(uVar4) + 2)) = pCVar2->fov;
      Camera_gInfo[player].splineMode = (u_char)(uVar4 >> 0xb) & 7;
      Camera_SetMode(player,0xb);
    }
    else {
      iVar7 = Replay_ReplayCamera[player].cutToNextCamera;
      Replay_ReplayCamera[player].defaultCamera = 1;
      Camera_ReplayUpdate(player,gReplayCameraSlots + iVar7);
    }
  }
  return;
}

/* ---- Replay_ReplayFindClosestCamera__Fii  [REPLAY.CPP:841-871] SLD-VERIFIED ---- */
void Replay_ReplayFindClosestCamera(int player,int slice)

{
  bool bVar1;
  int iVar2;
  Camera_tCamSlot *pCVar3;
  u_int uVar4;
  u_int uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  Camera_tCamSlot *pCVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  
  pCVar9 = gReplayCameraSlots;
  iVar8 = 1;
  iVar10 = gNumSlices / 2;
  for (iVar12 = 0; iVar6 = 0, iVar12 < numValidCams; iVar12 = iVar12 + 1) {
    iVar6 = slice - pCVar9->slice;
    if (iVar10 < iVar6) {
      if (0 < gNumSlices - iVar6) goto Replay_FindCam_diffPosA;
Replay_FindCam_diffNegA:
      iVar6 = slice - pCVar9->slice;
      iVar2 = iVar6 - gNumSlices;
      if (iVar6 <= iVar10) {
        iVar2 = pCVar9->slice - slice;
      }
    }
    else {
      if (iVar6 < 1) goto Replay_FindCam_diffNegA;
Replay_FindCam_diffPosA:
      iVar2 = slice - pCVar9->slice;
      if (iVar10 < iVar2) {
        iVar2 = gNumSlices - iVar2;
      }
    }
    bVar1 = iVar8 < numValidCams;
    iVar6 = 0;
    if (bVar1) {
      iVar6 = iVar8 << 5;
    }
    if (iVar10 < slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) {
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 << 5;
      }
      if (0 < gNumSlices - (slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)))
      goto Replay_FindCam_diffPosB;
Replay_FindCam_diffNegB:
      bVar1 = iVar8 < numValidCams;
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 * 0x20;
      }
      if (iVar10 < slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar11 = (slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) - gNumSlices;
      }
      else {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar11 = *(short *)((int)&gReplayCameraSlots[0].slice + iVar6) - slice;
      }
    }
    else {
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 << 5;
      }
      if (slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6) < 1)
      goto Replay_FindCam_diffNegB;
Replay_FindCam_diffPosB:
      bVar1 = iVar8 < numValidCams;
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 << 5;
      }
      if (iVar10 < slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar11 = gNumSlices - (slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6));
      }
      else {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar11 = slice - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6);
      }
    }
    iVar7 = (int)pCVar9->slice;
    bVar1 = iVar8 < numValidCams;
    iVar6 = 0;
    if (bVar1) {
      iVar6 = iVar8 << 5;
    }
    if (iVar10 < iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) {
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 << 5;
      }
      if (0 < gNumSlices - (iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)))
      goto Replay_FindCam_diffPosC;
Replay_FindCam_diffNegC:
      iVar7 = (int)pCVar9->slice;
      bVar1 = iVar8 < numValidCams;
      pCVar3 = gReplayCameraSlots;
      if (bVar1) {
        pCVar3 = gReplayCameraSlots + iVar8;
      }
      if (iVar10 < iVar7 - pCVar3->slice) {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar7 = (iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) - gNumSlices;
      }
      else {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar7 = *(short *)((int)&gReplayCameraSlots[0].slice + iVar6) - iVar7;
      }
    }
    else {
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 << 5;
      }
      if (iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6) < 1)
      goto Replay_FindCam_diffNegC;
Replay_FindCam_diffPosC:
      iVar7 = (int)pCVar9->slice;
      bVar1 = iVar8 < numValidCams;
      iVar6 = 0;
      if (bVar1) {
        iVar6 = iVar8 << 5;
      }
      if (iVar10 < iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6)) {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar7 = gNumSlices - (iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6));
      }
      else {
        iVar6 = 0;
        if (bVar1) {
          iVar6 = iVar8 << 5;
        }
        iVar7 = iVar7 - *(short *)((int)&gReplayCameraSlots[0].slice + iVar6);
      }
    }
    pCVar9 = pCVar9 + 1;
    iVar6 = iVar12;
    if (iVar2 + iVar11 <= iVar7) break;
    iVar8 = iVar8 + 1;
  }
  Replay_ReplayCamera[player].cutToNextCamera = iVar6;
  if (gReplayCameraSlots[iVar6].mode == '\v') {
    pCVar9 = gReplayCameraSlots + iVar6;
    Replay_ReplayCamera[player].defaultCamera = 0;
    ((u_char *)&(uVar4))[0] = pCVar9->mode;
    ((u_char *)&(uVar4))[1] = ((char *)(pCVar9))[0x1];
    (*(u_short *)((u_char *)&(uVar4) + 2)) = pCVar9->fov;
    *(u_int *)((char *)&(Camera_gInfo[player]) + 0x74) =
         *(u_int *)((char *)&(Camera_gInfo[player]) + 0x74) & 0xf9ffffff | (uVar4 >> 9 & 3) << 0x19;
    pCVar9 = gReplayCameraSlots + Replay_ReplayCamera[player].cutToNextCamera;
    ((u_char *)&(uVar5))[0] = pCVar9->mode;
    ((u_char *)&(uVar5))[1] = ((char *)(pCVar9))[0x1];
    (*(u_short *)((u_char *)&(uVar5) + 2)) = pCVar9->fov;
    Camera_gInfo[player].splineMode = (u_char)(uVar5 >> 0xb) & 7;
    Camera_SetMode(player,0xb);
  }
  else {
    iVar8 = Replay_ReplayCamera[player].cutToNextCamera;
    Replay_ReplayCamera[player].defaultCamera = 1;
    Camera_ReplayUpdate(player,gReplayCameraSlots + iVar8);
  }
  return;
}

/* end of replay.cpp */
