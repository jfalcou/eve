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
// two_o_sqrt_pi Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of two_o_sqrt_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::two_o_sqrt_pi(as<T>()), T);
  TTS_EXPR_IS(eve::two_o_sqrt_pi(as<v_t>()), v_t);
};
//==================================================================================================
// two_o_sqrt_pi tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_o_sqrt_pi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::two_o_sqrt_pi[eve::downward](eve::as<T>()) <= 2.0/std::sqrt(3.141592653589793238462643l));
    TTS_EXPECT(eve::two_o_sqrt_pi[eve::upward](eve::as<T>()) >= 2.0/std::sqrt(3.141592653589793238462643l)); 
  }
  TTS_EQUAL(eve::two_o_sqrt_pi(eve::as<T>()), T(2.0/std::sqrt(3.141592653589793238462643l)));
};

//==================================================================================================
// two_o_sqrt_pi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_o_sqrt_pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::two_o_sqrt_pi[eve::downward](as<T>()), eve::two_o_sqrt_pi[eve::upward](as<T>()))));
};
