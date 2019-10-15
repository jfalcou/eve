//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitwise_not.hpp>
#include <eve/constant/allbits.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bitwise_not return type")
{
  TTS_EXPR_IS(eve::bitwise_not(Type()), (Type));
}

TTS_CASE("Check eve::bitwise_not behavior")
{
  TTS_IEEE_EQUAL(eve::bitwise_not(Type(0)), (eve::Allbits<Type>()));

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL ( eve::bitwise_not( static_cast<Type>(0x1234567890ABCDEFULL))
              , static_cast<Type>(0xEDCBA9876F543210ULL)
              );

    TTS_EQUAL(eve::bitwise_not(Type( 0)), (Type(-1)));
    TTS_EQUAL(eve::bitwise_not(Type(-1)), (Type( 0)));
  }
}

