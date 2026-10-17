/* link_ida.cpp -- AGGREGATION TU. Module-owned globals resolved via IDA
 * (NFS4-v3-work.i64 / nfs4-f.exe.i64) that were extern-declared but never
 * defined. Zero image -> zero-init typed; nonzero primitive -> byte-exact. */
#include "nfs4_types.h"

int Device_Null(uint32 param);
int Device_Analog(uint32 param);
int Device_PSXPad(uint32 param);
int Device_PSXPadMulti(uint32 param);

extern "C" {

static char Device_nameNull[] = "Null";
static char Device_nameAnalog[] = "Analog";
static char Device_namePad[] = "Pad";
static char Device_nameMulti[] = "Multi";

CarIO_textureInfo CarIO_textureName[51] = { /* @8011e804 612B; pointer targets resolved to image strings */
    {"frnt", "Pfrn", 0}, {"rear", "Prea", 0}, {"side", "Psid", 0},
    {"top1", "Ptp1", 0}, {"top2", "Ptp2", 0}, {"dHiF", "", 1},
    {"dHiR", "", 2}, {"dHiS", "", 3}, {"dTp1", "", 4},
    {"dTop", "", 5}, {"dLoF", "", 1}, {"dLoR", "", 2},
    {"dLoS", "", 3}, {"wndw", "Pwnd", 0}, {"ftdm", "Pftd", 0},
    {"splr", "Pspl", 0}, {"ext2", "Pex2", 0}, {"ext3", "Pex3", 0},
    {"ext4", "Pex4", 0}, {"whl ", "Pwhl", 0}, {"ext1", "", 0},
    {"botm", "", 0}, {"whlI", "", 0}, {"tred", "", 0},
    {"bROf", "", 0}, {"bSOf", "", 0}, {"rvOf", "", 0},
    {"sFOf", "", 0}, {"sROf", "", 0}, {"ltOf", "", 0},
    {"bROn", "", 0}, {"bSOn", "", 0}, {"shdw", "", 0},
    {"sFOn", "", 0}, {"sROn", "", 0}, {"ltOn", "", 0},
    {"dcl1", "", 0}, {"dcl2", "", 0}, {"dcl3", "", 0},
    {"dcl4", "", 0}, {"dcl5", "", 0}, {"dcl6", "", 0},
    {"ins0", "", 0}, {"ins1", "", 0}, {"ins2", "", 0},
    {"ins3", "", 0}, {"ins4", "", 0}, {"ins5", "", 0},
    {"ins6", "", 0}, {"ins7", "", 0}, {"ins8", "", 0},
};
/* MIPS cdfs.obj treats 0x80146CC4 as one context: CD_Init clears 0x83c
 * bytes and every named CD_* datum is an offset from this base. */
unsigned char CD_context[0x83c];                                                /* backing for @80146cc4 */
Input_tDeviceList Device_gDeviceList[5] = {
    {Device_nameNull,   Device_Null,        0},
    {Device_nameAnalog, Device_Analog,      0},
    {Device_namePad,    Device_PSXPad,      0},
    {Device_nameMulti,  Device_PSXPadMulti, 0},
    {0,                 0,                          0}
}; /* @8011ec18 60B */
PAD_COMMON Padglobal[2];                                                         /* @8013e8f0 16B */
int Weather_gLastProcessTime[2];                                                 /* @8013de54 12B */
unsigned int _stacksize = 0x8000;                                                /* @80136cd0 4B */
int asyncfilehandle;                                                             /* @8013deb0 4B */
int debounce[2];                                                                 /* @80052b60 8B */
AnimDef gAnimDefs[14] = {                                                    /* @80115c48 280B */
    {0,  1, -1, 2, 0},
    {1, 10,  0, 0, 1},
    {1, 20,  0, 0, 1},
    {1,  6,  0, 0, 1},
    {1,  2,  0, 0, 1},
    {1,  1,  0, 0, 1},
    {1, 10,  0, 0, 1},
    {1, 14,  0, 0, 1},
    {1,  5,  0, 0, 1},
    {1,  5,  0, 0, 1},
    {1,  1,  0, 0, 1},
    {1,  8,  0, 0, 1},
    {0,  1, -1, 2, 0},
    {0,  1, -1, 2, 0},
};
uint32 hilight_colors[5] = {0x700a00,0x400a00,0x300300,0x180300,0x180300};       /* @8011f4b4 20B */
int hoff[6] = {0x4d,0x1,0x0,0x0,0x0,0x0};                                        /* @8013dac0 24B */
sim_queue inputQueue;                                                            /* @8013e0f4 524B */
static char loading_languageNameStorage[6][8] = {
    "engl", "germ", "fren", "span", "itly", "swed"
};
char *loading_languageNames[6] = {                                               /* @80120d00 24B */
    loading_languageNameStorage[0], loading_languageNameStorage[1],
    loading_languageNameStorage[2], loading_languageNameStorage[3],
    loading_languageNameStorage[4], loading_languageNameStorage[5]
};
long nextTick;                                                                   /* @80051738 4B */
Input_tResults output[2];                                                        /* @8013ddc8 28B */
SystemTaskSlot systemtasksubs[16];                                               /* @8013e980 16 x 16B on PSX */

}
