//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gcd.hpp>
#include <tts/tests/types.hpp>
#include <numeric>

TTS_CASE_TPL("Check eve::gcd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::gcd(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::gcd behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::gcd(T(22), T( 10)) , T(eve::gcd(T(22), T(10))) );
  TTS_EQUAL(eve::gcd(T(22), T(-10)) , T(eve::gcd(T(22), T(10))) );
}
