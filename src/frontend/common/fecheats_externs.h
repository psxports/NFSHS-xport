/* frontend/common/fecheats_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_FECHEATS_EXTERNS_H_
#define _FE_SCREENS_FECHEATS_EXTERNS_H_
#include "../../nfs4_types.h"

/* ===== globals ===== */
extern "C" unsigned int gFECheats;
extern "C" unsigned int gFEBonus;
extern tFEApplication *FEApp;
extern tCarManager carManager;
extern tTrackManager trackManager;
extern tTournamentManager tournamentManager;
extern "C" tRecordBuffer *Stats_gTrackRecords;

/* ===== helpers ===== */
void AudioCmn_PlayFESFX(int sfx);
extern "C"
{
    char *TextSys_Word(int id);
}
extern "C"
{
    void Stattool_GetAllDefaultRecords(tRecordBuffer *buf, bool def);
}

/* same-TU forward decls */
void FECheat_HandleActivation(tCheatCode cheat);
void FECheat_EncodeString(char *input, char *output);
void FECheat_EncodeString2(char *input, char *output);
extern "C"
{
    void FECheat_ActivateBonus(tCheatCode cheat);
}

#endif
