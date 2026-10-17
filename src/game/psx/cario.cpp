/* game/psx/cario.cpp -- RECONSTRUCTED (NFS4 PSX car texture/CLUT I/O; C++ TU)
 *   11 fns: StartUp/CleanUp/ReStart, Copy[From/To]Shape, CreateLicense/CleanUpLicense/LicenseCheck,
 *   ReadIn/UpdateCarTextureData, ReleaseCarCluts. GTE-free. Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "cario_externs.h"
#include "../../mips_semantics.h"

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
extern "C" { void CarIO_StartUp(void); }
extern "C" { void CarIO_CleanUp(void); }
extern "C" { void CarIO_ReStart(void); }
void CarIO_CopyFromShape(short *source,short *dest,int w,int h,int x,int y);
void CarIO_CopyToShape(short *source,short *dest,int mirror);
extern "C" { void CarIO_CreateLicense(char *text,int carType,int player); }
extern "C" { void CarIO_CleanUpLicense(int player); }
void CarIO_LicenseCheck(int reload,int *license_vx,int *license_vy,Car_tObj *carObj,int plate);
void CarIO_ReadInCarTextureData(char *shpfile,Car_tObj *carObj,int reload,int player);
void CarIO_UpdateCarTextureData(char *shpfile,Car_tObj *carObj,int player);
void CarIO_ReleaseCarCluts(Car_tObj *carObj);


/* ---- CarIO_StartUp__Fv  [CARIO.CPP:208-229] SLD-VERIFIED ---- */
extern "C" void CarIO_StartUp(void)

{
  Draw_tPixMap *pDVar1;
  int iVar2;
  
  if (CarIO_carPixMap == (Draw_tPixMap *)0x0) {
    CarIO_carPixMap = (Draw_tPixMap *)reservememadr("carPixMap",0x2640,0);
  }
  iVar2 = 0x263;
  pDVar1 = CarIO_carPixMap + 0x263;
  do {
    pDVar1->flag = 0;
    iVar2 = iVar2 + -1;
    pDVar1 = pDVar1 + -1;
  } while (-1 < iVar2);
  CarIO_carPixMapCount = 0;
  CarIO_carVRamCount = 0;
  CarIO_licenseSFX_Count = 0;
  CarIO_Plate2[0] = (shapetbl *)0x0;
  CarIO_Plate1[0] = (shapetbl *)0x0;
  CarIO_Plate2[1] = (shapetbl *)0x0;
  CarIO_Plate1[1] = (shapetbl *)0x0;
  return;
}

/* ---- CarIO_CleanUp__Fv  [CARIO.CPP:233-238] SLD-VERIFIED ---- */
extern "C" void CarIO_CleanUp(void)

{
  if (CarIO_carPixMap != (Draw_tPixMap *)0x0) {
    purgememadr(CarIO_carPixMap);
  }
  CarIO_carPixMap = (Draw_tPixMap *)0x0;
  return;
}

/* ---- CarIO_ReStart__Fv  [CARIO.CPP:244-253] SLD-VERIFIED ---- */
extern "C" void CarIO_ReStart(void)

{
  Draw_tPixMap *pDVar1;
  int iVar2;
  
  iVar2 = 0x263;
  pDVar1 = CarIO_carPixMap + 0x263;
  do {
    pDVar1->flag = 0;
    iVar2 = iVar2 + -1;
    pDVar1 = pDVar1 + -1;
  } while (-1 < iVar2);
  CarIO_carPixMapCount = 0;
  CarIO_carVRamCount = 0;
  CarIO_CleanUpLicense(0);
  CarIO_CleanUpLicense(1);
  return;
}

/* ---- CarIO_CopyFromShape__FPsT0iiii  [CARIO.CPP:258-342] SLD-VERIFIED ---- */
void CarIO_CopyFromShape(short *source,short *dest,int w,int h,int x,int y)

{
  u_int uVar1;
  u_int uVar2;
  u_short *puVar3;
  u_short *puVar4;
  u_int uVar5;
  u_short uVar6;
  u_short *puVar8;
  int iVar9;
  u_short uVar10;
  u_int uVar11;
  u_int uVar12;
  u_int uVar13;
  int iVar7;
  
  iVar7 = w >> 2;
  uVar5 = w & 3;
  if (uVar5 != 0) {
    iVar7 = iVar7 + 1;
  }
  puVar4 = (u_short *)(dest + (x >> 2) + y * 0xc);
  uVar12 = 0xffff;
  uVar11 = 0xffff;
  if (uVar5 == 0) {
    uVar11 = 0;
  }
  while (uVar5 = uVar5 - 1, uVar5 != 0xffffffff) {
    uVar11 = uVar11 << 4;
  }
  uVar13 = 0;
  uVar5 = x & 3;
  while( true ) {
    uVar5 = uVar5 - 1;
    if (uVar5 == 0xffffffff) break;
    uVar13 = uVar13 << 4 | 0xf;
    uVar1 = uVar11 & 0xf000;
    uVar11 = uVar11 << 4;
    uVar12 = uVar12 << 4 | uVar1 >> 0xc;
  }
  uVar10 = (u_short)uVar11;
  if ((uVar12 & 0xffff) != 0xffff) {
    iVar7 = iVar7 + 1;
    uVar10 = (u_short)uVar12;
  }
  while( true ) {
    h = h + -1;
    uVar5 = 0;
    if (h == -1) break;
    uVar1 = (u_int)(u_short)*source;
    uVar11 = x & 3;
    while( true ) {
      uVar11 = uVar11 - 1;
      uVar2 = uVar1 & 0xf000;
      if (uVar11 == 0xffffffff) break;
      uVar1 = uVar1 << 4;
      uVar5 = uVar5 << 4 | uVar2 >> 0xc;
    }
    iVar9 = 1;
    *puVar4 = *puVar4 & (u_short)uVar13 | (u_short)uVar1;
    puVar3 = (u_short *)source;
    puVar8 = puVar4;
    while( true ) {
      puVar8 = puVar8 + 1;
      source = (short *)(puVar3 + 1);
      uVar11 = x & 3;
      if (iVar7 + -1 <= iVar9) break;
      *puVar8 = (u_short)uVar5;
      uVar1 = (u_int)(u_short)*source;
      uVar5 = 0;
      while( true ) {
        uVar11 = uVar11 - 1;
        uVar2 = uVar1 & 0xf000;
        if (uVar11 == 0xffffffff) break;
        uVar1 = uVar1 << 4;
        uVar5 = uVar5 << 4 | uVar2 >> 0xc;
      }
      iVar9 = iVar9 + 1;
      *puVar8 = *puVar8 | (u_short)uVar1;
      puVar3 = (u_short *)source;
    }
    puVar4[iVar9] = puVar4[iVar9] & uVar10 | (u_short)uVar5;
    if ((uVar12 & 0xffff) == 0xffff) {
      uVar6 = *source;
      source = (short *)(puVar3 + 2);
      while (uVar11 = uVar11 - 1, uVar11 != 0xffffffff) {
        uVar6 = uVar6 << 4;
      }
      puVar4[iVar9] = puVar4[iVar9] | uVar6;
    }
    puVar4 = puVar4 + 0xc;
  }
  return;
}

/* ---- CarIO_CopyToShape__FPsT0i  [CARIO.CPP:347-374] SLD-VERIFIED ---- */
void CarIO_CopyToShape(short *source,short *dest,int mirror)

{
  bool bVar1;
  u_short uVar2;
  u_short *puVar3;
  u_int uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0x16;
  while (iVar6 = iVar6 + -1, iVar6 != -1) {
    iVar5 = 5;
    if (mirror == 0) {
      iVar5 = 0;
      puVar3 = (u_short *)source;
      do {
        uVar2 = *puVar3;
        puVar3 = puVar3 + 1;
        iVar5 = iVar5 + 1;
        *dest = uVar2;
        dest = dest + 1;
      } while (iVar5 < 6);
      source = source + 0xc;
    }
    else {
      puVar3 = (u_short *)(source + 5);
      while (bVar1 = -1 < iVar5, iVar5 = iVar5 + -1, bVar1) {
        uVar2 = *puVar3;
        uVar4 = (u_int)uVar2;
        puVar3 = puVar3 + -1;
        *dest = (u_short)((uVar4 & 0xf) << 0xc) | (u_short)((uVar4 & 0xf0) << 4) |
                (u_short)((uVar4 & 0xf00) >> 4) | uVar2 >> 0xc;
        dest = dest + 1;
      }
      source = source + 0xc;
    }
  }
  return;
}

/* ---- CarIO_CreateLicense__FPcii  [CARIO.CPP:379-483] SLD-VERIFIED ---- */
extern "C" void CarIO_CreateLicense(char *text,int carType,int player)

{
  shapetbl *psVar1;
  short *dest;
  int *piVar2;
  int tu3;
  void *pvVar4;
  u_char ascii;
  int iVar6;
  shapetbl *psVar7;
  short *source;
  int iVar8;
  int *piVar9;
  int *piVar10;
  shapetbl *psVar11;
  shapetbl **ppsVar12;
  int length;
  int iVar13;
  u_char letter [5];
  
  if (carType < 0x16) {
    psVar1 = (shapetbl *)reservememadr("plate1",0x148,0);
    ppsVar12 = CarIO_Plate1 + player;
    *ppsVar12 = psVar1;
    psVar1 = (shapetbl *)reservememadr("plate2",0x148,0);
    iVar13 = 0;
    CarIO_Plate2[player] = psVar1;
    psVar1 = psVar1 + 0xe;
    psVar11 = *ppsVar12 + 0xe;
    dest = (short *)reservememadr("theplate",0x210,0x10);
    piVar2 = (int *)locateshapez(R3DCar_LicenseShapeFile,"blnk");
    piVar10 = (int *)((u_char *)piVar2 + nfs4_mips_sra_s32(*piVar2,8));
    piVar9 = piVar2;
    do {
      iVar8 = *piVar9;
      piVar9 = piVar9 + 1;
      iVar6 = iVar13;
      iVar13 = nfs4_mips_addu_s32(iVar13,1);
      psVar7 = *ppsVar12;
      ((int *)CarIO_Plate2[player])[iVar6] = iVar8;
      ((int *)psVar7)[iVar6] = iVar8;
    } while (iVar13 < 4);
    iVar13 = 0;
    do {
      tu3 = *piVar10;
      piVar10 = piVar10 + 1;
      iVar13 = iVar13 + 1;
      *(int *)psVar1 = tu3;
      *(int *)psVar11 = tu3;
      psVar11 = (shapetbl *)&psVar11->width;
      psVar1 = (shapetbl *)&psVar1->width;
    } while (iVar13 < 0xc);
    psVar11 = CarIO_Plate2[player];
    psVar1 = CarIO_Plate1[player];
    *(u_int *)psVar11 = *(u_char *)psVar11 | 0x11800;
    *(u_int *)psVar1 = *(u_char *)psVar1 | 0x11800;
    psVar1 = CarIO_Plate1[player];
    CarIO_Plate2[player]->width = 0x18;
    psVar1->width = 0x18;
    CarIO_CopyFromShape((short *)(piVar2 + 4),dest,0x30,0x16,0,0);
    length = (int)strlen(text);
    iVar13 = nfs4_mips_subu_s32(0x18,
        nfs4_mips_addu_s32(nfs4_mips_sll_s32(length,1),length));
    for (iVar6 = 0; iVar6 < length; iVar6 = nfs4_mips_addu_s32(iVar6,1)) {
      ascii = (u_char)text[iVar6];
      if (ascii != ' ') {
        switch(ascii) {
        case 0xc0:
        case 0xc4:
        case 0xc5:
          ascii = 'a';
          break;
        case 0xc8:
          ascii = 'e';
          break;
        case 0xcc:
          ascii = 'i';
          break;
        case 0xd1:
          ascii = 'n';
          break;
        case 0xd2:
        case 0xd6:
          ascii = 'o';
          break;
        case 0xd9:
        case 0xdc:
          ascii = 'u';
        }
        letter[1] = '\0';
        letter[0] = ascii;
        strcat((char *)letter,"   ");
        pvVar4 = locateshapez(R3DCar_LicenseShapeFile,(char *)letter);
        CarIO_CopyFromShape((short *)((u_char *)pvVar4 + 0x10),dest,7,0xc,iVar13,5);
      }
      iVar13 = nfs4_mips_addu_s32(iVar13,6);
    }
    if ((R3DCar_InMenu == 0) && (GameSetup_gData.mirrorTrack != 0)) {
      CarIO_CopyToShape(dest + 6,(short *)&CarIO_Plate1[player]->data,1);
      psVar1 = CarIO_Plate2[player];
      iVar13 = 1;
      source = dest;
    }
    else {
      CarIO_CopyToShape(dest,(short *)&CarIO_Plate1[player]->data,0);
      source = dest + 6;
      psVar1 = CarIO_Plate2[player];
      iVar13 = 0;
    }
    CarIO_CopyToShape(source,(short *)&psVar1->data,iVar13);
    purgememadr(dest);
  }
  else {
    CarIO_Plate2[player] = (shapetbl *)0x0;
    CarIO_Plate1[player] = (shapetbl *)0x0;
  }
  return;
}

/* ---- CarIO_CleanUpLicense__Fi  [CARIO.CPP:486-490] SLD-VERIFIED ---- */
extern "C" void CarIO_CleanUpLicense(int player)

{
  shapetbl *psVar1;
  
  psVar1 = CarIO_Plate1[player];
  if (psVar1 != (shapetbl *)0x0) {
    purgememadr(psVar1);
  }
  CarIO_Plate1[player] = (shapetbl *)0x0;
  psVar1 = CarIO_Plate2[player];
  if (psVar1 != (shapetbl *)0x0) {
    purgememadr(psVar1);
  }
  CarIO_Plate2[player] = (shapetbl *)0x0;
  return;
}

/* ---- CarIO_LicenseCheck__FiPiT1P8Car_tObji  [CARIO.CPP:497-511] SLD-VERIFIED ---- */
void CarIO_LicenseCheck(int reload,int *license_vx,int *license_vy,Car_tObj *carObj,int plate)

{
  short sVar1;
  short sVar2;
  
  if (((reload & 2U) != 0) && (CarIO_licenseSFX_Count < 0xc)) {
    sVar1 = CarIO_licenseSFX_Vram[CarIO_licenseSFX_Count][0];
    sVar2 = CarIO_licenseSFX_Vram[CarIO_licenseSFX_Count][1];
    (carObj->render).licenseOffsetU[plate] = (((u_char)sVar1 & 0x3f) - ((u_char)*license_vx & 0x3f)) * '\x04'
    ;
    (carObj->render).licenseOffsetV[plate] = (char)sVar2 - (char)*license_vy;
    *license_vx = (int)sVar1;
    *license_vy = (int)sVar2;
    CarIO_licenseSFX_Count = CarIO_licenseSFX_Count + 1;
    return;
  }
  (carObj->render).licenseOffsetV[plate] = '\0';
  (carObj->render).licenseOffsetU[plate] = '\0';
  return;
}

/* ---- CarIO_ReadInCarTextureData__FPcP8Car_tObjii  [CARIO.CPP:515-713] SLD-VERIFIED ---- */
void CarIO_ReadInCarTextureData(char *shpfile,Car_tObj *carObj,int reload,int player)

{
  short sVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  int index;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int cx_00;
  int cy_00;
  int rx;
  int ry;
  CarIO_textureInfo *pCVar10;
  int license_vx;
  int license_vy;
  int carType;
  int carPixMapCount;
  int recolor_flag;
  Draw_tPixMap *pmx;
  
  recolor_flag = 8;
  carType = (int)(carObj->render).currentCarType;
  if ((reload & 1U) == 0) {
    if (R3DCar_InMenu == 0) {
      sVar2 = CarIO_carVRamSlots[CarIO_carVRamCount][0];
      (carObj->render).VRamX = sVar2;
      rx = (int)sVar2;
      ry = (int)CarIO_carVRamSlots[CarIO_carVRamCount][1];
      (carObj->render).VRamY = CarIO_carVRamSlots[CarIO_carVRamCount][1];
      if (carType < 0x1c) {
        if (((carObj->render).inside & 1U) == 0) {
          CarIO_carVRamCount = nfs4_mips_addu_s32(CarIO_carVRamCount,3);
        }
        else {
          index = CarIO_carVRamCount / 3;
          CarIO_carVRamCount = nfs4_mips_addu_s32(CarIO_carVRamCount,
              nfs4_mips_addu_s32(nfs4_mips_sll_s32((int)CarIO_carVRamAdd[index],1),
                                    (int)CarIO_carVRamAdd[index]));
        }
      }
      else {
        CarIO_carVRamCount = nfs4_mips_addu_s32(CarIO_carVRamCount,1);
      }
    }
    else {
      sVar2 = CarIO_carVRamSlotsMenu[CarIO_carVRamCount][0];
      (carObj->render).VRamX = sVar2;
      rx = (u_int)sVar2;
      sVar2 = CarIO_carVRamSlotsMenu[CarIO_carVRamCount][1];
      (carObj->render).VRamY = sVar2;
      CarIO_carVRamCount = nfs4_mips_addu_s32(CarIO_carVRamCount,
                                               (int)CarIO_carVRamAdd[CarIO_carVRamCount]);
      ry = (int)sVar2;
    }
  }
  else {
    rx = (int)(carObj->render).VRamX;
    ry = (int)(carObj->render).VRamY;
  }
  if ((reload & 0x10U) == 0) {
    carPixMapCount = CarIO_carPixMapCount;
    (carObj->render).textureStartIndex = CarIO_carPixMapCount;
  }
  else {
    carPixMapCount = (carObj->render).textureStartIndex;
  }
  if ((reload & 8U) != 0) {
    if (((carObj->render).inside & 1U) != 0) {
      iVar6 = nfs4_mips_addu_s32(rx,-0x200);
      if (R3DCar_InMenu == 0) {
        iVar6 = nfs4_mips_addu_s32(rx,-0x280);
      }
      rx = nfs4_mips_addu_s32(rx,
          (int)CarIO_carVRamOffset[nfs4_mips_sra_s32(iVar6,6)]);
    }
    (carObj->render).textureOffsetU = (short)((rx & 0x3f) << 2);
    (carObj->render).textureOffsetV = (u_short)ry & 0xff;
  }
  iVar6 = 0;
  if (R3DCar_InMenu == 0) {
    recolor_flag = 0x18;
  }
  Texture_palCopy = (Texture_pal8bit *)(carObj->render).palCopy;
  Texture_ResetPaletteSharing();
  pCVar10 = CarIO_textureName;
  for (; iVar6 < 0x33; iVar6 = iVar6 + 1) {
    pmx = CarIO_carPixMap + carPixMapCount;
    bVar4 = true;
    pcVar5 = (char *)locateshapez(shpfile,pCVar10->pal);
    iVar7 = pCVar10->palShare;
    if ((pcVar5 == (char *)0x0) && (iVar7 == 0)) {
      bVar4 = false;
      pcVar5 = (char *)locateshapez(shpfile,pCVar10->tex);
    }
    if (iVar6 == 0x14) {
      recolor_flag = 0;
    }
    if (pcVar5 != (char *)0x0) {
      bVar3 = false;
      if (recolor_flag != 0) {
        carObj->render.palCopyNum[iVar6] = (short)Texture_palNum;
      }
      if (carType < 0x16) {
        if (iVar6 == CarIO_licensePlate[carType][0]) {
          sVar2 = CarIO_licensePlate[carType][1];
          sVar1 = CarIO_licensePlate[carType][2];
          license_vx = nfs4_mips_addu_s32(rx,(int)sVar2);
          license_vy = nfs4_mips_addu_s32(ry,(int)sVar1);
          CarIO_LicenseCheck(reload,&license_vx,&license_vy,carObj,0);
          Texture_LoadPmx((char *)0x0,(char *)CarIO_Plate1[player],recolor_flag,license_vx,
                     license_vy,-1,-1,pmx);
          bVar3 = true;
          pmx->flag = 1;
        }
        else if (iVar6 == CarIO_licensePlate[carType][3]) {
          sVar2 = CarIO_licensePlate[carType][4];
          sVar1 = CarIO_licensePlate[carType][5];
          license_vx = nfs4_mips_addu_s32(rx,(int)sVar2);
          license_vy = nfs4_mips_addu_s32(ry,(int)sVar1);
          CarIO_LicenseCheck(reload,&license_vx,&license_vy,carObj,1);
          Texture_LoadPmx((char *)0x0,(char *)CarIO_Plate2[player],recolor_flag,license_vx,
                     license_vy,-1,-1,pmx);
          bVar3 = true;
          pmx->flag = 2;
        }
      }
      if (!bVar3) {
        Texture_LoadPmx((char *)0x0,pcVar5,recolor_flag,rx,ry,-1,-1,
                   pmx);
      }
      if (iVar6 == 0x20) {
        ChangeTPage(&pmx->tpage,2);
      }
      pmx->flag |= 0x80;
    }
    if (bVar4) {
      iVar8 = carPixMapCount;
      if (iVar7 != 0) {
        if (recolor_flag != 0) {
          carObj->render.palCopyNum[iVar6] = (carObj->render).palCopyNum[iVar7 + -1];
        }
        iVar8 = nfs4_mips_addu_s32(nfs4_mips_addu_s32(iVar7,-1),
                                    (carObj->render).textureStartIndex);
      }
      pcVar5 = (char *)locateshapez(shpfile,pCVar10->tex);
      if (pcVar5 != (char *)0x0) {
        bVar4 = false;
        cx_00 = (CarIO_carPixMap[iVar8].clut & 0x3f) << 4;
        cy_00 = (int)(CarIO_carPixMap[iVar8].clut >> 6);
        if (carType < 0x16) {
          if (iVar6 == CarIO_licensePlate[carType][0]) {
            sVar2 = CarIO_licensePlate[carType][1];
            sVar1 = CarIO_licensePlate[carType][2];
            license_vx = nfs4_mips_addu_s32(rx,(int)sVar2);
            license_vy = nfs4_mips_addu_s32(ry,(int)sVar1);
            CarIO_LicenseCheck(reload,&license_vx,&license_vy,carObj,0);
            Texture_LoadPmx((char *)0x0,(char *)CarIO_Plate1[player],0x20,license_vx,license_vy,
                       cx_00,cy_00,pmx);
            bVar4 = true;
            pmx->flag = 1;
          }
          else if (iVar6 == CarIO_licensePlate[carType][3]) {
            sVar2 = CarIO_licensePlate[carType][4];
            sVar1 = CarIO_licensePlate[carType][5];
            license_vx = nfs4_mips_addu_s32(rx,(int)sVar2);
            license_vy = nfs4_mips_addu_s32(ry,(int)sVar1);
            CarIO_LicenseCheck(reload,&license_vx,&license_vy,carObj,1);
            Texture_LoadPmx((char *)0x0,(char *)CarIO_Plate2[player],0x20,license_vx,license_vy,
                       cx_00,cy_00,pmx);
            bVar4 = true;
            pmx->flag = 2;
          }
        }
        if (!bVar4) {
          Texture_LoadPmx((char *)0x0,pcVar5,0x20,rx,ry,cx_00,cy_00,
                     pmx);
        }
        if (iVar6 == 0x20) {
          ChangeTPage(&pmx->tpage,2);
        }
        if (iVar7 == 0) {
          pmx->flag |= 0x80;
        }
      }
    }
    pCVar10 = pCVar10 + 1;
    carPixMapCount = nfs4_mips_addu_s32(carPixMapCount,1);
  }
  if ((reload & 0x80U) != 0) {
    CarIO_carPixMapCount = carPixMapCount;
  }
  return;
}

/* ---- CarIO_UpdateCarTextureData__FPcP8Car_tObji  [CARIO.CPP:718-849] SLD-VERIFIED ---- */
void CarIO_UpdateCarTextureData(char *shpfile,Car_tObj *carObj,int player)

{
  short sVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  char *pcVar5;
  shapetbl **ppsVar6;
  Draw_tPixMap *pmx;
  int carType;
  int rx;
  int ry;
  int iVar9;
  int iVar10;
  int cx_00;
  u_int uVar11;
  int iVar13;
  CarIO_textureInfo *pCVar14;
  int ctrl;
  int carPixMapCount;
  
  carPixMapCount = (carObj->render).textureStartIndex;
  carType = (int)(carObj->render).currentCarType;
  rx = (int)(carObj->render).VRamX;
  ry = (int)(carObj->render).VRamY;
  ctrl = 8;
  if (R3DCar_InMenu == 0) {
    ctrl = 0x18;
  }
  Texture_palCopy = (Texture_pal8bit *)(carObj->render).palCopy;
  iVar13 = 0;
  Texture_ResetPaletteSharing();
  pCVar14 = CarIO_textureName;
  do {
    if (0x32 < iVar13) {
      return;
    }
    pmx = CarIO_carPixMap + carPixMapCount;
    bVar4 = true;
    pcVar5 = (char *)locateshapez(shpfile,pCVar14->pal);
    iVar9 = pCVar14->palShare;
    if ((pcVar5 == (char *)0x0) && (iVar9 == 0)) {
      bVar4 = false;
      pcVar5 = (char *)locateshapez(shpfile,pCVar14->tex);
    }
    if (iVar13 == 0x14) {
      ctrl = 0;
    }
    if (pcVar5 == (char *)0x0) {
CarIOUpd_locateShape:
      if (bVar4) {
        iVar10 = carPixMapCount;
        if (iVar9 != 0) {
          if (ctrl != 0) {
            carObj->render.palCopyNum[iVar13] = (carObj->render).palCopyNum[iVar9 + -1];
          }
          iVar10 = iVar9 + -1 + (carObj->render).textureStartIndex;
        }
        pcVar5 = (char *)locateshapez(shpfile,pCVar14->tex);
        if (pcVar5 != (char *)0x0) {
          bVar4 = false;
          cx_00 = (CarIO_carPixMap[iVar10].clut & 0x3f) << 4;
          uVar11 = (u_int)(CarIO_carPixMap[iVar10].clut >> 6);
          if (carType < 0x16) {
            if (iVar13 == CarIO_licensePlate[carType][0]) {
              sVar1 = CarIO_licensePlate[carType][1];
              sVar2 = CarIO_licensePlate[carType][2];
              ppsVar6 = CarIO_Plate1;
            }
            else {
              if (iVar13 != CarIO_licensePlate[carType][3]) goto CarIOUpd_loadPmxCtrl20;
              sVar1 = CarIO_licensePlate[carType][4];
              sVar2 = CarIO_licensePlate[carType][5];
              ppsVar6 = CarIO_Plate2;
            }
            bVar4 = true;
            Texture_LoadPmx((char *)0x0,(char *)ppsVar6[player],0x20,rx + sVar1,ry + sVar2,cx_00,uVar11,
                       pmx);
          }
CarIOUpd_loadPmxCtrl20:
          if (!bVar4) {
            Texture_LoadPmx((char *)0x0,pcVar5,0x20,rx,ry,cx_00,uVar11,
                       pmx);
          }
          if (iVar13 == 0x20) {
            ChangeTPage(&pmx->tpage,2);
          }
          if (iVar9 == 0) {
            pmx->flag |= 0x80;
          }
        }
      }
    }
    else {
      bVar3 = false;
      if ((pmx->flag & 0x80) != 0) {
        iVar10 = (pmx->clut & 0x3f) << 4;
        uVar11 = (u_int)(pmx->clut >> 6);
        if (ctrl != 0) {
          Texture_palNum = (int)carObj->render.palCopyNum[iVar13];
        }
        if (carType < 0x16) {
          if (iVar13 == CarIO_licensePlate[carType][0]) {
            sVar1 = CarIO_licensePlate[carType][2];
            sVar2 = CarIO_licensePlate[carType][1];
            ppsVar6 = CarIO_Plate1;
          }
          else {
            if (iVar13 != CarIO_licensePlate[carType][3]) goto CarIOUpd_loadPmxFallback;
            sVar1 = CarIO_licensePlate[carType][5];
            sVar2 = CarIO_licensePlate[carType][4];
            ppsVar6 = CarIO_Plate2;
          }
          bVar3 = true;
          Texture_LoadPmx((char *)0x0,(char *)ppsVar6[player],ctrl,rx + sVar2,ry + sVar1,iVar10,uVar11,
                     pmx);
        }
CarIOUpd_loadPmxFallback:
        if (!bVar3) {
          Texture_LoadPmx((char *)0x0,pcVar5,ctrl,rx,ry,iVar10,uVar11,
                     pmx);
        }
        if (iVar13 == 0x20) {
          ChangeTPage(&pmx->tpage,2);
        }
        pmx->flag |= 0x80;
        goto CarIOUpd_locateShape;
      }
    }
    pCVar14 = pCVar14 + 1;
    carPixMapCount = carPixMapCount + 1;
    iVar13 = iVar13 + 1;
  } while( true );
}

/* ---- CarIO_ReleaseCarCluts__FP8Car_tObj  [CARIO.CPP:856-871] SLD-VERIFIED ---- */
void CarIO_ReleaseCarCluts(Car_tObj *carObj)

{
  Draw_tPixMap *pDVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = (carObj->render).textureStartIndex;
  do {
    if ((CarIO_carPixMap[iVar3].flag & 0x80) != 0) {
      pDVar1 = CarIO_carPixMap + iVar3;
      CarIO_carPixMap[iVar3].flag = 0;
      Texture_MenuReleaseClutId(pDVar1->clut);
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 1;
  } while (iVar2 < 0x33);
  return;
}

/* end of cario.cpp */
