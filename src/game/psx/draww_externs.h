#include "../../lib/libfns.h"
/* draww_externs.h -- extern decls for game/psx/draww.cpp (NFS4 PSX world-geometry draw). */
#ifndef DRAWW_EXTERNS_H
    #define DRAWW_EXTERNS_H

/* ---- GTE intrinsics (no-op symbolic; faithful cop2 source) ---- */
extern void gte_rtps(void);
extern void gte_rtpt(void);
extern void gte_lwc2(int reg, int data);
extern void gte_swc2(int reg, void *ptr);
    #ifdef AP_WIN
extern void nfs4_gte_set_rot_matrix(const void *);
extern void nfs4_gte_set_trans_matrix(const void *);
extern void nfs4_gte_nclip(void);
extern void nfs4_gte_avsz4(void);
extern void nfs4_gte_ldsxy3(int, int, int);
extern void nfs4_gte_stflg(void *);
extern void nfs4_gte_ldir0(int);
extern void nfs4_gte_rt(void);
extern void nfs4_gte_dpcs(void);
extern void nfs4_gte_dpct(void);
extern "C" void NFSHS_GTE_DebugState(int *, int *, int *);
extern "C" void NFSHS_HostTraceDrawQuadCandidate(const void *, const void *, const void *, long, long, long, long);
        #define gte_SetRotMatrix(mp) nfs4_gte_set_rot_matrix(mp)
        #define gte_SetTransMatrix(mp) nfs4_gte_set_trans_matrix(mp)
    #else
        #define gte_SetRotMatrix(mp) ((void)(mp))
        #define gte_SetTransMatrix(mp) ((void)(mp))
    #endif
    #define gte_ldsv(p) ((void)(p))
    #define gte_stsv(p) ((void)(p))
    #define gte_stsxy(p) ((void)(p))
    #define gte_stsz(p) ((void)(p))
    #ifdef AP_WIN
        #define gte_stflg(p) nfs4_gte_stflg(p)
    #else
        #define gte_stflg(p) ((void)(p))
    #endif
    #define gte_rtir(...) ((void)0)
    #define gte_ldtr(...) ((void)0)
    #ifdef AP_WIN
        #define gte_rtps_b(...) gte_rtps()
    #else
        #define gte_rtps_b(...) ((void)0)
    #endif
    /* GTE ops Ghidra inlines as macro CALLS in draww (nclip/avsz/depth-cue/ldsxy3/ldIR0/rt) */
    #ifdef AP_WIN
        #define gte_nclip(...) nfs4_gte_nclip()
        #define gte_nclip_b(...) nfs4_gte_nclip()
        #define gte_avsz4(...) nfs4_gte_avsz4()
        #define gte_avsz4_b(...) nfs4_gte_avsz4()
    #else
        #define gte_nclip(...) ((void)0)
        #define gte_nclip_b(...) ((void)0)
        #define gte_avsz4(...) ((void)0)
        #define gte_avsz4_b(...) ((void)0)
    #endif
    #ifdef AP_WIN
        #define gte_dpcs(...) nfs4_gte_dpcs()
        #define gte_dpct(...) nfs4_gte_dpct()
        #define gte_ldsxy3(a, b, c) nfs4_gte_ldsxy3((int)(a), (int)(b), (int)(c))
        #define gte_ldIR0(p) nfs4_gte_ldir0((int)(p))
        #define gte_rt(...) nfs4_gte_rt()
    #else
        #define gte_dpcs(...) ((void)0)
        #define gte_dpct(...) ((void)0)
        #define gte_ldsxy3(a, b, c) ((void)0)
        #define gte_ldIR0(p) ((void)(p))
        #define gte_rt(...) ((void)0)
    #endif

extern "C" char *&Render_gPacketPtr;
extern "C" char *&Render_gPalettePtr;
extern "C" char *&Render_gPacketEnd;

/* ---- world/cop/night transform matrices (Ghidra-named; matrixtdef like SYM gWorldMat) ---- */
extern "C" MATRIX &Render_gWorldMat, &Render_gNightMat, &Render_gCopMat;

/* ---- PsyQ libgte / libgpu ---- */

/* ---- eaclib / math fixed-point + transform helpers ---- */

extern int Skid_gCtrlPoint_0, Skid_gCtrlPoint_1, Skid_gCtrlPoint_2, Skid_gCtrlPoint_3;
extern int Skid_gCtrlPoint_4, Skid_gCtrlPoint_5, Skid_gCtrlPoint_6;
extern "C" int &Skid_gCtrlScratch_94, &Skid_gCtrlScratch_98, Skid_gScratchPos1, Skid_gScratchPos2, &gScratchLastWord;
extern int &INT_1f800084, &INT_1f800088, &INT_1f80008c, &INT_1f800090;

/* ---- auto-generated from SYM Globals + Demangled ---- */
extern Trk_AnimateInst *Anim_gInstanceFromIndex[8];
extern Car_tObj *BW_gCopCarObj;
extern Trk_NewSlice *BWorldSm_slices;
extern int BWorld_gChunkCount;
extern "C" u_char CF_DVLC[49096];
extern camera_info Camera_gInfo[136];
extern Car_tObj *Cars_gHumanRaceCarList[2];
extern Car_tObj *Cars_gList[2];
extern "C" extern int Cars_gNumHumanRaceCars;
extern coorddef *Chunk_chunkCenters;
extern "C" CVECTOR *Chunk_lightTable;
extern "C" int Draw_gMidGroundOtz;
extern "C" int Draw_gViewOtSize;
extern "C" extern "C" GameSetup_tData GameSetup_gData;
extern u_char (*Night_gCopColor[2])[256][8];
extern "C" u_char (*Night_gCurrentNightColor)[256][16];
extern char *Night_gNightTbl;
extern u_char (*Night_gWeatherLightingTable[2])[256];
extern Group *Object_customObjInst;
extern Group *Object_customSimObjs;
extern "C" CTrackSpec TrackSpec_gSpec;
extern "C" Chunk *Track_chunkList;
extern "C" short *Track_gInViewList;
extern "C" Trk_ObjectDef **Track_gObjDefs;
extern "C" Track_tMaterial *Track_materials;
// [owned->defined in draww.cpp] extern int animation_timer[12];
// [owned->defined in draww.cpp] extern ChunkObjectInfo gChunkObjInfo;
extern "C" short gClutDepth[256][16];
extern matrixtdef gCopMat;
extern BW_tContext *gCurrContext;
extern Draw_tPixMap *gDLPixmap[2];
// [owned->defined in draww.cpp] extern Draw_SubdivStruct gDiv;
// [owned->defined in draww.cpp] extern MATRIX gIdentTemplate;
extern "C" Track_tArtresource gInitialArt;
extern matrixtdef gNightMat;
extern "C" extern int gNight_renderNight;
extern "C" Group *gPersistMidgroundObjInst;
extern "C" Group *gPersistObjDefBoundingSpheres;
extern "C" Group *gPersistObjInst;
extern Draw_tPixMap *gSkidMarkPixmap[1];
extern int gSpikeBeltSlice;
extern int gSpikeBeltX;
// [owned->defined in draww.cpp] extern CCOORD16 gVertex3d[320];
// [owned->defined in draww.cpp] extern DRender_tView * gVi;
// [owned->defined in draww.cpp] extern intptr gWSavePtr;
extern matrixtdef gWorldMat;
// [owned->defined in draww.cpp] extern char goffsets[8];
// [owned->defined in draww.cpp] extern char offsets[8];
extern "C" Sim_tSimGlobalVar simGlobal;
// [owned->defined in draww.cpp] extern int stackSpeedUpEnbabledFlag;
// [owned->defined in draww.cpp] extern int trk0[9][2];
// [owned->defined in draww.cpp] extern int trk4[10][2];
extern "C"
{
    extern void Anim_GetRotPos(Trk_AnimateInst *, int, int, coorddef *, matrixtdef *);
}
extern "C"
{
    extern int BWorld_IsSliceInBuildList(int);
}
extern void Flare_Halo2(DRender_tView *, int, int, coorddef *, coorddef *, Draw_FlareCache *);
extern void Math_fasttransmult(matrixtdef *, matrixtdef *, matrixtdef *);
extern ObjectAnim *Object_GetAnim(Trk_SimObject *);
extern void Quatern_QuatToMat(tQuat *, matrixtdef *);
extern void TrsProj_SetPsxTransZero(void);
extern void TrsProj_TransPt(coorddef *, coorddef *);
extern int xzsquaredist32(coorddef *, coorddef *);
/* forward decl missed by proto-emitter (defined later in draww.cpp, called earlier) */
extern int DrawObjectTransform(DRender_tView *Vi, Draw_DCache *sd, matrixtdef *matrix, Trk_ObjectDef *objDef, coorddef *pCp, int offset, short light);

#endif
