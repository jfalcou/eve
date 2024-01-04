//revised
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
// inv_2eps Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of inv_2eps", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::inv_2eps(as<T>()), T);
  TTS_EXPR_IS(eve::inv_2eps(as<v_t>()), v_t);
};
//==================================================================================================
// inv_2eps tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of inv_2eps on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::inv_2eps[eve::downward](eve::as<T>()) <= 0.5/eve::eps(eve::as<T>()));
    TTS_EXPECT(eve::inv_2eps[eve::upward](eve::as<T>()) >= 0.5/eve::eps(eve::as<T>())); 
  }
  TTS_EQUAL(eve::inv_2eps(eve::as<T>()), T(0.5/eve::eps(eve::as<T>())));
};

//==================================================================================================
// inv_2eps  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of inv_2eps on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::inv_2eps[eve::downward](as<T>()), eve::inv_2eps[eve::upward](as<T>()))));
};
