//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::medium_(eve::sinpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::medium_(eve::sinpi)(T(0)), T);
}

TTS_CASE_TPL("Check eve::medium_(eve::sinpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::Minf<T>()), eve::nan(eve::as<T>()) );
  }

  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::sinpi)(T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::sinpi)(T(-0.)))));

  TTS_IEEE_EQUAL( eve::medium_(eve::sinpi)(T( 0.)), T(0) );
  TTS_IEEE_EQUAL( eve::medium_(eve::sinpi)(T(-0.)), T(0) );

  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(  1   )), T(0)  , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(- 1   )), T(0)  , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T( 22.5 )), T(1)  , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(-22.5 )), T(-1) , 0.5);

  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(100000.0))    , T(0), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(-100000.0))   , T(0), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(100000000.0)) , T(0), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)( T(-100000000.0)), T(0), 0.5);
}
