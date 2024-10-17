//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_test.hpp"
#include <eve/module/core.hpp>

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
using types = tts::filter<rvv_compress_filter, eve::test::simd::all_types>::type;
#else
using types = eve::test::simd::all_types;
#endif

TTS_CASE_WITH("Check compress wide diff logicals", types, tts::generate(tts::ramp(1)))
<typename T> (T data)
{
  using N = eve::fixed<T::size()>;
  smaller_test_for<eve::logical<eve::wide<std::uint8_t,  N>>>(data);
  smaller_test_for<eve::logical<eve::wide<std::uint16_t, N>>>(data);
  smaller_test_for<eve::logical<eve::wide<std::uint32_t, N>>>(data);
  smaller_test_for<eve::logical<eve::wide<std::uint64_t, N>>>(data);
};
