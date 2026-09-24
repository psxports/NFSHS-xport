/* game/psx/draww.cpp -- RECONSTRUCTED (NFS4 PSX world-geometry draw; C++ TU)
 *   35 fns: subdivision facets, world matrix/translation setup, night colour calc, DrawW_DrawQuad,
 *   object/chunk facet builders, object transforms, skidmarks, lines/spike-belt, anim timers, depth cue.
 *   GTE-heavy (142 cop2 stubs -> gte_ intrinsics). Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "draww_externs.h"

#define PSYQ_SCRATCH_BYTES(off) ((void *)getScratchAddr((off) / 4))
#define NFSHS_WORLD_CACHE_AS(type) ((type *)getScratchAddr(0))

/* ---- DrawW.obj-OWNED globals -- DEFINED here (self-contained; SYM-typed via gen_owned_defs:
   .data = real NFS4.EXE bytes, .bss = zero) ---- */
char         offsets[8] = { 125, 125, 50, 15, -1, 125, 0, 0 };   /* @0x8013D828 */
MATRIX       gIdentTemplate = {{{4096,0,0},{0,4096,0},{0,0,4096}},{0,0,0}};   /* @0x8011f570 */
int          trk0[9][2] = { 410, 530, 800, 850, 800, 850, 800, 850, 800, 850, 800, 850, 815, 885, 815, 885, 815, 885 };   /* @0x8011f590 */
int          trk4[10][2] = { 300, 440, 300, 440, 300, 440, 300, 440, 300, 440, 705, 910, 705, 910, 705, 910, 705, 910, 705, 910 };   /* @0x8011f5d8 */
Draw_SubdivStruct gDiv;   /* @0x8011f628  (bss(zero)) */
int          animation_timer[12];   /* @0x8011f718  (bss(zero)) */
ChunkObjectInfo gChunkObjInfo;   /* @0x8011f748  (bss(zero)) */
CCOORD16     gVertex3d[160];   /* @0x8011f760  (bss(zero)) */
extern "C" { int          stackSpeedUpEnbabledFlag; } /* @0x8013d81c  (bss(zero)) */
char         goffsets[8] = { 125, 125, 50, 15, -1, 125, 0, 0 };   /* @0x8013d820 */
intptr     gWSavePtr;   /* @0x8013d830  (bss(zero); native SetSp address) */
int          gSD_gt4counter;   /* @0x8013d834  (bss(zero)) */
int          gSD_gt3counter;   /* @0x8013d838  (bss(zero)) */
DRender_tView *gVi;   /* @0x8013d83c  (bss(zero)) */

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void DrawW_DivVertice(Draw_SVertex *v0,Draw_SVertex *v1,Draw_SVertex *v2);
void DrawW_LoadPrecVECTOR(Draw_SVertex *v,VECTOR *dv);
void DrawW_SetUpSubdividFacet(int face,Draw_tGiveShelbyMoreCache *sd);
void Night_NightCopCalc(VECTOR *v,short *idx);
void Night_NightCalc(VECTOR *v,short *idx,Draw_tGiveShelbyMoreCache *sd);
void DrawW_DrawQuad(Draw_tGiveShelbyMoreCache *sd,Trk_Quad *inQuad);
void DrawW_kCtrlWorld_High(Draw_tGiveShelbyMoreCache *sd);
void DrawW_StripDraw_High(Draw_tGiveShelbyMoreCache *sd);
void DrawW_DoTrough(DRender_tView *Vi,tBuildEntry *buildList);
void DrawW_WorldSetUpMatrix(matrixtdef *m,MATRIX *mat);
void DrawW_WorldSetUpTranslation(coorddef *t,MATRIX *mat);
void DrawW_ResetAnimationTimer(void);
int DrawW_GetAnimationTime(Trk_AnimateInst *animInst);
void DrawW_SetAnimationTime(Trk_AnimateInst *animInst,int *table,int time);
void DrawW_DoObjectAnimations(void);
int DrawW_BuildObjectFacets(DRender_tView *Vi,ChunkObjectInfo *gObjInfo);
int DrawW_BuildCustomObjectFacets(DRender_tView *Vi,Draw_DCache *sd,Trk_SimObject *simObjs,Group *group,int zClipSq);
int DrawObjectSimple(DRender_tView *Vi,Draw_DCache *sd,Trk_ObjectDef *objDef,coorddef *pCp,int offset);
int DrawW_BuildChunkObjectFacets(DRender_tView *Vi,ChunkObjectInfo *gObjInfo);
BOOL ObjectClipped(DRender_tView *Vi,int ind,coorddef *pCp,Draw_tGiveShelbyMoreCache *sd);
void DrawW_DoObjects(DRender_tView *Vi,tBuildEntry *buildList);
int Draw_CircleClip(coorddef *pt1,coorddef *pt2,int r);
void Draw_kCtrlSkidmark(Draw_tCtrlSkidmark *fskid);
void DrawW_SetUpSubdividFacet_Line(Draw_tGiveShelbyMoreCache *sd);
void DrawW_OnyxLinePrim(CCOORD16 *geomVertices,Trk_Line *lineQuad,int count,Draw_tGiveShelbyMoreCache *sd);
void DrawW_BuildChunkCenterLineFacets(Chunk *chunkDat,Group *group,Draw_tGiveShelbyMoreCache *sd,COORD16 *trans);
void DrawW_DoLines(DRender_tView *Vi,tBuildEntry *buildList,Draw_DCache *sd);
void DrawW_BuildSpikeBelt(DRender_tView *Vi,int scale,Draw_DCache *sd);
void DepthCue_Init(void);


/* ---- DrawW_AddSubdividPrimGT4__FP8POLY_GT4P12Draw_SVertexN31P25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:235-282] SLD-VERIFIED ---- */
void DrawW_AddSubdividPrimGT4(POLY_GT4 *prim,Draw_SVertex *v0,Draw_SVertex *v1,Draw_SVertex *v2,Draw_SVertex *v3,
               Draw_tGiveShelbyMoreCache *sd)

{
  u_short uVar1;
  u_short uVar2;
  u_char uVar3;
  u_char uVar4;
  u_char uVar5;
  u_char uVar6;
  u_char uVar7;
  u_char uVar8;
  u_char uVar9;
  u_char uVar10;
  u_char uVar11;
  u_char uVar12;
  u_char uVar13;
  u_char uVar14;
  u_char uVar15;
  u_char uVar16;
  u_char uVar17;
  short sVar18;
  short sVar19;
  short sVar20;
  short sVar21;
  short sVar22;
  short sVar23;
  short sVar24;
  u_char a;
  u_short b;
  long c;
  long d;
  
  ((u_char *)&prim->tag)[3] = 0xc;
  uVar3 = v0->g;
  uVar4 = v0->b;
  uVar5 = v0->a;
  uVar6 = v1->r;
  uVar7 = v1->g;
  uVar8 = v1->b;
  uVar9 = v1->a;
  uVar10 = v2->r;
  uVar11 = v2->g;
  uVar12 = v2->b;
  uVar13 = v2->a;
  uVar14 = v3->r;
  uVar15 = v3->g;
  uVar16 = v3->b;
  uVar17 = v3->a;
  prim->r0 = v0->r;
  prim->g0 = uVar3;
  prim->b0 = uVar4;
  prim->code = uVar5;
  prim->r1 = uVar6;
  prim->g1 = uVar7;
  prim->b1 = uVar8;
  prim->p1 = uVar9;
  prim->r3 = uVar10;
  prim->g3 = uVar11;
  prim->b3 = uVar12;
  prim->p3 = uVar13;
  prim->r2 = uVar14;
  prim->g2 = uVar15;
  prim->b2 = uVar16;
  prim->p2 = uVar17;
  sVar18 = v0->dvy;
  sVar19 = v1->dvx;
  sVar20 = v1->dvy;
  sVar21 = v2->dvx;
  sVar22 = v2->dvy;
  sVar23 = v3->dvx;
  sVar24 = v3->dvy;
  prim->x0 = v0->dvx;
  prim->y0 = sVar18;
  prim->x1 = sVar19;
  prim->y1 = sVar20;
  prim->x3 = sVar21;
  prim->y3 = sVar22;
  prim->x2 = sVar23;
  prim->y2 = sVar24;
  uVar3 = v0->v;
  uVar4 = v1->u;
  uVar5 = v1->v;
  uVar6 = v2->u;
  uVar7 = v2->v;
  uVar8 = v3->u;
  uVar9 = v3->v;
  prim->u0 = v0->u;
  prim->v0 = uVar3;
  prim->u1 = uVar4;
  prim->v1 = uVar5;
  prim->u3 = uVar6;
  prim->v3 = uVar7;
  prim->u2 = uVar8;
  prim->v2 = uVar9;
  uVar1 = (sd->GT4Prim).tpage;
  uVar2 = (sd->GT4Prim).clut;
  prim->code = (sd->GT4Prim).code;
  prim->tpage = uVar1;
  prim->clut = uVar2;
  return;
}

/* ---- DrawW_AddSubdividPrimGT3__FP8POLY_GT3P12Draw_SVertexN21P25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:316-357] SLD-VERIFIED ---- */
void DrawW_AddSubdividPrimGT3(POLY_GT3 *prim,Draw_SVertex *v0,Draw_SVertex *v1,Draw_SVertex *v2,
               Draw_tGiveShelbyMoreCache *sd)

{
  u_short uVar1;
  u_short uVar2;
  u_char uVar3;
  u_char uVar4;
  u_char uVar5;
  u_char uVar6;
  u_char uVar7;
  u_char uVar8;
  u_char uVar9;
  u_char uVar10;
  u_char uVar11;
  u_char uVar12;
  u_char uVar13;
  short sVar14;
  short sVar15;
  short sVar16;
  short sVar17;
  short sVar18;
  u_char a;
  u_short b;
  long c;
  
  ((u_char *)&prim->tag)[3] = 9;
  uVar3 = v0->g;
  uVar4 = v0->b;
  uVar5 = v0->a;
  uVar6 = v1->r;
  uVar7 = v1->g;
  uVar8 = v1->b;
  uVar9 = v1->a;
  uVar10 = v2->r;
  uVar11 = v2->g;
  uVar12 = v2->b;
  uVar13 = v2->a;
  prim->r0 = v0->r;
  prim->g0 = uVar3;
  prim->b0 = uVar4;
  prim->code = uVar5;
  prim->r1 = uVar6;
  prim->g1 = uVar7;
  prim->b1 = uVar8;
  prim->p1 = uVar9;
  prim->r2 = uVar10;
  prim->g2 = uVar11;
  prim->b2 = uVar12;
  prim->p2 = uVar13;
  sVar14 = v0->dvy;
  sVar15 = v1->dvx;
  sVar16 = v1->dvy;
  sVar17 = v2->dvx;
  sVar18 = v2->dvy;
  prim->x0 = v0->dvx;
  prim->y0 = sVar14;
  prim->x1 = sVar15;
  prim->y1 = sVar16;
  prim->x2 = sVar17;
  prim->y2 = sVar18;
  uVar3 = v0->v;
  uVar4 = v1->u;
  uVar5 = v1->v;
  uVar6 = v2->u;
  uVar7 = v2->v;
  prim->u0 = v0->u;
  prim->v0 = uVar3;
  prim->u1 = uVar4;
  prim->v1 = uVar5;
  prim->u2 = uVar6;
  prim->v2 = uVar7;
  uVar1 = (sd->GT4Prim).tpage;
  uVar2 = (sd->GT4Prim).clut;
  prim->code = (sd->GT4Prim).code;
  prim->tpage = uVar1;
  prim->clut = uVar2;
  return;
}

/* ---- DrawW_DivVertice__FP12Draw_SVertexN20  [DRAWW.CPP:387-398] SLD-VERIFIED ---- */
void DrawW_DivVertice(Draw_SVertex *v0,Draw_SVertex *v1,Draw_SVertex *v2)

{
  v0->vx = (short)((int)v1->vx + (int)v2->vx + 1 >> 1);
  v0->vy = (short)((int)v1->vy + (int)v2->vy + 1 >> 1);
  v0->vz = (short)((int)v1->vz + (int)v2->vz + 1 >> 1);
  v0->u = (u_char)((int)((u_int)v1->u + (u_int)v2->u + 1) >> 1);
  v0->v = (u_char)((int)((u_int)v1->v + (u_int)v2->v + 1) >> 1);
  v0->r = (u_char)((int)((u_int)v1->r + (u_int)v2->r) >> 1);
  v0->g = (u_char)((int)((u_int)v1->g + (u_int)v2->g) >> 1);
  v0->b = (u_char)((int)((u_int)v1->b + (u_int)v2->b) >> 1);
  return;
}

/* ---- DrawW_CalcSubdivision__FP25Draw_tGiveShelbyMoreCacheP12Draw_SVertexN31  [DRAWW.CPP:402-418] SLD-VERIFIED ---- */
int DrawW_CalcSubdivision(Draw_tGiveShelbyMoreCache *sd,Draw_SVertex *v0,Draw_SVertex *v1,Draw_SVertex *v2,
              Draw_SVertex *v3)

{
  int iVar1;
  int z0;
  int iVar2;
  int z1;
  int z2;
  int z3;
  
  iVar2 = (int)v0->vz;
  if ((int)v1->vz < (int)v0->vz) {
    iVar2 = (int)v1->vz;
  }
  if (v2->vz < iVar2) {
    iVar2 = (int)v2->vz;
  }
  if (v3->vz < iVar2) {
    iVar2 = (int)v3->vz;
  }
  iVar2 = iVar2 + sd->offsubdivid;
  if (0x800 < iVar2) {
    return 0;
  }
  if (iVar2 < 0x501) {
    iVar1 = 2;
    if (iVar2 < 0x201) {
      return 3;
    }
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}

/* ---- DrawW_SubdividFacet__FP25Draw_tGiveShelbyMoreCacheiP12Draw_SVertexN32ss  [DRAWW.CPP:425-590] SLD-VERIFIED ---- */
void DrawW_SubdividFacet(Draw_tGiveShelbyMoreCache *sd,int l,Draw_SVertex *v0,Draw_SVertex *v1,
               Draw_SVertex *v2,Draw_SVertex *v3,short n,short subDivide)

{
  u_int tu1;
  int iVar1;
  int subdivisionLevel;
  u_int *tp2;
  int child_n;
  int subOtz_local;
  Draw_SVertex *v4;
  POLY_GT4 *prim;
  int l_00;
  int subDivCount;
  Draw_SVertex *v5;
  Draw_SVertex *v7;
  Draw_SVertex *v6;
  short n_00;
  int child_l;
  int flag;
  long bfct;
  Draw_SVertex *v8;
  short ts1;
  u_char *tp4;
  short ts2;
  u_char *tp5;
  u_char *tp3;
  u_char *prim_00;
  u_long *otEntry;
  int vertexWord0;
  int vertexWord1;
  
  ts1 = (sd->head).clipW;
  if ((((ts1 < v0->dvx) && (ts1 < v1->dvx)) && (ts1 < v2->dvx)) && (ts1 < v3->dvx)) {
    return;
  }
  if (((v0->dvx < 0) && (v1->dvx < 0)) && ((v2->dvx < 0 && (v3->dvx < 0)))) {
    return;
  }
  ts2 = (sd->head).clipH;
  if (((ts2 < v0->dvy) && (ts2 < v1->dvy)) && ((ts2 < v2->dvy && (ts2 < v3->dvy)))) {
    return;
  }
  if ((((v0->dvy < 0) && (v1->dvy < 0)) && (v2->dvy < 0)) && (v3->dvy < 0)) {
    return;
  }
  if (((v0->vz < 0) && (v1->vz < 0)) && ((v2->vz < 0 && (v3->vz < 0)))) {
    return;
  }
  subdivisionLevel = DrawW_CalcSubdivision(sd,v0,v1,v2,v3);
  if (subdivisionLevel <= l) {
    if (subDivide != 0) {
      subDivCount = nfs4_mips_bits_to_s32(
          (u_int)(u_short)v0->dvx | (u_int)(u_short)v0->dvy << 16);
      child_l = nfs4_mips_bits_to_s32(
          (u_int)(u_short)v2->dvx | (u_int)(u_short)v2->dvy << 16);
      child_n = nfs4_mips_bits_to_s32(
          (u_int)(u_short)v1->dvx | (u_int)(u_short)v1->dvy << 16);
      gte_ldsxy3(subDivCount,child_n,child_l);
      gte_nclip();
gte_swc2(0x18,&bfct);
      iVar1 = 1;
      if ((sd->head).mirror == 1) {
        bfct = (long)nfs4_mips_negu_s32((int)bfct);
      }
      if (bfct < 0) {
        child_n = nfs4_mips_bits_to_s32(
            (u_int)(u_short)v3->dvx | (u_int)(u_short)v3->dvy << 16);
        gte_ldsxy3(subDivCount,child_l,child_n);
        gte_nclip();
        gte_swc2(0x18,&bfct);
        if ((sd->head).mirror == iVar1) {
          bfct = (long)nfs4_mips_negu_s32((int)bfct);
        }
        if (bfct < 0) {
          return;
        }
      }
    }
    prim = (POLY_GT4 *)(sd->head).cprim.PrimPtr;
    otEntry = (sd->head).cprim.LastPrim + sd->otz;
    (sd->head).cprim.PrimPtr = (char *)(prim + 1);
    prim->tag = 0x0c000000U;
    AddPrim(otEntry,prim);
    DrawW_AddSubdividPrimGT4(prim,v0,v1,v2,v3,sd);
    return;
  }
  n_00 = n + 5;
  v4 = &gDiv.v[(short)(u_short)n];
  v5 = &gDiv.v[(short)((u_short)n + 1)];
  v6 = &gDiv.v[(short)((u_short)n + 2)];
  v7 = &gDiv.v[(short)((u_short)n + 3)];
  v8 = &gDiv.v[(short)((u_short)n + 4)];
  DrawW_DivVertice(v4,v0,v1);
  nfs4_mips_copy_bytes(&vertexWord0,v4,4);
  nfs4_mips_copy_bytes(&vertexWord1,(u_char *)v4 + 4,4);
gte_lwc2(0,vertexWord0);
  gte_lwc2(1,vertexWord1);
  gte_rtps();
  DrawW_DivVertice(v5,v1,v2);
gte_stflg(&flag);
  if (flag < 0) {
    v4->a = '\x01';
  }
  else {
    v4->a = '\0';
  }
gte_swc2(0xe,&v4->dvx);
  nfs4_mips_copy_bytes(&vertexWord0,v5,4);
  nfs4_mips_copy_bytes(&vertexWord1,(u_char *)v5 + 4,4);
gte_lwc2(0,vertexWord0);
  gte_lwc2(1,vertexWord1);
  gte_rtps();
  DrawW_DivVertice(v6,v2,v3);
gte_stflg(&flag);
  if (flag < 0) {
    v5->a = '\x01';
  }
  else {
    v5->a = '\0';
  }
gte_swc2(0xe,&v5->dvx);
  nfs4_mips_copy_bytes(&vertexWord0,v6,4);
  nfs4_mips_copy_bytes(&vertexWord1,(u_char *)v6 + 4,4);
gte_lwc2(0,vertexWord0);
  gte_lwc2(1,vertexWord1);
  gte_rtps();
  DrawW_DivVertice(v7,v3,v0);
gte_stflg(&flag);
  if (flag < 0) {
    v6->a = '\x01';
  }
  else {
    v6->a = '\0';
  }
gte_swc2(0xe,&v6->dvx);
  nfs4_mips_copy_bytes(&vertexWord0,v7,4);
  nfs4_mips_copy_bytes(&vertexWord1,(u_char *)v7 + 4,4);
gte_lwc2(0,vertexWord0);
  gte_lwc2(1,vertexWord1);
  gte_rtps();
  DrawW_DivVertice(v8,v0,v2);
gte_stflg(&flag);
  if (flag < 0) {
    v7->a = '\x01';
  }
  else {
    v7->a = '\0';
  }
gte_swc2(0xe,&v7->dvx);
  nfs4_mips_copy_bytes(&vertexWord0,v8,4);
  nfs4_mips_copy_bytes(&vertexWord1,(u_char *)v8 + 4,4);
gte_lwc2(0,vertexWord0);
  gte_lwc2(1,vertexWord1);
  gte_rtps();
gte_stflg(&flag);
  if (flag < 0) {
    v8->a = 1;
  }
  else {
    v8->a = '\0';
  }
  if (sd->doublelayer == 0) goto DrawWSubdiv_recurse;
  (sd->GT4Prim).code = (sd->GT4Prim).code & 0xf7;
  tp3 = (u_char *)Render_gPacketPtr;
  subOtz_local = nfs4_mips_addu_s32(sd->otz,8);
  if (v0->a == '\0') {
    if (v1->a == '\0') {
      if (v4->a == '\0') {
        otEntry = (u_long *)(Render_gPalettePtr + subOtz_local * 4);
#ifdef AP_WIN
        AddPrim(otEntry,Render_gPacketPtr);
#else
        *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *otEntry & 0xffffff;
        tu1 = (u_int)Render_gPacketPtr & 0xffffff;
        *otEntry = *otEntry & 0xff000000 | tu1;
#endif
        Render_gPacketPtr = Render_gPacketPtr + 0x28;
        DrawW_AddSubdividPrimGT3((POLY_GT3 *)tp3,v0,v1,v4,sd);
      }
      goto DrawWSubdiv_testV1;
    }
DrawWSubdiv_testV2:
    tp5 = (u_char *)Render_gPacketPtr;
    if (v2->a != '\0') goto DrawWSubdiv_testV3;
    if (v3->a == '\0') {
    if (v6->a == '\0') {
        tp2 = (u_int *)(Render_gPalettePtr + subOtz_local * 4);
#ifdef AP_WIN
        AddPrim(tp2,Render_gPacketPtr);
#else
        *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *tp2 & 0xffffff;
        tu1 = (u_int)Render_gPacketPtr & 0xffffff;
        *tp2 = *tp2 & 0xff000000 | tu1;
#endif
        Render_gPacketPtr = Render_gPacketPtr + 0x28;
        DrawW_AddSubdividPrimGT3((POLY_GT3 *)tp5,v2,v3,v6,sd);
      }
      goto DrawWSubdiv_testV3;
    }
  }
  else {
DrawWSubdiv_testV1:
    tp4 = (u_char *)Render_gPacketPtr;
    if (v1->a != '\0') goto DrawWSubdiv_testV2;
    if (v2->a == '\0') {
      if (v5->a == '\0') {
        otEntry = (u_long *)(Render_gPalettePtr + subOtz_local * 4);
#ifdef AP_WIN
        AddPrim(otEntry,Render_gPacketPtr);
#else
        *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *otEntry & 0xffffff;
        tu1 = (u_int)Render_gPacketPtr & 0xffffff;
        *otEntry = *otEntry & 0xff000000 | tu1;
#endif
        Render_gPacketPtr = Render_gPacketPtr + 0x28;
        DrawW_AddSubdividPrimGT3((POLY_GT3 *)tp4,v1,v2,v5,sd);
      }
      goto DrawWSubdiv_testV2;
    }
DrawWSubdiv_testV3:
    prim_00 = (u_char *)Render_gPacketPtr;
  if (((v3->a == '\0') && (v0->a == '\0')) && (v7->a == '\0')) {
      tp2 = (u_int *)(Render_gPalettePtr + subOtz_local * 4);
#ifdef AP_WIN
      AddPrim(tp2,Render_gPacketPtr);
#else
      *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *tp2 & 0xffffff;
      tu1 = (u_int)Render_gPacketPtr & 0xffffff;
      *tp2 = *tp2 & 0xff000000 | tu1;
#endif
      Render_gPacketPtr = Render_gPacketPtr + 0x28;
      DrawW_AddSubdividPrimGT3((POLY_GT3 *)prim_00,v3,v0,v7,sd);
    }
  }
  (sd->GT4Prim).code = (sd->GT4Prim).code | 8;
DrawWSubdiv_recurse:
  l_00 = nfs4_mips_addu_s32(l,1);
gte_swc2(0xe,&v8->dvx);
  DrawW_SubdividFacet(sd,l_00,v0,v4,v8,v7,n_00,
             subDivide);
  DrawW_SubdividFacet(sd,l_00,v4,v1,v5,v8,n_00,
             subDivide);
  DrawW_SubdividFacet(sd,l_00,v8,v5,v2,v6,n_00,
             subDivide);
  DrawW_SubdividFacet(sd,l_00,v7,v8,v6,v3,n_00,
             subDivide);
  return;
}

/* ---- DrawW_LoadPrecVECTOR__FP12Draw_SVertexP6VECTOR  [DRAWW.CPP:593-606] SLD-VERIFIED ---- */
void DrawW_LoadPrecVECTOR(Draw_SVertex *v,VECTOR *dv)

{
  int y;
  int x;
  long temp;
  u_int uVar1;
  int iVar2;
  int z;
  
  x = dv->vx;
  iVar2 = dv->vz;
  uVar1 = dv->vy << 0x12 | (x & 0x3fffU) << 2;
  v->vx = (short)uVar1;
  v->vy = (short)(uVar1 >> 0x10);
  v->vz = (short)(iVar2 << 2);
  return;
}

/* ---- DrawW_SetUpSubdividFacet__FiP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:612-696] SLD-VERIFIED ---- */
void DrawW_SetUpSubdividFacet(int face,Draw_tGiveShelbyMoreCache *sd)

{
  long t0;
  long t1;
  long t2;
  long t3;
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  u_char uVar8;
  u_char uVar9;
  u_char uVar10;
  u_char uVar11;
  u_char uVar12;
  u_char uVar13;
  u_char uVar14;
  u_char uVar15;
  u_char uVar16;
  u_char uVar17;
  u_char uVar18;
  u_char uVar19;
  u_char uVar20;
  u_char uVar21;
  u_char uVar22;
  short u3;
  short u0;
  short u1;
  short u2;
  POLY_GT4 *prim;
  POLY_GT4 *pPVar23;
  Draw_SVertex *v2;
  Draw_SVertex *v3;
  Draw_SVertex *v1;
  Draw_SVertex *v0;
  
  DrawW_LoadPrecVECTOR(&sd->v0,&sd->tVn0);
  DrawW_LoadPrecVECTOR(&sd->v1,&sd->tVn1);
  DrawW_LoadPrecVECTOR(&sd->v2,&sd->tVn2);
  DrawW_LoadPrecVECTOR(&sd->v3,&sd->tVn3);
  pPVar23 = &sd->GT4Prim;
  sVar1 = (sd->GT4Prim).y0;
  sVar2 = (sd->GT4Prim).x1;
  sVar3 = (sd->GT4Prim).y1;
  sVar4 = (sd->GT4Prim).x3;
  sVar5 = (sd->GT4Prim).y3;
  sVar6 = (sd->GT4Prim).x2;
  sVar7 = (sd->GT4Prim).y2;
  (sd->v0).dvx = (sd->GT4Prim).x0;
  (sd->v0).dvy = sVar1;
  (sd->v1).dvx = sVar2;
  (sd->v1).dvy = sVar3;
  (sd->v2).dvx = sVar4;
  (sd->v2).dvy = sVar5;
  (sd->v3).dvx = sVar6;
  (sd->v3).dvy = sVar7;
  if ((sd->tVn0).vz < 0x140) {
gte_lwc2(0,*(int *)(((char *)sd + 0x14c)));
    gte_lwc2(1,*(int *)(((char *)sd + 0x150)));
    gte_rtps();
gte_swc2(0xe,((char *)sd + 0x154));
  }
  if ((sd->tVn1).vz < 0x140) {
gte_lwc2(0,*(int *)(((char *)sd + 0x15c)));
    gte_lwc2(1,*(int *)(((char *)sd + 0x160)));
    gte_rtps();
gte_swc2(0xe,((char *)sd + 0x164));
  }
  if ((sd->tVn2).vz < 0x140) {
gte_lwc2(0,*(int *)(((char *)sd + 0x16c)));
    gte_lwc2(1,*(int *)(((char *)sd + 0x170)));
    gte_rtps();
gte_swc2(0xe,((char *)sd + 0x174));
  }
  if ((sd->tVn3).vz < 0x140) {
gte_lwc2(0,*(int *)(((char *)sd + 0x17c)));
    gte_lwc2(1,*(int *)(((char *)sd + 0x180)));
    gte_rtps();
gte_swc2(0xe,((char *)sd + 0x184));
  }
  uVar8 = pPVar23->g0;
  uVar9 = pPVar23->b0;
  uVar10 = pPVar23->code;
  uVar11 = pPVar23->r1;
  uVar12 = pPVar23->g1;
  uVar13 = pPVar23->b1;
  uVar14 = pPVar23->p1;
  uVar15 = pPVar23->r3;
  uVar16 = pPVar23->g3;
  uVar17 = pPVar23->b3;
  uVar18 = pPVar23->p3;
  uVar19 = pPVar23->r2;
  uVar20 = pPVar23->g2;
  uVar21 = pPVar23->b2;
  uVar22 = pPVar23->p2;
  (sd->v0).r = pPVar23->r0;
  (sd->v0).g = uVar8;
  (sd->v0).b = uVar9;
  (sd->v0).a = uVar10;
  (sd->v1).r = uVar11;
  (sd->v1).g = uVar12;
  (sd->v1).b = uVar13;
  (sd->v1).a = uVar14;
  (sd->v2).r = uVar15;
  (sd->v2).g = uVar16;
  (sd->v2).b = uVar17;
  (sd->v2).a = uVar18;
  (sd->v3).r = uVar19;
  (sd->v3).g = uVar20;
  (sd->v3).b = uVar21;
  (sd->v3).a = uVar22;
  uVar8 = pPVar23->v0;
  uVar9 = pPVar23->u1;
  uVar10 = pPVar23->v1;
  uVar13 = pPVar23->u2;
  uVar14 = pPVar23->v2;
  uVar11 = pPVar23->u3;
  uVar12 = pPVar23->v3;
  (sd->v0).u = pPVar23->u0;
  (sd->v0).v = uVar8;
  (sd->v1).u = uVar9;
  (sd->v1).v = uVar10;
  (sd->v2).u = uVar11;
  (sd->v2).v = uVar12;
  (sd->v3).u = uVar13;
  (sd->v3).v = uVar14;
  sVar1 = (sd->v0).dvx;
  (sd->v0).a = '\0';
  if (sVar1 < 0x3e9) {
    sVar2 = (sd->v0).dvy;
    if ((((1000 < sVar2) || (sVar1 < -1000)) || (sVar2 < -1000)) || ((sd->v0).vz < 0x65))
    goto DrW_SubSetup_v0Alpha;
  }
  else {
DrW_SubSetup_v0Alpha:
    (sd->v0).a = '\x01';
  }
  sVar1 = (sd->v1).dvx;
  (sd->v1).a = '\0';
  if (sVar1 < 0x3e9) {
    sVar2 = (sd->v1).dvy;
    if (((1000 < sVar2) || (sVar1 < -1000)) || ((sVar2 < -1000 || ((sd->v1).vz < 0x65))))
    goto DrW_SubSetup_v1Alpha;
  }
  else {
DrW_SubSetup_v1Alpha:
    (sd->v1).a = '\x01';
  }
  sVar1 = (sd->v2).dvx;
  (sd->v2).a = '\0';
  if (sVar1 < 0x3e9) {
    sVar2 = (sd->v2).dvy;
    if (((1000 < sVar2) || (sVar1 < -1000)) || ((sVar2 < -1000 || ((sd->v2).vz < 0x65))))
    goto DrW_SubSetup_v2Alpha;
  }
  else {
DrW_SubSetup_v2Alpha:
    (sd->v2).a = '\x01';
  }
  sVar1 = (sd->v3).dvx;
  (sd->v3).a = '\0';
  if (sVar1 < 0x3e9) {
    sVar2 = (sd->v3).dvy;
    if ((((sVar2 < 0x3e9) && (-0x3e9 < sVar1)) && (-0x3e9 < sVar2)) && (100 < (sd->v3).vz))
    goto DrW_SubSetup_callSubdiv;
  }
  (sd->v3).a = '\x01';
DrW_SubSetup_callSubdiv:
  DrawW_SubdividFacet(sd,0,&sd->v0,&sd->v1,&sd->v2,&sd->v3,0,(u_short)(face == 0));
  return;
}

/* ---- Night_NightCopCalc__FP6VECTORPs  [DRAWW.CPP:711-744] SLD-VERIFIED ---- */
void Night_NightCopCalc(VECTOR *v,short *idx)

{
  int z;
  int side;
  int lookup;
  int x;

  z = v->vz;
  x = v->vx;
  if (((u_int)(z + 0x7ff) < 0xfffU) && ((u_int)(x + 0x3ff) < 0x7ffU)) {
    side = 0;
    if (z < 0) {
      z = -z;
      side = 1;
    }
    lookup = (z >> 5) * 0x40 + ((x + 0x400) >> 5);
    *idx = (u_short)(*Night_gCopColor[side])[(short)*idx]
                     [(u_char)Night_gNightTbl[lookup] >> 1];
  }
  return;
}

/* ---- Night_NightCalc__FP6VECTORPsP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:750-788] SLD-VERIFIED ---- */
void Night_NightCalc(VECTOR *v,short *idx,Draw_tGiveShelbyMoreCache *sd)

{
  int index;
  int xdist;
  u_char bVar1;
  int lookup;
  int iVar2;
  int x;
  int iVar3;
  int iVar4;
  int z;
  int znear;
  int iVar5;
  int zfar;
  
  bVar1 = sd->night_ZDistShift;
  iVar4 = v->vz;
  iVar5 = (int)sd->night_ZNear;
  if (sd->night_DrawLightning != '\0') {
    *idx = (u_short)(*Night_gWeatherLightingTable[sd->night_LightningType])[*idx];
  }
  if ((iVar5 < iVar4) && (iVar4 < iVar5 + (1 << (bVar1 + 6 & 0x1f)))) {
    iVar3 = v->vx;
    iVar2 = 1 << (sd->night_XDistShift + 5 & 0x1f);
    if ((-iVar2 < iVar3) && (iVar3 < iVar2)) {
      *idx = (u_short)(*Night_gCurrentNightColor)[*idx]
                     [(u_char)Night_gNightTbl
                            [(iVar4 - iVar5 >> (sd->night_ZDistShift & 0x1f)) * 0x40 +
                             (iVar3 + iVar2 >> (sd->night_XDistShift & 0x1f))]];
    }
  }
  return;
}

/* ---- DrawW_NightColorCalc__FP25Draw_tGiveShelbyMoreCacheP8POLY_GT4P8CCOORD16N32  [DRAWW.CPP:802-894] SLD-VERIFIED ---- */
void DrawW_NightColorCalc(Draw_tGiveShelbyMoreCache *sd,POLY_GT4 *prim,CCOORD16 *vt0,CCOORD16 *vt1,
               CCOORD16 *vt2,CCOORD16 *vt3)

{
  long d;
  VECTOR temp0;
  VECTOR tempnight;
  u_char uVar1;
  u_char uVar2;
  u_char uVar3;
  u_char uVar4;
  u_char uVar5;
  u_char uVar6;
  u_char uVar7;
  u_char uVar8;
  u_char uVar9;
  u_char uVar10;
  u_char uVar11;
  long color;
  CVECTOR CVar12;
  long c;
  CVECTOR *pCVar13;
  long b;
  CVECTOR *pCVar14;
  VECTOR *pVVar15;
  long a;
  CVECTOR *pCVar16;
  CCOORD16 *idx;
  VECTOR tempcop;
  
  if (sd->light == -1) {
    idx = vt1;
    if ((sd->nightFlags & 1U) != 0) {
gte_SetRotMatrix(((char *)sd + 0x34));
gte_SetTransMatrix(((char *)sd + 0x34));
gte_lwc2(0,*(int *)(vt0));
      gte_lwc2(1,*(int *)(((char *)vt0 + 0x4)));
      gte_rt();
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(vt1));
      gte_lwc2(1,*(int *)(((char *)vt1 + 0x4)));
      gte_rt();
      a = (long)&vt0->light;
      Night_NightCalc(&tempcop,(short *)a,sd);
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(vt2));
      gte_lwc2(1,*(int *)(((char *)vt2 + 0x4)));
      gte_rt();
      Night_NightCalc(&tempcop,&vt1->light,sd);
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(vt3));
      gte_lwc2(1,*(int *)(((char *)vt3 + 0x4)));
      gte_rt();
      Night_NightCalc(&tempcop,&vt2->light,sd);
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
      Night_NightCalc(&tempcop,&vt3->light,sd);
    }
    if ((sd->nightFlags & 2U) != 0) {
gte_SetRotMatrix(((char *)sd + 0x54));
gte_SetTransMatrix(((char *)sd + 0x54));
gte_lwc2(0,*(int *)(vt0));
      gte_lwc2(1,*(int *)(((char *)vt0 + 0x4)));
      gte_rt();
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(vt1));
      gte_lwc2(1,*(int *)(((char *)vt1 + 0x4)));
      gte_rt();
      Night_NightCopCalc(&tempcop,&idx->x);
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(vt2));
      gte_lwc2(1,*(int *)(((char *)vt2 + 0x4)));
      gte_rt();
      Night_NightCopCalc(&tempcop,&idx->x);
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(vt3));
      gte_lwc2(1,*(int *)(((char *)vt3 + 0x4)));
      gte_rt();
      Night_NightCopCalc(&tempcop,&idx->x);
gte_swc2(0x19,&temp0);
      gte_swc2(0x1a,((char *)&temp0 + 0x4));
      gte_swc2(0x1b,((char *)&temp0 + 0x8));
      Night_NightCopCalc(&tempcop,&idx->x);
    }
    pCVar16 = Chunk_lightTable + vt0->light;
    pCVar14 = Chunk_lightTable + vt1->light;
    pCVar13 = Chunk_lightTable + vt3->light;
    uVar1 = pCVar16->g;
    uVar2 = pCVar16->b;
    uVar3 = pCVar16->cd;
    uVar4 = pCVar14->r;
    uVar5 = pCVar14->g;
    uVar6 = pCVar14->b;
    uVar7 = pCVar14->cd;
    uVar8 = pCVar13->r;
    uVar9 = pCVar13->g;
    uVar10 = pCVar13->b;
    uVar11 = pCVar13->cd;
    CVar12 = Chunk_lightTable[vt2->light];
    prim->r0 = pCVar16->r;
    prim->g0 = uVar1;
    prim->b0 = uVar2;
    prim->code = uVar3;
    prim->r1 = uVar4;
    prim->g1 = uVar5;
    prim->b1 = uVar6;
    prim->p1 = uVar7;
    prim->r2 = uVar8;
    prim->g2 = uVar9;
    prim->b2 = uVar10;
    prim->p2 = uVar11;
  }
  else {
    if ((sd->nightFlags & 1U) != 0) {
gte_SetRotMatrix(((char *)sd + 0x34));
gte_SetTransMatrix(((char *)sd + 0x34));
gte_lwc2(0,*(int *)(vt0));
      gte_lwc2(1,*(int *)(((char *)vt0 + 0x4)));
      gte_rt();
      pVVar15 = &tempcop;
gte_swc2(0x19,&tempnight);
      gte_swc2(0x1a,((char *)&tempnight + 0x4));
      gte_swc2(0x1b,((char *)&tempnight + 0x8));
      Night_NightCalc(pVVar15,&sd->light,sd);
    }
    if ((sd->nightFlags & 2U) != 0) {
gte_SetRotMatrix(((char *)sd + 0x54));
gte_SetTransMatrix(((char *)sd + 0x54));
gte_lwc2(0,*(int *)(vt0));
      gte_lwc2(1,*(int *)(((char *)vt0 + 0x4)));
      gte_rt();
      pVVar15 = &tempcop;
gte_swc2(0x19,&tempcop);
      gte_swc2(0x1a,((char *)&tempcop + 0x4));
      gte_swc2(0x1b,((char *)&tempcop + 0x8));
      Night_NightCopCalc(pVVar15,&vt1->x);
    }
    CVar12 = Chunk_lightTable[sd->light];
    prim->r0 = CVar12.r;
    prim->g0 = CVar12.g;
    prim->b0 = CVar12.b;
    prim->code = CVar12.cd;
    prim->r1 = CVar12.r;
    prim->g1 = CVar12.g;
    prim->b1 = CVar12.b;
    prim->p1 = CVar12.cd;
    prim->r2 = CVar12.r;
    prim->g2 = CVar12.g;
    prim->b2 = CVar12.b;
    prim->p2 = CVar12.cd;
  }
  prim->r3 = CVar12.r;
  prim->g3 = CVar12.g;
  prim->b3 = CVar12.b;
  prim->p3 = CVar12.cd;
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
  return;
}

/* ---- DrawW_DrawQuad__FP25Draw_tGiveShelbyMoreCacheP8Trk_Quad  [DRAWW.CPP:930-1297] SLD-VERIFIED ---- */
void DrawW_DrawQuad(Draw_tGiveShelbyMoreCache *sd,Trk_Quad *inQuad)

{
  int*z;
  int p1;
  int p2;
  int p3;
  int t2;
  short tx;
  short ty;
  short tz;
  long * dp0;
  long * dp1;
  long * dp2;
  int newIndex;
  DR_TWIN * aprim;
  int p0;
  u_long l1;
  u_long l2;
  u_long l3;
  int dU;
  short vert2_proj_x;
  u_long l0;
  short vert0_proj_x;
  short tu27;
  short vert1_proj_x;
  short tu28;
  short vert3_proj_x;
  short tu29;
  short tu30;
  int bfctResult;
  intptr tu24;
  int dV;
  int tu4;
  int ti5;
  u_int uVar3_00;
  short sVar1;
  short ts27;
  int iVar2;
  u_int uVar3;
  int depth_avg;
  short ts31;
  int uVar7_00;
  int ti18;
  Track_tMaterial *currentQuadMat;
  u_char d;
  int vert_y_pack;
  u_char c;
  int vert_x_pack;
  CCOORD16 *geomVertices;
  CCOORD16 *sourceVertex;
  short vert0_proj_y;
  short vert1_proj_y;
  short vert2_proj_y;
  short vert3_proj_y;
  int t1;
  short tu46;
  short tu47;
  short tu48;
  short tu49;
  int t3;
  int zeroTransFlag;
  POLY_GT4 *prim;
  Draw_tPixMap *workPmx;
  u_long *otEntry;
  int save_pre_otz;
  char flag;
  int doSubdivision;
  int face;
  int facetIdx;
  CCOORD16 vt0;
  CCOORD16 vt1;
  CCOORD16 vt2;
  CCOORD16 vt3;
  PSX_RECT r;
  long dvxy0;
  long dvxy1;
  long dvxy3;
  long dvxy2;
  long bfct;
  int depthcue;
  long a;
  long b;
  u_int uStack_28;
  long color;
  u_char bVar2;
  u_char tc3;
  u_char bVar4;
  int tu5;
  u_char bVar1;
  int tp6;
  u_char *tp20;
  u_char *p;
  u_char *tp18;
  u_char *tp19;
  int tu1;
  u_int tu2;
  u_int tu18;
  
  geomVertices = sd->vertices;
  ts31 = (sd->trans).x;
  ts27 = (sd->trans).y;
  /* Trk_Quad stores its four vertex indices as bytes 2..5.  The old
     decompiler cast to short* before adding 3/5, accidentally reading bytes
     6 and 10.  Oracle lbu sequence: t2=3, a=2, c=4, d=5. */
  vert_x_pack = (int)*(u_char *)((char *)inQuad + 4); /* c: vertex 3 */
  vert_y_pack = (int)*(u_char *)((char *)inQuad + 5); /* d: vertex 2 */
  sVar1 = (sd->trans).z;
  sourceVertex = &geomVertices[inQuad->aPoints[1]];
  vt0.x = (short)(sourceVertex->x + ts31);
  vt0.y = (short)(sourceVertex->y + ts27);
  vt0.light = sourceVertex->light;
  vt0.z = (short)(sourceVertex->z + sVar1);
gte_lwc2(0,*(int *)(&vt0));
  gte_lwc2(1,*(int *)(((char *)&vt0 + 0x4)));
  sourceVertex = &geomVertices[inQuad->aPoints[0]];
  gte_rtps_b();
  vt1.x = (short)(sourceVertex->x + ts31);
  vt1.y = (short)(sourceVertex->y + ts27);
  vt1.light = sourceVertex->light;
  vt1.z = (short)(sourceVertex->z + sVar1);
gte_swc2(0x19,((char *)sd + 0x98));
  gte_swc2(0x1a,((char *)sd + 0x9c));
  gte_swc2(0x1b,((char *)sd + 0xa0));
gte_swc2(0xe,&dvxy0);
gte_lwc2(0,*(int *)(&vt1));
  gte_lwc2(1,*(int *)(((char *)&vt1 + 0x4)));
  sourceVertex = &geomVertices[vert_y_pack & 0xffU];
  gte_rtps_b();
  vt2.x = (short)(sourceVertex->x + ts31);
  vt2.y = (short)(sourceVertex->y + ts27);
  vt2.light = sourceVertex->light;
  vt2.z = (short)(sourceVertex->z + sVar1);
gte_swc2(0x19,((char *)sd + 0xa8));
  gte_swc2(0x1a,((char *)sd + 0xac));
  gte_swc2(0x1b,((char *)sd + 0xb0));
gte_lwc2(0,*(int *)(&vt2));
  gte_lwc2(1,*(int *)(((char *)&vt2 + 0x4)));
  sourceVertex = &geomVertices[vert_x_pack & 0xffU];
  gte_rtps_b();
  vt3.x = (short)(sourceVertex->x + ts31);
  vt3.y = (short)(sourceVertex->y + ts27);
  vt3.light = sourceVertex->light;
  vt3.z = (short)(sourceVertex->z + sVar1);
gte_swc2(0x19,((char *)sd + 0xb8));
  gte_swc2(0x1a,((char *)sd + 0xbc));
  gte_swc2(0x1b,((char *)sd + 0xc0));
gte_lwc2(0,*(int *)(&vt3));
  gte_lwc2(1,*(int *)(((char *)&vt3 + 0x4)));
  gte_rtps();
gte_swc2(0x19,((char *)sd + 0xc8));
  gte_swc2(0x1a,((char *)sd + 0xcc));
  gte_swc2(0x1b,((char *)sd + 0xd0));
  if ((((sd->tVn3).vx <= (sd->tVn3).vz) ||
       ((sd->tVn0).vx <= (sd->tVn0).vz) ||
       ((sd->tVn1).vx <= (sd->tVn1).vz) ||
       ((sd->tVn2).vx <= (sd->tVn2).vz)) &&
      ((nfs4_mips_negu_s32((sd->tVn3).vx) <= (sd->tVn3).vz) ||
       (nfs4_mips_negu_s32((sd->tVn0).vx) <= (sd->tVn0).vz) ||
       (nfs4_mips_negu_s32((sd->tVn1).vx) <= (sd->tVn1).vz) ||
       (nfs4_mips_negu_s32((sd->tVn2).vx) <= (sd->tVn2).vz)) &&
      ((-1 < (sd->tVn0).vz) || (-1 < (sd->tVn1).vz) ||
       (-1 < (sd->tVn2).vz) || (-1 < (sd->tVn3).vz))) {
    gte_avsz4_b();
    currentQuadMat = sd->materials + inQuad->material;
    bVar2 = (u_char)currentQuadMat->flag;
gte_swc2(0x7,((char *)sd + 0x94));
    facetIdx = bVar2 >> 3 & 2;
gte_swc2(0xc,&dvxy1);
    gte_swc2(0xd,&dvxy3);
    gte_swc2(0xe,&dvxy2);
    bVar4 = 199 < sd->otz;
#ifdef AP_WIN
    /* Observation only.  This is placed after the exact 0x800C67D4..67F4
       AVSZ4/SXY stores and before either 0x800C680C/6868 NCLIP, so it cannot
       influence the branch being diagnosed. */
    NFSHS_DIAGNOSTIC_CALL(NFSHS_HostTraceDrawQuadCandidate(sd,inQuad,currentQuadMat,
                                     dvxy0,dvxy1,dvxy2,dvxy3));
#endif
    if (((bVar2 >> 3 & 2) == 0) && ((bool)bVar4)) {
      gte_nclip_b();
gte_swc2(0x18,&bfct);
      iVar2 = 1;
      if ((sd->head).mirror == 1) {
        bfct = (long)nfs4_mips_negu_s32((int)bfct);
      }
      if (bfct < 0) {
        /* 0x800C6848..0x800C686C replaces the SXY FIFO with vertices
           0,1,2 and executes a second NCLIP for the other triangle of the
           quad.  The decompiler had dropped all four COP2 operations and
           merely re-read the first (negative) MAC0, culling valid quads. */
        gte_ldsxy3(dvxy0,dvxy1,dvxy2);
        gte_nclip_b();
gte_swc2(0x18,&bfct);
        if ((sd->head).mirror == iVar2) {
          bfct = (long)nfs4_mips_negu_s32((int)bfct);
        }
        if (bfct < 0) {
          return;
        }
      }
    }
gte_swc2(0x8,&depthcue);
    workPmx = sd->artInfo->pPmx + currentQuadMat->pmxIndex;
    if ((((bVar2 & 8) != 0) && (sd->fogstate != '\0')) && ((int)sd->startfog <= sd->otz)) {
      workPmx = sd->artInfo->pPmx +
                nfs4_mips_addu_s32((int)currentQuadMat->pmxIndex,
                                   (int)(u_char)currentQuadMat->mipmap_offset);
    }
    depth_avg = sd->otz;
    bfctResult = nfs4_mips_sra_s32(depth_avg,1);
    bVar1 = sd->offset == Draw_gMidGroundOtz;
    sd->otz = bfctResult;
    iVar2 = bfctResult;
    if ((bool)bVar1) {
      bfctResult = nfs4_mips_sll_s32(bfctResult,2);
      iVar2 = nfs4_mips_sra_s32(depth_avg,4);
    }
    sd->otz = nfs4_mips_addu_s32(iVar2,sd->offset);
    tp19 = (u_char *)Render_gPacketPtr;
    tp18 = (u_char *)Render_gPalettePtr;
    if ((0 < sd->otz) && (sd->otz <= Draw_gViewOtSize + -3)) {
      if ((bVar2 & 0x80) != 0) {
        r.w = 0;
        r.h = 0;
        r.x = 0;
        r.y = 0;
#ifdef AP_WIN
        AddPrim(Render_gPalettePtr+sd->otz*4,Render_gPacketPtr);
#else
        *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *(u_int *)(Render_gPalettePtr + sd->otz * 4) & 0xffffff;
        tu4 = (u_int)Render_gPacketPtr & 0xffffff;
        *(u_int *)(tp18 + sd->otz * 4) = *(u_int *)(tp18 + sd->otz * 4) & 0xff000000 | tu4;
#endif
        Render_gPacketPtr = Render_gPacketPtr + 0xc;
        SetTexWindow((DR_TWIN *)tp19,&r);
      }
      if ((bool)bVar4) {
        prim = (POLY_GT4 *)(sd->head).cprim.PrimPtr;
        otEntry = (sd->head).cprim.LastPrim + sd->otz;
        (sd->head).cprim.PrimPtr = (char *)(prim + 1);
        prim->tag = (u_long)(intptr)(u_long *)0x0c000000;
        AddPrim(otEntry,prim);
      }
      else {
        prim = &sd->GT4Prim;
      }
      prim->x0 = (u_short)dvxy0;
      prim->y0 = (*(u_short *)((u_char *)&(dvxy0) + 2));
      prim->x1 = (u_short)dvxy1;
      prim->y1 = (*(u_short *)((u_char *)&(dvxy1) + 2));
      prim->x2 = (u_short)dvxy2;
      prim->y2 = (*(u_short *)((u_char *)&(dvxy2) + 2));
      prim->x3 = (u_short)dvxy3;
      prim->y3 = (*(u_short *)((u_char *)&(dvxy3) + 2));
      if (sd->nightFlags == '\0') {
        gte_ldIR0(depthcue);
        if (sd->light == -1) {
          nfs4_mips_copy_bytes(&l2,Chunk_lightTable + vt2.light,4);
 gte_lwc2(6,(int)l2);
          gte_dpcs();
          nfs4_mips_copy_bytes(&l0,Chunk_lightTable + vt0.light,4);
          nfs4_mips_copy_bytes(&l1,Chunk_lightTable + vt1.light,4);
          nfs4_mips_copy_bytes(&l3,Chunk_lightTable + vt3.light,4);
          gte_swc2(0x16,&prim->r3);
          /* 0x800C6B28..0x800C6B34 loads RGB0/1/2 and RGBC directly
             from three stack words.  Express the values directly here:
             round-tripping `long` locals through `int*` invokes strict-
             aliasing UB on the host and GCC reused stale stack contents. */
          gte_lwc2(20,(int)l0);
          gte_lwc2(21,(int)l1);
          gte_lwc2(22,(int)l3);
          gte_lwc2(6,(int)l3);
          gte_dpct();
          gte_swc2(0x14,&prim->r0);
          gte_swc2(0x15,&prim->r1);
          gte_swc2(0x16,&prim->r2);
        }
        else {
          nfs4_mips_copy_bytes(&color,Chunk_lightTable + sd->light,4);
          gte_lwc2(6,(int)color);
          gte_dpcs();
          gte_swc2(0x16,&color);
          prim->r0 = (u_char)color;
          prim->g0 = ((u_char *)&(color))[1];
          prim->b0 = ((u_char *)&(color))[2];
          prim->code = ((u_char *)&(color))[3];
          prim->r1 = (u_char)color;
          prim->g1 = ((u_char *)&(color))[1];
          prim->b1 = ((u_char *)&(color))[2];
          prim->p1 = ((u_char *)&(color))[3];
          prim->r2 = (u_char)color;
          prim->g2 = ((u_char *)&(color))[1];
          prim->b2 = ((u_char *)&(color))[2];
          prim->p2 = ((u_char *)&(color))[3];
          prim->r3 = (u_char)color;
          prim->g3 = ((u_char *)&(color))[1];
          prim->b3 = ((u_char *)&(color))[2];
          prim->p3 = ((u_char *)&(color))[3];
        }
      }
      else {
        DrawW_NightColorCalc(sd,prim,&vt0,&vt1,&vt2,&vt3);
      }
      ((u_char *)&prim->tag)[3] = 0xc;
      prim->code = (u_char)workPmx->flag | 0x3c;
      prim->u0 = workPmx->u0;
      prim->v0 = workPmx->v0;
      prim->clut = workPmx->clut;
      prim->u1 = workPmx->u1;
      prim->v1 = workPmx->v1;
      prim->tpage = workPmx->tpage;
      prim->u2 = workPmx->u2;
      prim->v2 = workPmx->v2;
      prim->pad2 = workPmx->pad2;
      prim->u3 = workPmx->u3;
      prim->v3 = workPmx->v3;
      prim->pad3 = workPmx->flag;
      if (prim->clut == 0xffff) {
        ti18 = nfs4_mips_srav_s32(
            nfs4_mips_sll_s32(nfs4_mips_subu_s32(
                bfctResult,(int)sd->startfog),4),(int)sd->distfog);
        if (ti18 < 0) {
          ti18 = 0;
        }
        else if (0xf < ti18) {
          ti18 = 0xf;
        }
        prim->clut = gClutDepth[workPmx->pad2][ti18];
      }
      if (!(bool)bVar4) {
        tc3 = sd->zeroGTETransFlag;
gte_SetRotMatrix(((char *)sd + 0x74));
        if (tc3 == 0) {
gte_SetTransMatrix(((char *)sd + 0x74));
        }
        if (stackSpeedUpEnbabledFlag == 0) {
          DrawW_SetUpSubdividFacet(facetIdx,sd);
        }
        else {
          tu24 = (intptr)SetSp((void *)gWSavePtr);
          stackSpeedUpEnbabledFlag = 0;
          gWSavePtr = tu24;
          DrawW_SetUpSubdividFacet(facetIdx,sd);
          gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
          stackSpeedUpEnbabledFlag = 1;
        }
gte_SetRotMatrix(((char *)sd + 0x14));
        if (tc3 == 0) {
gte_SetTransMatrix(((char *)sd + 0x14));
        }
      }
      p = (u_char *)Render_gPacketPtr;
      tp20 = (u_char *)Render_gPalettePtr;
      if ((bVar2 & 0x80) != 0) {
        iVar2 = nfs4_mips_subu_s32((int)workPmx->u3,(int)workPmx->u0);
        if (iVar2 < 0) {
          iVar2 = -iVar2;
        }
        ti5 = nfs4_mips_subu_s32((int)workPmx->v3,(int)workPmx->v0);
        if (ti5 < 0) {
          ti5 = -ti5;
        }
        r.w = (short)iVar2 + 1;
        r.h = (short)ti5 + 1;
        r.x = 0;
        r.y = 0;
#ifdef AP_WIN
        AddPrim(Render_gPalettePtr+sd->otz*4,Render_gPacketPtr);
#else
        *(u_int *)Render_gPacketPtr = *(u_int *)Render_gPacketPtr & 0xff000000 | *(u_int *)(Render_gPalettePtr + sd->otz * 4) & 0xffffff;
        uVar3_00 = (u_int)Render_gPacketPtr & 0xffffff;
        *(u_int *)(tp20 + sd->otz * 4) = *(u_int *)(tp20 + sd->otz * 4) & 0xff000000 | uVar3_00;
#endif
        Render_gPacketPtr = Render_gPacketPtr + 0xc;
        SetTexWindow((DR_TWIN *)p,&r);
      }
    }
  }
  return;
}

/* ---- DrawW_kCtrlWorld_High__FP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:1302-1324] SLD-VERIFIED ---- */
void DrawW_kCtrlWorld_High(Draw_tGiveShelbyMoreCache *sd)

{
  int numQuads;
  u_int n_remaining;
  Trk_Quad *pquad;
  n_remaining = (u_int)sd->quadCount;
  pquad = (Trk_Quad *)sd->quads;
  while (n_remaining = n_remaining - 1, n_remaining != 0xffffffff) {
    if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
      DrawW_DrawQuad(sd,pquad);
    }
    /* Original MIPS advances this pointer in the loop branch delay slot. */
    pquad = pquad + 1;
  }
  return;
}

/* ---- DrawW_StripDraw_High__FP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:1331-1375] SLD-VERIFIED ---- */
void DrawW_StripDraw_High(Draw_tGiveShelbyMoreCache *sd)

{
  int r0;
  int r2;
  u_char bVar1;
  short sVar2;
  int r1;
  int r3;
  int iquad;
  int iVar3;
  Trk_NewStrip *stripPtr;
  Trk_NewStrip *pTVar4;
  int numQuads;
  Trk_Quad newQuad;
  pTVar4 = sd->stripPtr;
  sd->doublelayer = 1;
  while( true ) {
    sVar2 = sd->numStrips + -1;
    sd->numStrips = sVar2;
    iVar3 = 0;
    if (sVar2 == -1) break;
    bVar1 = pTVar4->quadCount;
    for (; iVar3 < (int)(u_int)bVar1; iVar3 = iVar3 + 1) {
      if ((sd->head).cprim.PrimPtr < (sd->head).cprim.MPrimPtr) {
        newQuad.material = *(u_short *)((char *)pTVar4 + 4 + iVar3 * 2);
        newQuad.aPoints[0] = (u_char)(*(u_char *)pTVar4 + iVar3 + 1);
        newQuad.aPoints[1] = (u_char)(*(u_char *)pTVar4 + iVar3);
        newQuad.aPoints[2] = (u_char)(*(u_char *)((char *)pTVar4 + 1) + iVar3);
        newQuad.aPoints[3] = (u_char)(*(u_char *)((char *)pTVar4 + 1) + iVar3 + 1);
        DrawW_DrawQuad(sd,&newQuad);
      }
    }
    pTVar4 = (Trk_NewStrip *)(&pTVar4->topVert + (u_char)pTVar4->size);
  }
  return;
}

/* ---- DrawW_DoTrough__FP13DRender_tViewP11tBuildEntry  [DRAWW.CPP:1390-1654] SLD-VERIFIED ---- */
void DrawW_DoTrough(DRender_tView *Vi,tBuildEntry *buildList)

{
  int cx;
  int cz;
  Group * group;
  u_char bVar1;
  int iVar2;
  Chunk *pCVar3;
  int dist;
  int iVar4;
  int iVar5;
  Group *pThis;
  Group *pGVar6;
  Draw_tGiveShelbyMoreCache *sd;
  Chunk *chunkDat;
  coorddef *pChunkCp;
  coorddef *pcVar7;
  int buildInd;
  int iVar8;
  coorddef tmp;
  coorddef tmp2;
  int chunkCount;
  sd = (Draw_tGiveShelbyMoreCache *)getScratchAddr(0);
  
  iVar2 = BWorld_gChunkCount;
  iVar8 = 0;
  sd->doublelayer = 1;
  sd->identMat = gIdentTemplate;
  sd->offsubdivid = 0;
  do {
    pCVar3 = Track_chunkList;
    if (iVar2 <= iVar8) {
      return;
    }
    if ((buildList->enableBits & 1U) != 0) {
      sd->artInfo = &gInitialArt;
      bVar1 = (u_char)buildList->chunkInd;
      sd->rezInd = buildList->geomRez;
      sd->chunkInd = bVar1;
      DrawW_WorldSetUpMatrix(&gWorldMat,&Render_gWorldMat);
      sd->nightFlags = '\0';
      sd->vertices = (CCOORD16 *)(pCVar3[bVar1].vertexBuf + 1);
      sd->materials = Track_materials;
      pcVar7 = Chunk_chunkCenters + sd->chunkInd;
      if (gNight_renderNight != 0) {
        sd->nightFlags = '\x04';
        iVar4 = nfs4_mips_sra_s32(nfs4_mips_subu_s32(pcVar7->x,
            ((Camera_gInfo[Vi->player].target)->position).x),10);
        iVar5 = nfs4_mips_sra_s32(nfs4_mips_subu_s32(pcVar7->z,
            ((Camera_gInfo[Vi->player].target)->position).z),10);
        dist = nfs4_mips_addu_s32(nfs4_mips_mult_s32(iVar4,iVar4),
            nfs4_mips_mult_s32(iVar5,iVar5));
        if (dist < 0x47e0000) {
          if (((Cars_gList[Vi->player]->control).lights & 6U) != 0) {
            sd->nightFlags = '\x05';
          }
          tmp.x = nfs4_mips_subu_s32((Vi->cview).translation.x,
              ((Camera_gInfo[Vi->player].target)->position).x);
          tmp.y = nfs4_mips_subu_s32((Vi->cview).translation.y,
              ((Camera_gInfo[Vi->player].target)->position).y);
          tmp.z = nfs4_mips_subu_s32((Vi->cview).translation.z,
              ((Camera_gInfo[Vi->player].target)->position).z);
          transform(&tmp.x,gNightMat.m,&tmp2.x);
          DrawW_WorldSetUpTranslation(&tmp2,&Render_gNightMat);
        }
        if (BW_gCopCarObj != (Car_tObj *)0x0) {
          iVar4 = nfs4_mips_sra_s32(nfs4_mips_subu_s32(pcVar7->x,
              (BW_gCopCarObj->N).position.x),10);
          iVar5 = nfs4_mips_sra_s32(nfs4_mips_subu_s32(pcVar7->z,
              (BW_gCopCarObj->N).position.z),10);
          dist = nfs4_mips_addu_s32(nfs4_mips_mult_s32(iVar4,iVar4),
              nfs4_mips_mult_s32(iVar5,iVar5));
          if (dist < 0x47e0000) {
            sd->nightFlags = sd->nightFlags | 2;
            tmp.x = nfs4_mips_subu_s32((Vi->cview).translation.x,
                (BW_gCopCarObj->N).position.x);
            tmp.y = nfs4_mips_subu_s32((Vi->cview).translation.y,
                (BW_gCopCarObj->N).position.y);
            tmp.z = nfs4_mips_subu_s32((Vi->cview).translation.z,
                (BW_gCopCarObj->N).position.z);
            transform(&tmp.x,gCopMat.m,&tmp2.x);
            DrawW_WorldSetUpTranslation(&tmp2,&Render_gCopMat);
          }
        }
      }
      sd->trans.x = (short)nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(pcVar7->x,(Vi->cview).translation.x),10);
      sd->trans.y = (short)nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(pcVar7->y,(Vi->cview).translation.y),10);
      sd->trans.z = (short)nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(pcVar7->z,(Vi->cview).translation.z),10);
      sd->light = -1;
      Render_gWorldMat.t[2] = 0;
      Render_gWorldMat.t[1] = 0;
      Render_gWorldMat.t[0] = 0;
      gte_SetTransMatrix(&sd->matB);
      if (sd->rezInd == '\0') {
        pGVar6 = pCVar3[bVar1].lorezstripBuf;
        if (pGVar6 != (Group *)0x0) {
          sd->numStrips = (u_short)pGVar6->m_num_elements;
          sd->stripPtr = (Trk_NewStrip *)(pGVar6 + 1);
          if (sd->stripPtr != (Trk_NewStrip *)0x0) {
            sd->offset = 0x7d;
            DrawW_StripDraw_High(sd);
          }
        }
        sd->quadCount = pCVar3[bVar1].quadCounts[0];
        if (sd->quadCount != '\0') {
          sd->quads = pCVar3[bVar1].renderQuads[0];
          sd->offset = 0x7d;
          sd->zeroGTETransFlag = '\x01';
          DrawW_kCtrlWorld_High(sd);
        }
        sd->quadCount = pCVar3[bVar1].quadCounts[1];
        if (sd->quadCount != '\0') {
          sd->quads = pCVar3[bVar1].renderQuads[1];
DrawWTrough_setStateCallHigh:
          sd->offset = 0x1e;
          sd->zeroGTETransFlag = '\x01';
          DrawW_kCtrlWorld_High(sd);
        }
      }
      else {
        pGVar6 = pCVar3[bVar1].stripBuf;
        if (pGVar6 != (Group *)0x0) {
          sd->stripPtr = (Trk_NewStrip *)(pGVar6 + 1);
          sd->numStrips = (u_short)pGVar6->m_num_elements;
          sd->offset = 0x7d;
          DrawW_StripDraw_High(sd);
          sd->quadCount = pCVar3[bVar1].quadCounts[5];
          if (sd->quadCount != '\0') {
            sd->quads = pCVar3[bVar1].renderQuads[3];
            goto DrawWTrough_setStateCallHigh;
          }
        }
      }
      sd->vertices = (CCOORD16 *)(pCVar3[bVar1].objVertexBuf + 1);
      sd->quadCount = pCVar3[bVar1].quadCounts[2];
      if (sd->quadCount != '\0') {
        sd->offset = 0x7d;
        sd->zeroGTETransFlag = '\x01';
        sd->quads = (Trk_Quad *)(pCVar3[bVar1].objQuadBuf + 1);
        DrawW_kCtrlWorld_High(sd);
      }
      sd->quadCount = pCVar3[bVar1].quadCounts[3];
      if (sd->quadCount != '\0') {
        sd->offset = 0x32;
        sd->zeroGTETransFlag = '\x01';
        sd->quads = (Trk_Quad *)(pCVar3[bVar1].objQuadInstanceBuf + 1);
        DrawW_kCtrlWorld_High(sd);
      }
    }
    buildList = buildList + 1;
    iVar8 = iVar8 + 1;
  } while( true );
}

/* ---- DrawW_WorldSetUpMatrix__FP10matrixtdefP6MATRIX  [DRAWW.CPP:1663-1670] SLD-VERIFIED ---- */
void DrawW_WorldSetUpMatrix(matrixtdef *m,MATRIX *mat)

{
  int r0;
  int r1;
  int iVar1;
  int iVar2;
  int r2;
  
  r0 = m->m[0];
  iVar1 = m->m[3];
  iVar2 = m->m[6];
  mat->m[0][0] = (short)nfs4_mips_sra_s32(r0,4);
  mat->m[0][1] = (short)nfs4_mips_sra_s32(iVar1,4);
  mat->m[0][2] = (short)nfs4_mips_sra_s32(iVar2,4);
  iVar1 = m->m[4];
  iVar2 = m->m[7];
  mat->m[1][0] = (short)nfs4_mips_sra_s32(m->m[1],4);
  mat->m[1][1] = (short)nfs4_mips_sra_s32(iVar1,4);
  mat->m[1][2] = (short)nfs4_mips_sra_s32(iVar2,4);
  iVar1 = m->m[5];
  iVar2 = m->m[8];
  mat->m[2][0] = (short)nfs4_mips_sra_s32(m->m[2],4);
  mat->m[2][1] = (short)nfs4_mips_sra_s32(iVar1,4);
  mat->m[2][2] = (short)nfs4_mips_sra_s32(iVar2,4);
gte_SetRotMatrix(mat);
  return;
}

/* ---- DrawW_WorldSetUpTranslation__FP8coorddefP6MATRIX  [DRAWW.CPP:1674-1684] SLD-VERIFIED ---- */
void DrawW_WorldSetUpTranslation(coorddef *t,MATRIX *mat)

{
  int tx;
  int ty;
  int iVar1;
  int iVar2;
  int tz;
  
  tx = t->x;
  iVar1 = t->y;
  iVar2 = t->z;
  mat->t[0] = nfs4_mips_sra_s32(tx,10);
  mat->t[1] = nfs4_mips_sra_s32(iVar1,10);
  mat->t[2] = nfs4_mips_sra_s32(iVar2,10);
gte_SetTransMatrix(mat);
  return;
}

/* ---- DrawW_ResetAnimationTimer__Fv  [DRAWW.CPP:1698-1700] SLD-VERIFIED ---- */
void DrawW_ResetAnimationTimer(void)

{
  int *piVar1;
  int i;
  
  i = 0xb;
  piVar1 = animation_timer + 0xb;
  do {
    *piVar1 = 0;
    i = i + -1;
    piVar1 = piVar1 + -1;
  } while (-1 < i);
  return;
}

/* ---- DrawW_GetAnimationTime__FP15Trk_AnimateInst  [DRAWW.CPP:1704-1716] SLD-VERIFIED ---- */
int DrawW_GetAnimationTime(Trk_AnimateInst *animInst)

{
  int track;
  int iVar1;
  int iVar2;
  int maxTick;
  
  if (((animInst->objectIndex != '\0') && (GameSetup_gData.track != 3)) &&
     (GameSetup_gData.track != 7)) {
    iVar1 = (animInst->count + -2) * (int)animInst->interval;
    iVar2 = animation_timer[animInst->objectIndex - 1];
    if (iVar1 <= animation_timer[animInst->objectIndex - 1]) {
      iVar2 = iVar1;
    }
    return iVar2;
  }
  return simGlobal.gameTicks;
}

/* ---- DrawW_SetAnimationTime__FP15Trk_AnimateInstPii  [DRAWW.CPP:1721-1779] SLD-VERIFIED ---- */
void DrawW_SetAnimationTime(Trk_AnimateInst *animInst,int *table,int time)

{
  int objIndex;
  int iVar1;
  int *piVar2;
  int iVar3;
  int slice;
  int iVar4;
  Car_tObj **ppCVar5;
  int i;
  int iVar6;
  
  iVar1 = Cars_gNumHumanRaceCars;
  iVar3 = animInst->objectIndex - 1;
  if (animation_timer[iVar3] < 0xf01) {
    piVar2 = animation_timer + iVar3;
    iVar6 = 0;
    if (0 < *piVar2) {
      *piVar2 = *piVar2 + 1;
      return;
    }
    ppCVar5 = Cars_gHumanRaceCarList;
    for (; iVar6 < iVar1; iVar6 = iVar6 + 1) {
      iVar4 = (int)((*ppCVar5)->N).simRoadInfo.slice;
      if ((table[iVar3 * 2] <= iVar4) && (iVar4 <= (table + iVar3 * 2)[1])) {
        *piVar2 = *piVar2 + 1;
      }
      ppCVar5 = ppCVar5 + 1;
    }
  }
  else {
    ppCVar5 = Cars_gHumanRaceCarList;
    for (iVar6 = 0; iVar6 < iVar1; iVar6 = iVar6 + 1) {
      iVar4 = (int)((*ppCVar5)->N).simRoadInfo.slice;
      if ((iVar4 < table[iVar3 * 2]) || ((table + iVar3 * 2)[1] < iVar4)) {
        animation_timer[iVar3] = 0;
      }
      ppCVar5 = ppCVar5 + 1;
    }
  }
  return;
}

/* ---- DrawW_DoObjectAnimations__Fv  [DRAWW.CPP:1784-1805] SLD-VERIFIED ---- */
void DrawW_DoObjectAnimations(void)

{
  int time_00;
  int track;
  Trk_AnimateInst **ppTVar1;
  int i;
  int iVar2;
  int *trackPtr;
  int (*table) [2];
  int time;
  
  time_00 = simGlobal.gameTicks;
  if (GameSetup_gData.track == 0) {
    table = trk0;
  }
  else {
    if (GameSetup_gData.track != 4) {
      return;
    }
    table = trk4;
  }
  iVar2 = 0;
  ppTVar1 = Anim_gInstanceFromIndex;
  do {
    if ((*ppTVar1)->objectIndex != '\0') {
      DrawW_SetAnimationTime(*ppTVar1,*table,time_00);
    }
    iVar2 = iVar2 + 1;
    ppTVar1 = ppTVar1 + 1;
  } while (iVar2 < 0x10);
  return;
}

/* ---- DrawW_BuildObjectFacets__FP13DRender_tViewP15ChunkObjectInfo  [DRAWW.CPP:1909-2048] SLD-VERIFIED ---- */
int DrawW_BuildObjectFacets(DRender_tView *Vi,ChunkObjectInfo *gObjInfo)

{
  Group * group;
  u_char bVar1;
  Group *pThis;
  int iVar2;
  void *pvVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  Trk_SimpleInst *objInstance;
  Trk_AnimateInst *animInst;
  Trk_ObjectDef *objDef;
  Trk_ObjectDef *objDef_00;
  int objectOffset;
  int iVar8;
  int objectIndex;
  int iVar9;
  int totalCount;
  int iVar10;
  int zClipSq;
  int iVar11;
  Draw_DCache *sd;
  matrixtdef matrix;
  coorddef cp;
  coorddef pt2;
  int groupNumElements;
  int offset;
  int doFrustumClip;
  short *visList;
  
  iVar10 = 0;
  animInst = (Trk_AnimateInst *)(gObjInfo->objInstanceBuf + 1);
  iVar2 = gObjInfo->objInstanceBuf->m_num_elements;
  if (iVar2 == 0) {
    iVar10 = 0;
  }
  else {
    iVar6 = gObjInfo->offset;
    iVar7 = gObjInfo->doFrustumClip;
    iVar11 = gObjInfo->zClipSq;
    psVar5 = gObjInfo->visList;
    Render_gWorldMat.t[2] = 0;
    Render_gWorldMat.t[1] = 0;
    Render_gWorldMat.t[0] = 0;
gte_SetTransMatrix(&Render_gWorldMat);
    for (iVar9 = 0; iVar9 < iVar2; iVar9 = iVar9 + 1) {
      if ((psVar5 == (short *)0x0) || ((((u_short)psVar5[iVar9] >> 0xc ^ 1) & 1) == 0)) {
        iVar8 = iVar6;
        if (iVar6 == 0) {
          iVar8 = (int)goffsets[animInst->zoffset];
        }
        bVar1 = animInst->type;
        if (bVar1 == 1) {
          objDef_00 = Track_gObjDefs[animInst->pad];
          if (((iVar7 == 0) ||
              (ObjectClipped(Vi,(int)animInst->pad,(coorddef *)&animInst->count,
                             NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)) == 0)) &&
             ((iVar11 == -1 ||
              (iVar4 = xzsquaredist32((coorddef *)&animInst->count,&(Vi->cview).translation),
              iVar4 < iVar11)))) {
            iVar8 = DrawObjectSimple(Vi,NFSHS_WORLD_CACHE_AS(Draw_DCache),objDef_00,
                               (coorddef *)&animInst->count,iVar8);
            iVar10 = iVar10 + iVar8;
          }
        }
        else if ((1 < bVar1) && ((bVar1 == 3 || (bVar1 == 7)))) {
          Anim_GetRotPos(animInst,1,DrawW_GetAnimationTime(animInst),&cp,&matrix);
          if ((iVar11 == -1) ||
             (iVar4 = xzsquaredist32(&cp,&(Vi->cview).translation),
             iVar4 < iVar11)) {
            iVar8 = DrawObjectTransform(Vi,NFSHS_WORLD_CACHE_AS(Draw_DCache),&matrix,
                               Track_gObjDefs[animInst->pad],&cp,iVar8,-1);
            iVar10 = iVar10 + iVar8;
            if ((animInst->flags & 2) != 0) {
              pt2.x = cp.x + matrix.m[6] * -0x10;
              pt2.y = cp.y + matrix.m[7] * -0x10;
              pt2.z = cp.z + matrix.m[8] * -0x10;
              Flare_Halo2(Vi,-1,0x1e,&cp,&pt2,NFSHS_WORLD_CACHE_AS(Draw_FlareCache));
            }
          }
        }
      }
      animInst = (Trk_AnimateInst *)((u_char *)animInst + animInst->size);
    }
  }
  return iVar10;
}

/* ---- DrawW_BuildCustomObjectFacets__FP13DRender_tViewP11Draw_DCacheP13Trk_SimObjectP5Groupi  [DRAWW.CPP:2054-2151] SLD-VERIFIED ---- */
int DrawW_BuildCustomObjectFacets(DRender_tView *Vi,Draw_DCache *sd,Trk_SimObject *simObjs,Group *group,int zClipSq)

{
  Trk_CollideBoomInst * objCollideBoomInstance;
  u_int uVar1;
  u_int uVar2;
  int buildResult;
  int instData_p;
  int iVar3;
  int iVar11_emit;
  int iVar4;
  ObjectAnim *pOVar5;
  Group *pThis;
  int iVar6;
  int sx;
  int blend_x;
  int sy;
  int blend_y;
  int sz;
  int blend_z;
  int t2;
  Trk_SimpleInst *objInstance;
  u_char *groupBase_p;
  int t1;
  int objectOffset;
  int objectIndex;
  int facetCount;
  Trk_ObjectDef *objDef;
  Trk_ObjectDef *objDef_00;
  int loc_70;
  int loc_6c;
  int loc_68;
  matrixtdef matrix;
  tQuat quat;
  int totalCount;
  int groupNumElements;
  int loc_28;
  int loc_24;
  int loc_20;
  int tu6;
  u_char bVar7;
  int tp2;
  int pbVar3;
  u_char tc4;
  u_char tc5;
  void *tp1;
  
  groupBase_p = (u_char *)(group + 1);
  totalCount = 0;
  iVar6 = group->m_num_elements;
  if (iVar6 == 0) {
    totalCount = 0;
  }
  else {
    (sd->matB).t[2] = 0;
    (sd->matB).t[1] = 0;
    (sd->matB).t[0] = 0;
gte_SetTransMatrix(&CF_DVLC);
    for (facetCount = 0; facetCount < iVar6; facetCount = facetCount + 1) {
      tc5 = groupBase_p[2];
      tc4 = offsets[groupBase_p[4]];
      if ((tc5 == 5) || (tc5 == 2)) {
        objDef_00 = Track_gObjDefs[*(short *)(groupBase_p + 6)];
        if ((tc5 == 2) ||
           (Object_GetAnim(simObjs + groupBase_p[0x22]) == (ObjectAnim *)0x0)) {
          buildResult = xzsquaredist32((coorddef *)(groupBase_p + 8),&(Vi->cview).translation);
          bVar7 = 0;
          if ((zClipSq <= buildResult) ||
             ((*(char *)(groupBase_p + 2) == '\x02' &&
              (instData_p = ObjectClipped(Vi,(int)*(short *)(groupBase_p + 6),
                                            (coorddef *)(groupBase_p + 8),
                                            (Draw_tGiveShelbyMoreCache *)sd), instData_p != 0)))) {
            bVar7 = 1;
          }
          if (!(bool)bVar7) {
            nfs4_mips_copy_bytes(&quat,(void *)(groupBase_p + 0x14),8);
            Quatern_QuatToMat(&quat,&matrix);
            blend_x = (int)*(short *)(groupBase_p + 0x1c) << 8;
            blend_y = (int)*(short *)(groupBase_p + 0x1e) << 8;
            blend_z = (int)*(short *)(groupBase_p + 0x20) << 8;
            iVar3 = fixedmult(matrix.m[0],blend_x);
            iVar11_emit = fixedmult(matrix.m[3],blend_x);
            matrix.m[6] = fixedmult(matrix.m[6],blend_x);
            matrix.m[0] = iVar3;
            matrix.m[3] = iVar11_emit;
            iVar3 = fixedmult(matrix.m[1],blend_y);
            iVar4 = fixedmult(matrix.m[4],blend_y);
            matrix.m[7] = fixedmult(matrix.m[7],blend_y);
            matrix.m[1] = iVar3;
            matrix.m[4] = iVar4;
            iVar3 = fixedmult(matrix.m[2],blend_z);
            iVar4 = fixedmult(matrix.m[5],blend_z);
            matrix.m[8] = fixedmult(matrix.m[8],blend_z);
            matrix.m[2] = iVar3;
            matrix.m[5] = iVar4;
            iVar3 = DrawObjectTransform(Vi,sd,&matrix,objDef_00,(coorddef *)(groupBase_p + 8),(int)(char)tc4,
                               -1);
            totalCount = totalCount + iVar3;
          }
        }
        else {
          pOVar5 = Object_GetAnim(simObjs + groupBase_p[0x22]);
          NFS4_VCALL_PTR_PTR_INT((*pOVar5->_vf)[2].pfn,
                    (u_char *)pOVar5 + (*pOVar5->_vf)[2].delta,Vi,sd,(int)(char)tc4);
        }
      }
      groupBase_p += *(short *)groupBase_p;
    }
  }
  return totalCount;
}

/* ---- DrawObjectTransform__FP13DRender_tViewP11Draw_DCacheP10matrixtdefP13Trk_ObjectDefP8coorddefis  [DRAWW.CPP:2156-2241] SLD-VERIFIED ---- */
int DrawObjectTransform(DRender_tView *Vi,Draw_DCache *sd,matrixtdef *matrix,Trk_ObjectDef *objDef,
              coorddef *pCp,int offset,short light)

{
  MATRIX *mat_local;
  matrixtdef mattemp;
  coorddef tmp;
  coorddef tmp2;
  u_char isCullable;
  int drawResult;
  Draw_tGiveShelbyMoreCache *worldCache;
  
  worldCache = (Draw_tGiveShelbyMoreCache *)sd;
  worldCache->vertices = (CCOORD16 *)(objDef + 1);
  worldCache->quadCount = objDef->quadCount;
  isCullable = objDef->vertexCount;
  worldCache->nightFlags = 0;
  drawResult = gNight_renderNight;
  worldCache->quads = (void *)((CCOORD16 *)(objDef + 1) + isCullable);
  worldCache->offset = offset;
  worldCache->materials = Track_materials;
  if (drawResult != 0) {
    worldCache->nightFlags = 4;
    if (((Cars_gList[Vi->player]->control).lights & 6U) != 0) {
      worldCache->nightFlags = 5;
    }
    tmp.x = nfs4_mips_subu_s32(pCp->x,
        ((Camera_gInfo[Vi->player].target)->position).x);
    tmp.y = nfs4_mips_subu_s32(pCp->y,
        ((Camera_gInfo[Vi->player].target)->position).y);
    tmp.z = nfs4_mips_subu_s32(pCp->z,
        ((Camera_gInfo[Vi->player].target)->position).z);
    transform(&tmp.x,gNightMat.m,&tmp2.x);
    DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matNight);
    if (BW_gCopCarObj != (Car_tObj *)0x0) {
      worldCache->nightFlags = worldCache->nightFlags | 2;
      tmp.x = nfs4_mips_subu_s32(pCp->x,(BW_gCopCarObj->N).position.x);
      tmp.y = nfs4_mips_subu_s32(pCp->y,(BW_gCopCarObj->N).position.y);
      tmp.z = nfs4_mips_subu_s32(pCp->z,(BW_gCopCarObj->N).position.z);
      transform(&tmp.x,gCopMat.m,&tmp2.x);
      DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matCop);
    }
    (worldCache->matB).t[2] = 0;
    (worldCache->matB).t[1] = 0;
    (worldCache->matB).t[0] = 0;
gte_SetTransMatrix(&worldCache->matB);
  }
  tmp.x = nfs4_mips_subu_s32(pCp->x,(Vi->cview).translation.x);
  tmp.y = nfs4_mips_subu_s32(pCp->y,(Vi->cview).translation.y);
  tmp.z = nfs4_mips_subu_s32(pCp->z,(Vi->cview).translation.z);
  TrsProj_SetPsxTransZero();
  TrsProj_TransPt(&tmp,&tmp2);
  if (offset == -1) {
    /* 0x800C8134..0x800C8140: -1 is the midground selector, not an
       OT bias. Replace it before DrawW_DrawQuad chooses its depth scale. */
    worldCache->offset = Draw_gMidGroundOtz;
    tmp2.x = nfs4_mips_sra_s32(tmp2.x,2);
    tmp2.z = nfs4_mips_sra_s32(tmp2.z,2);
    tmp2.y = nfs4_mips_sra_s32(tmp2.y,2);
  }
  worldCache->trans.x = 0;
  worldCache->trans.y = 0;
  worldCache->trans.z = 0;
  Math_fasttransmult(matrix,&gWorldMat,&mattemp);
  mat_local = &worldCache->matB;
  DrawW_WorldSetUpMatrix(&mattemp,mat_local);
  DrawW_WorldSetUpTranslation(&tmp2,mat_local);
  worldCache->zeroGTETransFlag = 0;
  worldCache->light = light;
  DrawW_kCtrlWorld_High(worldCache);
  DrawW_WorldSetUpMatrix(&gWorldMat,mat_local);
  (worldCache->matB).t[2] = 0;
  (worldCache->matB).t[1] = 0;
  (worldCache->matB).t[0] = 0;
  /* 0x800C81C8..0x800C81DC reloads TRX/TRY/TRZ from sd->matB after
     restoring gWorldMat.  `tmp2` is only a coorddef; treating it as MATRIX
     read beyond the object and poisoned the following object's GTE state. */
gte_SetTransMatrix(&worldCache->matB);
  return (u_int)objDef->quadCount;
}

/* ---- DrawObjectSimple__FP13DRender_tViewP11Draw_DCacheP13Trk_ObjectDefP8coorddefi  [DRAWW.CPP:2261-2334] SLD-VERIFIED ---- */
int DrawObjectSimple(DRender_tView *Vi,Draw_DCache *sd,Trk_ObjectDef *objDef,coorddef *pCp,int offset)

{
  coorddef tmp;
  coorddef tmp2;
  u_char isCullable;
  int drawResult;
  Draw_tGiveShelbyMoreCache *worldCache;
  
  /* Draw_DCache is the historical parameter type, but retail offsets
     0xe0..0x107 are the extended Draw_tGiveShelbyMoreCache tail.  Typed
     fields also keep host pointers intact when pointer width changes. */
  worldCache = (Draw_tGiveShelbyMoreCache *)sd;
  worldCache->vertices = (CCOORD16 *)(objDef + 1);
  worldCache->materials = Track_materials;
  worldCache->quadCount = objDef->quadCount;
  isCullable = objDef->vertexCount;
  worldCache->nightFlags = 0;
  drawResult = gNight_renderNight;
  worldCache->quads = (void *)((CCOORD16 *)(objDef + 1) + isCullable);
  worldCache->offset = offset;
  if (drawResult != 0) {
    worldCache->nightFlags = 4;
    if (((Cars_gList[Vi->player]->control).lights & 6U) != 0) {
      worldCache->nightFlags = 5;
    }
    tmp.x = nfs4_mips_subu_s32((Vi->cview).translation.x,
        ((Camera_gInfo[Vi->player].target)->position).x);
    tmp.y = nfs4_mips_subu_s32((Vi->cview).translation.y,
        ((Camera_gInfo[Vi->player].target)->position).y);
    tmp.z = nfs4_mips_subu_s32((Vi->cview).translation.z,
        ((Camera_gInfo[Vi->player].target)->position).z);
    transform(&tmp.x,gNightMat.m,&tmp2.x);
    DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matNight);
    if (BW_gCopCarObj != (Car_tObj *)0x0) {
      worldCache->nightFlags = worldCache->nightFlags | 2;
      tmp.x = nfs4_mips_subu_s32((Vi->cview).translation.x,
          (BW_gCopCarObj->N).position.x);
      tmp.y = nfs4_mips_subu_s32((Vi->cview).translation.y,
          (BW_gCopCarObj->N).position.y);
      tmp.z = nfs4_mips_subu_s32((Vi->cview).translation.z,
          (BW_gCopCarObj->N).position.z);
      transform(&tmp.x,gCopMat.m,&tmp2.x);
      DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matCop);
    }
    (worldCache->matB).t[2] = 0;
    (worldCache->matB).t[1] = 0;
    (worldCache->matB).t[0] = 0;
gte_SetTransMatrix(&worldCache->matB);
  }
  if (offset == -1) {
    /* 0x800C8428..0x800C8434 loads 0x8013D7BC into sd+0xEC. */
    worldCache->offset = Draw_gMidGroundOtz;
    worldCache->trans.x = (short)nfs4_mips_sra_s32(
        nfs4_mips_subu_s32(pCp->x,(Vi->cview).translation.x),0xc);
    worldCache->trans.y = (short)nfs4_mips_sra_s32(
        nfs4_mips_subu_s32(pCp->y,(Vi->cview).translation.y),0xc);
    worldCache->trans.z = (short)nfs4_mips_sra_s32(
        nfs4_mips_subu_s32(pCp->z,(Vi->cview).translation.z),0xc);
  }
  else {
    worldCache->trans.x = (short)nfs4_mips_sra_s32(
        nfs4_mips_subu_s32(pCp->x,(Vi->cview).translation.x),10);
    worldCache->trans.y = (short)nfs4_mips_sra_s32(
        nfs4_mips_subu_s32(pCp->y,(Vi->cview).translation.y),10);
    worldCache->trans.z = (short)nfs4_mips_sra_s32(
        nfs4_mips_subu_s32(pCp->z,(Vi->cview).translation.z),10);
  }
  worldCache->zeroGTETransFlag = 1;
  worldCache->light = -1;
  DrawW_kCtrlWorld_High(worldCache);
  return (u_int)objDef->quadCount;
}

/* ---- DrawW_BuildChunkObjectFacets__FP13DRender_tViewP15ChunkObjectInfo  [DRAWW.CPP:2346-2649] SLD-VERIFIED ---- */
int DrawW_BuildChunkObjectFacets(DRender_tView *Vi,ChunkObjectInfo *gObjInfo)

{
  Group * instGroup;
  u_char type;
  int t2;
  u_char bVar1;
  Group *pThis;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  ObjectAnim *pOVar6;
  int iVar7;
  Trk_SimObject *pTVar8;
  int sx;
  int iVar9;
  short light;
  int sy;
  int iVar10;
  int sz;
  int iVar11;
  int t1;
  Trk_SimpleInst *objInstance;
  Trk_CollideBoomInst *extendedInst;
  Trk_ObjectDef *objDef;
  Trk_ObjectDef *objDef_00;
  int totalCount;
  int iVar13;
  int objectOffset;
  int iVar14;
  matrixtdef matrix;
  Trk_SimObject *simObjs;
  int doFrustumClip;
  int groupNumElements;
  int objectIndex;
  
  pTVar8 = gObjInfo->simObjs;
  objInstance = (Trk_SimpleInst *)(gObjInfo->objInstanceBuf + 1);
  iVar2 = gObjInfo->objInstanceBuf->m_num_elements;
  iVar7 = gObjInfo->doFrustumClip;
  iVar13 = 0;
  if (iVar2 == 0) {
    iVar13 = 0;
  }
  else {
    Render_gWorldMat.t[2] = 0;
    Render_gWorldMat.t[1] = 0;
    Render_gWorldMat.t[0] = 0;
gte_SetTransMatrix(&Render_gWorldMat);
    for (objectIndex = 0; objectIndex < iVar2; objectIndex = objectIndex + 1) {
      extendedInst = (Trk_CollideBoomInst *)objInstance;
      bVar1 = objInstance->type;
      iVar14 = (int)goffsets[objInstance->zoffset];
      if (((bVar1 & 0x80) != 0) ||
         ((((bVar1 != 5 && (iVar7 != 0)) &&
           (ObjectClipped(Vi,(int)objInstance->pad,
                          (coorddef *)&objInstance->x,
                          NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)) != 0)) &&
          (objInstance->type != '\x02'))))
      goto DrawWChunkFacets_groupNext;
      NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)->offsubdivid = 0x400;
      light = -1;
      if ((objInstance->flags & 1) == 0) {
        if (bVar1 == 2) {
          Quatern_QuatToMat((tQuat *)&extendedInst->qx,&matrix);
          iVar9 = nfs4_mips_sll_s32((int)extendedInst->sx,8);
          iVar10 = nfs4_mips_sll_s32((int)extendedInst->sy,8);
          iVar11 = nfs4_mips_sll_s32((int)extendedInst->sz,8);
          iVar4 = fixedmult(matrix.m[0],iVar9);
          iVar5 = fixedmult(matrix.m[3],iVar9);
          matrix.m[6] = fixedmult(matrix.m[6],iVar9);
          matrix.m[0] = iVar4;
          matrix.m[3] = iVar5;
          iVar4 = fixedmult(matrix.m[1],iVar10);
          iVar5 = fixedmult(matrix.m[4],iVar10);
          matrix.m[7] = fixedmult(matrix.m[7],iVar10);
          matrix.m[1] = iVar4;
          matrix.m[4] = iVar5;
          iVar4 = fixedmult(matrix.m[2],iVar11);
          iVar5 = fixedmult(matrix.m[5],iVar11);
          matrix.m[8] = fixedmult(matrix.m[8],iVar11);
          objDef_00 = Track_gObjDefs[objInstance->pad];
          light = (short)nfs4_mips_sign_extend(
              (u_int)extendedInst->simIndex |
              ((u_int)extendedInst->boomIndex << 8),16);
          matrix.m[2] = iVar4;
          matrix.m[5] = iVar5;
          goto DrawWChunkFacets_emitObj;
        }
        if (bVar1 < 3) {
          if (bVar1 == 1) {
            iVar14 = DrawObjectSimple(Vi,NFSHS_WORLD_CACHE_AS(Draw_DCache),
                                Track_gObjDefs[objInstance->pad],
                                (coorddef *)&objInstance->x,iVar14);
            iVar13 = nfs4_mips_addu_s32(iVar13,iVar14);
          }
        }
        else if (bVar1 == 5) {
          objDef_00 = Track_gObjDefs[objInstance->pad];
          pOVar6 = Object_GetAnim(pTVar8 + extendedInst->simIndex);
          if (pOVar6 == (ObjectAnim *)0x0) {
            Quatern_QuatToMat((tQuat *)&extendedInst->qx,&matrix);
            iVar9 = nfs4_mips_sll_s32((int)extendedInst->sx,8);
            iVar10 = nfs4_mips_sll_s32((int)extendedInst->sy,8);
            iVar11 = nfs4_mips_sll_s32((int)extendedInst->sz,8);
            iVar4 = fixedmult(matrix.m[0],iVar9);
            iVar5 = fixedmult(matrix.m[3],iVar9);
            matrix.m[6] = fixedmult(matrix.m[6],iVar9);
            matrix.m[0] = iVar4;
            matrix.m[3] = iVar5;
            iVar4 = fixedmult(matrix.m[1],iVar10);
            iVar5 = fixedmult(matrix.m[4],iVar10);
            matrix.m[7] = fixedmult(matrix.m[7],iVar10);
            matrix.m[1] = iVar4;
            matrix.m[4] = iVar5;
            iVar4 = fixedmult(matrix.m[2],iVar11);
            iVar5 = fixedmult(matrix.m[5],iVar11);
            matrix.m[8] = fixedmult(matrix.m[8],iVar11);
            light = -1;
            matrix.m[2] = iVar4;
            matrix.m[5] = iVar5;
            goto DrawWChunkFacets_emitObj;
          }
          pOVar6 = Object_GetAnim(pTVar8 + extendedInst->simIndex);
          NFS4_VCALL_PTR_PTR_INT((*pOVar6->_vf)[2].pfn,
                    (u_char *)pOVar6 + (*pOVar6->_vf)[2].delta,Vi,
                    NFSHS_WORLD_CACHE_AS(Draw_DCache),iVar14);
        }
        else if (bVar1 == 9) {
          xformy(&matrix,(int)extendedInst->qx);
          iVar9 = nfs4_mips_sll_s32((int)extendedInst->qz,8);
          iVar10 = nfs4_mips_sll_s32((int)extendedInst->qy,8);
          iVar4 = fixedmult(matrix.m[0],iVar9);
          iVar5 = fixedmult(matrix.m[3],iVar9);
          matrix.m[6] = fixedmult(matrix.m[6],iVar9);
          matrix.m[0] = iVar4;
          matrix.m[3] = iVar5;
          iVar4 = fixedmult(matrix.m[1],iVar10);
          iVar5 = fixedmult(matrix.m[4],iVar10);
          matrix.m[7] = fixedmult(matrix.m[7],iVar10);
          matrix.m[1] = iVar4;
          matrix.m[4] = iVar5;
          iVar4 = fixedmult(matrix.m[2],iVar9);
          iVar5 = fixedmult(matrix.m[5],iVar9);
          matrix.m[8] = fixedmult(matrix.m[8],iVar9);
          NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)->offsubdivid = 0;
          objDef_00 = Track_gObjDefs[objInstance->pad];
          light = extendedInst->qw;
          matrix.m[2] = iVar4;
          matrix.m[5] = iVar5;
          goto DrawWChunkFacets_emitObj;
        }
      }
      else {
        iVar4 = fixedatan(nfs4_mips_subu_s32(objInstance->x,(Vi->cview).translation.x),
                           nfs4_mips_subu_s32(objInstance->z,(Vi->cview).translation.z));
        fixedxformy(&matrix,iVar4);
        if (bVar1 == 9) {
          iVar9 = nfs4_mips_sll_s32((int)extendedInst->qz,8);
          iVar10 = nfs4_mips_sll_s32((int)extendedInst->qy,8);
          iVar4 = fixedmult(matrix.m[0],iVar9);
          iVar5 = fixedmult(matrix.m[3],iVar9);
          matrix.m[6] = fixedmult(matrix.m[6],iVar9);
          matrix.m[0] = iVar4;
          matrix.m[3] = iVar5;
          iVar4 = fixedmult(matrix.m[1],iVar10);
          iVar5 = fixedmult(matrix.m[4],iVar10);
          matrix.m[7] = fixedmult(matrix.m[7],iVar10);
          matrix.m[1] = iVar4;
          matrix.m[4] = iVar5;
          iVar4 = fixedmult(matrix.m[2],iVar9);
          iVar5 = fixedmult(matrix.m[5],iVar9);
          matrix.m[8] = fixedmult(matrix.m[8],iVar9);
          light = extendedInst->qw;
          NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)->offsubdivid = 0;
          matrix.m[2] = iVar4;
          matrix.m[5] = iVar5;
        }
        objDef_00 = Track_gObjDefs[objInstance->pad];
DrawWChunkFacets_emitObj:
        iVar14 = DrawObjectTransform(Vi,NFSHS_WORLD_CACHE_AS(Draw_DCache),&matrix,objDef_00,
                            (coorddef *)&objInstance->x,iVar14,light);
        iVar13 = nfs4_mips_addu_s32(iVar13,iVar14);
      }
DrawWChunkFacets_groupNext:
      objInstance = (Trk_SimpleInst *)((u_char *)objInstance + objInstance->size);
    }
  }
  return iVar13;
}

/* ---- ObjectClipped__FP13DRender_tViewiP8coorddefP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:2660-2709] SLD-VERIFIED ---- */
BOOL ObjectClipped(DRender_tView *Vi,int ind,coorddef *pCp,Draw_tGiveShelbyMoreCache *sd)

{
  tBoundingSphere * bSphere;
  int iVar1;
  int iVar2;
  coorddef tmp;
  coorddef tmp2;
  coorddef trans;
  
  bSphere = (tBoundingSphere *)(gPersistObjDefBoundingSpheres + 1) + ind;
  tmp.x = nfs4_mips_addu_s32(nfs4_mips_sll_s32((int)bSphere->cp.x,10),pCp->x);
  tmp.y = nfs4_mips_addu_s32(nfs4_mips_sll_s32((int)bSphere->cp.y,10),pCp->y);
  tmp.z = nfs4_mips_addu_s32(nfs4_mips_sll_s32((int)bSphere->cp.z,10),pCp->z);
  iVar1 = (Vi->cview).translationInv.x;
  iVar2 = (Vi->cview).translationInv.z;
  transform(&tmp.x,(Vi->cview).mrotationInv.m,&tmp2.x);
  iVar1 = nfs4_mips_addu_s32(tmp2.x,iVar1);
  iVar2 = nfs4_mips_addu_s32(tmp2.z,iVar2);
  iVar2 = nfs4_mips_addu_s32(iVar2,
      nfs4_mips_sll_s32((int)bSphere->radius,10));
  if (iVar2 < iVar1) {
    return 1;
  }
  return iVar2 < nfs4_mips_negu_s32(iVar1);
}

/* ---- DrawW_DoObjects__FP13DRender_tViewP11tBuildEntry  [DRAWW.CPP:2717-2864] SLD-VERIFIED ---- */
void DrawW_DoObjects(DRender_tView *Vi,tBuildEntry *buildList)

{
  short sVar1;
  int iVar2;
  Chunk *pCVar3;
  Group *pGVar4;
  int chunkInd;
  int geomRez;
  Chunk *chunkDat;
  Trk_SimObject *simObjs;
  int buildInd;
  int iVar5;
  int thisChunkInd;
  int iVar6;
  Draw_DCache *sd;
  int chunkCount;
  
  iVar2 = BWorld_gChunkCount;
  iVar6 = gCurrContext->currentChunk;
  NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)->artInfo = &gInitialArt;
  gVi = Vi;
  for (iVar5 = 0; pCVar3 = Track_chunkList, iVar5 < iVar2; iVar5 = iVar5 + 1) {
    if ((buildList->enableBits & 2U) != 0) {
      sVar1 = buildList->chunkInd;
      pGVar4 = Track_chunkList[sVar1].simObjBuf;
      geomRez = (int)buildList->geomRez;
      if (Track_chunkList[sVar1].objInstanceBuf != (Group *)0x0) {
        NFSHS_WORLD_CACHE_AS(Draw_DCache)->doublelayer = 1;
        gChunkObjInfo.objInstanceBuf = Track_chunkList[sVar1].objInstanceBuf;
        gChunkObjInfo.doFrustumClip = (int)(geomRez == 4);
        gChunkObjInfo.simObjs = (Trk_SimObject *)(pGVar4 + 1);
        gWSavePtr = (intptr)SetSp(getScratchAddr(0xff));
        stackSpeedUpEnbabledFlag = 1;
        DrawW_BuildChunkObjectFacets(gVi,&gChunkObjInfo);
        gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
        stackSpeedUpEnbabledFlag = 0;
      }
      if (((GameSetup_gData.Time == 0) && (GameSetup_gData.Weather == 0)) &&
         (pCVar3[sVar1].objSpecialInstanceBuf != (Group *)0x0)) {
        NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)->offsubdivid = 0x400;
        NFSHS_WORLD_CACHE_AS(Draw_DCache)->doublelayer = 0;
        gChunkObjInfo.visList = (short *)0x0;
        gChunkObjInfo.objInstanceBuf = pCVar3[sVar1].objSpecialInstanceBuf;
        gChunkObjInfo.zClipSq = -1;
        gChunkObjInfo.offset = 0x32;
        gChunkObjInfo.doFrustumClip = 1;
        gChunkObjInfo.simObjs = (Trk_SimObject *)(pGVar4 + 1);
        DrawW_BuildObjectFacets(gVi,&gChunkObjInfo);
      }
    }
    buildList = buildList + 1;
  }
  NFSHS_WORLD_CACHE_AS(Draw_DCache)->doublelayer = 0;
  NFSHS_WORLD_CACHE_AS(Draw_tGiveShelbyMoreCache)->offsubdivid = 0x400;
  if (gPersistObjInst != (Group *)0x0) {
    if (((GameSetup_gData.track != 4) ||
        (((0x27 < iVar6 - 1U && (0x1d < iVar6 - 0x3dU)) && (8 < iVar6 - 0x6cU)))) &&
       ((GameSetup_gData.track != 0 ||
        (((0x34 < iVar6 - 1U && (0x1b < iVar6 - 0x44U)) && (0x13 < iVar6 - 0x6cU)))))) {
      gChunkObjInfo.objInstanceBuf = gPersistObjInst;
      gChunkObjInfo.simObjs = (Trk_SimObject *)0x0;
      gChunkObjInfo.offset = 0x7d;
      gChunkObjInfo.doFrustumClip = 1;
      gChunkObjInfo.zClipSq = gCurrContext->polyFarZClipSq;
      gChunkObjInfo.visList = (short *)0x0;
      gWSavePtr = (intptr)SetSp(getScratchAddr(0xff));
      stackSpeedUpEnbabledFlag = 1;
      DrawW_BuildObjectFacets(gVi,&gChunkObjInfo);
      gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
      stackSpeedUpEnbabledFlag = 0;
    }
  }
  if (gPersistMidgroundObjInst != (Group *)0x0) {
    gChunkObjInfo.simObjs = (Trk_SimObject *)0x0;
    gChunkObjInfo.objInstanceBuf = gPersistMidgroundObjInst;
    gChunkObjInfo.zClipSq = -1;
    gChunkObjInfo.offset = -1;
    gChunkObjInfo.doFrustumClip = 1;
    /* 0x800C8F88: sll v1,s5,6; 0x800C8F90 adds the byte offset.
       The visibility row stride is 64 bytes = 32 shorts. */
    gChunkObjInfo.visList = Track_gInViewList + iVar6 * 32;
    gWSavePtr = (intptr)SetSp(getScratchAddr(0xff));
    stackSpeedUpEnbabledFlag = 1;
    DrawW_BuildObjectFacets(gVi,&gChunkObjInfo);
    gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
    stackSpeedUpEnbabledFlag = 0;
  }
  if ((Object_customObjInst != (Group *)0x0) && (0 < Object_customObjInst->m_num_elements)) {
    DrawW_BuildCustomObjectFacets(Vi,NFSHS_WORLD_CACHE_AS(Draw_DCache),(Trk_SimObject *)(Object_customSimObjs + 1),
               Object_customObjInst,gCurrContext->polyFarZClipSq);
  }
  return;
}

/* ---- Draw_CircleClip__FP8coorddefT0i  [DRAWW.CPP:2888-2896] SLD-VERIFIED ---- */
int Draw_CircleClip(coorddef *pt1,coorddef *pt2,int r)

{
  int dist;
  int dz;
  int iVar1;
  int iVar2;
  int dx;
  
  dz = pt1->x;
  iVar2 = dz - pt2->x;
  if (iVar2 < 1) {
    iVar2 = pt2->x - dz;
  }
  iVar1 = pt1->z - pt2->z;
  if (iVar1 < 1) {
    iVar1 = pt2->z - pt1->z;
  }
  if (iVar1 < iVar2) {
    iVar2 = iVar2 + (iVar1 >> 2);
  }
  else {
    iVar2 = iVar1 + (iVar2 >> 2);
  }
  return (u_int)(iVar2 < r);
}

/* ---- Draw_kCtrlSkidmark__FP18Draw_tCtrlSkidmark  [DRAWW.CPP:2900-3038] SLD-VERIFIED ---- */
void Draw_kCtrlSkidmark(Draw_tCtrlSkidmark *fskid)

{
  int r0;
  int r1;
  int r2;
  u_long l1;
  u_long l0;
  int skidChunk_p;
  int vert_count;
  int vert_idx;
  u_long l2;
  u_long l3;
  POLY_GT4 *prim;
  POLY_GT4 *primPtr;
  Draw_tPixMap *pmx;
  int type;
  int color_pack;
  int save_pre_otz;
  int vt_y;
  int depth_offset;
  int i;
  int depth_skid;
  int count;
  Draw_DCache *sd;
  Skidmark_Chunk *sm;
  matrixtdef *m;
  int ccount;
  int ccount_local;
  coorddef *t;
  coorddef td;
  coorddef ts;
  int ti2;
  u_char bVar2;
  int ti3;
  
  ccount_local = fskid->count;
  l2 = (fskid->m).m[3];
  Render_gWorldMat.m[0][0] = (short)nfs4_mips_sra_s32((fskid->m).m[0],4);
  Render_gWorldMat.m[0][1] = (short)nfs4_mips_sra_s32((int)l2,4);
  Render_gWorldMat.m[0][2] = (short)nfs4_mips_sra_s32((fskid->m).m[6],4);
  Render_gWorldMat.m[1][0] = (short)nfs4_mips_sra_s32((fskid->m).m[1],4);
  Render_gWorldMat.m[1][1] = (short)nfs4_mips_sra_s32((fskid->m).m[4],4);
  Render_gWorldMat.m[1][2] = (short)nfs4_mips_sra_s32((fskid->m).m[7],4);
  Render_gWorldMat.m[2][0] = (short)nfs4_mips_sra_s32((fskid->m).m[2],4);
  Render_gWorldMat.m[2][1] = (short)nfs4_mips_sra_s32((fskid->m).m[5],4);
  Render_gWorldMat.m[2][2] = (short)nfs4_mips_sra_s32((fskid->m).m[8],4);
  do {
    do {
      ccount_local = nfs4_mips_addu_s32(ccount_local,-1);
      if (ccount_local == -1) {
        return;
      }
      sm = &fskid->smp[ccount_local];
      bVar2 = false;
      skidChunk_p = (int)BWorld_IsSliceInBuildList((int)sm->slice);
      if (skidChunk_p != 0) {
        vert_count = Draw_CircleClip(&sm->cp,&fskid->t,0x320000);
        bVar2 = vert_count != 0;
      }
    } while (!(bool)bVar2);
    ts.x = nfs4_mips_subu_s32(sm->cp.x,(fskid->t).x);
    ts.y = nfs4_mips_subu_s32(sm->cp.y,(fskid->t).y);
    ts.z = nfs4_mips_subu_s32(sm->cp.z,(fskid->t).z);
    transform(&ts.x,(fskid->m).m,&td.x);
    Render_gWorldMat.t[0] = nfs4_mips_sra_s32(td.x,6);
    Render_gWorldMat.t[1] = nfs4_mips_sra_s32(td.y,6);
    Render_gWorldMat.t[2] = nfs4_mips_sra_s32(td.z,6);
gte_SetRotMatrix(&Render_gWorldMat);
gte_SetTransMatrix(&Render_gWorldMat);
    ti2 = sm->n;
    for (depth_skid = 0; depth_skid < (short)ti2; depth_skid = depth_skid + 1) {
      Skidmark_Segment *seg = &sm->seg[depth_skid];
      if ((Render_gPacketPtr < Render_gPacketEnd) && (seg->next != 0)) {
gte_lwc2(0,*(int *)&seg->svx[0]);
        gte_lwc2(1,*(int *)((u_char *)&seg->svx[0] + 4));
        gte_rtps();
gte_swc2(0x19,PSYQ_SCRATCH_BYTES(0x098));
        gte_swc2(0x1a,PSYQ_SCRATCH_BYTES(0x09c));
        gte_swc2(0x1b,PSYQ_SCRATCH_BYTES(0x0a0));
        primPtr = (POLY_GT4 *)Render_gPacketPtr;
        /* MIPS 0x800C92E0..0x800C92F0 loads the pointer stored at
           scratch+4 (Render_gPacketPtr) and writes SXY2 at packet+8. */
gte_swc2(0xe,(char *)primPtr + 8);
gte_lwc2(0,*(int *)&seg->svx[1]);
        gte_lwc2(1,*(int *)((u_char *)&seg->svx[1] + 4));
        gte_rtps();
gte_swc2(0x19,PSYQ_SCRATCH_BYTES(0x0a8));
        gte_swc2(0x1a,PSYQ_SCRATCH_BYTES(0x0ac));
        gte_swc2(0x1b,PSYQ_SCRATCH_BYTES(0x0b0));
gte_lwc2(0,*(int *)((char *)&seg->next->svx[1]));
gte_lwc2(1,*(int *)((char *)&seg->next->svx[1] + 4));
        gte_rtps();
gte_swc2(0x19,PSYQ_SCRATCH_BYTES(0x0b8));
        gte_swc2(0x1a,PSYQ_SCRATCH_BYTES(0x0bc));
        gte_swc2(0x1b,PSYQ_SCRATCH_BYTES(0x0c0));
gte_lwc2(0,*(int *)((char *)&seg->next->svx[0]));
gte_lwc2(1,*(int *)((char *)&seg->next->svx[0] + 4));
        gte_rtps();
gte_swc2(0x19,PSYQ_SCRATCH_BYTES(0x0c8));
        gte_swc2(0x1a,PSYQ_SCRATCH_BYTES(0x0cc));
        gte_swc2(0x1b,PSYQ_SCRATCH_BYTES(0x0d0));
        /* 0x800C9378..0x800C9430 reads the four MAC1/MAC3 pairs just
           stored at scratch+98/A8/B8/C8, not independent BSS globals. */
        const int *cam = (const int *)getScratchAddr(0x98 / 4);
        if ((cam[0] < cam[2] || cam[4] < cam[6] ||
             cam[8] < cam[10] || cam[12] < cam[14]) &&
            (nfs4_mips_negu_s32(cam[0]) < cam[2] ||
             nfs4_mips_negu_s32(cam[4]) < cam[6] ||
             nfs4_mips_negu_s32(cam[8]) < cam[10] ||
             nfs4_mips_negu_s32(cam[12]) < cam[14])) {
          color_pack = seg->type;
          pmx = gSkidMarkPixmap[color_pack & 1];
          /* 0x800C9440..0x800C9468 keeps a2 = packet (loaded at
             0x800C92E4); SXY stores must not overwrite the GTE matrix. */
          gte_swc2(0xc,(char *)primPtr + 0x14);
          gte_swc2(0xd,(char *)primPtr + 0x2c);
          gte_swc2(0xe,(char *)primPtr + 0x20);
          gte_avsz4();
gte_swc2(0x7,PSYQ_SCRATCH_BYTES(0x094));
          vt_y = nfs4_mips_sra_s32(Skid_gCtrlScratch_94,5);
          Skid_gCtrlScratch_94 = nfs4_mips_addu_s32(vt_y,0x32);
          if (Skid_gCtrlScratch_94 < 1) {
            return;
          }
          if (nfs4_mips_addu_s32(Draw_gViewOtSize,-3) < Skid_gCtrlScratch_94) {
            return;
          }
          if (color_pack == 0) {
            nfs4_mips_copy_bytes(&primPtr->r0,&seg->rgb,4);
            nfs4_mips_copy_bytes(&primPtr->r1,&seg->rgb,4);
            nfs4_mips_copy_bytes(&primPtr->r3,&seg->next->rgb,4);
            nfs4_mips_copy_bytes(&primPtr->r2,&seg->next->rgb,4);
          }
          else {
            const u_int gray = 0x00404040;
            nfs4_mips_copy_bytes(&primPtr->r0,&gray,4);
            nfs4_mips_copy_bytes(&primPtr->r1,&gray,4);
            nfs4_mips_copy_bytes(&primPtr->r3,&gray,4);
            nfs4_mips_copy_bytes(&primPtr->r2,&gray,4);
          }
          primPtr->code = 0x3e;
          ((u_char *)&primPtr->tag)[3] = 0xc;
          nfs4_mips_copy_bytes(&primPtr->u0,&pmx->u0,4);
          nfs4_mips_copy_bytes(&primPtr->u1,&pmx->u1,4);
          nfs4_mips_copy_bytes(&primPtr->u2,&pmx->u2,4);
          nfs4_mips_copy_bytes(&primPtr->u3,&pmx->u3,4);
          if ((short)primPtr->clut == -1) {
            vert_idx = nfs4_mips_sra_s32(
                nfs4_mips_sll_s32(
                    nfs4_mips_subu_s32(vt_y,*(short *)getScratchAddr(0xdc / 4)),4),
                ((u_short *)getScratchAddr(0xdc / 4))[1] & 0x1f);
            if (vert_idx < 0) {
              vert_idx = 0;
            }
            else if (0xf < vert_idx) {
              vert_idx = 0xf;
            }
            primPtr->clut = gClutDepth[pmx->pad2][vert_idx];
          }
          ti3 = Skid_gCtrlScratch_94;
          *(u_int *)Render_gPacketPtr = 0x0c000000;
          AddPrim(Render_gPalettePtr + Skid_gCtrlScratch_94 * 4,Render_gPacketPtr);
          Render_gPacketPtr += 0x34;
        }
      }
    }
  } while( true );
}

/* ---- DrawW_SetUpSubdividFacet_Line__FP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:3049-3103] SLD-VERIFIED ---- */
void DrawW_SetUpSubdividFacet_Line(Draw_tGiveShelbyMoreCache *sd)

{
  POLY_GT4 * prim;
  u_char tpage_byte;
  u_short a;
  u_char tu8;
  u_char tu9;
  u_char tu10;
  u_short d;
  u_short b;
  u_char tu12;
  u_char tu13;
  u_char uVar1;
  u_char tu14;
  u_short c;
  Draw_SVertex *v2;
  Draw_SVertex *v3;
  Draw_SVertex *v1;
  Draw_SVertex *v0;
  int loc_28;
  int loc_24;
  int loc_20;
  short ts1;
  short ts3;
  short ts4;
  short ts2;
  short ts5;
  short ts6;
  
  DrawW_LoadPrecVECTOR(&sd->v0,&sd->tVn0);
  DrawW_LoadPrecVECTOR(&sd->v1,&sd->tVn1);
  DrawW_LoadPrecVECTOR(&sd->v2,&sd->tVn2);
  DrawW_LoadPrecVECTOR(&sd->v3,&sd->tVn3);
gte_lwc2(0,*(int *)(((char *)sd + 0x14c)));
  gte_lwc2(1,*(int *)(((char *)sd + 0x150)));
  gte_rtps();
gte_swc2(0xe,((char *)sd + 0x154));
gte_lwc2(0,*(int *)(((char *)sd + 0x15c)));
  gte_lwc2(1,*(int *)(((char *)sd + 0x160)));
  gte_lwc2(2,*(int *)(((char *)sd + 0x16c)));
  gte_lwc2(3,*(int *)(((char *)sd + 0x170)));
  gte_lwc2(4,*(int *)(((char *)sd + 0x17c)));
  gte_lwc2(5,*(int *)(((char *)sd + 0x180)));
  gte_rtpt();
  tpage_byte = (sd->GT4Prim).r1;
  tu8 = (sd->GT4Prim).g1;
  tu9 = (sd->GT4Prim).b1;
  tu10 = (sd->GT4Prim).p1;
  uVar1 = (sd->GT4Prim).r0;
  tu12 = (sd->GT4Prim).g0;
  tu13 = (sd->GT4Prim).b0;
  tu14 = (sd->GT4Prim).code;
  (sd->v2).r = tpage_byte;
  (sd->v2).g = tu8;
  (sd->v2).b = tu9;
  (sd->v2).a = tu10;
  (sd->v1).r = tpage_byte;
  (sd->v1).g = tu8;
  (sd->v1).b = tu9;
  (sd->v1).a = tu10;
  (sd->v3).r = uVar1;
  (sd->v3).g = tu12;
  (sd->v3).b = tu13;
  (sd->v3).a = tu14;
  (sd->v0).r = uVar1;
  (sd->v0).g = tu12;
  (sd->v0).b = tu13;
  (sd->v0).a = tu14;
gte_swc2(0xc,((char *)sd + 0x164));
  gte_swc2(0xd,((char *)sd + 0x174));
  gte_swc2(0xe,((char *)sd + 0x184));
  (sd->v0).u = (sd->GT4Prim).u0;
  (sd->v0).v = (sd->GT4Prim).v0;
  (sd->v1).u = (sd->GT4Prim).u1;
  (sd->v1).v = (sd->GT4Prim).v1;
  (sd->v2).u = (sd->GT4Prim).u3;
  (sd->v2).v = (sd->GT4Prim).v3;
  (sd->v3).u = (sd->GT4Prim).u2;
  (sd->v3).v = (sd->GT4Prim).v2;
  ts1 = (sd->v0).dvx;
  (sd->v0).a = '\0';
  if (ts1 < 0x3e9) {
    ts2 = (sd->v0).dvy;
    if ((((1000 < ts2) || (ts1 < -1000)) || (ts2 < -1000)) || ((sd->v0).vz < 0x65))
    goto DrW_SubSetupLine_v0Alpha;
  }
  else {
DrW_SubSetupLine_v0Alpha:
    (sd->v0).a = '\x01';
  }
  ts3 = (sd->v1).dvx;
  (sd->v1).a = '\0';
  if (ts3 < 0x3e9) {
    ts4 = (sd->v1).dvy;
    if (((1000 < ts4) || (ts3 < -1000)) || ((ts4 < -1000 || ((sd->v1).vz < 0x65))))
    goto DrW_SubSetupLine_v1Alpha;
  }
  else {
DrW_SubSetupLine_v1Alpha:
    (sd->v1).a = '\x01';
  }
  ts5 = (sd->v2).dvx;
  (sd->v2).a = '\0';
  if (ts5 < 0x3e9) {
    ts6 = (sd->v2).dvy;
    if (((1000 < ts6) || (ts5 < -1000)) || ((ts6 < -1000 || ((sd->v2).vz < 0x65))))
    goto DrW_SubSetupLine_v2Alpha;
  }
  else {
DrW_SubSetupLine_v2Alpha:
    (sd->v2).a = '\x01';
  }
  ts5 = (sd->v3).dvx;
  (sd->v3).a = '\0';
  if (ts5 < 0x3e9) {
    ts6 = (sd->v3).dvy;
    if ((((ts6 < 0x3e9) && (-0x3e9 < ts5)) && (-0x3e9 < ts6)) && (100 < (sd->v3).vz))
    goto DrW_SubSetupLine_callSubdiv;
  }
  (sd->v3).a = '\x01';
DrW_SubSetupLine_callSubdiv:
  DrawW_SubdividFacet(sd,0,&sd->v0,&sd->v1,&sd->v2,&sd->v3,0,0);
  return;
}

/* ---- DrawW_OnyxLinePrim__FP8CCOORD16P8Trk_LineiP25Draw_tGiveShelbyMoreCache  [DRAWW.CPP:3108-3330] SLD-VERIFIED ---- */
void DrawW_OnyxLinePrim(CCOORD16 *geomVertices,Trk_Line *lineQuad,int count,Draw_tGiveShelbyMoreCache *sd)

{
  int linetype;
  int t1;
  int t2;
  long b;
  u_long l3;
  VECTOR temp0;
  u_long l0;
  int ot_addr_pack;
  int CVar19;
  int vert_iter;
  CVECTOR *tC8;
  int color_pack;
  u_long l1;
  int depth_avg;
  int CVar23;
  int uVar8_00;
  u_long l2;
  u_int uVar1;
  int depth_index;
  u_int uVar2;
  int tpage_word;
  int vert_y_pack;
  int v0_pack;
  int vert_x_pack;
  int ti9;
  POLY_GT4 *prim;
  Draw_tPixMap *pmx;
  int save_pre_otz;
  int save_pre_otz_l;
  int lineQuadCount;
  int lineIdx;
  CCOORD16 vt0;
  CCOORD16 vt1;
  CCOORD16 vt2;
  CCOORD16 vt3;
  CVECTOR a;
  long bfct;
  int depthcue;
  int loc_30;
  int doSubdivision;
  u_char *tp17;
  void *tp1;
  int tp4;
  int tp5;
  CCOORD16 *tC6;
  int tu1;
  int tp3;
  int tp2;
  u_char *tp6;
  u_int tu2;
  u_int tu4;
  int lineLimit;
  intptr previousStack;
  int positiveSideVisible;
  int negativeSideVisible;
  
  sd->offsubdivid = 0x200;
  lineLimit = nfs4_mips_addu_s32(count,-1);
  for (lineIdx = 0; tC6 = geomVertices, lineIdx < lineLimit;
       lineIdx = nfs4_mips_addu_s32(lineIdx,1)) {
    for (; lineIdx < lineLimit && (lineQuad->type != 0xff);
        lineQuad = lineQuad + 1) {
      /* gDLPixmap is a table of Draw_tPixMap pointers.  The recovered source
         used the address of the table slot itself, turning pointer bytes into
         UV/CLUT/TPAGE data (notably 0x005e:0x005e blue line artifacts). */
      pmx = gDLPixmap[lineQuad->type];
      /* Original 0x800C9950..0x800C999C loads the four line-corner
         CCOORD16s in winding order 3,1,0,2.  The recovered source had lost
         the first two assignments entirely, so vt0/vt1 contained stack
         garbage and near-line subdivision covered the screen. */
      vt0 = geomVertices[3];
      vt1 = geomVertices[1];
      vt2 = geomVertices[0];
      vt3 = geomVertices[2];
      v0_pack = count;
gte_lwc2(0,*(int *)(&vt0));
      gte_lwc2(1,*(int *)(((char *)&vt0 + 0x4)));
      gte_rtps();
gte_swc2(0x19,((char *)sd + 0x98));
      gte_swc2(0x1a,((char *)sd + 0x9c));
      gte_swc2(0x1b,((char *)sd + 0xa0));
      tp17 = (u_char *)sd->head.cprim.PrimPtr;
      /* Original 0x800C99C8 loads the packet pointer stored at scratchpad
         +4, then 0x800C99D8 stores SXY2 to packet+8.  The decompiler lost
         that indirection and incorrectly treated +8 as a scratch address. */
gte_swc2(0xe,tp17 + 0x08);
gte_lwc2(0,*(int *)(&vt1));
      gte_lwc2(1,*(int *)(((char *)&vt1 + 0x4)));
      gte_rtps();
gte_swc2(0x19,((char *)sd + 0xa8));
      gte_swc2(0x1a,((char *)sd + 0xac));
      gte_swc2(0x1b,((char *)sd + 0xb0));
gte_lwc2(0,*(int *)(&vt2));
      gte_lwc2(1,*(int *)(((char *)&vt2 + 0x4)));
      gte_rtps();
gte_swc2(0x19,((char *)sd + 0xb8));
      gte_swc2(0x1a,((char *)sd + 0xbc));
      gte_swc2(0x1b,((char *)sd + 0xc0));
gte_lwc2(0,*(int *)(&vt3));
      gte_lwc2(1,*(int *)(((char *)&vt3 + 0x4)));
      gte_rtps();
gte_swc2(0x19,((char *)sd + 0xc8));
      gte_swc2(0x1a,((char *)sd + 0xcc));
gte_swc2(0x1b,((char *)sd + 0xd0));
      positiveSideVisible =
          (sd->tVn0).vx < (sd->tVn0).vz || (sd->tVn1).vx < (sd->tVn1).vz ||
          (sd->tVn2).vx < (sd->tVn2).vz || (sd->tVn3).vx < (sd->tVn3).vz;
      negativeSideVisible =
          nfs4_mips_negu_s32((sd->tVn0).vx) < (sd->tVn0).vz ||
          nfs4_mips_negu_s32((sd->tVn1).vx) < (sd->tVn1).vz ||
          nfs4_mips_negu_s32((sd->tVn2).vx) < (sd->tVn2).vz ||
          nfs4_mips_negu_s32((sd->tVn3).vx) < (sd->tVn3).vz;
      if (positiveSideVisible && negativeSideVisible) {
        /* SXY FIFO after the remaining three RTPS operations.  These stores
           target the tentative GT4 packet, not scratchpad offsets. */
        gte_swc2(0xc,tp17 + 0x14);
        gte_swc2(0xd,tp17 + 0x2c);
        gte_swc2(0xe,tp17 + 0x20);
        gte_avsz4();
gte_swc2(0x7,&sd->otz);
        gte_nclip();
gte_swc2(0x18,&bfct);
        if ((sd->head).mirror == 1) {
          bfct = (long)nfs4_mips_negu_s32((int)bfct);
        }
        if (-1 < bfct) {
          save_pre_otz_l = nfs4_mips_sra_s32(sd->otz,1);
          depth_avg = nfs4_mips_addu_s32(save_pre_otz_l,0x4b);
          ot_addr_pack = (int)(sd->otz < 200);
          sd->otz = depth_avg;
          if ((0 < depth_avg) && (depth_avg <= Draw_gViewOtSize + -3)) {
            if (ot_addr_pack == 0) {
              prim = (POLY_GT4 *)(sd->head).cprim.PrimPtr;
              (sd->head).cprim.PrimPtr = (char *)(prim + 1);
              *(u_int *)prim = 0x0c000000;
              AddPrim((sd->head).cprim.LastPrim + sd->otz,prim);
            }
            else {
              prim = &sd->GT4Prim;
            }
            tpage_word = ot_addr_pack;
gte_swc2(0x8,&depthcue);
            if (sd->nightFlags == 0) {
              nfs4_mips_copy_bytes(&a,Chunk_lightTable + vt3.light,4);
              gte_lwc2(6,*(int *)&a);
              gte_ldIR0(depthcue);
              gte_dpcs();
              gte_swc2(0x16,&prim->r2);
              nfs4_mips_copy_bytes(&prim->r0,&prim->r2,4);

              nfs4_mips_copy_bytes(&a,Chunk_lightTable + vt2.light,4);
              gte_lwc2(6,*(int *)&a);
              gte_ldIR0(depthcue);
              gte_dpcs();
              gte_swc2(0x16,&prim->r3);
              nfs4_mips_copy_bytes(&prim->r1,&prim->r3,4);
            }
            else {
              if ((sd->nightFlags & 1U) != 0) {
gte_SetRotMatrix(((char *)sd + 0x34));
gte_SetTransMatrix(((char *)sd + 0x34));
gte_lwc2(0,*(int *)(&vt2));
                gte_lwc2(1,*(int *)(((char *)&vt2 + 0x4)));
                gte_rt();
gte_swc2(0x19,&temp0);
                gte_swc2(0x1a,((char *)&temp0 + 0x4));
                gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(&vt3));
                gte_lwc2(1,*(int *)(((char *)&vt3 + 0x4)));
                gte_rt();
                Night_NightCalc(&temp0,&vt2.light,sd)
                ;
gte_swc2(0x19,&temp0);
                gte_swc2(0x1a,((char *)&temp0 + 0x4));
                gte_swc2(0x1b,((char *)&temp0 + 0x8));
                Night_NightCalc(&temp0,&vt3.light,sd)
                ;
              }
              if (BW_gCopCarObj != (Car_tObj *)0x0) {
gte_SetRotMatrix(((char *)sd + 0x54));
gte_SetTransMatrix(((char *)sd + 0x54));
gte_lwc2(0,*(int *)(&vt2));
                gte_lwc2(1,*(int *)(((char *)&vt2 + 0x4)));
                gte_rt();
gte_swc2(0x19,&temp0);
                gte_swc2(0x1a,((char *)&temp0 + 0x4));
                gte_swc2(0x1b,((char *)&temp0 + 0x8));
gte_lwc2(0,*(int *)(&vt3));
                gte_lwc2(1,*(int *)(((char *)&vt3 + 0x4)));
                gte_rt();
                Night_NightCopCalc(&temp0,&vt2.light);
gte_swc2(0x19,&temp0);
                gte_swc2(0x1a,((char *)&temp0 + 0x4));
                gte_swc2(0x1b,((char *)&temp0 + 0x8));
                Night_NightCopCalc(&temp0,&vt3.light);
              }
              CVar19 = *(int *)(Chunk_lightTable + vt2.light);
              CVar23 = *(int *)(Chunk_lightTable + vt3.light);
              prim->r3 = (char)CVar19;
              prim->g3 = (char)((u_int)CVar19 >> 8);
              prim->b3 = (char)((u_int)CVar19 >> 0x10);
              prim->p3 = (char)((u_int)CVar19 >> 0x18);
              prim->r1 = (char)CVar19;
              prim->g1 = (char)((u_int)CVar19 >> 8);
              prim->b1 = (char)((u_int)CVar19 >> 0x10);
              prim->p1 = (char)((u_int)CVar19 >> 0x18);
              prim->r2 = (char)CVar23;
              prim->g2 = (char)((u_int)CVar23 >> 8);
              prim->b2 = (char)((u_int)CVar23 >> 0x10);
              prim->p2 = (char)((u_int)CVar23 >> 0x18);
              prim->r0 = (char)CVar23;
              prim->g0 = (char)((u_int)CVar23 >> 8);
              prim->b0 = (char)((u_int)CVar23 >> 0x10);
              prim->code = (char)((u_int)CVar23 >> 0x18);
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
            }
            prim->code = '>';
            ((u_char *)&prim->tag)[3] = 0xc;
            prim->u0 = pmx->u0;
            prim->v0 = pmx->v0;
            prim->clut = pmx->clut;
            prim->u1 = pmx->u1;
            prim->v1 = pmx->v1;
            prim->tpage = pmx->tpage;
            prim->u2 = pmx->u2;
            prim->v2 = pmx->v2;
            prim->pad2 = pmx->pad2;
            prim->u3 = pmx->u3;
            prim->v3 = pmx->v3;
            prim->pad3 = pmx->flag;
            if (prim->clut == 0xffff) {
              ti9 = nfs4_mips_srav_s32(
                  nfs4_mips_sll_s32(
                      nfs4_mips_subu_s32(save_pre_otz_l,sd->startfog),4),
                  (int)sd->distfog);
              if (ti9 < 0) {
                ti9 = 0;
              }
              else if (0xf < ti9) {
                ti9 = 0xf;
              }
              prim->clut = gClutDepth[pmx->pad2][ti9];
            }
            if (ot_addr_pack != 0) {
gte_SetRotMatrix(((char *)sd + 0x74));
gte_SetTransMatrix(((char *)sd + 0x74));
              if (stackSpeedUpEnbabledFlag == 0) {
                DrawW_SetUpSubdividFacet_Line(sd);
              }
              else {
                previousStack = (intptr)SetSp((void *)gWSavePtr);
                stackSpeedUpEnbabledFlag = 0;
                gWSavePtr = previousStack;
                DrawW_SetUpSubdividFacet_Line(sd);
                gWSavePtr = (intptr)SetSp((void *)gWSavePtr);
                stackSpeedUpEnbabledFlag = 1;
              }
gte_SetRotMatrix(((char *)sd + 0x14));
gte_SetTransMatrix(((char *)sd + 0x14));
            }
          }
        }
      }
      lineIdx = nfs4_mips_addu_s32(lineIdx,1);
      geomVertices = geomVertices + 2;
      tC6 = geomVertices;
    }
    lineQuad = lineQuad + 1;
    geomVertices = geomVertices + 2;
  }
  return;
}

/* ---- DrawW_BuildChunkCenterLineFacets__FP5ChunkP5GroupP25Draw_tGiveShelbyMoreCacheP7COORD16  [DRAWW.CPP:3344-3392] SLD-VERIFIED ---- */
void DrawW_BuildChunkCenterLineFacets(Chunk *chunkDat,Group *group,Draw_tGiveShelbyMoreCache *sd,COORD16 *trans)

{
  u_char bVar1;
  u_char bVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  bool bVar10;
  u_char *pbVar11;
  short sVar12;
  short sVar13;
  short sVar14;
  Trk_NewSlice *pTVar15;
  Group *pThis;
  Group *pGVar16;
  int iVar17;
  short x;
  short y;
  short z;
  int vertexIndex;
  short wz;
  CCOORD16 *chunkVertex;
  short wx;
  short wy;
  short *psVar19;
  CCOORD16 *pts3d;
  CCOORD16 *pCVar20;
  Trk_Line *lineQuad;
  int i;
  int iVar21;
  short tz;
  short ty;
  CCOORD16 *wpts;
  int slice;
  short tx;
  
  pTVar15 = BWorldSm_slices;
  pCVar20 = gVertex3d;
  iVar21 = 0;
  psVar19 = &gVertex3d[0].light;
  sVar3 = chunkDat->firstSimSliceInd;
  sVar4 = trans->x;
  sVar5 = trans->y;
  sVar6 = trans->z;
  pGVar16 = chunkDat->vertexBuf;
  pbVar11 = (u_char *)group;
  while( true ) {
    bVar10 = *(int *)(u_char *)group << 1 <= iVar21;
    iVar21 = iVar21 + 2;
    if (bVar10) break;
    vertexIndex = (u_int)pbVar11[4];
    iVar17 = (int)sVar3 + (u_int)pbVar11[5];
    chunkVertex = (CCOORD16 *)(pGVar16 + 1) + vertexIndex;
    bVar1 = pTVar15[iVar17].right[1];
    bVar2 = pTVar15[iVar17].right[2];
    sVar7 = chunkVertex->x;
    sVar8 = chunkVertex->y;
    sVar9 = chunkVertex->z;
    sVar12 = (short)((int)((u_int)(u_char)pTVar15[iVar17].right[0] << 0x18) >> 0x1b);
    pCVar20->x = sVar4 + (sVar7 - sVar12);
    sVar13 = (short)((int)((u_int)bVar1 << 0x18) >> 0x1b);
    psVar19[-2] = sVar5 + (sVar8 - sVar13);
    sVar14 = (short)((int)((u_int)bVar2 << 0x18) >> 0x1b);
    psVar19[-1] = sVar6 + (sVar9 - sVar14);
    *psVar19 = chunkVertex->light;
    pCVar20[1].x = sVar4 + sVar7 + sVar12;
    psVar19[2] = sVar5 + sVar8 + sVar13;
    psVar19[3] = sVar6 + sVar9 + sVar14;
    pCVar20 = pCVar20 + 2;
    psVar19[4] = (u_short)chunkVertex->light;
    psVar19 = psVar19 + 8;
    pbVar11 = pbVar11 + 4;
  }
  DrawW_OnyxLinePrim(gVertex3d,(Trk_Line *)((u_char *)group + 4),*(int *)(u_char *)group,sd);
  return;
}

/* ---- DrawW_DoLines__FP13DRender_tViewP11tBuildEntryP11Draw_DCache  [DRAWW.CPP:3396-3467] SLD-VERIFIED ---- */
void DrawW_DoLines(DRender_tView *Vi,tBuildEntry *buildList,Draw_DCache *sd)

{
  u_char bVar1;
  int iVar2;
  int geomRez;
  coorddef *pChunkCp;
  coorddef *pcVar3;
  Chunk *chunkDat;
  Chunk *chunkDat_00;
  Group *group;
  int buildInd;
  int iVar4;
  COORD16 trans;
  coorddef tmp;
  coorddef tmp2;
  int chunkCount;
  Draw_tGiveShelbyMoreCache *worldCache;
  
  worldCache = (Draw_tGiveShelbyMoreCache *)sd;
  iVar2 = BWorld_gChunkCount;
  worldCache->doublelayer = 0;
  (worldCache->matB).t[2] = 0;
  (worldCache->matB).t[1] = 0;
  (worldCache->matB).t[0] = 0;
gte_SetTransMatrix(&worldCache->matB);
  for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
    if (((buildList->geomRez == '\x04') &&
        (chunkDat_00 = Track_chunkList + buildList->chunkInd, chunkDat_00->lineBuf != (Group *)0x0))
      && ((buildList->enableBits & 4U) != 0)) {
      if (gNight_renderNight != 0) {
        bVar1 = worldCache->nightFlags;
        worldCache->nightFlags = bVar1 | 4;
        if (((Cars_gList[Vi->player]->control).lights & 6U) != 0) {
          worldCache->nightFlags = bVar1 | 5;
        }
        tmp.x = nfs4_mips_subu_s32((Vi->cview).translation.x,
            ((Camera_gInfo[Vi->player].target)->position).x);
        tmp.y = nfs4_mips_subu_s32((Vi->cview).translation.y,
            ((Camera_gInfo[Vi->player].target)->position).y);
        tmp.z = nfs4_mips_subu_s32((Vi->cview).translation.z,
            ((Camera_gInfo[Vi->player].target)->position).z);
        transform(&tmp.x,gNightMat.m,&tmp2.x);
        DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matNight);
        if (BW_gCopCarObj != (Car_tObj *)0x0) {
          tmp.x = nfs4_mips_subu_s32((Vi->cview).translation.x,
              (BW_gCopCarObj->N).position.x);
          tmp.y = nfs4_mips_subu_s32((Vi->cview).translation.y,
              (BW_gCopCarObj->N).position.y);
          tmp.z = nfs4_mips_subu_s32((Vi->cview).translation.z,
              (BW_gCopCarObj->N).position.z);
          transform(&tmp.x,gCopMat.m,&tmp2.x);
          DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matCop);
        }
        (worldCache->matB).t[2] = 0;
        (worldCache->matB).t[1] = 0;
        (worldCache->matB).t[0] = 0;
gte_SetTransMatrix(&worldCache->matB);
      }
      pcVar3 = Chunk_chunkCenters + buildList->chunkInd;
      trans.x = (short)nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(pcVar3->x,(Vi->cview).translation.x),10);
      trans.y = (short)nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(pcVar3->y,(Vi->cview).translation.y),10);
      trans.z = (short)nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(pcVar3->z,(Vi->cview).translation.z),10);
      DrawW_BuildChunkCenterLineFacets(chunkDat_00,chunkDat_00->lineBuf,worldCache,&trans);
    }
    buildList = buildList + 1;
  }
  return;
}

/* ---- DrawW_BuildSpikeBelt__FP13DRender_tViewiP11Draw_DCache  [DRAWW.CPP:3692-3815] SLD-VERIFIED ---- */
void DrawW_BuildSpikeBelt(DRender_tView *Vi,int scale,Draw_DCache *sd)

{
  int i;
  int slice;
  int scaledWidth;
  int spikeOffset;
  u_int stepX;
  u_int stepY;
  u_int stepZ;
  short dx;
  short dy;
  short dz;
  short forwardX;
  short forwardY;
  short forwardZ;
  short baseX;
  short baseY;
  short baseZ;
  Trk_NewSlice *trackSlice;
  CCOORD16 vertex3d [27];
  Trk_Quad quads [16];
  Track_tMaterial material;
  coorddef tmp;
  coorddef tmp2;
  Draw_tGiveShelbyMoreCache *worldCache;
  
  slice = gSpikeBeltSlice;
  trackSlice = BWorldSm_slices + slice;
  worldCache = (Draw_tGiveShelbyMoreCache *)sd;
  if (scale < 0) {
    scale = nfs4_mips_addu_s32(scale,7);
  }
  scaledWidth = nfs4_mips_sra_s32(scale,3);
  stepX = (u_int)fixedmult(nfs4_mips_sll_s32((int)trackSlice->right[0],9),scaledWidth);
  stepY = (u_int)fixedmult(nfs4_mips_sll_s32((int)trackSlice->right[1],9),scaledWidth);
  stepZ = (u_int)fixedmult(nfs4_mips_sll_s32((int)trackSlice->right[2],9),scaledWidth);
  dx = (short)(stepX >> 10);
  dy = (short)(stepY >> 10);
  dz = (short)(stepZ >> 10);
  forwardX = (short)nfs4_mips_sra_s32((int)trackSlice->forward[0],1);
  forwardY = (short)nfs4_mips_sra_s32((int)trackSlice->forward[1],1);
  forwardZ = (short)nfs4_mips_sra_s32((int)trackSlice->forward[2],1);
  spikeOffset = fixedmult(gSpikeBeltX,nfs4_mips_sll_s32((int)trackSlice->right[0],9));
  baseX = (short)nfs4_mips_sra_s32(spikeOffset,10);
  spikeOffset = fixedmult(gSpikeBeltX,nfs4_mips_sll_s32((int)trackSlice->right[1],9));
  baseY = (short)nfs4_mips_sra_s32(spikeOffset,10);
  spikeOffset = fixedmult(gSpikeBeltX,nfs4_mips_sll_s32((int)trackSlice->right[2],9));
  baseZ = (short)nfs4_mips_sra_s32(spikeOffset,10);

  vertex3d[0].x = (short)(baseX - forwardX);
  vertex3d[0].y = (short)(baseY - forwardY);
  vertex3d[0].z = (short)(baseZ - forwardZ);
  vertex3d[0].light = 0;
  for (i = 1; i < 9; i = i + 1) {
    vertex3d[i].x = (short)(vertex3d[i - 1].x + dx);
    vertex3d[i].y = (short)(vertex3d[i - 1].y + dy);
    vertex3d[i].z = (short)(vertex3d[i - 1].z + dz);
    vertex3d[i].light = 0;
  }

  vertex3d[9].x = baseX;
  vertex3d[9].y = (short)(baseY + 0x19);
  vertex3d[9].z = baseZ;
  vertex3d[9].light = 0;
  for (i = 10; i < 18; i = i + 1) {
    vertex3d[i].x = (short)(vertex3d[i - 1].x + dx);
    vertex3d[i].y = (short)(vertex3d[i - 1].y + dy);
    vertex3d[i].z = (short)(vertex3d[i - 1].z + dz);
    vertex3d[i].light = 0;
  }

  vertex3d[18].x = (short)(baseX + forwardX);
  vertex3d[18].y = (short)(baseY + forwardY);
  vertex3d[18].z = (short)(baseZ + forwardZ);
  vertex3d[18].light = 0;
  for (i = 19; i < 27; i = i + 1) {
    vertex3d[i].x = (short)(vertex3d[i - 1].x + dx);
    vertex3d[i].y = (short)(vertex3d[i - 1].y + dy);
    vertex3d[i].z = (short)(vertex3d[i - 1].z + dz);
    vertex3d[i].light = 0;
  }

  for (i = 0; i < 8; i = i + 1) {
    Trk_Quad *frontQuad = &quads[i];
    Trk_Quad *backQuad = &quads[i + 8];
    frontQuad->material = 0;
    frontQuad->aPoints[0] = (u_char)(i + 1);
    frontQuad->aPoints[1] = (u_char)(i + 10);
    frontQuad->aPoints[2] = (u_char)(i + 9);
    frontQuad->aPoints[3] = (u_char)i;
    backQuad->material = 0;
    backQuad->aPoints[0] = (u_char)(i + 18);
    backQuad->aPoints[1] = (u_char)(i + 9);
    backQuad->aPoints[2] = (u_char)(i + 10);
    backQuad->aPoints[3] = (u_char)(i + 19);
  }
  material.flag = '\0';
  material.mipmap_offset = '\0';
  material.pmxIndex = (short)gInitialArt.shapeCount + -1;
  worldCache->nightFlags = 0;
  tmp.x = nfs4_mips_subu_s32(trackSlice->center[0],(Vi->cview).translation.x);
  tmp.y = nfs4_mips_subu_s32(trackSlice->center[1],(Vi->cview).translation.y);
  tmp.z = nfs4_mips_subu_s32(trackSlice->center[2],(Vi->cview).translation.z);
  transform(&tmp.x,gWorldMat.m,&tmp2.x);
  DrawW_WorldSetUpTranslation(&tmp2,&worldCache->matB);
  worldCache->vertices = vertex3d;
  worldCache->quadCount = 0x10;
  worldCache->quads = quads;
  worldCache->offset = 0x23;
  worldCache->materials = &material;
  worldCache->trans.x = 0;
  worldCache->trans.y = 0;
  worldCache->trans.z = 0;
  worldCache->zeroGTETransFlag = 0;
  worldCache->light = -1;
  DrawW_kCtrlWorld_High(worldCache);
  return;
}

/* ---- DepthCue_Init__Fv  [DRAWW.CPP:3830-3834] SLD-VERIFIED ---- */
void DepthCue_Init(void)

{
  int dist;
  int i;
  int slice;
  int maxTick;
  int z2;
  int znear;
  int objectOffset;
  int save_pre_otz;
  int objectIndex;
  int totalCount;
  matrixtdef matrix;
  coorddef cp;
  coorddef pt2;
  int dvxy1;
  int groupNumElements;
  int offset;
  int doFrustumClip;
  short *visList;
  int chunkCount;
  
  SetFogNear(TrackSpec_gSpec.depthcuespec.distance << 6,0xa0);
  SetFarColor((u_int)TrackSpec_gSpec.depthcuespec.color.r,(u_int)TrackSpec_gSpec.depthcuespec.color.g,
             (u_int)TrackSpec_gSpec.depthcuespec.color.b);
  return;
}

/* end of draww.cpp */
