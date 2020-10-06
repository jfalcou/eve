//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/math.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log10.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/atan.hpp>

TTS_CASE_TPL("Check basic constants behavior", EVE_TYPE)
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
}
