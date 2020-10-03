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

TTS_CASE("Check eve::cotd return type")
{
  TTS_EXPR_IS(eve::cotd(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::cotd behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cotd(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cotd(eve::inf(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cotd(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::cotd(EVE_TYPE(0))  , eve::inf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::cotd(EVE_TYPE(-0.)), eve::minf(eve::as<EVE_TYPE>()));

  TTS_ULP_EQUAL(eve::cotd( EVE_TYPE(  1))   , EVE_TYPE(57.289961630759424687278147537112577980217522235144)    , 6);
  TTS_ULP_EQUAL(eve::cotd(-EVE_TYPE(  1))   , EVE_TYPE(-57.289961630759424687278147537112577980217522235144)   , 6);
  TTS_ULP_EQUAL(eve::cotd( EVE_TYPE( 45))   , EVE_TYPE(1)                                                      , 6);
  TTS_ULP_EQUAL(eve::cotd(-EVE_TYPE( 45))   , EVE_TYPE(-1)                                                     , 6);
  TTS_ULP_EQUAL(eve::cotd( EVE_TYPE(500.0)) , EVE_TYPE(-1.19175359259420995870530807186041933693070040770853)  , 6);
  TTS_ULP_EQUAL(eve::cotd(-EVE_TYPE(500.0)) , EVE_TYPE(1.19175359259420995870530807186041933693070040770853)   , 6);
}
