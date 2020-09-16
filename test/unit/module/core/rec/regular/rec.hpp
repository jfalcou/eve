//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/sequence.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::rec return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::rec(T(0)), T);
}

TTS_CASE_TPL("Check eve::rec behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T> && eve::platform::supports_infinites)
  {
    TTS_ULP_EQUAL(eve::rec( T(-0.)), eve::minf(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::rec( T( 0 )), eve::inf(eve::as<T>())  , 0.5);
    TTS_ULP_EQUAL(eve::rec( T( 1 )), T(1)           , 0.5);
    TTS_ULP_EQUAL(eve::rec( T( 2 )), T(1./2.)       , 0.5);
  }
  else
  {
    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::rec(T(- 1)), T(-1));
      TTS_EQUAL(eve::rec(T(-47)), T( 0));
    }
    else
    {
      TTS_EQUAL(eve::rec(T(1)) , T(1));
      TTS_EQUAL(eve::rec(T(47)), T(0));
    }
  }
}
