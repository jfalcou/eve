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

TTS_CASE("Check eve::restricted(eve::cotd) return type")
{
  TTS_EXPR_IS(eve::restricted(eve::cotd)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::restricted(eve::cotd) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::cotd)(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cotd)(eve::inf(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cotd)(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::cotd)(EVE_TYPE(0))    , eve::inf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cotd)(EVE_TYPE(-0.))  , eve::minf(eve::as<EVE_TYPE>()));
  TTS_IEEE_EQUAL(eve::restricted(eve::cotd)( EVE_TYPE(90.0)), eve::nan(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cotd)(-EVE_TYPE(90.0)), eve::nan(eve::as<EVE_TYPE>()) );

  TTS_ULP_EQUAL(eve::restricted(eve::cotd)( EVE_TYPE(  1))   , EVE_TYPE(57.289961630759424687278147537112577980217522235144)    , 1.0);
  TTS_ULP_EQUAL(eve::restricted(eve::cotd)(-EVE_TYPE(  1))   , EVE_TYPE(-57.289961630759424687278147537112577980217522235144)   , 1.0);
  TTS_ULP_EQUAL(eve::restricted(eve::cotd)( EVE_TYPE( 45))   , EVE_TYPE(1)                                                      , 1.0);
  TTS_ULP_EQUAL(eve::restricted(eve::cotd)(-EVE_TYPE( 45))   , EVE_TYPE(-1)                                                     , 1.0);
}
