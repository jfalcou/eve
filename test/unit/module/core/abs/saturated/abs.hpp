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

TTS_CASE("Check abs return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::abs)(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::saturated_(eve::abs) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::abs)(EVE_TYPE{0}), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated_(eve::abs)(EVE_TYPE{1}), EVE_TYPE(1));
  TTS_EQUAL(eve::saturated_(eve::abs)(EVE_TYPE{2}), EVE_TYPE(2));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::abs)(static_cast<EVE_TYPE>(-1)), EVE_TYPE(1));
    TTS_EQUAL(eve::saturated_(eve::abs)(static_cast<EVE_TYPE>(-2)), EVE_TYPE(2));
    TTS_EQUAL(eve::saturated_(eve::abs)(eve::Valmin<EVE_TYPE>()), eve::Valmax<EVE_TYPE>());
  }
}
