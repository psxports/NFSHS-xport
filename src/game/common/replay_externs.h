#include "../../lib/libfns.h"
/* replay_externs.h -- extern decls for game/psx/replay.cpp
 *   (NFS4 PSX replay record/playback: per-frame controller capture + RLE-style compress into a
 *    ring buffer, decompress on playback, camera-file load and replay-camera selection). */
#ifndef REPLAY_EXTERNS_H
    #define REPLAY_EXTERNS_H

/* ---- replay state globals ---- */
extern "C" tReplayBuffer Replay_ReplayBuffer;         /* 0x8011716c (27180B; .buffer[24576] @0xA2C) */
extern "C" tReplayInterface Replay_ReplayInterface;   /* 0x8011702c */
extern "C" tReplayCameraModes Replay_ReplayCamera[2]; /* 0x8011704c */
extern "C" tControllerData controlData[];             /* 0x8011706c (256B) */
extern "C" int Replay_ReplayCounter[2];               /* 0x8013d400 */
extern "C" int Replay_ReplayMode;                     /* 0x8013d3f4 */
extern "C" int Replay_ReplayStorePtr;                 /* 0x8013d3f8 */
extern "C" int Replay_ReplayGetPtr;                   /* 0x8013d3fc */
extern "C" int Replay_Size;                           /* 0x8013d3ec */
extern "C" int ReplayCameraList[];                    /* 0x80117008 (int[9]) */
extern "C" int numValidCams;                          /* 0x8013d3f0 */
extern "C" char compressed_data[33];                  /* 0x8011db98 */
extern "C" char uncompressed_data[32];                /* 0x8011dbbc */

/* ---- camera + slices ---- */
extern "C" Camera_tCamSlot gReplayCameraSlots[]; /* 0x8011dbdc (1024B) */
extern camera_info Camera_gInfo[];               /* 0x8010f2ac (544B) */
extern int gNumSlices;                           /* 0x8013c7c8 */

/* ---- sim / cars / input / setup ---- */
extern "C" Sim_tSimGlobalVar simGlobal; /* 0x8011e0ac */
extern "C" Sim_tSimSystemVar simVar;    /* 0x8011e0c4 */
extern Car_tObj *Cars_gHumanRaceCarList[2];
extern "C" extern int Cars_gNumHumanRaceCars;
extern Input_tResults Input_gSim; /* per-frame fetched controller state */
extern "C" int StatsTimer[2];
extern "C" extern "C" GameSetup_tData GameSetup_gData;
extern "C" extern char *Paths_Paths[]; /* 0x80116468 */

/* ---- functions ---- */
extern void Input_Fetch(int car);
extern "C"
{
    extern int Input_Interface(unsigned long button, int player);
}
extern void Camera_Update(void);
extern void Camera_SetMode(int player, int mode);
extern void Camera_ReplayUpdate(int player, Camera_tCamSlot *slot);
extern void AudioCmn_PlayPauseSound(int which);

#endif
