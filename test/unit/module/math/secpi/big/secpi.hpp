//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::big_(eve::secpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::secpi)(T()), T);
}

TTS_CASE_TPL("Check eve::big_(eve::secpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::secpi)(eve::Nan<T>()) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::secpi)(eve::Inf<T>()) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::secpi)(eve::Minf<T>()), eve::Nan<T>() );
  }

  TTS_IEEE_EQUAL(eve::big_(eve::secpi)(T( 0 )), T(1));
  TTS_IEEE_EQUAL(eve::big_(eve::secpi)(T(-0.)), T(1));

  TTS_ULP_EQUAL(eve::big_(eve::secpi)( T( 1))       ,-T(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)(-T( 1))       ,-T(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)( T(22.5))     , eve::Nan<T>() , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)(-T(22.5))     , eve::Nan<T>() , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)( T(100000.0)) , T(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)(-T(100000.0)) , T(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)( T(1000001.0)),-T(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::secpi)(-T(100001.0)) ,-T(1)          , 0.5);
}
