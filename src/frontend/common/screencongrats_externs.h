/* frontend/common/screencongrats_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENCONGRATS_EXTERNS_H_
#define _FE_SCREENS_SCREENCONGRATS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
#include "../psx/psxfront.h" /* DrawShapeExtended/CleanupSpinningCarsMenu */

extern "C" extern tfrontEnd frontEnd;
extern tCarManager carManager;
extern tTournamentManager tournamentManager;

extern char congratsSwapFileName[16];
extern char fPermFileNameBuf[16];
extern int kRGBVals[28];
extern "C" char textDefinitions[14][6];
/* (gFE_congratsCarRot is NOT extern: SYM marks it STAT carRotate = DrawBackground-local static) */
extern int R3DCar_aSyncLoading;
extern "C" int showRoomFlag;
extern "C" extern SPEECHINFO ginfo;

/* external methods declared free-form (mgr/mgr2 = the implicit this) */
tCarInfo *GetCarFromID(tCarManager *mgr, short carID);
void GetGarageCar(tCarManager *mgr, short garageNumber, tCarInfo *carInfo, short playerNum);
extern "C"
{
    void GetPinkSlipsCar(tCarManager *mgr, short garageNumber, tCarInfo *carInfo, short playerNum);
}
extern "C"
{
    void GetAwardInformation(tTournamentManager *mgr, tAwardInformation *info);
}
void GetTrophyName(tTournamentManager *mgr, tTourneyInfo *tourn, tTrophySize size, char *buffer, int place);
short PlayerRanking(tTournamentManager *mgr, short pos);

/* game C++ helpers + eaclib */
void AudioCmn_PlayFESFX(int SFXnum);
int CalcFadeVal(int col1, int col2, int amount);
int CalcFadeVal(int col1, int amount); /* 2-arg overload */
extern "C" int ticks;
extern "C"
{
    void CarIO_CleanUpLicense(int player);
}
extern "C"
{
    void CarIO_CreateLicense(char *text, int carType, int player);
}
void DrawCar(tCarInfo *carInfo, short x, short y, float camerax, float cameray, char brightness, bool reflection, u_long rotate, tPlayer player);
extern "C"
{
    void DrawMoney(int x, int y, int numplaces, long number, int colfore, int colback);
}
void ScaleShapeExtended(int index, int flags, int x, int y, int fade, int abr, tDrawShapeExtended *extra);
extern "C"
{
    void FETextRender_FullTextRGB(char *s, short x, short y, int col, char size, short justify);
}
void FETextRender_MenuTextFade(int fade, short index, tMenuTextState st, tMenuTextType ty);
extern "C"
{
    int FETextRender_WordWrapHeight(short width, char *str);
}
extern "C"
{
    void FETextRender_WordWrapText(char *str, PSX_RECT *r, tMenuTextState st, tMenuTextType ty);
}
extern "C"
{
    void FETextRender_WordWrapTextFade(int fade, char *str, PSX_RECT *r, tMenuTextState st, tMenuTextType ty);
}
extern "C"
{
    short FeAudio_AsyncPlaySpeech(int type, int index);
}
extern "C"
{
    void FeTools_FormatMoney(char *string, long amount);
}
extern "C"
{
    char *PlayerName(int player);
}
extern "C"
{
    void SetLicensePlate(void);
}
extern "C"
{
    char *TextSys_Word(int wordnum);
}
extern "C"
{
    int TextSys_WordX(int wordnum);
}
extern "C"
{
    int TextSys_WordY(int wordnum);
}
void trap(int code);

#endif
