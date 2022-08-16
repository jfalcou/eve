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
TTS_CASE_TPL("Check return types of sqrt_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrt_2(as<T>()), T);
  TTS_EXPR_IS(eve::sqrt_2(as<v_t>()), v_t);
};

//==================================================================================================
// sqrt_2  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrt_2 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(downward(eve::sqrt_2)(as<elt_t>()) < std::sqrt(2.0l));
    TTS_EXPECT(upward(eve::sqrt_2)(as<elt_t>()) > std::sqrt(2.0l));
  }
  TTS_ULP_EQUAL(eve::sqrt_2(as<T>()), T(std::sqrt(2.0l)), 0.0);
  TTS_EXPECT(eve::all(downward(eve::sqrt_2)(as<T>()) <= eve::sqrt_2(as<T>())));
  TTS_EXPECT(eve::all(eve::sqrt_2(as<T>()) <= upward(eve::sqrt_2)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::sqrt_2)(as<T>()), upward(eve::sqrt_2)(as<T>()), 0.5);
};
