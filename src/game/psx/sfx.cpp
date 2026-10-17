/* game/psx/sfx.cpp -- RECONSTRUCTED (NFS4 PSX "souffle" smoke/dust/spark FX renderer; C++ TU)
 *   7 fns: Sfx_Transform (GTE world->cam), Sfx_BuildSmokeFacet/ThickenXZ/BuildFastDisolveFacet
 *   (billboard/ribbon facet builders), Sfx_AdditivePrim (GTE additive POLY_FT4 emit),
 *   Sfx_BuildSouffleFacet (per-type render dispatch), Sfx_Add (per-type init).
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "sfx_externs.h"

static int Sfx_OffsetCoordinate(int point,int offset,int center,unsigned int shift)
{
  return nfs4_mips_sra_s32(
      nfs4_mips_subu_s32(nfs4_mips_addu_s32(point,offset),center),shift);
}

/* ---- Sfx_Transform__FP8coorddefP7SVECTORT0  [SFX.CPP:40-75] SLD-VERIFIED ---- */
void Sfx_Transform(coorddef *worldpt,SVECTOR *campt,coorddef *t)

{
  SVECTOR pt;
  VECTOR campt32;
  MATRIX ident;

  TrsProj_SetPsxMatrix(&gWorldMat,(coorddef *)0x0);
  pt.vx = (short)((worldpt->x - t->x) >> 10);
  pt.vy = (short)((worldpt->y - t->y) >> 10);
  pt.vz = (short)((worldpt->z - t->z) >> 10);
  gte_ldv0(&pt);
  gte_mvmva(1,0,0,0,0);
  gte_stlvnl(&campt32);
  campt->vx = (short)campt32.vx;
  campt->vy = (short)campt32.vy;
  campt->vz = (short)campt32.vz;
  ident.m[0][0] = 0x1000; ident.m[0][1] = 0; ident.m[0][2] = 0;
  ident.m[1][0] = 0; ident.m[1][1] = 0x1000; ident.m[1][2] = 0;
  ident.m[2][0] = 0; ident.m[2][1] = 0; ident.m[2][2] = 0x1000;
  ident.t[0] = 0; ident.t[1] = 0; ident.t[2] = 0;
  gte_SetRotMatrix(&ident);
  return;
}

/* ---- Sfx_BuildSmokeFacet__FP17Souffle_tISouffleP10sfxsouffleP12Draw_tPixMap  [SFX.CPP:106-114] SLD-VERIFIED ---- */
void Sfx_BuildSmokeFacet(Souffle_tISouffle *is,sfxsouffle *dSouffle,Draw_tPixMap *cpixmap)

{
  int radius;
  int cosa;
  int sina;
  int iclut;

  radius = (0x1f - (u_char)is->cycle) * 4 + 0x26;
  cosa = fixedmult(fastintcos(is->angle),radius);
  sina = fixedmult(fastintsin(is->angle),radius);
  dSouffle->v0.vx = is->trans.vx - (short)sina;
  dSouffle->v0.vy = is->trans.vy + (short)cosa;
  dSouffle->v0.vz = is->trans.vz;
  dSouffle->v1.vx = is->trans.vx + (short)cosa;
  dSouffle->v1.vy = is->trans.vy + (short)sina;
  dSouffle->v1.vz = is->trans.vz;
  dSouffle->v2.vx = is->trans.vx + (short)sina;
  dSouffle->v2.vy = is->trans.vy - (short)cosa;
  dSouffle->v2.vz = is->trans.vz;
  dSouffle->v3.vx = is->trans.vx - (short)cosa;
  dSouffle->v3.vy = is->trans.vy - (short)sina;
  dSouffle->v3.vz = is->trans.vz;
  iclut = (int)(0x1f - (u_char)is->cycle) >> 1;
  if (iclut >= 0x10) {
    iclut = 0xf;
  }
  dSouffle->pmx = *gSMokePixmap[is->rndpixmap];
  dSouffle->pmx.clut = cpixmap->clut + (short)iclut;
  return;
}

/* ---- Sfx_ThickenXZ__FP7SVECTORP8coorddefN21  [SFX.CPP:163-191] SLD-VERIFIED ---- */
void Sfx_ThickenXZ(SVECTOR *d,coorddef *pt1,coorddef *pt2,coorddef *cp)

{
  int angle;
  int pxp;
  int pzp;

  angle = intatan(pt2->x - pt1->x,pt2->z - pt1->z);
  pxp = nfs4_mips_sra_s32(fixedmult(0xe666,-fastintcos(angle)),1);
  pzp = nfs4_mips_sra_s32(fixedmult(0xe666,fastintsin(angle)),1);
  d[1].vx = (short)Sfx_OffsetCoordinate(pt1->x,pxp,cp->x,10);
  d[1].vy = (short)Sfx_OffsetCoordinate(pt1->y,0,cp->y,10);
  d[1].vz = (short)Sfx_OffsetCoordinate(pt1->z,pzp,cp->z,10);
  d[2].vx = (short)Sfx_OffsetCoordinate(pt1->x,nfs4_mips_negu_s32(pxp),cp->x,10);
  d[2].vy = (short)Sfx_OffsetCoordinate(pt1->y,0,cp->y,10);
  d[2].vz = (short)Sfx_OffsetCoordinate(pt1->z,nfs4_mips_negu_s32(pzp),cp->z,10);
  d->vx = (short)Sfx_OffsetCoordinate(pt2->x,pxp,cp->x,10);
  d->vy = (short)Sfx_OffsetCoordinate(pt2->y,0,cp->y,10);
  d->vz = (short)Sfx_OffsetCoordinate(pt2->z,pzp,cp->z,10);
  d[3].vx = (short)Sfx_OffsetCoordinate(pt2->x,nfs4_mips_negu_s32(pxp),cp->x,10);
  d[3].vy = (short)Sfx_OffsetCoordinate(pt2->y,0,cp->y,10);
  d[3].vz = (short)Sfx_OffsetCoordinate(pt2->z,nfs4_mips_negu_s32(pzp),cp->z,10);
  return;
}

/* ---- Sfx_BuildFastDisolveFacet__FP17Souffle_tISouffleP10sfxsouffleP12Draw_tPixMapT2  [SFX.CPP:290-295] SLD-VERIFIED ---- */
void Sfx_BuildFastDisolveFacet(Souffle_tISouffle *is,sfxsouffle *dSouffle,Draw_tPixMap *t,Draw_tPixMap *c)

{
  int iclut;

  iclut = 8 - (u_char)is->cycle;
  if (iclut >= 0x10) {
    iclut = 0xf;
  }
  dSouffle->pmx = *t;
  dSouffle->pmx.clut = c->clut + (short)iclut;
  return;
}

/* ---- Sfx_AdditivePrim__FP12Draw_tPixMapP7SVECTORiiP10Sfx_tCache  [SFX.CPP:306-363] SLD-VERIFIED ---- */
void Sfx_AdditivePrim(Draw_tPixMap *pmx,SVECTOR *pt,int mode,int offset,Sfx_tCache *sd)

{
  POLY_FT4 *prim;
  uint32 l1;
  uint32 l2;
  uint32 l3;
  u_short tpage;

  if (sd->head.cprim.PrimPtr < sd->head.cprim.MPrimPtr) {
    gte_ldv0(pt);
    gte_rtps();
    prim = (POLY_FT4 *)Render_gPacketPtr;
    gte_stsxy(&prim->p[0].xy.x);
    gte_ldv3(pt + 1,pt + 2,pt + 3);
    gte_rtpt();
    if ((mode & 2U) != 0) {
      *(int *)&prim->rgbc.r = 0x2e5898b8;
    }
    else if (GameSetup_gData.Time == 0) {
      *(int *)&prim->rgbc.r = 0x2e181818;
    }
    else {
      *(int *)&prim->rgbc.r = 0x2e080808;
    }
    gte_stsxy3(&prim->p[1].xy.x,&prim->p[3].xy.x,&prim->p[2].xy.x);
    gte_avsz4();
    gte_stotz(&sd->otz);
    sd->otz = (sd->otz >> 1) + offset;
    if ((-1 < sd->otz) && (sd->otz <= Draw_gViewOtSize + -3)) {
      /* 0x800DD6B8: sb v0,3(s0) sets the DMA length, not code at +7. */
      prim->tag = (prim->tag & 0x00ffffffU) | 0x09000000U;
      l1 = *(u_int *)&pmx->u1;
      l2 = *(u_int *)&pmx->u2;
      l3 = *(u_int *)&pmx->u3;
      *(u_int *)&prim->p[0].uv.u = *(u_int *)&pmx->u0;
      *(u_int *)&prim->p[1].uv.u = l1;
      *(u_int *)&prim->p[2].uv.u = l2;
      *(u_int *)&prim->p[3].uv.u = l3;
      tpage = pmx->tpage;
      ChangeTPage(&tpage,(mode & 1U) == 0 ? 1 : 2);
      prim->p[1].attr = tpage;
      AddPrim(Render_gPalettePtr + sd->otz * 4,Render_gPacketPtr);
      Render_gPacketPtr = Render_gPacketPtr + 0x28;
    }
  }
  return;
}

/* ---- Sfx_BuildSouffleFacet__FP13DRender_tViewP17Souffle_tISouffle  [SFX.CPP:367-525] SLD-VERIFIED ---- */
void Sfx_BuildSouffleFacet(DRender_tView *Vi,Souffle_tISouffle *is)

{
  sfxsouffle dSouffle;
  Sfx_tCache *sd;
  POLY_FT4 *prim;
  Draw_tPixMap *pmx;
  SVECTOR ribbon[4];
  SVECTOR ptrans;
  VECTOR proj;
  coorddef wpos;
  coorddef src;
  u_short tpage;
  int radius;
  int cosa;
  int sina;
  int otz;
  int colorcode;

  /* Retail 0x800DD7C4 loads s3 with 0x1f800000 and passes that address as
     Sfx_tCache*.  Its first three words are the same scratch cells exported
     as Render_gPalettePtr/Render_gPacketPtr/Render_gPacketEnd. */
  sd = (Sfx_tCache *)getScratchAddr(0);
  switch((u_char)is->type) {
  case 1:
    Sfx_BuildSmokeFacet(is,&dSouffle,gSMokePalette);
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,0,0xf,sd);
    break;
  case 2:
    Sfx_BuildSmokeFacet(is,&dSouffle,gSMokePalette);
    if ((u_char)is->cycle < 0x12) {
      is->type = 1;
    }
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,0,0xf,sd);
    break;
  case 3:
    Sfx_BuildSmokeFacet(is,&dSouffle,gSMokePalette);
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,1,0xf,sd);
    break;
  case 4:
    wpos.x = is->motion.x; wpos.y = is->motion.y; wpos.z = is->motion.z;
    Math_NormalizeVector(&wpos);
    wpos.x = is->source.x + wpos.x * -4;
    wpos.y = is->source.y + wpos.y * -4;
    wpos.z = is->source.z + wpos.z * -4;
    Sfx_Transform(&wpos,&ptrans,&Vi->cview.translation);
    if (ptrans.vz < 0x40) {
      break;
    }
    radius = ptrans.vx - is->trans.vx;
    if (radius < 1) radius = is->trans.vx - ptrans.vx;
    if (radius < 0x20) {
      ptrans.vx = (ptrans.vx <= is->trans.vx) ? is->trans.vx + -0x20 : is->trans.vx + 0x20;
    }
    dSouffle.v0.vx = is->trans.vx;  dSouffle.v0.vy = is->trans.vy + 0x20;  dSouffle.v0.vz = is->trans.vz;
    dSouffle.v3.vx = is->trans.vx;  dSouffle.v3.vy = is->trans.vy + -0x20; dSouffle.v3.vz = is->trans.vz;
    dSouffle.v1.vx = ptrans.vx;     dSouffle.v1.vy = ptrans.vy + 0x20;     dSouffle.v1.vz = ptrans.vz;
    dSouffle.v2.vx = ptrans.vx;     dSouffle.v2.vy = ptrans.vy + -0x20;    dSouffle.v2.vz = ptrans.vz;
    dSouffle.pmx = *gSparkHPixmap[6 - (u_char)is->cycle];
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,2,0x28,sd);
    break;
  case 6:
    radius = 0x88 - (u_char)is->cycle;
    cosa = fixedmult(fastintcos(is->angle),radius);
    sina = fixedmult(fastintsin(is->angle),radius);
    goto SfxSouffle_billboard;
  case 7:
    radius = (8 - (u_char)is->cycle) * 4 + 0x19;
    cosa = fixedmult(fastintcos(is->angle),radius);
    sina = fixedmult(fastintsin(is->angle),radius);
    dSouffle.v0.vx = is->trans.vx - (short)sina;  dSouffle.v0.vy = is->trans.vy + (short)cosa;  dSouffle.v0.vz = is->trans.vz;
    dSouffle.v1.vx = is->trans.vx + (short)cosa;  dSouffle.v1.vy = is->trans.vy + (short)sina;  dSouffle.v1.vz = is->trans.vz;
    dSouffle.v2.vx = is->trans.vx + (short)sina;  dSouffle.v2.vy = is->trans.vy - (short)cosa;  dSouffle.v2.vz = is->trans.vz;
    dSouffle.v3.vx = is->trans.vx - (short)cosa;  dSouffle.v3.vy = is->trans.vy - (short)sina;  dSouffle.v3.vz = is->trans.vz;
    Sfx_BuildFastDisolveFacet(is,&dSouffle,gGravelPixmap[is->rndpixmap],gGrassPalette);
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,0,0xf,sd);
    break;
  case 9:
    radius = (8 - (u_char)is->cycle) * 4 + 0x19;
    cosa = fixedmult(fastintcos(is->angle),radius);
    sina = fixedmult(fastintsin(is->angle),radius);
    dSouffle.v0.vx = is->trans.vx - (short)sina;  dSouffle.v0.vy = is->trans.vy + (short)cosa;  dSouffle.v0.vz = is->trans.vz;
    dSouffle.v1.vx = is->trans.vx + (short)cosa;  dSouffle.v1.vy = is->trans.vy + (short)sina;  dSouffle.v1.vz = is->trans.vz;
    dSouffle.v2.vx = is->trans.vx + (short)sina;  dSouffle.v2.vy = is->trans.vy - (short)cosa;  dSouffle.v2.vz = is->trans.vz;
    dSouffle.v3.vx = is->trans.vx - (short)cosa;  dSouffle.v3.vy = is->trans.vy - (short)sina;  dSouffle.v3.vz = is->trans.vz;
    Sfx_BuildFastDisolveFacet(is,&dSouffle,gGravelPixmap[is->rndpixmap],gSnowPalette);
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,0,0xf,sd);
    break;
  case 11:
    radius = (8 - (u_char)is->cycle) * 4 + 0xc;
    cosa = fixedmult(fastintcos(is->angle),radius);
    sina = fixedmult(fastintsin(is->angle),radius);
SfxSouffle_billboard:
    dSouffle.v0.vx = is->trans.vx - (short)sina;  dSouffle.v0.vy = is->trans.vy + (short)cosa;  dSouffle.v0.vz = is->trans.vz;
    dSouffle.v1.vx = is->trans.vx + (short)cosa;  dSouffle.v1.vy = is->trans.vy + (short)sina;  dSouffle.v1.vz = is->trans.vz;
    dSouffle.v2.vx = is->trans.vx + (short)sina;  dSouffle.v2.vy = is->trans.vy - (short)cosa;  dSouffle.v2.vz = is->trans.vz;
    dSouffle.v3.vx = is->trans.vx - (short)cosa;  dSouffle.v3.vy = is->trans.vy - (short)sina;  dSouffle.v3.vz = is->trans.vz;
    Sfx_BuildFastDisolveFacet(is,&dSouffle,gSMokePixmap[is->rndpixmap],
                              (is->type == 6) ? gDirtPalette : gSnowPalette);
    Sfx_AdditivePrim(&dSouffle.pmx,&dSouffle.v0,0,0xf,sd);
    break;
  case 8:
  case 10:
    wpos.x = is->motion.x; wpos.y = is->motion.y; wpos.z = is->motion.z;
    Math_NormalizeVector(&wpos);
    src.x = is->source.x; src.y = is->source.y; src.z = is->source.z;
    radius = *(short *)((char *)is + 0x3a);   /* push-back scale */
    wpos.x = src.x - (wpos.x * radius >> 4);
    wpos.y = src.y - (wpos.y * radius >> 4);
    wpos.z = src.z - (wpos.z * radius >> 4);
    Sfx_ThickenXZ(ribbon,&wpos,&src,&Vi->cview.translation);
    colorcode = (is->type == 8) ? 0x2e301818 : 0x2e181010;
    otz = 0x32;
    pmx = gSparkHPixmap[6 - (u_char)is->cycle];
    TrsProj_SetPsxMatrix(&gWorldMat,(coorddef *)0x0);
    if (sd->head.cprim.PrimPtr < sd->head.cprim.MPrimPtr) {
      gte_ldv0(&ribbon[1]);
      gte_rtps();
      prim = (POLY_FT4 *)sd->head.cprim.PrimPtr;
      gte_stlvnl(&proj);
      if (proj.vz >= 0x20) {
        gte_stsxy(&prim->p[1].xy.x);
        gte_ldv3(&ribbon[0],&ribbon[2],&ribbon[3]);
        gte_rtpt();
        *(int *)&prim->rgbc.r = colorcode;
        gte_stsxy3(&prim->p[0].xy.x,&prim->p[3].xy.x,&prim->p[2].xy.x);
        gte_avsz4();
        gte_stotz(&sd->otz);
        sd->otz = (sd->otz >> 1) + otz;
        if ((sd->otz >= 0) && (sd->otz <= Draw_gViewOtSize + -3)) {
          /* 0x800DE308: sb v0,3(s0), preserving the FT4 GPU opcode. */
          prim->tag = (prim->tag & 0x00ffffffU) | 0x09000000U;
          *(u_int *)&prim->p[0].uv.u = *(u_int *)&pmx->u0;
          *(u_int *)&prim->p[1].uv.u = *(u_int *)&pmx->u1;
          *(u_int *)&prim->p[2].uv.u = *(u_int *)&pmx->u2;
          *(u_int *)&prim->p[3].uv.u = *(u_int *)&pmx->u3;
          tpage = pmx->tpage;
          ChangeTPage(&tpage,(is->type == 8) ? 2 : 1);
          prim->p[1].attr = tpage;
          AddPrim(sd->head.cprim.LastPrim + sd->otz,sd->head.cprim.PrimPtr);
          sd->head.cprim.PrimPtr = (char *)((char *)sd->head.cprim.PrimPtr + 0x28);
        }
      }
    }
    break;
  case 13:
  case 14:
    cosa = fixedmult(fastintcos(is->angle),6);
    sina = fixedmult(fastintsin(is->angle),6);
    dSouffle.v0.vx = is->trans.vx - (short)sina;  dSouffle.v0.vy = is->trans.vy + (short)cosa;  dSouffle.v0.vz = is->trans.vz;
    dSouffle.v1.vx = is->trans.vx + (short)cosa;  dSouffle.v1.vy = is->trans.vy + (short)sina;  dSouffle.v1.vz = is->trans.vz;
    dSouffle.v2.vx = is->trans.vx + (short)sina;  dSouffle.v2.vy = is->trans.vy - (short)cosa;  dSouffle.v2.vz = is->trans.vz;
    dSouffle.v3.vx = is->trans.vx - (short)cosa;  dSouffle.v3.vy = is->trans.vy - (short)sina;  dSouffle.v3.vz = is->trans.vz;
    if (sd->head.cprim.PrimPtr < sd->head.cprim.MPrimPtr) {
      gte_ldv0(&dSouffle.v0);
      gte_rtps();
      prim = (POLY_FT4 *)sd->head.cprim.PrimPtr;
      gte_stsxy(&prim->p[0].xy.x);
      gte_ldv3(&dSouffle.v1,&dSouffle.v2,&dSouffle.v3);
      gte_rtpt();
      *(int *)&prim->rgbc.r = is->colour | 0x2c000000;
      gte_stsxy3(&prim->p[1].xy.x,&prim->p[3].xy.x,&prim->p[2].xy.x);
      gte_avsz4();
      gte_stotz(&sd->otz);
      sd->otz = (sd->otz >> 1) + 0xf;
      if ((sd->otz >= 0) && (sd->otz <= Draw_gViewOtSize + -3)) {
        /* 0x800DE590: sb v0,3(t0), preserving the FT4 GPU opcode. */
        prim->tag = (prim->tag & 0x00ffffffU) | 0x09000000U;
        *(u_int *)&prim->p[0].uv.u = *(u_int *)&gLeafPixmap->u0;
        *(u_int *)&prim->p[1].uv.u = *(u_int *)&gLeafPixmap->u1;
        *(u_int *)&prim->p[2].uv.u = *(u_int *)&gLeafPixmap->u2;
        *(u_int *)&prim->p[3].uv.u = *(u_int *)&gLeafPixmap->u3;
        AddPrim(sd->head.cprim.LastPrim + sd->otz,sd->head.cprim.PrimPtr);
        sd->head.cprim.PrimPtr = (char *)((char *)sd->head.cprim.PrimPtr + 0x28);
      }
    }
    break;
  }
  return;
}

/* ---- Sfx_Add__FP17Souffle_tISouffle  [SFX.CPP:534-577] SLD-VERIFIED ---- */
void Sfx_Add(Souffle_tISouffle *is)

{
  char cycle;

  switch((u_char)is->type) {
  case 1:
  case 2:
  case 3:
    cycle = 0x1f;
SfxAdd_setRandom:
    is->cycle = cycle;
    is->rndpixmap = random() & 1;
    return;
  case 6:
  case 7:
  case 9:
    cycle = 8;
    goto SfxAdd_setRandom;
  case 11:
    is->rndpixmap = random() & 1;
    is->cycle = 2;
    return;
  case 4:
  case 8:
  case 10:
    is->cycle = 6;
    return;
  case 13:
    is->cycle = 0x40;
    is->extramotion.y = 0;
    is->extramotion.x = -is->motion.z;
    is->extramotion.z = is->motion.x;
  }
  return;
}

/* end of sfx.cpp */
