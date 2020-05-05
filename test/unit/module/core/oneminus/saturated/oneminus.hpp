//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/function/inc.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::saturated_(eve::oneminus) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated_(eve::oneminus)(T(1)), T(0));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(T(2)               ) , T(-1)           );
    TTS_EQUAL(eve::saturated_(eve::oneminus)(static_cast<T>(-2) ) , T(3)            );
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Valmin<T>()   ) , eve::Valmax<T>());
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::inc(eve::Valmin<T>()))          , eve::Valmax<T>());
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::inc(eve::inc(eve::Valmin<T>()))), eve::Valmax<T>());
  }

  if constexpr(eve::unsigned_value<T>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(T(2)), T(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(T(1)), T(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(T(0)), T(1));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(T(-0.)), T(1));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(T( 0 )), T(1));
  }
}
