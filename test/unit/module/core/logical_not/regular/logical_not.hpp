//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_not.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE("Check logical_not return type")
{
  TTS_EXPR_IS(eve::logical_not(EVE_TYPE())               , eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_not(eve::logical<EVE_TYPE>()) , eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::logical_not behavior")
{
  TTS_EQUAL(eve::logical_not(EVE_TYPE(1))             , eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_not(EVE_TYPE(0))             , eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_not(eve::allbits(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_not(eve::true_(eve::as<EVE_TYPE>()))   , eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_not(eve::false_(eve::as<EVE_TYPE>()))  , eve::true_(eve::as<EVE_TYPE>()) );
}

TTS_CASE("Check eve::operator! behavior")
{
  TTS_EQUAL(!eve::true_(eve::as<EVE_TYPE>())  , eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(!eve::false_(eve::as<EVE_TYPE>()) , eve::true_(eve::as<EVE_TYPE>()));
}
