/* link_defs.cpp -- AGGREGATION TU: storage definitions for module-owned globals
 * that were declared `extern` (a promise) but never given a home in any TU.
 * Surfaced by the whole-tree LINK harness (link_harness.py). All BSS (zero-init);
 * types taken from each symbol's extern decl; buffer-bases sized to the SYM v3
 * object size. Stage 1 of self-containment (nfs4-f.exe not needed to link). */
#include "nfs4_types.h"

extern "C" {

/* ---- Stage 1: 34 BSS-zero (.bss/.sbss/front.bss) ---- */
int gDataRate;                                             /* @80148434 4B */
intptr gEventDats[4];                                    /* PSX @80148048: four pointer words */
int gFilterSetting;                                        /* @8014842c 4B */
int gGameNum;                                              /* @80148428 4B */
unsigned short gLastSubTick;                               /* @80148430 2B */
int gLastTick;                                             /* @80148438 4B */
fMemCardInfo_def gMemCardInfo;                             /* @80052d68 6112B */
tPadModuleState gPadinfo;                                  /* @8013e89c 84B */
int gPreLoadTicks;                                         /* @80148044 4B */
SPCHChosenSentence NFSHS_gSentenceChoice_storage;           /* backing for @8014843c */
#ifdef AP_WIN
unsigned char NFSHS_gVoxEvents_storage[968];               /* backing for @80148060 */
#else
int gVoxEvents;                                            /* @80148060 */
#endif
#ifdef AP_WIN
unsigned char NFSHS_gVoxInGame_storage[8];                 /* backing for @80148058 */
#else
int gVoxInGame;                                            /* @80148058 */
#endif
short ispch_gChoice[72];                                   /* @801484e4 144B */
unsigned char ispch_gPickSamples[100];                     /* @8014847c 100B */
int maxot;                                                 /* @8013de7c 4B */
int maxprim;                                               /* @8013de8c 4B */
short mutexbuf[64];                                        /* @801477e0 128B */
char * nextprim;                                           /* @8013de78 4B */
char * otbl;                                               /* @8013de70 8B */
int oti;                                                   /* @8013de68 4B */
int otp;                                                   /* @8013de6c 4B */
char * primbase;                                           /* @8013de84 8B */
char * primptr;                                            /* @8013de80 4B */
int reentryflag;                                           /* @8013dec0 4B */
unsigned char sndchanreserved[4];                          /* @80147914 4B */
int sndgs[47];   /* @80147860 : sized to full SndState 0xBC=188B (47*4); SND casts this */
/* gSndState: EA/engine semantic alias for the SndState block; SAME object as sndgs @0x80147860
 *   (snd.h: #define SND ((SndState*)gSndState)).  Aliased so both names resolve to one buffer.
 *   gcc2.7.2/ccpsx has no __attribute__((alias)); keep for the modern pre-gate, resolve the
 *   gSndState symbol bridge in the deferred linkage/hygiene pass. */
#ifndef NFS4_PSYQ_HEADERS
/* gSndState removed: snd.h SND macro now casts sndgs directly (ccpsx ignores alias attr). */
#endif
/* CF_DVLC @0x80123838-region NAME COLLISION NOTE: the game-side CF_DVLC is a 49096-byte BSS
 *   load/overlay buffer (asyncloadfileat target; speech-bank-pool overlay), NOT the MDEC table.
 *   psxfront/video/nfs3/draww take its address; zero-init BSS is faithful. */
unsigned char CF_DVLC[];                            /* @BSS : 49096B load buffer */
#ifdef AP_WIN
unsigned char NFSHS_sndmm_storage[588];                    /* backing for @80148780 */
unsigned char NFSHS_sndpd_storage[1836];                   /* backing for @80147918 */
#else
int sndmm;                                                 /* @80148780 */
unsigned char sndpd;                                       /* @80147918 */
#endif
int sndpp;                                                 /* @80148578 4B */
intptr sndpps[1];                                        /* @80148574 pointer slot */
#ifdef AP_WIN
unsigned char NFSHS_snd_stream_registry_storage[8];        /* sndss @+0, sndStreamMap @+4 */
#else
intptr sndss[1];                                         /* @8013ea80 pointer slot */
signed char sndStreamMap[4];                               /* @8013ea84 4B */
#endif
int timerevent;                                            /* @8013dec4 4B */

}
