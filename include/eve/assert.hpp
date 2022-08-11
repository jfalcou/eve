//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#undef EVE_ASSERT
#undef EVE_VERIFY

#if defined(EVE_DISABLE_ASSERTS) || defined(NDEBUG)

#  define EVE_ASSERT(cond, ...) ((void)0)
#  define EVE_VERIFY(cond, ...) ((void)(cond))

#else

#  include <iostream>

#  define EVE_ASSERT(cond, ...)                                                                     \
    do                                                                                              \
    {                                                                                               \
      if(!(cond))                                                                                   \
      {                                                                                             \
        std::cerr << "[EVE] - Assertion '" << #cond                                                 \
                  << "' failed !\nIn file " << __FILE__ << ", line " << __LINE__                    \
                  << "\nBecause:\n" << __VA_ARGS__ << "\n";                                         \
        std::abort();                                                                               \
      }                                                                                             \
    } while(0)                                                                                      \
/**/

#  define EVE_VERIFY(cond, ...) EVE_ASSERT(cond, __VA_ARGS__)

#endif
