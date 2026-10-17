/* game/psx/skidmark.cpp -- RECONSTRUCTED (NFS4 PSX tyre skid-mark system; C++ TU)
 *   11 fns: Calc{Start,One}Segment (perp-offset segment geometry), Skidmark_CheckChunk
 *   (24-slot chunk allocator), Skidmark_Add/AddStretch/Stretch/EndStretch (append/extend
 *   skid trails), Skidmark_OnyxBuildFacets (queue render), Init/Restart/Kill. No GTE.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "skidmark_externs.h"

/* ---- Skidmark.obj-OWNED globals -- DEFINED here (self-contained; SYM-typed via gen_owned_defs:
   .data = real NFS4.EXE bytes, .bss = zero) ---- */
Skidmark_Chunk *gSm;   /* @0x8013dac8  (bss(zero)) */
int          gCountSm;   /* @0x8013dacc  (bss(zero)) */
int          gUseSm;   /* @0x8013dad0  (bss(zero)) */
int          gMaxSChunk;   /* @0x8013dad4  (bss(zero)) */
/* skid-spline control-point + scratch state (extern-declared in draww/bworld externs,
   defined here in the owning Skidmark.obj TU; BSS zero -- runtime spline work area). */
int          Skid_gCtrlPoint_0, Skid_gCtrlPoint_1, Skid_gCtrlPoint_2, Skid_gCtrlPoint_3;
int          Skid_gCtrlPoint_4, Skid_gCtrlPoint_5, Skid_gCtrlPoint_6;
extern "C" { int Skid_gScratchPos1, Skid_gScratchPos2; }

static int Skidmark_OffsetCoordinate(int point,int offset,int center)
{
  return nfs4_mips_sra_s32(
      nfs4_mips_subu_s32(nfs4_mips_addu_s32(point,offset),center),6);
}

/* ---- CalcStartSegment__FP16Skidmark_SegmentT0P8coorddefN22i  [SKIDMARK.CPP:48-72] SLD-VERIFIED ---- */
void CalcStartSegment(Skidmark_Segment *r1,Skidmark_Segment *r2,coorddef *cp,coorddef *pt1,
                      coorddef *pt2,int tireWidth)

{
  int angle;
  int pxp;
  int pzp;

  angle = intatan(pt2->x - pt1->x,pt2->z - pt1->z);
  pxp = nfs4_mips_sra_s32(fixedmult(tireWidth,-fastintcos(angle)),1);
  pzp = nfs4_mips_sra_s32(fixedmult(tireWidth,fastintsin(angle)),1);
  r1->svx[0].vx = (short)Skidmark_OffsetCoordinate(pt1->x,pxp,cp->x);
  r1->svx[0].vy = (short)Skidmark_OffsetCoordinate(pt1->y,0,cp->y);
  r1->svx[0].vz = (short)Skidmark_OffsetCoordinate(pt1->z,pzp,cp->z);
  r1->svx[1].vx = (short)Skidmark_OffsetCoordinate(pt1->x,nfs4_mips_negu_s32(pxp),cp->x);
  r1->svx[1].vy = (short)Skidmark_OffsetCoordinate(pt1->y,0,cp->y);
  r1->svx[1].vz = (short)Skidmark_OffsetCoordinate(pt1->z,nfs4_mips_negu_s32(pzp),cp->z);
  r2->svx[1].vx = (short)Skidmark_OffsetCoordinate(pt2->x,nfs4_mips_negu_s32(pxp),cp->x);
  r2->svx[1].vy = (short)Skidmark_OffsetCoordinate(pt2->y,0,cp->y);
  r2->svx[1].vz = (short)Skidmark_OffsetCoordinate(pt2->z,nfs4_mips_negu_s32(pzp),cp->z);
  r2->svx[0].vx = (short)Skidmark_OffsetCoordinate(pt2->x,pxp,cp->x);
  r2->svx[0].vy = (short)Skidmark_OffsetCoordinate(pt2->y,0,cp->y);
  r2->svx[0].vz = (short)Skidmark_OffsetCoordinate(pt2->z,pzp,cp->z);
  return;
}

/* ---- CalcOneSegment__FP16Skidmark_SegmentP8coorddefN21i  [SKIDMARK.CPP:81-99] SLD-VERIFIED ---- */
void CalcOneSegment(Skidmark_Segment *r1,coorddef *cp,coorddef *pt1,coorddef *pt2,int tireWidth)

{
  int angle;
  int pxp;
  int pzp;

  angle = intatan(pt2->x - pt1->x,pt2->z - pt1->z);
  pxp = fixedmult(tireWidth,-fastintcos(angle));
  pzp = fixedmult(tireWidth,fastintsin(angle));
  pxp = nfs4_mips_sra_s32(pxp,1);
  pzp = nfs4_mips_sra_s32(pzp,1);
  r1->svx[0].vx = (short)Skidmark_OffsetCoordinate(pt2->x,pxp,cp->x);
  r1->svx[0].vy = (short)Skidmark_OffsetCoordinate(pt2->y,0,cp->y);
  r1->svx[0].vz = (short)Skidmark_OffsetCoordinate(pt2->z,pzp,cp->z);
  r1->svx[1].vx = (short)Skidmark_OffsetCoordinate(pt2->x,nfs4_mips_negu_s32(pxp),cp->x);
  r1->svx[1].vy = (short)Skidmark_OffsetCoordinate(pt2->y,0,cp->y);
  r1->svx[1].vz = (short)Skidmark_OffsetCoordinate(pt2->z,nfs4_mips_negu_s32(pzp),cp->z);
  return;
}

/* ---- Skidmark_CheckChunk__FP8coorddefii  [SKIDMARK.CPP:115-151] SLD-VERIFIED ---- */
Skidmark_Chunk *
Skidmark_CheckChunk(coorddef *skidpt,int newsegs,int slice)

{
  bool needNew;
  int dist;
  Skidmark_Chunk *returnsm;
  int anchor;
  
  returnsm = gSm + gUseSm;
  anchor = (returnsm->cp).x;
  needNew = 0x18 < returnsm->n + newsegs;
  dist = anchor - skidpt->x;
  if (dist < 1) {
    dist = skidpt->x - anchor;
  }
  if (dist < 0x100000) {
    anchor = (returnsm->cp).y;
    dist = anchor - skidpt->y;
    if (dist < 1) {
      dist = skidpt->y - anchor;
    }
    if (dist < 0x100000) {
      anchor = (returnsm->cp).z;
      dist = anchor - skidpt->z;
      if (0 < dist) {
        if (0xfffff < dist) {
          needNew = true;
        }
        goto SkidChkChunk_useGCount;
      }
      if (skidpt->z - anchor < 0x100000) goto SkidChkChunk_useGCount;
    }
  }
  needNew = true;
SkidChkChunk_useGCount:
  if (needNew) {
    if (gCountSm < gMaxSChunk) {
      gUseSm = gCountSm;
      gCountSm = gCountSm + 1;
    }
    else {
      needNew = gMaxSChunk + -1 <= gUseSm;
      gUseSm = gUseSm + 1;
      if (needNew) {
        gUseSm = 0;
      }
    }
    returnsm = gSm + gUseSm;
    returnsm->n = 0;
  }
  if (returnsm->n == 0) {
    dist = skidpt->y;
    anchor = skidpt->z;
    (returnsm->cp).x = skidpt->x;
    (returnsm->cp).y = dist;
    (returnsm->cp).z = anchor;
    returnsm->slice = (short)slice;
  }
  return returnsm;
}

/* ---- Skidmark_Add__FP5tSkidP8coorddefP7CVECTORiii  [SKIDMARK.CPP:159-239] SLD-VERIFIED ---- */
void Skidmark_Add(tSkid *prevskid,coorddef *skidpt,CVECTOR *color,int tireWidth,int type,int slice)

{
  Skidmark_Chunk *sm;
  int n;

  if (prevskid->nseg == (Skidmark_Segment *)0x0) {
    sm = Skidmark_CheckChunk(skidpt,2,slice);
    CalcStartSegment(sm->seg + sm->n,sm->seg + sm->n + 1,&sm->cp,&prevskid->pt,skidpt,tireWidth);
    n = sm->n;
    sm->seg[n + 1].rgb = *color;
    sm->seg[n].rgb = sm->seg[n + 1].rgb;
    n = sm->n;
    sm->seg[n + 1].type = type;
  }
  else {
    sm = Skidmark_CheckChunk(skidpt,2,slice);
    if (prevskid->chunk == gUseSm) {
      CalcOneSegment(sm->seg + sm->n,&sm->cp,&prevskid->pt,skidpt,tireWidth);
      sm->seg[sm->n].rgb = *color;
      sm->seg[sm->n].type = type;
      prevskid->nseg->next = sm->seg + sm->n;
      sm->seg[sm->n].next = (Skidmark_Segment *)0x0;
      prevskid->clr = *color;
      prevskid->type = type;
      prevskid->pt = *skidpt;
      prevskid->chunk = gUseSm;
      prevskid->nseg = sm->seg + sm->n;
      sm->n = sm->n + 1;
      return;
    }
    n = sm->n;
    CalcStartSegment(sm->seg + n,sm->seg + n + 1,&sm->cp,&prevskid->pt,skidpt,tireWidth);
    sm->seg[sm->n].rgb = prevskid->clr;
    sm->seg[sm->n].type = prevskid->type;
    sm->seg[sm->n + 1].rgb = *color;
    n = sm->n + 1;
  }
  sm->seg[n].type = type;
  sm->seg[sm->n].next = sm->seg + sm->n + 1;
  sm->seg[sm->n + 1].next = (Skidmark_Segment *)0x0;
  prevskid->clr = *color;
  prevskid->type = type;
  prevskid->pt = *skidpt;
  prevskid->chunk = gUseSm;
  prevskid->nseg = sm->seg + sm->n + 1;
  sm->n = sm->n + 2;
  return;
}

/* ---- Skidmark_AddStretch__FPP16Skidmark_SegmentPiP5tSkidP8coorddefP7CVECTORiii  [SKIDMARK.CPP:264-326] SLD-VERIFIED ---- */
void Skidmark_AddStretch(Skidmark_Segment **save,int *savechunk,tSkid *prevskid,coorddef *skidpt,
                        CVECTOR *color,int tireWidth,int type,int slice)

{
  Skidmark_Chunk *sm;
  int n;

  if (prevskid->nseg == (Skidmark_Segment *)0x0) {
    sm = Skidmark_CheckChunk(skidpt,2,slice);
    CalcStartSegment(sm->seg + sm->n,sm->seg + sm->n + 1,&sm->cp,&prevskid->pt,skidpt,tireWidth);
    n = sm->n;
    sm->seg[n + 1].rgb = *color;
    sm->seg[n].rgb = sm->seg[n + 1].rgb;
    n = sm->n;
    sm->seg[n + 1].type = type;
  }
  else {
    sm = Skidmark_CheckChunk(skidpt,2,slice);
    if (prevskid->chunk == gUseSm) {
      CalcOneSegment(sm->seg + sm->n,&sm->cp,&prevskid->pt,skidpt,tireWidth);
      sm->seg[sm->n].rgb = *color;
      sm->seg[sm->n].type = type;
      prevskid->nseg->next = sm->seg + sm->n;
      sm->seg[sm->n].next = (Skidmark_Segment *)0x0;
      *save = sm->seg + sm->n;
      *savechunk = gUseSm;
      sm->n = sm->n + 1;
      return;
    }
    n = sm->n;
    CalcStartSegment(sm->seg + n,sm->seg + n + 1,&sm->cp,&prevskid->pt,skidpt,tireWidth);
    sm->seg[sm->n].rgb = prevskid->clr;
    sm->seg[sm->n].type = prevskid->type;
    sm->seg[sm->n + 1].rgb = *color;
    n = sm->n + 1;
  }
  sm->seg[n].type = type;
  sm->seg[sm->n].next = sm->seg + sm->n + 1;
  sm->seg[sm->n + 1].next = (Skidmark_Segment *)0x0;
  *save = sm->seg + sm->n + 1;
  *savechunk = gUseSm;
  sm->n = sm->n + 2;
  return;
}

/* ---- Skidmark_Stretch__FP16Skidmark_SegmentiP5tSkidP8coorddefP7CVECTORii  [SKIDMARK.CPP:336-341] SLD-VERIFIED ---- */
void Skidmark_Stretch(Skidmark_Segment *save,int savechunk,tSkid *prevskid,coorddef *skidpt,
                     CVECTOR *color,int tireWidth,int type)

{
  CalcOneSegment(save,&gSm[savechunk].cp,&prevskid->pt,skidpt,tireWidth);
  save->rgb = *color;
  save->type = type;
  return;
}

/* ---- Skidmark_EndStretch__FP16Skidmark_SegmentiP5tSkidP8coorddefP7CVECTORii  [SKIDMARK.CPP:350-361] SLD-VERIFIED ---- */
void Skidmark_EndStretch(Skidmark_Segment *save,int savechunk,tSkid *prevskid,coorddef *skidpt,
                        CVECTOR *color,int tireWidth,int type)

{
  CalcOneSegment(save,&gSm[savechunk].cp,&prevskid->pt,skidpt,tireWidth);
  save->rgb = *color;
  save->type = type;
  prevskid->clr = *color;
  prevskid->type = type;
  prevskid->pt = *skidpt;
  prevskid->nseg = save;
  prevskid->chunk = savechunk;
  return;
}

/* ---- Skidmark_OnyxBuildFacets__FP13DRender_tView  [SKIDMARK.CPP:365-408] SLD-VERIFIED ---- */
void Skidmark_OnyxBuildFacets(DRender_tView *Vi)

{
  Draw_tCtrlSkidmark fskidspace;
  
  fskidspace.t = Vi->cview.translation;
  fskidspace.count = gCountSm;
  fskidspace.smp = gSm;
  fskidspace.m.m[0] = Vi->cview.mrotationInv.m[0];
  fskidspace.m.m[1] = nfs4_mips_negu_s32(Vi->cview.mrotationInv.m[1]);
  fskidspace.m.m[2] = Vi->cview.mrotationInv.m[2];
  fskidspace.m.m[3] = Vi->cview.mrotationInv.m[3];
  fskidspace.m.m[4] = nfs4_mips_negu_s32(Vi->cview.mrotationInv.m[4]);
  fskidspace.m.m[5] = Vi->cview.mrotationInv.m[5];
  fskidspace.m.m[6] = Vi->cview.mrotationInv.m[6];
  fskidspace.m.m[7] = nfs4_mips_negu_s32(Vi->cview.mrotationInv.m[7]);
  fskidspace.m.m[8] = Vi->cview.mrotationInv.m[8];
  Draw_kCtrlSkidmark(&fskidspace);
  return;
}

/* ---- Skidmark_InitSkidmark__Fv  [SKIDMARK.CPP:419-429] SLD-VERIFIED ---- */
void Skidmark_InitSkidmark(void)

{
  gMaxSChunk = 0x10;
  if (GameSetup_gData.commMode == 1) {
    gMaxSChunk = 8;
  }
  gSm = (Skidmark_Chunk *)reservememadr("SkidMark",gMaxSChunk * 0x2b0,0);
  gSm->n = 0;
  gCountSm = 0;
  gUseSm = 0;
  return;
}

/* ---- Skidmark_RestartSkidmark__Fv  [SKIDMARK.CPP:433-437] SLD-VERIFIED ---- */
void Skidmark_RestartSkidmark(void)

{
  gCountSm = 0;
  gUseSm = 0;
  gSm->n = 0;
  return;
}

/* ---- Skidmark_KillSkidmark__Fv  [SKIDMARK.CPP:441-443] SLD-VERIFIED ---- */
void Skidmark_KillSkidmark(void)

{
  
  if (gSm != (Skidmark_Chunk *)0x0) {
    purgememadr(gSm);
  }
  gSm = (Skidmark_Chunk *)0x0;
  return;
}

/* end of skidmark.cpp */
