/* game/common/nfs3_externs.h -- auto-generated cross-TU decls for nfs3.cpp */
#ifndef _GAME_COMMON_NFS3_EXTERNS_H_
#define _GAME_COMMON_NFS3_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
#include "new.h"

/* cross-TU globals + unmangled lib fns referenced by nfs3.obj */
extern Speaker *_6Speech_fgUndefined;    /* Speech::fgUndefined */
extern Speech *_6Speech_fgSpeech;        /* Speech::fgSpeech */
// [owned->defined in nfs3.cpp] extern char befuddleExtensions[][4];
extern "C" char *Paths_Paths[];
extern "C" GameSetup_tData GameSetup_gData;
// [owned->defined in nfs3.cpp] extern tfrontEnd frontEnd;
extern "C" Sim_tSimSystemVar simVar;
extern Car_tObj *Cars_gList[];
extern Car_tObj *Cars_gHumanRaceCarList[];
extern "C" Car_tStats Cars_gNewCarStatsList[9];
// [owned->defined in nfs3.cpp] extern "C" int Cars_gNumHumanRaceCars, gUseFrontend, quitType;
extern "C" int Cars_gNumHumanRaceCars, quitType;
extern int *gFileMem, *gFileHandleTable;
extern "C" tReplayInterface Replay_ReplayInterface;
extern "C" int Replay_ReplayMode, ComingIntoTheFrontEndTheVeryFirstTime, CF_DVLC;
// [owned->defined in nfs3.cpp] extern tCarManager carManager; extern tTrackManager trackManager;
// [owned->defined in nfs3.cpp] extern tTournamentManager tournamentManager; extern tMissionManager missionManager;
extern "C" unsigned char bigBuf[];
/* GCC global-ctor caller (crt0) */
/* libc / eaclib / libgpu / libetc (unmangled) */
extern void restoretextdraw(void);

extern "C"
{
    extern void AudioClc_StartUp(void);
}
extern void AudioCmn_DeInit(void);
extern void AudioCmn_LoadGameSamples(void);
extern "C"
{
    extern void AudioCmn_Reset(void);
}
extern void AudioMus_BuildPlayList(int, int *);
extern "C"
{
    extern int AudioMus_PlaySong(char *);
}
extern "C"
{
    extern void AudioMus_SysStartUp(int, int, const char *);
}
extern "C"
{
    extern void Audio_DeInitDriver(void);
}
extern "C"
{
    extern void Audio_InitDriver(int, int);
}
extern "C"
{
    extern void BWorld_DeInit(void);
}
extern "C"
{
    extern void BWorld_Init(void);
}
extern "C"
{
    extern void BWorld_Restart(void);
}
extern "C"
{
    extern void Camera_Init(void);
}
extern "C"
{
    extern void Camera_Kill(void);
}
extern "C"
{
    extern void Clock_SystemCleanUp(void);
}
extern "C"
{
    extern void Clock_SystemStartUp(void);
}
extern void CopSpeak_CleanUp(void);
extern void CopSpeak_StartUp(void);
extern "C"
{
    extern void DashHUD_ResetHUD(void);
}
extern "C"
{
    extern void Draw_DirectSetEnvironment(int, int, int, int, int, int, int, int, int, int);
}
extern "C"
{
    extern void FECheat_ActivateBonus(tCheatCode);
}
extern "C"
{
    extern int Front_BuildStream(int *);
}
extern "C"
{
    extern void Front_GetInGameVars(void);
}
extern "C"
{
    extern void Front_InitGraphics(void);
}
extern "C"
{
    extern void Front_InitGraphicsAndDisplayLoading(void);
}
extern int Front_Menu(tFront_ProcessingType);
extern "C"
{
    extern void GameSetup_CleanUp(void);
}
extern "C"
{
    extern void GameSetup_StartUp(int *);
}
extern "C"
{
    extern void Hrz_InitHorizon(void);
}
extern "C"
{
    extern void Hrz_KillHorizon(void);
}
extern "C"
{
    extern void Hud_InitMap(void);
}
/* tCar/Track/Mission/TournamentManager::Initialize/LoadDescription now called as C++ members (front.obj) -- flat externs removed */
extern "C"
{
    extern void Loading_DrawLoadingScreen(void);
}
extern "C"
{
    extern void Loading_GetInitialMemory(void);
}
extern "C"
{
    extern void Loading_UpdateLoadingScreen(int);
}
extern "C"
{
    extern int MinFront_ParseOptions(void);
}
extern "C"
{
    extern void Night_InitNightDriving(void);
}
extern "C"
{
    extern void Physics_CheckGamedata(void);
}
extern "C"
{
    extern void Platform_DebuggerPollHost(void);
}
extern "C"
{
    extern void Platform_InitMemory(void);
}
extern "C"
{
    extern void Platform_ResetDCTBuffer(void);
}
extern "C"
{
    extern void Platform_SysStartUp(void);
}
/* tCar/Track/Mission/TournamentManager::ReleaseDescription now C++ members (front.obj) -- flat externs removed */
extern "C"
{
    extern void Render_InitLibRender(void);
}
extern "C"
{
    extern void Render_InitPauseMenu(void);
}
extern "C"
{
    extern void Render_InitTrackRender(void);
}
extern "C"
{
    extern void Render_InitTrackRenderPostSim(void);
}
extern "C"
{
    extern void Render_KillPauseMenu(void);
}
extern "C"
{
    extern void Render_KillTrackRender(void);
}
extern "C"
{
    extern void Replay_InitReplay(void);
}
extern "C"
{
    extern void Replay_ResetReplay(void);
}
extern "C"
{
    extern void Replay_StoringReplay(void);
}
/* tCarManager::SetClassViewable now called as C++ member (front.obj) -- flat extern removed */
extern "C"
{
    extern void SimQueue_StartUp(void);
}
extern "C"
{
    extern void Sim_CleanUp(void);
}
extern "C"
{
    extern void Sim_MainGameLoop(void);
}
extern "C"
{
    extern void Sim_Restart(void);
}
extern "C"
{
    extern void Sim_StartUp(void);
}

extern int Stats_GetNumOpponents(void);
extern "C"
{
    extern void Weather_DeInit(void);
}
extern "C"
{
    extern void Weather_Init(void);
}
extern "C"
{
    extern void Weather_Restart(void);
}
extern void Speech_Reset();


#endif
