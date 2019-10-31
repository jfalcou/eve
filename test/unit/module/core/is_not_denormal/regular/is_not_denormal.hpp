//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_denormal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_not_denormal return type")
{
  TTS_EXPR_IS(eve::is_not_denormal(Type(0)), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_not_denormal behavior")
{
  TTS_EQUAL(eve::is_not_denormal(Type(0)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_denormal(Type(2)), eve::True<Type>());

  if constexpr(eve::platform::supports_denormals && std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::is_not_denormal(eve::Smallestposval<Type>() / 2), eve::False<Type>());
  }
  else
  {
    TTS_EQUAL(eve::is_not_denormal(eve::Smallestposval<Type>() / 2), eve::True<Type>());
  }
}
