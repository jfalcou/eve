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
#include <eve/tags.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::round return type")
{
  TTS_EXPR_IS(eve::round(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::round behavior")
{
  TTS_EQUAL(eve::round((EVE_TYPE(1.7)), eve::upward_      ), eve::ceil   ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.7)), eve::downward_    ), eve::floor  ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.7)), eve::toward_zero_ ), eve::trunc  ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.7)), eve::to_nearest_  ), eve::nearest((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.7))                    ), eve::nearest((EVE_TYPE(1.7))) );

  TTS_EQUAL(eve::round((EVE_TYPE(1.3)), eve::upward_      ), eve::ceil   ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.3)), eve::downward_    ), eve::floor  ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.3)), eve::toward_zero_ ), eve::trunc  ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.3)), eve::to_nearest_  ), eve::nearest((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::round((EVE_TYPE(1.3))                    ), eve::nearest((EVE_TYPE(1.3))) );
}
