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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::round return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::round(T(0)), T);
}

TTS_CASE_TPL("Check eve::upward(eve::round) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::upward      (eve::round)(T(1.7)), eve::ceil   (T(1.7)) );
  TTS_EQUAL(eve::downward    (eve::round)(T(1.7)), eve::floor  (T(1.7)) );
  TTS_EQUAL(eve::toward_zero (eve::round)(T(1.7)), eve::trunc  (T(1.7)) );
  TTS_EQUAL(eve::to_nearest  (eve::round)(T(1.7)), eve::nearest(T(1.7)) );
  TTS_EQUAL(eve::round(T(1.7))                    , eve::nearest(T(1.7)) );

  TTS_EQUAL(eve::upward      (eve::round)(T(1.3)), eve::ceil   (T(1.3)) );
  TTS_EQUAL(eve::downward    (eve::round)(T(1.3)), eve::floor  (T(1.3)) );
  TTS_EQUAL(eve::toward_zero (eve::round)(T(1.3)), eve::trunc  (T(1.3)) );
  TTS_EQUAL(eve::to_nearest  (eve::round)(T(1.3)), eve::nearest(T(1.3)) );
  TTS_EQUAL(eve::round(T(1.3))                    , eve::nearest(T(1.3)) );
}
