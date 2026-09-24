/* game/common/nfs3_externs.h -- auto-generated cross-TU decls for nfs3.cpp */
#ifndef _GAME_COMMON_NFS3_EXTERNS_H_
#define _GAME_COMMON_NFS3_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
#include "new.h"

/* cross-TU globals + unmangled lib fns referenced by nfs3.obj */
extern Speaker *_6Speech_fgUndefined;    /* Speech::fgUndefined */
extern Speech *_6Speech_fgSpeech;        /* Speech::fgSpeech */
extern __vtbl_ptr_type Speaker_vtable[]; /* @0x80055dc4  Speech::Speaker vtable (defined in speech.cpp); Ghidra fabricated the name "Speech_Speaker_vtable" for this same VA */
// [owned->defined in nfs3.cpp] extern char befuddleExtensions[][4];
extern "C" extern "C" char *Paths_Paths[];
extern "C" extern "C" GameSetup_tData GameSetup_gData;
// [owned->defined in nfs3.cpp] extern tfrontEnd frontEnd;
extern "C" Sim_tSimSystemVar simVar;
extern Car_tObj *Cars_gList[];
extern Car_tObj *Cars_gHumanRaceCarList[];
extern "C" Car_tStats *Cars_gNewCarStatsList;
// [owned->defined in nfs3.cpp] extern "C" int Cars_gNumHumanRaceCars, gUseFrontend, quitType;
extern "C" int Cars_gNumHumanRaceCars, quitType;
extern int *gFileMem, *gFileHandleTable;
extern "C" tReplayInterface Replay_ReplayInterface;
extern "C" int Replay_ReplayMode, ComingIntoTheFrontEndTheVeryFirstTime, CF_DVLC;
// [owned->defined in nfs3.cpp] extern tCarManager carManager; extern tTrackManager trackManager;
// [owned->defined in nfs3.cpp] extern tTournamentManager tournamentManager; extern tMissionManager missionManager;
extern "C" unsigned char bigBuf[];
extern void trap(unsigned int);
/* GCC global-ctor caller (crt0) */
/* libc / eaclib / libgpu / libetc (unmangled) */
extern void restoretextdraw(void);

extern "C"
{
    extern int AudioClc_StartUp(void);
}
extern void AudioCmn_DeInit(void);
extern void AudioCmn_LoadGameSamples(void);
extern "C"
{
    extern int AudioCmn_Reset(void);
}
extern void AudioMus_BuildPlayList(int, int *);
extern "C"
{
    extern int AudioMus_PlaySong(char *);
}
extern "C"
{
    extern int AudioMus_SysStartUp(int, int, char *);
}
extern "C"
{
    extern int Audio_DeInitDriver(void);
}
extern "C"
{
    extern int Audio_InitDriver(int, int);
}
extern "C"
{
    extern int BWorld_DeInit(void);
}
extern "C"
{
    extern int BWorld_Init(void);
}
extern "C"
{
    extern int BWorld_Restart(void);
}
extern "C"
{
    extern int Camera_Init(void);
}
extern "C"
{
    extern int Camera_Kill(void);
}
extern "C"
{
    extern int Clock_SystemCleanUp(void);
}
extern "C"
{
    extern int Clock_SystemStartUp(void);
}
extern void CopSpeak_CleanUp(void);
extern void CopSpeak_StartUp(void);
extern "C"
{
    extern int DashHUD_ResetHUD(void);
}
extern "C"
{
    extern int Draw_DirectSetEnvironment(int, int, int, int, int, int, int, int, int, int);
}
extern "C"
{
    extern int FECheat_ActivateBonus(tCheatCode);
}
extern "C"
{
    extern int Front_BuildStream(int *);
}
extern "C"
{
    extern int Front_GetInGameVars(void);
}
extern "C"
{
    extern int Front_InitGraphics(void);
}
extern "C"
{
    extern int Front_InitGraphicsAndDisplayLoading(void);
}
extern int Front_Menu(tFront_ProcessingType);
extern "C"
{
    extern int GameSetup_CleanUp(void);
}
extern "C"
{
    extern int GameSetup_StartUp(int *);
}
extern "C"
{
    extern int Hrz_InitHorizon(void);
}
extern "C"
{
    extern int Hrz_KillHorizon(void);
}
extern "C"
{
    extern int Hud_InitMap(void);
}
/* tCar/Track/Mission/TournamentManager::Initialize/LoadDescription now called as C++ members (front.obj) -- flat externs removed */
extern "C"
{
    extern int Loading_DrawLoadingScreen(void);
}
extern "C"
{
    extern int Loading_GetInitialMemory(void);
}
extern "C"
{
    extern int Loading_UpdateLoadingScreen(int);
}
extern "C"
{
    extern int MinFront_ParseOptions(void);
}
extern "C"
{
    extern int Night_InitNightDriving(void);
}
extern "C"
{
    extern int Physics_CheckGamedata(void);
}
extern "C"
{
    extern int Platform_DebuggerPollHost(void);
}
extern "C"
{
    extern int Platform_InitMemory(void);
}
extern "C"
{
    extern int Platform_ResetDCTBuffer(void);
}
extern "C"
{
    extern int Platform_SysStartUp(void);
}
/* tCar/Track/Mission/TournamentManager::ReleaseDescription now C++ members (front.obj) -- flat externs removed */
extern "C"
{
    extern int Render_InitLibRender(void);
}
extern "C"
{
    extern int Render_InitPauseMenu(void);
}
extern "C"
{
    extern int Render_InitTrackRender(void);
}
extern "C"
{
    extern int Render_InitTrackRenderPostSim(void);
}
extern "C"
{
    extern int Render_KillPauseMenu(void);
}
extern "C"
{
    extern int Render_KillTrackRender(void);
}
extern "C"
{
    extern int Replay_InitReplay(void);
}
extern "C"
{
    extern int Replay_ResetReplay(void);
}
extern "C"
{
    extern int Replay_StoringReplay(void);
}
/* tCarManager::SetClassViewable now called as C++ member (front.obj) -- flat extern removed */
extern "C"
{
    extern int SimQueue_StartUp(void);
}
extern "C"
{
    extern int Sim_CleanUp(void);
}
extern "C"
{
    extern int Sim_MainGameLoop(void);
}
extern "C"
{
    extern int Sim_Restart(void);
}
extern "C"
{
    extern int Sim_StartUp(void);
}
extern Speech *Speech_ct(Speech *);
extern int Stats_GetNumOpponents(void);
extern "C"
{
    extern int Weather_DeInit(void);
}
extern "C"
{
    extern int Weather_Init(void);
}
extern "C"
{
    extern int Weather_Restart(void);
}
extern void Speech_Reset();
extern void Speech_dt(Speech *, u_int);

#endif
