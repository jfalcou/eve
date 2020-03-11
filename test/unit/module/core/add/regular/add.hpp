//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::add return type")
{
  TTS_EXPR_IS(eve::add(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::add behavior")
{
  TTS_EQUAL(eve::add(EVE_TYPE{0}, EVE_TYPE{0}), EVE_TYPE(0));
  TTS_EQUAL(eve::add(EVE_TYPE{1}, EVE_TYPE{1}), EVE_TYPE(2));
  TTS_EQUAL(eve::add(EVE_TYPE{2}, EVE_TYPE{2}), EVE_TYPE(4));

  TTS_EQUAL(eve::add(EVE_VALUE{0}, EVE_TYPE{0}), EVE_TYPE(0));
  TTS_EQUAL(eve::add(EVE_VALUE{1}, EVE_TYPE{1}), EVE_TYPE(2));
  TTS_EQUAL(eve::add(EVE_VALUE{2}, EVE_TYPE{2}), EVE_TYPE(4));

  TTS_EQUAL(eve::add(EVE_TYPE{0}, EVE_VALUE{0}), EVE_TYPE(0));
  TTS_EQUAL(eve::add(EVE_TYPE{1}, EVE_VALUE{1}), EVE_TYPE(2));
  TTS_EQUAL(eve::add(EVE_TYPE{2}, EVE_VALUE{2}), EVE_TYPE(4));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::add(EVE_TYPE(-1), EVE_TYPE(1)), EVE_TYPE(0));
    TTS_EQUAL(eve::add(EVE_TYPE(-2), EVE_TYPE(-6)), EVE_TYPE(-8));

    TTS_EQUAL(eve::add(EVE_VALUE(-1), EVE_TYPE(1)), EVE_TYPE(0));
    TTS_EQUAL(eve::add(EVE_VALUE(-2), EVE_TYPE(-6)), EVE_TYPE(-8));

    TTS_EQUAL(eve::add(EVE_TYPE(-1), EVE_VALUE(1)), EVE_TYPE(0));
    TTS_EQUAL(eve::add(EVE_TYPE(-2), EVE_VALUE(-6)), EVE_TYPE(-8));
  }
}
