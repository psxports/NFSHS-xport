#include "../../lib/libfns.h"
/* draww_externs.h -- extern decls for game/psx/drawc.cpp (NFS4 PSX world-geometry draw). */
#ifndef DRAWC_EXTERNS_H
    #define DRAWC_EXTERNS_H

/* ---- Night.obj globals (defined in night.cpp) -- weather/lightning tint, DrawC_NightHeadlight (H46) ---- */
extern char Night_gDrawLightning;   /* @0x8013d9e0 (bss=0) */
extern int Night_gLightningType;    /* @0x8013da44 (bss=0) */
extern long Night_gWeatherColor[2]; /* @0x8013da88 (bss=0) -- per-type RGB tint (bytes 0/1/2 = R/G/B) */

#include "psx_gte.h"
extern "C" void NFSHS_HostTraceDrawCPrimEntry(const void *, const void *, const void *, const void *, int, const void *);

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
extern "C" GameSetup_tData GameSetup_gData;
extern void Night_AdditiveNightCalc(VECTOR *, CVECTOR *);
extern "C" char *Paths_Paths[]; /* 0x80116468 */
extern void R3DCar_GetCarName(char *, int, int);
extern "C" int R3DCar_Clock, R3DCar_ClockLast, R3DCar_InMenu;
extern CVECTOR R3DCar_eMapColour;
extern char R3DCar_SignalBrakeFlare[28];
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
extern int TrsProj_precision;        /* 0x8013db9c */
extern "C" DRender_tView gCView;     /* 0x80116f7c */
extern "C" int gFlip;                /* 0x8013d7b4 */
extern Draw_tPixMap *gMenuPixmap[8]; /* 0x80120fd0 */
extern matrixtdef gNightMat;
extern Draw_tPixMap *gShadowPixmap[2];
extern "C" int gShowroomLights; /* TODO type-refine */
extern "C" uint32 hilight_colors[5];

#endif
