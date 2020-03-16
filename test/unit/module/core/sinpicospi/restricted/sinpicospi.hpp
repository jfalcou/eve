//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/sinpi.hpp> 
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>
#include <cmath>

TTS_CASE("Check sinpicospi  return type")
{
  TTS_EXPR_IS((eve::restricted_(eve::sinpicospi)(EVE_TYPE())), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check (eve::sinpicospi behavior")
{
  static const int N = 6; 
  EVE_VALUE x[N] = {   eve::One<EVE_VALUE>()/8, -eve::One<EVE_VALUE>()/8
                   , eve::One<EVE_VALUE>()/4, -eve::One<EVE_VALUE>()/4
                   , EVE_VALUE(1), EVE_VALUE(-1)}; 
  
  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sinpicospi)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, EVE_TYPE(eve::restricted_(eve::sinpi)(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, EVE_TYPE(eve::restricted_(eve::cospi)(x[i])), 0.5);
  }
  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sinpicospi)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(p1, eve::Nan<EVE_TYPE>(), 0.5);
  }
}
