//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MINNUMMAG_HPP
#define MINNUMMAG_HPP

#include <eve/function/scalar/minnummag.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>


TTS_CASE("Check eve::minnummag behavior")
{
  TTS_EQUAL(eve::minnummag(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::minnummag(Type{0}, Type{1}), Type{0});
  TTS_EQUAL(eve::minnummag(Type{1}, Type{0}), Type{0});
  TTS_EQUAL(eve::minnummag(Type{1}, Type{2}), Type{1});
  TTS_EQUAL(eve::minnummag(Type{2}, Type{1}), Type{1});
  if constexpr(std::is_signed_v<Type> )
  {
    TTS_EQUAL(eve::minnummag(static_cast<Type>(-3), Type{2}), Type{2});
    TTS_EQUAL(eve::minnummag(static_cast<Type>(-1), Type{2}), static_cast<Type>(-1));
  }
  if constexpr(std::is_floating_point_v<Type> )
  {
    Type n =  eve::Nan<Type>();
    Type o =  eve::One<Type>();
    TTS_IEEE_EQUAL(eve::minnummag(n, o), o);
    TTS_IEEE_EQUAL(eve::minnummag(o, n), o);
  }
}

#endif
