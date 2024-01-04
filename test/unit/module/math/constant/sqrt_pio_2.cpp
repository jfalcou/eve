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
// sqrt_pio_2 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sqrt_pio_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrt_pio_2(as<T>()), T);
  TTS_EXPR_IS(eve::sqrt_pio_2(as<v_t>()), v_t);
};
//==================================================================================================
// sqrt_pio_2 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrt_pio_2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::sqrt_pio_2[eve::downward](eve::as<T>()) <= std::sqrt(3.141592653589793238462643l/2));
    TTS_EXPECT(eve::sqrt_pio_2[eve::upward](eve::as<T>()) >= std::sqrt(3.141592653589793238462643l/2)); 
  }
  TTS_EQUAL(eve::sqrt_pio_2(eve::as<T>()), T(std::sqrt(3.141592653589793238462643l/2)));
};

//==================================================================================================
// sqrt_pio_2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrt_pio_2 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::sqrt_pio_2[eve::downward](as<T>()), eve::sqrt_pio_2[eve::upward](as<T>()))));
};
