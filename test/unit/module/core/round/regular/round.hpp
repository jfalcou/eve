//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/round.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/roundings.hpp>

TTS_CASE("Check eve::round return type")
{
  TTS_EXPR_IS(eve::round(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::upward(eve::round) behavior")
{
  TTS_EQUAL(eve::upward      (eve::round)(EVE_TYPE(1.7)), eve::ceil   (EVE_TYPE(1.7)) );
  TTS_EQUAL(eve::downward    (eve::round)(EVE_TYPE(1.7)), eve::floor  (EVE_TYPE(1.7)) );
  TTS_EQUAL(eve::toward_zero (eve::round)(EVE_TYPE(1.7)), eve::trunc  (EVE_TYPE(1.7)) );
  TTS_EQUAL(eve::to_nearest  (eve::round)(EVE_TYPE(1.7)), eve::nearest(EVE_TYPE(1.7)) );
  TTS_EQUAL(eve::round(EVE_TYPE(1.7))                    , eve::nearest(EVE_TYPE(1.7)) );

  TTS_EQUAL(eve::upward      (eve::round)(EVE_TYPE(1.3)), eve::ceil   (EVE_TYPE(1.3)) );
  TTS_EQUAL(eve::downward    (eve::round)(EVE_TYPE(1.3)), eve::floor  (EVE_TYPE(1.3)) );
  TTS_EQUAL(eve::toward_zero (eve::round)(EVE_TYPE(1.3)), eve::trunc  (EVE_TYPE(1.3)) );
  TTS_EQUAL(eve::to_nearest  (eve::round)(EVE_TYPE(1.3)), eve::nearest(EVE_TYPE(1.3)) );
  TTS_EQUAL(eve::round(EVE_TYPE(1.3))                    , eve::nearest(EVE_TYPE(1.3)) );
}
