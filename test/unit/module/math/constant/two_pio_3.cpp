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
// two_pio_3 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of two_pio_3", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::two_pio_3(as<T>()), T);
  TTS_EXPR_IS(eve::two_pio_3(as<v_t>()), v_t);
};
//==================================================================================================
// two_pio_3 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_pio_3 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::two_pio_3[eve::downward](eve::as<T>()) <= 2.0*3.141592653589793238462643l/3);
    TTS_EXPECT(eve::two_pio_3[eve::upward](eve::as<T>()) >= 2.0*3.141592653589793238462643l/3); 
  }
  TTS_EQUAL(eve::two_pio_3(eve::as<T>()), T(2.0*3.141592653589793238462643l/3));
};

//==================================================================================================
// two_pio_3  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_pio_3 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::two_pio_3[eve::downward](as<T>()), eve::two_pio_3[eve::upward](as<T>()))));
};
