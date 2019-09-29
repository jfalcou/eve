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

#include <eve/function/scalar/minmag.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

TTS_CASE("Check eve::minmag behavior")
{
  TTS_EQUAL(eve::minmag(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::minmag(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::minmag(Type{1}, Type{0}), Type{0});
  TTS_EQUAL(eve::minmag(Type{1}, Type{2}), Type{1});
  TTS_EQUAL(eve::minmag(Type{2}, Type{1}), Type{1});
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::minmag(static_cast<Type>(-3), Type{2}), Type{2});
    TTS_EQUAL(eve::minmag(static_cast<Type>(-1), Type{2}), static_cast<Type>(-1));
    TTS_EQUAL(eve::minmag(static_cast<Type>(-1), Type{1}), static_cast<Type>(-1));
  }
}

#endif
