//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <eve/function/scalar/floor.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check floor return type") { TTS_EXPR_IS(eve::floor(Type()), Type); }

TTS_CASE("Check eve::floor behavior")
{
  TTS_EQUAL(eve::floor(Type{0}), Type(0));
  TTS_EQUAL(eve::floor(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>) { TTS_EQUAL(eve::floor(static_cast<Type>(-2)), Type(-2)); }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::floor(Type(3) / Type(-2)), Type(-2));
    TTS_EQUAL(eve::floor(Type(3) / Type(2)), Type(1));
  }
}

#endif
