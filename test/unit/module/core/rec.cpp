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
TTS_CASE_TPL("Check return types of eve::rec", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::rec(T()), T);
  TTS_EXPR_IS(eve::rec[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::rec[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::rec[bool()](T()), T);

  TTS_EXPR_IS(eve::rec(v_t()), v_t);
  TTS_EXPR_IS(eve::rec[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::rec[bool()](v_t()), v_t);

  if constexpr( eve::floating_value<T> ) {}
};

//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return eve::smallestposval(tgt)*10; });
auto maxi = tts::constant([](auto tgt) { return eve::valmax(tgt) / 10; });

//==================================================================================================
// Tests for eve::rec
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rec(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(mini, maxi), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::rec(a0),
                map([](auto e) -> v_t { return e ? v_t(1 / e) : eve::valmax(eve::as<v_t>()); }, a0),
                2.5);

  TTS_EQUAL(eve::rec[mask](a0), eve::if_else(mask, eve::rec(a0), a0));
  TTS_EQUAL(eve::rec[eve::raw2][mask](a0), eve::if_else(mask, eve::rec[eve::raw2](a0), a0));
  TTS_EQUAL(eve::rec[eve::pedantic2][mask](a0), eve::if_else(mask, eve::rec[eve::pedantic2](a0), a0));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::rec variants on wide", eve::test::simd::all_types)
  <typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(eve::rec(cases.nan), cases.nan, 0.5);
    TTS_ULP_EQUAL(eve::rec(cases.nan), cases.nan, 0.5);
    TTS_ULP_EQUAL(eve::rec(cases.minf), cases.mzero, 0.5);
    TTS_ULP_EQUAL(eve::rec(cases.inf) , cases.zero, 0.5);
    TTS_ULP_EQUAL(eve::rec(cases.mzero), cases.minf, 0.5);
    TTS_ULP_EQUAL(eve::rec(cases.zero), cases.inf, 0.5);
    TTS_ULP_EQUAL(eve::rec(eve::smallestposval(eve::as<T>())), T(1)/eve::smallestposval(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::rec(2*eve::smallestposval(eve::as<T>())), T(0.5)/eve::smallestposval(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::rec(eve::mindenormal(eve::as<T>())), T(1)/eve::mindenormal(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::rec(2*eve::mindenormal(eve::as<T>())), T(0.5)/eve::mindenormal(eve::as<T>()), 0.5);

    TTS_ULP_EQUAL(eve::rec[eve::pedantic2](cases.valmin), T(1)/cases.valmin, 0.5);
    TTS_ULP_EQUAL(eve::rec[eve::pedantic2](cases.valmax), T(1)/cases.valmax, 0.5);
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](cases.nan), cases.nan);
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](cases.minf), cases.mzero);
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](cases.inf) , cases.zero);
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](cases.mzero), cases.minf);
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](cases.zero), cases.inf);
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](eve::mindenormal(eve::as<T>())), T(1)/eve::mindenormal(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](2*eve::mindenormal(eve::as<T>())), T(1)/(2*eve::mindenormal(eve::as<T>())));
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](eve::smallestposval(eve::as<T>())), T(1)/eve::smallestposval(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::rec[eve::pedantic2](2*eve::smallestposval(eve::as<T>())), T(1)/(2*eve::smallestposval(eve::as<T>())));
  }
  else TTS_EQUAL(0, 0);


};
