//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sign", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sign(T()), T);
  TTS_EXPR_IS(eve::sign[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::sign[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::sign[bool()](T()), T);

  TTS_EXPR_IS(eve::sign(v_t()), v_t);
  TTS_EXPR_IS(eve::sign[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::sign[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::sign[bool()](v_t()), v_t);

  if constexpr( eve::floating_value<T> ) {}
};

//==================================================================================================
// Tests for eve::sign
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sign(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(-10, +10), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using eve::all;
  using eve::is_positive;
  using eve::is_negative;
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPECT( all(is_positive(eve::sign(eve::zero (eve::as(a0))))) );
    TTS_EXPECT( all(is_negative(eve::sign(eve::mzero(eve::as(a0))))) );
  }

  TTS_EQUAL(eve::sign(a0), map([](auto e) -> v_t { return e > 0 ? 1 : (e ? -1 : 0); }, a0));
  TTS_EQUAL(eve::sign[mask](a0), eve::if_else(mask, eve::sign(a0), a0));
};
