#ifndef PRAGMAS_PRAGMA_HPP_INCLUDED
#define PRAGMAS_PRAGMA_HPP_INCLUDED
#include <eve/detail/spy.hpp>

#if defined(SPY_COMPILER_IS_GCC)

#  define EVE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA                                                 \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")           \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")

#  define EVE_RESTORE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA
_Pragma("GCC diagnostic pop")

#elif defined(SPY_COMPILER_IS_CLANG)

#  define EVE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA                                                 \
    _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wuninitialized\"")

#  define EVE_RESTORE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA _Pragma("clang diagnostic pop")

#else

#  define EVE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA
#  define EVE_RESTORE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA

#endif

#endif
