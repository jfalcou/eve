//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/firstbitunset.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check firstbitunset return type")
{
  TTS_EXPR_IS(eve::firstbitunset(Type()), (Type));
}

TTS_CASE("Check eve::firstbitunset behavior")
{
  TTS_EQUAL(eve::firstbitunset(Type(0)), Type(1));
  TTS_EQUAL(eve::firstbitunset(Type(1)), Type(2));
  TTS_EQUAL(eve::firstbitunset(Type(2)), Type(1));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::firstbitunset(Type(-1)), Type(0));
    TTS_EQUAL(eve::firstbitunset(Type(-2)), Type(1));
  }
}
