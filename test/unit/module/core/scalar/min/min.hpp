//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MIN_HPP
#define MIN_HPP

#include <eve/function/scalar/min.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>


TTS_CASE("Check eve::min behavior")
{
  TTS_EQUAL(eve::min(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::min(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::min(Type{1}, Type{0}), Type{0});
  TTS_EQUAL(eve::min(Type{1}, Type{1}), Type{1});
  if constexpr(std::is_floating_point_v<Type> )
  {
    Type n =  eve::Nan<Type>();
    Type o =  eve::One<Type>();
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)(n, o), n);
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)(o, n), o);
  }
}

#endif
