//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_pow2 return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::is_pow2(Type() )), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_pow2 behavior")
{
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_pow2(Type(-1)), eve::False<Type>());
  }

  TTS_EQUAL(eve::is_pow2(Type(0)), eve::False<Type>());
  TTS_EQUAL(eve::is_pow2(Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_pow2(Type(3)), eve::False<Type>());
  TTS_EQUAL(eve::is_pow2(Type(4)), eve::True<Type>());
  TTS_EQUAL(eve::is_pow2(eve::Valmax<Type>()/2+1), eve::True<Type>());
}
