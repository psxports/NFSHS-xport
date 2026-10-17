#ifndef NFSHS_FILEROOT_H
#define NFSHS_FILEROOT_H
#include <stddef.h>

/* Game-owned deferred PC read command, five 32-bit fields */
struct ReadCmd
{
    int pending;
    int handle;
    int dest;
    int offset;
    int len;
};

static_assert(sizeof(ReadCmd) == 20 && offsetof(ReadCmd, pending) == 0 &&
              offsetof(ReadCmd, handle) == 4 && offsetof(ReadCmd, dest) == 8 &&
              offsetof(ReadCmd, offset) == 12 && offsetof(ReadCmd, len) == 16,
              "Deferred read command must retain the original five-word layout");

extern ReadCmd readcmd;

extern "C" {
int readfile_systask(int taskArg, int elapsed);
int writefile(int handle, int buf, int offset, int len);
}

#endif
