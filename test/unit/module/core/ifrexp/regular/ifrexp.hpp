//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ifrexp.hpp>
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

TTS_CASE("Check ifrexp return type")
{
  TTS_EXPR_IS((eve::ifrexp(Type())), (std::tuple<Type,eve::detail::as_integer_t<Type,signed>>));
}

TTS_CASE("Check (eve::ifrexp behavior")
{
  using i_t = eve::detail::as_integer_t<Type,signed>; 
  {
    auto [p0, p1] = eve::ifrexp(Type(1));
    TTS_EQUAL(p0, Type(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::ifrexp(Type(0));
    TTS_EQUAL (p0 , Type(0));
    TTS_EQUAL (p1, i_t(0));
  }
}
