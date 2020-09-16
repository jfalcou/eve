//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/deginrad.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <tts/tts.hpp>

TTS_CASE_TPL("Check deginrad return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::deginrad(T()),  T);
}

TTS_CASE_TPL("Check eve::deginrad behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::deginrad(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::deginrad(eve::minf(eve::as<T>())) , eve::minf(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::deginrad(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) , 0.5);
  }

  TTS_ULP_EQUAL(eve::deginrad(T( 0)), T( 0 )                                , 0.5);
  TTS_ULP_EQUAL(eve::deginrad(T( 1)), T(0.017453292519943295769236907684886), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(T(10)), T(0.17453292519943295769236907684886) , 0.5);
}
