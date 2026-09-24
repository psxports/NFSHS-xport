/* game/psx/platform.cpp -- RECONSTRUCTED (NFS4 PSX platform memory + system init; C++ TU)
 *   8 fns: Platform_InitMemory (set up bump arena), Platform_ReserveMemory/TempReserveMemory
 *   (bump alloc), Platform_SysStartUp (PSX boot: heap/eaclib/display/FS/timers), nfs2eacinit
 *   (eaclib boot), Platform_DebuggerPollHost (stub), Platform_Reset/GetDCTBuffer (DCT scratch). No GTE.
 */
#include "../../nfs4_types.h"
#include "platform_externs.h"

/* ---- owning-TU defs for link-harness (extern-declared, never defined; BSS) ---- */
#ifdef AP_WIN /* PORTABILITY-REVIEWED: host-owned PSX memory regions */
char *gDctBuffer = (char *)DRAM + 0x124038;
char *gDctXtraMem;
char *gEAMemPoolBase = (char *)DRAM + 0x148b0c;
char *gPlatformInitMem = (char *)DRAM + 0x054d10;
#else
char gDctBuffer[64]; char *gDctXtraMem; char gEAMemPoolBase[64]; char gPlatformInitMem[64];  /* PSX linker-owned regions */
#endif


/* ---- Platform_InitMemory__Fv  [PLATFORM.CPP:125-135] SLD-VERIFIED ---- */
extern "C" void Platform_InitMemory(void)

{
  intptr tempLow;

#ifdef AP_WIN /* PORTABILITY-REVIEWED: host bump-arena address boundary */
  tempLow = (intptr)DRAM + 0x10080;
  gTotalMemory = 0x54d10 - 0x10080;
  gLowMemory = tempLow;
  gHighMemory = (intptr)DRAM + 0x54d10;
  gCurrentMemory = tempLow;
#else
  tempLow = 0x80010080;   /* PSX prog base 0x80010000 + 0x80 EXE-header = low-mem bound; memory-map constant (no data symbol), not a VA to migrate */
  gTotalMemory = (u_int)((intptr)gPlatformInitMem - tempLow);
  gLowMemory = tempLow;
  gHighMemory = (intptr)gPlatformInitMem;
  gCurrentMemory = tempLow;
#endif
  return;
}

/* ---- Platform_ReserveMemory__FiPc  [PLATFORM.CPP:139-156] SLD-VERIFIED ---- */
extern "C" char *Platform_ReserveMemory(int size,char *string)

{
  int alignedSize;
  intptr newmem;
  char *mem;

  alignedSize = size + 3;
  if (alignedSize < 0) {
    alignedSize = size + 6;
  }
  newmem = gCurrentMemory + (alignedSize >> 2) * 4;
  mem = (char *)gCurrentMemory;
  if (newmem - gLowMemory <= (intptr)gTotalMemory) {
    gCurrentMemory = newmem;
    return mem;
  }
  return (char *)0x0;
}

/* ---- Platform_TempReserveMemory__FiPc  [PLATFORM.CPP:161-178] SLD-VERIFIED ---- */
extern "C" char *Platform_TempReserveMemory(int size,char *string)

{
  int alignedSize;
  intptr newmem;
  char *mem;

  alignedSize = size + 3;
  if (alignedSize < 0) {
    alignedSize = size + 6;
  }
  mem = (char *)0x0;
  newmem = gCurrentMemory + (alignedSize >> 2) * 4;
  if (newmem - gLowMemory <= (intptr)gTotalMemory) {
    mem = (char *)gCurrentMemory;
  }
  return mem;
}

/* ---- Platform_SysStartUp__Fv  [PLATFORM.CPP:207-305] SLD-VERIFIED ---- */
extern "C" void Platform_SysStartUp(void)

{
  char *endofcode;

  disablecd = 0;
#ifdef AP_WIN /* PORTABILITY-REVIEWED: separate host EAC heap region */
  endofcode = (char *)DRAM + 0x148b0c;
  /* Native call stacks do not consume the PSX top-of-RAM stack reserve */
  nfs_sysInfo.userRam = PSX_DRAM_SIZE - 0x148b0c;
#else
  endofcode = (char *)gEAMemPoolBase;
  nfs_sysInfo.userRam = (int)((intptr)0x801fc000 - (intptr)endofcode);   /* PSX RAM top (2MB) - 16KB stack reserve */
#endif
  initmemadr(endofcode,nfs_sysInfo.userRam);
  nfs2eacinit();
  Draw_SetEnvironment(0x200,0xf0,1,0,1,0,0,0);
  initlinkmode(0,1,1);
  setdirectory((char *)&gSysStartUp[1]);
  initlinkmode(0,1000,1);
  initlinkmode(0,1000,1);
  gSysStartUp[0] = 1;
  inittimer(0x80);
  Paths_StartUp();
  initasync(0x1e,0x2000,0);
  return;
}

/* ---- Platform_DebuggerPollHost__Fv  [PLATFORM.CPP:326-330] SLD-VERIFIED ---- */
extern "C" void Platform_DebuggerPollHost(void)

{
  return;
}

/* ---- nfs2eacinit__Fv  [PLATFORM.CPP:369-408] SLD-VERIFIED ---- */
void nfs2eacinit(void)

{
  FlushCache();
  ResetCallback();
  ResetGraph(3);   /* @0x800ED670 (libgpu); was mislabeled "Eac_vars" -- delay-slot arg=3 */
  initjoy(2);
  FILE_init(10,800,0x30);
  return;
}

/* ---- Platform_ResetDCTBuffer__Fv  [PLATFORM.CPP:439-440] SLD-VERIFIED ---- */
extern "C" void Platform_ResetDCTBuffer(void)

{
  gDctXtraMem = gDctBuffer;
  return;
}

/* ---- Platform_GetDCTBuffer__FiPc  [PLATFORM.CPP:444-461] SLD-VERIFIED ---- */
extern "C" char * Platform_GetDCTBuffer(int size,char *string)

{
  char *p;
  
  p = gDctXtraMem;
  gDctXtraMem = gDctXtraMem + size;
  return p;
}

/* end of platform.cpp */
