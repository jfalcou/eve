//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MAX_HPP
#define MAX_HPP

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/max.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

TTS_CASE("Check eve::max behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::max)(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::pedantic_(eve::max)(Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::pedantic_(eve::max)(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::pedantic_(eve::max)(Type{1}, Type{1}), Type{1});
  if constexpr(std::is_floating_point_v<Type>)
  {
    Type n = eve::Nan<Type>();
    Type o = eve::One<Type>();
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)(n, o), n);
    TTS_IEEE_EQUAL(eve::pedantic_(eve::max)(o, n), o);
  }
}

#endif
