#include "video.h"
#include "psx_press.h"
#include <new>
#include <vector>

extern "C" int ticks, timerhz;

struct NfshsVideo
{
    int file, width, height;
    uint32 reference, display, fraction, increment;
    VIDEOSTATE state;
    std::vector<uint32> chunk;
};

int NfshsVideoDecode(uint32 *bitstream, int width, int height, bool rgb24, int x, int y)
{
    if (!bitstream || width <= 0 || width > 640 || height <= 0 || height > 256)
        return 0;
    const int step = rgb24 ? 24 : 16;
    const int rows = (height + 15) & ~15;
    const int words = step * rows / 2;
    std::vector<uint32> vlc(65536), strip((size_t)words);
    DecDCTCallback previous = DecDCToutCallback(NULL);
    DecDCTCallback previous_input = DecDCTinCallback(NULL);
    DecDCTReset(0);
    DecDCTvlcSize(0);
    if (DecDCTvlc(bitstream, vlc.data()) != 0)
    {
        DecDCToutCallback(previous);
        DecDCTinCallback(previous_input);
        return 0;
    }
    DecDCTin(vlc.data(), rgb24 ? 3 : 2);
    for (int column = 0; column < width; column += 16)
    {
        DecDCTout(strip.data(), words);
        if (DecDCToutSync(0) != 0)
        {
            DecDCTReset(1);
            DecDCToutCallback(previous);
            DecDCTinCallback(previous_input);
            return 0;
        }
        PSX_RECT rect = {(sint16)(x + column * step / 16), (sint16)y,
                         (sint16)step, (sint16)height};
        LoadImagePSX(&rect, strip.data());
    }
    DrawSync(0);
    DecDCToutCallback(previous);
    DecDCTinCallback(previous_input);
    return 1;
}

intptr VIDEO_create(int width, int height, int fps, int streambuffersize, int)
{
    if (width <= 0 || height <= 0 || fps <= 0 || streambuffersize <= 0)
        return 0;
    NfshsVideo *video = new (std::nothrow) NfshsVideo();
    if (!video)
        return 0;
    video->file = -1;
    video->width = width;
    video->height = height;
    video->increment = (uint32)(((uint64)(uint32)timerhz * 10u << 32) / (uint32)fps);
    video->state = VIDEOSTATE_IDLE;
    return (intptr)video;
}

void VIDEO_abortplayback(intptr handle)
{
    NfshsVideo *video = (NfshsVideo *)handle;
    if (!video)
        return;
    if (video->file >= 0)
        PCclose(video->file);
    video->file = -1;
    video->state = VIDEOSTATE_IDLE;
    video->chunk.clear();
}

void VIDEO_destroy(intptr handle)
{
    VIDEO_abortplayback(handle);
    delete (NfshsVideo *)handle;
}

void VIDEO_spoolfile(intptr handle, char *name)
{
    NfshsVideo *video = (NfshsVideo *)handle;
    if (!video || !name || video->state != VIDEOSTATE_IDLE)
        return;
    video->file = PCopen(name, 0, 0);
    if (video->file < 0)
        return;
    video->state = VIDEOSTATE_SPOOLING;
}

void VIDEO_startplayback(intptr handle)
{
    NfshsVideo *video = (NfshsVideo *)handle;
    if (!video || video->state != VIDEOSTATE_SPOOLING)
        return;
    video->reference = (uint32)ticks * 10u;
    video->display = video->fraction = 0;
    video->state = VIDEOSTATE_PLAYING;
}

extern "C" VIDEOSTATE VIDEO_state(intptr handle)
{
    NfshsVideo *video = (NfshsVideo *)handle;
    if (!video)
        return VIDEOSTATE_IDLE;
    if (video->state == VIDEOSTATE_SPOOLING)
        VIDEO_startplayback(handle);
    return video->state;
}

int VIDEO_updateframexy(intptr handle, int x, int y)
{
    NfshsVideo *video = (NfshsVideo *)handle;
    if (!video || video->state != VIDEOSTATE_PLAYING)
        return 0;
    const uint32 current = (uint32)ticks * 10u - video->reference;
    if (current < video->display)
        return 0;
    for (;;)
    {
        uint32 header[2];
        if (PCread(video->file, (char *)header, sizeof(header)) != sizeof(header))
        {
            VIDEO_abortplayback(handle);
            return 0;
        }
        const uint32 size = header[1] & 0x00ffffffu;
        if (size < 8u || size > 0x100000u)
        {
            VIDEO_abortplayback(handle);
            return 0;
        }
        video->chunk.assign((size + 3u) / 4u + 16u, 0);
        if (PCread(video->file, (char *)video->chunk.data(), (sint32)size - 8) != (sint32)size - 8)
        {
            VIDEO_abortplayback(handle);
            return 0;
        }
        const uint32 accumulated = video->fraction + video->increment;
        video->display += accumulated >> 16;
        video->fraction = accumulated & 0xffffu;
        if (current >= video->display || header[0] != 0x4443546du)
            continue;
        uint32 *payload = video->chunk.data();
        int width = (sint16)(payload[1] & 0xffffu), height = (sint16)(payload[1] >> 16);
        if (size < 28u || width > video->width || height > video->height ||
            !NfshsVideoDecode(payload + 2, width, height, false, x, y))
        {
            VIDEO_abortplayback(handle);
            return 0;
        }
        return 1;
    }
}
