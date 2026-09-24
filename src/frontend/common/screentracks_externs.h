/* frontend/screens/screentracks_externs.h - reconstructed externs. NOT original. */
#ifndef _FE_SCREENS_SCREENTRACKS_EXTERNS_H_
#define _FE_SCREENS_SCREENTRACKS_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"

/* --- globals --- */
extern "C" extern tfrontEnd frontEnd;
extern "C" int ticks;
extern tTrackManager trackManager;
extern tGlobalMenuDefs *menuDefs;
extern tFEApplication *FEApp;
extern "C" extern char *Paths_Paths[];
extern "C" u_char *&Render_gPacketPtr, *&Render_gPalettePtr;

/* --- storage owned by ScreenTracks.obj --- */
static short tvOrder[10] = {2, 7, 4, 8, 1, 6, 0, 9, 3, 5}; /* STAT @0x800520a0 */
static char gSwapFileName[20];                             /* STAT @0x80052ca0 */
tScreenTrackSelect *screenTrackSelect;                     /* EXT  @0x800520b4 (runtime-set) */

/* --- PSX video player (nfs4::FRONTEND::PSX::video) --- */
intptr VIDEO_create(int w, int h, int a, int b, int c);
extern "C"
{
    int VIDEO_state(intptr h);
}
int VIDEO_updateframexy(intptr h, int x, int y);
void VIDEO_spoolfile(intptr h, char *name);
void VIDEO_startplayback(intptr h);
void VIDEO_abortplayback(intptr h);
void VIDEO_destroy(intptr h);

/* --- PsyQ / syslib --- */

/* --- FE draw / text / effect --- */
extern "C"
{
    void DrawShape_NFS4RoundRectangle(int textValue, PSX_RECT *r, short s);
}
void FETextRender_MenuTextPositionedJustify(short index, short x, short y, short justify, tMenuTextState state, tMenuTextType type);
void PSXDrawTransSquare(int col, int x, int y, int w, int h, short opacity);
void FeDraw_SetABRMode(int abr);
void *Front_EnableLocalSpeech();

/* --- list iterator / track manager (called as free fns) --- */
short TextValue(tListIteratorTrack *it, tPlayer p);
extern "C"
{
    void Decrement(tListIteratorTrack *it, tPlayer p);
}
void Increment(tListIteratorTrack *it, tPlayer p);
void GetTrack(tTrackManager *tm, u_short track, tTrackInformation *out);

/* --- tScreen helpers (non-member; base passed explicitly) --- */
extern "C"
{
    BOOL IsShapeFileLoaded(tScreen *s, tShapeInformation *shp);
}
extern "C"
{
    void UploadSwapShapes(tScreen *s, int n);
}
void AsyncLoadSwapShapeFile(tScreen *s, char *name);
void DrawBackgroundImage(tScreen *s, int startShape, int numShapes, tTexture_ShapeInfo *shapes, int flip);

/* --- tVideoWall methods (free-fn form; called on this->fVideoWall) --- */
void TurnOn(tVideoWall *vw);
void TurnOff(tVideoWall *vw);
void TurnOffInstant(tVideoWall *vw);
void Initialize(tVideoWall *vw, tTVConfig *cfgs, tTexture_ShapeInfo *shapes, short a, short b, short *order, short c);
void SetAvailableText(tVideoWall *vw, short a, short b, short c);
void SetAvailableIcon(tVideoWall *vw, short a, short b, short c, short d, tTexture_ShapeInfo *shapes);
void SetAvailable(tVideoWall *vw, u_short avail);
void UpdateImages(tVideoWall *vw);
void UpdateTransition(tVideoWall *vw);
void Draw(tVideoWall *vw);

#endif
