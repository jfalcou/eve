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
  TTS_EXPR_IS(eve::saturate(EVE_TYPE(), eve::as<std::int64_t>()), EVE_TYPE);
}

TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate(EVE_TYPE(0)    , eve::as<std::int64_t>() ), EVE_TYPE(0)     );
  TTS_EQUAL(eve::saturate(EVE_TYPE(42.69), eve::as<std::int64_t>() ), EVE_TYPE(42.69) );

  if constexpr(eve::floating_value<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), EVE_TYPE(eve::valmin(eve::as<std::int64_t>())) );
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), EVE_TYPE(eve::valmax(eve::as<std::int64_t>())) );
  }
  else
  {
    if constexpr(eve::signed_value<EVE_VALUE>)
    {
          if constexpr(sizeof(EVE_VALUE) <= sizeof(std::int64_t))
      {
        TTS_EQUAL(eve::saturate(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), eve::valmin(eve::as<EVE_TYPE>()) );
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), EVE_TYPE(eve::valmin(eve::as<std::int64_t>())) );
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), EVE_TYPE(0) );
    }

      if constexpr(sizeof(EVE_VALUE) < sizeof(std::int64_t))
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), eve::valmax(eve::as<EVE_TYPE>()) );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::int64_t>()), EVE_TYPE(eve::valmax(eve::as<std::int64_t>())) );
    }
  }
}
