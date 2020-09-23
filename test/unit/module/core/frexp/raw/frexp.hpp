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
#include <tuple>

TTS_CASE_TPL("Check frexp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw(eve::frexp)(T()), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check eve::raw(eve::frexp) behavior", EVE_TYPE)
{
  auto [p0, p1] = eve::raw(eve::frexp)(T(1));
  TTS_EQUAL(p0, T(0.5));
  TTS_EQUAL(p1, T(1));
}
