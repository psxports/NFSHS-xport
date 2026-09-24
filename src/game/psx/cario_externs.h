#include "../../lib/libfns.h"
/* cario_externs.h -- extern decls for game/psx/cario.cpp (NFS4 PSX car texture/CLUT I/O). */
#ifndef CARIO_EXTERNS_H
    #define CARIO_EXTERNS_H

/* ---- libc ---- */

/* ---- harvested from sealed *_externs.h ---- */
extern "C" Draw_tPixMap *CarIO_carPixMap;
extern "C" extern GameSetup_tData GameSetup_gData;
extern Texture_pal8bit *Texture_palCopy; /* 0x8013db0c */
extern int Texture_palNum;               /* 0x8013db10 */
extern "C" extern int R3DCar_InMenu;
/* generic shape-data ptr (int, char, void ptr) */
extern void Texture_MenuReleaseClutId(short id);
extern void ChangeTPage(u_short *tpage, int abr);

/* ---- SYM Globals + free fns ---- */
extern "C"
{
    extern void Texture_LoadPmx(char *, char *, int, int, int, int, int, Draw_tPixMap *);
}
extern void Texture_ResetPaletteSharing(void);

/* ---- CarIO.obj own globals (SYM dims known; element widths from cpp reads/casts) ---- */
extern "C" CarIO_textureInfo CarIO_textureName[51]; /* dims 1 51; pCVar->pal/palShare/tex */
extern "C" short CarIO_carVRamSlots[18][2];         /* [c][0/1] -> short sVar / (int) cast */
extern "C" short CarIO_carVRamSlotsMenu[6][2];      /* short */
extern "C" short CarIO_carVRamAdd[6];               /* SYM: short[6], 12 bytes @8011EAC8 */
extern "C" short CarIO_carVRamOffset[6];            /* (int) cast => short */
extern "C" short CarIO_licensePlate[22][6];         /* [c][0..2] short (id+coords) */
extern "C" short CarIO_licenseSFX_Vram[12][2];      /* short vram coords */
extern "C" shapetbl *CarIO_Plate1[2];               /* = (shapetbl*)0 */
extern "C" shapetbl *CarIO_Plate2[2];
extern "C" int CarIO_carPixMapCount;
extern "C" int CarIO_carVRamCount;
extern "C" int CarIO_licenseSFX_Count;
extern char *R3DCar_LicenseShapeFile; /* MIPS loads the pointer value before locateshapez */

#endif
