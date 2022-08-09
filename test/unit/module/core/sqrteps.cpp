//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sqrteps", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrteps(as<T>()), T);
  TTS_EXPR_IS(eve::sqrteps(as<v_t>()), v_t);
};

//==================================================================================================
// sqrteps  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrteps on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::sqrteps(as<T>()), T(std::sqrt(eve::eps(as<eve::element_type_t<T>>()))));
  TTS_EXPECT(eve::all(downward(eve::sqrteps)(as<elt_t>())
                      <= std::sqrt((long double)(eve::eps(as<elt_t>())))));
  TTS_EXPECT(eve::all(upward(eve::sqrteps)(as<elt_t>())
                      >= std::sqrt((long double)(eve::eps(as<elt_t>())))));
  TTS_EXPECT(eve::all(downward(eve::sqrteps)(as<T>()) <= eve::sqrteps(as<T>())));
  TTS_EXPECT(eve::all(eve::sqrteps(as<T>()) <= upward(eve::sqrteps)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::sqrteps)(as<T>()), upward(eve::sqrteps)(as<T>()), 0.5);
};
