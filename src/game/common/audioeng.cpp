/* game/common/audioeng.cpp -- RECONSTRUCTED from Ghidra 12.0.4 decompile + PsyQ SYM v3.
 *   bworld.obj (GAME\COMMON\bworld.cpp) = 20 fns: BWorld road geometry build/render
 *   (chunk visibility, build lists, spike belt, glare effects, render contexts). Self-contained.
 *   Verified vs disasm-v2.txt. NOT original source; SYM-faithful, recompilable C++.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "audioeng_externs.h"

/* ---- audioeng.obj-owned globals (SYM-typed; .data=real EXE bytes, .bss=zero) ---- */
AudioEng_t   *AudioEng_g[2];   /* @0x8013c734  (bss(zero)) */


/* ---- intra-TU forward declarations ---- */
void AudioEng_Set(int player,int vol,int esp,int gas,int cam,int dop,int azi,int dir);
void AudioEng_Update(void);
void AudioEng_LoadDef(char *filename,char *name,int handle,long offset,long size,AudioEng_tDef **ed);
int AudioEng_StartUp(int player,char *carname);
void AudioEng_StartServer(void);
void AudioEng_StopServer(void);
void AudioEng_Pause(void);
void AudioEng_Resume(void);
void AudioEng_CleanUp(void);


/* ---- AudioEng_Set__Fiiiiiiii  [@0x8007b5a8] ---- */
void AudioEng_Set(int player,int vol,int esp,int gas,int cam,int dop,int azi,int dir)
{
  AudioEng_t*g;
  AudioEng_tAdjustments*a;
  AudioEng_tState*s;
  int value;
  int exhaustDelta;
  u_char boost;

  if ((u_int)player >= 2) {
    return;
  }
  g = AudioEng_g[player];
  if (g == (AudioEng_t *)0x0) {
    return;
  }
  if ((g->plypos == '\x0f') &&
      (((nfs4_mips_addu_s32((int)(u_char)g->setpos,1)) & 1) != 0)) {
    return;
  }

  a = &g->adjust;
  s = g->queue + (u_char)g->setpos;
  value = nfs4_mips_sra_s32(
      nfs4_mips_mult_s32((int)a->timbreScale,esp),0xe);
  s->esp = (u_short)(value < 0x200 ? value : 0x1ff);

  if (Cars_gList[player]->carInfo->carType == 0x1c) {
    value = nfs4_mips_addu_s32(nfs4_mips_sra_s32(esp,2),0xc000);
  }
  else {
    value = nfs4_mips_addu_s32(esp,0x3333);
  }
  value = fixedmult(value,dop);
  s->dop = (u_short)nfs4_mips_sra_s32(
      nfs4_mips_mult_s32((int)a->pitchScale,value),10);

  value = nfs4_mips_addu_s32(
      nfs4_mips_addu_s32(gas,nfs4_mips_sra_s32(gas,5)),
      nfs4_mips_sra_s32(gas,6));
  s->gas = (u_char)(value < 0x81 ? value : 0x80);

  if (cam == 0) {
    s->exh = a->inCarExhaust;
    if (GameSetup_gData.commMode == 1) {
      s->sep = 0;
      s->azi = (u_short)azi;
    }
    else {
      s->azi = 0;
      s->sep = 0x3fff;
    }
    boost = a->inCarBoost;
  }
  else {
    s->exh = a->outCarExhaust;
    if (dir < 0) {
      value = nfs4_mips_mult_s32(
          nfs4_mips_mult_s32(dir,(int)a->fwdEngBoost),(int)s->exh);
    }
    else {
      value = nfs4_mips_mult_s32(
          nfs4_mips_mult_s32(dir,(int)a->rwdExhBoost),
          nfs4_mips_subu_s32(0x80,(int)s->exh));
    }
    exhaustDelta = nfs4_mips_sra_s32(value,7);
    if (exhaustDelta < 0) {
      exhaustDelta = nfs4_mips_addu_s32(exhaustDelta,0xffff);
    }
    exhaustDelta = nfs4_mips_sra_s32(exhaustDelta,0x10);
    s->exh = (u_char)nfs4_mips_addu_s32((int)s->exh,exhaustDelta);
    s->azi = (u_short)azi;
    s->sep = 0;
    boost = a->outCarBoost;
  }

  value = nfs4_mips_sra_s32(nfs4_mips_mult_s32(vol,(int)boost),6);
  s->vol = (u_short)(value < 0x800 ? value : 0x7ff);
  g->setpos = (char)(nfs4_mips_addu_s32((int)(u_char)g->setpos,1) & 0xf);
  return;
}

/* ---- AudioEng_Update__Fv  [@0x8007b824] ---- */
void AudioEng_Update(void)
{
  int player;
  AudioEng_t*g;
  int n;
  AudioEng_tState*s;
  int tick;
  u_long vol;
  SNDPLAYOPTS playopts;
  u_short leftazim;
  u_short rightazim;
  short sVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  u_int uVar5;
  char cVar6;
  u_int uVar7;
  int iVar8;
  int iVar9;
  AudioEng_t *pAVar10;
  AudioEng_t *pAVar11;
  AudioEng_tState *pAVar12;
  AudioEng_t *pAVar13;
  u_short uVar14;
  u_short uVar15;
  AudioEng_t *pAVar16;
  int local_30;
  
  local_30 = 0;
  do {
    if ((1 < local_30) || (pAVar13 = AudioEng_g[local_30], pAVar13 == (AudioEng_t *)0x0)) {
      return;
    }
    pAVar12 = pAVar13->queue + (u_char)pAVar13->plypos;
    iVar4 = gettick();
    if (pAVar13->plypos != pAVar13->setpos) {
      iVar8 = gettick();
      if (pAVar13->tick < iVar8) {
        pAVar13->tick = iVar4 + 2;
        pAVar10 = pAVar13;
        pAVar11 = pAVar13;
        for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
          if (-1 < pAVar10->chan[0].patchnum) {
            uVar7 = (u_int)pAVar12->esp;
            iVar8 = (int)pAVar10->chan[0].min;
            if (((int)uVar7 < iVar8) || ((int)pAVar10->chan[0].max <= (int)uVar7)) {
              iVar8 = 0;
            }
            else {
              iVar8 = (int)pAVar10->chan[0].xlate[uVar7 - iVar8];
            }
            iVar9 = 0;
            if (iVar8 != 0) {
              if (iVar4 < 8) {
                uVar7 = 0x80 - pAVar12->gas;
              }
              else {
                uVar7 = (u_int)pAVar12->gas;
              }
              if (pAVar10->chan[0].patchnum < '@') {
                uVar5 = (u_int)pAVar12->exh;
code_r_8007b9f4:
                uVar5 = (u_int)(u_char)Xfade[uVar5];
              }
              else {
                if (pAVar12->sep == 0) {
                  uVar5 = 0x80 - pAVar12->exh;
                  goto code_r_8007b9f4;
                }
                uVar5 = (int)((u_int)(u_char)Xfade[0x80 - (u_int)pAVar12->exh] * 0x2f) >> 6;
              }
              iVar9 = iVar8 * (u_int)(u_char)Xfade[uVar7] * uVar5;
            }
            uVar7 = iVar9 * (u_int)pAVar12->vol >> 0x15;
            if (0x7f < uVar7) {
              uVar7 = 0x7f;
            }
            pAVar11->vol[0] = uVar7;
            pAVar13->azi = (u_int)pAVar12->azi;
            pAVar13->sep = (u_int)pAVar12->sep;
            pAVar13->dop = (u_int)pAVar12->dop;
          }
          pAVar11 = (AudioEng_t *)&(pAVar11->adjust).rwdExhBoost;
          pAVar10 = (AudioEng_t *)pAVar10->vol;
        }
        pAVar13->plypos = pAVar13->plypos + 1U & 0xf;
      }
    }
    pAVar10 = pAVar13;
    pAVar11 = pAVar13;
    pAVar16 = pAVar13;
    for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
      cVar6 = pAVar10->chan[0].patchnum;
      if (-1 < cVar6) {
        if (pAVar16->vol[0] == 0) {
          uVar7 = pAVar10->left[0].handle;
          if (uVar7 != 0xffffffff) {
            SNDstop(uVar7);
            uVar7 = pAVar10->right[0].handle;
            if (uVar7 != 0xffffffff) {
              SNDstop(uVar7);
            }
            pAVar10->left[0].handle = -1;
            pAVar10->right[0].handle = -1;
          }
        }
        else {
          if (cVar6 < '@') {
            uVar15 = (u_short)pAVar13->azi;
            uVar14 = uVar15;
          }
          else {
            sVar1 = (short)pAVar13->azi;
            sVar2 = (short)pAVar13->sep;
            uVar15 = sVar1 + sVar2;
            uVar14 = sVar1 - sVar2;
          }
          SNDplaysetdef(&playopts);
          playopts.bhandle = pAVar13->bhandle;
          playopts.patnum = (int)pAVar10->chan[0].patchnum;
          playopts.vol = 0;
          playopts.pitchmult = (u_short)pAVar13->dop;
          playopts.use3dpos = 1;
          playopts.elevation = 0;
          iVar8 = pAVar10->left[0].handle;
          if (iVar8 == -1) {
            playopts.azimuth = uVar14;
            iVar8 = SNDplay(&playopts);
            pAVar10->left[0].handle = iVar8;
            pAVar11->delay[0] = '\x02';
            pAVar10->left[0].vol = '\0';
            pAVar10->left[0].azim = uVar14;
            pAVar10->left[0].pitch = (u_short)pAVar13->dop;
          }
          else {
            if (((pAVar13->sep == 0) || (pAVar10->chan[0].patchnum < '@')) ||
               (pAVar10->right[0].handle != -1)) {
              iVar8 = (int)pAVar10->left[0].vol;
              iVar9 = pAVar16->vol[0];
              if (iVar8 != iVar9) {
                if (iVar9 < iVar8) {
                  iVar8 = iVar8 + -2;
                  bVar3 = iVar8 < iVar9;
                }
                else {
                  iVar8 = iVar8 + 2;
                  bVar3 = iVar9 < iVar8;
                }
                cVar6 = (char)iVar8;
                if (bVar3) {
                  cVar6 = (char)iVar9;
                }
                pAVar10->left[0].vol = cVar6;
                SNDvol(pAVar10->left[0].handle,(int)pAVar10->left[0].vol);
              }
            }
            if ((u_int)pAVar10->left[0].azim != (u_int)uVar14) {
              SND3dpos(pAVar10->left[0].handle,(u_int)uVar14,0);
              pAVar10->left[0].azim = uVar14;
            }
            if ((u_int)pAVar10->left[0].pitch != pAVar13->dop) {
              SNDpitchmult(pAVar10->left[0].handle,pAVar13->dop);
              pAVar10->left[0].pitch = (u_short)pAVar13->dop;
            }
            if ((pAVar10->chan[0].patchnum < '@') || (pAVar13->sep == 0)) {
              uVar7 = pAVar10->right[0].handle;
              if (uVar7 != 0xffffffff) {
                SNDstop(uVar7);
                pAVar10->right[0].handle = -1;
                pAVar11->delay[0] = '\x02';
              }
            }
            else if (pAVar10->right[0].handle == -1) {
              cVar6 = pAVar11->delay[0] + -1;
              pAVar11->delay[0] = cVar6;
              iVar8 = (int)cVar6;
              if (iVar8 == -1) {
                playopts.azimuth = uVar15;
                iVar8 = SNDplay(&playopts);
                pAVar10->right[0].handle = iVar8;
                pAVar10->right[0].vol = '\0';
                pAVar10->right[0].azim = uVar15;
LAB_8007bd18:
                pAVar10->right[0].pitch = (u_short)pAVar13->dop;
              }
            }
            else {
              iVar8 = (int)pAVar10->right[0].vol;
              iVar9 = pAVar16->vol[0];
              if (iVar8 != iVar9) {
                if (iVar9 < iVar8) {
                  iVar8 = iVar8 + -2;
                  bVar3 = iVar8 < iVar9;
                }
                else {
                  iVar8 = iVar8 + 2;
                  bVar3 = iVar9 < iVar8;
                }
                cVar6 = (char)iVar8;
                if (bVar3) {
                  cVar6 = (char)iVar9;
                }
                pAVar10->right[0].vol = cVar6;
                SNDvol(pAVar10->right[0].handle,(int)pAVar10->right[0].vol);
              }
              if ((u_int)pAVar10->right[0].azim != (u_int)uVar15) {
                SND3dpos(pAVar10->right[0].handle,(u_int)uVar15,0);
                pAVar10->right[0].azim = uVar15;
              }
              if ((u_int)pAVar10->right[0].pitch != pAVar13->dop) {
                SNDpitchmult(pAVar10->right[0].handle,pAVar13->dop);
                goto LAB_8007bd18;
              }
            }
          }
        }
      }
      pAVar11 = (AudioEng_t *)&(pAVar11->adjust).inCarExhaust;
      pAVar10 = (AudioEng_t *)pAVar10->vol;
      pAVar16 = (AudioEng_t *)&(pAVar16->adjust).rwdExhBoost;
    }
    local_30 = local_30 + 1;
  } while( true );
}

/* ---- AudioEng_LoadDef__FPcT0illPP13AudioEng_tDef  [@0x8007bddc] ---- */
void AudioEng_LoadDef(char *filename,char *name,int handle,long offset,long size,AudioEng_tDef **ed)
{
  AudioEng_tDef *pAVar1;
  
  pAVar1 = (AudioEng_tDef *)reservememadr(name,size,0x10);
  *ed = pAVar1;
  if (pAVar1 != (AudioEng_tDef *)0x0) {
    FILE_readsync(handle,offset,(intptr)*ed,size,0x64);   /* oracle 0x8007be1c: a0=h a1=off a2=*ed a3=size stk=0x64 */
  }
  return;
}

/* ---- AudioEng_StartUp__FiPc  [@0x8007be54] ---- */
int AudioEng_StartUp(int player,char *carname)
{
  AudioEng_tDef*cruisedef;
  AudioEng_tDef*loaddef;
  int tablesize;
  int i;
  int bankloaded;
  int spu;
  char filename[64];
  AudioEng_t*g;
  char*header;
  int handle;
  long size;
  long offset;
  char*current;
  int c;
  AudioEng_tChanAttr*chan;
  int j;
  bool bVar1;
  int iVar2;
  AudioEng_t *pAVar3;
  int iVar4;
  void *pThis;
  char *pdata;
  AudioEng_tDef **ed;
  u_char *dest;
  short *psVar5;
  AudioEng_t *pAVar6;
  int iVar7;
  AudioEng_t *pAVar8;
  char *pcVar9;
  AudioEng_tDef *pAVar10;
  AudioEng_tDef *pAVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  u_char *puVar16;
  u_int name;
  int iVar17;
  char acStack_80 [64];
  int local_40;
  long local_3c;
  u_int local_38;
  AudioEng_tDef *local_34;
  AudioEng_tDef *local_30 [2];
  
  if (1 < (u_int)player) {
    return 0;
  }
  name = 0;
  if (AudioEng_g[player] != (AudioEng_t *)0x0) {
    return 0;
  }
  iVar17 = 0;
  pAVar3 = (AudioEng_t *)reservememadr("Engine Audio",0x370,0);
  iVar15 = 0;
  AudioEng_g[player] = pAVar3;
  pAVar3->tables = (char *)0x0;
  pAVar3->tick = 0;
  pAVar3->azi = 0;
  pAVar3->sep = 0;
  pAVar3->dop = 0x1000;
  pAVar6 = pAVar3;
  pAVar8 = pAVar3;
  do {
    pAVar8->vol[0] = 0;
    pAVar6->left[0].handle = -1;
    pAVar6->right[0].handle = -1;
    pAVar6->chan[0].patchnum = -1;
    pAVar6->chan[0].min = 0x200;
    pAVar6->chan[0].max = 0x200;
    pAVar6->chan[0].xlate = (char *)0x0;
    pAVar6 = (AudioEng_t *)pAVar6->vol;
    iVar15 = iVar15 + 1;
    pAVar8 = (AudioEng_t *)&(pAVar8->adjust).rwdExhBoost;
  } while (iVar15 < 0x10);
  local_30[0] = (AudioEng_tDef *)0x0;
  local_34 = (AudioEng_tDef *)0x0;
  (pAVar3->adjust).inCarBoost = '2';
  (pAVar3->adjust).inCarExhaust = '\x1f';
  (pAVar3->adjust).outCarBoost = 0xa6;
  (pAVar3->adjust).outCarExhaust = '+';
  (pAVar3->adjust).fwdEngBoost = '@';
  (pAVar3->adjust).rwdExhBoost = 'y';
  (pAVar3->adjust).pitchScale = 'P';
  (pAVar3->adjust).timbreScale = 'h';
  pAVar3->setpos = '\0';
  pAVar3->plypos = '\0';
  bVar1 = false;
  if (GameSetup_gData.commMode == 1) {
    pcVar9 = "%s%sens.viv";
  }
  else {
    pcVar9 = "%s%seng.viv";
  }
  sprintf(acStack_80,pcVar9,Paths_Paths[28],carname);
  pcVar9 = (char *)loadbigfileheader(acStack_80,0x10);
  if (pcVar9 == (char *)0x0) {
    if (GameSetup_gData.commMode == 1) {
      pcVar9 = "%sp993ens.viv";
    }
    else {
      pcVar9 = "%sp993eng.viv";
    }
    sprintf(acStack_80,pcVar9,Paths_Paths[28]);
    pcVar9 = (char *)loadbigfileheader(acStack_80,0x10);
    if (pcVar9 == (char *)0x0) goto LAB_8007c1ac;
  }
  FILE_opensync(acStack_80,1,0x64,&local_40);   /* oracle 0x8007c03c: a3=&handle out */
  for (iVar15 = 0; iVar4 = bigcount(pcVar9), iVar15 < iVar4;
      iVar15 = iVar15 + 1) {
    pThis = locatebigentry(pcVar9,(char *)0x0,iVar15,&local_3c,&local_38);   /* oracle 0x8007c06c: a2=i a3=&offset stk=&size */
    iVar4 = wildcard((u_char *)pThis,"*.bnk");
    if ((iVar4 == 0) || (bVar1)) {
      iVar4 = wildcard((u_char *)pThis,"*.ltb");
      if ((iVar4 == 0) || (local_34 != (AudioEng_tDef *)0x0)) {
        iVar4 = wildcard((u_char *)pThis,"*.ctb");
        if ((iVar4 == 0) || (local_30[0] != (AudioEng_tDef *)0x0)) goto LAB_8007c190;
        ed = local_30;
      }
      else {
        ed = &local_34;
      }
      AudioEng_LoadDef(acStack_80,(char *)pThis,local_40,local_3c,local_38,ed);
    }
    else {
      pdata = (char *)reservememadr(pThis,local_38,0x10);
      if (pdata != (char *)0x0) {
        bVar1 = true;
        FILE_readsync(local_40,local_3c,(intptr)pdata,local_38,0x64);   /* oracle 0x8007c0c8: a0=h a1=off a2=pdata a3=size stk=0x64 */
        iVar17 = AudioCmn_AddBank((char *)pThis,local_38,pdata,player);
        pAVar3->bhandle = (char)gSndBnk[player].bnkID;
      }
    }
LAB_8007c190: ;   /* empty stmt: gcc2.7.2 rejects label before '}' */
  }
  FILE_closesync(local_40,100);   /* oracle 0x8007c198/c1a0: a0=handle a1=0x64 (both were dropped) */
  purgememadr(pcVar9);
LAB_8007c1ac:
  if (!bVar1) {
    return iVar17;
  }
  if (local_30[0] == (AudioEng_tDef *)0x0) {
    return iVar17;
  }
  iVar15 = 0;
  if (local_34 == (AudioEng_tDef *)0x0) {
    return iVar17;
  }
  do {
    if (1 < iVar15) {
      dest = (u_char *)reservememadr("Engine Tables",name,0)
      ;
      pAVar3->tables = (char *)dest;
      for (iVar15 = 0; iVar15 < 2; iVar15 = iVar15 + 1) {
        iVar4 = 0;
        pAVar11 = local_30[0];
        if (iVar15 != 0) {
          pAVar11 = local_34;
        }
        iVar12 = 0;
        for (; iVar4 < 8; iVar4 = iVar4 + 1) {
          psVar5 = (short *)((int)&pAVar3->chan[0].min + iVar12);
          if (iVar15 != 0) {
            psVar5 = psVar5 + 0x30;
          }
          iVar13 = (int)*psVar5;
          puVar16 = dest;
          if (psVar5[1] != iVar13) {
            iVar14 = psVar5[1] - iVar13;
            *(u_char **)(psVar5 + 2) = dest;
            puVar16 = dest + iVar14;
            memcpy(dest,(u_char *)(pAVar11->pvoltable[0]->xlate + iVar13),iVar14);
          }
          pAVar11 = (AudioEng_tDef *)&pAVar11->ver;
          iVar12 = iVar12 + 0xc;
          dest = puVar16;
        }
      }
      purgememadr(local_34);
      purgememadr(local_30[0]);
      return iVar17;
    }
    pAVar11 = local_30[0];
    if (iVar15 != 0) {
      pAVar11 = local_34;
    }
    iVar4 = 0;
    if (pAVar11->resolved == '\0') {
      iVar14 = 0;
      iVar13 = 0x148;
      iVar12 = 0x128;
      pAVar10 = pAVar11;
      for (; iVar4 < 8; iVar4 = iVar4 + 1) {
        if (-1 < pAVar11->patchnum[iVar4]) {
          psVar5 = (short *)((int)&pAVar3->chan[0].min + iVar14);
          pAVar10->pvoltable[0] =
               (AudioEng_tTable *)
               (pAVar10->pvoltable[0]->xlate + (int)(pAVar11->patchnum + iVar12 + -0x20));
          pAVar10->pbendtable[0] =
               (AudioEng_tTable *)
               (pAVar10->pbendtable[0]->xlate + (int)(pAVar11->patchnum + iVar13 + -0x20));
          if (iVar15 != 0) {
            psVar5 = psVar5 + 0x30;
          }
          *(char *)(psVar5 + 4) = pAVar11->patchnum[iVar4];
          iVar7 = 0;
          if (pAVar10->pvoltable[0]->xlate[0] == '\0') {
            iVar2 = 1;
            do {
              iVar7 = iVar2;
              bVar1 = iVar7 < 0x200;
              if (!bVar1) goto LAB_8007c2c4;
              iVar2 = iVar7 + 1;
            } while (pAVar10->pvoltable[0]->xlate[iVar7] == '\0');
          }
          bVar1 = iVar7 < 0x200;
LAB_8007c2c4:
          *psVar5 = (short)iVar7;
          if (bVar1) {
            do {
              if (pAVar10->pvoltable[0]->xlate[iVar7] == '\0') break;
              iVar7 = iVar7 + 1;
            } while (iVar7 < 0x200);
          }
          psVar5[1] = (short)iVar7;
          name = name + ((int)(short)iVar7 - (int)*psVar5);
        }
        pAVar11->resolved = '\x01';
        pAVar10 = (AudioEng_tDef *)&pAVar10->ver;
        iVar14 = iVar14 + 0xc;
        iVar13 = iVar13 + 4;
        iVar12 = iVar12 + 4;
      }
    }
    iVar15 = iVar15 + 1;
  } while( true );
}

/* ---- AudioEng_StartServer__Fv  [@0x8007c434] ---- */
void AudioEng_StartServer(void)
{
  iSNDserveradd100hzclient(AudioEng_Update /* @0x8007b824 100Hz server callback */);
  return;
}

/* ---- AudioEng_StopServer__Fv  [@0x8007c458] ---- */
void AudioEng_StopServer(void)
{
  iSNDserverremove100hzclient(AudioEng_Update /* @0x8007b824 100Hz server callback */);
  return;
}

/* ---- AudioEng_Pause__Fv  [@0x8007c47c] ---- */
void AudioEng_Pause(void)
{
  int player;
  AudioEng_t*g;
  AudioEng_tState*s;
  AudioEng_tState *pAVar1;
  AudioEng_t *pAVar2;
  AudioEng_t **ppAVar3;
  int iVar4;
  
  iVar4 = 0;
  ppAVar3 = AudioEng_g;
  while (((iVar4 < 2 && (pAVar2 = *ppAVar3, pAVar2 != (AudioEng_t *)0x0)) &&
         ((pAVar2->plypos != '\x0f' || ((pAVar2->setpos + 1U & 1) == 0))))) {
    ppAVar3 = ppAVar3 + 1;
    pAVar1 = pAVar2->queue + (u_char)pAVar2->setpos;
    pAVar1->vol = 0;
    pAVar1->esp = 0;
    pAVar1->dop = 0x1000;
    pAVar1->gas = '\0';
    pAVar1->exh = '\0';
    pAVar1->sep = 0;
    pAVar1->azi = 0;
    iVar4 = iVar4 + 1;
    pAVar2->setpos = pAVar2->setpos + 1U & 0xf;
  }
  return;
}

/* ---- AudioEng_Resume__Fv  [@0x8007c52c] ---- */
void AudioEng_Resume(void)
{
  return;
}

/* ---- AudioEng_CleanUp__Fv  [@0x8007c534] ---- */
void AudioEng_CleanUp(void)
{
  AudioEng_t*g;
  int j;
  AudioEng_tChanAttr *chan;
  u_int uVar1;
  int c;
  char *pdata;
  AudioEng_t *pAVar2;
  int i;
  int iVar3;
  u_short leftazim;
  AudioEng_t *ptr;
  char *current;
  char *header;
  int tablesize;
  AudioEng_t **ppAVar4;
  int bankloaded;
  SNDPLAYOPTS playopts;
  AudioEng_tDef *loaddef;
  AudioEng_tDef *cruisedef;
  
  ppAVar4 = AudioEng_g;
  while( true ) {
    if (AudioEng_g + 2 <= ppAVar4) {
      return;
    }
    ptr = *ppAVar4;
    iVar3 = 0;
    pAVar2 = ptr;
    if (ptr == (AudioEng_t *)0x0) break;
    do {
      uVar1 = pAVar2->left[0].handle;
      if (uVar1 != 0xffffffff) {
        SNDstop(uVar1);
        uVar1 = pAVar2->right[0].handle;
        if (uVar1 != 0xffffffff) {
          SNDstop(uVar1);
        }
        pAVar2->left[0].handle = -1;
        pAVar2->right[0].handle = -1;
      }
      iVar3 = iVar3 + 1;
      pAVar2 = (AudioEng_t *)pAVar2->vol;
    } while (iVar3 < 0x10);
    purgememadr(ptr->tables);
    purgememadr(ptr);
    *ppAVar4 = (AudioEng_t *)0x0;
    ppAVar4 = ppAVar4 + 1;
  }
  return;
}
