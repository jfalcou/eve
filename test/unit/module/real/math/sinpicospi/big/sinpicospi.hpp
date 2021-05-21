//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check  eve::big(eve::sinpicospi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big(eve::sinpicospi)(T()), (std::array<T,2>));
}

TTS_CASE_TPL("Check  eve::big(eve::sinpicospi) behavior", EVE_TYPE)
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
    auto [p0, p1] = eve::big(eve::sinpicospi)(e);
    TTS_ULP_EQUAL(p0, eve::sinpi(e), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(e), 0.5);
  }
}
