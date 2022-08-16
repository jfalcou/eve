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
TTS_CASE_TPL("Check return types of minlog", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::minlog(as<T>()), T);
  TTS_EXPR_IS(eve::minlog(as<v_t>()), v_t);
};

//==================================================================================================
// minlog  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp(eve::minlog(as<T>())), eve::zero(as<T>()), 0.0);
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::next(eve::minlog(as<T>()))))));
};
