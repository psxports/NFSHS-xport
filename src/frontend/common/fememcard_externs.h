/* frontend/common/fememcard_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_FEMEMCARD_EXTERNS_H_
#define _FE_FEMEMCARD_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* ===== globals ===== */
extern "C" int ticks;
extern "C" extern tfrontEnd frontEnd;
extern tFEApplication *FEApp;
extern "C" extern char *Paths_Paths[];
extern tTrackManager trackManager;
extern tCarManager carManager;
extern tTournamentManager tournamentManager;
extern "C" tPadModuleState gPadinfo;
extern "C" fMemCardInfo_def gMemCardInfo;
extern "C" tScreenMemcard *screenMemcard;
extern "C" int *Stats_gTrackRecords;
extern "C" int gMasterSFXLevel;
/* FEMemCard.obj data globals */
extern int CURRENTPLAYER;               /* @0x80051A68 */
extern char productCode[11];            /* @0x80051A6C */
extern "C" int nomessage;               /* @0x80051A78 */
extern "C" char CURRENTLYUSINGMEMCARD;  /* @0x80051A7C */
extern "C" int MEMCARD_INITIALIZED;     /* @0x80051A80 */
extern int textSysMemCardFail_Index[7]; /* @0x80051A84 */
extern "C" char MEMCARDFRONTENDISINITTED;
static char TITLE[40]; /* STAT @0x80052B68 */

/* ===== vtables (manual) ===== */
extern __vtbl_ptr_type tDialogYesNoMem_vtable[];
extern __vtbl_ptr_type tDialogNoInputMessage_vtable[];

/* ===== dialog ctors/dtors + member fns (rendered free by Ghidra) ===== */
extern "C"
{
    void tScreen_ctor(tScreen *);
}
void tScreen_dtor(tScreen *, int);
void tDialogYesNo_ctor(tDialogYesNo *);
extern "C"
{
    void Display(tDialogBase *);
}
extern "C"
{
    void Hide(tDialogBase *);
}
extern "C"
{
    short Run(tDialogInteractive *);
}
extern "C"
{
    void Redraw(tFEApplication *);
}
void UpdateMusic(tFEApplication *);

/* ===== memcard (PSX::memcard) ===== */
extern "C"
{
    int MCRD_handlecardevents(int);
}
extern "C"
{
    void MCRD_savefile(int, MCRDFILE_def *);
}
extern "C"
{
    void MCRD_loadfile(int, MCRDFILE_def *, int);
}
extern "C"
{
    CARDINFO_def *MCRD_getcard(int);
}
extern "C"
{
    void MCRD_init(int);
}
extern "C"
{
    void MCRD_restore();
}
extern "C"
{
    void MCRD_getopts(MCRDOPTS_def *);
}
extern "C"
{
    void MCRD_setopts(MCRDOPTS_def *);
}

/* ===== eaclib / syslib / game ===== */
void Clock_MasterInterruptHandler();
void timedwait5(int);
extern "C"
{
    void AudioMus_StopSong(int);
}
extern "C"
{
    char *TextSys_Word(int);
}
void *PlayerNameExist(int);
extern "C"
{
    char *PlayerName(int);
}
extern "C"
{
    void FECheat_SaveBonus(u_long *);
}
extern "C"
{
    void FECheat_LoadBonus(u_long *);
}

/* ===== game-manager methods (rendered free by Ghidra; first arg is the manager ptr) ===== */
void SaveTournament(tTournamentManager *, tSaveTournament *);
void RestoreTournament(tTournamentManager *, tSaveTournament *);
void LoadTournament(tTournamentManager *, tSaveTournament *);
void SaveTracks(tTrackManager *, tSaveTrackInfo *);
void LoadTracks(tTrackManager *, tSaveTrackInfo *);
void SaveCars(tCarManager *, tSaveCarInfo *);
void LoadCars(tCarManager *, tSaveCarInfo *, short);
void SavePinkSlipsCars(tCarManager *, tSaveCarInfo *, short); /* overload of FE SavePinkSlipsCars(short,short) */
void LoadPinkSlipsCars(tCarManager *, tSaveCarInfo *, short);
void SetPads();
extern "C"
{
    void Front_ResetPSXController(int, unsigned int);
}

#endif
