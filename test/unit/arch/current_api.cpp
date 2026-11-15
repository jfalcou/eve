//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/arch/spec.hpp>

TTS_CASE("Check eve::current_api selection")
{
# if defined(EVE_NO_SIMD)
  TTS_EQUAL     ( eve::current_api  , eve::undefined_simd );
  TTS_EXPECT_NOT( eve::platform::supports_simd            );
# else
  TTS_NOT_EQUAL ( eve::current_api  , eve::undefined_simd );
  TTS_EXPECT    ( eve::platform::supports_simd            );
# endif
};

#if (defined(SPY_SIMD_IS_ARM_SVE) || defined(SPY_SIMD_IS_ARM_SVE2)) && !defined(EVE_SIMD_IS_ANY_FIXED_SVE) \
    && !defined(EVE_NO_SIMD)
TTS_CASE("Check that SVE without a supported vector size falls back to ASIMD")
{
  TTS_EQUAL(eve::current_api, eve::asimd);
};
#endif
