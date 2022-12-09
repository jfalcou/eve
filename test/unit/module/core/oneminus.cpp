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
TTS_CASE_TPL("Check return types of eve::oneminus", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::oneminus(T()), T);
  TTS_EXPR_IS(eve::oneminus[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::oneminus[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::oneminus[bool()](T()), T);

  TTS_EXPR_IS(eve::saturated(eve::oneminus)(T()), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[eve::logical<T>()])(T()), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[eve::logical<v_t>()])(T()), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[bool()])(T()), T);

  TTS_EXPR_IS(eve::oneminus(v_t()), v_t);
  TTS_EXPR_IS(eve::oneminus[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::oneminus[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::oneminus[bool()](v_t()), v_t);

  TTS_EXPR_IS(eve::saturated(eve::oneminus)(v_t()), v_t);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[eve::logical<T>()])(v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[eve::logical<v_t>()])(v_t()), v_t);
  TTS_EXPR_IS(eve::saturated(eve::oneminus[bool()])(v_t()), v_t);

  if constexpr( eve::floating_value<T> ) {}
};

//==================================================================================================
// Tests for eve::oneminus
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::oneminus(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(-10, +10), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::as;
  using eve::oneminus;
  using eve::saturated;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(oneminus(a0), map([](auto e) -> v_t { return 1 - e; }, a0));
  TTS_EQUAL(oneminus[mask](a0), eve::if_else(mask, oneminus(a0), a0));
  if constexpr( eve::unsigned_value<T> )
    TTS_EQUAL(saturated(oneminus)(a0),
              eve::if_else(eve::is_eqz(a0), eve::one(eve::as(a0)), eve::zero));
  else
    TTS_EQUAL(
        saturated(oneminus)(a0),
        eve::if_else(a0 < eve::valmin(eve::as(a0)) + 2, eve::valmax(eve::as(a0)), oneminus(a0)));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::oneminus variants on wide",
             eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::saturated(eve::oneminus)(T(1)), T(0));

  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(2)), T(-1));
    TTS_EQUAL(eve::saturated(eve::oneminus)(static_cast<T>(-2)), T(3));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::valmin(eve::as<T>())), eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::inc(eve::valmin(eve::as<T>()))),
              eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::inc(eve::inc(eve::valmin(eve::as<T>())))),
              eve::valmax(eve::as<T>()));
  }

  if constexpr( eve::unsigned_value<T> )
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(2)), T(0));
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(1)), T(0));
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(0)), T(1));
  }

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(-0.)), T(1));
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(0)), T(1));
  }
};
