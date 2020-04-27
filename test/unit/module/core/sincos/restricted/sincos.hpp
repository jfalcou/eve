//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <type_traits>
#include <utility>
#include <cmath>

TTS_CASE_TPL("Check sincos  return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::restricted_(eve::sincos)(T())), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::sincos behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  static const int N = 6;
  v_t x[N] = {   eve::One<v_t>()/8, -eve::One<v_t>()/8
                   , eve::One<v_t>()/4, -eve::One<v_t>()/4
                   , v_t(1), v_t(-1)};

  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sincos)(T(x[i]));
    TTS_ULP_EQUAL(p0, T(std::sin(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, T(std::cos(x[i])), 0.5);
  }
  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sincos)(T(x[i]));
    TTS_ULP_EQUAL(p0, eve::Nan<T>(), 0.5);
    TTS_ULP_EQUAL(p1, eve::Nan<T>(), 0.5);
  }
}
