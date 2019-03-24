//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef UNARY_MINUS_HPP
#define UNARY_MINUS_HPP

#include <eve/function/scalar/unary_minus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check unary_minus return type")
{
  TTS_EXPR_IS(eve::unary_minus(Type(0)), Type);
}
TTS_CASE("Check eve::unary_minus behavior")
{
  TTS_EQUAL(eve::unary_minus(Type{1}), Type{-1});
  TTS_EQUAL(eve::unary_minus(Type{-2}), Type{2});
}

#endif
