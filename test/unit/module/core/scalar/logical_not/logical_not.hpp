//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_NOT_HPP
#define LOGICAL_NOT_HPP

#include <eve/function/scalar/logical_not.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check logical_not return type")
{
  TTS_EXPR_IS(eve::logical_not(Type()),   eve::as_logical_t<Type>);
}


TTS_CASE("Check eve::logical_not behavior")
{
  TTS_EQUAL(eve::logical_not(Type(1)), eve::False<Type>());
  TTS_EQUAL(eve::logical_not(Type(0)), eve::True<Type>());
  TTS_EQUAL(eve::logical_not(eve::Allbits<Type>()), eve::False<Type>()); 
}

#endif
