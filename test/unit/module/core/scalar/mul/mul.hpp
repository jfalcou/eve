//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MUL_HPP
#define MUL_HPP

#include <eve/function/scalar/mul.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check mul return type" )
{
  TTS_EXPR_IS(eve::mul(Type(), Type()) , Type);
}

TTS_CASE("Check eve::mul behavior")
{
  TTS_EQUAL(eve::mul(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::mul(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::mul(Type{1}, Type{0}), Type{0});
  TTS_EQUAL(eve::mul(Type{1}, Type{1}), Type{1});
  TTS_EQUAL(eve::mul(Type{2}, Type{3}), Type{6});
}

#endif
