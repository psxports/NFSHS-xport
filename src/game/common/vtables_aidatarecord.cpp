/* game/common/vtables_aidatarecord.cpp -- #75 data-materialization: AIDataRecord-family vtables (6).
 * Real nfs4-f.exe bytes; __vtbl_ptr_type; size = null-delimited rodata segment. @0xVA breadcrumbs.
 * CarTracking_t has 4 slots (virtual Get); others 3. NOT original layout; self-contained + links. */
#include "../../nfs4_types.h"
extern void __builtin_delete(void *);
extern "C" void __pure_virtual(void);   /* @0x800e4354 (eaclib cfront runtime) */

static void NFS4_VT_THUNK _vtdtor_AIDataRecord_AccTable_t(AIDataRecord_AccTable_t *p, int mode)
{
    p->~AIDataRecord_AccTable_t();
    if (mode & 1) __builtin_delete(p);
}
static void NFS4_VT_THUNK _vtdtor_AIDataRecord_BestLine_t(AIDataRecord_BestLine_t *p, int mode)
{
    p->~AIDataRecord_BestLine_t();
    if (mode & 1) __builtin_delete(p);
}
static void NFS4_VT_THUNK _vtdtor_AIDataRecord_CarTracking_t(AIDataRecord_CarTracking_t *p, int mode)
{
    p->~AIDataRecord_CarTracking_t();
    if (mode & 1) __builtin_delete(p);
}
static void NFS4_VT_THUNK _vtdtor_AIDataRecord_CurveSpeedTable_t(AIDataRecord_CurveSpeedTable_t *p, int mode)
{
    p->~AIDataRecord_CurveSpeedTable_t();
    if (mode & 1) __builtin_delete(p);
}
static void NFS4_VT_THUNK _vtdtor_AIDataRecord_TrackCurve_t(AIDataRecord_TrackCurve_t *p, int mode)
{
    p->~AIDataRecord_TrackCurve_t();
    if (mode & 1) __builtin_delete(p);
}
static void NFS4_VT_THUNK _vtdtor_AIDataRecord_t(AIDataRecord_t *p, int mode)
{
    p->~AIDataRecord_t();
    if (mode & 1) __builtin_delete(p);
}

__vtbl_ptr_type AIDataRecord_CarTracking_t_vtable[4] = {   /* @0x8005542c */
  {0, 0, NFS4_VTABLE_ENTRY(0)},                           /* @0x8005542c  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_AIDataRecord_CarTracking_t)}, /* @0x80055434  ~AIDataRecord_CarTracking_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_t::Setup)},      /* @0x8005543c  Setup__14AIDataRecord_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_CarTracking_t::Get)}, /* @0x80055444  Get__26AIDataRecord_CarTracking_ti */
};
__vtbl_ptr_type AIDataRecord_CurveSpeedTable_t_vtable[3] = {   /* @0x8005544c */
  {0, 0, NFS4_VTABLE_ENTRY(0)},                           /* @0x8005544c  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_AIDataRecord_CurveSpeedTable_t)}, /* @0x80055454  ~AIDataRecord_CurveSpeedTable_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_t::Setup)},      /* @0x8005545c  Setup__14AIDataRecord_t */
};
__vtbl_ptr_type AIDataRecord_TrackCurve_t_vtable[3] = {   /* @0x80055464 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},                           /* @0x80055464  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_AIDataRecord_TrackCurve_t)}, /* @0x8005546c  ~AIDataRecord_TrackCurve_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_t::Setup)},      /* @0x80055474  Setup__14AIDataRecord_t */
};
__vtbl_ptr_type AIDataRecord_BestLine_t_vtable[3] = {   /* @0x8005547c */
  {0, 0, NFS4_VTABLE_ENTRY(0)},                           /* @0x8005547c  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_AIDataRecord_BestLine_t)}, /* @0x80055484  ~AIDataRecord_BestLine_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_t::Setup)},      /* @0x8005548c  Setup__14AIDataRecord_t */
};
__vtbl_ptr_type AIDataRecord_AccTable_t_vtable[3] = {   /* @0x80055494 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},                           /* @0x80055494  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_AIDataRecord_AccTable_t)}, /* @0x8005549c  ~AIDataRecord_AccTable_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_AccTable_t::Setup)}, /* @0x800554a4  Setup__23AIDataRecord_AccTable_t */
};
__vtbl_ptr_type AIDataRecord_t_vtable[3] = {   /* @0x800554ac */
  {0, 0, NFS4_VTABLE_ENTRY(0)},                           /* @0x800554ac  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_AIDataRecord_t)},     /* @0x800554b4  ~AIDataRecord_t */
  {0, 0, NFS4_VTABLE_ENTRY(&AIDataRecord_t::Setup)},      /* @0x800554bc  Setup__14AIDataRecord_t */
};
