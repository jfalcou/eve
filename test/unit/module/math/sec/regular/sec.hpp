//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::sec return type")
{
  TTS_EXPR_IS(eve::sec(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::sec behavior")
{
  auto ref_sec =  [](auto x){return eve::rec(std::cos(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sec(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::sec(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::sec(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::sec(EVE_TYPE( 0 )), EVE_TYPE(ref_sec(0.0)) );
  TTS_IEEE_EQUAL(eve::sec(EVE_TYPE(-0.)), EVE_TYPE(ref_sec(0.0)) );

  TTS_ULP_EQUAL(eve::sec( EVE_TYPE(1))                  , EVE_TYPE(ref_sec(1.0))                   , 1.0 );
  TTS_ULP_EQUAL(eve::sec( EVE_TYPE(-1))                 , EVE_TYPE(ref_sec(-1.0))                  , 1.0 );
  TTS_ULP_EQUAL(eve::sec( eve::pio_4(eve::as<EVE_TYPE>()))       , EVE_TYPE(ref_sec(eve::pio_4(eve::as<EVE_VALUE>())))     , 0.75);
  TTS_ULP_EQUAL(eve::sec(-eve::pio_4(eve::as<EVE_TYPE>()))       , EVE_TYPE(ref_sec(-eve::pio_4(eve::as<EVE_VALUE>())))    , 0.75);
  TTS_ULP_EQUAL(eve::sec( EVE_TYPE(100000.0))           , EVE_TYPE(ref_sec(100000.0))              , 0.5 );
  TTS_ULP_EQUAL(eve::sec(-EVE_TYPE(100000.0))           , EVE_TYPE(ref_sec(-100000.0))             , 0.5 );
  TTS_ULP_EQUAL(eve::sec( EVE_TYPE(100000000.0))        , EVE_TYPE(ref_sec(100000000.0))           , 0.5 );
  TTS_ULP_EQUAL(eve::sec(-EVE_TYPE(100000000.0))        , EVE_TYPE(ref_sec(-100000000.0))          , 0.5 );
  TTS_ULP_EQUAL(eve::sec(EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>())))    , EVE_TYPE(ref_sec(eve::valmax(eve::as<EVE_VALUE>())))    , 1.5 );
  TTS_ULP_EQUAL(eve::sec(EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>()))/10) , EVE_TYPE(ref_sec(eve::valmax(eve::as<EVE_VALUE>())/10)) , 1.5 );
}
