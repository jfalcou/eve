//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/signgam.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::signgam return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::signgam(T(0)), T);
}

TTS_CASE_TPL("Check eve::signgam behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::signgam(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::signgam(eve::inf(eve::as<T>()))  , eve::one(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::signgam(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_EQUAL(eve::signgam(T(0.5)), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T(-35)), eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::signgam(T( 0 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T(-0.)), T(-1) );
  TTS_IEEE_EQUAL(eve::signgam(T( 1 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T( 2 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T( 3 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T( 5 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T( -1.1 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T( -2.1 )), T(-1) );
  TTS_IEEE_EQUAL(eve::signgam(T( -3.1 )), T(1) );
  TTS_IEEE_EQUAL(eve::signgam(T( -4.1 )), T(-1) );
  TTS_IEEE_EQUAL(eve::signgam(T( -5.1 )), T(1) );
}
