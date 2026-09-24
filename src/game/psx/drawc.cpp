/* game/psx/drawc.cpp -- RECONSTRUCTED (NFS4 PSX world-geometry draw; C++ TU)
 *   35 fns: subdivision facets, world matrix/translation setup, night colour calc, DrawW_DrawQuad,
 *   object/chunk facet builders, object transforms, skidmarks, lines/spike-belt, anim timers, depth cue.
 *   GTE-heavy (142 cop2 stubs -> gte_ intrinsics). Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "drawc_externs.h"
#define PSYQ_SCRATCH_BYTES(off) ((void *)getScratchAddr((off) / 4))

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void ChangeTPage(u_short *tpage,int nabr);
void DrawC_SetEnviroment(void);
void DrawC_ReadLightingData(void);
extern "C" { void DrawC_ReadeMapData(void); }
void DrawC_BuildRenderingData(void);
void DrawC_KillRenderingData(void);
void DrawC_NightHeadlight(Car_tObj *carObj);
extern "C" { void DrawC_MenuColorData(int color,Car_tObj *carObj,int player); }
int DrawC_PrimStart(Draw_tVertex *center,Car_tObj *carObj,int lightAvg,Draw_CarCache *sd);
void DrawC_PrimStop(Car_tObj *carObj,Draw_CarCache *sd);
void DrawC_ShadowPrim(Draw_tVertex *shadowVT,Draw_CarCache *sd);
void DrawC_ShadowPrimClip(Draw_tVertex *shadowVT,Draw_CarCache *sd);
void DrawC_SpotPrims(matrixtdef *m,coorddef *t,Draw_CarCache *sd);
void DrawC_ShowroomPrims(matrixtdef *m,coorddef *t,Draw_CarCache *sd);


/* ---- ChangeTPage__FPUsi  [DRAWC.CPP:112-114] SLD-VERIFIED ---- */
void ChangeTPage(u_short *tpage,int nabr)

{
  *tpage = *tpage & 0xff9f | (u_short)(nabr << 5);
  return;
}

/* ---- DrawC_SetEnviroment__Fv  [DRAWC.CPP:119-120] SLD-VERIFIED ---- */
void DrawC_SetEnviroment(void)

{
  return;
}

/* ---- DrawC_ReadLightingData__Fv  [DRAWC.CPP:123-177] SLD-VERIFIED ---- */
void DrawC_ReadLightingData(void)

{
  char *addr;
  int val;
  int iVar1;
  int iVar2;
  int i;
  int i_2;
  char *RenderingFileData;
  char name [256];
  char *ScaneData;
  
  sprintf(name,"%sTr%02d.env",Paths_Paths[6],GameSetup_gData.track);
  addr = (char *)loadfileadr(name,0x10);
  if (addr == (char *)0x0)
    return;
  ScaneData = addr;
  DrawC_gEnvMapMax = Risk_ReadNextValue(&ScaneData);
  DrawC_gEnvMap = (DrawC_tEnvMap *)reservememadr("envmap",DrawC_gEnvMapMax * 6,0);
  i_2 = 0;
  if (0 < DrawC_gEnvMapMax) {
    do {
      val = Risk_ReadNextValue(&ScaneData);
      DrawC_gEnvMap[i_2].slice = (short)val;
      iVar1 = Risk_ReadNextValue(&ScaneData);
      DrawC_gEnvMap[i_2].tex = (short)iVar1;
      iVar1 = Risk_ReadNextValue(&ScaneData);
      DrawC_gEnvMap[i_2].extra = (short)((u_int)iVar1 << 8);
      iVar1 = Risk_ReadNextValue(&ScaneData);
      DrawC_gEnvMap[i_2].extra =
          (short)((u_short)DrawC_gEnvMap[i_2].extra + (short)iVar1);
      if (DrawC_gEnvMap[i_2].slice < 0) {
        DrawC_gEnvMap[i_2].slice = 0x7fff;
        break;
      }
      i_2 = i_2 + 1;
    } while (i_2 < DrawC_gEnvMapMax);
  }
  DrawC_gShadowMax = Risk_ReadNextValue(&ScaneData);
  DrawC_gShadow = (DrawC_tEnvMap *)reservememadr("Shadow",DrawC_gShadowMax * 6,0);
  iVar1 = 0;
  if (0 < DrawC_gShadowMax) {
    do {
      iVar2 = Risk_ReadNextValue(&ScaneData);
      DrawC_gShadow[iVar1].slice = (short)iVar2;
      iVar2 = Risk_ReadNextValue(&ScaneData);
      DrawC_gShadow[iVar1].tex = (short)iVar2;
      iVar2 = Risk_ReadNextValue(&ScaneData);
      DrawC_gShadow[iVar1].extra = (short)((u_int)iVar2 << 8);
      iVar2 = Risk_ReadNextValue(&ScaneData);
      DrawC_gShadow[iVar1].extra =
          (short)((u_short)DrawC_gShadow[iVar1].extra + (short)iVar2);
      if (DrawC_gShadow[iVar1].slice < 0) {
        DrawC_gShadow[iVar1].slice = 0x7fff;
        break;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < DrawC_gShadowMax);
  }
  purgememadr(addr);
  return;
}

/* ---- DrawC_ReadeMapData__Fv  [DRAWC.CPP:181-182] SLD-VERIFIED ---- */
extern "C" void DrawC_ReadeMapData(void)

{
  R3DCcar_ReadeMapData();
  return;
}

/* ---- DrawC_BuildRenderingData__Fv  [DRAWC.CPP:190-198] SLD-VERIFIED ---- */
void DrawC_BuildRenderingData(void)

{
  DrawC_ReadLightingData();
  DrawC_ReadeMapData();
  R3DCcar_ReadTrackShadow();
  return;
}

/* ---- DrawC_KillRenderingData__Fv  [DRAWC.CPP:208-210] SLD-VERIFIED ---- */
void DrawC_KillRenderingData(void)

{
  purgememadr(DrawC_gEnvMap);
  purgememadr(DrawC_gShadow);
  return;
}

/* ---- DrawC_NightHeadlight__FP8Car_tObj  [DRAWC.CPP:214-265] SLD-VERIFIED ---- */
void DrawC_NightHeadlight(Car_tObj *carObj)

{
  int i;
  short newB;
  Car_tObj **ppCVar1;
  VECTOR *v;
  coorddef *pos;
  short newG;
  short newR;
  MATRIX nightMat;
  VECTOR nightV;
  PCOORD16 zero = {0,0,0,0};
  coorddef tmp;
  coorddef tmp2;
  int *light;

  /* @0x800BE9A8-AC: light = &carObj->render.light, set unconditionally (before the lights&6 test);
   * used by the Night_AdditiveNightCalc call and by the lightning-tint block below. */
  light = (int *)&(carObj->render).light;
  if (((Cars_gList[gCView.player]->control).lights & 6U) != 0) {
    ppCVar1 = Cars_gHumanRaceCarList + gCView.player;
    tmp.x = nfs4_mips_subu_s32((carObj->N).position.x,((*ppCVar1)->N).position.x);
    tmp.y = nfs4_mips_subu_s32((carObj->N).position.y,((*ppCVar1)->N).position.y);
    tmp.z = nfs4_mips_subu_s32((carObj->N).position.z,((*ppCVar1)->N).position.z);
    transform(&tmp.x,gNightMat.m,&tmp2.x);
    DrawW_WorldSetUpTranslation(&tmp2,&nightMat);
    DrawW_WorldSetUpMatrix(&gNightMat,&nightMat);
gte_lwc2(0,*(int *)(&zero));
    gte_lwc2(1,*(int *)(((char *)&zero + 0x4)));
    gte_rt();
    v = &nightV;
gte_swc2(0x19,&nightV);
    gte_swc2(0x1a,((char *)&nightV + 0x4));
    gte_swc2(0x1b,((char *)&nightV + 0x8));
    Night_AdditiveNightCalc(v,(CVECTOR *)&(carObj->render).light);
  }
  /* @0x800BEA80-EB10: weather/lightning RGB tint -- ALWAYS runs (fall-through from the lights&6 test).
   * Adds Night_gWeatherColor[Night_gLightningType] (read as 3 bytes R/G/B) to the low 3 bytes of the
   * `light` local, clamps each channel to 0xFF, and writes back. The binary reads/writes the bytes of
   * the `light` POINTER slot itself (104+$sp = &light), NOT *light -- gcc-2.7.2 preserved these stores
   * because &light escapes. Reproduced byte-faithfully; this whole block was missing (H46). */
  if (Night_gDrawLightning != '\0') {
    newR = (short)((int)*(u_char *)&light +
                   (int)*(u_char *)&Night_gWeatherColor[Night_gLightningType]);
    newG = (short)((int)((u_char *)&light)[1] +
                   (int)((u_char *)&Night_gWeatherColor[Night_gLightningType])[1]);
    newB = (short)((int)((u_char *)&light)[2] +
                   (int)((u_char *)&Night_gWeatherColor[Night_gLightningType])[2]);
    if (0xff < newR) {
      newR = 0xff;
    }
    if (0xff < newG) {
      newG = 0xff;
    }
    if (0xff < newB) {
      newB = 0xff;
    }
    *(char *)&light = (char)newR;
    ((char *)&light)[1] = (char)newG;
    ((char *)&light)[2] = (char)newB;
  }
  return;
}

/* ---- DrawC_MenuColorData__FiP8Car_tObji  [DRAWC.CPP:388-527] SLD-VERIFIED ---- */
extern "C" void DrawC_MenuColorData(int color,Car_tObj *carObj,int player)

{
  int menuColor;
  short sVar1;
  int carType;
  u_int uVar2;
  int iVar3;
  GameSetup_tCarData *pGVar4;
  Texture_pal8bit *palCopy;
  char *pcVar5;
  char *shpfile;
  char filename [10];
  char infilename [100];
  
  pGVar4 = carObj->carInfo;
  if (carObj->async_handle == 0) {
    if ((int)(carObj->render).currentCarType != pGVar4->carType) {
      return;
    }
    (carObj->render).upgradeFlags =
         (char)pGVar4->EngineMods + (char)pGVar4->WeightTransfer * '\x02' +
         (char)pGVar4->GroundEffects * '\x04';
    // 800BEB80..800BEB90: LHU, ADDIU -16, SLTIU 3 (types 16..18 only).
    if ((u_int)((u_short)(carObj->render).currentCarType - 0x10) < 3U) {
      (carObj->render).upgradeFlags = '\a';
    }
    uVar2 = (u_int)(u_char)(carObj->render).upgradeFlags;
    iVar3 = color + (uVar2 & 1) * 0x100 + (uVar2 & 2) * 0x100;
    if (DrawC_gMenuColor[player] == iVar3) {
      return;
    }
    DrawC_gMenuColor[player] = iVar3;
    DrawSync(0);
    iVar3 = (int)(carObj->render).currentCarType;
    if (iVar3 < 0x1c) {
      if ((color & 8U) != ((u_short)(carObj->render).colorIndex & 8)) {
        R3DCar_GetCarName(filename,iVar3,carObj->carInfo->Country);
        if (color < 8) {
          pcVar5 = "l";
        }
        else {
          pcVar5 = "d";
        }
        strcat(filename,pcVar5);
        strcpy(infilename,Paths_Paths[0x18]);
        strcat(infilename,filename);
        strcat(infilename,".psh");
        // 800BEC80..800BECA0: s0 receives loadfileadr's v0, not strcat's
        // filename pointer; the loaded shape buffer is processed then freed.
        pcVar5 = (char *)loadfileadr(infilename,0x10);
        CarIO_UpdateCarTextureData(pcVar5,carObj,player);
        purgememadr(pcVar5);
        DrawSync(0);
      }
      Texture_CarColor = (color & 7U) + ((u_char)(carObj->render).upgradeFlags & 2) * 4;
      Texture_ProcessPaletteCopy((Texture_pal8bit *)(carObj->render).palCopy,0,1);
      iVar3 = 1;
      palCopy = (Texture_pal8bit *)(carObj->render).palCopy;
      sVar1 = (carObj->render).palNum;
      Texture_CarColor = (color & 7U) + ((u_char)(carObj->render).upgradeFlags & 1) * 8;
    }
    else {
      iVar3 = 0;
      palCopy = (Texture_pal8bit *)(carObj->render).palCopy;
      sVar1 = (carObj->render).palNum;
      Texture_CarColor = color & 7;
    }
    Texture_ProcessPaletteCopy(palCopy,iVar3,(int)sVar1);
  }
  (carObj->render).colorIndex = (short)color;
  return;
}

/* ---- DrawC_PrimStart__FP12Draw_tVertexP8Car_tObjiP13Draw_CarCache  [DRAWC.CPP:1148-1531] SLD-VERIFIED ---- */
int DrawC_PrimStart(Draw_tVertex *center,Car_tObj *carObj,int lightAvg,Draw_CarCache *sd)

{
  int i;
  int cop_flag;
  int half;
  int mirror;
  int overlay;
  SVECTOR r;
  int eSpeed;
  int quad;
  short envMap;
  int eColor;
  int eColor2;
  u_int uVar1;
  Draw_tPixMap *pDVar2;
  short tu12;
  int envColor2;
  u_long *sub_ot_p;
  int sub_otz_x4;
  u_short *lightTable;
  DRAWENV *drawEnv_p;
  int envTexShape;
  int tunnelFlag;
  DRAWENV *shapeData_p;
  short extraShadow;
  int sub_otz_h2;
  int sub_otOffset;
  short extraEnvMap;
  int iVar3;
  short shadow;
  u_char *puVar4;
  int lightAvgScaled;
  int envColor;
  u_int uVar5;
  int shadowQuad;
  int menuPmx_w2;
  int menuPmx_w3;
  int menuPmx_w0;
  int menuPmx_w1;
  int sub_otz;
  int shapeIdx;
  Draw_tPixMap *vertBuf_p;
  int carType;
  int vertCount;
  DRAWENV *LEnv;
  int tpageShadow;
  int nabr_blend;
  int envSpeed;
  int shadowAbsOffs;
  int halfTransp;
  PSX_RECT tw;
  u_int shadowTex;
  Draw_tPixMap *reflMap_iter;
  u_int envMapTex;
  u_int shadow_align_a;
  u_int envMap_w0;
  short eIndexEnvMap;
  u_int envMap_w3;
  short eIndexShadow;
  short headLight_bits;
  u_char envMapBigBit;
  short ts13;
  short tu14;
  short tu15;
  u_int envMap_align_a;
  u_int shadowMap_w1;
  u_char carTypeOffRange;
  u_int envMap_align_b;
  u_int shadowMap_w2;
  long sub_otSize_local;
  u_int shadow_align_b;
  u_short tu27;
  
  envMapBigBit = false;
  vertCount = (int)(carObj->render).currentCarType;
  carTypeOffRange = 5 < vertCount - 0x16U;
gte_SetRotMatrix(&DrawC_gScreenMat);
gte_SetTransMatrix(&DrawC_gScreenMat);
gte_lwc2(0,*(int *)(center));
  gte_lwc2(1,*(int *)(((char *)center + 0x4)));
  gte_rtps();
gte_stsz(&sd->sub_otz);
  shapeIdx = sd->sub_otz;
  sub_otz_h2 = nfs4_mips_sra_s32(shapeIdx,1);
  if (R3DCar_InMenu == 0) {
    sd->sub_otz = sub_otz_h2;
    if ((sub_otz_h2 < 0) || (Draw_gViewOtSize + -3 < sub_otz_h2)) {
      return -1;
    }
  }
  else {
    sd->sub_otz = 0;
  }
  puVar4 = (u_char *)(carObj->render).sort_carObj;
  (carObj->render).world_otz = sd->sub_otz;
  if (puVar4 == (u_char *)0x0) {
    sub_ot_p = (carObj->render).sub_ot;
    sd->sub_ot = sub_ot_p;
    sub_otSize_local = (carObj->render).sub_otSize;
    sd->sub_otSize = sub_otSize_local;
    ClearOTagR(sub_ot_p,sub_otSize_local);
    sd->sub_otz = 0;
    sub_otOffset = (carObj->render).sub_otOffset;
  }
  else {
    sd->sub_ot = *(u_long **)(puVar4 + 0x86c);
    sd->sub_otSize = *(int *)(puVar4 + 0x870);
    sd->sub_otz = nfs4_mips_sll_s32(
        nfs4_mips_subu_s32(sd->sub_otz,*(int *)(puVar4 + 0x864)),1);
    sub_otOffset = *(int *)(puVar4 + 0x874);
  }
  sub_otz_x4 = nfs4_mips_sll_s32(sd->sub_otz,2);
  sd->sub_otz = sub_otz_x4;
  (carObj->render).sub_otz = nfs4_mips_subu_s32(
      nfs4_mips_addu_s32(sub_otz_x4,sub_otOffset),
      nfs4_mips_sll_s32(shapeIdx,2));
  sd->sub_otSize = sd->sub_otSize + -1;
  sd->pmxStart = CarIO_carPixMap + (carObj->render).textureStartIndex;
  sd->offsetU0 = (u_char)(carObj->render).textureOffsetU;
  sd->offsetV0 = (u_char)(carObj->render).textureOffsetV;
  sd->offsetU1 = (carObj->render).licenseOffsetU[0];
  sd->offsetV1 = (carObj->render).licenseOffsetV[0];
  lightAvgScaled = 0x32;
  sd->offsetU2 = (carObj->render).licenseOffsetU[1];
  lightTable = (u_short *)&DrawC_gOverlay[50];
  sd->offsetV2 = (carObj->render).licenseOffsetV[1];
  do {
    *lightTable = 0;
    lightAvgScaled = lightAvgScaled + -1;
    lightTable = lightTable - 1;
  } while (-1 < lightAvgScaled);
  if (R3DCar_InMenu == 0) {
    iVar3 = (carObj->N).damage[0];
    if (iVar3 < 0x1e0001) {
      if (0xa0000 < iVar3) {
        DrawC_gOverlay[0] = DrawC_gOverlay[0] | 2;
        DrawC_gOverlay[2] = DrawC_gOverlay[2] | 2;
      }
    }
    else {
      DrawC_gOverlay[0] = DrawC_gOverlay[0] | 1;
      DrawC_gOverlay[2] = DrawC_gOverlay[2] | 1;
    }
    iVar3 = (carObj->N).damage[2];
    if (iVar3 < 0x1e0001) {
      if (0xa0000 < iVar3) {
        DrawC_gOverlay[0] = DrawC_gOverlay[0] | 0x200;
        DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x200;
      }
    }
    else {
      DrawC_gOverlay[0] = DrawC_gOverlay[0] | 0x100;
      DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x100;
    }
    iVar3 = (carObj->N).damage[3];
    if (iVar3 < 0x1e0001) {
      if (0xa0000 < iVar3) {
        DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x800;
      }
    }
    else {
      DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x400;
    }
    iVar3 = (carObj->N).damage[4];
    if (iVar3 < 0x1e0001) {
      if (0xa0000 < iVar3) {
        DrawC_gOverlay[1] = DrawC_gOverlay[1] | 0x200;
        DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x2000;
      }
    }
    else {
      DrawC_gOverlay[1] = DrawC_gOverlay[1] | 0x100;
      DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x1000;
    }
    iVar3 = (carObj->N).damage[6];
    if (iVar3 < 0x1e0001) {
      if (0xa0000 < iVar3) {
        DrawC_gOverlay[1] = DrawC_gOverlay[1] | 2;
        DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x20;
      }
    }
    else {
      DrawC_gOverlay[1] = DrawC_gOverlay[1] | 1;
      DrawC_gOverlay[2] = DrawC_gOverlay[2] | 0x10;
    }
    iVar3 = (carObj->N).damage[7];
    if (iVar3 < 0x1e0001) {
      if (0xa0000 < iVar3) {
        DrawC_gOverlay[2] = DrawC_gOverlay[2] | 8;
      }
    }
    else {
      DrawC_gOverlay[2] = DrawC_gOverlay[2] | 4;
    }
    if (0x30000 < (carObj->N).damage[8]) {
      DrawC_gOverlay[4] = DrawC_gOverlay[4] | 0x101;
    }
    if (((carObj->render).brakeLight & 1U) != 0) {
      if ((DrawC_gOverlay[1] & 1U) == 0) {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] | 0x81;
        DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] | 0x81;
      }
      if ((DrawC_gOverlay[1] & 0x100U) == 0) {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] | 0x8100;
        DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] | 0x8100;
      }
    }
    if ((carObj->control).gear == '\0') {
      if ((DrawC_gOverlay[1] & 1U) == 0) {
        DrawC_gOverlay[0x1a] = DrawC_gOverlay[0x1a] | 0x80;
      }
      if ((DrawC_gOverlay[1] & 0x100U) == 0) {
        DrawC_gOverlay[0x1a] = DrawC_gOverlay[0x1a] | 0x8000;
      }
    }
    headLight_bits = (carObj->render).headLight;
    if ((headLight_bits & 0x11U) != 0) {
      if (((headLight_bits & 0x40U) != 0) || ((DrawC_gOverlay[0] & 1U) == 0)) {
        DrawC_gOverlay[0x1d] = DrawC_gOverlay[0x1d] | 0x81;
      }
      if ((((carObj->render).headLight & 4U) != 0) || ((DrawC_gOverlay[0] & 0x100U) == 0)) {
        DrawC_gOverlay[0x1d] = DrawC_gOverlay[0x1d] | 0x8100;
      }
    }
    if (((carObj->render).brakeLight & 2U) != 0) {
      if ((DrawC_gOverlay[1] & 1U) == 0) {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] | 0x80;
        DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] | 0x80;
      }
      if ((DrawC_gOverlay[1] & 0x100U) == 0) {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] | 0x8000;
        DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] | 0x8000;
      }
    }
    ts13 = DrawC_gOverlay[0x18];
    if ((bool)carTypeOffRange) {
      shadow_align_b = (sd->head).mirror;
      if (((carObj->render).signalLight[shadow_align_b] & 0x80U) != 0) {
        DrawC_gOverlay[0x1c] = DrawC_gOverlay[0x1c] | 0x40;
      }
      if (((carObj->render).signalLight[shadow_align_b] & 8U) != 0) {
        if ((DrawC_gOverlay[0] & 1U) == 0) {
          DrawC_gOverlay[0x1b] = DrawC_gOverlay[0x1b] | 0x80;
        }
        if ((DrawC_gOverlay[1] & 1U) == 0) {
          DrawC_gOverlay[0x1c] = DrawC_gOverlay[0x1c] | 0x81;
        }
      }
      if (((carObj->render).signalLight[shadow_align_b ^ 1] & 0x80U) != 0) {
        DrawC_gOverlay[0x1c] = DrawC_gOverlay[0x1c] | 0x4000;
      }
      if (((carObj->render).signalLight[shadow_align_b ^ 1] & 8U) != 0) {
        if ((DrawC_gOverlay[0] & 0x100U) == 0) {
          DrawC_gOverlay[0x1b] = DrawC_gOverlay[0x1b] | 0x8000;
        }
        if ((DrawC_gOverlay[1] & 0x100U) == 0) {
          DrawC_gOverlay[0x1c] = DrawC_gOverlay[0x1c] | 0x8100;
        }
      }
      if (1 < (u_char)""[vertCount]) {
        if ((DrawC_gOverlay[0x1c] & 0x40U) == 0) {
          DrawC_gOverlay[0x1c] = DrawC_gOverlay[0x1c] | DrawC_gOverlay[0x18] & 0xffU;
        }
        if ((DrawC_gOverlay[0x1c] & 0x4000U) == 0) {
          DrawC_gOverlay[0x1c] = DrawC_gOverlay[0x1c] | DrawC_gOverlay[0x18] & 0xff00U;
        }
      }
      if (""[vertCount] == '\x03') {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x1c];
        DrawC_gOverlay[0x1c] = ts13;
      }
      goto DrawCPrimStart_carTypeOff;
    }
  }
  else {
DrawCPrimStart_carTypeOff:
    if ((bool)carTypeOffRange) goto DrawCPrimStart_camRotMatrix;
  }
  tu14 = DrawC_gOverlay[0x1b] | 2U;
  tu15 = DrawC_gOverlay[0x1c] | 0x200U;
  if (DrawC_gOverlay[4] == 0) {
    tu12 = DrawC_gOverlay[0x1b] | 0x83;
    DrawC_gOverlay[0x1b] = DrawC_gOverlay[0x1b] | 2U;
    tu27 = DrawC_gOverlay[0x1c] | 0x200U;
    if (DrawC_SirenFlash[(u_short)(carObj->render).signalLight[0] & 0xf] != 0) {
      DrawC_gOverlay[0x1b] = tu12;
      tu27 = DrawC_gOverlay[0x1c] | 0x281;
    }
    DrawC_gOverlay[0x1c] = tu27;
    tu14 = DrawC_gOverlay[0x1b];
    tu15 = DrawC_gOverlay[0x1c];
    if (DrawC_SirenFlash[(u_short)(carObj->render).signalLight[1] & 0xf] != 0) {
      tu14 = DrawC_gOverlay[0x1b] | 0x8100;
      tu15 = DrawC_gOverlay[0x1c] | 0x8100;
    }
  }
  DrawC_gOverlay[0x1c] = tu15;
  DrawC_gOverlay[0x1b] = tu14;
  if ((R3DCar_InMenu != 0) || ((carObj->AIFlags & 2U) != 0)) {
    DrawC_gOverlay[0x1d] = DrawC_gOverlay[0x1d] & 0x7e7e;
    if (((carObj->render).brakeLight & 1U) == 0) {
      DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] & 0x7f7f;
      DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] & 0x7f7f;
    }
    if ((DrawC_HeadLightFlash[(u_short)(carObj->render).signalLight[0] & 0xf] != 0) &&
       ((((carObj->render).headLight & 0x40U) != 0 || ((DrawC_gOverlay[0] & 1U) == 0)))) {
      DrawC_gOverlay[0x1d] = DrawC_gOverlay[0x1d] | 0x81;
    }
    if ((DrawC_HeadLightFlash[(u_short)(carObj->render).signalLight[1] & 0xf] != 0) &&
       ((((carObj->render).headLight & 4U) != 0 || ((DrawC_gOverlay[0] & 0x100U) == 0)))) {
      DrawC_gOverlay[0x1d] = DrawC_gOverlay[0x1d] | 0x8100;
    }
    if ((DrawC_gOverlay[1] & 1U) == 0) {
      if (DrawC_TailLightFlash[(u_short)(carObj->render).signalLight[0] & 0xf] != 0) {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] | 0x80;
        DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] | 0x80;
      }
      if (DrawC_HeadLightFlash[(u_short)(carObj->render).signalLight[0] & 0xf] != 0) {
        DrawC_gOverlay[0x1a] = DrawC_gOverlay[0x1a] | 0x80;
      }
    }
    if ((DrawC_gOverlay[1] & 0x100U) == 0) {
      if (DrawC_TailLightFlash[(u_short)(carObj->render).signalLight[1] & 0xf] != 0) {
        DrawC_gOverlay[0x18] = DrawC_gOverlay[0x18] | 0x8000;
        DrawC_gOverlay[0x19] = DrawC_gOverlay[0x19] | 0x8000;
      }
      if (DrawC_HeadLightFlash[(u_short)(carObj->render).signalLight[1] & 0xf] != 0) {
        DrawC_gOverlay[0x1a] = DrawC_gOverlay[0x1a] | 0x8000;
      }
    }
  }
DrawCPrimStart_camRotMatrix:
  tw.x = 0;
  tw.w = 0;
  tw.y = R3DCar_yawCam;
  RotMatrix((SVECTOR *)&tw,&DrawC_gMatA);
  DrawC_gMatA.t[2] = 0;
  DrawC_gMatA.t[1] = 0;
  DrawC_gMatA.t[0] = 0;
  DrawC_gWetRoad = 0;
  if (R3DCar_InMenu == 0) {
    shadowAbsOffs = 3;
    drawEnv_p = Draw_GetDRAWENV(gCView.id,gFlip);
    eIndexEnvMap = (carObj->N).eIndexEnvMap;
    eIndexShadow = (carObj->N).eIndexShadow;
    iVar3 = (int)(carObj->N).simRoadInfo.quad;
    uVar5 = (u_int)(u_short)DrawC_gEnvMap[eIndexEnvMap].tex;
    shadow_align_b = (u_int)(u_short)DrawC_gShadow[eIndexShadow].tex;
    nabr_blend = 2;
    if (iVar3 < (int)((u_short)DrawC_gEnvMap[eIndexEnvMap].extra & 0xff)) {
      uVar5 = (u_int)nfs4_mips_sra_s32(
          nfs4_mips_sll_s32((int)(u_short)DrawC_gEnvMap[eIndexEnvMap].extra,16),24);
    }
    if (iVar3 < (int)((u_short)DrawC_gShadow[eIndexShadow].extra & 0xff)) {
      shadow_align_b = (u_int)nfs4_mips_sra_s32(
          nfs4_mips_sll_s32((int)(u_short)DrawC_gShadow[eIndexShadow].extra,16),24);
    }
    envMapBigBit = 10 < (short)uVar5;
    if ((bool)envMapBigBit) {
      uVar5 = uVar5 - 10;
    }
    if ((int)(shadow_align_b << 0x10) < 0) {
      shadowAbsOffs = 0;
      shadow_align_b = (u_int)nfs4_mips_negu_s32((int)shadow_align_b);
    }
    if (10 < (short)shadow_align_b) {
      shadow_align_b = shadow_align_b - 10;
      nabr_blend = 1;
    }
    iVar3 = nfs4_mips_sra_s32(
        nfs4_mips_sll_s32(nfs4_mips_subu_s32((int)uVar5,1),16),16);
    if (iVar3 < 0) {
      (sd->ePmx0).u0 = '\0';
      (sd->ePmx0).v0 = '\0';
      (sd->ePmx0).clut = 0;
    }
    else {
      nfs4_mips_copy_bytes(&sd->ePmx0,Track_gReflectionMaps + iVar3,16);
    }
    iVar3 = nfs4_mips_sra_s32(
        nfs4_mips_sll_s32(nfs4_mips_subu_s32((int)shadow_align_b,1),16),16);
    if (iVar3 < 0) {
      (sd->ePmx1).u0 = '\0';
      (sd->ePmx1).v0 = '\0';
      (sd->ePmx1).clut = 0;
    }
    else {
      vertBuf_p = Track_gReflectionMaps + iVar3;
      tw.x = (short)vertBuf_p->u0;
      tw.w = 0x80;
      tw.h = 0x40;
      tw.y = (short)Track_gReflectionMaps[iVar3].v0;
      SetDrawMode(&sd->drawModeOn,(u_int)drawEnv_p->dfe,0,
                 (u_int)Track_gReflectionMaps[iVar3].tpage,&tw);
      tw.h = 0;
      tw.w = 0;
      tw.y = 0;
      tw.x = 0;
      SetDrawMode(&sd->drawModeOff,(u_int)drawEnv_p->dfe,0,
                 (u_int)drawEnv_p->tpage,&tw);
      nfs4_mips_copy_bytes(&sd->ePmx1,Track_gReflectionMaps + iVar3,16);
      ChangeTPage(&(sd->ePmx1).tpage,nabr_blend);
    }
    sd->eAddZ = (nfs4_mips_srav_s32((int)(carObj->N).positionXZ,
                                    shadowAbsOffs + 3) & 0x3fU) +
                (int)DrawC_gEnvMapOffset[(sd->ePmx1).v0 >> 6];
    if (((GameSetup_gData.Weather != 0) &&
        (tunnelFlag = (int)BWorldSm_TunnelFlagSm(&(carObj->N).simRoadInfo), tunnelFlag != 1)) &&
       (Cars_kSkidMarkSurface[(carObj->N).driveSurfaceType] == 1)) {
      DrawC_gWetRoad = 1;
    }
    DrawC_gReflectOffset = (short)nfs4_mips_sra_s32(
        nfs4_mips_addu_s32(
            nfs4_mips_sra_s32(nfs4_mips_addu_s32(
                nfs4_mips_sll_s32((carObj->N).dimension.y,1),
                (carObj->N).dimension.y),1),
            (carObj->N).objAltitude),8);
  }
  else {
    shapeData_p = Draw_GetDRAWENV(gCView.id,gFlip);
    SetDrawMode(&sd->drawModeOn,(u_int)shapeData_p->dfe,1,
               (u_int)shapeData_p->tpage,(PSX_RECT *)0x0);
    SetDrawMode(&sd->drawModeOff,(u_int)shapeData_p->dfe,0,
               (u_int)shapeData_p->tpage,(PSX_RECT *)0x0);
    nfs4_mips_copy_bytes(&sd->ePmx0,gMenuPixmap[0],16);
  }
  ChangeTPage(&(sd->ePmx0).tpage,1);
  if (R3DCar_InMenu == 0) {
    iVar3 = nfs4_mips_sra_s32(
        nfs4_mips_mult_s32(nfs4_mips_sra_s32(lightAvg,2),
                           (int)(u_int)R3DCar_eMapColour.r),7);
    if ((bool)envMapBigBit) {
      iVar3 = nfs4_mips_div_s32(nfs4_mips_sll_s32(iVar3,1),3);
    }
    sd->eColor2 = nfs4_mips_mult_s32(
        nfs4_mips_sra_s32(nfs4_mips_addu_s32(
            nfs4_mips_sll_s32(iVar3,1),iVar3),2),0x10101);
  }
  else {
    iVar3 = nfs4_mips_sra_s32(lightAvg,1);
  }
  sd->eColor0 = nfs4_mips_mult_s32(iVar3,0x10101);
  if ((carObj->render).currentCarType != 1) {
    iVar3 = nfs4_mips_addu_s32(nfs4_mips_sll_s32(iVar3,1),iVar3);
  }
  sd->eColor1 = nfs4_mips_mult_s32(nfs4_mips_sra_s32(iVar3,2),0x10101);
  return (carObj->render).world_otz;
}

/* ---- DrawC_PrimStop__FP8Car_tObjP13Draw_CarCache  [DRAWC.CPP:1535-1563] SLD-VERIFIED ---- */
void DrawC_PrimStop(Car_tObj *carObj,Draw_CarCache *sd)

{
  short sVar1;
  int iVar2;
  int worldZ;
  int iVar3;
  Car_tObj *sort_carObj;
  u_int *puVar4;
  int sub_otSize;
  
  if ((carObj->render).sort_flag == 0) {
    sort_carObj = (Car_tObj *)(carObj->render).sort_carObj;
    if (sort_carObj == (Car_tObj *)0x0) {
      iVar2 = (carObj->render).sub_otSize;
      iVar3 = (carObj->render).world_otz;
    }
    else {
      sVar1 = sort_carObj->render.sort_flag;
      if ((sort_carObj->render.sort_flag != 0) &&
         (sort_carObj->render.sort_flag = sVar1 + -1, sVar1 != 1)) {
        return;
      }
      iVar2 = sort_carObj->render.sub_otSize;
      iVar3 = sort_carObj->render.world_otz;
    }
    sd->sub_ot[0] = sd->sub_ot[0] & 0xff000000 |
                    sd->head.cprim.LastPrim[iVar3] & 0xffffff;
    puVar4 = (u_int *)sd->head.cprim.LastPrim + iVar3;
    *puVar4 = *puVar4 & 0xff000000 |
              (u_int)(intptr)(sd->sub_ot + (iVar2 + -1)) & 0xffffffU;
  }
  return;
}

/* ---- DrawC_Prim__FP10matrixtdefP8coorddefP16Transformer_zObjP20Transformer_zOverlayiP13Draw_CarCache  [DRAWC.CPP:1772-2543] SLD-VERIFIED ---- */
void DrawC_Prim(matrixtdef *m,coorddef *t,Transformer_zObj *obj,Transformer_zOverlay *overlay,
               int envmap,Draw_CarCache *sd)

{
  COORD16 * Nvertice;
  COORD16 * vt;
  int u;
  short t1;
  short t2;
  short t3;
  int r0;
  int r1;
  int r2;
  PCOORD16 * tV;
  POLY_FT3 * prim;
  Transformer_zFacet * facet;
  int id0;
  int id1;
  int id2;
  int bfct;
  u_long color;
  Draw_tPixMap * pmx;
  u_char offsetU;
  u_char offsetV;
  u_char u0;
  u_char u1;
  u_char u2;
  u_char v0;
  u_char v1;
  u_char v2;
  u_short uv0;
  u_short uv1;
  short * z;
  long xy0;
  long xy1;
  long xy2;
  int overlayFlag;
  int facet_flag;
  int sd_otz;
  int index;
  int which;
  Transformer_zOverlay * facetOverlay;
  char cVar1;
  u_char bVar2;
  u_char uVar3;
  u_int uVar4;
  u_int *puVar5;
  u_char primTypeByte_d;
  u_short clut;
  int absZ;
  short matRow1_x;
  int vertA_matBPtr;
  short *vert_xyz_iter;
  short *psVar6;
  int otz_check_a;
  u_short tpage;
  int matRow0_w1;
  int matRow_temp;
  int envmapMode;
  int bfctResult_c;
  int otz_check_b;
  int bfctResult_b;
  u_char primTypeByte;
  int ti34;
  int bfctResult_a;
  u_int facetIdx_dec;
  int dvx1_word;
  u_short uv2;
  u_int ot_offs_alt;
  u_char primTypeByte_b;
  u_char code;
  int iVar7;
  int facetByteOff;
  int iVar8;
  u_int uVar9;
  u_int uVar10;
  u_char v;
  int iVar11;
  u_int *primOut;
  char *envmapUV_dst;
  int iVar13;
  int iVar14;
  Transformer_zFacet *facet_p_v1;
  Transformer_zOverlay *overlay_entry;
  u_int ot_offs_byte;
  u_int uVar15;
  Transformer_zOverlay *pTVar16;
  COORD16 *vertex_iter;
  u_int *puVar17;
  Transformer_zFacet *facet_iter;
  Draw_CarVertex *tV_dst;
  Transformer_zFacet *facet_p_v3;
  Transformer_zFacet *facet_p_v2;
  Transformer_zFacet *facet_p_v4;
  Draw_CarVertex *facet_vertex0;
  Draw_CarVertex *facet_vertex1;
  Draw_CarVertex *facet_vertex2;
  Draw_tPixMap *facet_pmx;
  short facetFlag;
  int i;
  int remVerts;
  int vertCounter;
  u_int facetIdx;
  int vertIdx2;
  int loopDoneTag;
  int primTypeByte_c;
  u_int *ot_stitch_p;
  u_int *primOut_drm;
  u_int *primOut_drmOff;
  u_int *primOut_drm2;
  u_int drmode_tag;
  u_long *puVar19;
  int drmodeOff_w0;
  u_long *puVar20;
  int drmodeOn_tag;
  u_char ePmx1_uOff;
  u_char ePmx0_uOff;
  u_char ePmx1_uOff2;
  char vert_uv_b;
  u_long *sub_ot_p;
  u_char ePmx1_vOff;
  char vert_v_byte;
  u_long uVar21;
  int drmodeOff_w1;
  u_long drmode_w0;
  u_long drmode_w1;
  int drmodeOff_w2;
  int drmodeOn_w1;
  COORD16 *Nvertex_buf;
  COORD16 *Nvertex_p;
  int vertIdx1;
  int vertIdx0;
  short tu8;
  short tu9;
  u_char tc7;
  u_char vert_a_idx2;
  short ts10;
  u_char tu1;
  u_char tu4;
  u_char vert_c_idx;
  short tu19;
  int tu20;
  int ot_stitch_pb;
  short tu11;
  short tu12;
  short tu14;
  short tu15;
  u_char tu3;
  u_char vert_b_idx;
  u_char vert_c_idx2;
  u_char tu2;
  short tu7;
  int tu10;
  int ot_stitch_pa;
  u_char vert_a_idx;
  char tc6;
  short ts24;
  short ts7;
  u_short tu21;
  u_short tu23;
  u_int tu26;
  u_short tu27;
  u_char tu5;
  u_short uVar8_00;

  NFSHS_DIAGNOSTIC_CALL(NFSHS_HostTraceDrawCPrimEntry(m,t,obj,overlay,envmap,sd));
  
  ((u_char *)&(iVar7))[0] = (sd->ePmx0).u0;
  ((u_char *)&(iVar7))[1] = (sd->ePmx0).v0;
  (*(u_short *)((u_char *)&(iVar7) + 2)) = (sd->ePmx0).clut;
  Nvertex_p = obj->Nvertex;
  if ((iVar7 == 0) &&
     (((u_char *)&(iVar8))[0] = (sd->ePmx1).u0, ((u_char *)&(iVar8))[1] = (sd->ePmx1).v0, (*(u_short *)((u_char *)&(iVar8) + 2)) = (sd->ePmx1).clut,
     iVar8 == 0)) {
    envmap = envmap & 0xbe;
  }
  if ((envmap & 1U) != 0) {
gte_SetRotMatrix(&DrawC_gMatA);
gte_SetTransMatrix(&DrawC_gMatA);
    remVerts = (int)obj->numVertex;
    loopDoneTag = -1;
    envmapUV_dst = &sd->tV[0].v;
    vertex_iter = Nvertex_p;
    while (remVerts = remVerts + -1, remVerts != loopDoneTag) {
      sd->vt0 = *vertex_iter;
gte_lwc2(0,*(int *)(((char *)sd + 0xac)));
      gte_lwc2(1,*(int *)(((char *)sd + 0xb0)));
      gte_rt();
gte_swc2(0x19,((char *)sd + 0x9c));
      gte_swc2(0x1a,((char *)sd + 0xa0));
      gte_swc2(0x1b,((char *)sd + 0xa4));
      absZ = (sd->tv).vz;
      if (absZ < 0) {
        absZ = -absZ;
      }
      vertex_iter = vertex_iter + 1;
      envmapUV_dst[-1] = (char)(sd->tv).vx;
      *envmapUV_dst = (char)absZ;
      envmapUV_dst = envmapUV_dst + 8;
    }
  }
  TrsProj_SetTransPrecision(8);
  matRow0_w1 = m->m[3];
  iVar7 = m->m[6];
  (sd->matB).m[0][0] = (short)(m->m[0] >> 4);
  (sd->matB).m[0][1] = (short)(matRow0_w1 >> 4);
  (sd->matB).m[0][2] = (short)(iVar7 >> 4);
  matRow_temp = m->m[4];
  facetByteOff = m->m[7];
  matRow1_x = (short)(m->m[1] >> 4);
  (sd->matB).m[1][0] = matRow1_x;
  (sd->matB).m[1][1] = (short)(matRow_temp >> 4);
  (sd->matB).m[1][2] = (short)(facetByteOff >> 4);
  iVar7 = m->m[2];
  iVar8 = m->m[5];
  iVar11 = m->m[8];
  (sd->matB).m[1][0] = -matRow1_x;
  ts7 = (sd->matB).m[1][1];
  (sd->matB).m[2][0] = (short)(iVar7 >> 4);
  ts10 = (sd->matB).m[1][2];
  (sd->matB).m[2][1] = (short)(iVar8 >> 4);
  (sd->matB).m[2][2] = (short)(iVar11 >> 4);
  (sd->matB).m[1][1] = -ts7;
  (sd->matB).m[1][2] = -ts10;
  iVar7 = TrsProj_precision;
  (sd->matB).t[0] = t->x >> (TrsProj_precision & 0x1fU);
  (sd->matB).t[1] = -(t->y >> (iVar7 & 0x1fU));
  (sd->matB).t[2] = t->z >> (iVar7 & 0x1fU);
  TrsProj_ResetTransPrecision();
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
  tV_dst = sd->tV;
  vertex_iter = obj->vertex;
  vertCounter = (int)obj->numVertex;
  psVar6 = &vertex_iter->z;
  while( true ) {
    vertCounter = vertCounter + -1;
    envmapMode = envmap & 9;
    if (vertCounter == -1) break;
    tu11 = psVar6[-1];
    tu12 = *psVar6;
    psVar6 = psVar6 + 3;
    tu14 = vertex_iter->x;
    vertex_iter = vertex_iter + 1;
    tV_dst->vt.x = tu14;
    tV_dst->vt.y = tu11;
    tV_dst->vt.z = tu12;
    tV_dst = tV_dst + 1;
  }
  facetIdx = (u_int)obj->numFacet;
  if (envmapMode == 1) {
    iVar7 = facetIdx * 0xc;
DrawC_Prim_envmap1MainLoop:
    do {
      uVar10 = facetIdx - 1;
      iVar8 = iVar7;
      do {
        do {
          do {
            facetIdx = uVar10;
            iVar7 = iVar8 + -0xc;
            if (facetIdx == 0xffffffff) {
              return;
            }
            facet_p_v1 = obj->facet + facetIdx;
            vert_a_idx = facet_p_v1->vertexId0;
            vert_b_idx = facet_p_v1->vertexId1;
            vert_c_idx = facet_p_v1->vertexId2;
            uVar10 = facetIdx - 1;
            iVar8 = iVar7;
          } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
          gte_ldVXY0(sd->tV + vert_a_idx);
          gte_ldVZ0(&sd->tV[vert_a_idx].vt.z);
          gte_ldVXY1(sd->tV + vert_b_idx);
          gte_ldVZ1(&sd->tV[vert_b_idx].vt.z);
          gte_ldVXY2(sd->tV + vert_c_idx);
          gte_ldVZ2(&sd->tV[vert_c_idx].vt.z);
          gte_rtpt();
          gte_nclip();
          gte_stMAC0();
          iVar11 = sd->bfct;
          if ((sd->head).mirror != 0) {
            iVar11 = -iVar11;
          }
          uVar10 = facetIdx - 1;
        } while (iVar11 < 1);
        gte_stSXY0();
        gte_stSXY1();
        gte_stSXY2();
        gte_avsz3();
        gte_stOTZ();
        iVar11 = sd->otz + sd->sub_otz;
        sd->otz = iVar11;
        if (iVar11 < 0) goto DrawC_Prim_envmap1MainLoop;
        uVar10 = facetIdx - 1;
      } while (sd->sub_otSize < iVar11);
      if ((((u_short)facet_p_v1->flag & 0x3f3) != 0) &&
         (((u_char *)&(iVar11))[0] = (sd->ePmx1).u0, ((u_char *)&(iVar11))[1] = (sd->ePmx1).v0,
         (*(u_short *)((u_char *)&(iVar11) + 2)) = (sd->ePmx1).clut, iVar11 != 0)) {
        psVar6 = (short *)(Nvertex_p + facet_p_v1->vertexId0);
        ts7 = psVar6[1];
        ts24 = psVar6[2];
        (sd->vt0).x = *psVar6;
        (sd->vt0).y = ts7;
        (sd->vt0).z = ts24;
        psVar6 = (short *)(Nvertex_p + facet_p_v1->vertexId1);
        ts7 = psVar6[1];
        ts24 = psVar6[2];
        (sd->vt1).x = *psVar6;
        (sd->vt1).y = ts7;
        (sd->vt1).z = ts24;
        psVar6 = (short *)(Nvertex_p + facet_p_v1->vertexId2);
        ts7 = psVar6[1];
        ts24 = psVar6[2];
        (sd->vt2).x = *psVar6;
        (sd->vt2).y = ts7;
        (sd->vt2).z = ts24;
        ot_stitch_p = (u_int *)(sd->head).cprim.PrimPtr;
        iVar8 = sd->otz;
        puVar20 = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(ot_stitch_p + 3);
        drmode_tag = (u_int)(sd->drawModeOff).tag;
        uVar10 = (sd->drawModeOff).code[0];
        uVar15 = (sd->drawModeOff).code[1];
        *ot_stitch_p = drmode_tag;
        ot_stitch_p[1] = uVar10;
        ot_stitch_p[2] = uVar15;
        AddPrim(puVar20 + iVar8,ot_stitch_p);
        puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
        iVar8 = sd->otz;
        puVar20 = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
        *puVar17 = 0x07000000;
        AddPrim(puVar20 + iVar8,puVar17);
        primOut_drm = (u_int *)(sd->head).cprim.PrimPtr;
        iVar8 = sd->otz;
        puVar20 = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(primOut_drm + 3);
        puVar19 = (u_long *)(intptr)(sd->drawModeOn).tag;
        uVar21 = (sd->drawModeOn).code[0];
        drmode_w1 = (sd->drawModeOn).code[1];
        primOut_drm[0] = (u_int)(intptr)puVar19;
        primOut_drm[1] = uVar21;
        primOut_drm[2] = drmode_w1;
        AddPrim(puVar20 + iVar8,primOut_drm);
        uVar10 = *(u_int *)&sd->dvx1;
        uVar15 = *(u_int *)&sd->dvx2;
        puVar17[2] = *(u_int *)&sd->dvx0;
        puVar17[4] = uVar10;
        puVar17[6] = uVar15;
        puVar17[1] = sd->eColor0;
        *(u_char *)((u_char *)puVar17 + 7) = 0x26;
        tu21 = (sd->ePmx1).tpage;
        *(u_short *)((u_char *)puVar17 + 0xe) = (sd->ePmx1).clut;
        *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
        ePmx1_uOff = (sd->ePmx1).u0 + 0x40;
        ePmx1_vOff = (sd->ePmx1).v0 + (char)sd->eAddZ;
        ts7 = (sd->vt0).z;
        *(u_char *)(puVar17 + 3) = (char)(sd->vt0).y + ePmx1_uOff;
        *(u_char *)((u_char *)puVar17 + 0xd) = (char)ts7 + ePmx1_vOff;
        ts7 = (sd->vt1).z;
        *(u_char *)(puVar17 + 5) = (char)(sd->vt1).y + ePmx1_uOff;
        *(u_char *)((u_char *)puVar17 + 0x15) = (char)ts7 + ePmx1_vOff;
        ts7 = (sd->vt2).z;
        *(u_char *)(puVar17 + 7) = (char)(sd->vt2).y + ePmx1_uOff;
        *(u_char *)((u_char *)puVar17 + 0x1d) = (char)ts7 + ePmx1_vOff;
      }
      ((u_char *)&(iVar13))[0] = (sd->ePmx0).u0;
      ((u_char *)&(iVar13))[1] = (sd->ePmx0).v0;
      (*(u_short *)((u_char *)&(iVar13) + 2)) = (sd->ePmx0).clut;
      if (iVar13 != 0) {
        puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
        iVar8 = sd->otz;
        puVar20 = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
        *puVar17 = 0x07000000;
        AddPrim(puVar20 + iVar8,puVar17);
        uVar10 = *(u_int *)&sd->dvx1;
        uVar15 = *(u_int *)&sd->dvx2;
        puVar17[2] = *(u_int *)&sd->dvx0;
        puVar17[4] = uVar10;
        puVar17[6] = uVar15;
        puVar17[1] = sd->eColor0;
        *(u_char *)((u_char *)puVar17 + 7) = 0x26;
        tu21 = (sd->ePmx0).tpage;
        *(u_short *)((u_char *)puVar17 + 0xe) = (sd->ePmx0).clut;
        *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
        tu5 = (sd->ePmx0).v0;
        ePmx0_uOff = (sd->ePmx0).u0 + 0x40;
        cVar1 = sd->tV[vert_a_idx].v;
        *(u_char *)(puVar17 + 3) = sd->tV[vert_a_idx].u + ePmx0_uOff;
        *(u_char *)((u_char *)puVar17 + 0xd) = cVar1 + tu5;
        cVar1 = sd->tV[vert_b_idx].v;
        *(u_char *)(puVar17 + 5) = sd->tV[vert_b_idx].u + ePmx0_uOff;
        *(u_char *)((u_char *)puVar17 + 0x15) = cVar1 + tu5;
        cVar1 = sd->tV[vert_c_idx].v;
        *(u_char *)(puVar17 + 7) = sd->tV[vert_c_idx].u + ePmx0_uOff;
        *(u_char *)((u_char *)puVar17 + 0x1d) = cVar1 + tu5;
      }
      puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
      iVar8 = sd->otz;
      puVar20 = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
      *puVar17 = 0x07000000;
      AddPrim(puVar20 + iVar8,puVar17);
      uVar10 = *(u_int *)&sd->dvx1;
      uVar15 = *(u_int *)&sd->dvx2;
      puVar17[2] = *(u_int *)&sd->dvx0;
      puVar17[4] = uVar10;
      puVar17[6] = uVar15;
      puVar17[1] = sd->color;
      *(u_char *)((u_char *)puVar17 + 7) = 0x24;
      tu21 = sd->pmxStart[facet_p_v1->textureIndex].tpage;
      *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[facet_p_v1->textureIndex].clut;
      *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
      tu21 = (u_short)facet_p_v1->uv1.u | (u_short)facet_p_v1->uv1.v << 8;
      tu27 = (u_short)facet_p_v1->uv2.u | (u_short)facet_p_v1->uv2.v << 8;
      *(u_short *)(puVar17 + 3) = (u_short)facet_p_v1->uv0.u | (u_short)facet_p_v1->uv0.v << 8;
      *(u_short *)(puVar17 + 5) = tu21;
      *(u_short *)(puVar17 + 7) = tu27;
    } while( true );
  }
  if ((u_int)envmapMode < 2) {
    if (envmapMode == 0) {
      if ((envmap & 2U) != 0) {
        iVar7 = facetIdx * 0xc;
DrawC_Prim_envmap0AltPath:
        do {
          iVar8 = iVar7;
          uVar10 = facetIdx - 1;
          do {
            do {
              do {
                facetIdx = uVar10;
                iVar7 = iVar8 + -0xc;
                if (facetIdx == 0xffffffff) {
                  return;
                }
                facet_p_v3 = obj->facet + facetIdx;
                iVar8 = iVar7;
                uVar10 = facetIdx - 1;
              } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
              facet_vertex0 = sd->tV + facet_p_v3->vertexId0;
              facet_vertex1 = sd->tV + facet_p_v3->vertexId1;
              facet_vertex2 = sd->tV + facet_p_v3->vertexId2;
              gte_ldVXY0(facet_vertex0);
              gte_ldVZ0(&facet_vertex0->vt.z);
              gte_ldVXY1(facet_vertex1);
              gte_ldVZ1(&facet_vertex1->vt.z);
              gte_ldVXY2(facet_vertex2);
              gte_ldVZ2(&facet_vertex2->vt.z);
              gte_rtpt();
              gte_nclip();
              gte_stMAC0();
              bfctResult_b = sd->bfct;
              if ((sd->head).mirror != 0) {
                bfctResult_b = -bfctResult_b;
              }
              uVar10 = facetIdx - 1;
            } while (bfctResult_b < 1);
            gte_avsz3();
            gte_stOTZ();
            ti34 = sd->otz + sd->sub_otz;
            sd->otz = ti34;
            if (ti34 < 0) goto DrawC_Prim_envmap0AltPath;
            uVar10 = facetIdx - 1;
          } while (sd->sub_otSize < ti34);
          puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
          (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
          *puVar17 = 0x07000000;
          AddPrim(sd->sub_ot + sd->otz,puVar17);
          /* Retail 0x800C0168..0x800C0170 stores SXY0..2 into the
             POLY_GT3 x/y words; the recovered gte_ldv3 name was inverted. */
          gte_swc2(12,puVar17 + 2);
          gte_swc2(13,puVar17 + 4);
          gte_swc2(14,puVar17 + 6);
          primTypeByte_b = 0x24;
          if (((u_short)facet_p_v3->flag & 1) != 0) {
            primTypeByte_b = 0x26;
          }
          puVar17[1] = sd->color;
          *(u_char *)((u_char *)puVar17 + 7) = primTypeByte_b;
          if (((u_short)facet_p_v3->flag & 1) == 0) {
            tu1 = sd->offsetU0;
            tu4 = sd->offsetV0;
            tu15 = sd->pmxStart[facet_p_v3->textureIndex].tpage;
            *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[facet_p_v3->textureIndex].clut;
            *(short *)((u_char *)puVar17 + 0x16) = tu15;
            cVar1 = (char)facet_p_v3->uv1.u;
            tc6 = (char)facet_p_v3->uv2.u;
            *(u_char *)(puVar17 + 3) = (char)facet_p_v3->uv0.u + tu1;
            *(u_char *)(puVar17 + 5) = cVar1 + tu1;
            *(u_char *)(puVar17 + 7) = tc6 + tu1;
            cVar1 = (char)facet_p_v3->uv1.v;
            tc6 = (char)facet_p_v3->uv2.v;
            *(u_char *)((u_char *)puVar17 + 0xd) = (char)facet_p_v3->uv0.v + tu4;
            *(u_char *)((u_char *)puVar17 + 0x15) = cVar1 + tu4;
            *(u_char *)((u_char *)puVar17 + 0x1d) = tc6 + tu4;
          }
          else {
            tu21 = sd->pmxStart[facet_p_v3->textureIndex].tpage;
            *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[facet_p_v3->textureIndex].clut;
            *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
            uVar8_00 = (u_short)facet_p_v3->uv1.u | (u_short)facet_p_v3->uv1.v << 8;
            tu19 = (short)((u_short)facet_p_v3->uv2.u | (u_short)facet_p_v3->uv2.v << 8);
            *(u_short *)(puVar17 + 3) = (u_short)facet_p_v3->uv0.u | (u_short)facet_p_v3->uv0.v << 8;
            *(u_short *)(puVar17 + 5) = uVar8_00;
            *(short *)(puVar17 + 7) = tu19;
          }
        } while( true );
      }
      primTypeByte_c = 0x24;
      iVar7 = facetIdx * 0xc;
DrawC_Prim_envmap1AltGT3:
      do {
        iVar8 = iVar7;
        uVar10 = facetIdx - 1;
        do {
          do {
            do {
              facetIdx = uVar10;
              iVar7 = iVar8 + -0xc;
              if (facetIdx == 0xffffffff) {
                return;
              }
              facet_iter = obj->facet + facetIdx;
              iVar8 = iVar7;
              uVar10 = facetIdx - 1;
            } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
            facet_vertex0 = sd->tV + facet_iter->vertexId0;
            facet_vertex1 = sd->tV + facet_iter->vertexId1;
            facet_vertex2 = sd->tV + facet_iter->vertexId2;
            gte_ldVXY0(facet_vertex0);
            gte_ldVZ0(&facet_vertex0->vt.z);
            gte_ldVXY1(facet_vertex1);
            gte_ldVZ1(&facet_vertex1->vt.z);
            gte_ldVXY2(facet_vertex2);
            gte_ldVZ2(&facet_vertex2->vt.z);
            gte_rtpt();
            gte_nclip();
            gte_stMAC0();
            bfctResult_c = sd->bfct;
            if ((sd->head).mirror != 0) {
              bfctResult_c = -bfctResult_c;
            }
            uVar10 = facetIdx - 1;
          } while (bfctResult_c < 1);
          gte_avsz3();
          gte_stOTZ();
          otz_check_b = sd->otz + sd->sub_otz;
          sd->otz = otz_check_b;
          if (otz_check_b < 0) goto DrawC_Prim_envmap1AltGT3;
          uVar10 = facetIdx - 1;
        } while (sd->sub_otSize < otz_check_b);
        primOut = (u_int *)(sd->head).cprim.PrimPtr;
        (sd->head).cprim.PrimPtr = (char *)(primOut + 8);
        *primOut = 0x07000000;
        AddPrim(sd->sub_ot + sd->otz,primOut);
        /* Retail 0x800C0370..0x800C0378: swc2 SXY0/SXY1/SXY2. */
        gte_swc2(12,primOut + 2);
        gte_swc2(13,primOut + 4);
        gte_swc2(14,primOut + 6);
        primOut[1] = sd->color;
        *(char *)((u_char *)primOut + 7) = (char)primTypeByte_c;
        facet_pmx = sd->pmxStart + facet_iter->textureIndex;
        if ((facet_pmx->flag & 0x7f) == 0) {
          uVar8_00 = facet_pmx->tpage;
          *(u_short *)((u_char *)primOut + 0xe) = facet_pmx->clut;
          *(u_short *)((u_char *)primOut + 0x16) = uVar8_00;
          tu8 = (short)((u_short)facet_iter->uv1.u | (u_short)facet_iter->uv1.v << 8);
          tu9 = (short)((u_short)facet_iter->uv2.u | (u_short)facet_iter->uv2.v << 8);
          *(u_short *)(primOut + 3) = (u_short)facet_iter->uv0.u | (u_short)facet_iter->uv0.v << 8;
          *(short *)(primOut + 5) = tu8;
          *(short *)(primOut + 7) = tu9;
        }
        else {
          tu2 = sd->offsetU1;
          tu3 = sd->offsetV1;
          if ((facet_pmx->flag & 2) != 0) {
            tu2 = sd->offsetU2;
            tu3 = sd->offsetV2;
          }
          tu7 = (short)facet_pmx->tpage;
          *(u_short *)((u_char *)primOut + 0xe) = facet_pmx->clut;
          *(short *)((u_char *)primOut + 0x16) = tu7;
          cVar1 = (char)facet_iter->uv1.u;
          tc6 = (char)facet_iter->uv2.u;
          *(u_char *)(primOut + 3) = (char)facet_iter->uv0.u + tu2;
          *(u_char *)(primOut + 5) = cVar1 + tu2;
          *(u_char *)(primOut + 7) = tc6 + tu2;
          cVar1 = (char)facet_iter->uv1.v;
          tc6 = (char)facet_iter->uv2.v;
          *(u_char *)((u_char *)primOut + 0xd) = (char)facet_iter->uv0.v + tu3;
          *(u_char *)((u_char *)primOut + 0x15) = cVar1 + tu3;
          *(u_char *)((u_char *)primOut + 0x1d) = tc6 + tu3;
        }
      } while( true );
    }
  }
  else {
    if (envmapMode == 8) {
      iVar7 = facetIdx * 0xc;
DrawC_Prim_envmap8OverlayTop:
      uVar10 = facetIdx - 1;
      iVar8 = iVar7;
DrawC_Prim_envmap8InnerLoop:
      while( true ) {
        do {
          do {
            facetIdx = uVar10;
            iVar7 = iVar8 + -0xc;
            if (facetIdx == 0xffffffff) {
              return;
            }
            facet_p_v2 = obj->facet + facetIdx;
            uVar10 = facetIdx - 1;
            iVar8 = iVar7;
          } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
          facet_vertex0 = sd->tV + facet_p_v2->vertexId0;
          facet_vertex1 = sd->tV + facet_p_v2->vertexId1;
          facet_vertex2 = sd->tV + facet_p_v2->vertexId2;
          gte_ldVXY0(facet_vertex0);
          gte_ldVZ0(&facet_vertex0->vt.z);
          gte_ldVXY1(facet_vertex1);
          gte_ldVZ1(&facet_vertex1->vt.z);
          gte_ldVXY2(facet_vertex2);
          gte_ldVZ2(&facet_vertex2->vt.z);
          gte_rtpt();
          gte_nclip();
          gte_stMAC0();
          iVar11 = sd->bfct;
          if ((sd->head).mirror != 0) {
            iVar11 = -iVar11;
          }
          uVar10 = facetIdx - 1;
        } while (iVar11 < 1);
        gte_avsz3();
        gte_stOTZ();
        iVar11 = (u_int)(u_short)DrawC_gOverlay[facet_p_v2->textureIndex] << 0x10;
        uVar9 = iVar11 >> 0x10;
        if (uVar9 == 0) break;
        uVar15 = (u_int)(short)facet_p_v2->flag;
        uVar9 = uVar9 & 0xff;
        if ((int)uVar15 < 0) {
          uVar9 = iVar11 >> 0x18;
        }
        iVar11 = sd->otz + sd->sub_otz;
        if ((uVar9 & 0x40) != 0) {
          iVar11 = iVar11 + -2;
        }
        uVar10 = facetIdx - 1;
        if ((-1 < iVar11) && (uVar10 = facetIdx - 1, iVar11 <= sd->sub_otSize)) {
          uVar10 = uVar15 & 0xfff;
          if (((uVar15 & 0x3f0) != 0) && (uVar9 = uVar9 & uVar10 >> 4, uVar9 != 0)) {
            for (; (uVar9 & 3) == 0; uVar9 = (int)uVar9 >> 2) {
            }
          }
          sd->otz = iVar11;
          goto DrawC_Prim_otStitch24Emit;
        }
      }
      iVar11 = sd->otz + sd->sub_otz;
      sd->otz = iVar11;
      if (-1 < iVar11) goto cfLbl1;
      goto DrawC_Prim_envmap8OverlayTop;
    }
    if (envmapMode == 9) {
      iVar7 = facetIdx * 0xc;
DrawC_Prim_envmap9LoopTop:
      uVar10 = facetIdx - 1;
      iVar8 = iVar7;
DrawC_Prim_envmap9InnerLoop:
      while (facetIdx = uVar10, iVar7 = iVar8 + -0xc, facetIdx != 0xffffffff) {
        facet_p_v4 = obj->facet + facetIdx;
        vert_a_idx2 = facet_p_v4->vertexId0;
        bVar2 = facet_p_v4->vertexId1;
        vert_c_idx2 = facet_p_v4->vertexId2;
        uVar10 = facetIdx - 1;
        iVar8 = iVar7;
        if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
          gte_ldVXY0(sd->tV + vert_a_idx2);
          gte_ldVZ0(&sd->tV[vert_a_idx2].vt.z);
          gte_ldVXY1(sd->tV + bVar2);
          gte_ldVZ1(&sd->tV[bVar2].vt.z);
          gte_ldVXY2(sd->tV + vert_c_idx2);
          gte_ldVZ2(&sd->tV[vert_c_idx2].vt.z);
          gte_rtpt();
          gte_nclip();
          gte_stMAC0();
          bfctResult_a = sd->bfct;
          if ((sd->head).mirror != 0) {
            bfctResult_a = -bfctResult_a;
          }
          uVar10 = facetIdx - 1;
          if (0 < bfctResult_a) {
            gte_stSXY0();
            gte_stSXY1();
            gte_stSXY2();
            gte_avsz3();
            gte_stOTZ();
            ot_offs_byte = (int)((u_int)(u_short)DrawC_gOverlay[facet_p_v4->textureIndex] << 0x10) >> 0x10;
            if (ot_offs_byte == 0) {
              iVar11 = sd->otz + sd->sub_otz;
              sd->otz = iVar11;
              if (-1 < iVar11) goto cfLbl2;
              goto DrawC_Prim_envmap9LoopTop;
            }
            uVar9 = (u_int)(short)facet_p_v4->flag;
            uVar15 = ot_offs_byte & 0xff;
            if ((int)uVar9 < 0) {
              uVar15 = (int)((u_int)(u_short)DrawC_gOverlay[facet_p_v4->textureIndex] << 0x10) >> 0x18;
            }
            iVar11 = sd->otz + sd->sub_otz;
            uVar10 = facetIdx - 1;
            if ((-1 < iVar11) && (uVar10 = facetIdx - 1, iVar11 <= sd->sub_otSize)) {
              facetIdx_dec = uVar9 & 0xfff;
              if (((uVar9 & 0x3f0) != 0) && (uVar15 = uVar15 & facetIdx_dec >> 4, uVar15 != 0)) {
                for (; (uVar15 & 3) == 0; uVar15 = (int)uVar15 >> 2) {
                }
              }
              sd->otz = iVar11;
              goto DrawC_Prim_ePmx1UVEmit;
            }
          }
        }
      }
    }
  }
  return;
cfLbl1:   /* @0x800c0a7c  (-f-build goto label) */
  uVar10 = facetIdx - 1;
  if (iVar11 <= sd->sub_otSize) goto cfLbl3;
  goto DrawC_Prim_envmap8InnerLoop;
cfLbl3:   /* @0x800c0a90  (-f-build goto label) */
  uVar10 = (u_short)facet_p_v2->flag & 0xfff;
  uVar9 = 0;
DrawC_Prim_otStitch24Emit:
  if ((uVar9 & 3) == 0) {
    puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
    *puVar17 = 0x07000000;
    AddPrim(puVar20 + iVar8,puVar17);
    /* Retail 0x800C0AFC..0x800C0B04: projected screen coordinates. */
    gte_swc2(12,puVar17 + 2);
    gte_swc2(13,puVar17 + 4);
    gte_swc2(14,puVar17 + 6);
    uVar15 = 0x808080;
    if ((uVar9 & 0x80) == 0) {
      uVar15 = sd->color;
    }
    primTypeByte = 0x24;
    if ((uVar10 & 1) != 0) {
      primTypeByte = 0x26;
    }
    puVar17[1] = uVar15;
    *(u_char *)((u_char *)puVar17 + 7) = primTypeByte;
    tu21 = sd->pmxStart[facet_p_v2->textureIndex].tpage;
    *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[facet_p_v2->textureIndex].clut;
    *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
    uVar8_00 = (u_short)facet_p_v2->uv1.u | (u_short)facet_p_v2->uv1.v << 8;
    tu23 = (u_short)facet_p_v2->uv2.u | (u_short)facet_p_v2->uv2.v << 8;
    *(u_short *)(puVar17 + 3) = (u_short)facet_p_v2->uv0.u | (u_short)facet_p_v2->uv0.v << 8;
    *(u_short *)(puVar17 + 5) = uVar8_00;
    *(u_short *)(puVar17 + 7) = tu23;
  }
  else {
    puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
    overlay_entry = overlay + (u_int)facet_p_v2->textureIndex * 3 + ((uVar9 & 3) - 1);
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
    *puVar17 = 0x07000000;
    AddPrim(puVar20 + iVar8,puVar17);
    /* Retail 0x800C0BE8..0x800C0BF0: same SXY FIFO stores. */
    gte_swc2(12,puVar17 + 2);
    gte_swc2(13,puVar17 + 4);
    gte_swc2(14,puVar17 + 6);
    uVar15 = 0x808080;
    if ((uVar9 & 0x80) == 0) {
      uVar15 = sd->color;
    }
    primTypeByte_d = 0x24;
    if ((uVar10 & 1) != 0) {
      primTypeByte_d = 0x26;
    }
    puVar17[1] = uVar15;
    *(u_char *)((u_char *)puVar17 + 7) = primTypeByte_d;
    tu5 = overlay_entry->u;
    uVar3 = overlay_entry->v;
    iVar8 = (u_int)facet_p_v2->textureIndex + (int)overlay_entry->offset;
    tu21 = sd->pmxStart[iVar8].tpage;
    *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[iVar8].clut;
    *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
    tu21 = (u_short)facet_p_v2->uv1.u | (u_short)facet_p_v2->uv1.v << 8;
    tu27 = (u_short)facet_p_v2->uv2.u | (u_short)facet_p_v2->uv2.v << 8;
    *(u_char *)(puVar17 + 3) = (char)facet_p_v2->uv0.u + tu5;
    *(u_char *)(puVar17 + 5) = (char)tu21 + tu5;
    *(u_char *)(puVar17 + 7) = (char)tu27 + tu5;
    cVar1 = (char)facet_p_v2->uv1.v;
    tc7 = facet_p_v2->uv2.v;
    *(u_char *)((u_char *)puVar17 + 0xd) = (char)facet_p_v2->uv0.v + uVar3;
    *(u_char *)((u_char *)puVar17 + 0x15) = cVar1 + uVar3;
    *(u_char *)((u_char *)puVar17 + 0x1d) = tc7 + uVar3;
  }
  goto DrawC_Prim_envmap8OverlayTop;
cfLbl2:   /* @0x800c0df4  (-f-build goto label) */
  uVar10 = facetIdx - 1;
  if (iVar11 <= sd->sub_otSize) goto cfLbl4;
  goto DrawC_Prim_envmap9InnerLoop;
cfLbl4:   /* @0x800c0e08  (-f-build goto label) */
  facetIdx_dec = (u_short)facet_p_v4->flag & 0xfff;
  uVar15 = 0;
DrawC_Prim_ePmx1UVEmit:
  if (((facetIdx_dec & 0x3f3) != 0) &&
     (((u_char *)&(vertA_matBPtr))[0] = (sd->ePmx1).u0, ((u_char *)&(vertA_matBPtr))[1] = (sd->ePmx1).v0,
     (*(u_short *)((u_char *)&(vertA_matBPtr) + 2)) = (sd->ePmx1).clut, vertA_matBPtr != 0)) {
    sd->vt0 = Nvertex_p[facet_p_v4->vertexId0];
    sd->vt1 = Nvertex_p[facet_p_v4->vertexId1];
    sd->vt2 = Nvertex_p[facet_p_v4->vertexId2];
    primOut_drmOff = (u_int *)(sd->head).cprim.PrimPtr;
    iVar8 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(primOut_drmOff + 3);
    drmodeOff_w0 = (u_int)(intptr)(sd->drawModeOff).tag;
    drmodeOff_w1 = (sd->drawModeOff).code[0];
    drmodeOff_w2 = (sd->drawModeOff).code[1];
    primOut_drmOff[0] = drmodeOff_w0;
    primOut_drmOff[1] = drmodeOff_w1;
    primOut_drmOff[2] = drmodeOff_w2;
    AddPrim(sub_ot_p + iVar8,primOut_drmOff);
    puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
    *puVar17 = 0x07000000;
    AddPrim(puVar20 + iVar8,puVar17);
    primOut_drm2 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(primOut_drm2 + 3);
    drmodeOn_tag = (u_int)(intptr)(sd->drawModeOn).tag;
    drmode_w0 = (sd->drawModeOn).code[0];
    drmodeOn_w1 = (sd->drawModeOn).code[1];
    primOut_drm2[0] = drmodeOn_tag;
    primOut_drm2[1] = drmode_w0;
    primOut_drm2[2] = drmodeOn_w1;
    AddPrim(puVar20 + iVar8,primOut_drm2);
    dvx1_word = *(int *)&sd->dvx1;
    uVar10 = *(u_int *)&sd->dvx2;
    puVar17[2] = *(u_int *)&sd->dvx0;
    puVar17[4] = dvx1_word;
    puVar17[6] = uVar10;
    puVar17[1] = sd->eColor0;
    *(u_char *)((u_char *)puVar17 + 7) = 0x26;
    tu21 = (sd->ePmx1).tpage;
    *(u_short *)((u_char *)puVar17 + 0xe) = (sd->ePmx1).clut;
    *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
    ePmx1_uOff2 = (sd->ePmx1).u0 + 0x40;
    vert_v_byte = (sd->ePmx1).v0 + (char)sd->eAddZ;
    ts7 = (sd->vt0).z;
    *(u_char *)(puVar17 + 3) = (char)(sd->vt0).y + ePmx1_uOff2;
    *(char *)((u_char *)puVar17 + 0xd) = (char)ts7 + vert_v_byte;
    ts7 = (sd->vt1).z;
    *(u_char *)(puVar17 + 5) = (char)(sd->vt1).y + ePmx1_uOff2;
    *(char *)((u_char *)puVar17 + 0x15) = (char)ts7 + vert_v_byte;
    ts7 = (sd->vt2).z;
    *(u_char *)(puVar17 + 7) = (char)(sd->vt2).y + ePmx1_uOff2;
    *(char *)((u_char *)puVar17 + 0x1d) = (char)ts7 + vert_v_byte;
  }
  ((u_char *)&(otz_check_a))[0] = (sd->ePmx0).u0;
  ((u_char *)&(otz_check_a))[1] = (sd->ePmx0).v0;
  (*(u_short *)((u_char *)&(otz_check_a) + 2)) = (sd->ePmx0).clut;
  if (otz_check_a != 0) {
    puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
    *puVar17 = 0x07000000;
    AddPrim(puVar20 + iVar8,puVar17);
    ot_offs_alt = *(u_int *)&sd->dvx1;
    uVar10 = *(u_int *)&sd->dvx2;
    puVar17[2] = *(u_int *)&sd->dvx0;
    puVar17[4] = ot_offs_alt;
    puVar17[6] = uVar10;
    if ((uVar15 & 1) == 0) {
      if ((facetIdx_dec & 4) == 0) {
        puVar17[1] = sd->eColor0;
      }
      else {
        puVar17[1] = sd->eColor1;
      }
    }
    else {
      puVar17[1] = sd->eColor2;
    }
    *(u_char *)((u_char *)puVar17 + 7) = 0x26;
    tu21 = (sd->ePmx0).tpage;
    *(u_short *)((u_char *)puVar17 + 0xe) = (sd->ePmx0).clut;
    *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
    tu5 = (sd->ePmx0).v0;
    vert_uv_b = (sd->ePmx0).u0 + '@';
    cVar1 = sd->tV[vert_a_idx2].v;
    *(char *)(puVar17 + 3) = sd->tV[vert_a_idx2].u + vert_uv_b;
    *(u_char *)((u_char *)puVar17 + 0xd) = cVar1 + tu5;
    cVar1 = sd->tV[bVar2].v;
    *(char *)(puVar17 + 5) = sd->tV[bVar2].u + vert_uv_b;
    *(u_char *)((u_char *)puVar17 + 0x15) = cVar1 + tu5;
    cVar1 = sd->tV[vert_c_idx2].v;
    *(char *)(puVar17 + 7) = sd->tV[vert_c_idx2].u + vert_uv_b;
    *(u_char *)((u_char *)puVar17 + 0x1d) = cVar1 + tu5;
  }
  if ((uVar15 & 3) == 0) {
    puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
    *puVar17 = 0x07000000;
    AddPrim(puVar20 + iVar8,puVar17);
    uVar10 = *(u_int *)&sd->dvx1;
    uVar15 = *(u_int *)&sd->dvx2;
    puVar17[2] = *(u_int *)&sd->dvx0;
    puVar17[4] = uVar10;
    puVar17[6] = uVar15;
    primTypeByte_b = 0x24;
    if ((facetIdx_dec & 1) != 0) {
      primTypeByte_b = 0x26;
    }
    puVar17[1] = sd->color;
    *(u_char *)((u_char *)puVar17 + 7) = primTypeByte_b;
    tu21 = sd->pmxStart[facet_p_v4->textureIndex].tpage;
    *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[facet_p_v4->textureIndex].clut;
    *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
    tu21 = (u_short)facet_p_v4->uv1.u | (u_short)facet_p_v4->uv1.v << 8;
    tu27 = (u_short)facet_p_v4->uv2.u | (u_short)facet_p_v4->uv2.v << 8;
    *(u_short *)(puVar17 + 3) = (u_short)facet_p_v4->uv0.u | (u_short)facet_p_v4->uv0.v << 8;
    *(u_short *)(puVar17 + 5) = tu21;
    *(u_short *)(puVar17 + 7) = tu27;
  }
  else {
    puVar17 = (u_int *)(sd->head).cprim.PrimPtr;
    pTVar16 = overlay + (u_int)facet_p_v4->textureIndex * 3 + ((uVar15 & 3) - 1);
    iVar8 = sd->otz;
    puVar20 = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar17 + 8);
    *puVar17 = 0x07000000;
    AddPrim(puVar20 + iVar8,puVar17);
    uVar10 = *(u_int *)&sd->dvx1;
    uVar15 = *(u_int *)&sd->dvx2;
    puVar17[2] = *(u_int *)&sd->dvx0;
    puVar17[4] = uVar10;
    puVar17[6] = uVar15;
    primTypeByte_b = 0x24;
    if ((facetIdx_dec & 1) != 0) {
      primTypeByte_b = 0x26;
    }
    puVar17[1] = sd->color;
    *(u_char *)((u_char *)puVar17 + 7) = primTypeByte_b;
    tu5 = pTVar16->u;
    uVar3 = pTVar16->v;
    iVar8 = (u_int)facet_p_v4->textureIndex + (int)pTVar16->offset;
    tu21 = sd->pmxStart[iVar8].tpage;
    *(u_short *)((u_char *)puVar17 + 0xe) = sd->pmxStart[iVar8].clut;
    *(u_short *)((u_char *)puVar17 + 0x16) = tu21;
    tu21 = (u_short)facet_p_v4->uv1.u | (u_short)facet_p_v4->uv1.v << 8;
    tu27 = (u_short)facet_p_v4->uv2.u | (u_short)facet_p_v4->uv2.v << 8;
    *(u_char *)(puVar17 + 3) = (char)facet_p_v4->uv0.u + tu5;
    *(u_char *)(puVar17 + 5) = (char)tu21 + tu5;
    *(u_char *)(puVar17 + 7) = (char)tu27 + tu5;
    cVar1 = (char)facet_p_v4->uv1.v;
    tc6 = (char)facet_p_v4->uv2.v;
    *(u_char *)((u_char *)puVar17 + 0xd) = (char)facet_p_v4->uv0.v + uVar3;
    *(u_char *)((u_char *)puVar17 + 0x15) = cVar1 + uVar3;
    *(u_char *)((u_char *)puVar17 + 0x1d) = tc6 + uVar3;
  }
  goto DrawC_Prim_envmap9LoopTop;
}

/* ---- DrawC_DividePrim__FP7COORD16N20PUsN23P12Draw_tPixMapP13Draw_CarCache  [DRAWC.CPP:2554-2644] SLD-VERIFIED ---- */
void DrawC_DividePrim(COORD16 *vt0,COORD16 *vt1,COORD16 *vt2,u_short *u0,u_short *u1,u_short *u2,
               Draw_tPixMap *pmx,Draw_CarCache *sd)

{
  POLY_FT3 * prim;
  int bfct;
  long xy0;
  long xy1;
  long xy2;
  u_long color;
  u_char code;
  u_short uv1;
  u_short uv2;
  short sVar1;
  short sVar2;
  u_short uVar3;
  u_short uVar4;
  u_int *puVar5;
  u_short clut;
  int clipW;
  u_short tpage;
  int iVar6;
  u_int *puVar7;
  u_short uv0;
  u_int uVar8;
  u_int uVar9;
  int clipH;
  u_long *puVar10;
  
  if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
gte_lwc2(0,*(int *)(vt0));
    gte_lwc2(1,*(int *)(((char *)vt0 + 0x4)));
    gte_lwc2(2,*(int *)(vt1));
    gte_lwc2(3,*(int *)(((char *)vt1 + 0x4)));
    gte_lwc2(4,*(int *)(vt2));
    gte_lwc2(5,*(int *)(((char *)vt2 + 0x4)));
    gte_rtpt();
    gte_nclip();
    gte_stMAC0();
    iVar6 = sd->bfct;
    if ((sd->head).mirror != 0) {
      iVar6 = -iVar6;
    }
    if (0 < iVar6) {
      gte_stSXY0();
      gte_stSXY1();
      gte_stSXY2();
      sVar1 = (sd->head).clipW;
      sVar2 = (sd->head).clipH;
      if (((((((sd->dvx0 <= sVar1) || (sd->dvx1 <= sVar1)) || (sd->dvx2 <= sVar1)) &&
            (((-1 < sd->dvx0 || (-1 < sd->dvx1)) || (-1 < sd->dvx2)))) &&
           (((sd->dvy0 <= sVar2 || (sd->dvy1 <= sVar2)) || (sd->dvy2 <= sVar2)))) &&
          (((-1 < sd->dvy0 || (-1 < sd->dvy1)) || (-1 < sd->dvy2)))) &&
         (((-1 < vt0->z || (-1 < vt1->z)) || (-1 < vt2->z)))) {
        gte_avsz3();
        gte_stOTZ();
        iVar6 = sd->otz + sd->sub_otz;
        sd->otz = iVar6;
        if ((-1 < iVar6) && (iVar6 <= sd->sub_otSize)) {
          puVar7 = (u_int *)(sd->head).cprim.PrimPtr;
          iVar6 = sd->otz;
          puVar10 = sd->sub_ot;
          (sd->head).cprim.PrimPtr = (char *)(puVar7 + 8);
          *puVar7 = 0x07000000;
          AddPrim(puVar10 + iVar6,puVar7);
          uVar8 = *(u_int *)&sd->dvx1;
          uVar9 = *(u_int *)&sd->dvx2;
          puVar7[2] = *(u_int *)&sd->dvx0;
          puVar7[4] = uVar8;
          puVar7[6] = uVar9;
          puVar7[1] = sd->color;
          ((u_char *)puVar7)[7] = 0x24;
          uVar3 = pmx->tpage;
          *(u_short *)((u_char *)puVar7 + 0xe) = pmx->clut;
          *(u_short *)((u_char *)puVar7 + 0x16) = uVar3;
          uVar3 = *u1;
          uVar4 = *u2;
          *(u_short *)(puVar7 + 3) = *u0;
          *(u_short *)(puVar7 + 5) = uVar3;
          *(u_short *)(puVar7 + 7) = uVar4;
        }
      }
    }
  }
  return;
}

/* ---- DrawC_PrimClip__FP10matrixtdefP8coorddefP16Transformer_zObjP20Transformer_zOverlayiP13Draw_CarCache  [DRAWC.CPP:2647-3495] SLD-VERIFIED ---- */
void DrawC_PrimClip(matrixtdef *m,coorddef *t,Transformer_zObj *obj,Transformer_zOverlay *overlay,
               int envmap,Draw_CarCache *sd)

{
  COORD16 * Nvertice;
  COORD16 * vt;
  short t1;
  short t2;
  short t3;
  int r0;
  int r1;
  int r2;
  PCOORD16 * tV;
  int x;
  int y;
  int z;
  POLY_FT3 * prim;
  Transformer_zFacet * facet;
  int id0;
  int id1;
  int id2;
  int bfct;
  int clipW;
  int clipH;
  long xy0;
  long xy1;
  long xy2;
  u_long color;
  Draw_tPixMap * pmx;
  u_char u0;
  u_char v0;
  u_char v1;
  u_char v2;
  u_char offsetU;
  u_char offsetV;
  u_short uv0;
  u_short uv1;
  int overlayFlag;
  short facetFlag;
  int facet_flag;
  int sd_otz;
  int index;
  int which;
  Transformer_zOverlay * facetOverlay;
  char cVar1;
  u_char bVar3;
  short sVar4;
  short sVar5;
  u_short uVar6;
  u_int *puVar7;
  u_short clut;
  int absZ_envmap;
  int tu20;
  Draw_CarVertex *tD21;
  int ePmx1_pack;
  int ePmx0_pack;
  int absZ;
  int tps22;
  short *vert_xyz_iter;
  u_char primTypeByte;
  short *psVar8;
  int ti16;
  u_short tpage;
  int matRow0_w1;
  int matRow_temp;
  int vy_word;
  u_int facetIdx_dec;
  u_char primTypeByte_b;
  int bfctResult_b;
  int bfctResult_c;
  int tu21;
  Draw_tPixMap *tD22;
  Draw_CarVertex *tD23;
  int bfctResult_a;
  int tu25;
  u_short uv2;
  u_int tu40;
  u_int uVar9;
  u_char uVar10;
  u_char u;
  int iVar11;
  int iVar12;
  int vz_word;
  Draw_CarVertex *pDVar13;
  u_int uVar14;
  u_int uVar15;
  u_int uVar16;
  u_char uVar17;
  u_char bVar18;
  u_char v;
  Draw_tPixMap *pDVar19;
  int iVar20;
  char *envmapUV_dst;
  u_char uVar21;
  short *psVar22;
  Transformer_zFacet *puVar23;
  Transformer_zOverlay *pTVar24;
  u_int uVar25;
  int ot_offs_byte;
  u_int uVar26;
  Draw_CarVertex *tV_dst;
  u_int *facet_p_v3;
  Transformer_zFacet *overlay_entry;
  u_int *facet_p_v4;
  u_int *primOut;
  u_int *puVar27;
  Transformer_zFacet *facet_iter;
  COORD16 *vertex_p;
  Transformer_zFacet *facet_p_v2;
  Transformer_zFacet *facet_p_v1;
  int vertIdx2;
  int tu41;
  int vertIdx1;
  int loopDoneTag;
  int loopDoneTag2;
  int vertIdx0;
  u_int *primOut_drm;
  u_int *primOut_drmOn;
  u_int *primOut_drmOff;
  u_int *tp43;
  u_long *puVar28;
  int tu45;
  u_long *sub_ot_p;
  int tu43;
  u_char ePmx1_uOff;
  u_char tc45;
  char vert_v_byte;
  u_char ePmx0_uOff;
  char tc57;
  u_char ePmx1_vOff;
  int tu47;
  u_long drmodeOn_w0;
  int tu49;
  u_long drmodeOn_w1;
  int i;
  int facetCount;
  int vertCounter;
  u_int facetIdx;
  COORD16 *Nvertex_buf;
  COORD16 *Nvertex_p;
  u_char *u2;
  u_char code;
  COORD16 *vt2_00;
  u_char *u2_00;
  u_char *u1;
  COORD16 *vt1;
  COORD16 *vt2;
  short tu10;
  short tu11;
  u_char ePmx0_vOff;
  u_char vert_a_idx;
  u_char vert_c_idx;
  u_short tpage_alt;
  short clipW_or_vz;
  short clipH_or_vz;
  u_short uv_pack_alt;
  u_char bVar2;
  short ts3;
  short ts4;
  short matRow_y;
  u_char bVar1;
  int ot_stitch_p;
  short matRow_z;
  short tu7;
  short ts8;
  short ts9;
  u_char tu6;
  u_char tc7;
  u_char bVar8;
  short ts10;
  u_char vert_a_idx2;
  u_char vert_b_idx2;
  u_char tu5;
  short tu15;
  short tu16;
  int ot_stitch_pa;
  u_short tu19;
  short ts11;
  short vert_y;
  short vert_z;
  short tu14;
  short *vert_yz_iter;
  u_char vert_b_idx;
  short ts14;
  short ts15;
  u_short tu33;
  u_short uv_pack_b;

  NFSHS_DIAGNOSTIC_CALL(NFSHS_HostTraceDrawCPrimEntry(m,t,obj,overlay,envmap | 0x40000000,sd));
  
  ((u_char *)&(iVar11))[0] = (sd->ePmx0).u0;
  ((u_char *)&(iVar11))[1] = (sd->ePmx0).v0;
  (*(u_short *)((u_char *)&(iVar11) + 2)) = (sd->ePmx0).clut;
  Nvertex_p = obj->Nvertex;
  if ((iVar11 == 0) &&
     (((u_char *)&(iVar12))[0] = (sd->ePmx1).u0, ((u_char *)&(iVar12))[1] = (sd->ePmx1).v0, (*(u_short *)((u_char *)&(iVar12) + 2)) = (sd->ePmx1).clut,
     iVar12 == 0)) {
    envmap = envmap & 0xbe;
  }
  if ((envmap & 1U) != 0) {
    psVar8 = (short *)Nvertex_p;
gte_SetRotMatrix(&DrawC_gMatA);
gte_SetTransMatrix(&DrawC_gMatA);
    loopDoneTag = -1;
    envmapUV_dst = &sd->tV[0].v;
    vert_yz_iter = &Nvertex_p->z;
    facetCount = (int)obj->numVertex;
    while (facetCount = facetCount + -1, facetCount != loopDoneTag) {
      matRow_y = vert_yz_iter[-1];
      matRow_z = *vert_yz_iter;
      (sd->vt0).x = *psVar8;
      (sd->vt0).y = matRow_y;
      (sd->vt0).z = matRow_z;
gte_lwc2(0,*(int *)(((char *)sd + 0xac)));
      gte_lwc2(1,*(int *)(((char *)sd + 0xb0)));
      gte_rt();
gte_swc2(0x19,((char *)sd + 0x9c));
      gte_swc2(0x1a,((char *)sd + 0xa0));
      gte_swc2(0x1b,((char *)sd + 0xa4));
      absZ_envmap = (sd->tv).vz;
      if (absZ_envmap < 0) {
        absZ_envmap = -absZ_envmap;
      }
      vert_yz_iter = vert_yz_iter + 3;
      psVar8 = psVar8 + 3;
      envmapUV_dst[-1] = (char)(sd->tv).vx;
      *envmapUV_dst = (char)absZ_envmap;
      envmapUV_dst = envmapUV_dst + 8;
    }
  }
  TrsProj_SetTransPrecision(8);
  matRow0_w1 = m->m[3];
  iVar11 = m->m[6];
  (sd->matB).m[0][0] = (short)(m->m[0] >> 4);
  (sd->matB).m[0][1] = (short)(matRow0_w1 >> 4);
  (sd->matB).m[0][2] = (short)(iVar11 >> 4);
  matRow_temp = m->m[4];
  iVar11 = m->m[7];
  (sd->matB).m[1][0] = (short)(m->m[1] >> 4);
  (sd->matB).m[1][1] = (short)(matRow_temp >> 4);
  (sd->matB).m[1][2] = (short)(iVar11 >> 4);
  iVar11 = m->m[5];
  iVar12 = m->m[8];
  (sd->matB).m[2][0] = (short)(m->m[2] >> 4);
  (sd->matB).m[2][1] = (short)(iVar11 >> 4);
  (sd->matB).m[2][2] = (short)(iVar12 >> 4);
  iVar11 = TrsProj_precision;
  (sd->matB).t[0] = t->x >> (TrsProj_precision & 0x1fU);
  (sd->matB).t[1] = t->y >> (iVar11 & 0x1fU);
  (sd->matB).t[2] = t->z >> (iVar11 & 0x1fU);
  TrsProj_ResetTransPrecision();
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
  tV_dst = sd->tV;
  loopDoneTag2 = -1;
  psVar8 = &sd->tV[0].vt.z;
  vertex_p = obj->vertex;
  vertCounter = (int)obj->numVertex;
  psVar22 = &vertex_p->z;
  while (vertCounter = vertCounter + -1, vertCounter != loopDoneTag2) {
    vert_y = psVar22[-1];
    vert_z = *psVar22;
    tV_dst->vt.x = vertex_p->x;
    psVar8[-1] = vert_y;
    *psVar8 = vert_z;
    /* 0x800C17F4/17F8 load through a3, advanced by 8 at 0x800C183C.
       Each vertex is transformed once; sd+0xd0 is only the first vertex. */
    int vertexXY, vertexZ;
    nfs4_mips_copy_bytes(&vertexXY,&tV_dst->vt,4);
    nfs4_mips_copy_bytes(&vertexZ,(char *)&tV_dst->vt + 4,4);
    gte_lwc2(0,vertexXY);
    gte_lwc2(1,vertexZ);
    gte_rt();
gte_swc2(0x19,((char *)sd + 0x9c));
    gte_swc2(0x1a,((char *)sd + 0xa0));
    gte_swc2(0x1b,((char *)sd + 0xa4));
    psVar22 = psVar22 + 3;
    vy_word = (sd->tv).vy;
    vz_word = (sd->tv).vz;
    vertex_p = vertex_p + 1;
    tV_dst->vt.x = (short)(sd->tv).vx;
    psVar8[-1] = (short)vy_word;
    *psVar8 = (short)vz_word;
    psVar8 = psVar8 + 4;
    tV_dst = tV_dst + 1;
  }
gte_SetRotMatrix(&DrawC_gScreenMat);
gte_SetTransMatrix(&DrawC_gScreenMat);
  facetIdx = (u_int)obj->numFacet;
  facetIdx_dec = envmap & 9;
  if (facetIdx_dec == 1) {
    iVar11 = facetIdx * 0xc;
DrawC_PrimClip_envmap9Eq1Loop:
    do {
      iVar12 = iVar11;
      uVar9 = facetIdx - 1;
      do {
        do {
          do {
            do {
              facetIdx = uVar9;
              iVar11 = iVar12 + -0xc;
              if (facetIdx == 0xffffffff) {
                return;
              }
              puVar23 = obj->facet + facetIdx;
              bVar18 = puVar23->vertexId0;
              vert_b_idx = puVar23->vertexId1;
              bVar3 = puVar23->vertexId2;
              iVar12 = iVar11;
              uVar9 = facetIdx - 1;
            } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
            gte_ldVXY0(sd->tV + bVar18);
            gte_ldVZ0(&sd->tV[bVar18].vt.z);
            gte_ldVXY1(sd->tV + vert_b_idx);
            gte_ldVZ1(&sd->tV[vert_b_idx].vt.z);
            gte_ldVXY2(sd->tV + bVar3);
            gte_ldVZ2(&sd->tV[bVar3].vt.z);
            gte_rtpt();
            gte_nclip();
            gte_stMAC0();
            iVar20 = sd->bfct;
            if ((sd->head).mirror != 0) {
              iVar20 = -iVar20;
            }
            uVar9 = facetIdx - 1;
          } while (iVar20 < 1);
          gte_stSXY0();
          gte_stSXY1();
          gte_stSXY2();
          sVar4 = sd->tV[vert_b_idx].vt.z;
          sVar5 = sd->tV[bVar3].vt.z;
          (sd->vt0).z = sd->tV[bVar18].vt.z;
          (sd->vt1).z = sVar4;
          (sd->vt2).z = sVar5;
          sVar4 = (sd->head).clipW;
          sVar5 = (sd->head).clipH;
        } while ((((((sVar4 < sd->dvx0) && (sVar4 < sd->dvx1)) &&
                   (uVar9 = facetIdx - 1, sVar4 < sd->dvx2)) ||
                  (((sd->dvx0 < 0 && (sd->dvx1 < 0)) && (uVar9 = facetIdx - 1, sd->dvx2 < 0)))) ||
                 (((sVar5 < sd->dvy0 && (sVar5 < sd->dvy1)) &&
                  (uVar9 = facetIdx - 1, sVar5 < sd->dvy2)))) ||
                ((((sd->dvy0 < 0 && (sd->dvy1 < 0)) && (uVar9 = facetIdx - 1, sd->dvy2 < 0)) ||
                 ((((sd->vt0).z < 0 && ((sd->vt1).z < 0)) && (uVar9 = facetIdx - 1, (sd->vt2).z < 0)
                  )))));
        gte_avsz3();
        gte_stOTZ();
        iVar20 = sd->otz + sd->sub_otz;
        sd->otz = iVar20;
        if (iVar20 < 0) goto DrawC_PrimClip_envmap9Eq1Loop;
        uVar9 = facetIdx - 1;
      } while (sd->sub_otSize < iVar20);
      if ((((u_short)puVar23->flag & 0x3f3) != 0) &&
         (((u_char *)&(ePmx1_pack))[0] = (sd->ePmx1).u0, ((u_char *)&(ePmx1_pack))[1] = (sd->ePmx1).v0,
         (*(u_short *)((u_char *)&(ePmx1_pack) + 2)) = (sd->ePmx1).clut, ePmx1_pack != 0)) {
        sd->vt0 = Nvertex_p[puVar23->vertexId0];
        sd->vt1 = Nvertex_p[puVar23->vertexId1];
        sd->vt2 = Nvertex_p[puVar23->vertexId2];
        primOut_drm = (u_int *)(sd->head).cprim.PrimPtr;
        iVar12 = sd->otz;
        sub_ot_p = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(primOut_drm + 3);
        puVar28 = (u_long *)(intptr)(sd->drawModeOff).tag;
        uVar9 = (sd->drawModeOff).code[0];
        uVar26 = (sd->drawModeOff).code[1];
        *primOut_drm = (u_int)(intptr)puVar28;
        primOut_drm[1] = uVar9;
        primOut_drm[2] = uVar26;
        AddPrim(sub_ot_p + iVar12,primOut_drm);
        puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
        iVar12 = sd->otz;
        sub_ot_p = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
        *puVar27 = 0x07000000;
        AddPrim(sub_ot_p + iVar12,puVar27);
        primOut_drmOn = (u_int *)(sd->head).cprim.PrimPtr;
        iVar12 = sd->otz;
        sub_ot_p = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(primOut_drmOn + 3);
        puVar28 = (u_long *)(intptr)(sd->drawModeOn).tag;
        drmodeOn_w0 = (sd->drawModeOn).code[0];
        drmodeOn_w1 = (sd->drawModeOn).code[1];
        primOut_drmOn[0] = (u_int)(intptr)puVar28;
        primOut_drmOn[1] = drmodeOn_w0;
        primOut_drmOn[2] = drmodeOn_w1;
        AddPrim(sub_ot_p + iVar12,primOut_drmOn);
        uVar9 = *(u_int *)&sd->dvx1;
        uVar26 = *(u_int *)&sd->dvx2;
        puVar27[2] = *(u_int *)&sd->dvx0;
        puVar27[4] = uVar9;
        puVar27[6] = uVar26;
        puVar27[1] = sd->eColor0;
        *(u_char *)((u_char *)puVar27 + 7) = 0x26;
        uVar6 = (sd->ePmx1).tpage;
        *(u_short *)((u_char *)puVar27 + 0xe) = (sd->ePmx1).clut;
        *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
        ePmx1_uOff = (sd->ePmx1).u0 + 0x40;
        ePmx1_vOff = (sd->ePmx1).v0 + (char)sd->eAddZ;
        sVar4 = (sd->vt0).z;
        *(u_char *)(puVar27 + 3) = (char)(sd->vt0).y + ePmx1_uOff;
        *(u_char *)((u_char *)puVar27 + 0xd) = (char)sVar4 + ePmx1_vOff;
        sVar4 = (sd->vt1).z;
        *(u_char *)(puVar27 + 5) = (char)(sd->vt1).y + ePmx1_uOff;
        *(u_char *)((u_char *)puVar27 + 0x15) = (char)sVar4 + ePmx1_vOff;
        sVar4 = (sd->vt2).z;
        *(u_char *)(puVar27 + 7) = (char)(sd->vt2).y + ePmx1_uOff;
        *(u_char *)((u_char *)puVar27 + 0x1d) = (char)sVar4 + ePmx1_vOff;
      }
      ((u_char *)&(ePmx0_pack))[0] = (sd->ePmx0).u0;
      ((u_char *)&(ePmx0_pack))[1] = (sd->ePmx0).v0;
      (*(u_short *)((u_char *)&(ePmx0_pack) + 2)) = (sd->ePmx0).clut;
      if (ePmx0_pack != 0) {
        puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
        iVar12 = sd->otz;
        sub_ot_p = sd->sub_ot;
        (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
        *puVar27 = 0x07000000;
        AddPrim(sub_ot_p + iVar12,puVar27);
        uVar9 = *(u_int *)&sd->dvx1;
        uVar26 = *(u_int *)&sd->dvx2;
        puVar27[2] = *(u_int *)&sd->dvx0;
        puVar27[4] = uVar9;
        puVar27[6] = uVar26;
        puVar27[1] = sd->eColor0;
        *(u_char *)((u_char *)puVar27 + 7) = 0x26;
        uVar6 = (sd->ePmx0).tpage;
        *(u_short *)((u_char *)puVar27 + 0xe) = (sd->ePmx0).clut;
        *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
        uVar17 = (sd->ePmx0).v0;
        ePmx0_uOff = (sd->ePmx0).u0 + 0x40;
        cVar1 = sd->tV[bVar18].v;
        *(u_char *)(puVar27 + 3) = sd->tV[bVar18].u + ePmx0_uOff;
        *(u_char *)((u_char *)puVar27 + 0xd) = cVar1 + uVar17;
        cVar1 = sd->tV[vert_b_idx].v;
        *(u_char *)(puVar27 + 5) = sd->tV[vert_b_idx].u + ePmx0_uOff;
        *(u_char *)((u_char *)puVar27 + 0x15) = cVar1 + uVar17;
        cVar1 = sd->tV[bVar3].v;
        *(u_char *)(puVar27 + 7) = sd->tV[bVar3].u + ePmx0_uOff;
        *(u_char *)((u_char *)puVar27 + 0x1d) = cVar1 + uVar17;
      }
      puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
      iVar12 = sd->otz;
      sub_ot_p = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
      *puVar27 = 0x07000000;
      AddPrim(sub_ot_p + iVar12,puVar27);
      uVar9 = *(u_int *)&sd->dvx1;
      uVar26 = *(u_int *)&sd->dvx2;
      puVar27[2] = *(u_int *)&sd->dvx0;
      puVar27[4] = uVar9;
      puVar27[6] = uVar26;
      puVar27[1] = sd->color;
      *(u_char *)((u_char *)puVar27 + 7) = 0x24;
      uVar6 = sd->pmxStart[puVar23->textureIndex].tpage;
      *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[puVar23->textureIndex].clut;
      *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
      uVar6 = (u_short)puVar23->uv1.u | (u_short)puVar23->uv1.v << 8;
      uv_pack_alt = (u_short)puVar23->uv2.u | (u_short)puVar23->uv2.v << 8;
      *(u_short *)(puVar27 + 3) = (u_short)puVar23->uv0.u | (u_short)puVar23->uv0.v << 8;
      *(u_short *)(puVar27 + 5) = uVar6;
      *(u_short *)(puVar27 + 7) = uv_pack_alt;
    } while( true );
  }
  if (facetIdx_dec < 2) {
    if (facetIdx_dec == 0) {
      vt1 = &sd->vt3;
      if ((envmap & 0x20U) == 0) {
        iVar11 = facetIdx * 0xc;
DrawC_PrimClip_envmap20Main:
        do {
          iVar12 = iVar11;
          uVar9 = facetIdx - 1;
          do {
            do {
              do {
                do {
                  facetIdx = uVar9;
                  iVar11 = iVar12 + -0xc;
                  if (facetIdx == 0xffffffff) {
                    return;
                  }
                  facet_p_v2 = obj->facet + facetIdx;
                  vert_a_idx2 = facet_p_v2->vertexId0;
                  vert_b_idx2 = facet_p_v2->vertexId1;
                  bVar1 = facet_p_v2->vertexId2;
                  iVar12 = iVar11;
                  uVar9 = facetIdx - 1;
                } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
                gte_ldVXY0(sd->tV + vert_a_idx2);
                gte_ldVZ0(&sd->tV[vert_a_idx2].vt.z);
                gte_ldVXY1(sd->tV + vert_b_idx2);
                gte_ldVZ1(&sd->tV[vert_b_idx2].vt.z);
                gte_ldVXY2(sd->tV + bVar1);
                gte_ldVZ2(&sd->tV[bVar1].vt.z);
                gte_rtpt();
                gte_nclip();
                gte_stMAC0();
                bfctResult_b = sd->bfct;
                if ((sd->head).mirror != 0) {
                  bfctResult_b = -bfctResult_b;
                }
                uVar9 = facetIdx - 1;
              } while (bfctResult_b < 1);
              gte_stSXY0();
              gte_stSXY1();
              gte_stSXY2();
              clipW_or_vz = sd->tV[vert_b_idx2].vt.z;
              clipH_or_vz = sd->tV[bVar1].vt.z;
              (sd->vt0).z = sd->tV[vert_a_idx2].vt.z;
              (sd->vt1).z = clipW_or_vz;
              (sd->vt2).z = clipH_or_vz;
              sVar4 = (sd->head).clipW;
              sVar5 = (sd->head).clipH;
            } while (((((sVar4 < sd->dvx0) && (sVar4 < sd->dvx1)) &&
                      (uVar9 = facetIdx - 1, sVar4 < sd->dvx2)) ||
                     (((sd->dvx0 < 0 && (sd->dvx1 < 0)) && (uVar9 = facetIdx - 1, sd->dvx2 < 0))))
                    || ((((sVar5 < sd->dvy0 && (sVar5 < sd->dvy1)) &&
                         (uVar9 = facetIdx - 1, sVar5 < sd->dvy2)) ||
                        ((((sd->dvy0 < 0 && (sd->dvy1 < 0)) && (uVar9 = facetIdx - 1, sd->dvy2 < 0))
                         || ((((sd->vt0).z < 0 && ((sd->vt1).z < 0)) &&
                             (uVar9 = facetIdx - 1, (sd->vt2).z < 0))))))));
            gte_avsz3();
            gte_stOTZ();
            bfctResult_c = sd->otz + sd->sub_otz;
            sd->otz = bfctResult_c;
            if (bfctResult_c < 0) goto DrawC_PrimClip_envmap20Main;
            uVar9 = facetIdx - 1;
          } while (sd->sub_otSize < bfctResult_c);
          facet_p_v3 = (u_int *)(sd->head).cprim.PrimPtr;
          (sd->head).cprim.PrimPtr = (char *)(facet_p_v3 + 8);
          facet_p_v3[0] = 0x07000000;
          AddPrim(sd->sub_ot + sd->otz,facet_p_v3);
          tu20 = *(int *)&sd->dvx0;
          tu21 = *(int *)&sd->dvx1;
          facet_p_v3[6] = *(u_int *)&sd->dvx2;
          facet_p_v3[2] = tu20;
          facet_p_v3[4] = tu21;
          uVar10 = 0x24;
          if (((u_short)facet_p_v2->flag & 1) != 0) {
            uVar10 = 0x26;
          }
          facet_p_v3[1] = sd->color;
          *(u_char *)((u_char *)facet_p_v3 + 7) = uVar10;
          if (((envmap & 2U) == 0) || (((u_short)facet_p_v2->flag & 1) != 0)) {
            tD22 = sd->pmxStart + facet_p_v2->textureIndex;
            if ((tD22->flag & 0x7f) == 0) {
              uv_pack_b = tD22->tpage;
              *(u_short *)((u_char *)facet_p_v3 + 0xe) = tD22->clut;
              *(u_short *)((u_char *)facet_p_v3 + 0x16) = uv_pack_b;
              uv_pack_b = (u_short)facet_p_v2->uv1.u | (u_short)facet_p_v2->uv1.v << 8;
              tu15 = (short)((u_short)facet_p_v2->uv2.u | (u_short)facet_p_v2->uv2.v << 8);
              *(u_short *)((u_char *)facet_p_v3 + 0xc) = (u_short)facet_p_v2->uv0.u | (u_short)facet_p_v2->uv0.v << 8;
              *(u_short *)((u_char *)facet_p_v3 + 0x14) = uv_pack_b;
              *(short *)((u_char *)facet_p_v3 + 0x1c) = tu15;
              goto DrawC_PrimClip_envmap20Main;
            }
            uVar17 = sd->offsetU1;
            uVar21 = sd->offsetV1;
            if ((tD22->flag & 2) != 0) {
              uVar17 = sd->offsetU2;
              uVar21 = sd->offsetV2;
            }
            tu14 = (short)tD22->tpage;
            *(u_short *)((u_char *)facet_p_v3 + 0xe) = tD22->clut;
            *(short *)((u_char *)facet_p_v3 + 0x16) = tu14;
          }
          else {
            uVar17 = sd->offsetU0;
            uVar21 = sd->offsetV0;
            tu7 = sd->pmxStart[facet_p_v2->textureIndex].tpage;
            *(u_short *)((u_char *)facet_p_v3 + 0xe) = sd->pmxStart[facet_p_v2->textureIndex].clut;
            *(short *)((u_char *)facet_p_v3 + 0x16) = tu7;
          }
          cVar1 = (char)facet_p_v2->uv1.u;
          tc57 = (char)facet_p_v2->uv2.u;
          *(u_char *)((u_char *)facet_p_v3 + 0xc) = (char)facet_p_v2->uv0.u + uVar17;
          *(u_char *)((u_char *)facet_p_v3 + 0x14) = cVar1 + uVar17;
          *(u_char *)((u_char *)facet_p_v3 + 0x1c) = tc57 + uVar17;
          cVar1 = (char)facet_p_v2->uv1.v;
          tc57 = (char)facet_p_v2->uv2.v;
          *(u_char *)((u_char *)facet_p_v3 + 0xd) = (char)facet_p_v2->uv0.v + uVar21;
          *(u_char *)((u_char *)facet_p_v3 + 0x15) = cVar1 + uVar21;
          *(u_char *)((u_char *)facet_p_v3 + 0x1d) = tc57 + uVar21;
        } while( true );
      }
      vt2 = &sd->vt5;
      u1 = &sd->u3;
      u2_00 = &sd->u5;
      vt2_00 = &sd->vt4;
      u2 = &sd->u4;
      iVar11 = facetIdx * 0xc;
      while( true ) {
        facetIdx = facetIdx - 1;
        iVar11 = iVar11 + -0xc;
        if (facetIdx == 0xffffffff) break;
        overlay_entry = obj->facet + facetIdx;
        vert_a_idx = overlay_entry->vertexId2;
        bVar2 = overlay_entry->textureIndex;
        tD21 = sd->tV + overlay_entry->vertexId0;
        tD23 = sd->tV + overlay_entry->vertexId1;
        sd->vt0 = tD21->vt;
        sVar4 = tD23->vt.y;
        sVar5 = tD23->vt.z;
        pDVar13 = sd->tV + vert_a_idx;
        (sd->vt1).x = tD23->vt.x;
        (sd->vt1).y = sVar4;
        (sd->vt1).z = sVar5;
        ts8 = (pDVar13->vt).x;
        ts9 = (pDVar13->vt).y;
        sVar4 = (sd->vt0).x;
        sVar5 = (sd->vt1).x;
        ts3 = (sd->vt0).y;
        (sd->vt2).z = (pDVar13->vt).z;
        ts4 = (sd->vt1).y;
        (sd->vt3).x = (short)((int)sVar4 + (int)sVar5 + 1 >> 1);
        sVar4 = (sd->vt0).z;
        (sd->vt2).x = ts8;
        (sd->vt2).y = ts9;
        sVar5 = (sd->vt1).z;
        (sd->vt3).y = (short)((int)ts3 + (int)ts4 + 1 >> 1);
        ts10 = (sd->vt1).x;
        ts11 = (sd->vt2).x;
        (sd->vt3).z = (short)((int)sVar4 + (int)sVar5 + 1 >> 1);
        pDVar19 = sd->pmxStart;
        (sd->vt4).x = (short)((int)ts10 + (int)ts11 + 1 >> 1);
        sVar4 = (sd->vt2).z;
        sVar5 = (sd->vt1).z;
        (sd->vt4).y = (short)((int)(sd->vt1).y + (int)(sd->vt2).y + 1 >> 1);
        ts14 = (sd->vt2).x;
        ts15 = (sd->vt0).x;
        (sd->vt4).z = (short)((int)sVar5 + (int)sVar4 + 1 >> 1);
        sVar4 = (sd->vt2).y;
        sVar5 = (sd->vt0).y;
        (sd->vt5).x = (short)((int)ts14 + (int)ts15 + 1 >> 1);
        ts14 = (sd->vt2).z;
        ts15 = (sd->vt0).z;
        (sd->vt5).y = (short)((int)sVar4 + (int)sVar5 + 1 >> 1);
        (sd->vt5).z = (short)((int)ts14 + (int)ts15 + 1 >> 1);
        uv_pack_b = (u_short)overlay_entry->uv0.u | (u_short)overlay_entry->uv0.v << 8;
        tu10 = (short)((u_short)overlay_entry->uv1.u | (u_short)overlay_entry->uv1.v << 8);
        tu11 = (short)((u_short)overlay_entry->uv2.u | (u_short)overlay_entry->uv2.v << 8);
        sd->u0 = (char)uv_pack_b;
        sd->v0 = (char)((u_short)uv_pack_b >> 8);
        sd->u1 = (char)tu10;
        sd->v1 = (char)((u_short)tu10 >> 8);
        sd->u2 = (char)tu11;
        sd->v2 = (char)((u_short)tu11 >> 8);
        pDVar19 = pDVar19 + bVar2;
        if ((envmap & 2U) != 0) {
          tu5 = sd->offsetU0;
          tu6 = sd->offsetV0;
          sd->u0 = sd->u0 + tu5;
          sd->v0 = sd->v0 + tu6;
          sd->u1 = sd->u1 + tu5;
          sd->v1 = sd->v1 + tu6;
          sd->u2 = sd->u2 + tu5;
          sd->v2 = sd->v2 + tu6;
        }
        sd->u3 = (u_char)((int)((u_int)sd->u0 + (u_int)sd->u1 + 1) >> 1);
        sd->v3 = (u_char)((int)((u_int)sd->v0 + (u_int)sd->v1 + 1) >> 1);
        sd->u4 = (u_char)((int)((u_int)sd->u1 + (u_int)sd->u2 + 1) >> 1);
        sd->v4 = (u_char)((int)((u_int)sd->v1 + (u_int)sd->v2 + 1) >> 1);
        sd->u5 = (u_char)((int)((u_int)sd->u2 + (u_int)sd->u0 + 1) >> 1);
        sd->v5 = (u_char)((int)((u_int)sd->v2 + (u_int)sd->v0 + 1) >> 1);
        DrawC_DividePrim(&sd->vt0,vt1,vt2,(u_short *)&sd->u0,(u_short *)u1,
                   (u_short *)u2_00,pDVar19,sd);
        DrawC_DividePrim(vt1,&sd->vt1,vt2_00,(u_short *)u1,(u_short *)&sd->u1,
                   (u_short *)u2,pDVar19,sd);
        DrawC_DividePrim(vt2,vt2_00,&sd->vt2,(u_short *)u2_00,(u_short *)u2,
                   (u_short *)&sd->u2,pDVar19,sd);
        DrawC_DividePrim(vt2,vt1,vt2_00,(u_short *)u2_00,(u_short *)u1,
                   (u_short *)u2,pDVar19,sd);
      }
    }
  }
  else {
    if (facetIdx_dec == 8) {
      iVar11 = facetIdx * 0xc;
DrawC_PrimClip_envmap9Eq8Top:
      iVar12 = iVar11;
      uVar9 = facetIdx - 1;
DrawC_PrimClip_envmap9Eq8Inner:
      while( true ) {
        do {
          do {
            do {
              facetIdx = uVar9;
              iVar11 = iVar12 + -0xc;
              if (facetIdx == 0xffffffff) {
                return;
              }
              facet_p_v1 = obj->facet + facetIdx;
              bVar18 = facet_p_v1->vertexId0;
              bVar3 = facet_p_v1->vertexId1;
              vert_c_idx = facet_p_v1->vertexId2;
              iVar12 = iVar11;
              uVar9 = facetIdx - 1;
            } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
            gte_ldVXY0(sd->tV + bVar18);
            gte_ldVZ0(&sd->tV[bVar18].vt.z);
            gte_ldVXY1(sd->tV + bVar3);
            gte_ldVZ1(&sd->tV[bVar3].vt.z);
            gte_ldVXY2(sd->tV + vert_c_idx);
            gte_ldVZ2(&sd->tV[vert_c_idx].vt.z);
            gte_rtpt();
            gte_nclip();
            gte_stMAC0();
            iVar20 = sd->bfct;
            if ((sd->head).mirror != 0) {
              iVar20 = -iVar20;
            }
            uVar9 = facetIdx - 1;
          } while (iVar20 < 1);
          gte_stSXY0();
          gte_stSXY1();
          gte_stSXY2();
          sVar4 = sd->tV[bVar3].vt.z;
          sVar5 = sd->tV[vert_c_idx].vt.z;
          (sd->vt0).z = sd->tV[bVar18].vt.z;
          (sd->vt1).z = sVar4;
          (sd->vt2).z = sVar5;
          sVar4 = (sd->head).clipW;
          sVar5 = (sd->head).clipH;
        } while ((((((sVar4 < sd->dvx0) && (sVar4 < sd->dvx1)) &&
                   (uVar9 = facetIdx - 1, sVar4 < sd->dvx2)) ||
                  (((sd->dvx0 < 0 && (sd->dvx1 < 0)) && (uVar9 = facetIdx - 1, sd->dvx2 < 0)))) ||
                 ((((sVar5 < sd->dvy0 && (sVar5 < sd->dvy1)) &&
                   (uVar9 = facetIdx - 1, sVar5 < sd->dvy2)) ||
                  (((sd->dvy0 < 0 && (sd->dvy1 < 0)) && (uVar9 = facetIdx - 1, sd->dvy2 < 0)))))) ||
                ((((sd->vt0).z < 0 && ((sd->vt1).z < 0)) && (uVar9 = facetIdx - 1, (sd->vt2).z < 0))
                ));
        gte_avsz3();
        gte_stOTZ();
        uVar26 = (int)((u_int)(u_short)DrawC_gOverlay[facet_p_v1->textureIndex] << 0x10) >> 0x10;
        if (uVar26 == 0) break;
        uVar15 = (u_int)(short)facet_p_v1->flag;
        uVar26 = uVar26 & 0xff;
        if ((int)uVar15 < 0) {
          uVar26 = (int)((u_int)(u_short)DrawC_gOverlay[facet_p_v1->textureIndex] << 0x10) >> 0x18;
        }
        iVar20 = sd->otz + sd->sub_otz;
        if ((uVar26 & 0x40) != 0) {
          iVar20 = iVar20 + -2;
        }
        uVar9 = facetIdx - 1;
        if ((-1 < iVar20) && (uVar9 = facetIdx - 1, iVar20 <= sd->sub_otSize)) {
          uVar9 = uVar15 & 0xfff;
          if (((uVar15 & 0x3f0) != 0) && (uVar26 = uVar26 & uVar9 >> 4, uVar26 != 0)) {
            for (; (uVar26 & 3) == 0; uVar26 = (int)uVar26 >> 2) {
            }
          }
          sd->otz = iVar20;
          goto DrawC_PrimClip_otStitch24Emit;
        }
      }
      iVar20 = sd->otz + sd->sub_otz;
      sd->otz = iVar20;
      if (-1 < iVar20) goto cfLbl5;
      goto DrawC_PrimClip_envmap9Eq8Top;
    }
    if (facetIdx_dec == 9) {
      iVar11 = facetIdx * 0xc;
DrawC_PrimClip_envmap9Eq9Top:
      uVar9 = facetIdx - 1;
      iVar12 = iVar11;
DrawC_PrimClip_envmap9Eq9Inner:
      do {
        do {
          do {
            do {
              facetIdx = uVar9;
              iVar11 = iVar12 + -0xc;
              if (facetIdx == 0xffffffff) {
                return;
              }
              puVar23 = obj->facet + facetIdx;
              bVar18 = puVar23->vertexId0;
              bVar3 = puVar23->vertexId1;
              bVar8 = puVar23->vertexId2;
              uVar9 = facetIdx - 1;
              iVar12 = iVar11;
            } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
            gte_ldVXY0(sd->tV + bVar18);
            gte_ldVZ0(&sd->tV[bVar18].vt.z);
            gte_ldVXY1(sd->tV + bVar3);
            gte_ldVZ1(&sd->tV[bVar3].vt.z);
            gte_ldVXY2(sd->tV + bVar8);
            gte_ldVZ2(&sd->tV[bVar8].vt.z);
            gte_rtpt();
            gte_nclip();
            gte_stMAC0();
            bfctResult_a = sd->bfct;
            if ((sd->head).mirror != 0) {
              bfctResult_a = -bfctResult_a;
            }
            uVar9 = facetIdx - 1;
          } while (bfctResult_a < 1);
          gte_stSXY0();
          gte_stSXY1();
          gte_stSXY2();
          sVar4 = sd->tV[bVar3].vt.z;
          sVar5 = sd->tV[bVar8].vt.z;
          (sd->vt0).z = sd->tV[bVar18].vt.z;
          (sd->vt1).z = sVar4;
          (sd->vt2).z = sVar5;
          sVar4 = (sd->head).clipW;
          sVar5 = (sd->head).clipH;
        } while (((((((sVar4 < sd->dvx0) && (sVar4 < sd->dvx1)) &&
                    (uVar9 = facetIdx - 1, sVar4 < sd->dvx2)) ||
                   (((sd->dvx0 < 0 && (sd->dvx1 < 0)) && (uVar9 = facetIdx - 1, sd->dvx2 < 0)))) ||
                  (((sVar5 < sd->dvy0 && (sVar5 < sd->dvy1)) &&
                   (uVar9 = facetIdx - 1, sVar5 < sd->dvy2)))) ||
                 (((sd->dvy0 < 0 && (sd->dvy1 < 0)) && (uVar9 = facetIdx - 1, sd->dvy2 < 0)))) ||
                ((((sd->vt0).z < 0 && ((sd->vt1).z < 0)) && (uVar9 = facetIdx - 1, (sd->vt2).z < 0))
                ));
        gte_avsz3();
        gte_stOTZ();
        ot_offs_byte = (int)((u_int)(u_short)DrawC_gOverlay[puVar23->textureIndex] << 0x10) >> 0x10;
        if (ot_offs_byte == 0) {
          iVar20 = sd->otz + sd->sub_otz;
          sd->otz = iVar20;
          if (iVar20 < 0) goto DrawC_PrimClip_envmap9Eq9Top;
          uVar9 = facetIdx - 1;
          if (sd->sub_otSize < iVar20) goto DrawC_PrimClip_envmap9Eq9Inner;
          tu25 = (u_short)puVar23->flag & 0xfff;
          uVar26 = 0;
        }
        else {
          uVar15 = (u_int)(short)puVar23->flag;
          uVar26 = ot_offs_byte & 0xff;
          if ((int)uVar15 < 0) {
            uVar26 = (int)((u_int)(u_short)DrawC_gOverlay[puVar23->textureIndex] << 0x10) >> 0x18;
          }
          iVar20 = sd->otz + sd->sub_otz;
          uVar9 = facetIdx - 1;
          if ((iVar20 < 0) || (uVar9 = facetIdx - 1, sd->sub_otSize < iVar20))
          goto DrawC_PrimClip_envmap9Eq9Inner;
          tu25 = uVar15 & 0xfff;
          if (((uVar15 & 0x3f0) != 0) && (uVar26 = uVar26 & (u_int)tu25 >> 4, uVar26 != 0)) {
            for (; (uVar26 & 3) == 0; uVar26 = (int)uVar26 >> 2) {
            }
          }
          sd->otz = iVar20;
        }
        if (((envmap & 0x20U) == 0) || (uVar9 = facetIdx - 1, (tu25 & 1U) == 0))
        goto DrawC_PrimClip_ePmx1UVEmit;
      } while( true );
    }
  }
  return;
cfLbl5:   /* @0x800c28a8  (-f-build goto label) */
  uVar9 = facetIdx - 1;
  if (iVar20 <= sd->sub_otSize) goto cfLbl6;
  goto DrawC_PrimClip_envmap9Eq8Inner;
cfLbl6:   /* @0x800c28bc  (-f-build goto label) */
  uVar9 = (u_short)facet_p_v1->flag & 0xfff;
  uVar26 = 0;
DrawC_PrimClip_otStitch24Emit:
  if ((uVar26 & 3) == 0) {
    puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
    *puVar27 = 0x07000000;
    AddPrim(sub_ot_p + iVar12,puVar27);
    uVar15 = *(u_int *)&sd->dvx1;
    uVar14 = *(u_int *)&sd->dvx2;
    uVar25 = 0x808080;
    puVar27[2] = *(u_int *)&sd->dvx0;
    puVar27[4] = uVar15;
    puVar27[6] = uVar14;
    if ((uVar26 & 0x80) == 0) {
      uVar25 = sd->color;
    }
    primTypeByte_b = 0x24;
    if ((uVar9 & 1) != 0) {
      primTypeByte_b = 0x26;
    }
    puVar27[1] = uVar25;
    *(u_char *)((u_char *)puVar27 + 7) = primTypeByte_b;
    uVar6 = sd->pmxStart[facet_p_v1->textureIndex].tpage;
    *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[facet_p_v1->textureIndex].clut;
    *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
    uVar6 = (u_short)facet_p_v1->uv1.u | (u_short)facet_p_v1->uv1.v << 8;
    tu33 = (u_short)facet_p_v1->uv2.u | (u_short)facet_p_v1->uv2.v << 8;
    *(u_short *)(puVar27 + 3) = (u_short)facet_p_v1->uv0.u | (u_short)facet_p_v1->uv0.v << 8;
    *(u_short *)(puVar27 + 5) = uVar6;
    *(u_short *)(puVar27 + 7) = tu33;
  }
  else {
    puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
    pTVar24 = overlay + (u_int)facet_p_v1->textureIndex * 3 + ((uVar26 & 3) - 1);
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
    *puVar27 = 0x07000000;
    AddPrim(sub_ot_p + iVar12,puVar27);
    uVar15 = *(u_int *)&sd->dvx1;
    uVar14 = *(u_int *)&sd->dvx2;
    tu41 = 0x808080;
    puVar27[2] = *(u_int *)&sd->dvx0;
    puVar27[4] = uVar15;
    puVar27[6] = uVar14;
    if ((uVar26 & 0x80) == 0) {
      tu41 = sd->color;
    }
    primTypeByte = 0x24;
    if ((uVar9 & 1) != 0) {
      primTypeByte = 0x26;
    }
    puVar27[1] = tu41;
    *(u_char *)((u_char *)puVar27 + 7) = primTypeByte;
    uVar17 = pTVar24->u;
    uVar21 = pTVar24->v;
    iVar12 = (u_int)facet_p_v1->textureIndex + (int)pTVar24->offset;
    uVar6 = sd->pmxStart[iVar12].tpage;
    *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[iVar12].clut;
    *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
    uVar6 = (u_short)facet_p_v1->uv1.u | (u_short)facet_p_v1->uv1.v << 8;
    tu33 = (u_short)facet_p_v1->uv2.u | (u_short)facet_p_v1->uv2.v << 8;
    *(u_char *)(puVar27 + 3) = (char)facet_p_v1->uv0.u + uVar17;
    *(u_char *)(puVar27 + 5) = (char)uVar6 + uVar17;
    *(u_char *)(puVar27 + 7) = (char)tu33 + uVar17;
    cVar1 = (char)facet_p_v1->uv1.v;
    tc7 = facet_p_v1->uv2.v;
    *(u_char *)((u_char *)puVar27 + 0xd) = (char)facet_p_v1->uv0.v + uVar21;
    *(u_char *)((u_char *)puVar27 + 0x15) = cVar1 + uVar21;
    *(u_char *)((u_char *)puVar27 + 0x1d) = tc7 + uVar21;
  }
  goto DrawC_PrimClip_envmap9Eq8Top;
DrawC_PrimClip_ePmx1UVEmit:
  if (((tu25 & 0x3f3U) != 0) &&
     (((u_char *)&(absZ))[0] = (sd->ePmx1).u0, ((u_char *)&(absZ))[1] = (sd->ePmx1).v0, (*(u_short *)((u_char *)&(absZ) + 2)) = (sd->ePmx1).clut,
     absZ != 0)) {
    sd->vt0 = Nvertex_p[puVar23->vertexId0];
    sd->vt1 = Nvertex_p[puVar23->vertexId1];
    sd->vt2 = Nvertex_p[puVar23->vertexId2];
    primOut_drmOff = (u_int *)(sd->head).cprim.PrimPtr;
    (sd->head).cprim.PrimPtr = (char *)(primOut_drmOff + 3);
    tu45 = (u_int)(intptr)(sd->drawModeOff).tag;
    tu47 = (sd->drawModeOff).code[0];
    tu49 = (sd->drawModeOff).code[1];
    primOut_drmOff[0] = tu45;
    primOut_drmOff[1] = tu47;
    primOut_drmOff[2] = tu49;
    AddPrim(sd->sub_ot + sd->otz,primOut_drmOff);
    facet_p_v4 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(facet_p_v4 + 8);
    facet_p_v4[0] = 0x07000000;
    AddPrim(sub_ot_p + iVar12,facet_p_v4);
    tp43 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(tp43 + 3);
    tu43 = (u_int)(intptr)(sd->drawModeOn).tag;
    drmodeOn_w0 = (sd->drawModeOn).code[0];
    drmodeOn_w1 = (sd->drawModeOn).code[1];
    tp43[0] = tu43;
    tp43[1] = drmodeOn_w0;
    tp43[2] = drmodeOn_w1;
    AddPrim(sub_ot_p + iVar12,tp43);
    tu40 = *(u_int *)&sd->dvx1;
    uVar16 = *(u_int *)&sd->dvx2;
    facet_p_v4[2] = *(u_int *)&sd->dvx0;
    facet_p_v4[4] = tu40;
    facet_p_v4[6] = uVar16;
    facet_p_v4[1] = sd->eColor0;
    *(u_char *)((u_char *)facet_p_v4 + 7) = 0x26;
    tu16 = (sd->ePmx1).tpage;
    *(u_short *)((u_char *)facet_p_v4 + 0xe) = (sd->ePmx1).clut;
    *(short *)((u_char *)facet_p_v4 + 0x16) = tu16;
    tc45 = (sd->ePmx1).u0 + 0x40;
    vert_v_byte = (sd->ePmx1).v0 + (char)sd->eAddZ;
    sVar4 = (sd->vt0).z;
    *(u_char *)((u_char *)facet_p_v4 + 0xc) = (char)(sd->vt0).y + tc45;
    *(char *)((u_char *)facet_p_v4 + 0xd) = (char)sVar4 + vert_v_byte;
    sVar4 = (sd->vt1).z;
    *(u_char *)((u_char *)facet_p_v4 + 0x14) = (char)(sd->vt1).y + tc45;
    *(char *)((u_char *)facet_p_v4 + 0x15) = (char)sVar4 + vert_v_byte;
    sVar4 = (sd->vt2).z;
    *(u_char *)((u_char *)facet_p_v4 + 0x1c) = (char)(sd->vt2).y + tc45;
    *(char *)((u_char *)facet_p_v4 + 0x1d) = (char)sVar4 + vert_v_byte;
  }
  ((u_char *)&(ti16))[0] = (sd->ePmx0).u0;
  ((u_char *)&(ti16))[1] = (sd->ePmx0).v0;
  (*(u_short *)((u_char *)&(ti16) + 2)) = (sd->ePmx0).clut;
  if (ti16 != 0) {
    primOut = (u_int *)(sd->head).cprim.PrimPtr;
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(primOut + 8);
    *primOut = 0x07000000;
    AddPrim(sub_ot_p + iVar12,primOut);
    uVar9 = *(u_int *)&sd->dvx1;
    uVar15 = *(u_int *)&sd->dvx2;
    primOut[2] = *(u_int *)&sd->dvx0;
    primOut[4] = uVar9;
    primOut[6] = uVar15;
    if ((uVar26 & 1) == 0) {
      if ((tu25 & 4U) == 0) {
        primOut[1] = sd->eColor0;
      }
      else {
        primOut[1] = sd->eColor1;
      }
    }
    else {
      primOut[1] = sd->eColor2;
    }
    *(u_char *)((u_char *)primOut + 7) = 0x26;
    tpage_alt = (sd->ePmx0).tpage;
    *(u_short *)((u_char *)primOut + 0xe) = (sd->ePmx0).clut;
    *(u_short *)((u_char *)primOut + 0x16) = tpage_alt;
    ePmx0_vOff = (sd->ePmx0).v0;
    tc57 = (sd->ePmx0).u0 + '@';
    cVar1 = sd->tV[bVar18].v;
    *(char *)(primOut + 3) = sd->tV[bVar18].u + tc57;
    *(u_char *)((u_char *)primOut + 0xd) = cVar1 + ePmx0_vOff;
    cVar1 = sd->tV[bVar3].v;
    *(char *)(primOut + 5) = sd->tV[bVar3].u + tc57;
    *(u_char *)((u_char *)primOut + 0x15) = cVar1 + ePmx0_vOff;
    cVar1 = sd->tV[bVar8].v;
    *(char *)(primOut + 7) = sd->tV[bVar8].u + tc57;
    *(u_char *)((u_char *)primOut + 0x1d) = cVar1 + ePmx0_vOff;
  }
  if ((uVar26 & 3) == 0) {
    puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
    *puVar27 = 0x07000000;
    AddPrim(sub_ot_p + iVar12,puVar27);
    uVar9 = *(u_int *)&sd->dvx1;
    uVar26 = *(u_int *)&sd->dvx2;
    puVar27[2] = *(u_int *)&sd->dvx0;
    puVar27[4] = uVar9;
    puVar27[6] = uVar26;
    uVar10 = 0x24;
    if ((tu25 & 1U) != 0) {
      uVar10 = 0x26;
    }
    puVar27[1] = sd->color;
    *(u_char *)((u_char *)puVar27 + 7) = uVar10;
    uVar6 = sd->pmxStart[puVar23->textureIndex].tpage;
    *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[puVar23->textureIndex].clut;
    *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
    uVar6 = (u_short)puVar23->uv1.u | (u_short)puVar23->uv1.v << 8;
    tu33 = (u_short)puVar23->uv2.u | (u_short)puVar23->uv2.v << 8;
    *(u_short *)(puVar27 + 3) = (u_short)puVar23->uv0.u | (u_short)puVar23->uv0.v << 8;
    *(u_short *)(puVar27 + 5) = uVar6;
    *(u_short *)(puVar27 + 7) = tu33;
  }
  else {
    puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
    pTVar24 = overlay + (u_int)puVar23->textureIndex * 3 + ((uVar26 & 3) - 1);
    iVar12 = sd->otz;
    sub_ot_p = sd->sub_ot;
    (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
    *puVar27 = 0x07000000;
    AddPrim(sub_ot_p + iVar12,puVar27);
    uVar9 = *(u_int *)&sd->dvx1;
    uVar26 = *(u_int *)&sd->dvx2;
    puVar27[2] = *(u_int *)&sd->dvx0;
    puVar27[4] = uVar9;
    puVar27[6] = uVar26;
    bVar18 = 0x24;
    if ((tu25 & 1U) != 0) {
      bVar18 = 0x26;
    }
    puVar27[1] = sd->color;
    *(u_char *)((u_char *)puVar27 + 7) = bVar18;
    if ((tu25 & 1U) != 0) {
      *(u_char *)((u_char *)puVar27 + 7) = bVar18 | 2;
    }
    uVar17 = pTVar24->u;
    uVar21 = pTVar24->v;
    iVar12 = (u_int)puVar23->textureIndex + (int)pTVar24->offset;
    uVar6 = sd->pmxStart[iVar12].tpage;
    *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[iVar12].clut;
    *(u_short *)((u_char *)puVar27 + 0x16) = uVar6;
    uVar6 = (u_short)puVar23->uv1.u | (u_short)puVar23->uv1.v << 8;
    tu19 = (u_short)puVar23->uv2.u | (u_short)puVar23->uv2.v << 8;
    *(u_char *)(puVar27 + 3) = (char)puVar23->uv0.u + uVar17;
    *(u_char *)(puVar27 + 5) = (char)uVar6 + uVar17;
    *(u_char *)(puVar27 + 7) = (char)tu19 + uVar17;
    cVar1 = (char)puVar23->uv1.v;
    tc57 = (char)puVar23->uv2.v;
    *(u_char *)((u_char *)puVar27 + 0xd) = (char)puVar23->uv0.v + uVar21;
    *(u_char *)((u_char *)puVar27 + 0x15) = cVar1 + uVar21;
    *(u_char *)((u_char *)puVar27 + 0x1d) = tc57 + uVar21;
  }
  goto DrawC_PrimClip_envmap9Eq9Top;
}

/* ---- DrawC_PrimMenu__FP10matrixtdefP8coorddefP16Transformer_zObjP20Transformer_zOverlayiP13Draw_CarCache  [DRAWC.CPP:3551-3869] SLD-VERIFIED ---- */
void DrawC_PrimMenu(matrixtdef *m,coorddef *t,Transformer_zObj *obj,Transformer_zOverlay *overlay,
               int envmap,Draw_CarCache *sd)

{
  COORD16 * Nvertice;
  COORD16 * vt;
  short t1;
  short t2;
  short t3;
  int r0;
  int r1;
  int r2;
  PCOORD16 * tV;
  POLY_FT3 * prim;
  int overlayFlag;
  int id2;
  int bfct;
  long xy0;
  long xy1;
  long xy2;
  u_long color;
  u_char code;
  int index;
  int which;
  Transformer_zOverlay * facetOverlay;
  Draw_tPixMap * pmx;
  u_char u0;
  u_char u1;
  u_char u2;
  u_char v0;
  u_char v1;
  u_char v2;
  u_short uv0;
  u_short uv1;
  u_char bVar1;
  u_char bVar2;
  u_char bVar3;
  u_char uVar4;
  char cVar5;
  u_char uVar6;
  short sVar7;
  u_short uVar8;
  u_int uVar9;
  u_int *puVar10;
  short *psVar11;
  u_short clut;
  short sVar12;
  u_short uVar13;
  int iVar14;
  u_short tpage;
  u_short uv2;
  COORD16 *pCVar15;
  u_char u;
  int iVar16;
  u_char uVar17;
  u_char v;
  short *psVar18;
  int iVar19;
  u_int uVar20;
  char *pcVar21;
  short *psVar22;
  Transformer_zOverlay *pTVar23;
  Transformer_zFacet *facet;
  Draw_CarVertex *pDVar24;
  Transformer_zFacet *puVar25;
  int id1;
  int id0;
  u_int uVar26;
  short facetFlag;
  u_int *puVar27;
  u_int *puVar28;
  u_long *puVar29;
  char cVar30;
  u_long *puVar31;
  u_int uVar32;
  int i;
  u_int uVar33;
  
  pCVar15 = obj->Nvertex;
  if ((envmap & 1U) != 0) {
gte_SetRotMatrix(&DrawC_gMatA);
gte_SetTransMatrix(&DrawC_gMatA);
    uVar33 = (u_int)obj->numVertex;
    uVar26 = 0xffffffff;
    pcVar21 = &sd->tV[0].v;
    psVar18 = &pCVar15->z;
    while (uVar33 = uVar33 - 1, uVar33 != uVar26) {
      sVar12 = psVar18[-1];
      sVar7 = *psVar18;
      (sd->vt0).x = pCVar15->x;
      (sd->vt0).y = sVar12;
      (sd->vt0).z = sVar7;
gte_lwc2(0,*(int *)(((char *)sd + 0xac)));
      gte_lwc2(1,*(int *)(((char *)sd + 0xb0)));
      gte_rt();
gte_swc2(0x19,((char *)sd + 0x9c));
      gte_swc2(0x1a,((char *)sd + 0xa0));
      gte_swc2(0x1b,((char *)sd + 0xa4));
      iVar14 = (sd->tv).vz;
      if (iVar14 < 0) {
        iVar14 = -iVar14;
      }
      psVar18 = psVar18 + 3;
      pCVar15 = pCVar15 + 1;
      pcVar21[-1] = (char)(sd->tv).vx;
      *pcVar21 = (char)iVar14;
      pcVar21 = pcVar21 + 8;
    }
  }
  TrsProj_SetTransPrecision(8);
  iVar14 = m->m[3];
  iVar16 = m->m[6];
  (sd->matB).m[0][0] = (short)(m->m[0] >> 4);
  (sd->matB).m[0][1] = (short)(iVar14 >> 4);
  (sd->matB).m[0][2] = (short)(iVar16 >> 4);
  iVar14 = m->m[4];
  iVar16 = m->m[7];
  sVar12 = (short)(m->m[1] >> 4);
  (sd->matB).m[1][0] = sVar12;
  (sd->matB).m[1][1] = (short)(iVar14 >> 4);
  (sd->matB).m[1][2] = (short)(iVar16 >> 4);
  iVar14 = m->m[2];
  iVar16 = m->m[5];
  iVar19 = m->m[8];
  (sd->matB).m[1][0] = -sVar12;
  sVar12 = (sd->matB).m[1][1];
  (sd->matB).m[2][0] = (short)(iVar14 >> 4);
  sVar7 = (sd->matB).m[1][2];
  (sd->matB).m[2][1] = (short)(iVar16 >> 4);
  (sd->matB).m[2][2] = (short)(iVar19 >> 4);
  (sd->matB).m[1][1] = -sVar12;
  (sd->matB).m[1][2] = -sVar7;
  iVar14 = TrsProj_precision;
  (sd->matB).t[0] = t->x >> (TrsProj_precision & 0x1fU);
  (sd->matB).t[1] = -(t->y >> (iVar14 & 0x1fU));
  (sd->matB).t[2] = t->z >> (iVar14 & 0x1fU);
  TrsProj_ResetTransPrecision();
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
  pDVar24 = sd->tV;
  psVar22 = &sd->tV[0].vt.z;
  pCVar15 = obj->vertex;
  uVar26 = (u_int)obj->numVertex;
  psVar18 = &pCVar15->z;
  while (uVar26 = uVar26 - 1, uVar26 != 0xffffffff) {
    sVar12 = psVar18[-1];
    sVar7 = *psVar18;
    psVar18 = psVar18 + 3;
    psVar11 = &pCVar15->x;
    pCVar15 = pCVar15 + 1;
    (pDVar24->vt).x = *psVar11;
    psVar22[-1] = sVar12;
    *psVar22 = sVar7;
    psVar22 = psVar22 + 4;
    pDVar24 = pDVar24 + 1;
  }
  uVar26 = (u_int)obj->numFacet;
  iVar14 = uVar26 * 0xc;
DrawCPrimMenu_facetLoopTop:
  do {
    uVar33 = uVar26 - 1;
    iVar16 = iVar14;
    do {
      do {
        do {
          uVar26 = uVar33;
          iVar14 = iVar16 + -0xc;
          if (uVar26 == 0xffffffff) {
            return;
          }
          puVar25 = obj->facet + uVar26;
          bVar1 = puVar25->vertexId0;
          bVar2 = puVar25->vertexId1;
          bVar3 = puVar25->vertexId2;
          uVar33 = uVar26 - 1;
          iVar16 = iVar14;
        } while ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr);
        gte_ldVXY0(sd->tV + bVar1);
        gte_ldVZ0(&sd->tV[bVar1].vt.z);
        gte_ldVXY1(sd->tV + bVar2);
        gte_ldVZ1(&sd->tV[bVar2].vt.z);
        gte_ldVXY2(sd->tV + bVar3);
        gte_ldVZ2(&sd->tV[bVar3].vt.z);
        gte_rtpt();
        gte_nclip();
        gte_stMAC0();
        iVar19 = sd->bfct;
        if ((sd->head).mirror != 0) {
          iVar19 = -iVar19;
        }
        uVar33 = uVar26 - 1;
      } while (iVar19 < 1);
      gte_stSXY0();
      gte_stSXY1();
      gte_stSXY2();
      gte_avsz3();
      gte_stOTZ();
      iVar19 = sd->otz + sd->sub_otz;
      sd->otz = iVar19;
      if (iVar19 < 0) goto DrawCPrimMenu_facetLoopTop;
      uVar33 = uVar26 - 1;
    } while (sd->sub_otSize < iVar19);
    uVar13 = (u_short)puVar25->flag;
    uVar20 = (int)((u_int)(u_short)DrawC_gOverlay[puVar25->textureIndex] << 0x10) >> 0x10;
    uVar33 = 0;
    if (uVar20 != 0) {
      uVar33 = uVar20 & 0x3f;
      if ((int)((u_int)uVar13 << 0x10) < 0) {
        uVar33 = (int)((u_int)(u_short)DrawC_gOverlay[puVar25->textureIndex] << 0x10) >> 0x18;
      }
      if (((uVar13 & 0x3f0) != 0) && (uVar33 = uVar33 & (uVar13 & 0xfff) >> 4, uVar33 != 0)) {
        for (; (uVar33 & 3) == 0; uVar33 = (int)uVar33 >> 2) {
        }
      }
    }
    if ((envmap & 1U) != 0) {
      puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
      iVar16 = sd->otz;
      puVar31 = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar27 + 3);
      puVar29 = (u_long *)(intptr)(sd->drawModeOff).tag;
      uVar20 = (sd->drawModeOff).code[0];
      uVar32 = (sd->drawModeOff).code[1];
    *puVar27 = (u_int)(intptr)puVar29;
      puVar27[1] = uVar20;
      puVar27[2] = uVar32;
      AddPrim(puVar31 + iVar16,puVar27);
      puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
      iVar16 = sd->otz;
      puVar31 = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
      *puVar27 = 0x07000000;
      AddPrim(puVar31 + iVar16,puVar27);
      puVar28 = (u_int *)(sd->head).cprim.PrimPtr;
      iVar16 = sd->otz;
      puVar31 = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar28 + 3);
      puVar29 = (u_long *)(intptr)(sd->drawModeOn).tag;
      uVar20 = (sd->drawModeOn).code[0];
      uVar32 = (sd->drawModeOn).code[1];
    *puVar28 = (u_int)(intptr)puVar29;
      puVar28[1] = uVar20;
      puVar28[2] = uVar32;
      AddPrim(puVar31 + iVar16,puVar28);
      uVar20 = *(u_int *)&sd->dvx1;
      uVar32 = *(u_int *)&sd->dvx2;
      puVar27[2] = *(u_int *)&sd->dvx0;
      puVar27[4] = uVar20;
      puVar27[6] = uVar32;
      if ((uVar13 & 4) == 0) {
        puVar27[1] = sd->eColor0;
      }
      else {
        puVar27[1] = sd->eColor1;
      }
      *(u_char *)((u_char *)puVar27 + 7) = 0x26;
      uVar8 = (sd->ePmx0).tpage;
      *(u_short *)((u_char *)puVar27 + 0xe) = (sd->ePmx0).clut;
      *(u_short *)((u_char *)puVar27 + 0x16) = uVar8;
      uVar4 = (sd->ePmx0).v0;
      cVar30 = (sd->ePmx0).u0 + '@';
      cVar5 = sd->tV[bVar1].v;
      *(char *)(puVar27 + 3) = sd->tV[bVar1].u + cVar30;
      *(u_char *)((u_char *)puVar27 + 0xd) = cVar5 + uVar4;
      cVar5 = sd->tV[bVar2].v;
      *(char *)(puVar27 + 5) = sd->tV[bVar2].u + cVar30;
      *(u_char *)((u_char *)puVar27 + 0x15) = cVar5 + uVar4;
      cVar5 = sd->tV[bVar3].v;
      *(char *)(puVar27 + 7) = sd->tV[bVar3].u + cVar30;
      *(u_char *)((u_char *)puVar27 + 0x1d) = cVar5 + uVar4;
    }
    if ((uVar33 & 3) == 0) {
      puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
      iVar16 = sd->otz;
      puVar31 = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
      *puVar27 = 0x07000000;
      AddPrim(puVar31 + iVar16,puVar27);
      uVar33 = *(u_int *)&sd->dvx0;
      uVar20 = *(u_int *)&sd->dvx2;
      puVar27[4] = *(u_int *)&sd->dvx1;
      puVar27[2] = uVar33;
      puVar27[6] = uVar20;
      uVar17 = 0x24;
      if ((uVar13 & 1) != 0) {
        uVar17 = 0x26;
      }
      puVar27[1] = sd->color;
      *(u_char *)((u_char *)puVar27 + 7) = uVar17;
      if (((envmap & 2U) == 0) || ((uVar13 & 1) != 0)) {
        uVar13 = sd->pmxStart[puVar25->textureIndex].tpage;
        *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[puVar25->textureIndex].clut;
        *(u_short *)((u_char *)puVar27 + 0x16) = uVar13;
        uVar13 = (u_short)puVar25->uv1.u | (u_short)puVar25->uv1.v << 8;
        uVar8 = (u_short)puVar25->uv2.u | (u_short)puVar25->uv2.v << 8;
        *(u_short *)(puVar27 + 3) = (u_short)puVar25->uv0.u | (u_short)puVar25->uv0.v << 8;
        *(u_short *)(puVar27 + 5) = uVar13;
        *(u_short *)(puVar27 + 7) = uVar8;
        goto DrawCPrimMenu_facetLoopTop;
      }
      uVar4 = sd->offsetU0;
      uVar6 = sd->offsetV0;
      uVar13 = sd->pmxStart[puVar25->textureIndex].tpage;
      *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[puVar25->textureIndex].clut;
    }
    else {
      puVar27 = (u_int *)(sd->head).cprim.PrimPtr;
      pTVar23 = overlay + (u_int)puVar25->textureIndex * 3 + ((uVar33 & 3) - 1);
      iVar16 = sd->otz;
      puVar31 = sd->sub_ot;
      (sd->head).cprim.PrimPtr = (char *)(puVar27 + 8);
      *puVar27 = 0x07000000;
      AddPrim(puVar31 + iVar16,puVar27);
      uVar33 = *(u_int *)&sd->dvx1;
      uVar20 = *(u_int *)&sd->dvx2;
      puVar27[2] = *(u_int *)&sd->dvx0;
      puVar27[4] = uVar33;
      puVar27[6] = uVar20;
      uVar17 = 0x24;
      if ((uVar13 & 1) != 0) {
        uVar17 = 0x26;
      }
      puVar27[1] = sd->color;
      *(u_char *)((u_char *)puVar27 + 7) = uVar17;
      uVar4 = pTVar23->u;
      uVar6 = pTVar23->v;
      iVar16 = (u_int)puVar25->textureIndex + (int)pTVar23->offset;
      uVar13 = sd->pmxStart[iVar16].tpage;
      *(u_short *)((u_char *)puVar27 + 0xe) = sd->pmxStart[iVar16].clut;
    }
    *(u_short *)((u_char *)puVar27 + 0x16) = uVar13;
    uVar13 = (u_short)puVar25->uv1.u | (u_short)puVar25->uv1.v << 8;
    uVar8 = (u_short)puVar25->uv2.u | (u_short)puVar25->uv2.v << 8;
    *(u_char *)(puVar27 + 3) = (char)puVar25->uv0.u + uVar4;
    *(u_char *)(puVar27 + 5) = (char)uVar13 + uVar4;
    *(u_char *)(puVar27 + 7) = (char)uVar8 + uVar4;
    cVar5 = (char)puVar25->uv1.v;
    cVar30 = (char)puVar25->uv2.v;
    *(u_char *)((u_char *)puVar27 + 0xd) = (char)puVar25->uv0.v + uVar6;
    *(u_char *)((u_char *)puVar27 + 0x15) = cVar5 + uVar6;
    *(u_char *)((u_char *)puVar27 + 0x1d) = cVar30 + uVar6;
  } while( true );
}

/* ---- DrawC_PrimHalo__FP10matrixtdefP8coorddefP16Transformer_zObjiiiP13Draw_CarCache  [DRAWC.CPP:3881-3990] SLD-VERIFIED ---- */
void DrawC_PrimHalo(matrixtdef *m,coorddef *t,Transformer_zObj *obj,int type,int index,int reflect,
               Draw_CarCache *sd)

{
  int r0;
  int r1;
  int r2;
  Transformer_zFacet * facet;
  u_short id0;
  short * z;
  short t1;
  int bfct;
  short sVar1;
  short t3;
  short sVar2;
  short *psVar3;
  int overlayFlag;
  short t2;
  int iVar4;
  u_int uVar5;
  u_short id1;
  int iVar6;
  u_int uVar8;
  u_short id2;
  u_int uVar9;
  int real_type;
  u_long *copyLastPrim;
  u_long *puVar11;
  int i;
  u_int uVar12;
  COORD16 *vertice;
  int iVar7;
  
  TrsProj_SetTransPrecision(8);
  iVar4 = m->m[3];
  iVar6 = m->m[6];
  (sd->matB).m[0][0] = (short)(m->m[0] >> 4);
  (sd->matB).m[0][1] = (short)(iVar4 >> 4);
  (sd->matB).m[0][2] = (short)(iVar6 >> 4);
  iVar4 = m->m[4];
  iVar6 = m->m[7];
  sVar2 = (short)(m->m[1] >> 4);
  (sd->matB).m[1][0] = sVar2;
  (sd->matB).m[1][1] = (short)(iVar4 >> 4);
  (sd->matB).m[1][2] = (short)(iVar6 >> 4);
  iVar4 = m->m[2];
  iVar6 = m->m[5];
  iVar7 = m->m[8];
  (sd->matB).m[1][0] = -sVar2;
  sVar2 = (sd->matB).m[1][1];
  (sd->matB).m[2][0] = (short)(iVar4 >> 4);
  sVar1 = (sd->matB).m[1][2];
  (sd->matB).m[2][1] = (short)(iVar6 >> 4);
  (sd->matB).m[2][2] = (short)(iVar7 >> 4);
  (sd->matB).m[1][1] = -sVar2;
  (sd->matB).m[1][2] = -sVar1;
  iVar4 = TrsProj_precision;
  (sd->matB).t[0] = t->x >> (TrsProj_precision & 0x1fU);
  (sd->matB).t[1] = -(t->y >> (iVar4 & 0x1fU));
  (sd->matB).t[2] = t->z >> (iVar4 & 0x1fU);
  TrsProj_ResetTransPrecision();
  uVar12 = (u_int)obj->numFacet;
DrawCHalo_facetLoopTop:
  do {
    uVar8 = uVar12 - 1;
    do {
      do {
        do {
          uVar12 = uVar8;
          if (uVar12 == 0xffffffff) {
            return;
          }
          facet = obj->facet + uVar12;
          uVar8 = (u_int)facet->vertexId1;
          uVar9 = (u_int)facet->vertexId2;
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
          psVar3 = (short *)(obj->vertex + facet->vertexId0);
          sVar2 = *psVar3;
          sVar1 = psVar3[1];
          (sd->vt0).z = psVar3[2];
          psVar3 = (short *)(obj->vertex + uVar8);
          (sd->vt0).x = sVar2;
          (sd->vt0).y = sVar1;
          sVar2 = *psVar3;
          sVar1 = psVar3[1];
          (sd->vt1).z = psVar3[2];
          psVar3 = (short *)(obj->vertex + uVar9);
          (sd->vt1).x = sVar2;
          (sd->vt1).y = sVar1;
          sVar2 = *psVar3;
          sVar1 = psVar3[2];
          (sd->vt2).y = psVar3[1];
          (sd->vt2).x = sVar2;
          (sd->vt2).z = sVar1;
gte_lwc2(0,*(int *)(((char *)sd + 0xac)));
          gte_lwc2(1,*(int *)(((char *)sd + 0xb0)));
          gte_lwc2(2,*(int *)(((char *)sd + 0xb4)));
          gte_lwc2(3,*(int *)(((char *)sd + 0xb8)));
          gte_lwc2(4,*(int *)(((char *)sd + 0xbc)));
          gte_lwc2(5,*(int *)(((char *)sd + 0xc0)));
          gte_rtpt();
          gte_nclip();
          gte_stMAC0();
          iVar6 = sd->bfct;
          if ((sd->head).mirror != 0) {
            iVar6 = -iVar6;
          }
          uVar8 = uVar12 - 1;
        } while (iVar6 < 1);
        gte_avsz3();
        gte_stOTZ();
        iVar6 = sd->otz + sd->sub_otz;
        sd->otz = iVar6;
        if (iVar6 < 0) goto DrawCHalo_facetLoopTop;
        uVar8 = uVar12 - 1;
      } while (sd->sub_otSize < iVar6);
      uVar9 = ((u_int)type) & 0xffbf;
      if (index < 0) goto DrawCHalo_emitFlare;
      if (facet->flag < 0) {
        uVar5 = (int)((u_int)(u_short)DrawC_gOverlay[index] << 0x10) >> 0x18;
      }
      else {
        uVar5 = (int)((u_int)(u_short)DrawC_gOverlay[index] << 0x10) >> 0x10 & 0xff;
      }
      if (((((u_int)type) & 0x40) != 0) && ((uVar5 & 0x40) == 0)) {
        if (facet->flag < 0) {
          uVar5 = (int)((u_int)(u_short)DrawC_gOverlay[0x18] << 0x10) >> 0x18;
        }
        else {
          uVar5 = (int)((u_int)(u_short)DrawC_gOverlay[0x18] << 0x10) >> 0x10 & 0xff;
        }
      }
      uVar8 = uVar12 - 1;
    } while ((uVar5 & 0x81) == 0);
    uVar8 = ((u_int)type) & 0xbf;
    if (((uVar5 & 3) != 1) && ((((u_int)type) & 0x7f00) != 0)) {
      uVar9 = (int)uVar9 >> 8;
DrawCHalo_emitFlare:
      uVar8 = uVar9 & 0xff;
    }
    puVar11 = (sd->head).cprim.LastPrim;
    (sd->head).cprim.LastPrim = sd->sub_ot;
    Flare_CarShapedHalo(uVar8,&sd->vt0,&sd->vt1,&sd->vt2,facet->flag,sd->otz,(Draw_FlareCache *)sd);
    if (((0 < reflect) || ((reflect == -1 && (uVar8 == 5)))) || ((reflect == -2 && (uVar8 != 5)))) {
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
      Flare_CarShapedHalo(uVar9 & 0xff | 0x100,&sd->vt0,&sd->vt1,&sd->vt2,facet->flag,sd->otz,
                 (Draw_FlareCache *)sd);
    }
    (sd->head).cprim.LastPrim = puVar11;
  } while( true );
}

/* ---- DrawC_ShadowPrim__FP12Draw_tVertexP13Draw_CarCache  [DRAWC.CPP:3997-4051] SLD-VERIFIED ---- */
void DrawC_ShadowPrim(Draw_tVertex *shadowVT,Draw_CarCache *sd)

{
  POLY_FT4 * prim;
  u_long * ot;
  u_long l0;
  u_long l1;
  int iVar1;
  u_int uVar2;
  u_long l2;
  u_long *puVar3;
  u_int *puVar4;
  u_int uVar5;
  u_long l3;
  u_int uVar6;
  void *prim_pre_rtpt;
  u_int *puVar7;
  Draw_tPixMap *shadowPmx;
  Draw_tPixMap *pDVar8;
  
  pDVar8 = gShadowPixmap[0];
  if (R3DCar_InMenu != 0) {
    pDVar8 = gMenuPixmap[1];
  }
  l2 = (u_long)&pDVar8->tpage;
  ChangeTPage((u_short *)l2,2);
gte_SetRotMatrix(&DrawC_gScreenMat);
gte_SetTransMatrix(&DrawC_gScreenMat);
  if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
gte_lwc2(0,*(int *)(shadowVT));
    gte_lwc2(1,*(int *)(((char *)shadowVT + 0x4)));
    gte_rtps();
    prim_pre_rtpt = Render_gPacketPtr;
    /* MIPS 0x800C3F9C..0x800C3FAC loads Render_gPacketPtr from
       scratchpad+4, adds 8, then stores SXY2 at that packet address. */
gte_swc2(0xe,(char *)prim_pre_rtpt + 8);
gte_lwc2(0,*(int *)(((char *)shadowVT + 0x8)));
    gte_lwc2(1,*(int *)(((char *)shadowVT + 0xc)));
    gte_lwc2(2,*(int *)(((char *)shadowVT + 0x18)));
    gte_lwc2(3,*(int *)(((char *)shadowVT + 0x1c)));
    gte_lwc2(4,*(int *)(((char *)shadowVT + 0x10)));
    gte_lwc2(5,*(int *)(((char *)shadowVT + 0x14)));
    gte_rtpt();
    /* 0x800C3FE0..0x800C3FF4 keeps $a3 = the packet pointer loaded
       at 0x800C3FA0, not the address of the scratchpad itself. */
    gte_swc2(0xc,(char *)prim_pre_rtpt + 0x10);
    gte_swc2(0xd,(char *)prim_pre_rtpt + 0x20);
    gte_swc2(0xe,(char *)prim_pre_rtpt + 0x18);
    gte_avsz4();
    gte_stOTZ();
    iVar1 = (sd->otz >> 1) + 0x28;
    sd->otz = iVar1;
    if ((-1 < iVar1) && (iVar1 <= Draw_gViewOtSize + -3)) {
      puVar7 = (u_int *)(sd->head).cprim.PrimPtr;
      puVar3 = (sd->head).cprim.LastPrim;
      (sd->head).cprim.PrimPtr = (char *)(puVar7 + 10);
      puVar4 = (u_int *)(puVar3 + iVar1);
      *puVar7 = *puVar7 & 0xff000000 | *puVar4 & 0xffffff;
      *puVar4 = *puVar4 & 0xff000000 | (u_int)puVar7 & 0xffffff;
      uVar2 = sd->color;
      ((u_char *)puVar7)[3] = 9;
      puVar7[1] = uVar2;
      ((u_char *)puVar7)[7] = 0x2e;
      uVar2 = *(u_int *)&pDVar8->u1;
      uVar5 = *(u_int *)&pDVar8->u2;
      uVar6 = *(u_int *)&pDVar8->u3;
      puVar7[3] = *(u_int *)pDVar8;
      puVar7[5] = uVar2;
      puVar7[7] = uVar5;
      puVar7[9] = uVar6;
    }
  }
  return;
}

/* ---- DrawC_DivideShadowPrim__FP7COORD16N30PUsN34P12Draw_tPixMapP13Draw_CarCache  [DRAWC.CPP:4056-4114] SLD-VERIFIED ---- */
void DrawC_DivideShadowPrim(COORD16 *vt0,COORD16 *vt1,COORD16 *vt2,COORD16 *vt3,u_short *u0,u_short *u1,u_short *u2
               ,u_short *u3,Draw_tPixMap *pmx,Draw_CarCache *sd)

{
  POLY_FT4 * prim;
  u_long * ot;
  u_short uv2;
  u_short uv3;
  u_short uVar1;
  u_short uVar2;
  u_short uVar3;
  u_short clut;
  u_short tpage;
  int iVar4;
  u_int uVar5;
  u_short uv1;
  u_short uv0;
  u_long *puVar6;
  u_int *puVar7;
  void *tp8;
  u_int *puVar8;
  
  if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
gte_lwc2(0,*(int *)(vt0));
    gte_lwc2(1,*(int *)(((char *)vt0 + 0x4)));
    gte_rtps();
    tp8 = Render_gPacketPtr;
    /* MIPS 0x800C4110..0x800C4120 loads Render_gPacketPtr from
       scratchpad+4, adds 8, then stores SXY2 at that packet address. */
gte_swc2(0xe,(char *)tp8 + 8);
gte_lwc2(0,*(int *)(vt1));
    gte_lwc2(1,*(int *)(((char *)vt1 + 0x4)));
    gte_lwc2(2,*(int *)(vt2));
    gte_lwc2(3,*(int *)(((char *)vt2 + 0x4)));
    gte_lwc2(4,*(int *)(vt3));
    gte_lwc2(5,*(int *)(((char *)vt3 + 0x4)));
    gte_rtpt();
    /* 0x800C4148..0x800C415C uses $t0 loaded from scratchpad+4:
       these are FT4 packet fields, not scratchpad offsets. */
    gte_swc2(0xc,(char *)tp8 + 0x10);
    gte_swc2(0xd,(char *)tp8 + 0x20);
    gte_swc2(0xe,(char *)tp8 + 0x18);
    if (R3DCar_InMenu == 0) {
      gte_avsz4();
      gte_stOTZ();
      iVar4 = (sd->otz >> 3) + 0x28;
      sd->otz = iVar4;
      if (iVar4 < 0) {
        return;
      }
      if (Draw_gViewOtSize + -3 < iVar4) {
        return;
      }
    }
    else {
      sd->otz = 0;
    }
    if ((((-1 < vt0->z) || (-1 < vt1->z)) || (-1 < vt2->z)) || (-1 < vt3->z)) {
      puVar8 = (u_int *)(sd->head).cprim.PrimPtr;
      puVar6 = (sd->head).cprim.LastPrim;
      (sd->head).cprim.PrimPtr = (char *)(puVar8 + 10);
      puVar7 = (u_int *)(puVar6 + sd->otz);
      *puVar8 = *puVar8 & 0xff000000 | *puVar7 & 0xffffff;
      *puVar7 = *puVar7 & 0xff000000 | (u_int)puVar8 & 0xffffff;
      uVar5 = sd->color;
      ((u_char *)puVar8)[3] = 9;
      puVar8[1] = uVar5;
      ((u_char *)puVar8)[7] = 0x2e;
      uVar1 = pmx->tpage;
      *(u_short *)((u_char *)puVar8 + 0xe) = pmx->clut;
      *(u_short *)((u_char *)puVar8 + 0x16) = uVar1;
      uVar1 = *u1;
      uVar2 = *u3;
      uVar3 = *u2;
      *(u_short *)(puVar8 + 3) = *u0;
      *(u_short *)(puVar8 + 5) = uVar1;
      *(u_short *)(puVar8 + 7) = uVar2;
      *(u_short *)(puVar8 + 9) = uVar3;
    }
  }
  return;
}

/* ---- DrawC_ShadowPrimClip__FP12Draw_tVertexP13Draw_CarCache  [DRAWC.CPP:4117-4184] SLD-VERIFIED ---- */
void DrawC_ShadowPrimClip(Draw_tVertex *shadowVT,Draw_CarCache *sd)

{
  short t3;
  short * z;
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  u_char uVar6;
  u_char uVar7;
  u_char uVar8;
  u_char uVar9;
  u_char uVar10;
  u_char uVar11;
  u_char uVar12;
  u_short uv0;
  u_short uv1;
  short t2;
  short t1;
  u_short uv2;
  u_short uv3;
  u_char *u2;
  COORD16 *vt2;
  Draw_tPixMap *shadowPmx;
  Draw_tPixMap *pmx;
  
  pmx = gShadowPixmap[0];
  if (R3DCar_InMenu != 0) {
    pmx = gMenuPixmap[1];
  }
  ChangeTPage(&pmx->tpage,2);
gte_SetRotMatrix(&DrawC_gScreenMat);
gte_SetTransMatrix(&DrawC_gScreenMat);
  vt2 = &sd->vt8;
  sVar1 = (shadowVT->sv).y;
  sVar2 = (shadowVT->sv).z;
  (sd->vt0).x = (shadowVT->sv).x;
  (sd->vt0).y = sVar1;
  (sd->vt0).z = sVar2;
  sVar1 = shadowVT[1].sv.x;
  sVar2 = shadowVT[1].sv.y;
  (sd->vt1).z = shadowVT[1].sv.z;
  (sd->vt1).x = sVar1;
  (sd->vt1).y = sVar2;
  sVar1 = shadowVT[3].sv.y;
  sVar2 = shadowVT[3].sv.z;
  (sd->vt2).x = shadowVT[3].sv.x;
  (sd->vt2).y = sVar1;
  (sd->vt2).z = sVar2;
  sVar1 = shadowVT[2].sv.x;
  sVar2 = shadowVT[2].sv.y;
  sVar3 = shadowVT[2].sv.z;
  (sd->vt0).x = (sd->vt0).x << 2;
  sVar4 = (sd->vt0).y;
  (sd->vt0).z = (sd->vt0).z << 2;
  sVar5 = (sd->vt1).y;
  u2 = &sd->offsetU2;
  (sd->vt3).x = sVar1;
  (sd->vt3).y = sVar2;
  (sd->vt3).z = sVar3;
  (sd->vt0).y = sVar4 << 2;
  (sd->vt1).x = (sd->vt1).x << 2;
  (sd->vt1).y = sVar5 << 2;
  sVar4 = (sd->vt2).x;
  (sd->vt1).z = (sd->vt1).z << 2;
  (sd->vt2).x = sVar4 << 2;
  (sd->vt2).y = (sd->vt2).y << 2;
  (sd->vt2).z = (sd->vt2).z << 2;
  (sd->vt3).y = sVar2 << 2;
  (sd->vt3).x = sVar1 << 2;
  sVar1 = (sd->vt0).x;
  sVar2 = (sd->vt1).x;
  (sd->vt3).z = sVar3 << 2;
  sVar3 = (sd->vt0).y;
  sVar4 = (sd->vt1).y;
  (sd->vt4).x = (short)((int)sVar1 + (int)sVar2 + 1 >> 1);
  sVar1 = (sd->vt0).z;
  sVar2 = (sd->vt1).z;
  (sd->vt4).y = (short)((int)sVar3 + (int)sVar4 + 1 >> 1);
  sVar3 = (sd->vt1).x;
  sVar4 = (sd->vt2).x;
  (sd->vt4).z = (short)((int)sVar1 + (int)sVar2 + 1 >> 1);
  sVar1 = (sd->vt1).y;
  sVar2 = (sd->vt2).y;
  (sd->vt5).x = (short)((int)sVar3 + (int)sVar4 + 1 >> 1);
  sVar3 = (sd->vt1).z;
  sVar4 = (sd->vt2).z;
  (sd->vt5).y = (short)((int)sVar1 + (int)sVar2 + 1 >> 1);
  sVar1 = (sd->vt2).x;
  sVar2 = (sd->vt3).x;
  (sd->vt5).z = (short)((int)sVar3 + (int)sVar4 + 1 >> 1);
  (sd->vt6).x = (short)((int)sVar1 + (int)sVar2 + 1 >> 1);
  sVar1 = (sd->vt3).z;
  sVar2 = (sd->vt2).z;
  (sd->vt6).y = (short)((int)(sd->vt2).y + (int)(sd->vt3).y + 1 >> 1);
  sVar3 = (sd->vt3).x;
  sVar4 = (sd->vt0).x;
  (sd->vt6).z = (short)((int)sVar2 + (int)sVar1 + 1 >> 1);
  sVar1 = (sd->vt3).y;
  sVar2 = (sd->vt0).y;
  (sd->vt7).x = (short)((int)sVar3 + (int)sVar4 + 1 >> 1);
  sVar3 = (sd->vt3).z;
  sVar4 = (sd->vt0).z;
  (sd->vt7).y = (short)((int)sVar1 + (int)sVar2 + 1 >> 1);
  sVar1 = (sd->vt0).x;
  sVar2 = (sd->vt2).x;
  (sd->vt7).z = (short)((int)sVar3 + (int)sVar4 + 1 >> 1);
  sVar3 = (sd->vt2).y;
  sVar4 = (sd->vt0).y;
  (sd->vt8).x = (short)((int)sVar1 + (int)sVar2 + 1 >> 1);
  sVar1 = (sd->vt2).z;
  sVar2 = (sd->vt0).z;
  (sd->vt8).y = (short)((int)sVar4 + (int)sVar3 + 1 >> 1);
  (sd->vt8).z = (short)((int)sVar2 + (int)sVar1 + 1 >> 1);
  uVar6 = pmx->v0;
  uVar7 = pmx->u1;
  uVar8 = pmx->v1;
  uVar9 = pmx->u3;
  uVar10 = pmx->v3;
  uVar11 = pmx->u2;
  uVar12 = pmx->v2;
  sd->u0 = pmx->u0;
  sd->v0 = uVar6;
  sd->u1 = uVar7;
  sd->v1 = uVar8;
  sd->u2 = uVar9;
  sd->v2 = uVar10;
  sd->u3 = uVar11;
  sd->v3 = uVar12;
  sd->u4 = (u_char)((int)((u_int)sd->u0 + (u_int)sd->u1 + 1) >> 1);
  sd->v4 = (u_char)((int)((u_int)sd->v0 + (u_int)sd->v1 + 1) >> 1);
  sd->u5 = (u_char)((int)((u_int)sd->u1 + (u_int)sd->u2 + 1) >> 1);
  sd->v5 = (u_char)((int)((u_int)sd->v1 + (u_int)sd->v2 + 1) >> 1);
  sd->offsetU0 = (u_char)((int)((u_int)sd->u2 + (u_int)sd->u3 + 1) >> 1);
  sd->offsetV0 = (u_char)((int)((u_int)sd->v2 + (u_int)sd->v3 + 1) >> 1);
  sd->offsetU1 = (u_char)((int)((u_int)sd->u3 + (u_int)sd->u0 + 1) >> 1);
  sd->offsetV1 = (u_char)((int)((u_int)sd->v3 + (u_int)sd->v0 + 1) >> 1);
  sd->offsetU2 = (u_char)((int)((u_int)sd->u0 + (u_int)sd->u2 + 1) >> 1);
  sd->offsetV2 = (u_char)((int)((u_int)sd->v0 + (u_int)sd->v2 + 1) >> 1);
  DrawC_DivideShadowPrim(&sd->vt0,&sd->vt4,vt2,&sd->vt7,(u_short *)&sd->u0,(u_short *)&sd->u4,(u_short *)u2,
             (u_short *)&sd->offsetU1,pmx,sd);
  DrawC_DivideShadowPrim(&sd->vt4,&sd->vt1,&sd->vt5,vt2,(u_short *)&sd->u4,(u_short *)&sd->u1,(u_short *)&sd->u5,
             (u_short *)u2,pmx,sd);
  DrawC_DivideShadowPrim(&sd->vt7,vt2,&sd->vt6,&sd->vt3,(u_short *)&sd->offsetU1,(u_short *)u2,
             (u_short *)&sd->offsetU0,(u_short *)&sd->u3,pmx,sd);
  DrawC_DivideShadowPrim(&sd->vt8,&sd->vt5,&sd->vt2,&sd->vt6,(u_short *)u2,(u_short *)&sd->u5,(u_short *)&sd->u2,
             (u_short *)&sd->offsetU0,pmx,sd);
  return;
}

/* ---- DrawC_SpotPrims__FP10matrixtdefP8coorddefP13Draw_CarCache  [DRAWC.CPP:4189-4254] SLD-VERIFIED ---- */
void DrawC_SpotPrims(matrixtdef *m,coorddef *t,Draw_CarCache *sd)

{
  int r0;
  int r1;
  int r2;
  short * z;
  short t2;
  short sVar1;
  short t3;
  short sVar2;
  COORD16 *pCVar3;
  short t1;
  int iVar4;
  u_int uVar5;
  DR_MODE *prim;
  int iVar6;
  DR_MODE *pDVar7;
  u_int *puVar8;
  int iPlus;
  u_int *puVar9;
  int i;
  u_long *ot;
  u_long *puVar10;
  u_int uVar11;
  u_int uVar12;
  COORD16 *pCVar13;
  COORD16 *pCVar14;
  
  TrsProj_SetTransPrecision(8);
  iVar4 = m->m[3];
  iVar6 = m->m[6];
  (sd->matB).m[0][0] = (short)(m->m[0] >> 4);
  (sd->matB).m[0][1] = (short)(iVar4 >> 4);
  (sd->matB).m[0][2] = (short)(iVar6 >> 4);
  iVar4 = m->m[4];
  iVar6 = m->m[7];
  sVar2 = (short)(m->m[1] >> 4);
  (sd->matB).m[1][0] = sVar2;
  (sd->matB).m[1][1] = (short)(iVar4 >> 4);
  (sd->matB).m[1][2] = (short)(iVar6 >> 4);
  iVar4 = m->m[2];
  iVar6 = m->m[5];
  iPlus = m->m[8];
  (sd->matB).m[1][0] = -sVar2;
  sVar2 = (sd->matB).m[1][1];
  (sd->matB).m[2][0] = (short)(iVar4 >> 4);
  sVar1 = (sd->matB).m[1][2];
  (sd->matB).m[2][1] = (short)(iVar6 >> 4);
  (sd->matB).m[2][2] = (short)(iPlus >> 4);
  (sd->matB).m[1][1] = -sVar2;
  (sd->matB).m[1][2] = -sVar1;
  iVar4 = TrsProj_precision;
  (sd->matB).t[0] = t->x >> (TrsProj_precision & 0x1fU);
  (sd->matB).t[1] = -(t->y >> (iVar4 & 0x1fU));
  (sd->matB).t[2] = t->z >> (iVar4 & 0x1fU);
  TrsProj_ResetTransPrecision();
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
  pDVar7 = (DR_MODE *)(sd->head).cprim.PrimPtr;
  puVar10 = (sd->head).cprim.LastPrim;
  sd->otz = 0;
  (sd->head).cprim.PrimPtr = (char *)(pDVar7 + 1);
  puVar8 = (u_int *)(puVar10 + sd->otz);
  pDVar7->tag = (u_long)(intptr)(u_long *)((u_int)pDVar7->tag & 0xff000000 | *puVar8 & 0xffffff);
  *puVar8 = *puVar8 & 0xff000000 | (u_int)pDVar7 & 0xffffff;
  SetDrawMode(pDVar7,0,0,0x120,(PSX_RECT *)0x0);
  sVar1 = Fe3D_spotVertex[0x20].z;
  sVar2 = Fe3D_spotVertex[0x20].y;
  uVar11 = 0xffffff;
  uVar12 = 0xff000000;
  pCVar13 = Fe3D_spotVertex;
  (sd->vt0).x = Fe3D_spotVertex[0x20].x;
  (sd->vt0).y = sVar2;
  (sd->vt0).z = sVar1;
  pCVar14 = pCVar13;
  for (iVar4 = 0; iVar6 = iVar4 + 1, iVar4 < 0x20; iVar4 = iVar4 + 1) {
    if (iVar6 == 0x20) {
      iVar6 = 0;
    }
    if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
      sVar2 = pCVar13->y;
      sVar1 = pCVar13->z;
      (sd->vt1).x = pCVar13->x;
      pCVar3 = pCVar14 + iVar6;
      (sd->vt1).y = sVar2;
      (sd->vt1).z = sVar1;
      sVar2 = pCVar3->x;
      sVar1 = pCVar3->y;
      (sd->vt2).z = pCVar3->z;
      (sd->vt2).x = sVar2;
      (sd->vt2).y = sVar1;
gte_lwc2(0,*(int *)(((char *)sd + 0xac)));
      gte_lwc2(1,*(int *)(((char *)sd + 0xb0)));
      gte_lwc2(2,*(int *)(((char *)sd + 0xb4)));
      gte_lwc2(3,*(int *)(((char *)sd + 0xb8)));
      gte_lwc2(4,*(int *)(((char *)sd + 0xbc)));
      gte_lwc2(5,*(int *)(((char *)sd + 0xc0)));
      gte_rtpt();
      puVar8 = (u_int *)(sd->head).cprim.PrimPtr;
      puVar10 = (sd->head).cprim.LastPrim;
      (sd->head).cprim.PrimPtr = (char *)(puVar8 + 7);
      puVar9 = (u_int *)(puVar10 + sd->otz);
      *puVar8 = *puVar8 & uVar12 | *puVar9 & uVar11;
      *puVar9 = *puVar9 & uVar12 | (u_int)puVar8 & uVar11;
      /* Retail 0x800C4ACC..0x800C4AD4: SXY0..2 -> POLY_G3. */
      gte_swc2(12,puVar8 + 2);
      gte_swc2(13,puVar8 + 4);
      gte_swc2(14,puVar8 + 6);
      uVar5 = sd->color;
      ((u_char *)puVar8)[3] = 6;
      puVar8[3] = 0;
      puVar8[5] = 0;
      puVar8[1] = uVar5;
      ((u_char *)puVar8)[7] = 0x32;
    }
    pCVar13 = pCVar13 + 1;
  }
  pDVar7 = (DR_MODE *)(sd->head).cprim.PrimPtr;
  puVar10 = (sd->head).cprim.LastPrim;
  (sd->head).cprim.PrimPtr = (char *)(pDVar7 + 1);
  puVar8 = (u_int *)(puVar10 + sd->otz);
  pDVar7->tag = (u_long)(intptr)(u_long *)((u_int)pDVar7->tag & 0xff000000 | *puVar8 & 0xffffff);
  *puVar8 = *puVar8 & 0xff000000 | (u_int)pDVar7 & 0xffffff;
  SetDrawMode(pDVar7,0,1,0x120,(PSX_RECT *)0x0);
  return;
}

/* ---- DrawC_ShowroomPrims__FP10matrixtdefP8coorddefP13Draw_CarCache  [DRAWC.CPP:4260-4378] SLD-VERIFIED ---- */
void DrawC_ShowroomPrims(matrixtdef *m,coorddef *t,Draw_CarCache *sd)

{
  int index;
  int r0;
  int r1;
  int r2;
  int iPlus;
  short t1;
  short t2;
  short t3;
  short * z;
  u_long * ot;
  short sVar1;
  Draw_tPixMap *pDVar2;
  short sVar3;
  u_long l0;
  int iVar4;
  int iVar5;
  char *pcVar6;
  COORD16 *pCVar7;
  u_int uVar8;
  u_long l1;
  u_long l2;
  u_int *puVar9;
  u_int uVar10;
  u_long l3;
  int iVar11;
  u_int uVar12;
  int *prim;
  u_int *puVar13;
  int j;
  int i;
  int clipH;
  int *piVar14;
  char *pcVar15;
  u_char code;
  COORD16 *pCVar16;
  u_int uVar17;
  u_long *puVar18;
  Draw_tPixMap *lightPmx;
  u_int *copyLastPrim;
  int tpageShadow;
  int eSpeed;
  int half;
  COORD16 *pCVar19;
  COORD16 *pCVar20;
  char filename [10];
  char hilight_state [32];
  int hilight [2];
  int hilight_direction [2];
  int *light;
  
  pDVar2 = gMenuPixmap[3];
  if (gShowroomLights != 0) {
    iVar4 = gettick();
    iVar5 = iVar4;
    if (iVar4 < 0) {
      iVar5 = iVar4 + 0xff;
    }
    hilight[0] = iVar4 + (iVar5 >> 8) * -0x100 >> 3;
    hilight_direction[0] = -1;
    if (DrawC_gMenuLightsDirection == 0) {
      hilight[1] = hilight[0] + 0x10U & 0x1f;
      hilight_direction[1] = -1;
    }
    else {
      hilight[1] = 0x20 - hilight[0];
      hilight_direction[1] = 1;
    }
    iVar5 = 0x1f;
    pcVar6 = hilight_state + 0x1f;
    do {
      *pcVar6 = -1;
      iVar5 = iVar5 + -1;
      pcVar6 = pcVar6 + -1;
    } while (-1 < iVar5);
    iVar5 = 0;
    piVar14 = hilight_direction;
    prim = hilight;
    do {
      iVar4 = 0;
      do {
        if (hilight_state[*prim + iVar4 * *piVar14 & 0x1f] < iVar4) {
          hilight_state[*prim + iVar4 * *piVar14 & 0x1f] = (char)iVar4;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 5);
      piVar14 = piVar14 + 1;
      iVar5 = iVar5 + 1;
      prim = prim + 1;
    } while (iVar5 < 2);
    ChangeTPage(&pDVar2->tpage,1);
    TrsProj_SetTransPrecision(8);
    iVar5 = m->m[3];
    iVar4 = m->m[6];
    (sd->matB).m[0][0] = (short)(m->m[0] >> 4);
    (sd->matB).m[0][1] = (short)(iVar5 >> 4);
    (sd->matB).m[0][2] = (short)(iVar4 >> 4);
    iVar5 = m->m[4];
    iVar4 = m->m[7];
    sVar3 = (short)(m->m[1] >> 4);
    (sd->matB).m[1][0] = sVar3;
    (sd->matB).m[1][1] = (short)(iVar5 >> 4);
    (sd->matB).m[1][2] = (short)(iVar4 >> 4);
    iVar5 = m->m[2];
    iVar4 = m->m[5];
    iVar11 = m->m[8];
    (sd->matB).m[1][0] = -sVar3;
    sVar3 = (sd->matB).m[1][1];
    (sd->matB).m[2][0] = (short)(iVar5 >> 4);
    sVar1 = (sd->matB).m[1][2];
    (sd->matB).m[2][1] = (short)(iVar4 >> 4);
    (sd->matB).m[2][2] = (short)(iVar11 >> 4);
    (sd->matB).m[1][1] = -sVar3;
    (sd->matB).m[1][2] = -sVar1;
    iVar5 = TrsProj_precision;
    (sd->matB).t[0] = t->x >> (TrsProj_precision & 0x1fU);
    (sd->matB).t[1] = -(t->y >> (iVar5 & 0x1fU));
    (sd->matB).t[2] = t->z >> (iVar5 & 0x1fU);
    TrsProj_ResetTransPrecision();
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
    pcVar6 = hilight_state;
    uVar17 = 0xffffff;
    pCVar19 = Fe3D_lightsVertex;
    pCVar16 = Fe3D_lightsVertex + 1;
    sd->otz = 0;
    pCVar20 = pCVar19;
    for (iVar5 = 0; iVar5 < 0x20; iVar5 = iVar5 + 1) {
      iVar4 = iVar5 * 2 + 2;
      if (iVar4 == 0x40) {
        iVar4 = 0;
      }
      iVar11 = 0;
      if ((sd->head).cprim.MPrimPtr <= (sd->head).cprim.PrimPtr) {
        return;
      }
      sVar3 = pCVar19->x;
      sVar1 = pCVar19->z;
      (sd->vt0).y = pCVar19->y;
      (sd->vt0).x = sVar3;
      pCVar7 = pCVar20 + iVar4;
      (sd->vt0).z = sVar1;
      sVar3 = pCVar7->y;
      sVar1 = pCVar7->z;
      pcVar15 = pcVar6 + iVar5;
      (sd->vt1).x = pCVar7->x;
      (sd->vt1).y = sVar3;
      (sd->vt1).z = sVar1;
      sVar3 = pCVar16->y;
      sVar1 = pCVar16->z;
      (sd->vt2).x = pCVar16->x;
      (sd->vt2).y = sVar3;
      (sd->vt2).z = sVar1;
      sVar3 = Fe3D_lightsVertex[iVar4 + 1].y;
      sVar1 = Fe3D_lightsVertex[iVar4 + 1].z;
      puVar18 = hilight_colors;
      (sd->vt3).x = Fe3D_lightsVertex[iVar4 + 1].x;
      (sd->vt3).y = sVar3;
      (sd->vt3).z = sVar1;
      for (; iVar11 < 2; iVar11 = iVar11 + 1) {
        if ((iVar11 == 0) || (-1 < *pcVar15)) {
gte_lwc2(0,*(int *)(((char *)sd + 0xac)));
          gte_lwc2(1,*(int *)(((char *)sd + 0xb0)));
          gte_rtps();
          puVar13 = (u_int *)(sd->head).cprim.PrimPtr;
          (sd->head).cprim.PrimPtr = (char *)(puVar13 + 10);
          puVar9 = (u_int *)((sd->head).cprim.LastPrim + sd->otz);
          *puVar13 = *puVar13 & 0xff000000 | *puVar9 & uVar17;
          *puVar9 = *puVar9 & 0xff000000 | (u_int)puVar13 & uVar17;
gte_swc2(0xe,(char *)puVar13 + 0x08);
gte_lwc2(0,*(int *)(((char *)sd + 0xb4)));
          gte_lwc2(1,*(int *)(((char *)sd + 0xb8)));
          gte_lwc2(2,*(int *)(((char *)sd + 0x3d0)));
          gte_lwc2(3,*(int *)(((char *)sd + 0x3d4)));
          gte_lwc2(4,*(int *)(((char *)sd + 0xbc)));
          gte_lwc2(5,*(int *)(((char *)sd + 0xc0)));
          gte_rtpt();
gte_swc2(0xc,(char *)puVar13 + 0x10);
          gte_swc2(0xd,(char *)puVar13 + 0x20);
          gte_swc2(0xe,(char *)puVar13 + 0x18);
          if (iVar11 == 0) {
            uVar8 = 0x300a00;
          }
          else {
            uVar8 = puVar18[*pcVar15];
          }
          puVar13[1] = uVar8;
          ((u_char *)puVar13)[7] = 0x2e;
          ((u_char *)puVar13)[3] = 9;
          uVar8 = *(u_int *)&pDVar2->u1;
          uVar10 = *(u_int *)&pDVar2->u2;
          uVar12 = *(u_int *)&pDVar2->u3;
          puVar13[3] = *(u_int *)pDVar2;
          puVar13[5] = uVar8;
          puVar13[7] = uVar10;
          puVar13[9] = uVar12;
        }
      }
      pCVar16 = pCVar16 + 2;
      pCVar19 = pCVar19 + 2;
    }
  }
  return;
}

/* end of draww.cpp */

/* owning-TU def (extern-declared, never defined; link-harness) */
