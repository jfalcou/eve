//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_copy_test.hpp"

#include <eve/module/core.hpp>

using test_types = eve::test::wides<tts::types<std::int16_t, std::uint16_t, std::int8_t, std::uint8_t>>::type;

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
using types = tts::filter<rvv_compress_filter, test_types>::type;
#else
using types = test_types;
#endif

TTS_CASE_TPL("Check compress copy logical", types)
<typename T>(tts::type<T>) {
  compress_copy_tst(eve::as<eve::logical<T>>{}, eve::compress_copy);
};
