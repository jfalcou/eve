//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_store_test.hpp"
#include <eve/module/core.hpp>

TTS_CASE_WITH( "Check compress store behavior"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1))
        )
<typename T> ([[maybe_unused]]T data)
{
#if !defined(SPY_SIMD_IS_ARM_FIXED_SVE)
  all_tests_for_v<eve::logical<T>>(data);
#else
  TTS_PASS("Not tested for SVE at the moment");
#endif
};
