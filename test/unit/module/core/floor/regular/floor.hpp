//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/floor.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::floor return type")
{
  TTS_EXPR_IS(eve::floor(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::floor behavior")
{
  TTS_EQUAL(eve::floor(EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::floor(EVE_TYPE(1)), (EVE_TYPE(1)));
  TTS_EQUAL(eve::floor(EVE_TYPE(2)), (EVE_TYPE(2)));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(-1)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(-2)));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
   TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(-1.3)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(-1.5)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(-1.6)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(1.3)) , (EVE_TYPE( 1)));
   TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(1.5)) , (EVE_TYPE( 1)));
   TTS_EQUAL(eve::floor(static_cast<EVE_TYPE>(1.6)) , (EVE_TYPE( 1)));
  }
}
