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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of invsqrt_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::invsqrt_2(as<T>()), T);
  TTS_EXPR_IS(eve::invsqrt_2(as<v_t>()), v_t);
};
//==================================================================================================
// invsqrt_2  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of invsqrt_2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::invsqrt_2[eve::downward](as<elt_t>()) <= (1.0l / (std::sqrt(2.0l))));
    TTS_EXPECT(eve::invsqrt_2[eve::upward](as<elt_t>()) >= (1.0l / (std::sqrt(2.0l))));
  }
  TTS_ULP_EQUAL(eve::invsqrt_2(as<T>()), T(1.0l / (std::sqrt(2.0l))), 0.5);
};

//==================================================================================================
// invsqrt_2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of invsqrt_2 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::invsqrt_2[eve::upward](as<T>()) >= eve::invsqrt_2(as<T>())));
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::invsqrt_2[eve::downward](as<T>())), eve::invsqrt_2[eve::upward](as<T>()))));
};
