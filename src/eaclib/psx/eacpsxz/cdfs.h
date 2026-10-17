#ifndef NFSHS_CDFS_H
#define NFSHS_CDFS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*NFSHS_CdCompletion)(int result);

int CD_Open(char *name, int flags, int *handle);
int CD_Close(int handle);
int CD_Stopread(int device);
int CD_Getinfo(int handle, int nameBuffer, int *size);
int CD_Read(int device, int destination, int offset, int length);
unsigned char *readsectorB(void);
void loaddirinfo(int startSector, int numSectors, int maxEntries);
int dircompare(const void *left, const void *right);
void CD_Restore(void);
int CD_Init(int maxOpen, int numEntries, void *buffer, NFSHS_CdCompletion callback);
int CD_Restart(int startSector);
int CD_systaskfunc(int taskArg, int elapsed);
void CD_timerfunc(void);
void CdReadyHandler(unsigned char interrupt, unsigned char *result);

#ifdef __cplusplus
}
#endif

#endif
