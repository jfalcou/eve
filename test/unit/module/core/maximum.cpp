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
  TTS_EXPR_IS(eve::maximum(eve::logical<T>()), bool);
  TTS_EXPR_IS(eve::splat(eve::maximum)(T()), T);
  TTS_EXPR_IS(eve::splat(eve::maximum)(eve::logical<T>()), eve::logical<T>);
};

//==================================================================================================
// Tests for eve::maximum
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::maximum(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename L>(T const& a0, L const& l0)
{
  using v_t = eve::element_type_t<T>;

  v_t max_value = a0.front();
  for( int i = 1; i != T::size(); ++i ) { max_value = std::max(max_value, a0.get(i)); }

  TTS_EQUAL(eve::maximum(a0), max_value);
  TTS_EQUAL(eve::splat(eve::maximum)(a0), T(max_value));

  TTS_EQUAL(eve::maximum(l0), true);
  TTS_EQUAL(eve::splat(eve::maximum)(l0), L(true));

  TTS_EQUAL(eve::maximum[l0](a0), eve::maximum(eve::if_else(l0, a0, eve::valmin(eve::as(a0)))));
  TTS_EQUAL(eve::splat(eve::maximum[l0])(a0),
            T(eve::maximum(eve::if_else(l0, a0, eve::valmin(eve::as(a0))))));
};
