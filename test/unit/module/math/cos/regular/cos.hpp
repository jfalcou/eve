//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::cos return type")
{
  TTS_EXPR_IS(eve::cos(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::cos behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cos(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::cos(eve::inf(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::cos(eve::minf(eve::as<EVE_TYPE>())), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  auto std_cos = [](auto e) { return std::cos(double(e)); };

  TTS_IEEE_EQUAL( eve::cos(EVE_TYPE(-0.)), EVE_TYPE(1) );
  TTS_IEEE_EQUAL( eve::cos(EVE_TYPE( 0.)), EVE_TYPE(1) );

  TTS_ULP_EQUAL(eve::cos( EVE_TYPE(1)           )         , EVE_TYPE(std_cos(1.0))                   , 0.5);
  TTS_ULP_EQUAL(eve::cos(-EVE_TYPE(1)           )         , EVE_TYPE(std_cos(-1.0))                  , 0.5);
  TTS_ULP_EQUAL(eve::cos( eve::pio_4(eve::as<EVE_TYPE>()))         , EVE_TYPE(std_cos( eve::pio_4(eve::as<EVE_VALUE>())))    , 0.5);
  TTS_ULP_EQUAL(eve::cos(-eve::pio_4(eve::as<EVE_TYPE>()))         , EVE_TYPE(std_cos(-eve::pio_4(eve::as<EVE_VALUE>())))    , 0.5);
  TTS_ULP_EQUAL(eve::cos( EVE_TYPE(100000.0)    )         , EVE_TYPE(std_cos(100000.0))              , 0.5);
  TTS_ULP_EQUAL(eve::cos(-EVE_TYPE(100000.0)    )         , EVE_TYPE(std_cos(-100000.0))             , 0.5);
  TTS_ULP_EQUAL(eve::cos( EVE_TYPE(100000000.0) )         , EVE_TYPE(std_cos(100000000.0))           , 0.5);
  TTS_ULP_EQUAL(eve::cos(-EVE_TYPE(100000000.0) )         , EVE_TYPE(std_cos(-100000000.0))          , 0.5);
  TTS_ULP_EQUAL(eve::cos( EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>()))    ) , EVE_TYPE(std_cos(eve::valmax(eve::as<EVE_VALUE>()))   ) , 0.5);
  TTS_ULP_EQUAL(eve::cos( EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>())/10) ) , EVE_TYPE(std_cos(eve::valmax(eve::as<EVE_VALUE>())/10 )), 0.5);
}
