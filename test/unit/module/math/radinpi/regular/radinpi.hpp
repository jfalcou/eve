//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/radinpi.hpp>


TTS_CASE("Check eve::radinpi return type")
{
  TTS_EXPR_IS(eve::radinpi(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::radinpi behavior")
{
  TTS_ULP_EQUAL(eve::radinpi(-eve::pi(eve::as<EVE_TYPE>()))     , -EVE_TYPE(1)     , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(-eve::pi(eve::as<EVE_TYPE>())/3)   , -EVE_TYPE(1./3.) , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(-eve::pio_2(eve::as<EVE_TYPE>()))  , -EVE_TYPE(0.5)   , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(-eve::pio_4(eve::as<EVE_TYPE>()))  , -EVE_TYPE(0.25)  , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(EVE_TYPE(0))                       ,  EVE_TYPE(0)     , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pio_4(eve::as<EVE_TYPE>()))   ,  EVE_TYPE(0.25)  , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pio_2(eve::as<EVE_TYPE>()))   ,  EVE_TYPE(0.5)   , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pi(eve::as<EVE_TYPE>()) / 3)  ,  EVE_TYPE(1./3.) , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pi(eve::as<EVE_TYPE>()))      ,  EVE_TYPE(1)     , 0.5 );
}
