//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nearest.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check nearest return type")
{
  TTS_EXPR_IS(eve::nearest(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::nearest behavior")
{
  TTS_EQUAL(eve::nearest(EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::nearest(EVE_TYPE(1)), EVE_TYPE(1));
  TTS_EQUAL(eve::nearest(EVE_TYPE(2)), EVE_TYPE(2));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-1)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(-2)));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-1.3)), (EVE_TYPE(-1)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-1.5)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-1.6)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>( 1.3)), (EVE_TYPE( 1)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>( 1.5)), (EVE_TYPE( 2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>( 1.6)), (EVE_TYPE( 2)));

   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-2.3)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-2.5)), (EVE_TYPE(-2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>(-2.6)), (EVE_TYPE(-3)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>( 2.3)), (EVE_TYPE( 2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>( 2.5)), (EVE_TYPE( 2)));
   TTS_EQUAL(eve::nearest(static_cast<EVE_TYPE>( 2.6)), (EVE_TYPE( 3)));
  }
}
