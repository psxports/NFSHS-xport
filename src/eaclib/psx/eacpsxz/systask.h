#ifndef NFSHS_SYSTASK_H
#define NFSHS_SYSTASK_H
#include "psx.h"

typedef int (*NFSHS_SystemTask)(int taskArg, int elapsed);

struct SystemTaskSlot
{
    NFSHS_SystemTask callback;
    int period;
    int deadline;
    int busy;
};

extern "C" {
int addsystemtask(NFSHS_SystemTask taskFn, int period, int delay);
intptr delsystemtask(NFSHS_SystemTask taskFn);
unsigned int systemtask(int taskArg);
int asyncsystemtask(int taskArg, int elapsed);
int iSNDsystemtaskreal(int taskArg, int elapsed);
}
#endif
