//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscd.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cscd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cscd(T()), T);
}

TTS_CASE_TPL("Check eve::cscd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cscd(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cscd(eve::Inf<T>())  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cscd(eve::Minf<T>()) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::cscd(T( 0 )) , eve::Inf<T>() );
  TTS_IEEE_EQUAL(eve::cscd(T(-0.)) , eve::Minf<T>());

  TTS_ULP_EQUAL(eve::cscd( T(1)  ) , T(57.298688498550185476612685755175779889969877177276)   , 5);
  TTS_ULP_EQUAL(eve::cscd(-T(1)  ) , T(-57.298688498550185476612685755175779889969877177276)  , 5);
  TTS_ULP_EQUAL(eve::cscd( T(45) ) , T(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::cscd(-T(45) ) , T(-1.41421356237309504880168872420969807856967187537694) , 5);
  TTS_ULP_EQUAL(eve::cscd( T(500)) , T(1.5557238268604123200563559546372533808211721914623)   , 5);
  TTS_ULP_EQUAL(eve::cscd(-T(500)) , T(-1.5557238268604123200563559546372533808211721914623)  , 5);
}
