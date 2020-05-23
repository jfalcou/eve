//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check abs return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated_(eve::abs)(T()), T);
}

TTS_CASE_TPL("Check eve::saturated_(eve::abs) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated_(eve::abs)(T{0}), T(0));
  TTS_EQUAL(eve::saturated_(eve::abs)(T{1}), T(1));
  TTS_EQUAL(eve::saturated_(eve::abs)(T{2}), T(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated_(eve::abs)(static_cast<T>(-1)), T(1));
    TTS_EQUAL(eve::saturated_(eve::abs)(static_cast<T>(-2)), T(2));
    TTS_EQUAL(eve::saturated_(eve::abs)(eve::Valmin<T>()), eve::Valmax<T>());
  }
}
