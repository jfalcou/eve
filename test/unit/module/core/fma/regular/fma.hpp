//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FMA_HPP
#define FMA_HPP

#include <eve/function/fma.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check fma return type") { TTS_EXPR_IS(eve::fma(Type(), Type(), Type()), Type); }

TTS_CASE("Check fma behaviour")
{
  TTS_EQUAL(eve::fma(Type{0}, Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::fma(Type{0}, Type{0}, Type{7}), Type{7});
  TTS_EQUAL(eve::fma(Type{2}, Type{0}, Type{7}), Type{7});
  TTS_EQUAL(eve::fma(Type{0}, Type{5}, Type{7}), Type{7});
  TTS_EQUAL(eve::fma(Type{2}, Type{5}, Type{7}), Type{17});
}

#endif
