//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_NOT_HPP
#define BITWISE_NOT_HPP

#include <eve/function/bitwise_not.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check bitwise_not return type")
{
  TTS_EXPR_IS(eve::bitwise_not(Type()), Type);
}

TTS_CASE("Check eve::bitwise_not behavior")
{
  TTS_IEEE_EQUAL(eve::bitwise_not(Type{0}), eve::Allbits<Type>());
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::bitwise_not(static_cast<Type>(0x1234567890ABCDEFULL)), static_cast<Type>(0xEDCBA9876F543210ULL));
    TTS_EQUAL(eve::bitwise_not(eve::Zero<Type>()), eve::Mone<Type>());
    TTS_EQUAL(eve::bitwise_not(eve::Mone<Type>()), eve::Zero<Type>());
  }
}

#endif
