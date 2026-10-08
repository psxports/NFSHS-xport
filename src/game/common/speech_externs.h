#include "../../lib/libfns.h"
/* speech_externs.h -- cross-TU decls for game/common/speech.cpp (NFS4 cop speech/dispatch).
 *   Types in nfs4_types.h. speech.obj OWNS its globals + Speech_fgSpeech/fgUndefined (.cpp). */
#ifndef SPEECH_EXTERNS_H
    #define SPEECH_EXTERNS_H

    /* ---- speech-event trigger fns (spchevnt.cpp, unmangled C-linkage; variadic call sites) ---- */
    #if defined(_MSC_VER) || defined(__EMSCRIPTEN__)
        #include "spchevnt.h"
extern "C"
{
    int SPCH_AddBank(intptr bank);
    void SPCH_ClearEventQueue(void);
    void SPCH_Deinit(void);
    int SPCH_GetSampleDataRate(int numSamples, int rate, int channels);
    int SPCH_Init(intptr sampleRequestCb, unsigned int gameNum, int dataRate);
    intptr SPCH_InitBankMem(intptr memAllocFn, intptr memFreeFn, int numBanks);
    void SPCH_PlaySpeech(void);
    int SPCH_ResolveData(unsigned short *dat);
}
    #else
extern "C"
{
    extern "C"
    {
        long SPCHNFS_C_A_CONFIRM(SPCHNFSType_VOICE *VOICE, int ID_UNIT, SPCHNFSType_CONFIRM *CONFIRM);
    }
    extern "C"
    {
        long SPCHNFS_C_A_INTRO(SPCHNFSType_VOICE *VOICE, int ID_UNIT, int ID_UNIT1, SPCHNFSType_REVINTRO *REVINTRO);
    }
    extern "C"
    {
        long SPCHNFS_C_C_IDLE_WINGMAN_DISAPPEARS(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_C_IN_PURS_NEAR_PERP(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR);
    }
    extern "C"
    {
        long SPCHNFS_C_C_NEW_OFFICER_ENGAGING(SPCHNFSType_VOICE *VOICE, int ID_UNIT);
    }
    extern "C"
    {
        long SPCHNFS_C_C_PERP_REAQUIRED(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_DURING_FALSE_ARREST(SPCHNFSType_VOICE *VOICE, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_ENDGAME(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_ENGAGE_PURS_REP_SPDR(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE, int ID_SPEED, SPCHNFSType_vs_KMH_MPH *vs_KMH_MPH, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_ENGAGE_PURS_REP_SPDR_REPLY(SPCHNFSType_VOICE *VOICE, int ID_UNIT, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_CONFIRM *CONFIRM);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_AWAY_PERP_REPLY_LOC(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_AWAY_PERP_REPLY_STS(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_LOOK_PERP_REPLY_LOC(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_LOOK_PERP_REPLY_STS(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_LOC(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_SPD(SPCHNFSType_VOICE *VOICE, int ID_SPEED, SPCHNFSType_vs_KMH_MPH *vs_KMH_MPH);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_NEAR_PERP_REP_STS(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION);
    }
    extern "C"
    {
        long SPCHNFS_C_D_IN_PURS_PERP_AIRBORN(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_PERP_APPREHENSION(SPCHNFSType_VOICE *VOICE, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_PERP_CRASH_GEN(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_PERP_CRASH_ROLL(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_PERP_LOST(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_PERP_SIGHTED(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_C_D_RDBLK_FAILED(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR);
    }
    extern "C"
    {
        long SPCHNFS_C_D_REQUEST_BKUP(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_REQUEST_EMS(SPCHNFSType_VOICE *VOICE, SPCHNFSType_AMBULANCE *AMBULANCE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_REQ_RDBLK(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_REQ_SPBLT(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_D_SPBLT_FAILED(SPCHNFSType_VOICE *VOICE, SPCHNFSType_COLOUR *COLOUR, int ID_CAR);
    }
    extern "C"
    {
        long SPCHNFS_C_P_ARRESTED(SPCHNFSType_VOICE *VOICE, SPCHNFSType_ARREST *ARREST);
    }
    extern "C"
    {
        long SPCHNFS_C_P_BULLHORN_SPEECH(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_P_FALSE_ARREST_BULLHORN(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_C_P_TICKET(SPCHNFSType_VOICE *VOICE, SPCHNFSType_ARREST *ARREST);
    }
    extern "C"
    {
        long SPCHNFS_C_P_WARNING(SPCHNFSType_VOICE *VOICE, SPCHNFSType_ARREST *ARREST);
    }
    extern "C"
    {
        long SPCHNFS_D_A_CONFIRM(SPCHNFSType_CONFIRM *CONFIRM);
    }
    extern "C"
    {
        long SPCHNFS_D_C_BEGIN_PURS_REP_SPDR(SPCHNFSType_COLOUR *COLOUR, int ID_CAR, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_D_C_BKUP_REQUEST_DENIED_REPLY(void);
    }
    extern "C"
    {
        long SPCHNFS_D_C_BKUP_REQUEST_GRANT_REPLY(SPCHNFSType_DISTANCE *DISTANCE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, int ID_UNIT);
    }
    extern "C"
    {
        long SPCHNFS_D_C_INTRO_CALL(int ID_UNIT, int ID_UNIT1, SPCHNFSType_REVINTRO *REVINTRO);
    }
    extern "C"
    {
        long SPCHNFS_D_C_IN_PURS_AWAY_PERP_CONFIRM(SPCHNFSType_COLOUR *COLOUR, int ID_CAR, int ID_UNIT, SPCHNFSType_CONFIRM *CONFIRM, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_D_C_IN_PURS_NEAR_PERP(SPCHNFSType_PURS_UPDT *PURS_UPDT);
    }
    extern "C"
    {
        long SPCHNFS_D_C_IN_PURS_NEAR_PERP_CONFIRM(SPCHNFSType_COLOUR *COLOUR, int ID_CAR, int ID_UNIT, SPCHNFSType_CONFIRM *CONFIRM, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_D_C_PERP_APPREHENSION_REPLY(int ID_UNIT, SPCHNFSType_CONFIRM *CONFIRM, SPCHNFSType_PERP_NAME *PERP_NAME);
    }
    extern "C"
    {
        long SPCHNFS_D_C_PERP_LOST_CONFIRM(SPCHNFSType_COLOUR *COLOUR, int ID_CAR);
    }
    extern "C"
    {
        long SPCHNFS_D_C_PERP_SIGHTED_CONFIRM(SPCHNFSType_CONFIRM *CONFIRM, int ID_UNIT);
    }
    extern "C"
    {
        long SPCHNFS_D_C_RDBLK_CONFIRMED(SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_D_C_RDBLK_SPBLT_DENIED_REPLY(SPCHNFSType_vs_RDBLK_SSTRP *vs_RDBLK_SSTRP);
    }
    extern "C"
    {
        long SPCHNFS_D_C_RDBLK_SPBLT_GRANT_REPLY(SPCHNFSType_vs_RDBLK_SSTRP *vs_RDBLK_SSTRP, SPCHNFSType_CONFIRM *CONFIRM);
    }
    extern "C"
    {
        long SPCHNFS_D_C_SPBLT_CONFIRMED(SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE, int ID_UNIT, SPCHNFSType_SPIKE_BELT_SIDE *SPIKE_BELT_SIDE);
    }
    extern "C"
    {
        long SPCHNFS_S_C_SUPER_COP_ARRIVAL(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_S_C_SUPER_COP_CRITICISM(SPCHNFSType_VOICE *VOICE);
    }
    extern "C"
    {
        long SPCHNFS_W_D_RDBLK_PLC(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    extern "C"
    {
        long SPCHNFS_W_D_SPBLT_PLC(SPCHNFSType_VOICE *VOICE, SPCHNFSType_POSITION *POSITION, SPCHNFSType_SPIKE_BELT_SIDE *SPIKE_BELT_SIDE, int ID_UNIT, int ID_LOCATION, SPCHNFSType_DISTANCE *DISTANCE);
    }
    int SPCH_AddBank(intptr bank);
    void SPCH_ClearEventQueue(void);
    void SPCH_Deinit(void);
    int SPCH_GetSampleDataRate(int numSamples, int rate, int channels);
    int SPCH_Init(intptr sampleRequestCb, unsigned int gameNum, int dataRate);
    intptr SPCH_InitBankMem(intptr memAllocFn, intptr memFreeFn, int numBanks);
    void SPCH_PlaySpeech(void);
    int SPCH_ResolveData(unsigned short *dat);
}
    #endif

/* ---- SPCH_ speech-runtime API ---- */ /* (declared above; variadic) */

/* ---- audio ---- */
extern "C"
{
    extern int AudioMus_PlaySong(char *);
}
extern "C"
{
    extern void AudioMus_StopSong(int fadeticks);
}
extern "C"
{
    extern int AudioMus_Threshold(void);
}

/* ---- CopSpeak (sibling TU) ---- */
extern "C"
{
    extern void CopSpeak_DirectRequest(int filehandle, long offset, long size, Car_tObj *car, char *name);
}
extern "C"
{
    extern void CopSpeak_Flush(void);
}
extern "C"
{
    extern void CopSpeak_GenericBankRequest(int patch, Car_tObj *car);
}
extern int CopSpeak_gSpchHandle;

/* ---- eaclib / PsyQ / file I/O ---- */

/* ---- libc ---- */

/* ---- GCC 2.7.2 runtime (C++ new/delete, soft-float) ---- */
extern void *__builtin_new(unsigned);
extern void __builtin_delete(void *);

/* ---- cross-TU globals (typed from SYM Globals.jsonl) ---- */
extern "C" GameSetup_tData GameSetup_gData;
extern "C" char GameSetup_gCarNames[51][5];
extern "C" char *Paths_Paths[50];
extern int gNumSlices;
extern intptr gWSavePtr;
extern u_int fastRandom;
extern u_int randSeed;
extern u_int randtemp;
extern "C" int stackSpeedUpEnbabledFlag;

/* ---- per-class vtables (data syms; assigned to _vf[31]) ---- */
extern __vtbl_ptr_type Speaker_vtable[];         /* @0x80055dc4 #75 data-mat (defined in speech.cpp) */
extern __vtbl_ptr_type MobileSpeaker_vtable[];   /* @0x80055bd4 #75 data-mat (defined in speech.cpp) */
extern __vtbl_ptr_type DispatchSpeaker_vtable[]; /* @0x80055ccc #75 data-mat (defined in speech.cpp) */

#endif /* SPEECH_EXTERNS_H */
