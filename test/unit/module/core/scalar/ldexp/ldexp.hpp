//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LDEXP_HPP
#define LDEXP_HPP

#include <eve/function/scalar/ldexp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check eve::ldexp behavior")
{
  TTS_EQUAL(eve::ldexp(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::ldexp(Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::ldexp(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::ldexp(Type{1}, Type{1}), Type{2});
}

#endif
