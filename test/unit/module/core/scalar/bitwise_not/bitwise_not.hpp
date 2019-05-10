//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_NOT_HPP
#define BITWISE_NOT_HPP

#include <eve/function/scalar/bitwise_not.hpp>
#include <eve/constant/allbits.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_not return type")
{
  TTS_EXPR_IS(eve::bitwise_not(Type()), Type);
}


TTS_CASE("Check eve::bitwise_not behavior")
{
  TTS_EQUAL(eve::bitwise_not(Type(1)), Type(~Type(1)));
  TTS_EQUAL(eve::bitwise_not(Type(0)), eve::Allbits<Type>());
  TTS_EQUAL(eve::bitwise_not(eve::Allbits<Type>()), Type(0));
}

#endif
