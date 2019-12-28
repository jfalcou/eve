//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef QUADRANT_HPP
#define QUADRANT_HPP

#include <eve/function/scalar/quadrant.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check quadrant return type") { TTS_EXPR_IS(eve::quadrant(Type(0)), Type); }

TTS_CASE("Check eve::quadrant behavior")
{
  TTS_EQUAL(eve::quadrant(Type(1)), Type(1));
  TTS_EQUAL(eve::quadrant(Type(2)), Type(2));     
  TTS_EQUAL(eve::quadrant(Type(3)), Type(3));     
  TTS_EQUAL(eve::quadrant(Type(4)), Type(0));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::quadrant(Type(-1)), Type(3));
    TTS_EQUAL(eve::quadrant(Type(-2)), Type(2));     
    TTS_EQUAL(eve::quadrant(Type(-3)), Type(1));     
    TTS_EQUAL(eve::quadrant(Type(-4)), Type(0));     
  }
}

#endif
