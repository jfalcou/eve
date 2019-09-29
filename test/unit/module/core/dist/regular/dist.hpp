//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIST_HPP
#define DIST_HPP

#include <eve/function/scalar/dist.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check dist return type") { TTS_EXPR_IS(eve::dist(Type(), Type()), Type); }

TTS_CASE("Check eve::dist behavior")
{
  TTS_EQUAL(eve::dist(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::dist(Type{0}, Type{1}), Type{1});
  TTS_EQUAL(eve::dist(Type{1}, Type{0}), Type{1});
  TTS_EQUAL(eve::dist(Type{1}, Type{1}), Type{0});
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::dist(Type(-1), Type(1)), Type(2));
    TTS_EQUAL(eve::dist(Type(-2), Type(-6)), Type(4));
  }
}

#endif
