//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#undef EVE_ASSERT
#undef EVE_VERIFY

#if defined(EVE_DISABLE_ASSERTS) || defined(NDEBUG)

#  define EVE_ASSERT(cond, ...) ((void)0)
#  define EVE_VERIFY(cond, ...) ((void)(cond))

#else

#  include <cstdlib>
#  include <cstdio>

#define EVE_ASSERT_STRING(...)   TTS_STRING_((__VA_ARGS__))
#define EVE_ASSERT_STRING__(...) #__VA_ARGS__
#define EVE_ASSERT_STRING_(TXT)  TTS_STRING__ TXT

#  define EVE_ASSERT(cond, ...)                                                                     \
    do                                                                                              \
    {                                                                                               \
      if(!(cond))                                                                                   \
      {                                                                                             \
        std::fprintf ( stderr                                                                       \
                     , "Assertion '%s' failed in '%s':%d - %s\n"                                    \
                     , #cond, __FILE__, __LINE__, EVE_ASSERT_STRING__(__VA_ARGS__)                  \
                     );                                                                             \
        std::abort();                                                                               \
      }                                                                                             \
    } while(0)                                                                                      \
/**/

#  define EVE_VERIFY(cond, ...) EVE_ASSERT(cond, __VA_ARGS__)

#endif
