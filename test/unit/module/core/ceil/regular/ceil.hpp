//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check ceil return type")
{
  TTS_EXPR_IS(eve::ceil(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::ceil behavior")
{
  TTS_EQUAL(eve::ceil(EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::ceil(EVE_TYPE(1)), EVE_TYPE(1));
  TTS_EQUAL(eve::ceil(EVE_TYPE(2)), EVE_TYPE(2));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::ceil(EVE_TYPE(-1)), EVE_TYPE(-1));
    TTS_EQUAL(eve::ceil(EVE_TYPE(-2)), EVE_TYPE(-2));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
   TTS_EQUAL(eve::ceil(EVE_TYPE(-1.3)), EVE_TYPE(-1));
   TTS_EQUAL(eve::ceil(EVE_TYPE(-1.5)), EVE_TYPE(-1));
   TTS_EQUAL(eve::ceil(EVE_TYPE(-1.6)), EVE_TYPE(-1));
   TTS_EQUAL(eve::ceil(EVE_TYPE(1.3)) , EVE_TYPE(2));
   TTS_EQUAL(eve::ceil(EVE_TYPE(1.5)) , EVE_TYPE(2));
   TTS_EQUAL(eve::ceil(EVE_TYPE(1.6)) , EVE_TYPE(2));
  }
}
