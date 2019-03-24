//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_LESS_HPP
#define IS_NOT_LESS_HPP

#include <eve/function/scalar/is_not_less.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check eve::is_not_less behavior")
{
  TTS_EQUAL(eve::is_not_less(Type{0}), Type{1});
  TTS_EQUAL(eve::is_not_less(Type{2}), Type{3});
}

#endif
