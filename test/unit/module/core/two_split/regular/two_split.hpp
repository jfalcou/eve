//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/two_split.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/valmax.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_shl.hpp>
#include <eve/function/bitwise_shr.hpp> 
#include <utility>

TTS_CASE("Check two_split return type")
{
  TTS_EXPR_IS((eve::two_split(Type())), (std::tuple<Type,Type>));
}

TTS_CASE("Check (eve::two_split behavior")
{
  {
    auto [p0, p1] = eve::two_split(Type(1));
    TTS_EQUAL(p0, Type(1));
    TTS_EQUAL(p1, Type(0));
  }
  if (std::is_same_v<Value, double>)
  {
    auto [p0, p1] = eve::two_split(Type(1.0e-30));
    TTS_EQUAL (p0, Type(0x1.4484cp-100));
    TTS_EQUAL (p1, Type(-0x1.143d6p-128));
  }
  else
  {
    auto [p0, p1] = eve::two_split(Type(1.0e-30));
    TTS_EQUAL (p0, Type(0x1.448p-100f));
    TTS_EQUAL (p1, Type(0x1.3p-114f));
  }
    
}
