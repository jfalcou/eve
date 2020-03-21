//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/sinpicospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <utility>

TTS_CASE("Check  eve::big_(eve::sinpicospi) return type")
{
  TTS_EXPR_IS(eve::big_(eve::sinpicospi)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check  eve::big_(eve::sinpicospi) behavior")
{
  EVE_VALUE values[] =  { EVE_VALUE(1)/8          , -EVE_VALUE(1)/8
                        , EVE_VALUE(1)/4          , -EVE_VALUE(1)/4
                        , EVE_VALUE(1)            , EVE_VALUE(-1)
                        , EVE_VALUE(10)           , EVE_VALUE(-10)
                        , EVE_VALUE(1000000)      , EVE_VALUE(-1000000)
                        , EVE_VALUE(1000000000)   , EVE_VALUE(-1000000000)
                        , eve::Valmax<EVE_VALUE>(), eve::Valmin<EVE_VALUE>()
                        , eve::Valmax<EVE_VALUE>()/100000, eve::Valmin<EVE_VALUE>()/10000
                        };

  for(auto v : values)
  {
    EVE_TYPE e(v);
    auto [p0, p1] = eve::big_(eve::sinpicospi)(e);
    TTS_ULP_EQUAL(p0, eve::sinpi(e), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(e), 0.5);
  }
}
