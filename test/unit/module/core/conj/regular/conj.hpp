//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CONJ_HPP
#define CONJ_HPP

#include <eve/function/conj.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check conj return type")
{
  TTS_EXPR_IS(eve::conj(Type(0)),  Type);
}

TTS_CASE("Check eve::eve::conj behavior")
{
  TTS_ULP_EQUAL(eve::conj(eve::One<Type>()),    eve::One<Type>(), 0.5);
}

#endif
