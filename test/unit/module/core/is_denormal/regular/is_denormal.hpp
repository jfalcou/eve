//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_denormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE("Check eve::is_denormal return type")
{
  TTS_EXPR_IS(eve::is_denormal(EVE_TYPE(0)), eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::is_denormal behavior")
{
  TTS_EQUAL(eve::is_denormal(EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::is_denormal(EVE_TYPE(2)), eve::false_(eve::as<EVE_TYPE>()));

  if constexpr(eve::platform::supports_denormals && eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::is_denormal(eve::smallestposval(eve::as<EVE_TYPE>()) / 2), eve::true_(eve::as<EVE_TYPE>()));
  }
  else
  {
    TTS_EQUAL(eve::is_denormal(eve::smallestposval(eve::as<EVE_TYPE>()) / 2), eve::false_(eve::as<EVE_TYPE>()));
  }
}
