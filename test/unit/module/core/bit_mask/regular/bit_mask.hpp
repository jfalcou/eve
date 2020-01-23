//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_mask.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::bit_mask return type")
{
  TTS_EXPR_IS(eve::bit_mask(Type()), (Type));
}

TTS_CASE("Check eve::bit_mask behavior")
{
  TTS_EQUAL(eve::bit_mask( Type(0))           , (Type)(0));
  TTS_EQUAL(eve::bit_mask(-Type(0))           , (Type)(0));
  TTS_EQUAL(eve::bit_mask(eve::False<Type>()) , (Type)(0));

  TTS_IEEE_EQUAL(eve::bit_mask(Type(1))           , (eve::Allbits<Type>()));
  TTS_IEEE_EQUAL(eve::bit_mask(eve::True<Type>()) , (eve::Allbits<Type>()));
}
