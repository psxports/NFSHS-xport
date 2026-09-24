#include "../../lib/libfns.h"
/* draww_externs.h -- extern decls for game/psx/drawc.cpp (NFS4 PSX world-geometry draw). */
#ifndef DRAWC_EXTERNS_H
    #define DRAWC_EXTERNS_H

/* ---- Night.obj globals (defined in night.cpp) -- weather/lightning tint, DrawC_NightHeadlight (H46) ---- */
extern char Night_gDrawLightning;   /* @0x8013d9e0 (bss=0) */
extern int Night_gLightningType;    /* @0x8013da44 (bss=0) */
extern long Night_gWeatherColor[2]; /* @0x8013da88 (bss=0) -- per-type RGB tint (bytes 0/1/2 = R/G/B) */

/* ---- GTE intrinsics -------------------------------------------------------
 * The reconstructed PSX source retained PsyQ macro names.  On Windows these
 * must operate on the host GTE state; leaving them symbolic/no-op silently
 * culls car shadows and object facets because bfct/SXY/OTZ never update. */
extern void gte_rtps(void);
extern void gte_rtpt(void);
extern void gte_lwc2(int reg, int data);
extern void gte_swc2(int reg, void *ptr);
extern "C" void NFSHS_HostTraceDrawCPrimEntry(const void *, const void *, const void *, const void *, int, const void *);
    #ifdef AP_WIN
extern void nfs4_gte_set_rot_matrix(const void *);
extern void nfs4_gte_set_trans_matrix(const void *);
extern void nfs4_gte_nclip(void);
extern void nfs4_gte_avsz4(void);
extern void nfs4_gte_avsz3(void);
extern void nfs4_gte_rt(void);
        #define gte_SetRotMatrix(p) nfs4_gte_set_rot_matrix(p)
        #define gte_SetTransMatrix(p) nfs4_gte_set_trans_matrix(p)
        /* PsyQ gte_stsz reads SZ3 and stores SZ3>>2.  DrawC_PrimStart's emitted
   MIPS is mfc2 $12,$19; sra $12,2; sw $12,(p) at 0x800BEDF4..0x800BEE00. */
        #define gte_stsz(p) \
            do \
            { \
                int nfs4_sz_; \
                gte_swc2(19, &nfs4_sz_); \
                *(int *)(p) = nfs4_mips_sra_s32(nfs4_sz_, 2); \
            } while (0)
        #define gte_rt(...) nfs4_gte_rt()
        #define gte_nclip(...) nfs4_gte_nclip()
        #define gte_nclip_b(...) nfs4_gte_nclip()
        #define gte_avsz4(...) nfs4_gte_avsz4()
        #define gte_avsz4_b(...) nfs4_gte_avsz4()
        #define gte_avsz3(...) nfs4_gte_avsz3()
        #define gte_ldVXY0(p) gte_lwc2(0, *(int *)(p))
        #define gte_ldVZ0(p) gte_lwc2(1, *(short *)(p))
        #define gte_ldVXY1(p) gte_lwc2(2, *(int *)(p))
        #define gte_ldVZ1(p) gte_lwc2(3, *(short *)(p))
        #define gte_ldVXY2(p) gte_lwc2(4, *(int *)(p))
        #define gte_ldVZ2(p) gte_lwc2(5, *(short *)(p))
        /* These original macros store into fixed Draw_CarCache scratch offsets. */
        #define gte_stMAC0(...) gte_swc2(24, &sd->bfct)
        #define gte_stOTZ(...) gte_swc2(7, &sd->otz)
        #define gte_stSXY0(...) gte_swc2(12, &sd->dvx0)
        #define gte_stSXY1(...) gte_swc2(13, &sd->dvx1)
        #define gte_stSXY2(...) gte_swc2(14, &sd->dvx2)
    #else
        #define gte_SetRotMatrix(...) ((void)0)
        #define gte_SetTransMatrix(...) ((void)0)
        #define gte_stsz(...) ((void)0)
        #define gte_rt(...) ((void)0)
        #define gte_nclip(...) ((void)0)
        #define gte_nclip_b(...) ((void)0)
        #define gte_avsz4(...) ((void)0)
        #define gte_avsz4_b(...) ((void)0)
        #define gte_avsz3(...) ((void)0)
        #define gte_ldVXY0(...) ((void)0)
        #define gte_ldVZ0(...) ((void)0)
        #define gte_ldVXY1(...) ((void)0)
        #define gte_ldVZ1(...) ((void)0)
        #define gte_ldVXY2(...) ((void)0)
        #define gte_ldVZ2(...) ((void)0)
        #define gte_stMAC0(...) ((void)0)
        #define gte_stOTZ(...) ((void)0)
        #define gte_stSXY0(...) ((void)0)
        #define gte_stSXY1(...) ((void)0)
        #define gte_stSXY2(...) ((void)0)
    #endif
    #define gte_ldsv(...) ((void)0)
    #define gte_stsv(...) ((void)0)
    #define gte_stsxy(...) ((void)0)
    #define gte_stflg(...) ((void)0)
    #define gte_rtir(...) ((void)0)
    #define gte_ldtr(...) ((void)0)
    #define gte_rtps_b(...) ((void)0)
    /* GTE ops Ghidra inlines as macro CALLS in draww (nclip/avsz/depth-cue/ldsxy3/ldIR0/rt) */
    #define gte_dpcs(...) ((void)0)
    #define gte_dpct(...) ((void)0)
    #define gte_ldsxy3(...) ((void)0)
    #define gte_ldIR0(...) ((void)0)
/* ---- PsyQ libgte / libgpu (seed; extend as compile demands) ---- */

/* ---- game externs (harvested from sealed modules + usage-typed; int=TODO refine) ---- */
extern void *BWorldSm_TunnelFlagSm(BWorldSm_Pos *pos);
extern void CarIO_UpdateCarTextureData(char *, Car_tObj *, int);
extern "C" Draw_tPixMap *CarIO_carPixMap;
extern Car_tObj *Cars_gHumanRaceCarList[2];
extern Car_tObj *Cars_gList[2];
extern int Cars_kSkidMarkSurface[16];
extern "C" short DrawC_HeadLightFlash[16];
extern "C" short DrawC_SirenFlash[16];
extern "C" short DrawC_TailLightFlash[16];
extern "C" DrawC_tEnvMap *DrawC_gEnvMap;
extern "C" int DrawC_gEnvMapMax; /* TODO type-refine */
extern "C" short DrawC_gEnvMapOffset[4];
extern "C" MATRIX DrawC_gMatA;
extern "C" int DrawC_gMenuColor[2];
extern "C" int DrawC_gMenuLightsDirection; /* TODO type-refine */
extern "C" short DrawC_gOverlay[51];
extern "C" short DrawC_gReflectOffset; /* 0x8013d814 */
extern "C" MATRIX DrawC_gScreenMat;
extern "C" DrawC_tEnvMap *DrawC_gShadow;
extern "C" int DrawC_gShadowMax; /* TODO type-refine */
extern "C" int DrawC_gWetRoad;   /* TODO type-refine */
extern void DrawW_WorldSetUpMatrix(matrixtdef *, MATRIX *);
extern void DrawW_WorldSetUpTranslation(coorddef *, MATRIX *);
extern "C"
{
    extern DRAWENV *Draw_GetDRAWENV(int view, int buf);
}
extern "C" int Draw_gViewOtSize;
extern "C" COORD16 Fe3D_lightsVertex[64]; /* 0x80051334  ARY STRUCT COORD16 x64 */
extern "C" COORD16 Fe3D_spotVertex[33];   /* 0x8005126c  ARY STRUCT COORD16 x33 */
extern short *Flare_CarShapedHalo(int, COORD16 *, COORD16 *, COORD16 *, short, int, Draw_FlareCache *);
extern "C" extern "C" GameSetup_tData GameSetup_gData;
extern void Night_AdditiveNightCalc(VECTOR *, CVECTOR *);
extern "C" extern char *Paths_Paths[]; /* 0x80116468 */
extern void R3DCar_GetCarName(char *, int, int);
extern "C" extern int R3DCar_Clock, R3DCar_ClockLast, R3DCar_InMenu;
extern CVECTOR R3DCar_eMapColour;
extern "C" short R3DCar_yawCam;
extern void R3DCcar_ReadTrackShadow(void);
extern void R3DCcar_ReadeMapData(void);
extern "C" char *&Render_gPacketPtr;
extern int Risk_ReadNextValue(char **);
extern int Texture_CarColor; /* 0x8013db08 */
extern void Texture_ProcessPaletteCopy(Texture_pal8bit *, int, int);
extern "C" Draw_tPixMap Track_gReflectionMaps[4];
extern void TrsProj_ResetTransPrecision(void);
extern void TrsProj_SetTransPrecision(int);
extern int TrsProj_precision;           /* 0x8013db9c */
extern "C" extern DRender_tView gCView; /* 0x80116f7c */
extern "C" int gFlip;                   /* 0x8013d7b4 */
extern Draw_tPixMap *gMenuPixmap[8];    /* 0x80120fd0 */
extern matrixtdef gNightMat;
extern Draw_tPixMap *gShadowPixmap[2];
extern "C" int gShowroomLights; /* TODO type-refine */
extern "C" u_long hilight_colors[5];

#endif
