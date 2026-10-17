/* eaclib/psx/eacpsxz/systask.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 3/3 ***
 *   Source obj : nfs4\eaclib\psx\systask.obj ; archive C:\nfs4\EACLIB\PSX\EACPSXZ.LIB (xlsx col12 / SYM v3)
 *   3 fns @[0x800E6AF4 .. 0x800E6C04].  A 16-slot periodic system-task scheduler driven by libticks.
 *   Ghidra nfs4-f.exe.c (systask) + IDA sigs.  Slot = 4 ints {fn, period, deadline, busy} (the Ghidra
 *   DAT_8013e984/988/98c are systemtasksubs+1/+2/+3, folded into the one array here).
 */

#include "../../../nfs4_types.h"

/* ---- owning-TU defs for link-harness (extern-declared, never defined; BSS) ---- */
extern "C"
{
    int gSysTaskCount;
    int gSysTaskLastTick;
}
extern "C" int libticks; /* free-running tick counter */
extern "C" int ticks;    /* game/frontend frame clock */
extern "C" void NFSHS_HostPumpTimers(void);
extern "C" int gSysTaskCount;    /* live task count */
extern "C" int gSysTaskLastTick; /* last tick the task list ran */
extern "C" SystemTaskSlot systemtasksubs[16];


/* addsystemtask @0x800E6AF4 : register a periodic task (or update its slot); returns the running count. */
extern "C" int addsystemtask(NFSHS_SystemTask taskFn, int period, int delay)
{
    int activeAdds = gSysTaskCount;
    int selected = -1;
    gSysTaskCount = (int)((uint32)activeAdds + 1u);
    for (int i = 0; i < 0x10; ++i)
    {
        SystemTaskSlot *slot = &systemtasksubs[i];
        if (slot->callback == taskFn)
        {
            selected = i;
        }
        else if (slot->callback == 0 && selected == -1)
        {
            if (activeAdds == 0)
                selected = i;
            else
                activeAdds = (int)((uint32)activeAdds - 1u);
        }
    }
    if (selected != -1)
    {
        SystemTaskSlot *slot = &systemtasksubs[selected];
        slot->callback = taskFn;
        slot->period = period;
        slot->busy = 0;
        slot->deadline = (int)((uint32)libticks + (uint32)delay);
    }
    gSysTaskCount = (int)((uint32)gSysTaskCount - 1u);
    return gSysTaskCount;
}

/* delsystemtask @0x800E6BA8 : remove the task whose fn matches; returns the cleared fn (or end-marker). */
extern "C" intptr delsystemtask(NFSHS_SystemTask fn)
{
    for (int i = 0; i < 0x10; ++i)
    {
        if (systemtasksubs[i].callback == fn)
        {
            systemtasksubs[i].callback = 0;
            return (intptr)fn;
        }
    }
    return 0x100;
}

/* systemtask @0x800E6C04 : once per tick, run every due task (fn(arg1, elapsed)) and re-arm it; OR of returns. */
extern "C" unsigned int systemtask(int arg1)
{
    unsigned int result = 0;
    /* The native runtime is single-threaded. Pump the reconstructed 128 Hz
       root counter from the host monotonic clock. */
    NFSHS_HostPumpTimers();
    if (gSysTaskLastTick != libticks)
    {
        gSysTaskLastTick = libticks;
        for (int i = 0; i < 0x10; ++i)
        {
            SystemTaskSlot *slot = &systemtasksubs[i];
            if (slot->callback != 0 && slot->deadline <= libticks && slot->busy == 0)
            {
                unsigned int r;
                int t;
                slot->busy = 1;
                r = (unsigned int)slot->callback(arg1, (int)((uint32)libticks - (uint32)slot->deadline));
                t = libticks;
                result |= r;
                slot->busy = 0;
                slot->deadline = (int)((uint32)t + (uint32)slot->period);
            }
        }
    }
    return result;
}
