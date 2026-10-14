//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_copy_test.hpp"

#include <eve/module/core.hpp>

using test_types = eve::test::wides<tts::types<double, std::int64_t, std::uint64_t, float, std::int32_t, std::uint32_t>>::type;

TTS_CASE_TPL("Check compress copy behavior", simd_types_for_compress<test_types>)
<typename T>(tts::type<T>) {
  compress_copy_tst(eve::as<T>{}, eve::compress_copy_scalar);
};
