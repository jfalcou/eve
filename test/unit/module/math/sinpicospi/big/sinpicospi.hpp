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

TTS_CASE_TPL("Check  eve::big_(eve::sinpicospi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::sinpicospi)(T()), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check  eve::big_(eve::sinpicospi) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  v_t values[] =  { v_t(1)/8          , -v_t(1)/8
                        , v_t(1)/4          , -v_t(1)/4
                        , v_t(1)            , v_t(-1)
                        , v_t(10)           , v_t(-10)
                        , v_t(1000000)      , v_t(-1000000)
                        , v_t(1000000000)   , v_t(-1000000000)
                        , eve::valmax(eve::as<v_t>()), eve::valmin(eve::as<v_t>())
                        , eve::valmax(eve::as<v_t>())/100000, eve::valmin(eve::as<v_t>())/10000
                        };

  for(auto v : values)
  {
    T e(v);
    auto [p0, p1] = eve::big_(eve::sinpicospi)(e);
    TTS_ULP_EQUAL(p0, eve::sinpi(e), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(e), 0.5);
  }
}
