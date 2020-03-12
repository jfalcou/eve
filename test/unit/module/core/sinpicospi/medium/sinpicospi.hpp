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
#include <eve/function/sinpi.hpp>
#include <eve/function/cospi.hpp>    
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

TTS_CASE("Check sinpicospi return type")
{
  TTS_EXPR_IS( eve::medium_(eve::sinpicospi)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
} 

TTS_CASE("Check (eve::sinpicospi behavior")
{
  static const int N = 10; 
  EVE_VALUE x[N] = {  eve::One<EVE_VALUE>()/8, -eve::One<EVE_VALUE>()/8
                  , eve::One<EVE_VALUE>()/4, -eve::One<EVE_VALUE>()/4
                  , EVE_VALUE(1), EVE_VALUE(-1)
                  , EVE_VALUE(10), EVE_VALUE(-10)
                  , EVE_VALUE(1000000), EVE_VALUE(-1000000)}; 
  
  for(int i=0; i < N ; ++i)
  {
    auto [p0, p1] = eve::medium_(eve::sinpicospi)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, eve::sinpi(EVE_TYPE(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(EVE_TYPE(x[i])), 0.5);
  }
}
