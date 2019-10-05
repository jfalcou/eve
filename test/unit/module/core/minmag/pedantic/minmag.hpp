//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MINMAG_HPP
#define MINMAG_HPP

#include <eve/function/minmag.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>

TTS_CASE("Check eve::pedantic_(eve::minmag) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::minmag)(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::pedantic_(eve::minmag)(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::pedantic_(eve::minmag)(Type{1}, Type{0}), Type{0});
  TTS_EQUAL(eve::pedantic_(eve::minmag)(Type{1}, Type{2}), Type{1});
  TTS_EQUAL(eve::pedantic_(eve::minmag)(Type{2}, Type{1}), Type{1});
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<Type>(-3), Type{2}), Type{2});
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<Type>(-1), Type{2}), static_cast<Type>(-1));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<Type>(-1), Type{1}), static_cast<Type>(-1));
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
    Type n = eve::Nan<Type>();
    Type o = eve::One<Type>();
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)(n, o), n);
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)(o, n), o);
  }
}

#endif
