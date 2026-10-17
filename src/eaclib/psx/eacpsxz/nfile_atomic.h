#ifndef NFSHS_NFILE_ATOMIC_H
#define NFSHS_NFILE_ATOMIC_H

#include "psx.h"

typedef intptr (*NFSHS_FileAtomic)(int retry, void *args);

extern "C" {
intptr FILE_atomic(NFSHS_FileAtomic fn, int idle, int retries, void *args);
intptr filesizeatomic(int retry, void *args);
intptr loadfileadratomic(int retry, void *args);
intptr loadfileatadratomic(int retry, void *args);
intptr loadbigfileheaderatomic(int retry, void *args);
}

#endif
