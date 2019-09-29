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
#include <type_traits>

TTS_CASE("Check nearest return type") { TTS_EXPR_IS(eve::nearest(Type()), Type); }

TTS_CASE("Check eve::nearest behavior")
{
  TTS_EQUAL(eve::nearest(Type{0}), Type(0));
  TTS_EQUAL(eve::nearest(Type{1}), Type(1));
  TTS_EQUAL(eve::nearest(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::nearest(static_cast<Type>(-1)), Type(-1));
    TTS_EQUAL(eve::nearest(static_cast<Type>(-2)), Type(-2));
  }
  if constexpr(std::is_floating_point_v<Type>)
  {
   TTS_EQUAL(eve::nearest(static_cast<Type>(-1.3)), Type(-1));
   TTS_EQUAL(eve::nearest(static_cast<Type>(-1.5)), Type(-2));    
   TTS_EQUAL(eve::nearest(static_cast<Type>(-1.6)), Type(-2));
   TTS_EQUAL(eve::nearest(static_cast<Type>(1.3)), Type(1));
   TTS_EQUAL(eve::nearest(static_cast<Type>(1.5)), Type(2));
   TTS_EQUAL(eve::nearest(static_cast<Type>(1.6)), Type(2));
   TTS_EQUAL(eve::nearest(static_cast<Type>(-2.3)), Type(-2));
   TTS_EQUAL(eve::nearest(static_cast<Type>(-2.5)), Type(-2));    
   TTS_EQUAL(eve::nearest(static_cast<Type>(-2.6)), Type(-3));
   TTS_EQUAL(eve::nearest(static_cast<Type>(2.3)), Type(2));
   TTS_EQUAL(eve::nearest(static_cast<Type>(2.5)), Type(2));
   TTS_EQUAL(eve::nearest(static_cast<Type>(2.6)), Type(3));
  }
}

#endif
