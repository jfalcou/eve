//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::saturate return type")
{
  TTS_EXPR_IS(eve::saturate(EVE_TYPE(), eve::as<std::uint8_t>()), EVE_TYPE);
}

TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate(EVE_TYPE(0)    , eve::as<std::uint8_t>() ), EVE_TYPE(0)     );
  TTS_EQUAL(eve::saturate(EVE_TYPE(42.69), eve::as<std::uint8_t>() ), EVE_TYPE(42.69) );

  if constexpr(eve::signed_value<EVE_VALUE>)
  {
      if constexpr(sizeof(EVE_VALUE) <= sizeof(std::int8_t))
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::uint8_t>()), eve::valmax(eve::as<EVE_TYPE>()) );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::uint8_t>()), EVE_TYPE(eve::valmax(eve::as<std::uint8_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::uint8_t>()), EVE_TYPE(eve::valmax(eve::as<std::uint8_t>())) );
  }
}
