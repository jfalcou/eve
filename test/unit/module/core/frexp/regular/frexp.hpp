//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE_TPL("Check frexp return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::frexp(T())), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::frexp behavior", EVE_TYPE)
{
  {
    auto [p0, p1] = eve::frexp(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  {
    auto [p0, p1] = eve::frexp(T(0));
    TTS_EQUAL (p0 , T(0));
    TTS_EQUAL (p1, T(0));
  }
}
