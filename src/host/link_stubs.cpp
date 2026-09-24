/* link_stubs.cpp -- native spelling of compiler-emitted MIPS break instructions.
 *
 * trap is not a retail function or LINK gap: the recovered calls represent the
 * in-line `break 7`, `break 6` and explicit `break 1,0x266` instructions.  The
 * native implementation must therefore raise a synchronous processor trap and
 * must never return to the guarded division/assertion path.
 */
#if defined(_MSC_VER)
#include <intrin.h>
#endif

static void nfs4_compiler_trap(void)
{
#if defined(_MSC_VER)
    __debugbreak();
#else
    __builtin_trap();
#endif
}

void trap(int code)          { (void)code; nfs4_compiler_trap(); }
void trap(unsigned int code) { (void)code; nfs4_compiler_trap(); }
