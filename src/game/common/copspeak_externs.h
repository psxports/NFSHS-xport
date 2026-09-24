#include "../../lib/libfns.h"
/* copspeak_externs.h -- cross-TU decls for game/common/copspeak.cpp (NFS4 cop-radio speech/SFX).
 *   Types (CopSpeak_tRequest, CopSpeak_tBank, Car_tObj, SNDSTREAMSTATUS) live in nfs4_types.h.
 *   copspeak OWNS its CopSpeak_g* + buffer/queue globals (defined in the .cpp). */
#ifndef COPSPEAK_EXTERNS_H
    #define COPSPEAK_EXTERNS_H

/* ---- audio (audiocmn/audioclc/audiomus.obj) ---- */
extern void AudioClc_SndError(int code = 0); /* Ghidra dropped the arg at one site */
extern "C"
{
    extern int AudioCmn_GetAsyncSfx(int a, int b, bool c);
}
extern "C"
{
    extern int AudioCmn_LoadAsyncSfx(int a, int b, void *buf, int n);
}
extern int AudioMus_Buffered(void);
extern "C"
{
    extern int AudioMus_Threshold(void);
}

/* ---- platform / hud / font / textpix ---- */
extern "C"
{
    extern char *Platform_GetDCTBuffer(int size, char *name); /* platform.obj */
}
extern void Hud_FBuildF4(int t, int x, int y, int w, int h, u_long col, char c0, char c1); /* hud.obj */
extern void Font_TextXY(char *s, int x, int y);                                            /* font.obj */
extern "C"
{
    extern int textpixels(char *s); /* textpix.obj */
}

/* ---- sndpsxz (SND*) ---- */

/* ---- eaclib async FILE I/O ---- */

/* ---- eaclib BIG archive ---- */

/* ---- eaclib mem / sys / libc ---- */
extern void trap(int code);

/* ---- more cross-TU globals ---- */
extern "C" int gMasterFENarrationLevel, gMasterAmbientLevel, gStereoMode; /* audiocmn.obj */
extern "C" int Audio_direct3davail;                                       /* audio.obj */
extern SndBnk_t gSndBnk[7];                                               /* audiocmn.obj */
extern "C" extern "C" char *Paths_Paths[50];                              /* paths.obj */
extern "C" char GameSetup_gCarNames[51][5];                               /* gmesetup.obj */
extern "C" char GameSetup_gTrackNames[12][4];                             /* gmesetup.obj */
extern "C" extern "C" GameSetup_tData GameSetup_gData;                    /* gmesetup.obj */

#endif /* COPSPEAK_EXTERNS_H */
