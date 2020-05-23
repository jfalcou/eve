//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotd.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::restricted_(eve::cotd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::cotd)(T()), T);
}

TTS_CASE_TPL("Check eve::restricted_(eve::cotd) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)(eve::Inf<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  auto ref_cotd = [](auto e) { return eve::cotpi(double(e) / 180); };

  TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)(T(0))    , eve::Inf<T>() );
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)(T(-0.))  , eve::Minf<T>());
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)( T(90.0)), eve::Nan<T>() );
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotd)(-T(90.0)), eve::Nan<T>() );

  TTS_ULP_EQUAL(eve::restricted_(eve::cotd)( T( 1)) , T(ref_cotd(1.0))  , 3.0);
  TTS_ULP_EQUAL(eve::restricted_(eve::cotd)(-T( 1)) , T(ref_cotd(-1.0)) , 3.0);
  TTS_ULP_EQUAL(eve::restricted_(eve::cotd)( T(45)) , T(ref_cotd(45.0)) , 3.0);
  TTS_ULP_EQUAL(eve::restricted_(eve::cotd)(-T(45)) , T(ref_cotd(-45.0)), 3.0);
}
