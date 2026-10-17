/* game/common/object_externs.h -- cross-TU decls for object.cpp (track-object collision +
 *   custom-object pool + IMass props + ObjectMultiAnim/SignAnim animation classes).
 *   ObjectAnim inheritance and virtual methods are declared in nfs4_types.h */
#ifndef _GAME_COMMON_OBJECT_EXTERNS_H_
#define _GAME_COMMON_OBJECT_EXTERNS_H_
#include "../../nfs4_types.h"
#include "../../lib/libfns.h"
#include "new.h"

/* anim.obj free fns (demangled). AnimScript ctors/methods now called as C++ class members
 * (ctors via placement-new) -- the flat-mangled externs were removed (defs live in anim.obj). */
extern "C" int Anim_GetPos(Trk_AnimateInst *animInst, int flags, int ticks, coorddef *pt, int *animTicks, int *animLength);
extern "C" int Anim_GetRotPos(Trk_AnimateInst *animInst, int flags, int ticks, coorddef *pt, matrixtdef *mat);

/* ---- EXT data OWNED by object.obj (defined in object.cpp) ---- */
extern Group *Object_customObjInst;   /* 0x8013d2c8 */
extern Group *Object_customSimObjs;   /* 0x8013d2cc */
extern Group *Object_customSFXInst;   /* 0x8013d2d0 */
extern int Object_customSliceNum;     /* 0x8013d2d4 */
extern ObjectAnim *gSimObjAnims[450]; /* 0x.. status table [0..0x1c1] */
extern int gNumIMassObjects;
extern Object_tIMassObjInfo *Object_IMassObjInst;

/* ---- cross-TU globals ---- */
extern "C" Group *gPersistObjInst;         /* track.obj */
extern "C" Group *gPersistObjDef;          /* track.obj */
extern "C" Trk_ObjectDef **Track_gObjDefs; /* draww/track */
extern "C" Chunk *Track_chunkList;
extern Trk_NewSlice *BWorldSm_slices;
extern int gNumSlices;
extern "C" AnimDef gAnimDefs[14];
extern "C" SaveSurface *Track_gSaveSurface;
extern "C" Sim_tSimGlobalVar simGlobal;
extern "C" AIHigh_Traffic *highLevelAIObjs[]; /* per-car AI obj (accidentData_ @+0x20) */
extern Car_tObj *Cars_gTrafficCarList[];
extern int Cars_gNumTrafficCars;
extern Car_tObj *Cars_gCopCarList[];
extern int Cars_gNumCopCars;

/* ---- cross-TU fns ---- */
/* eaclib EACPSXZ fixdatan */
/* eaclib EACPSXZ fixdmult */
/* eaclib EACPSXZ trnsfrm */
/* eaclib EACPSXZ fxform */
/* eaclib EACPSXZ matrix */
/* eaclib EACPSXZ blkfill */
/* eaclib EACPSXZ memstd */
extern void Math_fasttransmult(matrixtdef *a, matrixtdef *b, matrixtdef *out); /* __FP10matrixtdefN20 */
extern int Math_DistXZ(coorddef *a, coorddef *b);
extern void Quatern_QuatToMat(tQuat *q, matrixtdef *m); /* quatern.obj */
extern void Quatern_MatToQuat(matrixtdef *m, tQuat *q);
extern int DrawObjectTransform(DRender_tView *Vi, Draw_DCache *sd, matrixtdef *matrix, Trk_ObjectDef *objDef, coorddef *cp, int offset, short flag); /* draww.obj */
extern int DrawW_GetAnimationTime(Trk_AnimateInst *animInst);
extern int BWorldSm_FindClosestQuadRez(coorddef *c, BWorldSm_Pos *pos, int rez); /* bworldsm.obj */
extern void BWorldSm_SetSlice(int slice, BWorldSm_Pos *pos);


#endif /* _GAME_COMMON_OBJECT_EXTERNS_H_ */
