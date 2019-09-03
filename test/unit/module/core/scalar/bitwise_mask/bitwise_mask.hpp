//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_MASK_HPP
#define BITWISE_MASK_HPP

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/scalar/bitwise_mask.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_mask return type") { TTS_EXPR_IS(eve::bitwise_mask(Type()), Type); }

TTS_CASE("Check eve::bitwise_mask behavior")
{
  TTS_EQUAL(eve::bitwise_mask(Type(0)), Type(0));

  if constexpr(std::is_floating_point_v<Type>)
  { TTS_IEEE_EQUAL(eve::bitwise_mask(Type(1)), eve::Allbits<Type>()); }
  else
  {
    TTS_EQUAL(eve::bitwise_mask(Type(1)), eve::Allbits<Type>());
  }
}

#endif
