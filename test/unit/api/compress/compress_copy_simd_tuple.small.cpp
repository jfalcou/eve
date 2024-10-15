//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_copy_test.hpp"

#include <eve/module/core.hpp>

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
using types = tts::filter<rvv_compress_filter, eve::test::simd::all_types>::type;
#else
using types = eve::test::simd::all_types;
#endif

TTS_CASE_TPL("Check compress copy behavior", types)
<typename T>(tts::type<T>) {
  using e_t = kumi::tuple<std::int8_t, eve::element_type_t<T>, double>;
  compress_copy_tst(eve::as<eve::wide<e_t, typename T::cardinal_type>>{}, eve::compress_copy_simd);
};
