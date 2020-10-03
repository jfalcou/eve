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
#include <tts/tts.hpp>

TTS_CASE("Check deginrad return type")
{
  TTS_EXPR_IS(eve::deginrad(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::deginrad behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::deginrad(eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()) , 0.5);
    TTS_ULP_EQUAL(eve::deginrad(eve::minf(eve::as<EVE_TYPE>())) , eve::minf(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve::deginrad(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  }

  TTS_ULP_EQUAL(eve::deginrad(EVE_TYPE( 0)), EVE_TYPE( 0 )                                , 0.5);
  TTS_ULP_EQUAL(eve::deginrad(EVE_TYPE( 1)), EVE_TYPE(0.017453292519943295769236907684886), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(EVE_TYPE(10)), EVE_TYPE(0.17453292519943295769236907684886) , 0.5);
}
