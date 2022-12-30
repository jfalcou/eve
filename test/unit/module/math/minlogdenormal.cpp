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
TTS_CASE_TPL("Check return types of minlogdenormal", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::minlogdenormal(as<T>()), T);
  TTS_EXPR_IS(eve::minlogdenormal(as<v_t>()), v_t);
};

//==================================================================================================
// minlogdenormal  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlogdenormal on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::exp(eve::minlogdenormal(as<T>())), eve::zero(as<T>()), 0.0);
};
