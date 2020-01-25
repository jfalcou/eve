//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ltz.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_ltz return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_ltz(Type() ), (logical<Type>));
}

TTS_CASE("Check eve::is_ltz behavior")
{
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_ltz(Type(-1)), eve::True<Type>());
  }

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::is_ltz(eve::Nan<Type>()), eve::False<Type>());
  }

  TTS_EQUAL(eve::is_ltz(Type(0)), eve::False<Type>());
  TTS_EQUAL(eve::is_ltz(Type(3)), eve::False<Type>());
}
