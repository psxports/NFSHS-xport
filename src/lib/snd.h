/* lib/snd.h -- EA "SND" sound-runtime shared types & API (struct-first SND pass, 2026-06-10).
 *   Reconstructed from nfs4-f.exe (disasm-v3 field-access sweeps). NOT original source.
 *   Single source of truth for the SND objs (SNDPSXZ.LIB) so they stop re-deriving offsets.
 *   Structs are BYTE-EXACT in size; key fields named, gaps padded, full offset map in comments.
 *   Some voice fields are accessed as both int and (its high) short -> treat as union-ish; the
 *   .cpp files use offset casts where the asm overlaps.  Grow this header as objs are reconstructed.
 */
#ifndef LIB_SND_H
#define LIB_SND_H

#include "../nfs4_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* ---- one playing voice/channel : 0x64 (100) bytes, table at SndState.voices ---- */
    typedef struct SndVoice
    {                        /* offset map from the field-access sweep            */
        int handle;          /* +0x00 voice handle/key (also read as u8/s8)                   */
        int f04;             /* +0x04                                                          */
        char _g08[2];        /* +0x08                                                          */
        signed char bank;    /* +0x0A owning sample bank                                       */
        signed char f0B;     /* +0x0B                                                          */
        unsigned char f0C;   /* +0x0C                                                          */
        char _g0D[3];        /* +0x0D                                                          */
        int f10;             /* +0x10                                                          */
        int f14;             /* +0x14                                                          */
        int f18;             /* +0x18                                                          */
        int f1C;             /* +0x1C (high half also read as short @+0x1E)                    */
        int f20;             /* +0x20                                                          */
        int f24;             /* +0x24 (high half also read as short @+0x26)                    */
        int f28;             /* +0x28                                                          */
        signed char f2C;     /* +0x2C                                                          */
        signed char vol_l;   /* +0x2D base volume (left)                                       */
        signed char pan;     /* +0x2E base pan                                                 */
        signed char f2F;     /* +0x2F                                                          */
        signed char f30;     /* +0x30                                                          */
        unsigned char f31;   /* +0x31                                                          */
        char f32;            /* +0x32                                                          */
        signed char f33;     /* +0x33                                                          */
        signed char f34;     /* +0x34                                                          */
        signed char f35;     /* +0x35                                                          */
        char f36;            /* +0x36                                                          */
        unsigned char f37;   /* +0x37                                                          */
        unsigned char f38;   /* +0x38                                                          */
        unsigned char f39;   /* +0x39                                                          */
        unsigned char f3A;   /* +0x3A                                                          */
        unsigned char f3B;   /* +0x3B                                                          */
        signed char f3C;     /* +0x3C                                                          */
        signed char pan_cur; /* +0x3D current pan                                              */
        char _g3E[2];        /* +0x3E                                                          */
        intptr f40;          /* +0x40 pitch-sweep table pointer                               */
        intptr f44;          /* +0x44 final-volume curve pointer                              */
        intptr pancurve;     /* +0x48 pan curve pointer (or 0)                                */
        intptr f4C;          /* +0x4C pointer-bearing voice field                             */
        intptr f50;          /* +0x50 velocity-envelope pointer                              */
        intptr f54;          /* +0x54 pitch-LFO pointer                                      */
        char _g58[2];        /* +0x58                                                          */
        short f5A;           /* +0x5A                                                          */
        short f5C;           /* +0x5C                                                          */
        short f5E;           /* +0x5E                                                          */
        unsigned short f60;  /* +0x60                                                          */
        unsigned short f62;  /* +0x62                                                          */
    } SndVoice;              /* 0x64                                                           */

    /* ---- one sample bank : 0x0C (12) bytes, table at SndState.banks ---- */
    typedef struct SndBank
    {
        void *datablk;       /* +0x00 sample header / data block                              */
        void *platblk;       /* +0x04 platform (SPU) block                                    */
        unsigned char f08;   /* +0x08                                                          */
        unsigned char inuse; /* +0x09 platform block allocated                                */
        signed char f0A;     /* +0x0A                                                          */
        char f0B;            /* +0x0B                                                          */
    } SndBank;               /* 0x0C                                                           */

    /* ---- one reverb/effect bus : 0x10 (16) bytes, array at SndState.fxbus (SND+0x9C) ---- */
    typedef struct SndFxBus
    {
        int type;   /* +0x00 fx type/mode (0 == off)                                 */
        int master; /* +0x04 master level                                            */
        int depth;  /* +0x08                                                          */
        int delay;  /* +0x0C                                                          */
    } SndFxBus;     /* 0x10                                                           */

    /* ---- one-shot play descriptor : 0x14 (20) bytes (see SNDplaysetdef) ---- */
    typedef struct SndPlayDef
    {
        int handle;        /* +0x00 = -1                                                     */
        signed char f04;   /* +0x04 = -1                                                     */
        signed char decay; /* +0x05 = 0x3C                                                   */
        signed char vol0;  /* +0x06 = 0x7F                                                   */
        signed char pan0;  /* +0x07 = 0x40                                                   */
        signed char vol1;  /* +0x08 = 0x7F                                                   */
        signed char pan1;  /* +0x09 = 0x40                                                   */
        signed char vol2;  /* +0x0A = 0x7F                                                   */
        signed char f0B;   /* +0x0B = 0                                                      */
        short pitch0;      /* +0x0C = 0x1000                                                 */
        short pitch1;      /* +0x0E = 0x1000                                                 */
        short f10;         /* +0x10 = 0                                                      */
        short f12;         /* +0x12 = 0                                                      */
    } SndPlayDef;          /* 0x14                                                           */

    /* Tagged-patch timbre record assembled by stagpat: 0x98 on PSX/Win32. */
    typedef struct SndTimbre
    {
        int f00, velMin, velMax, noteMin, noteMax;       /* +0x00..+0x10 */
        int priority, allocFlags, baseNote;              /* +0x14..+0x1C */
        int noteLimit, segmentCount, duration, channels; /* +0x20..+0x2C */
        int detune, detuneRandom, pan, panRandom;        /* +0x30..+0x3C */
        int pitchBase, pitchRandom;                      /* +0x40,+0x44 */
        intptr finalCurve;                               /* +0x48 */
        int volumeScale, f50;                            /* +0x4C,+0x50 */
        intptr panCurve;                                 /* +0x54 */
        int f58;
        intptr f5C; /* +0x5C */
        int f60;
        intptr sweepTable;                                /* +0x64 */
        int f68, f6C, sweepBase;                          /* +0x68..+0x70 */
        intptr velocityEnvelope;                          /* +0x74 */
        int velocityPeriod, velocityRandomPhase;          /* +0x78,+0x7C */
        intptr pitchLfo;                                  /* +0x80 */
        int pitchPeriod, pitchLfoStart, pitchRandomPhase; /* +0x84..+0x8C */
        int patchFlag, active;                            /* +0x90,+0x94 */
    } SndTimbre;

    /* ---- PSX packet-stream platform context : 0x50 bytes on PSX/Win32 ----
 * Pointer-bearing words use intptr directly.  Integer SPU-local addresses
 * remain int because they are offsets in the PSX SPU address space, not host
 * pointers.  Named fields remove the decompiler's int base + byte offsets. */
    typedef struct SndPacketContext
    {
        int spuAddr;                   /* +0x00 SPU-local byte address                            */
        int spuSize;                   /* +0x04                                                   */
        int bufferBytes;               /* +0x08                                                   */
        int totalBytes;                /* +0x0C                                                   */
        int refillThreshold;           /* +0x10                                                   */
        int writePos;                  /* +0x14                                                   */
        int readPos;                   /* +0x18                                                   */
        int servedPos;                 /* +0x1C                                                   */
        int dmaHandle;                 /* +0x20                                                   */
        intptr packetData[2];          /* +0x24,+0x28 main-RAM packet cursors                     */
        intptr frameSizeTable;         /* +0x2C unsigned-short table                              */
        short frameBytes;              /* +0x30                                                   */
        short packetOffset;            /* +0x32                                                   */
        short packetRemaining;         /* +0x34                                                   */
        short completionPasses;        /* +0x36                                                   */
        unsigned short chunkCount;     /* +0x38                                                   */
        short currentChunk;            /* +0x3A                                                   */
        short chunkRemaining;          /* +0x3C                                                   */
        short chunkOffset;             /* +0x3E                                                   */
        unsigned short blockFrames;    /* +0x40                                                   */
        signed char activeNote;        /* +0x42, -1 when idle                                     */
        unsigned char bufferShift;     /* +0x43                                                   */
        unsigned short blockBytes;     /* +0x44                                                   */
        unsigned short framesPerBlock; /* +0x46                                                 */
        intptr channelBuffers[2];      /* +0x48,+0x4C main-RAM staging buffers                    */
    } SndPacketContext;                /* 0x50 on PSX/Win32                                       */

    /* Packet-voice state table entry @sndpd+0xD8, exact 0x2C stride. */
    typedef struct SndPacketVoice
    {
        int spuAddr;             /* +0x00 */
        int f04;                 /* +0x04 */
        int f08;                 /* +0x08 */
        int bytePos;             /* +0x0C */
        int servedPos;           /* +0x10 */
        int loopBytes;           /* +0x14 */
        unsigned short volAngle; /* +0x18 */
        short pitch;             /* +0x1A */
        unsigned char playState; /* +0x1C */
        unsigned char f1D;       /* +0x1D */
        unsigned char route;     /* +0x1E */
        unsigned char channels;  /* +0x1F */
        signed char link;        /* +0x20 */
        unsigned char linkFlag;  /* +0x21 */
        unsigned char level;     /* +0x22 */
        unsigned char fxLevel;   /* +0x23 */
        unsigned char f24, f25, f26;
        signed char player; /* +0x27, -1 when inactive */
        int f28;            /* +0x28 */
    } SndPacketVoice;       /* 0x2C */

    /* One queued streaming-audio request.  Every member is numeric state or a
 * STREAM request id; there are no native pointers in this fixed 0x2C record. */
    typedef struct SndStreamRequest
    {
        unsigned int streamRequest; /* +0x00 STREAM queue result / request id                  */
        unsigned int id;            /* +0x04 public request id (counter | stream slot)          */
        int submitOverflow;         /* +0x08 first submitted packet handle                     */
        int submitHandle;           /* +0x0C latest submitted packet handle                    */
        int dataRate;               /* +0x10 bytes/second                                       */
        int consumed;               /* +0x14 bytes played                                       */
        int totalSize;              /* +0x18 rounded total bytes                               */
        int remaining;              /* +0x1C submitted bytes not yet played                    */
        int submitted;              /* +0x20 submitted chunk count                             */
        int numChunks;              /* +0x24 total chunk count                                 */
        short name;                 /* +0x28 caller tag                                         */
        short pad2A;                /* +0x2A                                                    */
    } SndStreamRequest;             /* 0x2C on every target                                    */

    /* One EA SCxl streaming-audio state.  Retail accesses exactly 0x60 bytes.
 * Only requests is a CPU pointer; STREAM/SNDPKTPLAY values are integer
 * handles.  Named access lets that pointer widen on a future x64 host without
 * pretending that the rest of the PSX words are addresses. */
    typedef struct SndStreamState
    {
        SndStreamRequest *requests; /* +0x00 on PSX/Win32                                      */
        intptr streamHandle;        /* +0x04 STREAM object pointer on PSX/Win32                 */
        int playResult;             /* +0x08 SNDPKTPLAY_start result (-1 idle)                 */
        int packetPlayer;           /* +0x0C SNDPKTPLAY handle                                 */
        int requestCounter;         /* +0x10 increments by 0x100                               */
        unsigned char state;        /* +0x14 0 idle, 1 playing, 2 restart                      */
        signed char maxRequests;    /* +0x15                                                    */
        signed char requestCount;   /* +0x16                                                    */
        signed char parseIndex;     /* +0x17                                                    */
        unsigned char external;     /* +0x18 external STREAM handle                            */
        unsigned char pad19[3];
        int lockedRate;                    /* +0x1C                                                    */
        int currentRate;                   /* +0x20                                                    */
        unsigned char lockedHeader[0x14];  /* +0x24                                             */
        unsigned char currentHeader[0x14]; /* +0x38                                             */
        int params[5];                     /* +0x4C..+0x5C                                            */
    } SndStreamState;                      /* 0x60 on PSX/Win32                                       */

    typedef void (*SndPacketReleaseCallback)(intptr sample);
    typedef void (*SndPacketNotifyCallback)(int player, unsigned int bytes);

    typedef struct SndPacketFrame
    {
        int sequence;
        int size;
        intptr sample[4];
    } SndPacketFrame; /* 0x18 on PSX/Win32                                       */

    typedef struct SndPacketPlayer
    {
        int voice;
        int sequence;
        short ringSize;
        short readIndex;
        short lastChannel;
        short outstanding;
        int bytesPending;
        int bytesConsumed;
        intptr memoryBase;
        SndPacketReleaseCallback release;
        SndPacketNotifyCallback notify;
        int rateWord;
        /* SndPacketFrame ring[] begins immediately here (+0x28 on PSX/Win32).
     * One additional frame-sized reserve follows the logical ring, matching
     * retail's 0x40 fixed overhead. */
    } SndPacketPlayer;

    /* ---- SND core state @0x80147860 : >= 0xB4 bytes ---- */
    typedef struct SndState
    {
        char _g00[2];                      /* +0x00                                                          */
        short f02;                         /* +0x02                                                          */
        char f04, f05, f06, f07, f08, f09; /* +0x04..0x09                                    */
        char _g0A[2];                      /* +0x0A                                                          */
        unsigned short bankcount;          /* +0x0C number of sample banks                   */
        short f0E;                         /* +0x0E                                                          */
        char f10;                          /* +0x10                                                          */
        unsigned char patchcount;          /* +0x11 voices per bank scan                     */
        char f12, f13, f14;                /* +0x12..0x14                                                    */
        char _g15[0x3C - 0x15];            /* +0x15..0x3B                                    */
        signed char enabled;               /* +0x3C sound system enabled                                     */
        signed char f3D;                   /* +0x3D                                                          */
        unsigned char f3E, f3F, f40, f41;  /* +0x3E..0x41                                    */
        char _g42[2];                      /* +0x42                                                          */
        int f44;                           /* +0x44 100 Hz audio tick                                       */
        void (*server100Hz)(void);         /* +0x48 main tick callback                       */
        void (*clients100Hz[12])(void);    /* +0x4C..0x7B registered callbacks               */
        int f7C, f80, f84, f88, f8C, f90;  /* +0x7C..0x90                                    */
        SndVoice *voices;                  /* +0x94 voice table                                              */
        SndBank *banks;                    /* +0x98 bank table                                               */
        SndFxBus fxbus[2];                 /* +0x9C reverb/effect buses (stride 0x10)                        */
    } SndState;                            /* 0xBC                                                           */

    int sndgs[]; /* @0x80147860 : the SndState block (was aliased as gSndState) */
#define SND ((SndState *)sndgs)

    /* ---- SND runtime helpers shared across SNDPSXZ objs (permissive; real sigs in each .cpp) ---- */
    int iSNDvalidbank(int bank); /* nonzero == invalid */
    int iSNDbankremovepat(int bank, int idx, int *scratch);
    int iSNDremovetaggedpatch(unsigned char *bank, int *patch);
    int SNDstop(int handle);
    void iSNDplatformfree(void *p);
    int SNDbankremove(int bank);
    /* critical section + voice iteration + SPU pokes */
    void iSNDenteraudio(void);                         /* @0x800EA534 lock   */
    void iSNDleaveaudio(void);                         /* @0x800EA56C unlock */
    int iSNDgetchan(int handle);                       /* @0x800EE9D4 channel index from handle (<0 if none) */
    int iSNDpatchkey(int chan, int *iter);             /* @0x800FEF4C iterate voices of a chan; 0 when done  */
    void iSNDplatform3dpos(int voice, int pan, int z); /* @0x800EEE30 */
    void iSNDcalcvol(int voice);                       /* @0x800EF050 */
    void iSNDvol(int voice, int vol);                  /* @0x800F00F8 */
    /* fx/reverb bus */
    int iSNDplatformfxinit(int bus, int type, int depth, int delay); /* @0x800F0584 */
    int iSNDplatformfxmasterlevel(int bus, int level);               /* @0x800F05BC */
    int SNDfxlevel(int handle, int bus, int level);                  /* @0x800F05E8 */
    int SNDfxmasterlevel(int bus, int level);                        /* @0x800E6DD0 */

#ifdef __cplusplus
}
#endif
#endif /* LIB_SND_H */
