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
TTS_CASE_TPL("Check return types of eve::bit_notor(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  bit_test_scalar_return_type<T>(eve::bit_notor);
};

TTS_CASE_TPL("Check return types of eve::bit_notor(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  bit_test_simd_return_type<T>(eve::bit_notor);
};

//==================================================================================================
//  bit_notor tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::bit_notor",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a, T b)
{
  bit_test_simd(eve::bit_notor, [](auto e, auto f) -> decltype(e) { return ~e | f; }, a, b);
};
