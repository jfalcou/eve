//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sign.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sign return type")
{
  TTS_EXPR_IS(eve::sign(Type()), (Type));
}

TTS_CASE("Check eve::sign behavior")
{
  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::sign(static_cast<Type>(-2)), (Type(-1)));
  }

  TTS_EQUAL(eve::sign(Type(0)), (Type(0)));
  TTS_EQUAL(eve::sign(Type(2)), (Type(1)));
}
