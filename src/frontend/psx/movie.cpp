#include "movie.h"
#include "video.h"
#include "psx_gpu.h"
#include "psx_stream.h"
#include "../../eaclib/psx/pad.h"
#include <vector>
#include <stdio.h>

extern "C" {
extern char *movienames[5];
extern int movie24bit[5];
extern short movieframes[6], user_exit;
extern char skip_all;
}

int play_movie(char movie)
{
    const unsigned index = (unsigned char)movie;
    if (index >= 5)
        return -1;
    char name[80];
    snprintf(name, sizeof(name), "MOVIES/%s", movienames[index]);
    int file = PCopen(name, 0, 0);
    if (file < 0)
        return -1;
    std::vector<uint32> ring(0x10000u / 4u);
    uint32 sector[512], *frame = NULL, *header = NULL;
    StSetRing(ring.data(), 32);
    StSetStream(movie24bit[index] != 0, 1, (uint32)movieframes[index], NULL, NULL);
    int result = 0, page = 0;
    while (!xport_isquit() && PCread(file, (char *)sector, sizeof(sector)) == sizeof(sector))
    {
        /* Rejected fragments resynchronize at the next frame's first sector */
        if (stream_feed_sector((uint8 *)sector, NULL) == -2)
        {
            result = -1;
            break;
        }
        if (StNextStatus(NULL, NULL) != StCOMPLETE)
            continue;
        if (StGetNext(&frame, &header) != 0)
            continue;
        StHEADER *info = (StHEADER *)header;
        const int width = info->width, height = info->height;
        const bool rgb24 = movie24bit[index] != 0;
        if (!NfshsVideoDecode(frame, width, height, rgb24, 0, page * 256))
        {
            StFreeRing(frame);
            result = -1;
            break;
        }
        StFreeRing(frame);
        DISPENV disp;
        SetDefDispEnv(&disp, 0, page * 256, width, height);
        disp.screen.h = 240;
        disp.isrgb24 = rgb24 ? 1 : 0;
        PutDispEnv(&disp);
        SetDispMask(1);
        gpu_present();
        xport_timer_wait_frame(15);
        xport_poll();
        psx_native_poll_events();
        PAD_update();
        const uint32 buttons = (PAD_state(0) | PAD_state(4)) & 0xffffu;
        if (buttons)
        {
            if (skip_all || buttons == 8)
                user_exit = 1;
            result = user_exit;
            break;
        }
        page ^= 1;
    }
    StUnSetRing();
    PCclose(file);
    return result;
}
