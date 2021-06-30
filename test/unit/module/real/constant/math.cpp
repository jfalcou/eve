//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/math.hpp>
#include <eve/platform.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log10.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/atan.hpp>

EVE_TEST_TYPES("Check math constants behavior"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::pi(as<T>()), 4*eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::pio_2(as<T>()), 2*eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::pio_4(as<T>()),   eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::sqrt_2(as<T>()), eve::sqrt(T(2)),0.5);
  TTS_ULP_EQUAL(eve::invsqrt_2(as<T>()), eve::sqrt(T(2))/2,0.5);
  TTS_ULP_EQUAL(eve::invlog_10(as<T>()), eve::rec(eve::log(T(10))),0.5);
  TTS_ULP_EQUAL(eve::invlog10_2(as<T>()), eve::rec(eve::log10(T(2))),0.5);
  TTS_ULP_EQUAL(eve::twopi(as<T>()), 8*eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::twoopi(as<T>()), eve::rec(eve::pio_2(as<T>())),0.5);
};
