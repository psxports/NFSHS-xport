#include "../../lib/libfns.h"
/* feapp_externs.h -- externs referenced by feapp.cpp (canonical decls from siblings + SYM Globals + usage inference) */
#ifndef FEAPP_EXTERNS_H
    #define FEAPP_EXTERNS_H

/* global instances / data */
extern tFEApplication *FEApp;
extern "C" extern tfrontEnd frontEnd;
extern tCarManager carManager;
extern tGlobalMenuDefs *menuDefs;
extern tScreenUserName *screenUserName;
extern "C" extern GameSetup_tData GameSetup_gData;
extern "C" Car_tStats Cars_gNewCarStatsList[9];
extern "C" tPadModuleState gPadinfo;
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;
extern "C" char bigBuf[];
extern int Cars_gNumRaceCars;
extern "C" int screenheight, ticks, gFlip, gLargestUnused, Draw_gPlayer1View, Draw_gDoVSync, currentVideo;

/* audio */
void AudioCmn_PlayFESFX(int);
extern "C"
{
    void AudioCmn_LoadFESamples(void);
}
int AudioMus_Buffered(void);
extern "C"
{
    int AudioMus_PlaySong(char *pattern);
}
extern "C"
{
    void AudioMus_StopSong(int);
}
extern "C"
{
    int AudioMus_Threshold(void);
}
extern "C"
{
    void AudioMus_Volume(int);
}
extern "C"
{
    void Audio_InitDriver(...);
}
extern "C"
{
    void Audio_DeInitDriver(void);
}
extern "C"
{
    int Audio_FECleanUp(void);
}
void FeAudio_systemtask(int);

/* draw / render */
extern "C"
{
    void DrawShapeExtended(int, int, int, int, int, int, tDrawShapeExtended *);
}
extern "C"
{
    DRAWENV *Draw_GetDRAWENV(int, int);
}
void Draw_StartFrameRender(void);
void Draw_StopFrameRender(void);
void Draw_StartRenderingView(int view);
void Draw_StopRenderingView(int view);
void PSXFront_AllocateDrawMemory(void);
void PSXFront_FreeDrawMemory(void);

/* text / tools / help shapes */
void FETextRender_FullText(char *, short, short, tMenuTextType, tMenuTextState, short);
extern "C"
{
    void FETextRender_FullTextRGB(char *, short, short, int, char, short);
}
extern "C"
{
    void FETextRender_SetABR(int, bool);
}
extern "C"
{
    int textpixels(char *);
}
extern "C"
{
    char *TextSys_Word(int id);
}
extern "C"
{
    void FeTools_init(void);
}
extern "C"
{
    int FeTools_deinit(void);
}
void LoadAllHelpShapes(void);
void FreeHelpShapeCluts(void);

/* input / clock / memcard / stats / misc subsystems */
tInputKeyType FEInput_GetKeyFromPlayer(tPlayer, long);
extern "C"
{
    void Front_ResetPSXController(int controller, int mode);
}
extern "C"
{
    void Clock_SystemStartUp(void);
}
extern "C"
{
    void Clock_SystemCleanUp(void);
}
extern "C"
{
    int Init_Memcard(...);
}
extern "C"
{
    int DeInit_Memcard(void);
}
extern "C"
{
    int StatChk_ClearNewRecords(void);
}
extern "C"
{
    void *StatChk_IsRecordLapTime(Car_tStats *, short, short *);
}
extern "C"
{
    short StatChk_IsTopTime(Car_tStats *, short);
}
PinkSlipsErrorCode SavePinkSlipsCarsWithErrorDialogs(short, short, short);
extern "C"
{
    char *PlayerName(int);
}
extern "C"
{
    void MenuExtended_PostGameMenu(tMenuCommand &command);
}
int play_movie(char);

/* CRT */

/* tDialog* vtables (defined in FEDialog.obj) */
extern __vtbl_ptr_type tDialogBase_vtable[], tDialogHelp_vtable[], tDialogMessageString_vtable[], tDialogNoInputMessage_vtable[];
extern __vtbl_ptr_type tDialogMessageStringWithTimeout_vtable[]; /* @0x80010098 (vtables_tdialog.cpp) */

#endif
