/* eaclib/psx/sndpsxz/sdpacket.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 13/13 ***
 *   Source obj : nfs4\eaclib\psx\sdpacket.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   13 fns @[0x80103784 .. 0x801046C8].  THE SPU/DMA HARDWARE FLOOR of the EA packet player -- the
 *   platform layer iSNDstream/spktplay call to actually stream ADPCM packets into the PSX SPU voice
 *   buffers via DMA, plus the SPU-IRQ-driven double-buffer service loop.
 *   Ghidra nfs4-f.exe.c (sdpacket) + disasm-v3 L<80103784+> -- disasm AUTHORITATIVE for every dropped arg:
 *     iSNDpsxzerospu(addr,LEN) [Ghidra in_a1]; iSNDpacketpurgeframes(p,byteoff,count) [Ghidra __thiscall];
 *     iSNDfillspuwithpackets(p,chunk) + its local frameSize is iSNDpacketget's 3rd (out) arg [Ghidra
 *     local_30]; iSNDplatformpacketplay is 8-ARG (p,note,volAngle:u16,level:u8,pitch:int,a6:int,fx:u8,
 *     hdr:u16*) [Ghidra dropped a3..a8 -> in_a2/in_a3/in_stack_*]; iSNDplatformpacketoverhead RETURNS a
 *     computed size [Ghidra emptied the delay-slot return]; iSNDpacketget(this,chanIdx,&frameSize) 3-arg.
 *
 *   PACKET-VOICE STATE TABLE @0x801479F0 (0x2c byte / 0xb int stride per voice, indexed [voice]):
 *     int +0x00 (DAT_801479f0) hdr-word0   int +0x04 (DAT_801479f4)   int +0x0c (DAT_801479fc) bytePos<<12
 *     int +0x10 (DAT_80147a00) servedPos   int +0x14 (DAT_80147a04) loopLen<<12
 *     u16 +0x18 (DAT_80147a08) volAngle    u16 +0x1a (DAT_80147a0a) pitch base
 *     b   +0x1c (DAT_80147a0c) playstate   b +0x1e (DAT_80147a0e) route   b +0x1f (DAT_80147a0f) channels
 *     b   +0x20 (DAT_80147a10) link        b +0x21 (DAT_80147a11) linkflag  b +0x22/0x23 (a12/a13) lvl/fx
 *     b   +0x27 (DAT_80147a17) voice-done flag (bit7 set == done)
 *   PER-PLAYER ctx (pp = (&DAT_80147e10)[player], malloc'd in create, int-indexed):
 *     +0x00 spuAddr  +0x04 spuSize  +0x0c bufBytes  +0x14 writePos  +0x18 servePos  +0x1c lastNewPos
 *     +0x20 dmaHandle  +0x2c frameSizeTbl  +0x34..0x46 fill state  +0x42(b) activeNote(-1 idle)
 *     +0x44(u16) blockBytes  +0x46(u16) framesPerBlock  +0x48.. per-channel SPU buffer ptrs
 */

#include "../../../nfs4_types.h"
#include "../../../lib/snd.h"
#include "../../../mips_semantics.h"
#include "psx_spu.h"

extern "C" int sndpp;                   /* current-player IRQ cursor                 */
extern "C" intptr &DAT_80147e10;        /* per-player ctx pointer table @0x80147e10  */
extern "C" int &DAT_80147e2c;           /* SPU control reg base (address) @0x80147e2c */
extern "C" int DAT_801234e4;            /* SPU ctx malloc size        @0x801234e4    */
extern "C" unsigned char &DAT_80147919; /* setirq re-entry guard byte @0x80147919    */

/* packet-voice state table fields (byte base; cast for int/short views) */
extern "C" unsigned char &DAT_801479f0; /* +0x00 */
extern "C" unsigned char &DAT_801479f4; /* +0x04 */
extern "C" unsigned char &DAT_801479fc; /* +0x0c */
extern "C" unsigned char &DAT_80147a00; /* +0x10 */
extern "C" unsigned char &DAT_80147a04; /* +0x14 */
extern "C" unsigned char &DAT_80147a08; /* +0x18 */
extern "C" unsigned char &DAT_80147a0a; /* +0x1a */
extern "C" unsigned char &DAT_80147a0c; /* +0x1c playstate */
extern "C" unsigned char &DAT_80147a0e; /* +0x1e route     */
extern "C" unsigned char &DAT_80147a0f; /* +0x1f channels  */
extern "C" unsigned char &DAT_80147a10; /* +0x20 link      */
extern "C" unsigned char &DAT_80147a11; /* +0x21 link flag */
extern "C" unsigned char &DAT_80147a12; /* +0x22 level     */
extern "C" unsigned char &DAT_80147a13; /* +0x23 fx level  */
extern "C" unsigned char &DAT_80147a17; /* +0x27 voice-done flag */

/* host/IRQ hooks (function-pointer globals installed by play/stop) */
extern "C" void (*snd_voice_done_hook)(void *voice); /* @0x8014803c */
extern "C"
{
    void (*snd_voice_done_hook)(void *voice) = 0; /* def @0x8014803c */
    void *snd_user_serve_hook = 0;
} /* def @0x80148038 */
extern "C" void *snd_user_serve_hook; /* @0x80148038 */
extern "C" void *gPreLoadTicks;       /* @0x80148040 (fn-ptr) */

/* sibling-obj dependencies */
extern "C" int iSNDpsxmalloc(int size);                                                                     /* sdmemman */
extern "C" void iSNDpsxfree(int spuAddr);                                                                   /* sdmemman */
extern "C" void iSNDpsxdisablespuirq(void);                                                                 /* sdspuirq */
extern "C" void iSNDpsxenablespuirq(void);                                                                  /* sdspuirq */
extern "C" void InterruptCallback(void);                                                                    /* syslib INTR */
extern "C" intptr iSNDpacketget(int p, int chanIdx, int *frameSizeOut);                                     /* spktplay */
extern "C" unsigned int iSNDpacketfreeframes(int p, int chanIdx, int bytes);                                /* spktplay */
extern "C" void iSNDstreamhotroddatachunks(void);                                                           /* sst */
extern "C" int iSNDdmqueue(intptr srcRam, int dstSpu, int len, unsigned char priority, unsigned char flag); /* sdma */
extern "C" int iSNDdmcomplete(int dmaHandle);                                                               /* sdma */
extern "C" void blockmove(int *dst, int *src, unsigned int len);                                            /* blkmov */
extern "C" int iSNDplatformpitch(int chan, int pitch);                                                      /* sdriver */
extern "C" void trap(unsigned int code);                                                                    /* compiler div-by-zero break */

/* forward decls (mutually referential within this obj) */
extern "C" void iSNDpacketgetirq(void);
extern "C" void iSNDpacketsetirq(void);
extern "C" int iSNDfillspuwithpackets(int p, int chunk);
extern "C" unsigned int iSNDpacketpurgeframes(int p, unsigned int byteoff, int count);
extern "C" void iSNDpsxpacketstop(void *voice);
extern "C" void iSNDpsxzerospu(int *addr, int len);

#define VB(base, idx) ((&(base))[idx])              /* byte at base+idx        */
#define VI(base, idx) (*(int *)(&(base) + (idx)))   /* int  at base+idx        */
#define VH(base, idx) (*(short *)(&(base) + (idx))) /* short at base+idx       */
#define VUH(base, idx) (*(unsigned short *)(&(base) + (idx)))

static uint64 sdpacket_served_samples[1];

static SndPacketContext *sdpacket_context(int player)
{
    return (SndPacketContext *)(&DAT_80147e10)[player];
}

static SndPacketVoice *sdpacket_voice(int note)
{
    return ((SndPacketVoice *)&DAT_801479f0) + note;
}

/* cop0-Status critical section wrapping the SPU-IRQ re-arm (target-only; host calls through). */
static void sdpacket_setirq_cs(void)
{
#if defined(__mips__)
    unsigned int sr;
    __asm__ volatile("mfc0 %0,$12" : "=r"(sr));
    __asm__ volatile("mtc0 %0,$12" : : "r"(sr & 0xfffffbfe)); /* mask IEc */
    iSNDpacketsetirq();
    __asm__ volatile("mtc0 %0,$12" : : "r"(sr));
#else
    iSNDpacketsetirq();
#endif
}

/* iSNDpacketgetirq @0x80103784 : on the SPU end-of-block IRQ, latch the current play byte-position of the
 *   active voice (and its linked partner) into the served-position slot, clamping at loop bounds. */
extern "C" void iSNDpacketgetirq(void)
{
    SndPacketContext *ctx = sdpacket_context(sndpp);
    int note = (int)ctx->activeNote;
    if (note < 0)
        return;
    SndPacketVoice *voice = sdpacket_voice(note);
    if ((voice->bytePos >> 0xc <= (unsigned)ctx->blockFrames) || ((unsigned)(ctx->totalBytes - (unsigned)ctx->blockFrames) <= voice->bytePos >> 0xc))
    {
        if ((unsigned)(voice->bytePos >> 0xb) < (unsigned)ctx->totalBytes)
        {
            voice->servedPos = voice->bytePos;
            if (voice->link >= 0)
            {
                sdpacket_voice(voice->link)->servedPos = voice->bytePos;
            }
        }
        else
        {
            voice->bytePos = 0;
            if (voice->link >= 0)
            {
                sdpacket_voice(voice->link)->bytePos = 0;
            }
        }
    }
}

/* iSNDpacketsetirq @0x801038BC : advance to the next playing player and arm the SPU IRQ on its next block
 *   boundary (writes the SPU IRQ-address register and re-installs the InterruptCallback). */
extern "C" void iSNDpacketsetirq(void)
{
    int i = 0;
    iSNDpsxdisablespuirq();
    if (DAT_80147919 == 0)
    {
        do
        {
            sndpp = sndpp + 1;
            if (0 < sndpp)
                sndpp = 0; /* single player -> wrap to 0 */
            SndPacketContext *ctx = sdpacket_context(sndpp);
            if (ctx != 0 && ctx->activeNote >= 0)
            {
#if !defined(AP_WIN)
                *(short *)(DAT_80147e2c + 0x1a4) = (short)((ctx->spuAddr + 8) >> 3);
#endif
                InterruptCallback();
                iSNDpsxenablespuirq();
                return;
            }
            i++;
        } while (i < 2);
    }
}

/* iSNDpacketirqcallback @0x8010399C : the SPU IRQ handler -- latch positions then re-arm. */
extern "C" void iSNDpacketirqcallback(void)
{
    iSNDpacketgetirq();
    iSNDpacketsetirq();
}

/* iSNDpsxzerospu @0x801039C4 : write SPU "silent loop" ADPCM (0x200 flag word + zero data) over `len`
 *   bytes at `addr`.  (Ghidra dropped the length arg as in_a1.) */
extern "C" void iSNDpsxzerospu(int *addr, int len)
{
    int i = 0;
    if (0 < len >> 2)
    {
        do
        {
            addr[0] = 0x200;
            addr[1] = 0;
            addr[2] = 0;
            addr[3] = 0;
            i += 4;
            addr += 4;
        } while (i < len >> 2);
    }
}

/* iSNDpacketpurgeframes @0x801039FC : release the packet frames that have finished playing, walking the
 *   ring from byte offset `byteoff` for `count` bytes and calling iSNDpacketfreeframes per channel as each
 *   frame's outstanding-byte counter drains.  Returns whether the cursor stayed within the buffer.
 *   (Ghidra rendered as __thiscall(this,p,arg2): this=player, p=byteoff, arg2=count.) */
extern "C" unsigned int iSNDpacketpurgeframes(int p, unsigned int byteoff, int count)
{
    SndPacketContext *ctx = sdpacket_context(p);
    SndPacketVoice *voice = sdpacket_voice(ctx->activeNote);
    unsigned int blk, span, taken, wrapped;
    unsigned short *fcnt;
    unsigned short n;
    int i;

    do
    {
        blk = (unsigned)ctx->framesPerBlock;
        if (blk == 0)
            trap(0x1c00);
        span = (byteoff / blk + 1) * blk - byteoff; /* bytes to next block boundary */
        if (count < (int)span)
            span = count;
        fcnt = (unsigned short *)ctx->frameSizeTable + byteoff / blk;
        n = *fcnt;
        taken = span;
        if ((int)(unsigned)n < (int)span)
            taken = (unsigned)n;
        *fcnt = n - (unsigned short)taken;
        if (taken != 0 && voice->channels != 0)
        {
            i = 0;
            do
            {
                iSNDpacketfreeframes(p, i, (int)taken);
                i++;
            } while (i < (int)voice->channels);
        }
        byteoff = byteoff + span;
        wrapped = (unsigned)(byteoff < (unsigned int)ctx->totalBytes);
        /* subu s4,s4,s2 is the branch delay slot at 0x80103B18 and therefore
         * executes for both outcomes; only the cursor reset is conditional. */
        count = count - (int)span;
        if (wrapped == 0)
        {
            byteoff = 0;
        }
    } while (0 < count);
    return wrapped;
}

/* iSNDfillspuwithpackets @0x80103B54 : the core DMA pump -- pull packet frames (iSNDpacketget), block-move
 *   their ADPCM into each channel's SPU buffer, set the ADPCM loop/end flags for `chunk` of the double
 *   buffer, and queue the SPU DMA (iSNDdmqueue).  (Ghidra __thiscall(this,p): this=player, p=chunk; the
 *   uninit local_30 is iSNDpacketget's frameSize out-param.) */
extern "C" int iSNDfillspuwithpackets(int p, int chunk)
{
    SndPacketContext *ctx = sdpacket_context(p);
    SndPacketVoice *voice = sdpacket_voice(ctx->activeNote);
    int i, dma;
    short rem;
    unsigned short take;
    short *ringp;
    int frameSize = 0;
    int avail;
    if (ctx->chunkRemaining == 0)
    {
        ctx->chunkOffset = 0;
        ctx->chunkRemaining = (short)ctx->blockBytes;
        ((short *)ctx->frameSizeTable)[chunk] = 0;
    }
    if (ctx->writePos == 0)
    { /* fresh start -> silence all SPU channels */
        i = 0;
        if (voice->channels != 0)
        {
            do
            {
                iSNDpsxzerospu((int *)ctx->channelBuffers[i], 0x10);
                i++;
            } while (i < (int)voice->channels);
        }
        ctx->chunkOffset = (short)(ctx->chunkOffset + 0x10);
        ctx->chunkRemaining = (short)(ctx->chunkRemaining - 0x10);
    }
    rem = ctx->chunkRemaining;
    for (;;)
    {
        if (rem == 0)
            goto queue_dma;
        take = (unsigned short)ctx->packetRemaining;
        if (take == 0)
        { /* need a new packet frame */
            i = 0;
            if (voice->channels != 0)
            {
                do
                {
                    ctx->packetData[i] = (intptr)iSNDpacketget(p, i, &frameSize);
                    i++;
                } while (i < (int)voice->channels);
            }
            if (ctx->packetData[0] == 0)
            { /* no frame available -> finish/flush */
                avail = ctx->writePos - ctx->readPos;
                if ((int)(unsigned)ctx->blockFrames < avail)
                    return avail;
                if (ctx->chunkCount < (unsigned short)ctx->completionPasses)
                    goto advance;
                if ((unsigned short)ctx->completionPasses < 2)
                { /* mark SPU loop-back */
                    i = 0;
                    if (voice->channels != 0)
                    {
                        do
                        {
                            iSNDpsxzerospu((int *)(ctx->channelBuffers[i] + (unsigned short)ctx->chunkOffset), (unsigned short)ctx->chunkRemaining);
                            i++;
                        } while (i < (int)voice->channels);
                    }
                }
                else
                { /* mark SPU end (flag byte = 2) */
                    i = 0;
                    if (voice->channels != 0)
                    {
                        do
                        {
                            *(char *)(ctx->channelBuffers[i] + 1) = 2;
                            i++;
                            *(char *)(ctx->channelBuffers[i - 1] + ctx->blockBytes - 0xf) = 2;
                        } while (i < (int)voice->channels);
                    }
                }
                if (ctx->chunkOffset == 0)
                    ctx->completionPasses = (short)(ctx->completionPasses + 1);
                ctx->chunkRemaining = 0;
            queue_dma:
                if (chunk == 0)
                { /* first chunk -> set SPU loop-start flag (|4) */
                    i = 0;
                    if (voice->channels != 0)
                    {
                        do
                        {
                            *(unsigned char *)(ctx->channelBuffers[i] + 1) |= 4;
                            i++;
                        } while (i < (int)voice->channels);
                    }
                }
                else if (chunk == ctx->chunkCount - 1)
                { /* last chunk -> loop-end (|1) */
                    i = 0;
                    if (voice->channels != 0)
                    {
                        do
                        {
                            intptr e = ctx->channelBuffers[i] + ctx->blockBytes;
                            *(unsigned char *)(e - 0xf) |= 1;
                            i++;
                        } while (i < (int)voice->channels);
                    }
                }
                i = 0; /* kick the SPU DMA for each channel */
                if (voice->channels != 0)
                {
                    do
                    {
                        int dstSpu = ctx->spuAddr + nfs4_mips_sll_s32(chunk, ctx->bufferShift) + ctx->bufferBytes * i;
                        dma = iSNDdmqueue(ctx->channelBuffers[i], dstSpu, ctx->blockBytes, 2, (unsigned char)(chunk == 0 && i == 0));
                        ctx->dmaHandle = dma;
                        i++;
                    } while (i < (int)voice->channels);
                }
            advance:
                ctx->currentChunk = (short)chunk;
                ctx->writePos += ctx->framesPerBlock;
                return ctx->writePos;
            }
            ctx->completionPasses = 0;
            ctx->packetOffset = 0;
            ctx->packetRemaining = (short)((frameSize * 4) / 7); /* ADPCM bytes per chunk */
            ctx->frameBytes = ctx->packetRemaining;
            take = (unsigned short)ctx->packetRemaining;
        }
        if (take >= (unsigned short)ctx->chunkRemaining)
            take = (unsigned short)ctx->chunkRemaining;
        ringp = (short *)ctx->frameSizeTable + chunk;
        *ringp = *ringp + (short)((int)((unsigned)take * 7) >> 2);
        i = 0;
        if (voice->channels != 0)
        {
            do
            {
                blockmove((int *)(ctx->packetData[0] + (unsigned short)ctx->packetOffset + (unsigned short)ctx->frameBytes * i), (int *)(ctx->channelBuffers[i] + (unsigned short)ctx->chunkOffset), (unsigned)take);
                i++;
            } while (i < (int)voice->channels);
        }
        ctx->chunkOffset = (short)(ctx->chunkOffset + take);
        ctx->packetOffset = (short)(ctx->packetOffset + take);
        ctx->chunkRemaining = (short)(ctx->chunkRemaining - take);
        rem = ctx->chunkRemaining;
        ctx->packetRemaining = (short)(ctx->packetRemaining - take);
    }
}

/* iSNDpacketserve @0x80104024 : per-tick service -- pull fresh stream chunks, advance each player's served
 *   position from the SPU play-cursor, purge finished frames, and top up the SPU double buffer. */
extern "C" void iSNDpacketserve(void)
{
    int p;
    iSNDstreamhotroddatachunks();
    for (p = 0; p < 1; p++)
    {
        SndPacketContext *ctx = sdpacket_context(p);
        if (ctx != 0 && ctx->activeNote >= 0)
        {
            SndPacketVoice *voice = sdpacket_voice(ctx->activeNote);
            int servePos = ctx->servedPos;
            uint64 playedSamples = spu_voice_sample_position(ctx->activeNote);
            uint64 completedSamples = playedSamples / 28u * 28u;
            uint64 advanceSamples = 0;
            unsigned int available;
            unsigned int adv;
            int newPos;
            if (voice->playState == 2 && playedSamples != ~(uint64)0 && sdpacket_served_samples[p] <= completedSamples)
                advanceSamples = completedSamples - sdpacket_served_samples[p];
            available = (unsigned int)(ctx->writePos - ctx->readPos);
            if (advanceSamples > available)
                advanceSamples = available;
            adv = (unsigned int)advanceSamples;
            newPos = servePos + (int)adv;
            if (ctx->totalBytes <= newPos)
                newPos %= ctx->totalBytes;
            sdpacket_served_samples[p] = completedSamples;
            if (0x70ffffff < ctx->readPos)
            { /* keep the byte counters from overflowing */
                ctx->readPos -= 0x70000000;
                ctx->writePos -= 0x70000000;
            }
            ctx->readPos += adv;
            iSNDpacketpurgeframes(p, (unsigned)servePos, (int)adv);
            /* The served-position store is in the refill branch delay slot */
            ctx->servedPos = newPos;
            if (ctx->writePos - ctx->readPos < ctx->refillThreshold)
            {
                if (iSNDdmcomplete(ctx->dmaHandle) != 0)
                {
                    unsigned int idx = (unsigned)(unsigned short)ctx->currentChunk + 1;
                    if (ctx->chunkCount <= idx)
                        idx -= ctx->chunkCount;
                    iSNDfillspuwithpackets(p, (int)idx);
                }
            }
        }
    }
}

/* iSNDplatformpacketoverhead @0x801041B8 : per-player SPU-context byte overhead (the malloc'd voice ctx
 *   sized from DAT_801234e4, /4096 rounded up to 4, *2, + 0x1050).  (Ghidra emptied the delay-slot return.) */
extern "C" int iSNDplatformpacketoverhead(void)
{
    int v = DAT_801234e4;
    if (v < 0)
        v += 0xfff;
    v >>= 0xc;
    return ((v + 3) & ~3) * 2 + 0x1050;
}

/* iSNDplatformcalcdatarate @0x801041EC : bytes/second for a sample of rate `sample_rate[0]` and channel
 *   count `sample_rate[1]`, scaled by 0x92/256 (ADPCM ratio). */
extern "C" int iSNDplatformcalcdatarate(unsigned short *sample_rate)
{
    return (int)((unsigned)*sample_rate * (unsigned)(unsigned char)sample_rate[1] * 0x92) >> 8;
}

/* iSNDplatformpacketplaycreate @0x8010421C : allocate a player's SPU context, install the voice-done hook,
 *   register the ctx in DAT_80147e10[p].  Returns its byte size / -9 on malloc failure. */
extern "C" int iSNDplatformpacketplaycreate(int p, int *mem)
{
    SndPacketContext *ctx = (SndPacketContext *)mem;
    int r;
    snd_voice_done_hook = (void (*)(void *))iSNDpsxpacketstop;
    ctx->activeNote = -1;
    ctx->frameSizeTable = (intptr)((unsigned char *)ctx + 0x1050);
    ctx->spuAddr = iSNDpsxmalloc(DAT_801234e4);
    ctx->spuSize = DAT_801234e4;
    if (ctx->spuAddr == 0)
    {
        r = -9;
    }
    else
    {
        (&DAT_80147e10)[p] = (intptr)ctx;
        r = iSNDplatformpacketoverhead();
    }
    return r;
}

/* iSNDplatformpacketplaydestroy @0x801042C0 : free a player's SPU context and clear its slot. */
extern "C" void iSNDplatformpacketplaydestroy(int p)
{
    SndPacketContext *ctx = sdpacket_context(p);
    iSNDpsxfree(ctx->spuAddr);
    (&DAT_80147e10)[p] = 0;
}

/* iSNDplatformpacketplay @0x80104304 : start a voice playing a packet stream -- program the voice state
 *   table, derive the SPU block geometry from the player ctx, prime two buffers via iSNDfillspuwithpackets,
 *   install the serve + IRQ hooks, set initial pitch, and key the voice.  8-arg (Ghidra dropped a3..a8). */
extern "C" int iSNDplatformpacketplay(int p, int note, unsigned short volAngle, unsigned char level, int pitch, int a6, unsigned char fxlevel, unsigned short *hdr)
{
    int vt = note * 0x2c;
    SndPacketContext *ctx = sdpacket_context(p);
    SndPacketVoice *voice = sdpacket_voice(note);
    unsigned int chunkBytes, frames, perCh;
    int blockSamps;
    int i;

    VB(DAT_80147a11, vt) = 0;
    VB(DAT_80147a10, vt) = 0xff;
    VB(DAT_80147a0e, vt) = 0;
    VB(DAT_80147a0f, vt) = (unsigned char)hdr[1]; /* channel count */
    VI(DAT_801479f4, vt) = 0;
    VUH(DAT_80147a08, vt) = volAngle;
    VB(DAT_80147a12, vt) = level;
    VB(DAT_80147a13, vt) = fxlevel;
    voice->spuAddr = ctx->spuAddr;
    VB(DAT_80147a17, vt) = (unsigned char)p;

    if ((unsigned char)VB(DAT_80147a0f, vt) == 0)
        trap(0x1c00);
    chunkBytes = 0x1000 / (unsigned char)VB(DAT_80147a0f, vt);
    ctx->blockBytes = (unsigned short)chunkBytes;
    ctx->framesPerBlock = (unsigned short)((int)(chunkBytes * 0x1c) >> 4);
    {
        unsigned char ch = (unsigned char)VB(DAT_80147a0f, vt);
        ctx->channelBuffers[0] = (intptr)((unsigned char *)ctx + 0x50);
        ctx->bufferShift = (unsigned char)(0xd - ch);
        ctx->channelBuffers[1] = (intptr)((unsigned char *)ctx + ctx->blockBytes + 0x50);
        blockSamps = ctx->spuSize >> ((0xd - ch) & 0x1f);
    }
    ctx->chunkCount = (unsigned short)blockSamps;
    frames = (unsigned)(blockSamps & 0xffff);
    perCh = (unsigned char)VB(DAT_80147a0f, vt);
    if (perCh == 0)
        trap(0x1c00);
    ctx->chunkCount = (unsigned short)(frames / perCh);
    {
        int total = (int)(frames / perCh) * ctx->framesPerBlock;
        ctx->blockFrames = ctx->framesPerBlock;
        ctx->activeNote = (signed char)note;
        ctx->completionPasses = 0;
        ctx->frameBytes = 0;
        ctx->packetOffset = 0;
        ctx->packetRemaining = 0;
        ctx->chunkRemaining = 0;
        ctx->packetData[0] = 0;
        ctx->packetData[1] = 0;
        ctx->dmaHandle = 0;
        ctx->servedPos = 0;
        ctx->readPos = 0;
        ctx->writePos = 0;
        ctx->bufferBytes = (unsigned)ctx->chunkCount << (ctx->bufferShift & 0x1f);
        ctx->totalBytes = total;
        ctx->refillThreshold = total - ctx->framesPerBlock;
        sdpacket_served_samples[p] = 0;
    }
    i = 0;
    do
    {
        while (iSNDdmcomplete(ctx->dmaHandle) == 0)
        {
        }
        iSNDfillspuwithpackets(p, i);
        i++;
    } while (i < 2);

    snd_user_serve_hook = (void *)iSNDpacketserve;
    gPreLoadTicks = (void *)iSNDpacketsetirq;
    VI(DAT_801479fc, vt) = 0;
    VI(DAT_80147a00, note * 0x2c) = 0;
    voice->loopBytes = nfs4_mips_sll_s32(ctx->totalBytes, 0xc);
    VH(DAT_80147a0a, vt) = (short)((unsigned)*hdr * 0x17c7 >> 0x10);
    if (1 < (unsigned char)VB(DAT_80147a0f, vt))
    { /* arm the linked partner voice */
        voice->link = (signed char)SND->voices[note].f04;
        VB(DAT_80147a11, (char)VB(DAT_80147a10, vt) * 0x2c) = 1;
        VI(DAT_801479fc, (char)VB(DAT_80147a10, vt) * 0x2c) = 0;
        VI(DAT_80147a00, (char)VB(DAT_80147a10, vt) * 0x2c) = 0;
        VI(DAT_80147a04, (char)VB(DAT_80147a10, vt) * 0x2c) = VI(DAT_80147a04, vt);
    }
    iSNDplatformpitch(note, pitch);
    sdpacket_setirq_cs();
    VB(DAT_80147a0c, vt) = 1; /* playstate = playing */
    return 0;
}

/* iSNDpsxpacketstop @0x801046C8 : tear down a finished voice -- mark its player + voice slot idle, and if no
 *   voices remain active, drop the serve hook and point the pre-load tick back at the bare IRQ re-arm. */
extern "C" void iSNDpsxpacketstop(void *voicePtr)
{
    SndPacketVoice *voice = (SndPacketVoice *)voicePtr;
    SndPacketContext *ctx = sdpacket_context(voice->player);
    int i, active = 0;
    ctx->activeNote = -1;
    voice->player = -1;
    if (((unsigned char *)sndgs)[0x11] != 0)
    { /* sndgs[4]._1_1_ = channel count */
        for (i = 0; i < (int)(unsigned)((unsigned char *)sndgs)[0x11]; i++)
            if (-1 < (int)((unsigned)VB(DAT_80147a17, i * 0x2c) << 0x18)) /* bit7 clear == still active */
                active++;
    }
    if (active == 0)
    {
        snd_user_serve_hook = 0;
        gPreLoadTicks = (void *)iSNDpacketsetirq;
    }
    sdpacket_setirq_cs();
}
