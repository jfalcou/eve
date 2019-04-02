//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIV_HPP
#define DIV_HPP

#include <eve/function/scalar/div.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check div return type" )
{
  TTS_EXPR_IS(eve::div(Type(), Type()) , Type);
}

TTS_CASE("Check eve::div behavior")
{
  TTS_EQUAL(eve::div(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::div(Type{1}, Type{1}), Type{1});
  TTS_EQUAL(eve::div(Type{12}, Type{3}), Type{4});
}

#endif
