//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ADD_HPP
#define ADD_HPP

#include <eve/function/scalar/add.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check add return type") { TTS_EXPR_IS(eve::add(Type(), Type()), Type); }

TTS_CASE("Check eve::add behavior")
{
  TTS_EQUAL(eve::add(Type{0}, Type{0}), Type(0));
  TTS_EQUAL(eve::add(Type{1}, Type{1}), Type(2));
  TTS_EQUAL(eve::add(Type{2}, Type{2}), Type(4));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::add(Type(-1), Type(1)), Type(0));
    TTS_EQUAL(eve::add(Type(-2), Type(-6)), Type(-8));
  }
}

#endif
