//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/arch/spec.hpp>

TTS_CASE("Check eve::current_api selection")
{
# if defined(EVE_NO_SIMD)
  TTS_EQUAL     ( eve::current_api  , eve::undefined_simd );
  TTS_EXPECT_NOT( eve::supports_simd                      );
# else
  TTS_NOT_EQUAL ( eve::current_api  , eve::undefined_simd );
  TTS_EXPECT    ( eve::supports_simd                      );
# endif
};
