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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of remainder", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::remainder;

  // regular
  TTS_EXPR_IS(remainder(T(), T()), T);
  TTS_EXPR_IS(remainder(T(), v_t()), T);
  TTS_EXPR_IS(remainder(v_t(), T()), T);
  TTS_EXPR_IS(remainder(v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(remainder[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(remainder[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](v_t(), v_t()), v_t);
};

//==================================================================================================
//==  remainder simd tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -100 : 0; };

TTS_CASE_WITH("Check behavior of remainder on wide",
              eve::test::simd::ieee_reals
              ,
              tts::generate(tts::randoms(tts::constant(mini), 100),
                            tts::randoms(tts::constant(mini), 100)))
<typename T>(T a0, T a1)
{
  using eve::remainder;
  using eve::detail::map;

  auto thrs = std::same_as<eve::element_type_t<T>, float> ? 5e-4 : 5e-12;
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_RELATIVE_EQUAL(remainder(a0, a1), map([](auto e, auto f) { return std::remainder(e, f); }, a0, a1), thrs);
};


TTS_CASE_TPL("Check corner-cases behavior of eve::remainder",
             eve::test::simd::ieee_reals)
  <typename T>(tts::type<T> const& tgt)
{
  auto cases = tts::limits(tgt);
  TTS_IEEE_EQUAL(eve::remainder(cases.nan,   cases.nan), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.nan,   cases.one), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.one,   cases.nan), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.zero,  cases.one), cases.zero);
  TTS_IEEE_EQUAL(eve::remainder(cases.mzero, cases.one), cases.mzero);
  TTS_IEEE_EQUAL(eve::remainder(cases.zero,  cases.zero), cases.zero);
  TTS_IEEE_EQUAL(eve::remainder(cases.mzero, cases.zero), cases.zero);
  TTS_IEEE_EQUAL(eve::remainder(cases.inf,   cases.one), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.nan,   cases.one), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.inf,   cases.one), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.minf,  cases.one), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.one,   cases.inf), cases.nan);
  TTS_IEEE_EQUAL(eve::remainder(cases.one,   cases.minf), cases.nan);

};
