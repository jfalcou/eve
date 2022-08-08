//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of oneosqrteps", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::oneosqrteps(as<T>()), T);
  TTS_EXPR_IS(eve::oneosqrteps(as<v_t>()), v_t);
};

//==================================================================================================
// oneosqrteps  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of oneosqrteps on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::oneosqrteps(as<T>()), T(1.0l / std::sqrt(eve::eps(as<eve::element_type_t<T>>()))));
  TTS_EXPECT(eve::all(downward(eve::oneosqrteps)(as<elt_t>())
                      <= std::sqrt(1.0l / (long double)(eve::eps(as<elt_t>())))));
  TTS_EXPECT(eve::all(upward(eve::oneosqrteps)(as<elt_t>())
                      >= std::sqrt(1.0l / (long double)(eve::eps(as<elt_t>())))));
  TTS_EXPECT(eve::all(downward(eve::oneosqrteps)(as<T>()) <= eve::oneosqrteps(as<T>())));
  TTS_EXPECT(eve::all(eve::oneosqrteps(as<T>()) <= upward(eve::oneosqrteps)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::oneosqrteps)(as<T>()), upward(eve::oneosqrteps)(as<T>()), 0.5);
};
