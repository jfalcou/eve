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
#include <eve/constant/one.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/trigo_tags.hpp>
#include <utility>

TTS_CASE("Check  eve::big_(eve::sinpicospi) return type")
{
  TTS_EXPR_IS(eve::big_(eve::sinpicospi)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
} 

TTS_CASE("Check  eve::big_(eve::sinpicospi) behavior")
{
  static const int N = 16; 
  EVE_VALUE x[N] = {  eve::One<EVE_VALUE>()/8, -eve::One<EVE_VALUE>()/8
                  , eve::One<EVE_VALUE>()/4, -eve::One<EVE_VALUE>()/4
                  , EVE_VALUE(1), EVE_VALUE(-1)
                  , EVE_VALUE(10), EVE_VALUE(-10)
                  , EVE_VALUE(1000000), EVE_VALUE(-1000000)
                  , EVE_VALUE(1000000000), EVE_VALUE(-1000000000)
                  , eve::Valmax<EVE_VALUE>(), eve::Valmin<EVE_VALUE>()    
                  , eve::Valmax<EVE_VALUE>()/100000, eve::Valmin<EVE_VALUE>()/10000}; 
  
  for(int i=0; i < N ; ++i)
  {
    auto [p0, p1] = eve::big_(eve::sinpicospi)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, eve::sinpi(EVE_TYPE(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(EVE_TYPE(x[i])), 0.5);
  }
}
