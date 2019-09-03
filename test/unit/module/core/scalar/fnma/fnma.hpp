//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FNMA_HPP
#define FNMA_HPP

#include "test.hpp"
#include <eve/function/fnma.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check fnma return type") { TTS_EXPR_IS(eve::fnma(Type(), Type(), Type()), Type); }

TTS_CASE("Check eve::fnma behavior")
{
  TTS_EQUAL(eve::fnma(Type{0}, Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::fnma(Type{0}, Type{0}, Type{7}), Type{7});
  TTS_EQUAL(eve::fnma(Type{2}, Type{0}, Type{7}), Type{7});
  TTS_EQUAL(eve::fnma(Type{0}, Type{5}, Type{7}), Type{7});
  TTS_EQUAL(eve::fnma(Type{2}, Type{5}, Type{7}), static_cast<Type>(-3));
}

#endif
