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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of maxlog10", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::maxlog10(as<T>()), T);
  TTS_EXPR_IS(eve::maxlog10(as<v_t>()), v_t);
};

//==================================================================================================
// maxlog10  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of maxlog10 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp10(eve::maxlog10(as<T>())), eve::inf(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog10(as<T>()))))));
  TTS_EXPECT(eve::all(eve::test::is_near(eve::maxlog10[eve::downward](as<T>()), eve::maxlog10[eve::upward](as<T>()))));
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog10(as<T>()))))));
};
