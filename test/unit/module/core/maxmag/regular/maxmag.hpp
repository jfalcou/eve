//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MAXMAG_HPP
#define MAXMAG_HPP

#include <eve/function/scalar/maxmag.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

TTS_CASE("Check eve::maxmag behavior")
{
  TTS_EQUAL(eve::maxmag(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::maxmag(Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::maxmag(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::maxmag(Type{1}, Type{2}), Type{2});
  TTS_EQUAL(eve::maxmag(Type{2}, Type{1}), Type{2});
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::maxmag(static_cast<Type>(-1), Type{2}), Type{2});
    TTS_EQUAL(eve::maxmag(static_cast<Type>(-2), Type{1}), static_cast<Type>(-2));
    TTS_EQUAL(eve::maxmag(static_cast<Type>(-2), Type{2}), Type{2});
  }
}

#endif

