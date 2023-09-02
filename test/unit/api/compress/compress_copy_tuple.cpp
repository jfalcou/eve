//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_copy_test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check compress copy behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>) {
  using e_t = kumi::tuple<std::int8_t, eve::element_type_t<T>, double>;
  compress_copy_tst(eve::as<eve::wide<e_t, typename T::cardinal_type>>{}, eve::compress_copy);
};
