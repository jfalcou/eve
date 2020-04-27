//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE_TPL("Check saturated_(eve::dist) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated_(eve::dist)(T(), T()), T);
}

TTS_CASE_TPL("Check saturated_(eve::dist) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated_(eve::dist)(T(0), T(0)), (T(0)));
  TTS_EQUAL(eve::saturated_(eve::dist)(T(1), T(5)), (T(4)));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL ( eve::saturated_(eve::dist)(eve::Valmax<T>(),eve::Valmin<T>())
              , eve::Valmax<T>()
              );

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<T>(),T(-1)), eve::Valmax<T>());
      TTS_EQUAL(eve::saturated_(eve::dist)(eve::Valmin<T>(),T( 0)), eve::Valmax<T>());
      TTS_EQUAL(eve::saturated_(eve::dist)(T(-1), T(1) ), (T(2)));
      TTS_EQUAL(eve::saturated_(eve::dist)(T(-2), T(-6)), (T(4)));
    }
  }
}
