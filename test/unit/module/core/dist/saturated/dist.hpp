//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dist.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check saturated_(eve::dist) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::dist)(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check saturated_(eve::dist) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::dist)(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::saturated_(eve::dist)(EVE_TYPE(1), EVE_TYPE(5)), (EVE_TYPE(4)));

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL ( eve::saturated_(eve::dist)(eve::Valmax<EVE_TYPE>(),eve::Valmin<EVE_TYPE>())
              , eve::Valmax<EVE_TYPE>()
              );

    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<EVE_TYPE>(),EVE_TYPE(-1)), eve::Valmax<EVE_TYPE>());
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<EVE_TYPE>(),EVE_TYPE( 0)), eve::Valmax<EVE_TYPE>());
      TTS_EQUAL(eve::saturated_(eve::dist)(EVE_TYPE(-1), EVE_TYPE(1) ), (EVE_TYPE(2)));
      TTS_EQUAL(eve::saturated_(eve::dist)(EVE_TYPE(-2), EVE_TYPE(-6)), (EVE_TYPE(4)));
    }
  }
}
