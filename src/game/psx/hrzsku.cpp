/* game/psx/hrzsku.cpp -- RECONSTRUCTED (NFS4 PSX in-race HUD; C++ TU)
 *   62 fns: sprite/poly builders, tachometer, number rasterizer, mini-map + radar,
 *   CD player, wingman interface, render views (hud/tac/map/stats), 3-2-1-GO, BTC/busted.
 *   Reconstructed with full SYM-locals applied (audited).
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "hrzsku_externs.h"
#ifdef AP_WIN
extern "C" void AddPrim(void *,void *);
extern "C" void NFSHS_HostTraceSkyProjection(void *);
extern "C" void NFSHS_HostTraceHorizonCache(void *);
#endif

/* ---- link-harness owned-global definition (extern-declared, never defined) ---- */
int Hrz_gProjResultZ0; int Hrz_gProjScratch_9C;  /* HrzSku.obj-owned projection scratch (BSS) */

/* ---- HrzSku.obj-OWNED globals -- DEFINED here (self-contained; SYM-typed via gen_owned_defs:
   .data = real NFS4.EXE bytes, .bss = zero) ---- */
Draw_tPixMap *gHorizonPixmap[16];   /* @0x801202f8  (bss(zero)) */
Draw_tPixMap gHorizonExtraSkyPixmaps[4];   /* @0x80120338  (bss(zero)) */
SVECTOR      gSkyMesh[85];   /* @0x80120378  (bss(zero)) */
CVECTOR      gSkyColor[85];   /* @0x80120620  (bss(zero)) */
char         gSkyPixmapIndex[64];   /* @0x80120774  (bss(zero)) */
Draw_tPixMap *gpPmx[16];   /* @0x801207b4  (bss(zero)) */
CVECTOR      gHrzRingColor[2][17];   /* @0x801207f4  (bss(zero)) */
int          gfxPmxHeightPercentage[16];   /* @0x8012087c  (bss(zero)) */
tHrz_Lightning gHrz_Lightning;   /* @0x801208bc  (bss(zero)) */
SVECTOR      *starPosInSky;   /* @0x8013d878  (bss(zero)) */
CVECTOR      *starColors;   /* @0x8013d87c  (bss(zero)) */
CHorizonSpec *Hrz_gTrackSpec;   /* @0x8013d888  (bss(zero)) */
CSkySpec     *Sky_gTrackSpec;   /* @0x8013d88c  (bss(zero)) */
SVECTOR      *gRngCoordTop;   /* @0x8013d890  (bss(zero)) */
SVECTOR      Hrz_gLightningPosInSky;   /* @0x8013d894  (bss(zero)) */
SVECTOR      sunPosInSky;   /* @0x8013ddf0  (bss(zero)) */
SVECTOR      moonPosInSky;   /* @0x8013ddf8  (bss(zero)) */
CVECTOR      Hrz_gSaveCol[4];   /* @0x8013e380  (bss?) */
/* hrzsku-internal lost-symbol globals (NOT in SYM Globals; 4 contiguous ints, sky double-buffer
   vertex counts, accessed via (&A0)[i]). DEFINED here for self-containment (was extern-only). */

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void Horizon_InterpolateLineSCoords(DVECTOR *sc,DVECTOR *s0,DVECTOR *s1,int *percentage,int n,int bPercentageArray);
void Sky_InitStars(void);
void Sky_KillStars(void);
void Hrz_InitSkyColor(void);
void Hrz_InitSky(void);
void Hrz_Init2DRing(void);
void Hrz_GetHorizonPixMap(Draw_tPixMap *p);
extern "C" { void Hrz_InitHorizon(void); }
extern "C" { void Hrz_KillHorizon(void); }
void Hrz_LightningAddFork(char direction,char column,char row);
void Hrz_CalculateLightning(void);
void Hrz_TextureQuad(DVECTOR *pt,char type,char bright,Draw_DCache *sd);
void Hrz_SetLightingPosInSky(DRender_tView *Vi);
void Hrz_BuildForkLightning(Draw_DCache *sd);
void Hrz_LightningFlicker(int on);
void HrzSetPsxMatrix(matrixtdef *m);
void HrzSetPsxTranslation(coorddef *t);
void Hrz_RotProj16(int n, SVECTOR *s, int *z, DVECTOR *p);
void Hrz_SetDitheringPrim(int dither,int otz);
void Hrz_BuildSky(void);
void Sky_RenderStars(Draw_SkyCache *sd,int otz);
void Hrz_BuildHorizon(DRender_tView *Vi);


/* ---- Horizon_InterpolateLineSCoords__FP7DVECTORN20Piii  [HRZSKU.CPP:128-156] SLD-VERIFIED ---- */
void Horizon_InterpolateLineSCoords(DVECTOR *sc,DVECTOR *s0,DVECTOR *s1,int *percentage,int n,int bPercentageArray)

{
  int iVar1;
  int iVar2;
  short *pScOut;
  int p;
  int i;
  int iVar3;
  
  pScOut = (short *)sc;
  if (bPercentageArray == 0) {
    iVar3 = *percentage;
    iVar1 = 0;
    if (0 < n) {
      do {
        iVar2 = iVar3 * ((int)s1->vx - (int)s0->vx);
        if (iVar2 < 0) {
          iVar2 = iVar2 + 0xffff;
        }
        *pScOut = s0->vx + (short)((u_int)iVar2 >> 0x10);
        iVar2 = iVar3 * ((int)s1->vy - (int)s0->vy);
        if (iVar2 < 0) {
          iVar2 = iVar2 + 0xffff;
        }
        pScOut[1] = s0->vy + (short)((u_int)iVar2 >> 0x10);
        s0 = s0 + 1;
        s1 = s1 + 1;
        iVar1 = iVar1 + 1;
        pScOut = pScOut + 2;
      } while (iVar1 < n);
      return;
    }
  }
  else {
    iVar3 = 0;
    if (0 < n) {
      do {
        iVar1 = *percentage * ((int)s1->vx - (int)s0->vx);
        if (iVar1 < 0) {
          iVar1 = iVar1 + 0xffff;
        }
        *pScOut = s0->vx + (short)((u_int)iVar1 >> 0x10);
        iVar1 = *percentage * ((int)s1->vy - (int)s0->vy);
        if (iVar1 < 0) {
          iVar1 = iVar1 + 0xffff;
        }
        pScOut[1] = s0->vy + (short)((u_int)iVar1 >> 0x10);
        percentage = percentage + 1;
        s0 = s0 + 1;
        s1 = s1 + 1;
        iVar3 = iVar3 + 1;
        pScOut = pScOut + 2;
      } while (iVar3 < n);
    }
  }
  return;
}

/* ---- Sky_InitStars__Fv  [HRZSKU.CPP:185-211] SLD-VERIFIED ---- */
void Sky_InitStars(void)

{
  int seed;
  u_int uVar1;
  u_int uVar2;
  int iVar3;
  int iVar4;
  u_int uVar5;
  SVECTOR *pSVar6;
  int starBright;
  int heightAngle;
  int iVar7;
  int radius;
  int height;
  int latAngle;
  int i;
  int iVar8;
  long oldSeed;
  
  if (starPosInSky == (SVECTOR *)0x0) {
    seed = random();
    seedrandom(Sky_gTrackSpec->starRandomSeed);
    starPosInSky = (SVECTOR *)reservememadr("stars",Sky_gTrackSpec->numStars << 3,0);
    starColors = (CVECTOR *)reservememadr("starCols",Sky_gTrackSpec->numStars << 2,0);
    for (iVar8 = 0; iVar8 < Sky_gTrackSpec->numStars; iVar8 = iVar8 + 1) {
      uVar1 = random();
      uVar2 = random();
      uVar5 = Sky_gTrackSpec->starAngleHigh - Sky_gTrackSpec->starAngleLow;
      if (uVar5 == 0) {
        trap(0x1c00);
      }
      iVar7 = Sky_gTrackSpec->starAngleLow + uVar2 % uVar5;
      iVar3 = fixedsin(iVar7);
      iVar3 = fixedmult(iVar3,1000);
      iVar7 = fixedcos(iVar7);
      iVar7 = fixedmult(iVar7,1000);
      iVar4 = fixedsin(uVar1 & 0xffff);
      iVar4 = fixedmult(iVar4,iVar7);
      pSVar6 = starPosInSky + iVar8;
      pSVar6->vx = (short)iVar4;
      pSVar6->vy = (short)iVar3;
      iVar3 = fixedcos(uVar1 & 0xffff);
      iVar3 = fixedmult(iVar3,iVar7);
      starPosInSky[iVar8].vz = (short)iVar3;
      uVar1 = random();
      uVar2 = Sky_gTrackSpec->starBrightMax - Sky_gTrackSpec->starBrightMin;
      if (uVar2 == 0) {
        trap(0x1c00);
      }
      uVar1 = Sky_gTrackSpec->starBrightMin + uVar1 % uVar2;
      (*(u_long *)&starColors[iVar8]) = uVar1 * 0x10000 | uVar1 * 0x100 | uVar1;
    }
    seedrandom(seed);
  }
  return;
}

/* ---- Sky_KillStars__Fv  [HRZSKU.CPP:216-222] SLD-VERIFIED ---- */
void Sky_KillStars(void)

{
  if (starPosInSky != (SVECTOR *)0x0) {
    purgememadr(starPosInSky);
  }
  if (starColors != (CVECTOR *)0x0) {
    purgememadr(starColors);
  }
  starPosInSky = (SVECTOR *)0x0;
  starColors = (CVECTOR *)0x0;
  return;
}

/* ---- Hrz_InitSkyColor__Fv  [HRZSKU.CPP:227-252] SLD-VERIFIED ---- */
void Hrz_InitSkyColor(void)
{
  int i, j, k, l;
  CVECTOR rounddiff, cur_bk, cur_fr;
  CVECTOR *pCVar9;

  k = 0;
  for (i = 0; i < 5; i++) {
    cur_bk = Sky_gTrackSpec->backcolors[i];
    cur_fr = Sky_gTrackSpec->frontcolors[i];
    j = cur_bk.r - cur_fr.r;  if (j < 0) j = j + 7;  rounddiff.r = (u_char)(j >> 3);
    j = cur_bk.g - cur_fr.g;  if (j < 0) j = j + 7;  rounddiff.g = (u_char)(j >> 3);
    j = cur_bk.b - cur_fr.b;  if (j < 0) j = j + 7;  rounddiff.b = (u_char)(j >> 3);
    pCVar9 = gSkyColor + k;
    for (l = 0; l < 0x11; l++) {
      j = l;
      if (8 < l) j = 0x10 - l;
      pCVar9->r = cur_fr.r + (char)rounddiff.r * (char)j;
      pCVar9->g = cur_fr.g + (char)rounddiff.g * (char)j;
      pCVar9->b = cur_fr.b + (char)rounddiff.b * (char)j;
      pCVar9 = pCVar9 + 1;
      k = k + 1;
    }
  }
}

/* ---- Hrz_InitSky__Fv  [HRZSKU.CPP:257-332] SLD-VERIFIED ---- */
void Hrz_InitSky(void)

{
  CSkySpec *pCVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int angle;
  int iVar5;
  int angle_00;
  int j;
  int iVar6;
  SVECTOR *pSVar7;
  int i;
  int iVar8;
  int height;
  int radius;
  int k;
  
  iVar2 = fixedcos(Sky_gTrackSpec->sunAngleInSky);
  iVar2 = fixedmult(iVar2,1000);
  sunPosInSky.vx = (short)iVar2;
  iVar2 = fixedsin(Sky_gTrackSpec->sunAngleInSky);
  iVar2 = fixedmult(iVar2,1000);
  sunPosInSky.vz = (short)iVar2;
  sunPosInSky.vy =
       (short)TrackSpec_gSpec.skyspec.sunHeightInSky + (short)TrackSpec_gSpec.skyspec.yoffset;
  iVar2 = fixedcos(Sky_gTrackSpec->moonAngleInSky);
  iVar2 = fixedmult(iVar2,1000);
  moonPosInSky.vx = (short)iVar2;
  iVar2 = fixedsin(Sky_gTrackSpec->moonAngleInSky);
  iVar2 = fixedmult(iVar2,1000);
  moonPosInSky.vz = (short)iVar2;
  moonPosInSky.vy =
       (short)TrackSpec_gSpec.skyspec.moonHeightInSky + (short)TrackSpec_gSpec.skyspec.yoffset;
  iVar2 = Draw_gPlayer1View;
  if (GameSetup_gData.commMode == 1) {
    Draw_SetViewColor(Draw_gPlayer1View,(u_int)(Sky_gTrackSpec->clearcolor).r,
               (u_int)(Sky_gTrackSpec->clearcolor).g,(u_int)(Sky_gTrackSpec->clearcolor).b);
    iVar2 = Draw_gPlayer2View;
  }
  iVar8 = 0;
  Draw_SetViewColor(iVar2,(u_int)(Sky_gTrackSpec->clearcolor).r,(u_int)(Sky_gTrackSpec->clearcolor).g,
             (u_int)(Sky_gTrackSpec->clearcolor).b);
  iVar2 = 0;
  do {
    if ((Sky_gTrackSpec->flags & 0x80U) == 0) {
      if (((Sky_gTrackSpec->flags & 2U) == 0) || (iVar3 = iVar8 << 0xb, 3 < iVar8)) {
        iVar3 = iVar8 << 0xc;
      }
      iVar4 = fixedcos(iVar3);
      iVar4 = fixedmult(iVar4,1000);
    }
    else {
      iVar3 = fixedcos(Sky_gTrackSpec->ringAngles[iVar8]);
      iVar4 = fixedmult(iVar3,1000);
      iVar3 = Sky_gTrackSpec->ringAngles[iVar8];
    }
    iVar6 = 0;
    iVar3 = fixedsin(iVar3);
    iVar3 = fixedmult(iVar3,1000);
    pSVar7 = gSkyMesh + iVar2;
    do {
      iVar5 = iVar6 * 0x1000;
      iVar6 = iVar6 + 1;
      angle_00 = (iVar5 - Sky_gTrackSpec->sunAngleInSky) + 0x4000;
      iVar5 = fixedsin(angle_00);
      iVar5 = fixedmult(iVar5,iVar4);
      pCVar1 = Sky_gTrackSpec;
      iVar2 = iVar2 + 1;
      pSVar7->vx = (short)iVar5;
      pSVar7->vy = (short)pCVar1->yoffset + (short)iVar3;
      iVar5 = fixedcos(angle_00);
      iVar5 = fixedmult(iVar5,iVar4);
      pSVar7->vz = (short)iVar5;
      pSVar7 = pSVar7 + 1;
    } while (iVar6 < 0x11);
    iVar8 = iVar8 + 1;
  } while (iVar8 < 5);
  iVar2 = 0;
  if (Sky_gTrackSpec->type == 1) {
    iVar8 = 0;
    do {
      iVar3 = 0;
      do {
        iVar4 = iVar3;
        if (iVar3 < 0) {
          iVar4 = iVar3 + 3;
        }
        iVar4 = iVar3 + (iVar4 >> 2) * -4;
        iVar3 = iVar3 + 1;
        gSkyPixmapIndex[iVar8] = Sky_gTrackSpec->cloudIndices[iVar2][iVar4] + '\b';
        iVar8 = iVar8 + 1;
      } while (iVar3 < 0x10);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
    if ((Sky_gTrackSpec->type == 1) && ((Sky_gTrackSpec->flags & 0x20U) == 0))
    goto HrzInitSky_initLensFlare;
  }
  Hrz_InitSkyColor();
HrzInitSky_initLensFlare:
  Flare_InitLensFlare();
  return;
}

/* ---- Hrz_Init2DRing__Fv  [HRZSKU.CPP:337-414] SLD-VERIFIED ---- */
void Hrz_Init2DRing(void)

{
  int pmxHeight[16];
  int maxPmxHeight = 1;

  for (int i = 0; i < 0x11; ++i) {
    int angle = i * 0x1000 + Hrz_gTrackSpec->angle;
    gRngCoordTop[i].vx = (short)fixedmult(fixedsin(angle),32000);
    gRngCoordTop[i].vy = 0;
    gRngCoordTop[i].vz = (short)fixedmult(fixedcos(angle),32000);
  }

  for (int i = 0; i < 0x10; ++i) {
    Draw_tPixMap *pmx = gHorizonPixmap[(u_char)Hrz_gTrackSpec->ringPMX[i] & 7];
    gpPmx[i] = pmx;
    pmxHeight[i] = (u_int)pmx->v2 - (u_int)pmx->v1;
    if (maxPmxHeight < pmxHeight[i]) {
      maxPmxHeight = pmxHeight[i];
    }
  }

  for (int i = 0; i < 0x10; ++i) {
    int scaledHeight = nfs4_mips_sll_s32(pmxHeight[i],0x10);
    if ((maxPmxHeight == -1) && (scaledHeight == -0x80000000)) {
      trap(0x1800);
    }
    gfxPmxHeightPercentage[i] = scaledHeight / maxPmxHeight;
  }

  for (int level = 0; level < 2; ++level) {
    CVECTOR back = Hrz_gTrackSpec->backColor[level];
    CVECTOR front = Hrz_gTrackSpec->frontColor[level];
    int dr = (int)back.r - (int)front.r;
    int dg = (int)back.g - (int)front.g;
    int db = (int)back.b - (int)front.b;
    if (dr < 0) dr += 7;
    if (dg < 0) dg += 7;
    if (db < 0) db += 7;
    dr >>= 3;
    dg >>= 3;
    db >>= 3;
    for (int row = 0; row < 0x10; ++row) {
      int step = row;
      if (8 < row) step = 0x10 - row;
      gHrzRingColor[level][row].r = front.r + (char)dr * (char)step;
      gHrzRingColor[level][row].g = front.g + (char)dg * (char)step;
      gHrzRingColor[level][row].b = front.b + (char)db * (char)step;
    }
    gHrzRingColor[level][0x10] = gHrzRingColor[level][0];
  }
  Hrz_InitSky();
  Hrz_gSaveCol[1] = Sky_gTrackSpec->frontcolors[0];
  return;
}

/* ---- Hrz_GetHorizonPixMap__FP12Draw_tPixMap  [HRZSKU.CPP:419-428] SLD-VERIFIED ---- */
void Hrz_GetHorizonPixMap(Draw_tPixMap *p)

{
  for (int i = 0; i < 12; ++i)
    gHorizonPixmap[i] = p + i;
  for (int i = 0; i < 4; ++i) {
    Texture_CloneUVPmx(gHorizonPixmap[8 + i],0,&gHorizonExtraSkyPixmaps[i]);
    gHorizonPixmap[12 + i] = &gHorizonExtraSkyPixmaps[i];
  }
  return;
}

/* ---- Hrz_InitHorizon__Fv  [HRZSKU.CPP:432-443] SLD-VERIFIED ---- */
extern "C" void Hrz_InitHorizon(void)

{
  Hrz_gTrackSpec = &TrackSpec_gSpec.horizonspec;
  Sky_gTrackSpec = &TrackSpec_gSpec.skyspec;
  gRngCoordTop = (SVECTOR *)reservememadr("gRngCoordTop",0x88,0);
  Hrz_Init2DRing();
  if ((TrackSpec_gSpec.skyspec.flags & 0x10U) != 0) {
    Sky_InitStars();
  }
  return;
}

/* ---- Hrz_KillHorizon__Fv  [HRZSKU.CPP:447-450] SLD-VERIFIED ---- */
extern "C" void Hrz_KillHorizon(void)

{
  purgememadr(gRngCoordTop);
  Sky_KillStars();
  return;
}

/* ---- Hrz_LightningAddFork__FScScSc  [HRZSKU.CPP:783-822] SLD-VERIFIED ---- */
void Hrz_LightningAddFork(char direction,char column,char row)

{
  u_char bVar1;
  int iVar2;
  u_int uVar3;
  u_int uVar4;
  char type;
  u_int uVar5;
  tHrz_LightningFork *fork;
  u_int uVar6;
  
  uVar5 = (u_int)(u_char)column;
  uVar3 = (u_int)(u_char)direction;
  if (row == '\0') {
    uVar6 = 3;
  }
  else {
    uVar6 = 2;
    if (row < '\x03') {
      uVar6 = random();
      uVar6 = uVar6 % 3;
    }
  }
  uVar4 = (u_int)(u_char)gHrz_Lightning.numForks;
  gHrz_Lightning.numForks = gHrz_Lightning.numForks + '\x01';
  gHrz_Lightning.forks[uVar4].pos.vx = column * 0xf;
  gHrz_Lightning.forks[uVar4].pos.vy = row * 0xf;
  if (uVar6 == 1) {
    Hrz_LightningAddFork(-1,(char)((uVar5 - 1) * 0x1000000 >> 0x18),row + '\x01');
    Hrz_LightningAddFork('\x01',(char)((uVar5 + 1) * 0x1000000 >> 0x18),row + '\x01');
    bVar1 = 6;
  }
  else if (uVar6 < 2) {
    if (uVar6 != 0) {
      iVar2 = uVar3 << 0x18;
      goto HrzLightFork_setPmxIdx;
    }
    Hrz_LightningAddFork(direction,(char)((uVar5 + uVar3) * 0x1000000 >> 0x18),row + '\x01');
    iVar2 = random();
    bVar1 = ((u_char)iVar2 & 1) + 2;
  }
  else if (uVar6 == 2) {
    iVar2 = random();
    bVar1 = ((u_char)iVar2 & 1) + 4;
  }
  else {
    iVar2 = uVar3 << 0x18;
    if (uVar6 != 3) goto HrzLightFork_setPmxIdx;
    uVar3 = random();
    uVar3 = (uVar3 & 1) * -2 + 1;
    Hrz_LightningAddFork((char)(uVar3 * 0x1000000 >> 0x18),(char)((uVar5 + uVar3) * 0x1000000 >> 0x18),
               row + '\x01');
    iVar2 = random();
    bVar1 = (u_char)iVar2 & 1;
  }
  gHrz_Lightning.forks[uVar4].pmxIndex = bVar1;
  iVar2 = uVar3 << 0x18;
HrzLightFork_setPmxIdx:
  if (iVar2 < 0) {
    gHrz_Lightning.forks[uVar4].pmxIndex = gHrz_Lightning.forks[uVar4].pmxIndex + '\b';
  }
  return;
}

/* ---- Hrz_CalculateLightning__Fv  [HRZSKU.CPP:826-829] SLD-VERIFIED ---- */
void Hrz_CalculateLightning(void)

{
  gHrz_Lightning.numForks = '\0';
  gHrz_Lightning.brightness = 200;
  Hrz_LightningAddFork('\x01','\0','\0');
  return;
}

/* ---- Hrz_TextureQuad__FP7DVECTORccP11Draw_DCache  [HRZSKU.CPP:833-856] SLD-VERIFIED ---- */
void Hrz_TextureQuad(DVECTOR *pt,char type,char bright,Draw_DCache *sd)

{
  int pkt_addr24;
  POLY_FT4 *prim;
  u_char *prev_pkt;
  Draw_tPixMap *pixmap;
  
  prim = (POLY_FT4 *)Render_gPacketPtr;
  prev_pkt = (u_char *)Render_gPalettePtr;
#ifdef AP_WIN
  AddPrim(Render_gPalettePtr + sd->otz * 4,Render_gPacketPtr);
  Render_gPacketPtr = Render_gPacketPtr + 0x28;
#else
  *(u_int *)Render_gPacketPtr =
       *(u_int *)Render_gPacketPtr & 0xff000000 |
       *(u_int *)(Render_gPalettePtr + sd->otz * 4) & 0xffffff;
  pkt_addr24 = (u_int)Render_gPacketPtr & 0xffffff;
  Render_gPacketPtr = Render_gPacketPtr + 0x28;
  *(u_int *)(prev_pkt + sd->otz * 4) = *(u_int *)(prev_pkt + sd->otz * 4) & 0xff000000 | pkt_addr24;
#endif
  ((u_char *)&prim->tag)[3] = 9;
  prim->code = 0x2e;
  prim->r0 = bright;
  prim->g0 = bright;
  prim->b0 = bright;
  prim->x0 = pt->vx;
  prim->y0 = pt->vy;
  prim->x2 = pt->vx;
  prim->y2 = pt->vy + 0x10;
  prim->x1 = pt->vx + 0x10;
  prim->y1 = pt->vy;
  prim->x3 = pt->vx + 0x10;
  prim->y3 = pt->vy + 0x10;
  pixmap = gLightningPixmap[(u_char)type];
  *(u_int *)&prim->u0 = ((u_int *)pixmap)[0];
  *(u_int *)&prim->u1 = ((u_int *)pixmap)[1];
  *(u_int *)&prim->u2 = ((u_int *)pixmap)[2];
  *(u_int *)&prim->u3 = ((u_int *)pixmap)[3];
  return;
}

/* ---- Hrz_SetLightingPosInSky__FP13DRender_tView  [HRZSKU.CPP:862-867] SLD-VERIFIED ---- */
void Hrz_SetLightingPosInSky(DRender_tView *Vi)

{
  u_int uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  coorddef forwardVec;
  
  iVar2 = (Vi->cview).mrotation.m[6];
  iVar3 = (Vi->cview).mrotation.m[7];
  iVar4 = (Vi->cview).mrotation.m[8];
  uVar1 = random();
  Hrz_gLightningPosInSky.vx =
       (short)(iVar2 >> 2) + (short)uVar1 + (short)(uVar1 / 8000) * -8000 + -4000;
  uVar1 = random();
  Hrz_gLightningPosInSky.vy =
       (short)(iVar3 >> 2) + 8000 + (short)uVar1 + (short)(uVar1 / 3000) * -3000;
  uVar1 = random();
  Hrz_gLightningPosInSky.vz =
       (short)(iVar4 >> 2) + (short)uVar1 + (short)(uVar1 / 8000) * -8000 + -4000;
  return;
}

/* ---- Hrz_BuildForkLightning__FP11Draw_DCache  [HRZSKU.CPP:872-898] SLD-VERIFIED ---- */
void Hrz_BuildForkLightning(Draw_DCache *sd)

{
  tHrz_LightningFork *fork;
  char i;
  u_char bVar1;
  u_char bVar2;
  DVECTOR pos;
  DVECTOR screenPos;
  coorddef trans;
  
  if (0 < gHrz_Lightning.brightness) {
    sd->otz = Draw_gViewOtSize + -2;
    memset(&trans,0,0xc);
    HrzSetPsxTranslation(&trans);
    gte_lwc2(0,((int *)&Hrz_gLightningPosInSky)[0]);
    gte_lwc2(1,((int *)&Hrz_gLightningPosInSky)[1]);
    gte_rtps();
    gte_swc2(0xe,&screenPos);
    bVar1 = 0;
    if (gHrz_Lightning.numForks != '\0') {
      do {
        bVar2 = bVar1 + 1;
        pos.vx = gHrz_Lightning.forks[bVar1].pos.vx + screenPos.vx;
        pos.vy = gHrz_Lightning.forks[bVar1].pos.vy + screenPos.vy;
        Hrz_TextureQuad(&pos,gHrz_Lightning.forks[bVar1].pmxIndex,(char)gHrz_Lightning.brightness,sd);
        bVar1 = bVar2;
      } while (bVar2 < (u_char)gHrz_Lightning.numForks);
    }
    gHrz_Lightning.brightness = gHrz_Lightning.brightness + -0x10;
  }
  return;
}

/* ---- Hrz_LightningFlicker__Fi  [HRZSKU.CPP:901-954] SLD-VERIFIED ---- */
void Hrz_LightningFlicker(int on)

{
  CSkySpec *pCVar1;
  CVECTOR *pCVar2;
  int i;
  int iVar3;
  
  if (on == 0) {
    Sky_gTrackSpec->frontcolors[0] = Hrz_gSaveCol[1];
    Hrz_InitSkyColor();
  }
  else {
    pCVar1 = Sky_gTrackSpec;
    if (on == 1) {
      if (Night_gShowForks == '\0') {
        iVar3 = 0x54;
        pCVar2 = gSkyColor + 0x54;
        pCVar1->frontcolors[0].r = 0xc0;
        pCVar1->frontcolors[0].g = 0xc0;
        pCVar1->frontcolors[0].b = 0xff;
        pCVar1->frontcolors[0].cd = '\0';
        do {
          pCVar2->r = 0xc0;
          pCVar2->g = 0xc0;
          pCVar2->b = 0xff;
          pCVar2->cd = '\0';
          iVar3 = iVar3 + -1;
          pCVar2 = pCVar2 + -1;
        } while (-1 < iVar3);
      }
    }
    else if (Night_gShowForks == '\0') {
      iVar3 = 0x54;
      pCVar2 = gSkyColor + 0x54;
      pCVar1->frontcolors[0].r = '(';
      pCVar1->frontcolors[0].g = '(';
      pCVar1->frontcolors[0].b = 0xc0;
      pCVar1->frontcolors[0].cd = '\0';
      do {
        pCVar2->r = '(';
        pCVar2->g = '(';
        pCVar2->b = 0xc0;
        pCVar2->cd = '\0';
        iVar3 = iVar3 + -1;
        pCVar2 = pCVar2 + -1;
      } while (-1 < iVar3);
    }
  }
  return;
}

/* ---- HrzSetPsxMatrix__FP10matrixtdef  [HRZSKU.CPP:982-1017] SLD-VERIFIED ---- */
void HrzSetPsxMatrix(matrixtdef *m)
{
  int r2, r0, r1, t2, t1, t3;
  MATRIX mpsx;
  matrixtdef temp;
  int *mm = (int *)m;

  mpsx.m[0][0] = (short)(mm[0] >> 4);
  mpsx.m[0][1] = (short)(mm[3] >> 4);
  mpsx.m[0][2] = (short)(mm[6] >> 4);
  mpsx.m[1][0] = (short)(-mm[1] >> 4);
  mpsx.m[1][1] = (short)(-mm[4] >> 4);
  mpsx.m[1][2] = (short)(-mm[7] >> 4);
  mpsx.m[2][0] = (short)(mm[2] >> 4);
  mpsx.m[2][1] = (short)(mm[5] >> 4);
  mpsx.m[2][2] = (short)(mm[8] >> 4);
  gte_SetRotMatrix(&mpsx);
}

/* ---- HrzSetPsxTranslation__FP8coorddef  [HRZSKU.CPP:1021-1028] SLD-VERIFIED ---- */
void HrzSetPsxTranslation(coorddef *t)
{
  MATRIX mpsx;
  int *tt = (int *)t;

  mpsx.t[0] = tt[0] >> 10;
  mpsx.t[1] = tt[1] >> 10;
  mpsx.t[2] = tt[2] >> 10;
  gte_SetTransMatrix(&mpsx);
}

/* ---- Hrz_RotProj16__FiP7SVECTORPiP7DVECTOR  [HRZSKU.CPP:1032-1045] SLD-VERIFIED ---- */
void Hrz_RotProj16(int n, SVECTOR *s, int *z, DVECTOR *p)
{
  int i;

  if (n != 0) {
    i = n - 1;
    do {
      gte_lwc2(0, ((int *)s)[0]);   /* load vx,vy */
      gte_lwc2(1, ((int *)s)[1]);   /* load vz,pad */
      gte_rtps();                   /* rotate / transform / perspective */
      s = s + 1;
      gte_swc2(0xe, p);             /* store screen XY -> DVECTOR */
      p = p + 1;
      gte_swc2(0x1b, z);            /* store screen Z -> int */
      i = i - 1;
      z = z + 1;
    } while (i != -1);
  }
}

/* ---- Hrz_SetDitheringPrim__Fii  [HRZSKU.CPP:1050-1055] SLD-VERIFIED ---- */
void Hrz_SetDitheringPrim(int dither,int otz)

{
  DR_MODE *prim;
  u_int *prev_pkt_slot;
  int pkt_addr24;
  int loc_10;
  int loc_8;
  u_char *p;
  
  p = (u_char *)Render_gPacketPtr;
  prev_pkt_slot = (u_int *)(Render_gPalettePtr + otz * 4);
#ifdef AP_WIN
  AddPrim(prev_pkt_slot,Render_gPacketPtr);
  Render_gPacketPtr = Render_gPacketPtr + 0xc;
#else
  *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *prev_pkt_slot & 0xffffff;
  pkt_addr24 = (u_int)Render_gPacketPtr & 0xffffff;
  Render_gPacketPtr = Render_gPacketPtr + 0xc;
  *prev_pkt_slot = *prev_pkt_slot & 0xff000000 | pkt_addr24;
#endif
  SetDrawMode((DR_MODE *)p,0,dither,0x100,(PSX_RECT *)0x0);
  return;
}

/* ---- Hrz_BuildSky__Fv  [HRZSKU.CPP:1060-1277] SLD-VERIFIED ---- */
void Hrz_BuildSky(void)
{
  coorddef trans;
  VECTOR transformed;
  Draw_DCache *sd;
  DVECTOR *pSkyMesh;
  int *pSkyZ;
  DVECTOR *scnt;
  SVECTOR *pcnt;
  int *zcnt;
  int n, otz_old, pshift, i, temp;
  POLY_GT4 *prim;
  Draw_tPixMap *pmx;
  int ti1, ti2, skyColIdx, skyRowIdx, tu7;
  u_char *skyMesh_iter;
  u_char *tp2, *tp3;
  CSkySpec *tC4;
  CVECTOR CVar3;
  sd = (Draw_DCache *)getScratchAddr(0);
  pSkyMesh = (DVECTOR *)((char *)sd + 0x14);
  pSkyZ = (int *)((char *)sd + 0x168);
  otz_old = 0x78;
  if (GameSetup_gData.commMode == 1) {
    otz_old = 0x3c;
  }
  pshift = otz_old;
  if ((Sky_gTrackSpec->flags & 1U) != 0) {
    /* RTPT fast path: 3 vertices per pass (0x55 total) + RTPS tail. */
    memset(&trans,0,0xc);
    HrzSetPsxTranslation(&trans);
    pcnt = (SVECTOR *)&gSkyMesh /* @0x80120378 */;
    n = 0x55;
    scnt = (DVECTOR *)((char *)sd + 8);
    zcnt = (int *)((char *)sd + 0x15c);
    do {
      gte_lwc2(0,((int *)pcnt)[0]);
      gte_lwc2(1,((int *)pcnt)[1]);
      gte_lwc2(2,((int *)pcnt)[2]);
      gte_lwc2(3,((int *)pcnt)[3]);
      gte_lwc2(4,((int *)pcnt)[4]);
      gte_lwc2(5,((int *)pcnt)[5]);
      gte_rtpt();
      pcnt = pcnt + 3;
      n = n + -3;
      scnt = scnt + 3;
      zcnt = zcnt + 3;
      gte_swc2(0xc,&scnt[0]);
      gte_swc2(0xd,&scnt[1]);
      gte_swc2(0xe,&scnt[2]);
      gte_swc2(0x11,&zcnt[0]);
      gte_swc2(0x12,&zcnt[1]);
      gte_swc2(0x13,&zcnt[2]);
    } while (2 < n);
    scnt = &scnt[2];
    n = n + -1;
    zcnt = &zcnt[2];
    if (n != -1) {
      do {
        gte_lwc2(0,((int *)pcnt)[0]);
        gte_lwc2(1,((int *)pcnt)[1]);
        gte_rtps();
        pcnt = pcnt + 1;
        scnt = scnt + 1;
        zcnt = zcnt + 1;
        gte_swc2(0xe,scnt);
        gte_swc2(0x13,zcnt);
        n = n + -1;
      } while (n != -1);
    }
  }
  else {
    /* RTPS path: 1 vertex per pass (0x54 total), screen row pinned at otz_old. */
    memset(&trans,0,0xc);
    HrzSetPsxTranslation(&trans);
    pcnt = (SVECTOR *)&gSkyMesh /* @0x80120378 */;
    scnt = pSkyMesh + -1;
    zcnt = pSkyZ + -1;
    n = 0x54;
    do {
      gte_lwc2(0,((int *)pcnt)[0]);
      gte_lwc2(1,((int *)pcnt)[1]);
      gte_rtps();
      pcnt = pcnt + 1;
      scnt = scnt + 1;
      zcnt = zcnt + 1;
      gte_swc2(0x19,&transformed.vx);
      gte_swc2(0x1a,&transformed.vy);
      gte_swc2(0x1b,&transformed.vz);
      gte_swc2(0xe,scnt);
      scnt->vy = (short)nfs4_mips_sign_extend(
          (unsigned int)nfs4_mips_addu_s32(
              nfs4_mips_sra_s32(transformed.vy, 2), otz_old),
          16);
      gte_swc2(0x13,zcnt);
      n = n + -1;
    } while (n != -1);
  }
#ifdef AP_WIN
  NFSHS_DIAGNOSTIC_CALL(NFSHS_HostTraceSkyProjection(sd));
#endif
  if ((Sky_gTrackSpec->flags & 0x40U) != 0) {
    Hrz_SetDitheringPrim(0,Draw_gViewOtSize + -2);
  }
  ti1 = sd->otz;
  if ((TrackSpec_gSpec.skyspec.flags & 4U) != 0) {
    Flare_Sun(&sunPosInSky,(Draw_FlareCache *)sd);
  }
  i = 0;
  skyMesh_iter = (u_char *)gSkyPixmapIndex;
  sd->otz = ti1;
  do {
    tC4 = Sky_gTrackSpec;
    ti1 = Draw_gViewOtSize;
    tp2 = (u_char *)Render_gPacketPtr;
    tp3 = (u_char *)Render_gPalettePtr;
    prim = (POLY_GT4 *)tp2;
    if (0x3f < i) {
      if ((Sky_gTrackSpec->flags & 0x40U) != 0) {
        Hrz_SetDitheringPrim(1,Draw_gViewOtSize + -2);
      }
      return;
    }
    ti2 = i * 0x11;
    if (ti2 < 0) {
      ti2 = ti2 + 0xf;
    }
    temp = ti2 >> 4;
    if (pSkyZ[temp] != 0 || pSkyZ[temp + 1] != 0 ||
        pSkyZ[temp + 17] != 0 || pSkyZ[temp + 18] != 0) {
      if (((pSkyMesh[temp].vx <= (short)Render_gPacketLenLo) ||
           (pSkyMesh[temp + 1].vx <= (short)Render_gPacketLenLo) ||
           (pSkyMesh[temp + 17].vx <= (short)Render_gPacketLenLo) ||
           (pSkyMesh[temp + 18].vx <= (short)Render_gPacketLenLo)) &&
          ((pSkyMesh[temp].vx >= 0) || (pSkyMesh[temp + 1].vx >= 0) ||
           (pSkyMesh[temp + 17].vx >= 0) || (pSkyMesh[temp + 18].vx >= 0)) &&
          ((pSkyMesh[temp].vy <= (short)Render_gPacketLenHi) ||
           (pSkyMesh[temp + 1].vy <= (short)Render_gPacketLenHi) ||
           (pSkyMesh[temp + 17].vy <= (short)Render_gPacketLenHi) ||
           (pSkyMesh[temp + 18].vy <= (short)Render_gPacketLenHi)) &&
          ((pSkyMesh[temp].vy >= 0) || (pSkyMesh[temp + 1].vy >= 0) ||
           (pSkyMesh[temp + 17].vy >= 0) || (pSkyMesh[temp + 18].vy >= 0))) {
        {
          if (Sky_gTrackSpec->type == 1) {
            if ((Sky_gTrackSpec->flags & 0x20U) != 0) {
              pmx = gHorizonPixmap[*skyMesh_iter];
              if (pmx == (Draw_tPixMap *)0x0) goto HrzBuildSky_meshIterNext;
#ifdef AP_WIN
              AddPrim(Render_gPalettePtr + Draw_gViewOtSize * 4 - 8,
                                Render_gPacketPtr);
#else
              *(u_int *)Render_gPacketPtr =
                   *(u_int *)Render_gPacketPtr & 0xff000000 |
                   *(u_int *)(Render_gPalettePtr + Draw_gViewOtSize * 4 + -8) & 0xffffff;
              *(u_int *)(tp3 + ti1 * 4 + -8) =
                   *(u_int *)(tp3 + ti1 * 4 + -8) & 0xff000000 | (u_int)Render_gPacketPtr & 0xffffff;
#endif
              Render_gPacketPtr = Render_gPacketPtr + 0x34;
              *(CVECTOR *)(tp2 + 4) = gSkyColor[temp + 0x11];
              *(CVECTOR *)(tp2 + 0x10) = gSkyColor[temp + 0x12];
              *(CVECTOR *)(tp2 + 0x1c) = gSkyColor[temp];
              tp2[3] = 0xc;
              tp2[7] = 0x3c;
              *(CVECTOR *)(tp2 + 0x28) = gSkyColor[temp + 1];
              *(u_int *)(tp2 + 0xc) = ((u_int *)pmx)[0];
              *(u_int *)(tp2 + 0x18) = ((u_int *)pmx)[1];
              *(u_int *)(tp2 + 0x24) = ((u_int *)pmx)[2];
              *(u_int *)(tp2 + 0x30) = ((u_int *)pmx)[3];
              *(DVECTOR *)(tp2 + 8) = pSkyMesh[temp + 17];
              *(DVECTOR *)(tp2 + 0x14) = pSkyMesh[temp + 18];
              *(DVECTOR *)(tp2 + 0x20) = pSkyMesh[temp];
              *(DVECTOR *)(tp2 + 0x2c) = pSkyMesh[temp + 1];
              goto HrzBuildSky_meshIterNext;
            }
            pmx = gHorizonPixmap[*skyMesh_iter];
            if (pmx == (Draw_tPixMap *)0x0) goto HrzBuildSky_meshIterNext;
#ifdef AP_WIN
            AddPrim(Render_gPalettePtr + Draw_gViewOtSize * 4 - 8,
                              Render_gPacketPtr);
            Render_gPacketPtr = Render_gPacketPtr + 0x28;
#else
            *(u_int *)Render_gPacketPtr =
                 *(u_int *)Render_gPacketPtr & 0xff000000 |
                 *(u_int *)(Render_gPalettePtr + Draw_gViewOtSize * 4 + -8) & 0xffffff;
            tu7 = (u_int)Render_gPacketPtr & 0xffffff;
            Render_gPacketPtr = Render_gPacketPtr + 0x28;
            *(u_int *)(tp3 + ti1 * 4 + -8) = *(u_int *)(tp3 + ti1 * 4 + -8) & 0xff000000 | tu7;
#endif
            tp2[3] = 9;
            *(CVECTOR *)(tp2 + 4) = tC4->frontcolors[0];
            tp2[7] = 0x2c;
            *(u_int *)(tp2 + 0xc) = ((u_int *)pmx)[0];
            *(u_int *)(tp2 + 0x14) = ((u_int *)pmx)[1];
            *(u_int *)(tp2 + 0x1c) = ((u_int *)pmx)[2];
            *(u_int *)(tp2 + 0x24) = ((u_int *)pmx)[3];
          }
          else {
#ifdef AP_WIN
            AddPrim(Render_gPalettePtr + Draw_gViewOtSize * 4 - 8,
                              Render_gPacketPtr);
#else
            *(u_int *)Render_gPacketPtr =
                 *(u_int *)Render_gPacketPtr & 0xff000000 |
                 *(u_int *)(Render_gPalettePtr + Draw_gViewOtSize * 4 + -8) & 0xffffff;
            *(u_int *)(tp3 + ti1 * 4 + -8) =
                 *(u_int *)(tp3 + ti1 * 4 + -8) & 0xff000000 | (u_int)Render_gPacketPtr & 0xffffff;
#endif
            Render_gPacketPtr = Render_gPacketPtr + 0x24;
            *(CVECTOR *)(tp2 + 4) = gSkyColor[temp + 0x11];
            *(CVECTOR *)(tp2 + 0xc) = gSkyColor[temp + 0x12];
            *(CVECTOR *)(tp2 + 0x14) = gSkyColor[temp];
            CVar3 = gSkyColor[temp + 1];
            tp2[3] = 8;
            tp2[7] = 0x38;
            *(CVECTOR *)(tp2 + 0x1c) = CVar3;
          }
          *(DVECTOR *)(tp2 + 8) = pSkyMesh[temp + 17];
          *(DVECTOR *)(tp2 + 0x10) = pSkyMesh[temp + 18];
          *(DVECTOR *)(tp2 + 0x18) = pSkyMesh[temp];
          *(DVECTOR *)(tp2 + 0x20) = pSkyMesh[temp + 1];
        }
      }
    }
HrzBuildSky_meshIterNext:
    skyMesh_iter = skyMesh_iter + 1;
    i = i + 1;
  } while( true );
}

/* ---- Sky_RenderStars__FP13Draw_SkyCachei  [HRZSKU.CPP:1284-1330] SLD-VERIFIED ---- */
void Sky_RenderStars(Draw_SkyCache *sd,int otz)

{
  int iVar1;
  u_int uVar2;
  u_long uVar3;
  u_int *packetWords;
  TILE_1 *prim;
  u_int *puVar5;
  int n;
  int iVar6;
  u_int uVar7;
  u_int uVar8;
  SVECTOR *pcnt;
  int pshift;
  int iVar9;
  coorddef trans;
  DVECTOR scnt;
  VECTOR transformed;
  int zcnt;
  
  iVar9 = 0x78;
  if (GameSetup_gData.commMode == 1) {
    iVar9 = 0x3c;
  }
  memset(&trans,0,0xc);
  HrzSetPsxTranslation(&trans);
  iVar6 = 0;
  if (0 < Sky_gTrackSpec->numStars) {
    pcnt = starPosInSky;
    uVar7 = 0xffffff;
    uVar8 = 0xff000000;
    do {
      gte_lwc2(0,((int *)pcnt)[0]);
      gte_lwc2(1,((int *)pcnt)[1]);
      gte_rtps();
      pcnt = pcnt + 1;
      gte_swc2(0x13,&zcnt);
      if (0 < zcnt) {
        gte_swc2(0xe,&scnt);
        gte_swc2(0x19,&transformed.vx);
        gte_swc2(0x1a,&transformed.vy);
        gte_swc2(0x1b,&transformed.vz);
        iVar1 = (transformed.vy >> 2) + iVar9;
        scnt.vy = (short)iVar1;
        if ((((scnt.vx <= (sd->head).clipW) && (-1 < scnt.vx)) &&
            (iVar1 = iVar1 * 0x10000 >> 0x10, iVar1 <= (sd->head).clipH)) && (-1 < iVar1)) {
          packetWords = (u_int *)Render_gPacketPtr;
          prim = (TILE_1 *)Render_gPacketPtr;
          puVar5 = (u_int *)(Render_gPalettePtr + otz * 4);
#ifdef AP_WIN
          AddPrim(puVar5,packetWords);
          Render_gPacketPtr = Render_gPacketPtr + sizeof(TILE_1);
#else
          *packetWords = *packetWords & uVar8 | *puVar5 & uVar7;
          uVar2 = *puVar5;
          Render_gPacketPtr = Render_gPacketPtr + sizeof(TILE_1);
          *puVar5 = uVar2 & uVar8 | (u_int)packetWords & uVar7;
#endif
          uVar3 = (*(u_long *)&starColors[iVar6]);
          ((u_char *)&prim->tag)[3] = 2;
          *(u_long *)&prim->r0 = uVar3;
          prim->code = 0x68;
          prim->x0 = scnt.vx;
          prim->y0 = scnt.vy;
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < Sky_gTrackSpec->numStars);
  }
  return;
}

/* ---- Hrz_BuildHorizon__FP13DRender_tView  [HRZSKU.CPP:1338-1557] SLD-VERIFIED ---- */
void Hrz_BuildHorizon(DRender_tView *Vi)

{
  u_int *puVar1;
  u_int uVar2;
  u_int uVar3;
  u_int uVar4;
  u_char *puVar5;
  u_char *p;
  POLY_GT4 *prim;
  int iVar6;
  DVECTOR DVar7;
  int iVar8;
  int iVar9;
  u_int auVar10;
  short shape_short;
  int r2;
  int r0;
  int *zval;
  SVECTOR *pSVar12;
  int dx;
  int Zmax;
  SVECTOR *pcnt;
  int shape_visible;
  int shape_idx;
  int rowDelta;
  int shape_overlap;
  int shape_w_idx;
  int farIdx;
  int farI;
  int t1;
  DVECTOR *pDVar13;
  int t3;
  Draw_tPixMap *pmx;
  u_int *puVar14;
  int height;
  int iVar15;
  int latAngle;
  int iVar16;
  int i;
  int iVar17;
  int oldSeed;
  int iVar18;
  Draw_HorizonCache *hsd;
  int loc_70;
  int loc_6c;
  coorddef trans;
  coorddef trans2;
  u_int auStack_4c;
  DVECTOR right;
  SVECTOR p_;
  DVECTOR DStack_38;
  int fxOverlapPercentage;
  long hrz_projchange;
  VECTOR transformed;
  SVECTOR updown [2];
  DVECTOR temp2d [2];
  DVECTOR mpts [4];
  long s_;
  void *tp1;
  short ts3;
  int tp2;
  int tu5;
  short ts4;
  int tp6;
  int tu8;
  short tu7;
  int tp9;
  void *tp3;
  short tu6;
  short ts5;
  u_int *tp10;
  u_char *tp4;
  u_int tu9;
  hsd = (Draw_HorizonCache *)getScratchAddr(0);
  
  fxOverlapPercentage = 0x107ae;
  memset(&trans,0,sizeof(trans));
  hrz_projchange = 0;
  if (700 < Camera_gGeomScreen[0]) {
    hrz_projchange = Camera_gGeomScreen[0];
    SetGeomScreen(700);
  }
  HrzSetPsxMatrix(&(Vi->cview).mrotationInv);
  HrzSetPsxTranslation(&trans);
  Hrz_RotProj16(0x11,gRngCoordTop,hsd->vertexTop,hsd->scptMidBot);
  farI = 0;
  Zmax = 0;
  zval = hsd->vertexTop;
  rowDelta = 0;
  do {
    if (Zmax < *zval) {
      Zmax = *zval;
      farI = rowDelta;
    }
    rowDelta = rowDelta + 1;
    zval = zval + 1;
  } while (rowDelta < 0x10);
  pSVar12 = gRngCoordTop + farI;
  updown[0].vx = pSVar12->vx;
  updown[0].vy = (short)nfs4_mips_sign_extend(
      (unsigned int)nfs4_mips_addu_s32(
          nfs4_mips_sign_extend((unsigned int)Hrz_gTrackSpec->yoffset, 16),
          nfs4_mips_sign_extend((unsigned int)Hrz_gTrackSpec->height, 16)),
      16);
  updown[0].vz = pSVar12->vz;
  updown[0].pad = 0;
  updown[1].vx = pSVar12->vx;
  updown[1].vy = (short)Hrz_gTrackSpec->yoffset;
  updown[1].vz = pSVar12->vz;
  updown[1].pad = 0;

  /* Retail computes the lower and upper projections independently.  The old
     decompiler-shaped block reused DStack_38 for both and consequently applied
     one delta twice, stretching most horizon quads across the screen. */
  gte_lwc2(0,((int *)&updown[1])[0]);
  gte_lwc2(1,((int *)&updown[1])[1]);
  gte_rtps();
  gte_swc2(0xe,&temp2d[1]);
  gte_lwc2(0,((int *)&updown[0])[0]);
  gte_lwc2(1,((int *)&updown[0])[1]);
  gte_rtps();
  gte_swc2(0xe,&temp2d[0]);

  {
    int dx = nfs4_mips_subu_s32(temp2d[0].vx,hsd->scptMidBot[farI].vx);
    int ddy = nfs4_mips_subu_s32(temp2d[0].vy,hsd->scptMidBot[farI].vy);
    for(int k=0;k<0x11;k++) if(0 < hsd->vertexTop[k]) {
      hsd->scptTop[k].vx = (short)nfs4_mips_sign_extend(
          (unsigned int)nfs4_mips_addu_s32(hsd->scptMidBot[k].vx,dx),16);
      hsd->scptTop[k].vy = (short)nfs4_mips_sign_extend(
          (unsigned int)nfs4_mips_addu_s32(hsd->scptMidBot[k].vy,ddy),16);
    }
    dx = nfs4_mips_subu_s32(temp2d[1].vx,hsd->scptMidBot[farI].vx);
    ddy = nfs4_mips_subu_s32(temp2d[1].vy,hsd->scptMidBot[farI].vy);
    for(int k=0;k<0x11;k++) if(0 < hsd->vertexTop[k]) {
      hsd->scptMidBot[k].vx = (short)nfs4_mips_sign_extend(
          (unsigned int)nfs4_mips_addu_s32(hsd->scptMidBot[k].vx,dx),16);
      hsd->scptMidBot[k].vy = (short)nfs4_mips_sign_extend(
          (unsigned int)nfs4_mips_addu_s32(hsd->scptMidBot[k].vy,ddy),16);
    }
  }
  Horizon_InterpolateLineSCoords(hsd->scptPmxLeft,hsd->scptMidBot,
             hsd->scptTop,gfxPmxHeightPercentage,0x10,1);
  Horizon_InterpolateLineSCoords(hsd->scptPmxRight,hsd->scptMidBot + 1,
             hsd->scptTop + 1,gfxPmxHeightPercentage,0x10,1);
#ifdef AP_WIN
  NFSHS_DIAGNOSTIC_CALL(NFSHS_HostTraceHorizonCache(hsd));
#endif
  iVar17 = 0;
  if (TrackSpec_gSpec.horizonstate != 0) {
    for (; iVar17 < 0x10; iVar17 = iVar17 + 1) {
      if ((15999 < hsd->vertexTop[iVar17]) ||
          (15999 < hsd->vertexTop[iVar17 + 1])) {
        nfs4_mips_copy_bytes(&mpts[0],&hsd->scptPmxLeft[iVar17],4);
        nfs4_mips_copy_bytes(&mpts[1],&hsd->scptPmxRight[iVar17],4);
        nfs4_mips_copy_bytes(&mpts[2],&hsd->scptMidBot[iVar17 + 1],4);
        nfs4_mips_copy_bytes(&mpts[3],&hsd->scptMidBot[iVar17],4);

        if ((mpts[0].vx >= 0 || mpts[1].vx >= 0 ||
             mpts[2].vx >= 0 || mpts[3].vx >= 0) &&
            (mpts[0].vx <= hsd->head.clipW ||
             mpts[1].vx <= hsd->head.clipW ||
             mpts[2].vx <= hsd->head.clipW ||
             mpts[3].vx <= hsd->head.clipW) &&
            (mpts[0].vy >= 0 || mpts[1].vy >= 0 ||
             mpts[2].vy >= 0 || mpts[3].vy >= 0) &&
            (mpts[0].vy <= hsd->head.clipH ||
             mpts[1].vy <= hsd->head.clipH ||
             mpts[2].vy <= hsd->head.clipH ||
             mpts[3].vy <= hsd->head.clipH)) {
          Horizon_InterpolateLineSCoords(&right,
                     &hsd->scptPmxLeft[iVar17],
                     &hsd->scptPmxRight[iVar17],
                     &fxOverlapPercentage,1,0);
          p = (u_char *)Render_gPacketPtr;
          prim = (POLY_GT4 *)p;
          pmx = gpPmx[iVar17];
          if (Hrz_gTrackSpec->ringPMX[iVar17] != '\x10') {
#ifdef AP_WIN
            AddPrim(Render_gPalettePtr + Draw_gViewOtSize * 4 - 8,
                              Render_gPacketPtr);
#else
            *(u_int *)Render_gPacketPtr =
                 *(u_int *)Render_gPacketPtr & 0xff000000 |
                 *(u_int *)(Render_gPalettePtr + Draw_gViewOtSize * 4 + -8) & 0xffffff;
            *(u_int *)(Render_gPalettePtr + Draw_gViewOtSize * 4 + -8) =
                 *(u_int *)(Render_gPalettePtr + Draw_gViewOtSize * 4 + -8) & 0xff000000 |
                 (u_int)Render_gPacketPtr & 0xffffff;
#endif
            Render_gPacketPtr = Render_gPacketPtr + 0x34;
            *(u_int *)(p + 4) = *(u_int *)&gHrzRingColor[1][iVar17];
            *(u_int *)(p + 0x10) = *(u_int *)&gHrzRingColor[1][iVar17 + 1];
            *(u_int *)(p + 0x1c) = *(u_int *)&gHrzRingColor[0][iVar17];
            *(u_int *)(p + 0x28) = *(u_int *)&gHrzRingColor[0][iVar17 + 1];
            SetPolyGT4(prim);
            *(u_int *)(p + 0xc) = *(u_int *)pmx;
            *(u_int *)(p + 0x18) = ((u_int *)pmx)[1];
            *(u_int *)(p + 0x24) = ((u_int *)pmx)[2];
            *(u_int *)(p + 0x30) = ((u_int *)pmx)[3];
            if ((u_char)Hrz_gTrackSpec->ringPMX[iVar17] < 8) {
              *(DVECTOR *)(p + 8) = mpts[0];
              *(DVECTOR *)(p + 0x14) = right;
              *(DVECTOR *)(p + 0x20) = mpts[3];
              *(DVECTOR *)(p + 0x2c) = mpts[2];
            }
            else {
              *(DVECTOR *)(p + 8) = right;
              *(DVECTOR *)(p + 0x14) = mpts[0];
              *(DVECTOR *)(p + 0x20) = mpts[2];
              *(DVECTOR *)(p + 0x2c) = mpts[3];
            }
          }
        }
      }
    }
  }
  if ((Night_gLightning != 0) && (Night_gShowForks != '\0')) {
    Hrz_BuildForkLightning((Draw_DCache *)hsd);
  }
  if ((TrackSpec_gSpec.skyspec.flags & 8U) != 0) {
    memset(&trans2,0,0xc);
    HrzSetPsxTranslation(&trans2);
    Flare_Moon(&moonPosInSky,(Draw_FlareCache *)hsd);
  }
  if ((TrackSpec_gSpec.skyspec.flags & 0x10U) != 0) {
    Sky_RenderStars((Draw_SkyCache *)hsd,Draw_gViewOtSize + -2);
  }
  if (TrackSpec_gSpec.skystate != 0) {
    Hrz_BuildSky();
  }
  if (hrz_projchange != 0) {
    SetGeomScreen(hrz_projchange);
  }
  return;
}

/* end of hrzsku.cpp */
