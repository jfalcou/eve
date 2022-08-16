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
TTS_CASE_TPL("Check return types of two_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::two_pi(as<T>()), T);
  TTS_EXPR_IS(eve::two_pi(as<v_t>()), v_t);
};

//==================================================================================================
// two_pi  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::two_pi(as<T>()), T(8 * std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::two_pi)(as<T>()) <= eve::two_pi(as<T>())));
  TTS_EXPECT(eve::all(eve::two_pi(as<T>()) <= upward(eve::two_pi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::two_pi)(as<T>()), upward(eve::two_pi)(as<T>()), 0.5);
};
