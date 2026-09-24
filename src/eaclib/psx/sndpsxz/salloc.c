/* eaclib/psx/sndpsxz/salloc.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 4/4 ***
 *   Source obj : nfs4\eaclib\psx\salloc.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   4 fns @[0x800FE724 .. 0x800FEDC4].  Sound-channel allocation/arbitration (no SPU pokes -- pure
 *   priority logic over the channel pool sndgs[0x25]).  Ghidra nfs4-f.exe.c L163749..164019.
 *
 *   Channel slot (100 bytes, pool base = sndgs[0x25], count = (byte)sndgs[0x11]):
 *     +0x00 owning tag (id|priority)   +0x0B in-use state (0 free / 1 held / 2 linked)
 *     +0x0C age   +0x10 alloc timestamp   +0x3C link-back   +0x3D..  voice fields
 */

#include "../../../nfs4_types.h"
#include "../../../lib/snd.h"
#include "../../../mips_semantics.h"

extern "C" unsigned char sndchanreserved[]; /* scratch list of chosen channel indices */
extern "C" int DAT_80136dec;                /* rolling allocation id counter (+=0x20)  */
extern "C" int SNDstop(int tag);            /* sstop  */
extern "C" int SNDover(unsigned int tag);   /* sover  */

extern "C" int iSNDischanreserved(int chan, int count); /* @0x800FE724 */

#define SNDNUMCHAN (SND->patchcount)

/* iSNDischanreserved @0x800FE724 : is channel `chan` already in the chosen list (first `count` entries)? */
extern "C" int iSNDischanreserved(int chan, int count)
{
    int i;
    for (i = 0; i < count; i++)
        if ((signed char)sndchanreserved[i] == chan)
            return 1;
    return 0;
}

/* iSNDallocchan @0x800FE764 : reserve `numChannels` voices for a sound, honouring the `priority` channel
 *   mask.  First takes idle channels (lowest timestamp), then -- if short -- steals the lowest-age /
 *   lowest-timestamp busy channels (stopping their current sound, rolling back on refusal).  Writes the
 *   allocation id to *out and returns the primary channel index, or -9 on failure.
 *     priority = channel-eligibility bitmask;  numChannels = voices needed;  a2 = a voice flag byte. */
extern "C" int iSNDallocchan(unsigned int priority, int numChannels, int a2, unsigned int *out)
{
    int reserved = 0;
    int result = -9;
    int i, k, off;
    unsigned int best, c, v, bestval;

    for (i = 0; i < numChannels; i++) /* clear the chosen list */
        sndchanreserved[i] = 0xff;

    DAT_80136dec = nfs4_mips_addu_s32(DAT_80136dec, 0x20); /* addiu: fresh allocation id */
    if (DAT_80136dec < 0)
        DAT_80136dec = 0;

    if (0 < numChannels)
    {
        /* pass 1: take idle channels (state 0), preferring the oldest (lowest +0x10) */
        for (i = 0; i < numChannels; i++)
        {
            best = 0xffffffff;
            c = 0;
            if (SNDNUMCHAN != 0)
            {
                bestval = 0xffffffff;
                do
                {
                    if ((priority & (1u << (c & 0x1f))) != 0)
                    {
                        SndVoice *ch = &SND->voices[c];
                        if (ch->f0B == 0 && iSNDischanreserved(c, reserved) == 0)
                        {
                            v = (unsigned int)ch->f10;
                            if (v < bestval)
                            {
                                best = c;
                                bestval = v;
                            }
                        }
                    }
                    c++;
                } while ((int)c < (int)(unsigned)SNDNUMCHAN);
            }
            if (-1 < (int)best)
            {
                sndchanreserved[reserved] = (unsigned char)best;
                reserved++;
            }
        }
        /* pass 2: short of channels -> steal busy ones by lowest (age, timestamp) */
        for (k = reserved; k < numChannels; k++)
        {
            unsigned char bestage = 0x66;
            unsigned int bestv = 0xffffffff;
            v = 0;
            best = 0xffffffff;
            if (SNDNUMCHAN != 0)
            {
                c = 0;
                do
                {
                    if ((priority & (1u << (c & 0x1f))) != 0 && iSNDischanreserved(c, reserved) == 0)
                    {
                        SndVoice *ch = &SND->voices[c];
                        if (ch->f0C < 0x65)
                        {
                            unsigned char age = ch->f0C;
                            if (age < bestage)
                            {
                                v = (unsigned int)ch->f10;
                                bestage = age;
                            }
                            else if (age != bestage || (v = (unsigned int)ch->f10, bestv <= v))
                            {
                                goto next2;
                            }
                            best = c;
                            bestv = v;
                        }
                    }
                next2:
                    c++;
                } while ((int)c < (int)(unsigned)SNDNUMCHAN);
            }
            if (-1 < (int)best)
            {
                sndchanreserved[reserved] = (unsigned char)best;
                reserved++;
                if (numChannels <= reserved)
                    break;
            }
        }
    }

    if (reserved == numChannels)
    { /* got them all -> commit */
        *out = DAT_80136dec | (int)(signed char)sndchanreserved[0];
        result = (int)(signed char)sndchanreserved[0];
        i = 0;
        if (0 < reserved)
        {
            do
            {
                SndVoice *ch = &SND->voices[(signed char)sndchanreserved[i]];
                unsigned int owner = (unsigned int)ch->handle;
                if (ch->f0B == 1)
                { /* currently held -> stop it */
                    if ((int)owner < 0)
                        owner = (unsigned int)SND->voices[ch->f3C].handle;
                    SNDstop(nfs4_mips_bits_to_s32(owner));
                    if (SNDover(owner) != 1)
                    { /* refused -> roll back */
                        while (i = i - 1, -1 < i)
                            SND->voices[(signed char)sndchanreserved[i]].f0B = 0;
                        return -9;
                    }
                }
                ch->f0B = 1;
                ch->f10 = SND->f44;          /* timestamp */
                ch->f0C = (unsigned char)a2; /* voice flag byte */
                i++;
            } while (i < reserved);
        }
        /* link the secondary channels to the primary */
        SndVoice *primary = &SND->voices[(signed char)sndchanreserved[0]];
        primary->handle = (int)*out;
        for (i = 1; i < reserved; i++)
        {
            ((unsigned char *)&primary->f04)[i - 1] = sndchanreserved[i];
            SndVoice *secondary = &SND->voices[(signed char)sndchanreserved[i]];
            secondary->handle = -1;
            secondary->f3C = (signed char)sndchanreserved[0];
        }
    }
    return result;
}

/* iSNDfreechan @0x800FEC0C : release channel `chan`.  Honours linked-channel groups (a stereo/multi voice
 *   only frees when its partners are also done).  Returns the freed channel / 2 (still linked) / timestamp. */
extern "C" intptr iSNDfreechan(int chan)
{
    SndVoice *voice = &SND->voices[chan];
    int group = 0;
    int partner = -1;
    int idx;

    if (voice->f37 == 0)
    { /* not part of a link group */
        voice->f0B = 0;
        voice->f10 = SND->f44;
        return (intptr)SND->f44;
    }

    idx = 0;
    if (SNDNUMCHAN != 0)
    {
        do
        {
            SndVoice *p = &SND->voices[idx];
            if (p->f37 == voice->f37 && p->handle >= 0 && p->f0B != 0 && (group = group + 1, p->f36 != 0))
                partner = idx;
            idx++;
        } while (idx < (int)(unsigned)SNDNUMCHAN);
    }
    if (group != 1)
    {
        SndVoice *partnerVoice = &SND->voices[partner];
        if (partnerVoice->f0B == 2 && chan != partner && group == 2)
        {
            voice->f0B = 0;
            voice->f10 = SND->f44;
            partnerVoice->f0B = 0;
            partnerVoice->f10 = SND->f44;
            return (intptr)partnerVoice;
        }
        if (partnerVoice->f0B == 1 && chan == partner)
        {
            partnerVoice->f0B = 2;
            return 2;
        }
    }
    voice->f0B = 0;
    voice->f10 = SND->f44;
    return (intptr)SND->f44;
}

/* iSNDgetchan @0x800FEDC4 : resolve a sound tag back to its channel index, validating that the channel is
 *   still held by that exact tag.  Returns the channel, or a negative error. */
extern "C" int iSNDgetchan(int tag)
{
    unsigned int ch;
    if (tag >= 0 && (ch = (unsigned int)tag & 0x1f) < (unsigned)SNDNUMCHAN)
    {
        SndVoice *slot = &SND->voices[ch];
        if (slot->f0B == 0 || slot->handle != tag)
            ch = 0xfffffff8;
        return ch;
    }
    return -8;
}
