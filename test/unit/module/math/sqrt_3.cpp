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
TTS_CASE_TPL("Check return types of sqrt_3", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrt_3(as<T>()), T);
  TTS_EXPR_IS(eve::sqrt_3(as<v_t>()), v_t);
};

//==================================================================================================
// sqrt_3  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrt_3 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::sqrt_3[eve::downward](as<elt_t>()) < std::sqrt(3.0l));
    TTS_EXPECT(eve::sqrt_3[eve::upward](as<elt_t>()) > std::sqrt(3.0l));
  }
  TTS_IEEE_EQUAL(eve::sqrt_3(as<T>()), T(std::sqrt(3.0l)));
  TTS_EXPECT(eve::all(eve::sqrt_3[eve::downward](as<T>()) <= eve::sqrt_3(as<T>())));
  TTS_EXPECT(eve::all(eve::sqrt_3(as<T>()) <= eve::sqrt_3[eve::upward](as<T>())));
  TTS_ULP_EQUAL(eve::sqrt_3[eve::downward](as<T>()), eve::sqrt_3[eve::upward](as<T>()), 0.5);
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::sqrt_3[eve::downward](as<T>())), eve::sqrt_3[eve::upward](as<T>()))));
};
