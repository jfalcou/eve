//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dist.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::dist return type")
{
  TTS_EXPR_IS(eve::dist(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::dist behavior")
{
  TTS_EQUAL(eve::dist(EVE_TYPE{0}, EVE_TYPE{0}), EVE_TYPE{0});
  TTS_EQUAL(eve::dist(EVE_TYPE{0}, EVE_TYPE{1}), EVE_TYPE{1});
  TTS_EQUAL(eve::dist(EVE_TYPE{1}, EVE_TYPE{0}), EVE_TYPE{1});
  TTS_EQUAL(eve::dist(EVE_TYPE{1}, EVE_TYPE{1}), EVE_TYPE{0});

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::dist(EVE_TYPE(-1), EVE_TYPE(1)), EVE_TYPE(2));
    TTS_EQUAL(eve::dist(EVE_TYPE(-2), EVE_TYPE(-6)), EVE_TYPE(4));
  }
}
