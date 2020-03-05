//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/modf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>

TTS_CASE("Check modf return type")
{
  TTS_EXPR_IS((eve::modf(Type())), (std::tuple<Type,Type>));
}

TTS_CASE("Check (eve::modf behavior")
{
  if constexpr(std::is_floating_point_v<Value>)
  {
    {
      auto [p0, p1] = eve::modf(Type(1.5));
      TTS_EQUAL(p0, Type(0.5));
      TTS_EQUAL(p1, Type(1));
    }
    if constexpr(std::is_signed_v<Value>)
    {
      auto [p0, p1] = eve::modf(Type(-1.6));
      TTS_ULP_EQUAL (p0 , Type(-0.6), 0.5);
      TTS_EQUAL (p1, Type(-1));
    }
  }
  else
  {
     auto [p0, p1] = eve::modf(Type(1));
      TTS_EQUAL (p0 , Type(0));
      TTS_EQUAL (p1, Type(1));
  }
}
