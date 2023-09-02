//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_copy_test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check compress copy logical", eve::test::simd::all_types)
<typename T>(tts::type<T>) {
  compress_copy_tst(eve::as<eve::logical<T>>{}, eve::compress_copy);
};
