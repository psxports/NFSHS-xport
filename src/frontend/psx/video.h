/* frontend/psx/video.h - reconstructed (declarations for VIDEO.CPP) */
#ifndef _FRONTEND_PSX_VIDEO_H_
#define _FRONTEND_PSX_VIDEO_H_
#include "../../nfs4_types.h" /* VIDEOSTRUCT(64B), STREAMCHUNKHDR(8B), VIDEOSTATE - video.obj-owned */

intptr VIDEO_create(int width, int height, int fps, int streambuffersize, int memtype);
void VIDEO_destroy(intptr handle);
void VIDEO_spoolfile(intptr handle, char *fname);
void VIDEO_startplayback(intptr handle);
void VIDEO_abortplayback(intptr handle);
extern "C"
{
    VIDEOSTATE VIDEO_state(intptr handle);
}
int VIDEO_updateframexy(intptr handle, int x, int y);
void videoupdatetime(VIDEOSTRUCT *vid);
int videodecode(VIDEOSTRUCT *vid, STREAMCHUNKHDR *chunk, int x, int y);

#endif /* _FRONTEND_PSX_VIDEO_H_ */
