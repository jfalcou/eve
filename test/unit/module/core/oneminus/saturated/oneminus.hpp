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
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/inc.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::oneminus) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::oneminus)(EVE_TYPE{1}), EVE_TYPE(0));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(EVE_TYPE{2}), EVE_TYPE(-1));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(static_cast<EVE_TYPE>(-2)), EVE_TYPE(3));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Valmin<EVE_TYPE>()), eve::Valmax<EVE_TYPE>());
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::inc(eve::Valmin<EVE_TYPE>())), eve::Valmax<EVE_TYPE>());
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::inc(eve::inc(eve::Valmin<EVE_TYPE>()))), eve::Valmax<EVE_TYPE>());
  }

  if constexpr(std::is_unsigned_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(EVE_TYPE{2}), EVE_TYPE(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(EVE_TYPE{1}), EVE_TYPE(0));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(EVE_TYPE{0}), EVE_TYPE(1));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Mzero<EVE_TYPE>()), EVE_TYPE(1));
    TTS_EQUAL(eve::saturated_(eve::oneminus)(eve::Zero<EVE_TYPE>()),  EVE_TYPE(1));
  }
}
