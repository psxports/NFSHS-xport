#include "../nfs4_types.h"

extern "C" {
u_char *&Render_gPalettePtr = *(u_char **)((u_char *)SCRATCHPAD + 0x000);
u_char *&Render_gPacketPtr = *(u_char **)((u_char *)SCRATCHPAD + 0x004);
char *&Render_gPacketEnd = *(char **)((u_char *)SCRATCHPAD + 0x008);
int &Render_gMenuRenderFlag = *(int *)((u_char *)SCRATCHPAD + 0x00c);
short &Render_gPacketLenLo = *(short *)((u_char *)SCRATCHPAD + 0x010);
short &Render_gPacketLenHi = *(short *)((u_char *)SCRATCHPAD + 0x012);
MATRIX &Render_gWorldMat = *(MATRIX *)((u_char *)SCRATCHPAD + 0x014);
MATRIX &Render_gNightMat = *(MATRIX *)((u_char *)SCRATCHPAD + 0x034);
MATRIX &Render_gCopMat = *(MATRIX *)((u_char *)SCRATCHPAD + 0x054);
int &INT_1f800084 = *(int *)((u_char *)SCRATCHPAD + 0x084);
int &INT_1f800088 = *(int *)((u_char *)SCRATCHPAD + 0x088);
int &INT_1f80008c = *(int *)((u_char *)SCRATCHPAD + 0x08c);
int &INT_1f800090 = *(int *)((u_char *)SCRATCHPAD + 0x090);
int &Skid_gCtrlScratch_94 = *(int *)((u_char *)SCRATCHPAD + 0x094);
int &Skid_gCtrlScratch_98 = *(int *)((u_char *)SCRATCHPAD + 0x098);
int &gScratchLastWord = *(int *)((u_char *)SCRATCHPAD + 0x3fc);
}

extern "C" {
extern unsigned char CD_context[0x83c];
extern SPCHChosenSentence NFSHS_gSentenceChoice_storage;
extern unsigned char NFSHS_gVoxEvents_storage[968];
extern unsigned char NFSHS_gVoxInGame_storage[8];
extern unsigned char NFSHS_sndmm_storage[588];
extern unsigned char NFSHS_sndpd_storage[1836];
extern unsigned char NFSHS_snd_stream_registry_storage[8];

int &Cdinfo = *(int *)(CD_context + 0x00);
int &CD_maxOpen = *(int *)(CD_context + 0x04);
int &CD_dirEntryCount = *(int *)(CD_context + 0x08);
int &CD_cachedSector = *(int *)(CD_context + 0x0c);
int &CD_lastSector = *(int *)(CD_context + 0x10);
int &CD_curSector = *(int *)(CD_context + 0x14);
int &CD_timeout = *(int *)(CD_context + 0x18);
int &CD_ringIdx = *(int *)(CD_context + 0x1c);
int &CD_curLen = *(int *)(CD_context + 0x20);
int &CD_remLen = *(int *)(CD_context + 0x24);
int &CD_curOff = *(int *)(CD_context + 0x28);
void *&CD_curDst = *(void **)(CD_context + 0x2c);
void (*&CD_completionCallback)(int) = *(void (**)(int))(CD_context + 0x30);
void **&CD_handleTable = *(void ***)(CD_context + 0x34);
void *&CD_dirEntryArray = *(void **)(CD_context + 0x38);
unsigned char (&CD_sectorCache)[0x800] = *(unsigned char (*)[0x800])(CD_context + 0x3c);

intptr (&sndss)[1] = *(intptr (*)[1])NFSHS_snd_stream_registry_storage;
signed char (&sndStreamMap)[4] = *(signed char (*)[4])(NFSHS_snd_stream_registry_storage + 4);
int &gVoxInGame = *(int *)(NFSHS_gVoxInGame_storage + 0);
int &gRepeatCount = *(int *)(NFSHS_gVoxInGame_storage + 4);
int &gVoxEvents = *(int *)(NFSHS_gVoxEvents_storage + 0);
int &DAT_80148064 = *(int *)(NFSHS_gVoxEvents_storage + 4);
SPCHChosenSentence &gSentenceChoice = NFSHS_gSentenceChoice_storage;
int &DAT_80148440 = *(int *)((unsigned char *)&NFSHS_gSentenceChoice_storage + 4);
int &DAT_80148444 = *(int *)((unsigned char *)&NFSHS_gSentenceChoice_storage + 8);
int &DAT_80148448 = *(int *)((unsigned char *)&NFSHS_gSentenceChoice_storage + 12);
int &DAT_8014844c = *(int *)((unsigned char *)&NFSHS_gSentenceChoice_storage + 16);

int &sndmm = *(int *)(NFSHS_sndmm_storage + 0);
short &DAT_80148784 = *(short *)(NFSHS_sndmm_storage + 4);
short &DAT_80148786 = *(short *)(NFSHS_sndmm_storage + 6);
int &DAT_80148788 = *(int *)(NFSHS_sndmm_storage + 8);
unsigned short &DAT_8014878c = *(unsigned short *)(NFSHS_sndmm_storage + 12);

unsigned char &sndpd = *(unsigned char *)(NFSHS_sndpd_storage + 0x000);
unsigned char &DAT_80147919 = *(unsigned char *)(NFSHS_sndpd_storage + 0x001);
int &DAT_8014791c = *(int *)(NFSHS_sndpd_storage + 0x004);
int &DAT_80147920 = *(int *)(NFSHS_sndpd_storage + 0x008);
signed char &DAT_80147924 = *(signed char *)(NFSHS_sndpd_storage + 0x00c);
char &DAT_80147925 = *(char *)(NFSHS_sndpd_storage + 0x00d);
char &DAT_80147926 = *(char *)(NFSHS_sndpd_storage + 0x00e);
int &DAT_80147928 = *(int *)(NFSHS_sndpd_storage + 0x010);
int &DAT_8014792c = *(int *)(NFSHS_sndpd_storage + 0x014);
unsigned short &DAT_80147930 = *(unsigned short *)(NFSHS_sndpd_storage + 0x018);
unsigned char &DAT_80147932 = *(unsigned char *)(NFSHS_sndpd_storage + 0x01a);
unsigned char &DAT_80147934 = *(unsigned char *)(NFSHS_sndpd_storage + 0x01c);
int &DAT_80147938 = *(int *)(NFSHS_sndpd_storage + 0x020);
unsigned char &DAT_801479f0 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0d8);
unsigned char &DAT_801479f4 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0dc);
int &DAT_801479f8 = *(int *)(NFSHS_sndpd_storage + 0x0e0);
unsigned char &DAT_801479fc = *(unsigned char *)(NFSHS_sndpd_storage + 0x0e4);
unsigned char &DAT_80147a00 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0e8);
unsigned char &DAT_80147a04 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0ec);
unsigned char &DAT_80147a08 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f0);
unsigned char &DAT_80147a0a = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f2);
unsigned char &DAT_80147a0c = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f4);
unsigned char &DAT_80147a0d = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f5);
unsigned char &DAT_80147a0e = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f6);
unsigned char &DAT_80147a0f = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f7);
unsigned char &DAT_80147a10 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f8);
unsigned char &DAT_80147a11 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0f9);
unsigned char &DAT_80147a12 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0fa);
unsigned char &DAT_80147a13 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0fb);
unsigned char &DAT_80147a14 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0fc);
unsigned char &DAT_80147a15 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0fd);
unsigned char &DAT_80147a16 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0fe);
unsigned char &DAT_80147a17 = *(unsigned char *)(NFSHS_sndpd_storage + 0x0ff);
unsigned char &DAT_80147a18 = *(unsigned char *)(NFSHS_sndpd_storage + 0x100);
intptr &DAT_80147e10 = *(intptr *)(NFSHS_sndpd_storage + 0x4f8);
unsigned int *&DAT_80147e14 = *(unsigned int **)(NFSHS_sndpd_storage + 0x4fc);
unsigned int *&DAT_80147e18 = *(unsigned int **)(NFSHS_sndpd_storage + 0x500);
unsigned int *&DAT_80147e1c = *(unsigned int **)(NFSHS_sndpd_storage + 0x504);
unsigned int *&DAT_80147e20 = *(unsigned int **)(NFSHS_sndpd_storage + 0x508);
unsigned int *&DAT_80147e24 = *(unsigned int **)(NFSHS_sndpd_storage + 0x50c);
int &DAT_80147e28 = *(int *)(NFSHS_sndpd_storage + 0x510);
int &DAT_80147e2c = *(int *)(NFSHS_sndpd_storage + 0x514);
unsigned short &DAT_80147e38 = *(unsigned short *)(NFSHS_sndpd_storage + 0x520);

}
