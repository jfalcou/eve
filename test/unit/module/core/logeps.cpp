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
TTS_CASE_TPL("Check return types of logeps", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::logeps(as<T>()), T);
  TTS_EXPR_IS(eve::logeps(as<v_t>()), v_t);
};

//==================================================================================================
// logeps  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of logeps on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::logeps(as<T>()), T(std::log(eve::eps(as<eve::element_type_t<T>>()))));
  TTS_EXPECT(eve::all(downward(eve::logeps)(as<T>()) <= eve::logeps(as<T>())));
  TTS_EXPECT(eve::all(eve::logeps(as<T>()) <= upward(eve::logeps)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::logeps)(as<T>()), upward(eve::logeps)(as<T>()), 0.5);
};
