//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NEAREST_HPP
#define NEAREST_HPP

#include <eve/function/scalar/nearest.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check nearest return type") { TTS_EXPR_IS(eve::nearest(Type()), Type); }

TTS_CASE("Check eve::nearest behavior")
{
  TTS_EQUAL(eve::nearest(Type{0}), Type(0));
  TTS_EQUAL(eve::nearest(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>) { TTS_EQUAL(eve::nearest(static_cast<Type>(-2)), Type(-2)); }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::nearest(Type(3) / Type(-2)), Type(-2));
    TTS_EQUAL(eve::nearest(Type(3) / Type(2)), Type(2));
    TTS_EQUAL(eve::nearest(Type(5) / Type(-2)), Type(-2));
    TTS_EQUAL(eve::nearest(Type(5) / Type(2)), Type(2));
  }
}

#endif
