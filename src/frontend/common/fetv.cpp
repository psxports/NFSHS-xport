/* frontend/common/fetv.cpp -- RECONSTRUCTED (front-end "TV" grid widget; C++ TU)
 *   5 free fns on tTVConfig& (ns nfs4::FRONTEND::COMMON::FETv): DrawTVLines (scanline/stripe
 *   overlay), DrawTV (3260 B -- the TV-grid background drawer), InitTV, TurnOffTV, TurnOnTV.
 *   GPU packet building via Render_gPacketPtr/Render_gPalettePtr.
 */
#include "fetv.h"
#include "../../mips_semantics.h"


/* ---- DrawTVLines  [FETV.CPP:25-77] SLD-VERIFIED ---- */

extern "C" void DrawTVLines(tTVConfig &tv)

{
  u_short uVar1;
  int wrapPeriod;
  int ti6;
  int iVar2;
  u_int stripe_x;
  int fxWideAdj;
  int fxThinAdj;
  u_int abr;
  short ts11;
  int yScroll_or_break;
  short tu12;
  short ts5;
  short ts1;
  u_short tvY_orig;
  short ts2;
  short ts3;
  int fxWideMod;
  u_char *cur_pkt_thin;
  u_char *prev_pkt_thin;
  short ts6;
  short ts7;
  
  fxWideAdj = tv.fxWide + 1;
  wrapPeriod = tv.h * 0x30;
  fxWideMod = fxWideAdj % wrapPeriod;
  tu12 = (short)fxWideMod;
  ti6 = tv.h * 0x30;
  fxThinAdj = tv.fxThin + 2;
  tvY_orig = tv.y;
  tv.fxWide = tu12;
  abr = (u_int)tv.y;
  tv.fxThin = (short)(fxThinAdj % ti6);
  cur_pkt_thin = Render_gPacketPtr;
  prev_pkt_thin = Render_gPalettePtr;
  ts11 = 8;
  if ((int)tv.fxWide < (int)abr) {
    yScroll_or_break = 8 - ((u_int)tvY_orig - fxWideMod);
    tu12 = tvY_orig;
  }
  else {
    iVar2 = 0x80000;
    if (tv.fxWide + 8 <= (int)(abr + (int)tv.h)) goto DrawTVLines_writeTpage;
    yScroll_or_break = (u_int)tvY_orig - fxWideMod;
  }
  ts11 = (short)yScroll_or_break;
  iVar2 = yScroll_or_break << 0x10;
DrawTVLines_writeTpage:
  if (0 < iVar2) {
    AddPrim(prev_pkt_thin,cur_pkt_thin);
    Render_gPacketPtr = Render_gPacketPtr + 0x18;
    cur_pkt_thin[7] = 0x2a;
    cur_pkt_thin[3] = 5;
    ts2 = tv.x;
    *(short *)(cur_pkt_thin + 10) = tu12;
    *(short *)(cur_pkt_thin + 8) = ts2;
    ts1 = tv.x;
    ts3 = tv.w;
    *(short *)(cur_pkt_thin + 0xe) = tu12;
    *(short *)(cur_pkt_thin + 0xc) = ts1 + ts3;
    ts6 = tv.x;
    *(short *)(cur_pkt_thin + 0x12) = tu12 + ts11;
    *(short *)(cur_pkt_thin + 0x10) = ts6;
    ts6 = tv.x;
    uVar1 = tv.w;
    abr = (u_int)uVar1;
    *(short *)(cur_pkt_thin + 0x16) = tu12 + ts11;
    cur_pkt_thin[6] = 10;
    cur_pkt_thin[5] = 10;
    cur_pkt_thin[4] = 10;
    *(u_short *)(cur_pkt_thin + 0x14) = ts6 + uVar1;
  }
  cur_pkt_thin = Render_gPacketPtr;
  prev_pkt_thin = Render_gPalettePtr;
  ts6 = tv.fxThin;
  if (((int)tv.y < (int)tv.fxThin) && ((int)tv.fxThin < (int)tv.y + (int)tv.h)) {
    AddPrim(prev_pkt_thin,cur_pkt_thin);
    Render_gPacketPtr = Render_gPacketPtr + 0x18;
    cur_pkt_thin[7] = 0x2a;
    cur_pkt_thin[3] = 5;
    ts7 = tv.x;
    *(short *)(cur_pkt_thin + 10) = ts6;
    *(short *)(cur_pkt_thin + 8) = ts7;
    ts7 = tv.x;
    ts5 = tv.w;
    *(short *)(cur_pkt_thin + 0xe) = ts6;
    *(short *)(cur_pkt_thin + 0xc) = ts7 + ts5;
    ts7 = tv.x;
    *(short *)(cur_pkt_thin + 0x12) = ts6 + 1;
    *(short *)(cur_pkt_thin + 0x10) = ts7;
    ts7 = tv.x;
    uVar1 = tv.w;
    abr = (u_int)uVar1;
    *(short *)(cur_pkt_thin + 0x16) = ts6 + 1;
    cur_pkt_thin[6] = 10;
    cur_pkt_thin[5] = 10;
    cur_pkt_thin[4] = 10;
    *(u_short *)(cur_pkt_thin + 0x14) = ts7 + uVar1;
  }
  FeDraw_SetABRMode(abr);
  if ((tv.flags & 0x20) != 0) {
    stripe_x = (u_short)tv.x + 4 & 0xfffffffc;
    if ((int)(short)stripe_x < (int)tv.x + (int)tv.w) {
      do {
        abr = (u_int)(short)stripe_x;
        PSXDrawTransSquare(0xa0a0a,(int)(short)stripe_x,(int)tv.y,1,(int)tv.h,1);
        stripe_x = stripe_x + 4;
      } while ((int)(stripe_x * 0x10000) >> 0x10 < (int)tv.x + (int)tv.w);
    }
    FeDraw_SetABRMode(abr);
  }
  return;
}



/* ---- DrawTV  [FETV.CPP:82-284] SLD-VERIFIED ---- */

extern "C" void DrawTV(tTVConfig &tv)

{
  bool bVar1;
  short ts10;
  short ts11;
  short ts4;
  short ts5;
  short ts13;
  int rng_word;
  int noise_select;
  short ts12;
  int tintRed;
  short destBright_us;
  int destBright_int;
  int state;
  u_int tu15;
  int ti16;
  int transStep_or_brt;
  int ti17;
  int tu18;
  int destBrightness;
  u_int tu21;
  short tu17;
  int ti10;
  short ts20;
  int videoY_2;
  int tvY;
  short tu20;
  int tint_2;
  u_int tu24;
  u_char do_tint;
  short tu1;
  short ts1;
  u_char bVar4;
  u_short tu2;
  u_short tu3;
  u_char *prev_pkt_b;
  tTexture_ShapeInfo *noiseShape;
  u_char *cur_pkt_a;
  u_char *tp10;
  u_short tu4;
  
  rng_word = randPSX();
  noiseShape = gHelpShapes;
  noise_select = rng_word & 3;
  destBrightness = (int)tv.destBrightness;
  tint_2 = tv.tint;
  ts1 = tv.x;
  tu2 = tv.y;
  tvY = (int)tu2;
  ts13 = tv.w;
  tu3 = tv.h;
  bVar1 = (tv.flags & 2) == 0;
  if (bVar1) {
    tint_2 = 0x808080;
  }
  do_tint = (u_int)!bVar1;
  destBright_us = tv.destBrightness;
  destBright_int = (int)(u_short)destBright_us;
  if (tv.transition == destBright_int) {
DrawTV_stateFetch:
    state = tv.state;
  }
  else {
    if ((tv.transition < destBright_int) &&
        (ts12 = (short)nfs4_mips_sign_extend(
             (u_int)nfs4_mips_addu_s32((int)(u_short)tv.transition,4),16),
         (u_int)nfs4_mips_subu_s32(tv.state,(int)tv_StateOn) < 2U)
       ) {
      tv.transition = ts12;
      bVar4 = destBright_int < ts12;
DrawTV_brightStep:
      if ((bool)bVar4) {
        tv.transition = destBright_us;
      }
      goto DrawTV_stateFetch;
    }
    state = tv.state;
    if ((state == tv_TransitionOff) || (state == tv_StateOn)) {
      destBright_us = tv.destBrightness;
      ts12 = (short)nfs4_mips_sign_extend(
           (u_int)nfs4_mips_addu_s32((int)(u_short)tv.transition,-8),16);
      tv.transition = ts12;
      bVar4 = (int)ts12 < (int)(u_int)(u_short)destBright_us;
      goto DrawTV_brightStep;
    }
  }
  if (state == tv_StateOn) {
DrawTV_stateOn:
    tu4 = tv.destBrightness;
  }
  else {
    if (state < 2) {
      if (state != tv_StateOff) {
        tintRed = (u_int)tint_2 >> 0x10 & 0xff;
        goto DrawTV_emitTinted;
      }
      goto DrawTV_stateOn;
    }
    if (state == tv_TransitionOn) {
      if ((int)tv.transition == (u_int)tv.destBrightness) {
        tv.state = tv_StateOn;
      }
    }
    else {
        if (state != tv_TransitionOff) {
          tintRed = (u_int)tint_2 >> 0x10 & 0xff;
          goto DrawTV_emitTinted;
      }
      if ((int)tv.transition == (u_int)tv.destBrightness) {
        tv.state = tv_StateOff;
      }
    }
    do_tint = 1;
    tu4 = tv.transition;
  }
  destBrightness = (int)tu4;
  tintRed = (u_int)tint_2 >> 0x10 & 0xff;
DrawTV_emitTinted:
  videoY_2 = nfs4_mips_sra_s32(nfs4_mips_sll_s32(destBrightness,0x10),0x10);
  tu18 = (tint_2 & 0xffU) * videoY_2 >> 7;
  tu24 = ((u_int)(tintRed * videoY_2) >> 7) << 0x10 |
         (((u_int)tint_2 >> 8 & 0xff) * videoY_2 >> 7) << 8 | tu18;
  if ((tv.flags & 8) == 0) {
    DrawTVLines(tv);
  }
  tp10 = Render_gPacketPtr;
  cur_pkt_a = Render_gPalettePtr;
  if ((tv.flags & 0x10) == 0) {
    if (tv.state != tv_StateOn) {
      AddPrim(cur_pkt_a,tp10);
      Render_gPacketPtr = Render_gPacketPtr + 0x28;
      tu15 = (u_int)nfs4_mips_subu_s32(
           0x40,nfs4_mips_sra_s32(nfs4_mips_sll_s32(destBrightness,0x10),0x11));
      *(u_int *)(tp10 + 4) = tu15 * 0x10000 | tu15 * 0x100 | tu15;
      SetPolyFT4((POLY_FT4 *)tp10);
      SetSemiTrans(tp10,1);
      SetShadeTex(tp10,0);
      *(short *)(tp10 + 8) = ts1;
      *(u_short *)(tp10 + 10) = tu2;
      *(u_short *)(tp10 + 0x12) = tu2;
      *(short *)(tp10 + 0x18) = ts1;
      *(short *)(tp10 + 0x10) = ts1 + ts13;
      *(short *)(tp10 + 0x20) = ts1 + ts13;
      tu20 = (short)(tvY + (u_int)tu3);
      *(short *)(tp10 + 0x1a) = tu20;
      *(short *)(tp10 + 0x22) = tu20;
      tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
      ti16 = ((int)noiseShape[noise_select + 0x22].shapex -
             (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
      tp10[0xc] = (char)(ti16 / (int)tu15);
      tp10[0xd] = (char)noiseShape[noise_select + 0x22].shapey;
      tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
      transStep_or_brt =
           ((int)noiseShape[noise_select + 0x22].shapex -
           (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
      tp10[0x14] = (char)noiseShape[noise_select + 0x22].width +
                   (char)(transStep_or_brt / (int)tu15);
      tp10[0x15] = (char)noiseShape[noise_select + 0x22].shapey;
      tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
      ti17 = ((int)noiseShape[noise_select + 0x22].shapex -
             (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
      tp10[0x1c] = (char)(ti17 / (int)tu15);
      tp10[0x1d] = (char)noiseShape[noise_select + 0x22].height +
                   (char)noiseShape[noise_select + 0x22].shapey;
      tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
      ti17 = ((int)noiseShape[noise_select + 0x22].shapex -
             (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
      tp10[0x24] = (char)noiseShape[noise_select + 0x22].width + (char)(ti17 / (int)tu15);
      tp10[0x25] = (char)noiseShape[noise_select + 0x22].height +
                   (char)noiseShape[noise_select + 0x22].shapey;
      *(u_short *)(tp10 + 0x16) =
           ((u_char)(*((u_char *)&noiseShape[noise_select + 0x22] + 9)) & 3) << 7 |
           (short)(noiseShape[noise_select + 0x22].shapey & 0x100U) >> 4 | 0x60U |
           (u_short)(((u_short)noiseShape[noise_select + 0x22].shapex & 0x3c0) >> 6) |
           (noiseShape[noise_select + 0x22].shapey & 0x200U) << 2;
      ts10 = GetClut((noiseShape[noise_select + 0x22].clutID & 0x3fU) << 4,
                        noiseShape[noise_select + 0x22].clutID >> 6);
      *(short *)(tp10 + 0xe) = ts10;
      prev_pkt_b = Render_gPacketPtr;
      cur_pkt_a = Render_gPalettePtr;
      if ((tv.flags & 4) != 0) {
        ti17 = nfs4_mips_addu_s32(
             nfs4_mips_subu_s32((int)(u_short)tv.flip_axis,tvY),1);
        if (nfs4_mips_sll_s32(ti17,0x10) < 0) {
          ti17 = nfs4_mips_negu_s32(ti17);
        }
        ts12 = (short)nfs4_mips_sra_s32(
             nfs4_mips_sll_s32(nfs4_mips_sll_s32(ti17,1),0x10),0x10);
        if (0x80 < (int)ts12) {
          ts12 = 0x80;
        }
        ti17 = nfs4_mips_addu_s32(
             nfs4_mips_subu_s32((int)(u_short)tv.flip_axis,
                  nfs4_mips_addu_s32(tvY,(int)(u_short)tu3)),1);
        if (nfs4_mips_sll_s32(ti17,0x10) < 0) {
          ti17 = nfs4_mips_negu_s32(ti17);
        }
        ts11 = (short)nfs4_mips_sra_s32(
             nfs4_mips_sll_s32(nfs4_mips_sll_s32(ti17,1),0x10),0x10);
        if (0x80 < (int)ts11) {
          ts11 = 0x80;
        }
        ti17 = nfs4_mips_mult_s32(nfs4_mips_subu_s32(0x80,videoY_2),
                                  nfs4_mips_subu_s32(0x80,(int)ts12));
        AddPrim(cur_pkt_a,prev_pkt_b);
        Render_gPacketPtr = Render_gPacketPtr + 0x34;
        if (ti17 < 0) {
          ti17 = nfs4_mips_addu_s32(ti17,0x7f);
        }
        tu15 = (u_int)nfs4_mips_sra_s32(ti17,7);
        ti17 = nfs4_mips_mult_s32(nfs4_mips_subu_s32(0x80,videoY_2),
                                  nfs4_mips_subu_s32(0x80,(int)ts11));
        tu15 = tu15 << 0x10 | tu15 << 8 | tu15;
        *(u_int *)(prev_pkt_b + 0x10) = tu15;
        *(u_int *)(prev_pkt_b + 4) = tu15;
        if (ti17 < 0) {
          ti17 = nfs4_mips_addu_s32(ti17,0x7f);
        }
        tu15 = (u_int)nfs4_mips_sra_s32(ti17,7);
        tu15 = tu15 << 0x10 | tu15 << 8 | tu15;
        *(u_int *)(prev_pkt_b + 0x28) = tu15;
        *(u_int *)(prev_pkt_b + 0x1c) = tu15;
        prev_pkt_b[7] = 0x3e;
        prev_pkt_b[3] = 0xc;
        *(short *)(prev_pkt_b + 8) = ts1;
        tu1 = tv.flip_axis;
        *(short *)(prev_pkt_b + 0x14) = ts1 + ts13;
        *(u_short *)(prev_pkt_b + 10) = tu1 * 2 - tu2;
        tu4 = tv.flip_axis;
        *(short *)(prev_pkt_b + 0x20) = ts1;
        *(u_short *)(prev_pkt_b + 0x16) = tu4 * 2 - tu2;
        tu4 = tv.flip_axis;
        *(short *)(prev_pkt_b + 0x2c) = ts1 + ts13;
        *(u_short *)(prev_pkt_b + 0x22) = (tu4 * 2 - tu2) - tu3;
        *(u_short *)(prev_pkt_b + 0x2e) = (tv.flip_axis * 2 - tu2) - tu3;
        tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
        ti17 = ((int)noiseShape[noise_select + 0x22].shapex -
               (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
        prev_pkt_b[0xc] = (char)(ti17 / (int)tu15);
        prev_pkt_b[0xd] = (char)noiseShape[noise_select + 0x22].shapey + -1;
        tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
        ti17 = ((int)noiseShape[noise_select + 0x22].shapex -
               (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
        prev_pkt_b[0x18] = (char)noiseShape[noise_select + 0x22].width + (char)(ti17 / (int)tu15);
        prev_pkt_b[0x19] = (char)noiseShape[noise_select + 0x22].shapey + -1;
        tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
        ti17 = ((int)noiseShape[noise_select + 0x22].shapex -
               (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
        prev_pkt_b[0x24] = (char)(ti17 / (int)tu15);
        prev_pkt_b[0x25] =
             (char)noiseShape[noise_select + 0x22].height +
             (char)noiseShape[noise_select + 0x22].shapey + -1;
        tu15 = (u_int)(u_char)noiseShape[noise_select + 0x22].depth;
        ti17 = ((int)noiseShape[noise_select + 0x22].shapex -
               (int)(short)(noiseShape[noise_select + 0x22].shapex & 0xffc0)) * 0x10;
        prev_pkt_b[0x30] = (char)noiseShape[noise_select + 0x22].width + (char)(ti17 / (int)tu15);
        prev_pkt_b[0x31] =
             (char)noiseShape[noise_select + 0x22].height +
             (char)noiseShape[noise_select + 0x22].shapey + -1;
        *(u_short *)(prev_pkt_b + 0x1a) =
             ((u_char)(*((u_char *)&noiseShape[noise_select + 0x22] + 9)) & 3) << 7 |
             (short)(noiseShape[noise_select + 0x22].shapey & 0x100U) >> 4 | 0x60U |
             (u_short)(((u_short)noiseShape[noise_select + 0x22].shapex & 0x3c0) >> 6) |
             (noiseShape[noise_select + 0x22].shapey & 0x200U) << 2;
        ts4 = GetClut((noiseShape[noise_select + 0x22].clutID & 0x3fU) << 4,
                         noiseShape[noise_select + 0x22].clutID >> 6);
        *(short *)(prev_pkt_b + 0xe) = ts4;
      }
    }
    tp10 = Render_gPacketPtr;
    cur_pkt_a = Render_gPalettePtr;
    if (tv.state != tv_StateOff) {
      AddPrim(cur_pkt_a,tp10);
      Render_gPacketPtr = Render_gPacketPtr + 0x28;
      *(u_int *)(tp10 + 4) = tu24;
      SetPolyFT4((POLY_FT4 *)tp10);
      SetSemiTrans(tp10,0);
      SetShadeTex(tp10,do_tint ^ 1);
      *(short *)(tp10 + 8) = ts1;
      *(u_short *)(tp10 + 10) = tu2;
      ts20 = ts1 + ts13;
      *(short *)(tp10 + 0x10) = ts20;
      *(u_short *)(tp10 + 0x12) = tu2;
      *(short *)(tp10 + 0x18) = ts1;
      *(short *)(tp10 + 0x20) = ts20;
      tu17 = (short)(tvY + (u_int)tu3);
      *(short *)(tp10 + 0x1a) = tu17;
      *(short *)(tp10 + 0x22) = tu17;
      tp10[0xc] = tv.u;
      tp10[0xd] = tv.v;
      tp10[0x14] = tv.u + tv.uw;
      tp10[0x15] = tv.v;
      tp10[0x1c] = tv.u;
      tp10[0x1d] = tv.v + tv.vh;
      tp10[0x24] = tv.u + tv.uw;
      tp10[0x25] = tv.v + tv.vh;
      *(u_short *)(tp10 + 0x16) = tv.tpage;
      *(u_short *)(tp10 + 0xe) = tv.clut;
      tp10 = Render_gPacketPtr;
      cur_pkt_a = Render_gPalettePtr;
      if ((tv.flags & 4) != 0) {
        ti17 = nfs4_mips_addu_s32(
             nfs4_mips_subu_s32((int)(u_short)tv.flip_axis,tvY),1);
        if (nfs4_mips_sll_s32(ti17,0x10) < 0) {
          ti17 = nfs4_mips_negu_s32(ti17);
        }
        ts5 = (short)nfs4_mips_sra_s32(
             nfs4_mips_sll_s32(nfs4_mips_sll_s32(ti17,1),0x10),0x10);
        if (0x80 < (int)ts5) {
          ts5 = 0x80;
        }
        ti17 = nfs4_mips_addu_s32(
             nfs4_mips_subu_s32((int)(u_short)tv.flip_axis,
                  nfs4_mips_addu_s32(tvY,(int)(u_short)tu3)),1);
        if (nfs4_mips_sll_s32(ti17,0x10) < 0) {
          ti17 = nfs4_mips_negu_s32(ti17);
        }
        ts13 = (short)nfs4_mips_sra_s32(
             nfs4_mips_sll_s32(nfs4_mips_sll_s32(ti17,1),0x10),0x10);
        if (0x80 < (int)ts13) {
          ts13 = 0x80;
        }
        tu15 = tu24 >> 0x10 & 0xff;
        ti17 = 0x80 - ts5;
        tu21 = tu24 >> 8 & 0xff;
        ti10 = 0x80 - ts13;
        AddPrim(cur_pkt_a,tp10);
        Render_gPacketPtr = Render_gPacketPtr + 0x34;
        tp10[3] = 0xc;
        tu24 = (tu15 * ti17 >> 7) << 0x10 | (tu21 * ti17 >> 7) << 8 | (tu18 & 0xffU) * ti17 >> 7;
        *(short *)(tp10 + 8) = ts1;
        *(u_int *)(tp10 + 0x10) = tu24;
        *(u_int *)(tp10 + 4) = tu24;
        tu24 = (tu15 * ti10 >> 7) << 0x10 | (tu21 * ti10 >> 7) << 8 | (tu18 & 0xffU) * ti10 >> 7;
        *(u_int *)(tp10 + 0x28) = tu24;
        *(u_int *)(tp10 + 0x1c) = tu24;
        tp10[7] = 0x3c;
        tu4 = tv.flip_axis;
        *(short *)(tp10 + 0x14) = ts20;
        *(u_short *)(tp10 + 10) = tu4 * 2 - tu2;
        tu4 = tv.flip_axis;
        *(short *)(tp10 + 0x20) = ts1;
        *(u_short *)(tp10 + 0x16) = tu4 * 2 - tu2;
        tu4 = tv.flip_axis;
        *(short *)(tp10 + 0x2c) = ts20;
        *(u_short *)(tp10 + 0x22) = (tu4 * 2 - tu2) - tu3;
        *(u_short *)(tp10 + 0x2e) = (tv.flip_axis * 2 - tu2) - tu3;
        tp10[0xc] = tv.u;
        tp10[0xd] = tv.v + 0xff;
        tp10[0x18] = tv.u + tv.uw;
        tp10[0x19] = tv.v + 0xff;
        tp10[0x24] = tv.u;
        tp10[0x25] = tv.v + tv.vh + 0xff;
        tp10[0x30] = tv.u + tv.uw;
        tp10[0x31] = tv.v + tv.vh + 0xff;
        *(u_short *)(tp10 + 0x1a) = tv.tpage;
        *(u_short *)(tp10 + 0xe) = tv.clut;
      }
    }
  }
  return;
}



/* ---- InitTV  [FETV.CPP:287-309] SLD-VERIFIED ---- */

extern "C" void InitTV(tTVConfig &tv,tTexture_ShapeInfo *textures,short index)

{
  u_char uVar1;
  u_short uVar2;
  u_int uVar3;
  int iVar4;
  int iVar5;
  tTexture_ShapeInfo &texture = textures[(int)index];
  
  tv.state = tv_StateOff;
  tv.flags = 0;
  tv.x = -texture.centerx;
  tv.y = -texture.centery;
  tv.w = texture.width;
  tv.h = texture.height;
  uVar3 = (u_int)(u_char)texture.depth;
  iVar4 = ((int)texture.shapex -
          (int)(short)((u_short)texture.shapex & 0xffc0)) * 0x10;
  tv.u = (u_char)(iVar4 / (int)uVar3);
  uVar1 = (u_char)texture.shapey;
  tv.vh = (u_char)tv.h;
  tv.uw = (u_char)tv.w;
  tv.v = uVar1;
  tv.shapex = (u_short)texture.shapex;
  tv.shapey = (u_short)texture.shapey;
  tv.clutID = (u_short)texture.clutID;
  tv.shapeType = (u_char)texture.type & 3;
  uVar2 = GetClut((tv.clutID & 0x3f) << 4,(u_int)(tv.clutID >> 6));
  tv.clut = uVar2;
  uVar2 = (u_short)texture.shapey;
  tv.tpage = ((u_char)texture.type & 3) << 7 | (short)(uVar2 & 0x100) >> 4 |
              (u_short)(((u_short)texture.shapex & 0x3c0) >> 6) |
              (uVar2 & 0x200) << 2;
  iVar4 = randPSX();
  iVar5 = tv.h * 0x30;
  tv.fxWide = (short)(iVar4 % iVar5);
  iVar4 = randPSX();
  iVar5 = tv.h * 0x30;
  tv.flip_axis = 0;
  tv.transition = 0;
  tv.tint = 0x808080;
  tv.destBrightness = 0x80;
  tv.fxThin = (short)(iVar4 % iVar5);
  return;
}



/* ---- TurnOffTV  [FETV.CPP:313-315] SLD-VERIFIED ---- */

extern "C" void TurnOffTV(tTVConfig &tv)

{
  tv.state = tv_TransitionOff;
  tv.destBrightness = 0;
  return;
}



/* ---- TurnOnTV  [FETV.CPP:319-321] SLD-VERIFIED ---- */

extern "C" void TurnOnTV(tTVConfig &tv)

{
  
  tv.state = tv_TransitionOn;
  tv.destBrightness = 0x80;
  return;
}



/* end of fetv.cpp */
