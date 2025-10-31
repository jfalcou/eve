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
TTS_CASE_TPL("Check return types of eve::bit_notand(scalar)", eve::test::scalar::all_types_wf16)
<typename T>(tts::type<T>)
{
  bit_test_scalar_return_type<T>(eve::bit_notand);
};

TTS_CASE_TPL("Check return types of eve::bit_notand(simd)", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  bit_test_simd_return_type<T>(eve::bit_notand);
};

//==================================================================================================
//  bit_notand tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::bit_notand",
              eve::test::simd::all_types_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a, T b, T c)
{
  bit_test_simd(eve::bit_notand, [](auto e, auto f, auto... g) -> decltype(e) { return ~e & (f & ... & g); }, a, b, c);
};
