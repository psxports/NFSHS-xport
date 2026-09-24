#include "../../../nfs4_types.h"
#include "../../../lib/snd.h"
#include "../../../mips_semantics.h"

/* eaclib/psx/sndpsxz/stagpat.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 8/8 ***
 *   Source obj : nfs4\eaclib\psx\stagpat.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   8 fns @[0x80101ABC .. 0x801025C0].  The patch-trigger engine -- parse a sound bank's tag stream, build
 *   per-note "timbres", and launch the voices (cSNDplay's core).  Ghidra nfs4-f.exe.c (stagpat) + IDA sigs.
 *
 *   ALL 8 fns SEALED.  The two dense parsers (iSNDplaytaggedpatch 864B / iSNDplaytaggedtimbre 1280B) were
 *   reconstructed from Ghidra + disasm-v3 (7-arg timbre call, range fields, captured returns Ghidra lost).
 *   NEW leaf deps: sgettag(iSNDgettag), sdresolv(iSNDplatformresolve/remove), srrange(randrange),
 *   srandom(iSNDrandom), sdplapat(iSNDplatformplay).
 *
 *   TIMBRE struct (0x98 bytes): +0x14/0x20 note range, +0x1c base note, +0x30 detune, +0x08/0x10 vel,
 *     +0x64 envelope ptr (&snddefaultenvelope), +0x90 patch flag, +0x94 timbre-active.
 *   BANK header: +0x03 flags (bit1 = 8-byte header, bit0 = resolved), +0x04/+0x08 tag stream start.
 */

extern "C" int sndgs[];
extern "C" signed char snddefaultenvelope; /* default envelope table (sclcptch/data-mat) */
extern "C" char DAT_801371cc;              /* rolling key-group counter */

extern "C" int iSNDgettag(intptr *cursor, unsigned int *outId, int *outVal, intptr *outPtr);                                        /* sgettag */
extern "C" int iSNDplatformresolve(intptr resolv, intptr patchBase, int *scratch);                                                  /* sdresolv */
extern "C" int iSNDplatformremove(intptr resolv, int *patch_idx);                                                                   /* sdresolv */
extern "C" int randrange(int range);                                                                                                /* srrange  */
extern "C" int iSNDrandom(void);                                                                                                    /* srandom  */
extern "C" int iSNDallocchan(unsigned int priority, int numChannels, int a2, unsigned int *out);                                    /* salloc */
extern "C" intptr iSNDfreechan(int chan);                                                                                           /* salloc   */
extern "C" int iSNDcalcpitch(int note);                                                                                             /* sclcptch */
extern "C" void iSNDcalcvol(int chan);                                                                                              /* spatkey  */
extern "C" int iSNDplatformplay(intptr stream, int voice, int level, int pitch, int sampleArg, int fx, int volAngle, int volDelta); /* sdplapat */
extern "C" void trap(unsigned int code);                                                                                            /* compiler div-by-zero break */

extern "C" void iSNDresetpatch(SndTimbre *patch);                                                                                                          /* @0x80101ABC */
extern "C" unsigned char *iSNDresettimbre(SndTimbre *t, SndTimbre *buf);                                                                                   /* @0x80101AC4 */
extern "C" intptr iSNDresolveheader(SndTimbre *hdr, const SndTimbre *out);                                                                                 /* @0x80101B7C */
extern "C" void iSNDfindfreekey(void);                                                                                                                     /* @0x80101BFC */
extern "C" int iSNDresolvetaggedpatch(unsigned char *bank, intptr patchBase, int *scratch);                                                                /* @0x801024EC */
extern "C" int iSNDremovetaggedpatch(unsigned char *bank, int *patch_idx);                                                                                 /* @0x801025C0 */
extern "C" int iSNDplaytaggedtimbre(intptr timbre, const unsigned char *tag, SndTimbre *vol, SndTimbre *header, int baseNote, int velScale, int pitchOff); /* @0x80101C8C */
extern "C" int iSNDplaytaggedpatch(unsigned char *patch, int *tag);                                                                                        /* @0x8010218C */
extern "C" int SNDstop(int tag);                                                                                                                           /* sstop  */
extern "C" int iSNDgetchan(int tag);                                                                                                                       /* salloc */
extern "C" void iSNDenteraudio(void);                                                                                                                      /* sserver */
extern "C" void iSNDleaveaudio(void);

/* Tag ids are PSX 32-bit word indices.  Route them explicitly so pointer
 * fields may widen on a host without shifting every later tag field. */
static void snd_timbre_set_tag(SndTimbre *t, unsigned int id, intptr value)
{
    switch (id)
    {
        case 0:
            t->f00 = (int)value;
            break;
        case 1:
            t->velMin = (int)value;
            break;
        case 2:
            t->velMax = (int)value;
            break;
        case 3:
            t->noteMin = (int)value;
            break;
        case 4:
            t->noteMax = (int)value;
            break;
        case 5:
            t->priority = (int)value;
            break;
        case 6:
            t->allocFlags = (int)value;
            break;
        case 7:
            t->baseNote = (int)value;
            break;
        case 8:
            t->noteLimit = (int)value;
            break;
        case 9:
            t->segmentCount = (int)value;
            break;
        case 10:
            t->duration = (int)value;
            break;
        case 11:
            t->channels = (int)value;
            break;
        case 12:
            t->detune = (int)value;
            break;
        case 13:
            t->detuneRandom = (int)value;
            break;
        case 14:
            t->pan = (int)value;
            break;
        case 15:
            t->panRandom = (int)value;
            break;
        case 16:
            t->pitchBase = (int)value;
            break;
        case 17:
            t->pitchRandom = (int)value;
            break;
        case 18:
            t->finalCurve = value;
            break;
        case 19:
            t->volumeScale = (int)value;
            break;
        case 20:
            t->f50 = (int)value;
            break;
        case 21:
            t->panCurve = value;
            break;
        case 22:
            t->f58 = (int)value;
            break;
        case 23:
            t->f5C = value;
            break;
        case 24:
            t->f60 = (int)value;
            break;
        case 25:
            t->sweepTable = value;
            break;
        case 26:
            t->f68 = (int)value;
            break;
        case 27:
            t->f6C = (int)value;
            break;
        case 28:
            t->sweepBase = (int)value;
            break;
        case 29:
            t->velocityEnvelope = value;
            break;
        case 30:
            t->velocityPeriod = (int)value;
            break;
        case 31:
            t->velocityRandomPhase = (int)value;
            break;
        case 32:
            t->pitchLfo = value;
            break;
        case 33:
            t->pitchPeriod = (int)value;
            break;
        case 34:
            t->pitchLfoStart = (int)value;
            break;
        case 35:
            t->pitchRandomPhase = (int)value;
            break;
        case 36:
            t->patchFlag = (int)value;
            break;
        case 37:
            t->active = (int)value;
            break;
    }
}

/* iSNDresetpatch @0x80101ABC : clear a patch-play state's flag word (+0x90). */
extern "C" void iSNDresetpatch(SndTimbre *patch)
{
    patch->patchFlag = 0;
}

/* iSNDresettimbre @0x80101AC4 : zero the 0x98-byte timbre `buf` then load the default timbre into `t`
 *   (note range 0..0x3c, full velocity, default envelope). */
extern "C" unsigned char *iSNDresettimbre(SndTimbre *t, SndTimbre *buf)
{
    SndTimbre zero = {};
    *buf = zero; /* retail clears all 0x98 Win32 bytes */
    t->priority = -1;
    t->noteLimit = -1;
    t->baseNote = 0x3c;
    t->detune = 0x40;
    t->velMin = 0;
    t->velMax = 0x7f;
    t->noteMin = 0;
    t->noteMax = 0x7f;
    t->allocFlags = 0;
    t->segmentCount = 1;
    t->duration = 0;
    t->channels = 1;
    t->detuneRandom = 0;
    t->pan = 0x7f;
    t->panRandom = 0;
    t->pitchBase = 0;
    t->pitchRandom = 0;
    t->finalCurve = 0;
    t->volumeScale = 0;
    t->panCurve = 0;
    t->f5C = 0;
    t->sweepBase = 0x7f;
    t->velocityEnvelope = 0;
    t->velocityPeriod = 0;
    t->velocityRandomPhase = 0;
    t->pitchLfo = 0;
    t->pitchPeriod = 0;
    t->pitchRandomPhase = 0;
    t->pitchLfoStart = 0;
    t->active = 1;
    t->sweepTable = (intptr)&snddefaultenvelope;
    return (unsigned char *)&snddefaultenvelope;
}

/* iSNDresolveheader @0x80101B7C : fold an override header `out` into the running timbre header `hdr`
 *   (sum the envelope / volume / pitch fields). */
extern "C" intptr iSNDresolveheader(SndTimbre *hdr, const SndTimbre *out)
{
    intptr r;
    hdr->finalCurve += out->finalCurve;
    hdr->panCurve += out->panCurve;
    hdr->f5C += out->f5C;
    hdr->velocityEnvelope += out->velocityEnvelope;
    r = hdr->pitchLfo + out->pitchLfo;
    hdr->pitchLfo = r;
    if (hdr->sweepTable != 0)
    {
        r = hdr->sweepTable + out->sweepTable;
        hdr->sweepTable = r;
    }
    return r;
}

/* iSNDfindfreekey @0x80101BFC : advance the rolling key-group counter (DAT_801371cc) to a value not
 *   currently owned by any held channel. */
extern "C" void iSNDfindfreekey(void)
{
    char key;
    int i, slot;
    while (1)
    {
        key = DAT_801371cc + 1;
        if ((char)(DAT_801371cc + 1) == 0) /* skip 0 (the "no group" sentinel) */
            key = DAT_801371cc + 2;
        DAT_801371cc = key;
        i = 0;
        slot = sndgs[0x25];
        if (((unsigned char *)sndgs)[0x11] == 0)
            break;
        while (*(char *)(slot + 0xb) == 0 || *(char *)(slot + 0x37) != DAT_801371cc)
        {
            i++;
            slot += 100;
            if ((int)(unsigned)((unsigned char *)sndgs)[0x11] <= i)
                return; /* nobody owns this key -> it is free */
        }
    }
}

/* iSNDresolvetaggedpatch @0x801024EC : walk a bank's tag stream and resolve its SPU sample data (tag 0xfd
 *   = platform resolve), marking the bank resolved (+3 |= 1).  Returns -1 / resolve result. */
extern "C" int iSNDresolvetaggedpatch(unsigned char *bank, intptr patchBase, int *scratch)
{
    intptr cursor, tagPtr;
    unsigned int tagId;
    int tagValue;
    int r = -1;
    cursor = (intptr)(bank + ((bank[3] & 2) == 0 ? 4 : 8));
    while (iSNDgettag(&cursor, &tagId, &tagValue, &tagPtr) != 0)
    {
        if (tagId == 0xfd)
            r = iSNDplatformresolve(cursor, patchBase, scratch);
    }
    if (-1 < r)
        bank[3] |= 1;
    return r;
}

/* iSNDremovetaggedpatch @0x801025C0 : walk a bank's tag stream and release its resolved SPU data (tag 0xfd
 *   = platform remove), clearing the resolved flag (+3 &= ~1). */
extern "C" int iSNDremovetaggedpatch(unsigned char *bank, int *patch_idx)
{
    intptr cursor, tagPtr;
    unsigned int tagId;
    int tagValue;
    cursor = (intptr)(bank + ((bank[3] & 2) == 0 ? 4 : 8));
    while (iSNDgettag(&cursor, &tagId, &tagValue, &tagPtr) != 0)
    {
        if (tagId == 0xfd)
            iSNDplatformremove(cursor, patch_idx);
    }
    bank[3] &= 0xfe;
    return 0;
}

/* iSNDplaytaggedtimbre @0x80101C8C : launch ONE note's voice from a fully-resolved timbre.  Folds the
 *   override `header`, randomises detune/pan/pitch (srrange/srandom), allocates a channel, fills its ~50
 *   playback fields from the timbre `vol`, computes the SPU sweep, and starts it via iSNDplatformplay.
 *   7-arg per IDA/disasm (Ghidra showed 3 + dropped header/baseNote/velScale/pitchOff).
 *     header   = override header folded into `vol`
 *     baseNote = the note being played (transposes pitch off the timbre's base note vol[0x1c])
 *     velScale = velocity (scales the pan curve)
 *     pitchOff = pitch-bend offset (applied when vol[0x90] is set)
 *   iSNDallocchan is 4-arg (vol[0x14] priority, vol[0x2c] numCh, vol[0x18] flag, &out).  Retail passes
 *   eight words to iSNDplatformplay; its body consumes the first seven while preserving the source ABI. */
extern "C" int iSNDplaytaggedtimbre(intptr timbre, const unsigned char *tag, SndTimbre *vol, SndTimbre *header, int baseNote, int velScale, int pitchOff)
{
    unsigned char b7 = tag[7];
    signed char b8 = (signed char)tag[8];
    unsigned char b9 = tag[9];
    unsigned char b10 = tag[10];
    unsigned int out;
    int chan, detune, pan, panc, sw, s28, num, volAngle, fxLevel;
    short sv;

    iSNDresolveheader(vol, header);

    detune = vol->detune;
    if (vol->detuneRandom != 0)
        detune = nfs4_mips_addu_s32(detune, randrange(vol->detuneRandom));
    if (detune < 0x80)
    {
        if (detune < 0)
            detune = 0;
    }
    else
        detune = 0x7f;

    chan = iSNDallocchan((unsigned int)vol->priority, vol->channels, vol->allocFlags, &out);
    if (-1 < chan)
    {
        SndVoice *voice = &SND->voices[chan];
        voice->f33 = (signed char)vol->active;
        sv = *(short *)&vol->pitchBase;
        voice->f5C = sv;
        sv = (short)(sv - nfs4_mips_mult_s32(vol->baseNote - baseNote, 100));
        voice->f5C = sv;
        if (vol->patchFlag != 0)
            voice->f5C = (short)(sv + (short)pitchOff);
        if (vol->pitchRandom != 0)
            voice->f5C = (short)(voice->f5C + (short)randrange(vol->pitchRandom));
        voice->f44 = vol->finalCurve;
        voice->pancurve = vol->panCurve;
        voice->f1C = nfs4_mips_sll_s32((int)b8, 16);
        voice->f4C = vol->f5C;
        voice->f14 = 0;
        voice->pan_cur = (signed char)b7;

        volAngle = (int)b7;
        if (voice->f33 != 1)
            volAngle = nfs4_mips_addu_s32(nfs4_mips_mult_s32(volAngle - 0x40, (int)voice->f33), 0x40);
        volAngle = nfs4_mips_addu_s32(detune, volAngle) - 0x40;
        if (volAngle < 0)
            volAngle = 0;
        else if (volAngle >= 0x80)
            volAngle = 0x7f;
        if (voice->pancurve != 0)
            volAngle = ((signed char *)voice->pancurve)[volAngle];

        pan = vol->pan;
        if (vol->panRandom != 0)
            pan = nfs4_mips_addu_s32(pan, randrange(vol->panRandom));
        panc = pan;
        if (0x7f < pan)
            panc = 0x7f;
        if (pan < -0x80)
            panc = -0x80;
        voice->f2C = (signed char)((nfs4_mips_mult_s32(panc, velScale)) / 0x7f);
        voice->pan = (signed char)detune;
        voice->f2F = (signed char)b9;
        voice->f5A = (short)nfs4_mips_mult_s32(vol->duration, 100);
        voice->f40 = vol->sweepTable;
        voice->f31 = 0;
        voice->f24 = nfs4_mips_sll_s32(vol->sweepBase, 16);
        voice->f30 = (signed char)vol->segmentCount;
        voice->f32 = (signed char)vol->noteLimit;
        sw = *(int *)voice->f40;
        voice->f28 = sw;
        if (sw < 0)
            voice->f28 = 0x7fffffff;
        s28 = voice->f28;
        num = nfs4_mips_subu_s32(nfs4_mips_sll_s32(((int *)voice->f40)[1], 16), voice->f24);
        if (s28 == 0)
            trap(0x1c00);
        if (s28 == -1 && num == (int)0x80000000)
            trap(0x1800);
        voice->f20 = num / s28;
        voice->f50 = vol->velocityEnvelope;
        voice->f54 = vol->pitchLfo;
        voice->f38 = (unsigned char)vol->velocityPeriod;
        voice->f39 = (unsigned char)vol->pitchPeriod;
        *(unsigned short *)&voice->_g58[0] = (unsigned short)(unsigned char)vol->pitchLfoStart;
        {
            unsigned int rv = (unsigned int)vol->velocityRandomPhase;
            if (rv == 0)
            {
                voice->f3A = 0;
            }
            else
            {
                unsigned int randomValue = (unsigned int)iSNDrandom();
                if ((unsigned int)vol->velocityPeriod == 0)
                    trap(0x1c00);
                voice->f3A = (unsigned char)(randomValue % (unsigned int)vol->velocityPeriod);
            }
            rv = (unsigned int)vol->pitchRandomPhase;
            if (rv == 0)
            {
                voice->f3B = 0;
            }
            else
            {
                unsigned int randomValue = (unsigned int)iSNDrandom();
                if ((unsigned int)vol->pitchPeriod == 0)
                    trap(0x1c00);
                voice->f3B = (unsigned char)(randomValue % (unsigned int)vol->pitchPeriod);
            }
        }
        *(short *)&voice->_g3E[0] = *(const short *)(tag + 0xe);
        voice->f5E = 0;
        voice->f60 = *(const unsigned short *)(tag + 0xc);
        iSNDcalcpitch(chan);
        voice->f35 = (signed char)b10;
        voice->f34 = (signed char)vol->volumeScale;
        voice->bank = (signed char)tag[4];
        *(short *)&voice->_g08[0] = *(const short *)tag;
        iSNDcalcvol(chan);
        fxLevel = nfs4_mips_mult_s32(sndgs[0x28], (int)voice->f34);
        fxLevel = nfs4_mips_mult_s32(fxLevel, (int)voice->f35) / 0x7f;
        {
            int volParam = nfs4_mips_sll_s32(volAngle - 0x40, 8) & 0xffff;
            int volDelta = 0;
            if (tag[0xb] != 0)
            {
                volParam = *(const unsigned short *)(tag + 0x10);
                volDelta = *(const short *)(tag + 0x12);
            }
            int playResult = iSNDplatformplay(timbre, chan, (int)voice->vol_l, (int)(unsigned)voice->f62, *(const unsigned short *)(tag + 0xe), fxLevel, volParam, volDelta);
            if (playResult < 0)
            {
                iSNDfreechan(chan);
                return playResult;
            }
        }
        return nfs4_mips_bits_to_s32(out);
    }
    return chan;
}

/* iSNDplaytaggedpatch @0x8010218C : THE cSNDplay entry -- parse a patch's tag stream into per-note timbres
 *   and launch each note whose range matches.  For each tag: 0xfd records the SPU sample data ptr (the
 *   "timbre" to play); 0xfe terminates a note-region header -> if the requested note(tag[5])/vel(tag[6])
 *   fall in the accumulated range (builtTimbre[1..4]) launch it via iSNDplaytaggedtimbre, then reset the
 *   timbre; tag < 0x26 sets timbre[tag] (and the parallel override header) from the tag's two values.
 *   The started voices are collected and joined into a key group; on any failure all are SNDstop'd.
 *   Ghidra body + disasm: range fields are builtTimbre +4/+8 (vel min/max), +0xc/+0x10 (note min/max);
 *   the iSNDplaytaggedtimbre return (Ghidra lost it to void-typing) is the started voice tag.
 *     7-arg call: (timbreData, tag, &builtTimbre, &header, note, vel, pitchOff). pitchOff is best-effort 0
 *     (it is only used when the patch flag builtTimbre[0x90] is set, which iSNDresetpatch clears). */
extern "C" int iSNDplaytaggedpatch(unsigned char *bank, int *tag)
{
    int note, vel;
    intptr cursor, timbreData, prevTimbre;
    int nStarted = 0, nAtFail = 0;
    unsigned int ret = 0xfffffff7;
    unsigned int tagId;
    int tagValue;
    intptr tagPointer;
    SndTimbre bt;  /* built timbre   (anStack_198) */
    SndTimbre hdr; /* override header (auStack_100) */
    unsigned int started[12];
    int i, slot, lastSlot = 0, r;

    if (bank == 0)
        return -8;
    note = (int)*((signed char *)tag + 5);
    vel = (int)*((signed char *)tag + 6);
    cursor = (intptr)(bank + ((bank[3] & 2) == 0 ? 4 : 8));

    iSNDresetpatch(&bt);
    iSNDresettimbre(&bt, &hdr);
    iSNDenteraudio();
    iSNDfindfreekey();

    prevTimbre = 0;
    for (;;)
    {
        timbreData = prevTimbre;
        nAtFail = nStarted; /* iVar10 = iVar9 captured at iteration start */
        if (iSNDgettag(&cursor, &tagId, &tagValue, &tagPointer) == 0)
            break;
        prevTimbre = cursor; /* after a 0xfd tag the cursor IS the sample data */
        if (tagId == 0xfd)
            continue;
        prevTimbre = timbreData; /* non-0xfd: keep the last sample ptr */
        if (tagId == 0xfe)
        { /* note-region complete -> launch if in range */
            if (bt.velMin <= vel && vel <= bt.velMax && bt.noteMin <= note && note <= bt.noteMax)
            {
                r = iSNDplaytaggedtimbre(timbreData, (const unsigned char *)tag, &bt, &hdr, note, vel, 0);
                if (r < 0)
                    goto fail;
                started[nStarted++] = (unsigned int)r;
                ret = (unsigned int)r;
            }
            iSNDresettimbre(&bt, &hdr);
        }
        else if (tagId < 0x26)
        { /* field tag -> set timbre[idx] + parallel header[idx] */
            snd_timbre_set_tag(&bt, tagId, (intptr)tagValue);
            snd_timbre_set_tag(&hdr, tagId, tagPointer);
            if (tagId == 0x24)
                randrange(tagValue);
        }
    }
    /* the final note-region (no trailing 0xfe) */
    if (bt.velMin <= vel && vel <= bt.velMax && bt.noteMin <= note && note <= bt.noteMax)
    {
        r = iSNDplaytaggedtimbre(timbreData, (const unsigned char *)tag, &bt, &hdr, note, vel, 0);
        if (r < 0)
            goto fail;
        started[nStarted++] = (unsigned int)r;
        ret = (unsigned int)r;
    }

    nAtFail = 0;
    if (nStarted != 0)
    { /* join the started voices into a key group */
        if (nStarted == 1)
        {
            i = iSNDgetchan(started[0]);
            if (-1 < i)
            {
                slot = sndgs[0x25] + i * 100;
                *(unsigned char *)(slot + 0x37) = 0;
                *(unsigned char *)(slot + 0x36) = 0;
            }
        }
        else
        {
            for (i = 0; i < nStarted; i++)
            {
                int ch = iSNDgetchan(started[i]);
                if (-1 < ch)
                {
                    lastSlot = sndgs[0x25] + ch * 100;
                    *(unsigned char *)(lastSlot + 0x37) = (unsigned char)DAT_801371cc;
                    *(unsigned char *)(lastSlot + 0x36) = 0;
                }
            }
            *(unsigned char *)(lastSlot + 0x36) = 1; /* mark the last voice as the group end */
        }
        iSNDleaveaudio();
        return (int)ret;
    }

fail:
    iSNDleaveaudio();
    for (i = 0; i < nAtFail; i++) /* roll back every voice started before the failure */
        SNDstop(started[i]);
    return (int)ret;
}
