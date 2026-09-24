/* eaclib/psx/sndpsxz/smasterv.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\smasterv.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   1 fn @0x800E7FF0.  SNDmastervol -- set the global master volume and re-derive every voice's SPU volume.
 *   Ghidra nfs4-f.exe.c (smasterv).
 */
#include "../../../lib/snd.h"

extern "C" int SNDmastervol(int vol); /* @0x800E7FF0 */

/* SNDmastervol @0x800E7FF0 : store the master volume (sndgs[0xf]._1_1_) and refresh all held voices. */
extern "C" int SNDmastervol(int vol)
{
    int chan;
    if (SND->enabled == 0)
        return -10;
    iSNDenteraudio();
    SND->f3D = (signed char)vol;
    chan = 0;
    if (SND->patchcount != 0)
    {
        do
        {
            SndVoice *slot = &SND->voices[chan];
            if (slot->f0B == 1 && -1 < slot->handle)
            {
                iSNDcalcvol(chan);
                iSNDvol(chan, (int)slot->vol_l);
            }
            chan++;
        } while (chan < (int)(unsigned int)SND->patchcount);
    }
    iSNDleaveaudio();
    return 0;
}
