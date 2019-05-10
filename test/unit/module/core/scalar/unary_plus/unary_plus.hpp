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
#ifndef UNARY_PLUS_HPP
#define UNARY_PLUS_HPP

#include <eve/function/scalar/unary_plus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check unary_plus return type")
{
  TTS_EXPR_IS(eve::unary_plus(Type(0)), Type);
}

TTS_CASE("Check eve::unary_plus behavior")
{
  TTS_EQUAL(eve::unary_plus(Type{1}), Type{1});
  TTS_EQUAL(eve::unary_plus(Type{2}), Type{2});
}

#endif
