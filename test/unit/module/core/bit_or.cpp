//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/module/core/bit_test.hpp"

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::bit_or(scalar)", eve::test::scalar::all_types_wf16)
<typename T>(tts::type<T>)
{
  bit_test_scalar_return_type<T>(eve::bit_or);
};

TTS_CASE_TPL("Check return types of eve::bit_or(simd)", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  bit_test_simd_return_type<T>(eve::bit_or);
};

//==================================================================================================
//  bit_or tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::bit_or",
              eve::test::simd::all_types_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a, T b)
{
  bit_test_simd(eve::bit_or, [](auto e, auto f) -> decltype(e) { return e | f; }, a, b);
};
