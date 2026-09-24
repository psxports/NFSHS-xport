#ifndef NFSHS_DIAGNOSTICS_H
#define NFSHS_DIAGNOSTICS_H
#if defined(_MSC_VER)
    #include <intrin.h>
    #include <malloc.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define __builtin_alloca _alloca
    #define __builtin_return_address(level) ((void)(level), _ReturnAddress())
#endif
/* Standalone audit compiles retain historical Debug behavior. Production
   builds explicitly pass 0; this switch never changes PSX game arithmetic. */
#ifndef NFSHS_DIAGNOSTICS
    #define NFSHS_DIAGNOSTICS 1
#endif
#if NFSHS_DIAGNOSTICS
    #define NFSHS_DIAGNOSTIC_CALL(...) __VA_ARGS__
#else
    /* Arguments are deliberately not evaluated in Release. */
    #define NFSHS_DIAGNOSTIC_CALL(...) ((void)0)
#endif
#endif
