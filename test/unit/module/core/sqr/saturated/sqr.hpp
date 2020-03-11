//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/saturated.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::sqr) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::sqr)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::sqr behavior")
{
  TTS_EQUAL(eve::saturated_(eve::sqr)(EVE_TYPE(1)), (EVE_TYPE(1)));
  TTS_EQUAL(eve::saturated_(eve::sqr)(EVE_TYPE(2)), (EVE_TYPE(4)));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::sqr)(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(4)));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::sqr)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)));
  }

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturated_(eve::sqr)(eve::inc(eve::Sqrtvalmax<EVE_TYPE>())), eve::Valmax<EVE_TYPE>());
  }
}
