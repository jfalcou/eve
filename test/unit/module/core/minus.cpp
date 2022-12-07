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
TTS_CASE_TPL("Check return types of eve::minus", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::minus(T()), T);
  TTS_EXPR_IS(eve::minus[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::minus[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::minus[bool()](T()), T);

  TTS_EXPR_IS(eve::saturated(eve::minus)(T()), T);
  TTS_EXPR_IS(eve::saturated(eve::minus[eve::logical<T>()])(T()), T);
  TTS_EXPR_IS(eve::saturated(eve::minus[eve::logical<v_t>()])(T()), T);
  TTS_EXPR_IS(eve::saturated(eve::minus[bool()])(T()), T);

  TTS_EXPR_IS(eve::minus(v_t()), v_t);
  TTS_EXPR_IS(eve::minus[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::minus[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::minus[bool()](v_t()), v_t);

  TTS_EXPR_IS(eve::saturated(eve::minus)(v_t()), v_t);
  TTS_EXPR_IS(eve::saturated(eve::minus[eve::logical<T>()])(v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::minus[eve::logical<v_t>()])(v_t()), v_t);
  TTS_EXPR_IS(eve::saturated(eve::minus[bool()])(v_t()), v_t);

  if constexpr( eve::floating_ordered_value<T> ) {}
};

//==================================================================================================
// Tests for eve::minus
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::minus(eve::wide)",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(-10, +10), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::minus(a0), map([](auto e) -> v_t { return -e; }, a0));
  TTS_EQUAL(eve::minus[mask](a0), eve::if_else(mask, eve::minus(a0), a0));
};

//==================================================================================================
// Tests for eve::saturated(eve::minus)
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::saturated(eve::minus)(eve::wide)",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;

  TTS_EQUAL(eve::saturated(eve::minus)(a0),
            map([](auto e)
                { return e == eve::valmin(eve::as(e)) ? eve::valmax(eve::as(e)) : eve::minus(e); },
                a0));
  TTS_EQUAL(eve::saturated(eve::minus[mask])(a0),
            eve::if_else(mask, eve::saturated(eve::minus)(a0), a0));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::minus variants on wide",
             eve::test::simd::signed_types)
<typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  if constexpr( eve::floating_ordered_value<T> )
  {
    TTS_IEEE_EQUAL(eve::minus(cases.nan), cases.nan);
    TTS_IEEE_EQUAL(eve::minus(cases.minf), cases.inf);
    TTS_EQUAL(eve::minus(cases.mzero), T(0));
    TTS_EQUAL(eve::minus(cases.valmin), cases.valmax);
    TTS_EQUAL(eve::minus(cases.valmax), cases.valmin);
  }
  else
  {
    TTS_EQUAL(eve::saturated(eve::minus)(cases.valmin), cases.valmax);
    TTS_EQUAL(eve::minus(cases.valmax), cases.valmin + 1);
  }
};
