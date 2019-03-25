//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include <eve/function/scalar/extract.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check eve::extract behavior")
{
  TTS_EQUAL(eve::extract(Type{0}), Type{1});
  TTS_EQUAL(eve::extract(Type{2}), Type{3});
}

#endif
