//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/one.hpp>

TTS_CASE_TPL("Check sinpicospi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinpicospi(T()), (std::array<T,2>));
}

TTS_CASE_TPL("Check (eve::sinpicospi behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  static const int N = 16;
  v_t x[N]  = { v_t(1)/8, -v_t(1)/8
              , v_t(1)/4, -v_t(1)/4
              , v_t(1), v_t(-1)
              , v_t(10), v_t(-10)
              , v_t(1000000), v_t(-1000000)
              , v_t(1000000000), v_t(-1000000000)
              , eve::valmax(eve::as<v_t>()), eve::valmin(eve::as<v_t>())
              , eve::valmax(eve::as<v_t>())/100000, eve::valmin(eve::as<v_t>())/100000
              };

  for(int i=0; i < N ; ++i)
  {
    auto [p0, p1] = eve::sinpicospi(T(x[i]));
    TTS_ULP_EQUAL(p0, eve::sinpi(T(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(T(x[i])), 0.5);
  }
}
