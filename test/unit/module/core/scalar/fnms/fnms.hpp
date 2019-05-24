//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FNMS_HPP
#define FNMS_HPP

#include "test.hpp"
#include <eve/function/fnms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check fnms return type" )
{
  TTS_EXPR_IS(eve::fnms(Type(), Type(), Type()) , Type);
}

TTS_CASE("Check eve::fnms behavior")
{
  TTS_EQUAL(eve::fnms(Type{0}, Type{0} , Type{0}), Type{0});
  TTS_EQUAL(eve::fnms(Type{0}, Type{0} , Type{7}), static_cast<Type>(-7));
  TTS_EQUAL(eve::fnms(Type{2}, Type{0} , Type{7}), static_cast<Type>(-7));
  TTS_EQUAL(eve::fnms(Type{0}, Type{5} , Type{7}), static_cast<Type>(-7));     
  TTS_EQUAL(eve::fnms(Type{2}, Type{5} , Type{7}), static_cast<Type>(-17));
}

#endif
