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
  TTS_EXPR_IS(eve::saturate(EVE_TYPE(), eve::as<std::uint32_t>()), EVE_TYPE);
}

TTS_CASE_TPL("Check eve::saturate behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturate(EVE_TYPE(0)    , eve::as<std::uint32_t>()), EVE_TYPE(0)     );
  TTS_EQUAL(eve::saturate(EVE_TYPE(42.69), eve::as<std::uint32_t>()), EVE_TYPE(42.69) );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::uint32_t>()), EVE_TYPE(0)                           );
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()), EVE_TYPE(eve::valmax(eve::as<std::uint32_t>())));
  }
  else
  {
    if constexpr(eve::signed_value<T>)
    {

      if constexpr(sizeof(EVE_VALUE) <= sizeof(std::int32_t))
      {
        TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()), eve::valmax(eve::as<T>()) );
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()), EVE_TYPE(eve::valmax(eve::as<std::uint32_t>())) );
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()), EVE_TYPE(eve::valmax(eve::as<std::uint32_t>())) );
    }
  }
}
