//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::maximum(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::maximum(T()), v_t);
  TTS_EXPR_IS(eve::maximum[eve::splat](T()), T);
};

//==================================================================================================
// Tests for eve::maximum
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::maximum(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  v_t max_value = a0.front();
  for( int i = 1; i != T::size(); ++i ) { max_value = std::max(max_value, a0.get(i)); }

  TTS_EQUAL(eve::maximum(a0), max_value);
  TTS_EQUAL(eve::maximum[eve::splat](a0), T(max_value));
};
