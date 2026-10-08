/* vtables_tlist.cpp -- #75 data-materialization: tList-family vtables (10), faithful member-cast.
 * Real nfs4-f.exe bytes and real method addresses; overloaded methods
 * use a typed member-pointer cast (ret from header, params from mangle). @0xVA breadcrumbs. */
#include "../../nfs4_types.h"
extern "C" void __pure_virtual(void);   /* @0x800e4354 (eaclib cfront runtime) */

static int NFS4_VT_THUNK _vtdtor_tListIterator(tListIterator *p){ p->~tListIterator(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorCar(tListIteratorCar *p){ p->~tListIteratorCar(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorCarColor(tListIteratorCarColor *p){ p->~tListIteratorCarColor(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorDoubleIndexed(tListIteratorDoubleIndexed *p){ p->~tListIteratorDoubleIndexed(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorIndexed(tListIteratorIndexed *p){ p->~tListIteratorIndexed(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorMultiPlayer(tListIteratorMultiPlayer *p){ p->~tListIteratorMultiPlayer(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorRange(tListIteratorRange *p){ p->~tListIteratorRange(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorRangeIndexed(tListIteratorRangeIndexed *p){ p->~tListIteratorRangeIndexed(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorTournament(tListIteratorTournament *p){ p->~tListIteratorTournament(); return 0; }
static int NFS4_VT_THUNK _vtdtor_tListIteratorTrack(tListIteratorTrack *p){ p->~tListIteratorTrack(); return 0; }

__vtbl_ptr_type tListIteratorCarColor_vtable[6] = {   /* @0x800101d8 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x800101d8  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorCarColor)},    /* @0x800101e0  ~tListIteratorCarColor */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCarColor::Value)},    /* @0x800101e8  Value__21tListIteratorCarColor7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCarColor::TextValue)},    /* @0x800101f0  TextValue__21tListIteratorCarColor7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCarColor::Increment)},    /* @0x800101f8  Increment__21tListIteratorCarColor7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCarColor::Decrement)},    /* @0x80010200  Decrement__21tListIteratorCarColor7tPlayer */
};
__vtbl_ptr_type tListIteratorCar_vtable[6] = {   /* @0x80010208 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80010208  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorCar)},    /* @0x80010210  ~tListIteratorCar */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCar::Value)},    /* @0x80010218  Value__16tListIteratorCar7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCar::TextValue)},    /* @0x80010220  TextValue__16tListIteratorCar7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCar::Increment)},    /* @0x80010228  Increment__16tListIteratorCar7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorCar::Decrement)},    /* @0x80010230  Decrement__16tListIteratorCar7tPlayer */
};
__vtbl_ptr_type tListIteratorDoubleIndexed_vtable[6] = {   /* @0x80011368 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80011368  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorDoubleIndexed)},    /* @0x80011370  ~tListIteratorDoubleIndexed */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorDoubleIndexed::Value)},    /* @0x80011378  Value__26tListIteratorDoubleIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorDoubleIndexed::TextValue)},    /* @0x80011380  TextValue__26tListIteratorDoubleIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorDoubleIndexed::Increment)},    /* @0x80011388  Increment__26tListIteratorDoubleIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorDoubleIndexed::Decrement)},    /* @0x80011390  Decrement__26tListIteratorDoubleIndexed7tPlayer */
};
__vtbl_ptr_type tListIteratorIndexed_vtable[6] = {   /* @0x80011398 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80011398  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorIndexed)},    /* @0x800113a0  ~tListIteratorIndexed */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorIndexed::Value)},    /* @0x800113a8  Value__20tListIteratorIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorIndexed::TextValue)},    /* @0x800113b0  TextValue__20tListIteratorIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorIndexed::Increment)},    /* @0x800113b8  Increment__20tListIteratorIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorIndexed::Decrement)},    /* @0x800113c0  Decrement__20tListIteratorIndexed7tPlayer */
};
__vtbl_ptr_type tListIteratorMultiPlayer_vtable[6] = {   /* @0x80011338 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80011338  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorMultiPlayer)},    /* @0x80011340  ~tListIteratorMultiPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorMultiPlayer::Value)},    /* @0x80011348  Value__24tListIteratorMultiPlayer7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorMultiPlayer::TextValue)},    /* @0x80011350  TextValue__24tListIteratorMultiPlayer7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorMultiPlayer::Increment)},    /* @0x80011358  Increment__24tListIteratorMultiPlayer7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorMultiPlayer::Decrement)},    /* @0x80011360  Decrement__24tListIteratorMultiPlayer7tPlayer */
};
__vtbl_ptr_type tListIteratorRangeIndexed_vtable[6] = {   /* @0x800112d8 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x800112d8  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorRangeIndexed)},    /* @0x800112e0  ~tListIteratorRangeIndexed */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRangeIndexed::Value)},    /* @0x800112e8  Value__25tListIteratorRangeIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRange::TextValue)},    /* @0x800112f0  TextValue__18tListIteratorRange7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRangeIndexed::Increment)},    /* @0x800112f8  Increment__25tListIteratorRangeIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRangeIndexed::Decrement)},    /* @0x80011300  Decrement__25tListIteratorRangeIndexed7tPlayer */
};
__vtbl_ptr_type tListIteratorRange_vtable[6] = {   /* @0x80011308 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80011308  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorRange)},    /* @0x80011310  ~tListIteratorRange */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRange::Value)},    /* @0x80011318  Value__18tListIteratorRange7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRange::TextValue)},    /* @0x80011320  TextValue__18tListIteratorRange7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRange::Increment)},    /* @0x80011328  Increment__18tListIteratorRange7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorRange::Decrement)},    /* @0x80011330  Decrement__18tListIteratorRange7tPlayer */
};
__vtbl_ptr_type tListIteratorTournament_vtable[6] = {   /* @0x80011670 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80011670  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorTournament)},    /* @0x80011678  ~tListIteratorTournament */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTournament::Value)},    /* @0x80011680  Value__23tListIteratorTournament7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTournament::TextValue)},    /* @0x80011688  TextValue__23tListIteratorTournament7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTournament::Increment)},    /* @0x80011690  Increment__23tListIteratorTournament7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTournament::Decrement)},    /* @0x80011698  Decrement__23tListIteratorTournament7tPlayer */
};
__vtbl_ptr_type tListIteratorTrack_vtable[6] = {   /* @0x80010fe8 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x80010fe8  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIteratorTrack)},    /* @0x80010ff0  ~tListIteratorTrack */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorIndexed::Value)},    /* @0x80010ff8  Value__20tListIteratorIndexed7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTrack::TextValue)},    /* @0x80011000  TextValue__18tListIteratorTrack7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTrack::Increment)},    /* @0x80011008  Increment__18tListIteratorTrack7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIteratorTrack::Decrement)},    /* @0x80011010  Decrement__18tListIteratorTrack7tPlayer */
};
__vtbl_ptr_type tListIterator_vtable[6] = {   /* @0x800113c8 */
  {0, 0, NFS4_VTABLE_ENTRY(0)},    /* @0x800113c8  null */
  {0, 0, NFS4_VTABLE_ENTRY(&_vtdtor_tListIterator)},    /* @0x800113d0  ~tListIterator */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIterator::Value)},    /* @0x800113d8  Value__13tListIterator7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIterator::TextValue)},    /* @0x800113e0  TextValue__13tListIterator7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIterator::Increment)},    /* @0x800113e8  Increment__13tListIterator7tPlayer */
  {0, 0, NFS4_VTABLE_ENTRY(&tListIterator::Decrement)},    /* @0x800113f0  Decrement__13tListIterator7tPlayer */
};
