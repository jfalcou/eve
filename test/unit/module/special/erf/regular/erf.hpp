//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erf.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::erf return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::erf(T(0)), T);
}

TTS_CASE_TPL("Check eve::erf behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::erf(eve::minf(eve::as<T>())), T(-1), 0);
    TTS_ULP_EQUAL(eve::erf(eve::inf(eve::as<T>())), T(1), 0);
    TTS_ULP_EQUAL(eve::erf(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }


  TTS_ULP_EQUAL(eve::erf(T(-0.0)), T(0), 0);
  TTS_ULP_EQUAL(eve::erf(T(1)), T(0.842700792949714869341220635083), 0.5);
  TTS_ULP_EQUAL(eve::erf(T(2)), T(0.995322265018952734162069256367), 0);
  TTS_ULP_EQUAL(eve::erf(T(0)), T(0), 0);
  TTS_ULP_EQUAL(eve::erf(T(5)), T(0.99999999999846254020557196515), 0);
  TTS_ULP_EQUAL(eve::erf(T(27)), T(1), 0);

  TTS_ULP_EQUAL(eve::erf(-T(1)), -T(0.842700792949714869341220635083), 0.5);
  TTS_ULP_EQUAL(eve::erf(-T(2)), -T(0.995322265018952734162069256367), 0);
  TTS_ULP_EQUAL(eve::erf(-T(5)), -T(0.99999999999846254020557196515), 0);
  TTS_ULP_EQUAL(eve::erf(T(-27)), -T(1), 0);

  TTS_ULP_EQUAL(eve::erf(T(0.5)), T(0.520499877813046537682746653892), 0.5);
  TTS_ULP_EQUAL(eve::erf(T(0.1)), T(0.112462916018284892203275071744), 0);
  TTS_ULP_EQUAL(eve::erf(T(0.5)), T(0.520499877813046537682746653892), 0.5);
  TTS_ULP_EQUAL(eve::erf(-T(0.5)), -T(0.520499877813046537682746653892), 0.5);
  TTS_ULP_EQUAL(eve::erf(T(-0.1)), -T(0.112462916018284892203275071744), 0);
  TTS_ULP_EQUAL(eve::erf(eve::halfeps(eve::as<T>())), eve::eps(eve::as<T>())*eve::rsqrt(eve::pi(eve::as<T>())), 0);
  TTS_ULP_EQUAL(eve::erf(-eve::halfeps(eve::as<T>())), -eve::eps(eve::as<T>())*eve::rsqrt(eve::pi(eve::as<T>() )), 0);
  TTS_ULP_EQUAL(eve::erf(T(20)), T(1), 0);
}
