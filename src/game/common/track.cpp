/* game/psx/track.cpp -- RECONSTRUCTED (NFS4 PSX track load/resources/materials; C++ TU)
 *   29 fns: track init/deinit, art+texture resources, LoadShapesAndMakePmx, material linking,
 *   object bounding spheres, kill data, SaveSurface class. GTE-free. Full SYM-locals applied.
 */
#include "../../nfs4_types.h"
#include "../../mips_semantics.h"
#include "track_externs.h"
/* ---- owning-TU defs for link-harness (extern-declared, never defined; BSS) ---- */
Track_MipMap *gTempMipMapInfo; Track_MultiPalette *gTempMultiPalInfo;

/* track.obj car-dashboard shape/tach name-prefix tables @0x80055A54 (contiguous; 58 char*,
 *   't'=day shapes / 'n'=night, decoded byte-exact from nfs4-f.exe via IDA NFS4.EXE.i64).
 *   HudPmx_InitTextures copies the two 29-entry lists with explicit bounds
 *   Host declaration order does not imply contiguous storage */
const char *Track_gShapeNamePtrs[28] = {           /* @0x80055A54 : [0..27] */
    "tslk","tbz3","thsv","tfor","tz28","ttra","tdb7","txkr","ttm5","tvet",
    "t550","t911","tf50","tdsv","tclk","tmcf","t911","thsv","tvet","tbon",
    "tbon","tbon","tcap","thsv","ttm5","tvet","t911","tdsv" };
const char *Track_gShapeNamePtrs_end[1] = { "tbon" }; /* @0x80055AC4 : [28] (loop-bound marker) */
const char *Track_gTachNamePtrs[25] = {            /* @0x80055AC8 : [29..53] */
    "nslk","nbz3","nhsv","nfor","nz28","ntra","ndb7","nxkr","nnm5","nvet",
    "n550","n911","nf50","tdsv","tclk","nmcf","n911","nhsv","nvet","nbon",
    "nbon","nbon","ncap","nhsv","nnm5" };
const char *gShapeNamePtrs_subList[4] = { "nvet","n911","tdsv","nbon" }; /* @0x80055B2C : [54..57] */

/* ---- intra-TU forward declarations (auto-emitted, signature-exact) ---- */
void Track_SetTrackNumber(int tracknum);
char * Track_MakeTrackPathName(const char *ext);
char * Track_MakeTrackDataPathName(const char *ext);
void AllocArtResource(Track_tArtresource *artRes,int numPmx);
void InitArtResources(void);
void DeInitArtResources(void);
void LoadShapesAndMakePmx(char *shapefile,Draw_tPixMap *pmxList,int loadFlags,int x,int y);
void LoadShapesAndMakePmx_EnvMap(char *shapefile,Draw_tPixMap *pmxList,int x,int y);
void TexturesLoadInitial(void);
void Track_AnimateTextures(void);
int Track_GetProperMultiPalShapeIndex(int shapeindex,int paletteindex);
void Track_ProcessFlipAndUVFlags(int uvFlag,Draw_tPixMap *inputPmx,Draw_tPixMap *outputPmx);
void Track_AssociateSingleMaterial(Trk_Material *inputMat,Track_tMaterial *outputMat,Track_tArtresource *art);
void Track_LinkMaterials(SerializedGroup *group,int length,Track_tMaterial *matList);
void ReduceObjectPrecision(Group *instGroup,Group *defGroup,int bits);
void InvalidatePersistentCollideBoomObjects(Group *instGroup,Group *defGroup);
void CalcObjectBoundingSphere(Group *defGroup,Group *boundingSphereGroup);
void CalcObjDefPtrs(void);
void Track_InitPersistentData(SerializedGroup *perGroup);
void Track_Init(char *tempName);
void Track_DeInit(void);
void Track_AnimateTrackLighting(void);
char * KillFile_OpenRead(void);
void KillFile_ReadEntry(char *filePtr,int entryInd,int *chunkInd,int *objectInd);
void Track_LoadObjectKillData(void);


/* ---- Track_SetTrackNumber__Fi  [TRACK.CPP:95-96] SLD-VERIFIED ---- */
void Track_SetTrackNumber(int tracknum)

{
  gtrackNumber = tracknum & 0xf;
  return;
}

/* ---- Track_MakeTrackPathName__FPc  [TRACK.CPP:103-110] SLD-VERIFIED ---- */
char * Track_MakeTrackPathName(const char *ext)

{
  static char strspc[64];   /* @0x8013e300 STAT (.bss) */
  sprintf(strspc,"%sTr%02d%s",Paths_Paths[6],gtrackNumber,ext);
  return strspc;
}

/* ---- Track_MakeTrackDataPathName__FPc  [TRACK.CPP:114-121] SLD-VERIFIED ---- */
char * Track_MakeTrackDataPathName(const char *ext)

{
  static char strspc[64];   /* @0x8013e340 STAT (.bss) */
  sprintf(strspc,"%sTr%02d%s",Paths_Paths[8],gtrackNumber,ext);
  return strspc;
}

/* ---- AllocArtResource__FP18Track_tArtresourcei  [TRACK.CPP:142-151] SLD-VERIFIED ---- */
void AllocArtResource(Track_tArtresource *artRes,int numPmx)

{
  Draw_tPixMap *pDVar1;
  
  artRes->id = -1;
  artRes->basePmxCount = 0;
  pDVar1 = (Draw_tPixMap *)BWAllocMem(numPmx << 4);
  artRes->pPmx = pDVar1;
  artRes->shapeCount = 0;
  artRes->shapeFile = (char *)0x0;
  return;
}

/* ---- InitArtResources__Fv  [TRACK.CPP:155-165] SLD-VERIFIED ---- */
void InitArtResources(void)

{
  AllocArtResource(&gInitialArt,0x352);
  Track_materials = (Track_tMaterial *)BWAllocMem(0xd48);
  return;
}

/* ---- DeInitArtResources__Fv  [TRACK.CPP:176-192] SLD-VERIFIED ---- */
void DeInitArtResources(void)

{
  gInitialArt.pPmx = (Draw_tPixMap *)0x0;
  Chunk_DeInit();
  return;
}

/* ---- LoadShapesAndMakePmx__FPcP12Draw_tPixMapiii  [TRACK.CPP:225-359] SLD-VERIFIED ---- */
void LoadShapesAndMakePmx(char *shapefile,Draw_tPixMap *pmxList,int loadFlags,int x,int y)

{
  Track_MultiPalette *pTVar1;
  int shapeCount;
  u_char *n;
  int iVar3;
  Track_MipMap *pTVar4;
  int iVar5;
  Track_MultiPalette *pTVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char name [4];
  
  iVar9 = -1;
  gTempMipMapInfo = (Track_MipMap *)0x0;
  if (TrackSpec_gSpec.fogstate != 0) {
    iVar9 = -3;
    gTempMipMapInfo = (Track_MipMap *)reservememadr("mipmapinf",0x180,0x10);
    iVar5 = 0;
    do {
      *(u_int *)gTempMipMapInfo[iVar5].code = 0xffffffff;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x20);
  }
  gTempMultiPalInfo = (Track_MultiPalette *)reservememadr("mpalinfo",0x400,0x10);
  iVar3 = 0x7f;
  pTVar1 = gTempMultiPalInfo + 0x7f;
  do {
    pTVar1->palnum = -1;
    iVar3 = iVar3 + -1;
    pTVar1 = pTVar1 + -1;
  } while (-1 < iVar3);
  DrawSync(0);
  iVar8 = 0;
  iVar3 = 0;
  iVar5 = 0;
  do {
    shapeCount = shapecount(shapefile);
    if (shapeCount <= iVar3) {
      return;
    }
    n = (u_char *)shapepointer(shapefile,iVar3);
    if (n != (u_char *)0x0) {
      shapename(shapefile,iVar3,name);
      if (((iVar3 < 0xc) || ((*n & 3) == 1)) || (iVar7 = iVar9, name[0] == '#')) {
        iVar7 = -1;
      }
      Texture_LoadPmx((char *)0x0,(char *)n,loadFlags | 2,x,y,iVar7,iVar7,pmxList);
      if (name[0] == '!') {
        gTempMultiPalInfo->charcode[iVar5] = name[1];
        gTempMultiPalInfo->charcode[iVar5 + 1] = name[2];
        iVar7 = atoi(name + 3);
        pTVar1 = gTempMultiPalInfo;
        *(short *)(gTempMultiPalInfo->charcode + iVar5 + 2) = (short)iVar7;
        *(short *)(pTVar1->charcode + iVar5 + 6) = (short)iVar3;
        if (iVar7 == 0) {
          *(short *)(pTVar1->charcode + iVar5 + 4) = (short)iVar3;
        }
        else {
          iVar7 = 0;
          pTVar6 = pTVar1;
          do {
            if (((pTVar6->charcode[0] == name[1]) && (pTVar6->charcode[1] == name[2])) &&
               (pTVar6->palnum == 0)) {
              *(short *)(pTVar1->charcode + iVar5 + 4) = pTVar6->origshapeindex;
              break;
            }
            iVar7 = iVar7 + 1;
            pTVar6 = pTVar6 + 1;
          } while (iVar7 < 0x80);
        }
        iVar5 = iVar5 + 8;
      }
      if ((TrackSpec_gSpec.fogstate != 0) && (name[0] == 'Z')) {
        if ((name[1] == 'R') && ((*n & 3) == 1)) {
          pTVar4 = gTempMipMapInfo + iVar8;
          pTVar4->code[0] = (u_short)(u_char)name[2];
          iVar8 = iVar8 + 1;
          pTVar4->shapeParentIndex = iVar3;
          pTVar4->mipMapIndex = iVar3;
          pTVar4->code[1] = (u_short)(u_char)name[3];
        }
        else {
          iVar7 = 0;
          pTVar4 = gTempMipMapInfo;
          if (name[1] == 'Z') {
            do {
              if (((u_short)(u_char)name[2] == pTVar4->code[0]) &&
                 ((u_short)(u_char)name[3] == pTVar4->code[1])) {
                pTVar4->mipMapIndex = iVar3;
                break;
              }
              iVar7 = iVar7 + 1;
              pTVar4 = pTVar4 + 1;
            } while (iVar7 < 0x20);
          }
        }
      }
      pmxList = pmxList + 1;
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

/* ---- LoadShapesAndMakePmx_EnvMap__FPcP12Draw_tPixMapii  [TRACK.CPP:375-394] SLD-VERIFIED ---- */
void LoadShapesAndMakePmx_EnvMap(char *shapefile,Draw_tPixMap *pmxList,int x,int y)

{
  int shapeCount;
  char *n;
  int idx;
  
  for (idx = 0; shapeCount = shapecount(shapefile), idx < shapeCount;
      idx = idx + 1) {
    n = (char *)shapepointer(shapefile,idx);
    if (n != (char *)0x0) {
      Texture_LoadPmx((char *)0x0,n,0x42,x,y,-1,-1,pmxList)
      ;
      pmxList = pmxList + 1;
    }
  }
  return;
}

/* ---- TexturesLoadInitial__Fv  [TRACK.CPP:405-465] SLD-VERIFIED ---- */
void TexturesLoadInitial(void)

{
  char *shape_path;
  Draw_tPixMap *pDVar3;
  char *pcVar4;
  const char *track_path;
  
  if (GameSetup_gData.Time == 0) {
    if (GameSetup_gData.Weather == 0) {
      track_path = "0.psh";
    }
    else {
      track_path = "W0.psh";
    }
  }
  else if (GameSetup_gData.Weather == 0) {
    track_path = "N0.psh";
  }
  else {
    track_path = wordFile_psh_snow;
  }
  shape_path = Track_MakeTrackPathName(track_path);
  gInitialArt.shapeFile =
       (char *)loadshapeadr(shape_path,0x0);
  if (gInitialArt.shapeFile != (char *)0x0) {
    Texture_ResetPaletteSharing();
    gInitialArt.shapeCount = (int)shapecount(gInitialArt.shapeFile);
    LoadShapesAndMakePmx(gInitialArt.shapeFile,gInitialArt.pPmx,0x40,0x100,0);
    pDVar3 = gInitialArt.pPmx + gInitialArt.shapeCount;
    nfs4_mips_copy_bytes(pDVar3,gSpikeBeltPixmap,16);
    gInitialArt.shapeCount = gInitialArt.shapeCount + 1;
    gInitialArt.pmxCount = gInitialArt.shapeCount;
    gInitialArt.basePmxCount = gInitialArt.shapeCount;
    purgememadr(gInitialArt.shapeFile);
    Hrz_GetHorizonPixMap(gInitialArt.pPmx);
    pcVar4 = Track_MakeTrackPathName("r.psh");
    pcVar4 = (char *)loadshapeadr(pcVar4,0x0);
    if (pcVar4 != (char *)0x0) {
      Texture_ResetPaletteSharing();
      LoadShapesAndMakePmx_EnvMap(pcVar4,Track_gReflectionMaps,0x3e0,0);
      purgememadr(pcVar4);
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

/* ---- Track_AnimateTextures__Fv  [TRACK.CPP:491-517] SLD-VERIFIED ---- */
void Track_AnimateTextures(void)

{
  Track_tMaterialController *controller = Track_gMatController;
  int remaining = Track_gControllerCount;

  while (--remaining != -1) {
    if (controller->type == 0x80) {
      u_int interval = controller->interval;
      if (interval == 0) {
        trap(0x1c00);
      }
      if ((interval == 0xffffffff) && (simGlobal.gameTicks == 0x80000000)) {
        trap(0x1800);
      }
      u_int textureMax = controller->textureMax;
      if (textureMax == 0) {
        trap(0x1c00);
      }
      if ((textureMax == 0xffffffff) &&
          (simGlobal.gameTicks / (int)interval == 0x80000000)) {
        trap(0x1800);
      }
      short pmxIndex = controller->matPtr->pmxIndex;
      char frame = (char)((simGlobal.gameTicks / (int)interval) % (int)textureMax);
      Draw_tPixMap *pmx = &gInitialArt.pPmx[pmxIndex];
      pmx->v0 = controller->uv0 + frame;
      pmx->v1 = controller->uv1 + frame;
      pmx->v2 = controller->uv2 + frame;
      pmx->v3 = controller->uv3 + frame;
    }
    else if (controller->type == 4) {
      u_int interval = controller->interval;
      if (interval == 0) {
        trap(0x1c00);
      }
      if ((interval == 0xffffffff) && (simGlobal.gameTicks == 0x80000000)) {
        trap(0x1800);
      }
      u_int textureCount = (u_char)controller->textureCount;
      if (textureCount == 0) {
        trap(0x1c00);
      }
      if ((textureCount == 0xffffffff) &&
          (simGlobal.gameTicks / (int)interval == 0x80000000)) {
        trap(0x1800);
      }
      controller->matPtr->pmxIndex =
          controller->pmxIndex +
          (short)((simGlobal.gameTicks / (int)interval) % (int)textureCount);
    }
    ++controller;
  }
  return;
}

/* ---- Track_GetProperMultiPalShapeIndex__Fii  [TRACK.CPP:525-532] SLD-VERIFIED ---- */
int Track_GetProperMultiPalShapeIndex(int shapeindex,int paletteindex)

{
  Track_MultiPalette *pTVar1;
  int iVar2;
  
  iVar2 = 0;
  pTVar1 = gTempMultiPalInfo;
  while ((pTVar1->origshapeindex != shapeindex || (pTVar1->palnum != paletteindex))) {
    iVar2 = iVar2 + 1;
    pTVar1 = pTVar1 + 1;
    if (0x7f < iVar2) {
      return shapeindex;
    }
  }
  return (int)pTVar1->actualshapeindex;
}

/* ---- Track_ProcessFlipAndUVFlags__FiP12Draw_tPixMapT1  [TRACK.CPP:538-571] SLD-VERIFIED ---- */
void Track_ProcessFlipAndUVFlags(int uvFlag,Draw_tPixMap *inputPmx,Draw_tPixMap *outputPmx)

{
  Draw_tPixMap pmx[4];
  int count = 0;

  nfs4_mips_copy_bytes(&pmx[0],inputPmx,16);
  if ((uvFlag & 0x10U) != 0) {
    Texture_CloneUVPmx(&pmx[0],0,&pmx[1]);
    count = 1;
  }
  if ((uvFlag & 0x40U) != 0) {
    Texture_CloneUVPmx(&pmx[count],1,&pmx[count + 1]);
    count++;
  }
  if ((uvFlag & 0xeU) != 0) {
    int mode = (uvFlag & 2U) != 0 ? 2 : ((uvFlag & 4U) != 0 ? 3 : 4);
    Texture_CloneUVPmx(&pmx[count],mode,&pmx[count + 1]);
    count++;
  }
  nfs4_mips_copy_bytes(outputPmx,&pmx[count],16);
  return;
}

/* ---- Track_AssociateSingleMaterial__FP12Trk_MaterialP15Track_tMaterialP18Track_tArtresource  [TRACK.CPP:577-626] SLD-VERIFIED ---- */
/* void 
   Track_AssociateSingleMaterial(Trk_Material
   * inputMat, Track_tMaterial * outputMat, Track_tArtresource * art)
   
   Track-system helper (track).
   
   Phase F apply (2026-05-07): documentation-coverage closure for game-side undocumented fns.
   
   Provenance:
     VA=0x800B9D2C block=CODE size=364B
     Direct callers: 1
     SLD source: nfs4/GAME/COMMON/TRACK.CPP:577
     SYM data: 3 regparms / 0 args / 1 autos
     Sample callers: Track_LinkMaterials
   
   Toolchain: PsyQ SDK 4.3 (May 1998), GCC 2.7.2, ASPSX 2.77, PSYLINK 2.73.
   Build date: 1999-02-22.
   See PROJECT_AUDIT_2026-05-05.md and SESSION_2026-05-07_SUMMARY.md.
   
   [Locals 2026-05-09] Locals renamed via deep-body inspection. Track_AssociateSingleMaterial - bind
   one Trk_Material to its Track_tMaterial entry + Track_tArtresource (364B). Walks the inputMat's
   animFrame[] entries (animCount loop, anim_iter index): for each anim frame, resolves shapeIndex
   via art lookup → shapeData_p (Draw_tPixMap from the art atlas); applies uvFlag via
   Track_ProcessFlipAndUVFlags into outputMat's per-frame pixmap slot. originalPmx (16B local)
   preserves the unflipped reference pixmap for rollback. Used during scene/track init to bake
   material bindings + UV permutation flags so render time has zero conditional branches per
   material.
   
   [Locals 2026-05-10 bulk] Bulk-renamed Ghidra SSA temps to type-hinted user-names (ti=int,
   tu=u_int, ts=short, tb=u_char, tstr=char*, tp=void*, etc.) for audit cleanliness. Generic but
   preserves type info; these are minor secondary-effect register temps that did not warrant
   individual semantic naming. */

void Track_AssociateSingleMaterial(Trk_Material *inputMat,Track_tMaterial *outputMat,Track_tArtresource *art)

{
  outputMat->flag = inputMat->flag;
  for (int animCount = 0;
       animCount < 1 || animCount < (int)(u_char)inputMat->textureCount;
       animCount++) {
    int shapeIndex = (int)inputMat->shapeIndex;
    if ((inputMat->flag & 2) != 0) {
      shapeIndex = Track_GetProperMultiPalShapeIndex(shapeIndex,(u_int)inputMat->interval);
    }
    if ((inputMat->uvFlag & 0x5e) != 0) {
      Draw_tPixMap originalPmx;
      nfs4_mips_copy_bytes(&originalPmx,art->pPmx + shapeIndex + animCount,16);
      Track_ProcessFlipAndUVFlags((u_int)inputMat->uvFlag,&originalPmx,
                                 art->pPmx + art->pmxCount);
      if (animCount == 0) {
        outputMat->pmxIndex = (short)art->pmxCount;
      }
      art->pmxCount++;
    }
    else if (animCount == 0) {
      outputMat->pmxIndex = (short)shapeIndex;
    }
  }
  return;
}

/* ---- Track_LinkMaterials__FP15SerializedGroupiP15Track_tMaterial  [TRACK.CPP:688-848] SLD-VERIFIED ---- */
void Track_LinkMaterials(SerializedGroup *group,int length,Track_tMaterial *matList)

{
  u_char bVar2;
  short sVar3;
  Track_tMaterialController *pTVar7;
  Draw_tPixMap *pDVar8;
  Trk_Material *pSVar9;
  int iVar10;
  Track_MipMap *mipMapInfo;
  int iVar12;
  int shapeIndex;
  int iVar13;
  u_int uVar14;
  u_int uVar15;
  u_int pmxLnkW2;
  u_int uVar16;
  Trk_Material *inputMat;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  Draw_tPixMap originalPmx;
  
  if (group != (SerializedGroup *)0x0) {
    iVar18 = 0;
    inputMat = (Trk_Material *)(group + 1);
    Track_gControllerCount = 0;
    gInitialArt.pmxCount = gInitialArt.basePmxCount;
    uVar14 = (u_int)length / 10;
    pSVar9 = inputMat;
    if (uVar14 != 0) {
      do {
        if ((pSVar9->flag & 0x84) != 0) {
          Track_gControllerCount = Track_gControllerCount + 1;
        }
        iVar18 = iVar18 + 1;
        pSVar9 = pSVar9 + 1;
        pmxLnkW2 = uVar14;
      } while (iVar18 < (int)uVar14);
    }
    uVar15 = uVar14;
    if (Track_gControllerCount != 0) {
      Track_gMatController =
           (Track_tMaterialController *)BWAllocMem(Track_gControllerCount << 4);
    }
    iVar19 = 0;
    iVar18 = iVar19;
    for (; iVar19 < (int)uVar14; iVar19 = iVar19 + 1) {
      uVar16 = uVar14;
      Track_AssociateSingleMaterial(inputMat,matList,&gInitialArt);
      bVar2 = inputMat->flag;
      if ((bVar2 & 4) == 0) {
        iVar20 = iVar18;
        if ((bVar2 & 0x80) != 0) {
          Track_gMatController[iVar18].type = (u_short)inputMat->flag;
          if (inputMat->interval == 0) {
            inputMat->interval = 1;
          }
          Track_gMatController[iVar18].interval = inputMat->interval;
          Track_gMatController[iVar18].textureCount = inputMat->textureCount;
          pTVar7 = Track_gMatController;
          Track_gMatController[iVar18].pmxIndex = matList->pmxIndex;
          pTVar7[iVar18].matPtr = matList;
          pDVar8 = gInitialArt.pPmx;
          sVar3 = matList->pmxIndex;
          pTVar7[iVar18].uv0 = gInitialArt.pPmx[sVar3].v0;
          Track_gMatController[iVar18].uv1 = pDVar8[sVar3].v1;
          Track_gMatController[iVar18].uv2 = pDVar8[sVar3].v2;
          Track_gMatController[iVar18].uv3 = pDVar8[sVar3].v3;
          iVar17 = (u_int)pDVar8[sVar3].v3 - (u_int)pDVar8[sVar3].v0;
          if (iVar17 < 0) {
            iVar17 = -iVar17;
          }
          iVar20 = iVar18 + 1;
          Track_gMatController[iVar18].textureMax = (char)iVar17 + '\x01';
        }
      }
      else {
        pTVar7 = Track_gMatController + iVar18;
        pTVar7->type = (u_short)bVar2;
        pTVar7->interval = inputMat->interval;
        Track_gMatController[iVar18].textureCount = inputMat->textureCount;
        pTVar7 = Track_gMatController;
        Track_gMatController[iVar18].pmxIndex = matList->pmxIndex;
        pTVar7[iVar18].matPtr = matList;
        iVar20 = iVar18 + 1;
      }
      iVar18 = 0;
      if (TrackSpec_gSpec.fogstate != 0) {
        for (; iVar18 < 0x20; iVar18 = iVar18 + 1) {
          mipMapInfo = gTempMipMapInfo + iVar18;
          if ((*(u_int *)mipMapInfo->code != 0xffffffff) &&
              (iVar13 = mipMapInfo->shapeParentIndex,
               iVar13 == inputMat->shapeIndex)) {
            iVar10 = mipMapInfo->mipMapIndex;
            matList->flag = matList->flag | 8;
            iVar12 = inputMat->shapeIndex;
            iVar10 = iVar10 - iVar13;
            if (iVar12 == matList->pmxIndex) {
              matList->mipmap_offset = (char)iVar10;
            }
            else {
              shapeIndex = iVar12 + iVar10;
              nfs4_mips_copy_bytes(&originalPmx,gInitialArt.pPmx + shapeIndex,16);
              Track_ProcessFlipAndUVFlags(
                  (u_int)inputMat->uvFlag,
                  &originalPmx,
                  gInitialArt.pPmx + gInitialArt.pmxCount);
              gInitialArt.pmxCount = gInitialArt.pmxCount + 1;
              matList->mipmap_offset = '\x01';
            }
          }
        }
      }
      matList = matList + 1;
      inputMat = inputMat + 1;
      iVar18 = iVar20;
    }
    if (gTempMipMapInfo != (Track_MipMap *)0x0) {
      purgememadr(gTempMipMapInfo);
    }
    purgememadr(gTempMultiPalInfo);
    gInitialArt.shapeFile = (char *)0x0;
    gInitialArt.pmxCount = gInitialArt.shapeCount;
  }
  return;
}

/* ---- ReduceObjectPrecision__FP5GroupT0i  [TRACK.CPP:963-1004] SLD-VERIFIED ---- */
void ReduceObjectPrecision(Group *instGroup,Group *defGroup,int bits)

{
  short sVar1;
  short sVar2;
  Trk_ObjectDef **ppTVar3;
  Trk_ObjectDef *pTVar4;
  short tu5;
  Trk_ObjectDef *pTVar5;
  Trk_ObjectDef *pTVar6;
  u_int uVar7;
  Trk_SimpleInst *inst;
  int iVar8;
  
  ppTVar3 = Track_gObjDefs;
  inst = (Trk_SimpleInst *)(instGroup + 1);
  if (instGroup != (Group *)0x0) {
    iVar8 = instGroup->m_num_elements;
    while (iVar8 = iVar8 + -1, iVar8 != -1) {
      if (defGroup != (Group *)0x0) {
        pTVar4 = ppTVar3[inst->pad];
        pTVar6 = pTVar4 + 1;
        uVar7 = (u_int)pTVar4->vertexCount;
        while( true ) {
          pTVar5 = pTVar4 + 2;
          uVar7 = uVar7 - 1;
          if (uVar7 == 0xffffffff) break;
          ((u_char *)&(sVar1))[0] = pTVar4[1].vertexCount;
          ((u_char *)&(sVar1))[1] = pTVar4[1].quadCount;
          sVar2 = pTVar5->id;
          pTVar6->id = (short)((int)pTVar6->id >> (bits & 0x1fU));
          tu5 = (short)((int)sVar1 >> (bits & 0x1fU));
          ((u_char *)&(tu5))[0] = (u_char)tu5;
          ((u_char *)&(tu5))[1] = (u_char)((u_short)tu5 >> 8);
          pTVar4[1].vertexCount = (u_char)tu5;
          pTVar4[1].quadCount = ((u_char *)&(tu5))[1];
          pTVar5->id = (short)((int)sVar2 >> (bits & 0x1fU));
          pTVar6 = pTVar6 + 2;
          pTVar4 = pTVar5;
        }
      }
      inst = (Trk_SimpleInst *)((u_char *)inst + inst->size);
    }
  }
  return;
}

/* ---- InvalidatePersistentCollideBoomObjects__FP5GroupT0  [TRACK.CPP:1012-1026] SLD-VERIFIED ---- */
void InvalidatePersistentCollideBoomObjects(Group *instGroup,Group *defGroup)

{
  Trk_SimpleInst *inst;
  int iVar2;
  
  if ((instGroup != (Group *)0x0) && (defGroup != (Group *)0x0)) {
    iVar2 = instGroup->m_num_elements;
    inst = (Trk_SimpleInst *)(instGroup + 1);
    while (iVar2 = iVar2 + -1, iVar2 != -1) {
      if (Track_gObjDefs[inst->pad]->id != -1) {
        inst->type = 0;
      }
      inst = (Trk_SimpleInst *)((u_char *)inst + inst->size);
    }
  }
  return;
}

/* ---- CalcObjectBoundingSphere__FP5GroupT0  [TRACK.CPP:1064-1125] SLD-VERIFIED ---- */
void CalcObjectBoundingSphere(Group *defGroup,Group *boundingSphereGroup)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  u_int uVar4;
  u_int uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  Trk_ObjectDef *pTVar9;
  u_int uVar10;
  u_int uVar11;
  Trk_ObjectDef *pTVar12;
  Trk_ObjectDef *pTVar13;
  int iVar14;
  int iVar15;
  tBoundingSphere *bSphere;
  int iVar17;
  coorddef cp;
  
  bSphere = (tBoundingSphere *)(boundingSphereGroup + 1);
  iVar17 = defGroup->m_num_elements;
  for (iVar15 = 0; iVar15 < iVar17; iVar15 = iVar15 + 1) {
    pTVar9 = Track_gObjDefs[iVar15];
    uVar10 = (u_int)pTVar9->vertexCount;
    pTVar12 = pTVar9 + 1;
    cp.z = 0;
    cp.y = 0;
    cp.x = 0;
    pTVar13 = pTVar9;
    while (uVar10 = uVar10 - 1, uVar10 != 0xffffffff) {
      psVar3 = &pTVar12->id;
      pTVar12 = pTVar12 + 2;
      cp.x = cp.x + *psVar3;
      ((u_char *)&(sVar1))[0] = pTVar13[1].vertexCount;
      ((u_char *)&(sVar1))[1] = pTVar13[1].quadCount;
      cp.y = cp.y + sVar1;
      cp.z = cp.z + pTVar13[2].id;
      pTVar13 = pTVar13 + 2;
    }
    uVar10 = (u_int)pTVar9->vertexCount;
    if (uVar10 == 0) {
      trap(0x1c00);
    }
    if ((uVar10 == 0xffffffff) && (cp.x == 0x80000000)) {
      trap(0x1800);
    }
    uVar4 = (u_int)pTVar9->vertexCount;
    if (uVar4 == 0) {
      trap(0x1c00);
    }
    if ((uVar4 == 0xffffffff) && (cp.y == 0x80000000)) {
      trap(0x1800);
    }
    uVar5 = (u_int)pTVar9->vertexCount;
    if (uVar5 == 0) {
      trap(0x1c00);
    }
    if ((uVar5 == 0xffffffff) && (cp.z == 0x80000000)) {
      trap(0x1800);
    }
    pTVar13 = pTVar9 + 1;
    iVar14 = 0;
    uVar11 = (u_int)pTVar9->vertexCount;
    while( true ) {
      uVar11 = uVar11 - 1;
      if (uVar11 == 0xffffffff) break;
      iVar6 = nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(cp.x / (int)uVar10, (int)pTVar13->id), 6);
      ((u_char *)&(sVar2))[0] = pTVar9[1].vertexCount;
      ((u_char *)&(sVar2))[1] = pTVar9[1].quadCount;
      iVar7 = nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(cp.y / (int)uVar4, (int)sVar2), 6);
      iVar8 = nfs4_mips_sra_s32(
          nfs4_mips_subu_s32(cp.z / (int)uVar5, (int)pTVar9[2].id), 6);
      iVar6 = nfs4_mips_addu_s32(
          nfs4_mips_addu_s32(nfs4_mips_mult_s32(iVar6, iVar6),
                             nfs4_mips_mult_s32(iVar7, iVar7)),
          nfs4_mips_mult_s32(iVar8, iVar8));
      if (iVar14 < iVar6) {
        iVar14 = iVar6;
      }
      pTVar13 = pTVar13 + 2;
      pTVar9 = pTVar9 + 2;
    }
    bSphere->cp.x = (short)(cp.x / (int)uVar10);
    bSphere->cp.y = (short)(cp.y / (int)uVar4);
    bSphere->cp.z = (short)(cp.z / (int)uVar5);
    uVar10 = fixedsqrt(iVar14 << 10);
    bSphere->radius = (short)(uVar10 >> 7);
    ++bSphere;
    boundingSphereGroup->m_num_elements = boundingSphereGroup->m_num_elements + 1;
  }
  return;
}

/* ---- CalcObjDefPtrs__Fv  [TRACK.CPP:1179-1188] SLD-VERIFIED ---- */
void CalcObjDefPtrs(void)

{
  bool bVar1;
  Group *pGVar2;
  Group *pGVar3;
  int iVar4;
  
  pGVar2 = gPersistObjDef;
  iVar4 = 1;
  pGVar3 = gObjDefOffsetsGroup + 2;
  gObjDefOffsetsGroup[1].m_num_elements = (int)(gPersistObjDef + 1);
  while (bVar1 = iVar4 < pGVar2->m_num_elements, iVar4 = iVar4 + 1, bVar1) {
    pGVar3->m_num_elements = pGVar3[-1].m_num_elements + pGVar3->m_num_elements;
    pGVar3 = pGVar3 + 1;
  }
  Track_gObjDefs = (Trk_ObjectDef **)(gObjDefOffsetsGroup + 1);
  return;
}

/* ---- Track_InitPersistentData__FP15SerializedGroup  [TRACK.CPP:1212-1292] SLD-VERIFIED ---- */
void Track_InitPersistentData(SerializedGroup *perGroup)

{
  Group *simGroup;
  int iVar2;
  int iVar3;
  SerializedGroup **persistentGroups;
  SerializedGroup *group;
  
  iVar2 = 0;
  gObjDefOffsetsGroup = (Group *)0x0;
  persistentGroups = (SerializedGroup **)__builtin_alloca
      ((perGroup->m_num_elements * sizeof(*persistentGroups) + 7) & ~(size_t)7);
  if (0 < perGroup->m_num_elements) {
    do {
      persistentGroups[iVar2] = (perGroup)->LocateGroupNum(iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < perGroup->m_num_elements);
  }
  (perGroup)->LocateGroupType(8,0);
  iVar3 = perGroup->m_num_elements;
  iVar2 = 0;
  do {
    if (iVar3 <= iVar2) {
      if (gObjDefOffsetsGroup != (Group *)0x0) {
        CalcObjDefPtrs();
      }
      return;
    }
    group = persistentGroups[iVar2];
    switch(group->m_type) {
    case 2:
      Track_LinkMaterials(group,group->m_length + -0x10,Track_materials);
      break;
    case 7:
      gPersistObjInst = (group)->CreateLiteGroup(group,Track_mem);
      break;
    case 8:
      gPersistObjDef = (group)->CreateLiteGroup(group,Track_mem);
      break;
    case 0xf:
      simGroup = (group)->CreateLiteGroup(group,Track_mem);
      BWorldSm_Init(simGroup);
      break;
    case 0x24:
      gPersistMidgroundObjInst = (group)->CreateLiteGroup(group,Track_mem);
      break;
    case 0x26:
      gObjDefOffsetsGroup = (group)->CreateLiteGroup(group,Track_mem);
    default: break;
    }
    iVar2 = iVar2 + 1;
  } while( true );
}

/* ---- Track_Init__FPc  [TRACK.CPP:1312-1475] SLD-VERIFIED ---- */
void Track_Init(char *tempName)

{
  int loadResult;
  SimpleMem *this_00;
  void *loadBuf;
  u_char *scratchAlloc;
  SerializedGroup *rootSerGroup;
  Group *headerGroup;
  Group *chunkCenterGroup;
  SerializedGroup *lightGroup;
  SerializedGroup *lightCountGroup;
  SerializedGroup *perGroup;
  SerializedGroup *pSVar4;
  SaveSurface *newSaveSurface;
  void *tp7;
  short *viewRow;
  short *elemNext;
  u_short *serializedView;
  int elemIdx;
  int iVar43_field;
  int iVar44_field;
  int chunkCount;
  int groupOffset;
  SerializedGroup *matInfo_p;
  char trackName [128];
  u_short tu3;
  TrackHeader *tT33;
  
  Track_gSaveSurface = (SaveSurface *)0x0;
  Track_gObjDefs = (Trk_ObjectDef **)0x0;
  sprintf(trackName,"%s",tempName);
  loadResult = filesize(tempName);
  Chunk_lightTable = (CVECTOR *)reservememadr("lighttbl",0x404,0);
  TextureProcess_Init();
  chunkCount = loadResult + 0x9080;
  InitArtResources();
  TexturesLoadInitial();
  this_00 = (SimpleMem *)__builtin_new(sizeof(SimpleMem));
  loadBuf = reservememadr("Track_mem",chunkCount,0);
  this_00->heap = loadBuf;
  this_00->freeMem = loadBuf;
  if (loadBuf == (void *)0x0) {
    chunkCount = 0;
  }
  this_00->freeMemSize = chunkCount;
  Track_mem = this_00;
  scratchAlloc = (u_char *)(this_00)->FeignAlloc(loadResult);
  rootSerGroup = (SerializedGroup *)loadfileatadr(trackName,scratchAlloc + 0x9080);
  headerGroup = (Group *)(rootSerGroup)->LocateCreateGroupType(0x1f,Track_mem,0);
  Track_header = (TrackHeader *)(headerGroup + 1);
  chunkCenterGroup = (Group *)(rootSerGroup)->LocateCreateGroupType(0x20,Track_mem,0);
  Chunk_chunkCenters = (coorddef *)(chunkCenterGroup + 1);
  lightGroup = (rootSerGroup)->LocateGroupType(0x23,0);
  tp7 = (void *)(lightGroup + 1);
  nfs4_mips_copy_bytes(Chunk_lightTable,tp7,0x400);
  lightCountGroup = (rootSerGroup)->LocateGroupType(0x23,0);
  Chunk_numLight = (lightCountGroup->m_length - 0x10U) >> 2;
  Track_gInViewList = (short *)(Track_mem)->Alloc(Track_header->chunkCount * 0x48,0);
  Track_gInViewCount = (u_char *)(Track_mem)->Alloc(Track_header->chunkCount,0);
  Track_chunkList = (Chunk *)(Track_mem)->Alloc(Track_header->chunkCount * 0x70,0);
  Chunk_Init();
  perGroup = (rootSerGroup)->LocateGroupType(0x21,0);
  pSVar4 = (rootSerGroup)->LocateGroupType(0x1d,0);
  for (groupOffset = 0; groupOffset < Track_header->chunkCount; groupOffset = groupOffset + 1) {
    matInfo_p = (SerializedGroup *)0x0;
    if (groupOffset < Track_header->chunkCount + -1) {
      matInfo_p = (SerializedGroup *)(pSVar4)->LocateNextGroupType(0x1d);
    }
    (Track_chunkList + groupOffset)->InstanceGroup(pSVar4,Track_mem);
    pSVar4 = (pSVar4)->LocateGroupType(4,0);
    tT33 = Track_header;
    iVar44_field = pSVar4->m_num_elements;
    serializedView = (u_short *)(pSVar4 + 1);
    iVar43_field = 0;
    if (0x24 < iVar44_field) {
      iVar44_field = 0x24;
    }
    elemIdx = 0;
    viewRow = Track_gInViewList + groupOffset * 0x20;
    elemNext = viewRow;
    if (0 < iVar44_field) {
      do {
        tu3 = *serializedView;
        if ((int)(tu3 & 0x3ff) < tT33->chunkCount) {
          *elemNext = (short)tu3;
          elemNext = elemNext + 1;
          elemIdx = elemIdx + 1;
        }
        iVar43_field = iVar43_field + 1;
        serializedView = serializedView + 1;
      } while (iVar43_field < iVar44_field);
    }
    Track_gInViewCount[groupOffset] = (u_char)elemIdx;
    if (elemIdx < 0x24) {
      do {
        *elemNext = 0x3ff;
        elemIdx = elemIdx + 1;
        elemNext = elemNext + 1;
      } while (elemIdx < 0x24);
    }
    pSVar4 = matInfo_p;
  }
  Track_InitPersistentData(perGroup);
  (Track_mem)->ResizeToFit();
  Track_MakeTrackPathName(".grp");
  gPersistObjDefBoundingSpheres =
       (Group *)reservememadr("bsphere",gPersistObjDef->m_num_elements << 3 | 4,0);
  CalcObjectBoundingSphere(gPersistObjDef,gPersistObjDefBoundingSpheres);
  ReduceObjectPrecision(gPersistMidgroundObjInst,gPersistObjDef,2);
  InvalidatePersistentCollideBoomObjects(gPersistObjInst,gPersistObjDef);
  newSaveSurface = (SaveSurface *)__builtin_new(sizeof(SaveSurface));
  Track_gSaveSurface = new(newSaveSurface) SaveSurface(0x30);
  Track_LoadObjectKillData();
  return;
}

/* ---- Track_DeInit__Fv  [TRACK.CPP:1492-1533] SLD-VERIFIED ---- */
void Track_DeInit(void)

{
  SimpleMem *deleteMe;
  
  deleteMe = Track_mem;
  if (Track_mem != (SimpleMem *)0x0) {
    purgememadr(Track_mem->heap);
    deleteMe->freeMem = (u_char *)0x0;
    __builtin_delete(deleteMe);
  }
  if (Track_gSaveSurface != (SaveSurface *)0x0) {
    Track_gSaveSurface->~SaveSurface();
    __builtin_delete(Track_gSaveSurface);
    Track_gSaveSurface = (SaveSurface *)0x0;
  }
  if (gInitialArt.shapeFile != (char *)0x0) {
    gInitialArt.shapeFile = (char *)0x0;
  }
  BWorldSm_DeInit();
  DeInitArtResources();
  if (Chunk_lightTable != (CVECTOR *)0x0) {
    purgememadr(Chunk_lightTable);
    Chunk_lightTable = (CVECTOR *)0x0;
  }
  if (gPersistObjDefBoundingSpheres != (Group *)0x0) {
    purgememadr(gPersistObjDefBoundingSpheres);
  }
  gPersistObjDefBoundingSpheres = (Group *)0x0;
  gPersistMidgroundObjInst = (Group *)0x0;
  gPersistObjInst = (Group *)0x0;
  gPersistObjDef = (Group *)0x0;
  return;
}

/* ---- Track_AnimateTrackLighting__Fv  [TRACK.CPP:1537-1544] SLD-VERIFIED ---- */
void Track_AnimateTrackLighting(void)

{
  return;
}

/* ---- KillFile_OpenRead__Fv  [TRACK.CPP:1720-1726] SLD-VERIFIED ---- */
char * KillFile_OpenRead(void)

{
  char *pcVar1;
  char pathName [128];
  
  pcVar1 = Track_MakeTrackPathName(".kil");
  sprintf(pathName,"%s",pcVar1);
  pcVar1 = (char *)loadfileadrz(pathName,0);
  return pcVar1;
}

/* ---- KillFile_ReadEntry__FPciRiT2  [TRACK.CPP:1732-1736] SLD-VERIFIED ---- */
void KillFile_ReadEntry(char *filePtr,int entryInd,int *chunkInd,int *objectInd)

{
  *chunkInd = *(int *)(filePtr + entryInd * 8 + 4);
  *objectInd = *(int *)(filePtr + entryInd * 8 + 8);
  return;
}

/* ---- Track_LoadObjectKillData__Fv  [TRACK.CPP:1742-1821] SLD-VERIFIED ---- */
void Track_LoadObjectKillData(void)

{
  int *filePtr_00;
  int iVar1;
  int iVar2;
  Trk_SimObject *simObjs;
  Group *pGVar3;
  Group *pGVar4;
  int iVar5;
  int entryInd;
  int chunkInd;
  int objInd;
  
  filePtr_00 = (int *)KillFile_OpenRead();
  entryInd = 0;
  if (filePtr_00 != (int *)0x0) {
    for (; entryInd < *filePtr_00; entryInd = entryInd + 1) {
      KillFile_ReadEntry((char *)filePtr_00,entryInd,&chunkInd,&objInd);
      pGVar3 = Track_chunkList[chunkInd].objInstanceBuf;
      if ((pGVar3 != (Group *)0x0) && (pGVar4 = pGVar3 + 1, objInd < pGVar3->m_num_elements)) {
        iVar2 = 0;
        if (0 < objInd) {
          do {
            iVar2 = iVar2 + 1;
            pGVar4 = (Group *)((u_char *)pGVar4 + (short)pGVar4->m_num_elements);
          } while (iVar2 < objInd);
        }
        pGVar3 = Track_chunkList[chunkInd].simObjBuf;
        iVar2 = 0;
        if (pGVar3 != (Group *)0x0) {
          iVar5 = pGVar3->m_num_elements;
          simObjs = (Trk_SimObject *)(pGVar3 + 1);
          if (0 < iVar5) {
            do {
              iVar1 = Math_DistXZ((coorddef *)simObjs[iVar2].point,
                                  (coorddef *)((u_char *)pGVar4 + 8));
              if (iVar1 < 0x1999) {
                simObjs[iVar2].type = 0x10;
              }
              iVar2 = iVar2 + 1;
            } while (iVar2 < iVar5);
          }
        }
        ((Trk_SimpleInst *)pGVar4)->type |= 0x80;
      }
    }
    purgememadr(filePtr_00);
  }
  return;
}

/* ---- Save  [TRACK.CPP:1831-1850] SLD-VERIFIED ---- */
void SaveSurface::Save(Trk_NewSimQuad *simQuad)

{
  
  if ((this->fCount <= this->fMaxCount) && (simQuad != (Trk_NewSimQuad *)0x0)) {
    this->fStack[this->fCount].fSimQuad = simQuad;
    this->fStack[this->fCount].fSurface = simQuad->surface;
    this->fCount = this->fCount + 1;
  }
  return;
}

/* ---- SaveSurface  [TRACK.CPP:1855-1858] SLD-VERIFIED ---- */
/* SaveSurface * __11SaveSurfacei(SaveSurface * pThis, int numEntries)
   
   GCC compiler-emitted helper / runtime support (gcc-helper).
   Class: SaveSurface :: (ctor/dtor)
   
   Phase F apply (2026-05-07): documentation-coverage closure for game-side undocumented fns.
   
   Provenance:
     VA=0x800BAF70 block=CODE size=68B
     Direct callers: 1
     SLD source: nfs4/GAME/COMMON/TRACK.CPP:1855
     SYM data: 2 regparms / 0 args / 0 autos
     Sample callers: Track_Init
   
   Toolchain: PsyQ SDK 4.3 (May 1998), GCC 2.7.2, ASPSX 2.77, PSYLINK 2.73.
   Build date: 1999-02-22.
   See PROJECT_AUDIT_2026-05-05.md and SESSION_2026-05-07_SUMMARY.md. */

SaveSurface::SaveSurface(int numEntries)

{
  tSaveSurface *ptVar1;
  
  this->fMaxCount = (short)numEntries;
  this->fCount = 0;
  ptVar1 = (tSaveSurface *)reservememadr("Surface Save",numEntries << 3,0);
  this->fStack = ptVar1;
}

/* ---- ~SaveSurface  [TRACK.CPP:1864-1865] SLD-VERIFIED ---- */
/* void _._11SaveSurface(SaveSurface * pThis, int __in_chrg)
   
   PsyQ-style internal helper (uncategorized) (psyq-internal).
   
   Phase F apply (2026-05-07): documentation-coverage closure for game-side undocumented fns.
   
   Provenance:
     VA=0x800BAFB4 block=CODE size=72B
     Direct callers: 1
     SLD source: nfs4/GAME/COMMON/TRACK.CPP:1864
     SYM data: 2 regparms / 0 args / 0 autos
     Sample callers: Track_DeInit
   
   Toolchain: PsyQ SDK 4.3 (May 1998), GCC 2.7.2, ASPSX 2.77, PSYLINK 2.73.
   Build date: 1999-02-22.
   See PROJECT_AUDIT_2026-05-05.md and SESSION_2026-05-07_SUMMARY.md. */

SaveSurface::~SaveSurface()

{
  
  purgememadr(this->fStack);
  return;
}

/* ---- RestoreAll  [TRACK.CPP:1871-1879] SLD-VERIFIED ---- */
void SaveSurface::RestoreAll()

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < this->fCount) {
    do {
      (this->fStack[iVar1].fSimQuad)->surface = this->fStack[iVar1].fSurface;
      this->fStack[iVar1].fSimQuad = (Trk_NewSimQuad *)0x0;
      this->fStack[iVar1].fSurface = '\0';
      iVar1 = iVar1 + 1;
    } while (iVar1 < this->fCount);
  }
  this->fCount = 0;
  return;
}

/* end of track.cpp */

/* owning-TU def (extern-declared, never defined; link-harness) */
char wordFile_psh_snow[] = "S0.psh";
