//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frexp.hpp>
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

TTS_CASE("Check frexp return type")
{
  TTS_EXPR_IS((eve::frexp(Type())), (std::tuple<Type,Type>));
}

TTS_CASE("Check (eve::frexp behavior")
{
  {
    auto [p0, p1] = eve::frexp(Type(1));
    TTS_EQUAL(p0, Type(0.5));
    TTS_EQUAL(p1, Type(1));
  }
  {
    auto [p0, p1] = eve::frexp(Type(0));
    TTS_EQUAL (p0 , Type(0));
    TTS_EQUAL (p1, Type(0));
  }
}
