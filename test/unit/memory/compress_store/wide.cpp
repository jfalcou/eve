//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "compress_store_test.hpp"
#include <eve/module/core.hpp>

TTS_CASE_WITH( "Check compress store behavior"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1))
        )
<typename T> (T data)
{
  all_tests_for_v<eve::logical<T>>(data);
};
