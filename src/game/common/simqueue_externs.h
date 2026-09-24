/* simqueue_externs.h -- extern decls for game/psx/simqueue.cpp (NFS4 PSX sim input queue). */
#ifndef SIMQUEUE_EXTERNS_H
#define SIMQUEUE_EXTERNS_H

/* ---- harvested + SYM ---- */
extern "C" extern GameSetup_tData GameSetup_gData;

extern "C" sim_queue inputQueue;     /* Validity/Buffer/TailTime */
extern "C" Input_tResults output[2]; /* per-player current input */
extern "C" int gSimQueue_BlockOther;
extern "C" int gSimQueue_BlockSelf;
extern "C" int gSimQueue_Ticker;
extern int maxTicksPerFrame;

#endif
