/* frontend/psx/psxfront_externs.h - reconstructed extern decls (from Ghidra signatures).
 * NOT an original header; added for standalone C++ compile. */
#ifndef _FRONTEND_PSX_PSXFRONT_EXTERNS_H_
#define _FRONTEND_PSX_PSXFRONT_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

typedef void EAC_timerproc(void); /* fn type; EAC_timerproc* = void(*)(void) */

extern "C"
{
    extern "C"
    {
        void AudioCmn_LoadFESamples(void);
    }
    extern "C"
    {
        void Audio_DeInitDriver(void);
    }
    extern "C"
    {
        void Audio_InitDriver(int buffersize, int spusize);
    }
    extern "C"
    {
        void CarIO_CleanUp(void);
    }
    extern "C"
    {
        void CarIO_ReStart(void);
    }
    extern "C"
    {
        void CarIO_StartUp(void);
    }
    extern "C"
    {
        void ClearPrimitivesBuffer(void);
    }
    extern "C"
    {
        void DrawC_ReadeMapData(void);
    }
    extern "C"
    {
        void Draw_DirectSetEnvironment(int x, int y, int w, int h, int edraw, int edisplay, int erase, int r, int g, int b);
    }
    extern "C"
    {
        void Draw_InitViewOT(void);
    }
    extern "C"
    {
        void Draw_InitViews(void);
    }
    extern "C"
    {
        int Draw_SetView(int x0, int y0, int x1, int y1, int w, int h, int dtd, int isbg, int otsize);
    }
    extern "C"
    {
        void Draw_SetViewMemBudget(int viewid, int totalmem);
    }
    extern "C"
    {
        void FETextRender_SetABR(int abr, bool trans);
    }
    extern "C"
    {
        void FETexture_LoadPmx(char *f, int index, tTexture_ShapeInfo *dest);
    }
    extern "C"
    {
        void Fe3D_InitShowroom(void);
    }
    extern "C"
    {
        void FeTools_init(void);
    }
    extern "C"
    {
        void Front_InitialMemCardCheck(void);
    }
    extern "C"
    {
        void Front_SecondaryMemCardCheck(void);
    }
    extern "C"
    {
        void Platform_ResetDCTBuffer(void);
    }
    extern "C"
    {
        void R3DCar_CleanUp(void);
    }
    extern "C"
    {
        void R3DCar_DeInstantiate3DCar(Car_tObj *carObj);
    }
    extern "C"
    {
        void R3DCar_DeInstantiate3DCarMenu(Car_tObj *carObj);
    }
    extern "C"
    {
        void R3DCar_Instantiate3DCar(Car_tObj *carObj, int index);
    }
    extern "C"
    {
        void R3DCar_PostStartUp(void);
    }
    extern "C"
    {
        void R3DCar_StartUp(void);
    }
    extern "C"
    {
        void SetPlayList(int ivealreadygotone);
    }
    extern "C"
    {
        void TextSys_LoadWords(int language);
    }
    extern "C"
    {
        void Texture_CleanupMenuTexture(void);
    }
    extern "C"
    {
        void Texture_InitMenuClut(void);
    }
    extern "C"
    {
        void Texture_InitMenuTexture(void);
    }
    extern "C"
    {
        void Texture_KillMenuTexture(void);
    }
    int elapsedticks(void);
    int play_movie(char movie);
    void trap(int code);
    /* eaclib timer proc (from pad.c) */

    /* --- external game globals (Ghidra-typed) --- */
    extern "C" u_char CF_DVLC[49096];
    extern "C" extern int ComingIntoTheFrontEndTheVeryFirstTime;
    extern "C" int DrawC_gMenuColor[2];
    extern "C" int DrawC_gMenuLights;
    extern "C" int DrawC_gMenuLightsDirection;
    extern "C" int Draw_gDoVSync;
    extern "C" int Draw_gPlayer1View;
    extern "C" extern int Draw_gRearView;
    extern "C" char GameSetup_gCarNames[51][5];
    extern "C" extern "C" GameSetup_tData GameSetup_gData;
    extern "C" extern "C" char *Paths_Paths[50];
    extern "C" extern int R3DCar_InMenu;
    extern "C" u_char *&Render_gPacketPtr;  /* GPU packet build cursor (byte-arith) */
    extern "C" u_char *&Render_gPalettePtr; /* GPU packet build cursor (byte-arith) */
    extern "C" u_long font_tint;
    extern "C" extern tfrontEnd frontEnd;
    extern "C" extern DRender_tView gCView;
    extern "C" extern tTexture_ShapeInfo *gCurrentShapes;
    extern "C" dflip gEnviro[2];
    extern "C" int gFlip;
    extern "C" u_short gFontClut;
    extern "C" int gMenuRotate[2];
    extern int inFrontEnd;
    extern int screenbpp;
    extern "C" int screenwidth;
}
#endif