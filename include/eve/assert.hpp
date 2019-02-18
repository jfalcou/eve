
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#undef EVE_ASSERT
#undef EVE_VERIFY

#if defined(EVE_DISABLE_ASSERTS) || defined(NDEBUG)

#define EVE_ASSERT(cond, ... ) ((void)0)
#define EVE_VERIFY(cond, ... ) ((void)(cond))

#else

#include <cstdlib>
#include <iostream>

#define EVE_ASSERT(cond, ... )                                                                     \
do {                                                                                               \
  if (!(cond))                                                                                     \
  {                                                                                                \
    std::cerr << "Assertion '" << #cond << "' failed in " << __FILE__ << ":" << __LINE__ << " - "  \
              << __VA_ARGS__ << std::endl;                                                         \
    std::abort();                                                                                  \
  }                                                                                                \
} while(0)                                                                                         \
/**/

#define EVE_VERIFY(cond, ... ) EVE_ASSERT(cond,__VA_ARGS__)

#endif

#endif
