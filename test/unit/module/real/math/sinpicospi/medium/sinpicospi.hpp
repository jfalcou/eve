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

TTS_CASE_TPL("Check sinpicospi return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::medium(eve::sinpicospi)(T()), (kumi::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::sinpicospi behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  static const int N = 10;
  v_t x[N]  = {  v_t(1)/8, -v_t(1)/8, v_t(1)/4, -v_t(1)/4, v_t(1)
              , v_t(-1), v_t(10), v_t(-10), v_t(1000000), v_t(-1000000)
              };

  for(int i=0; i < N ; ++i)
  {
    auto [p0, p1] = eve::medium(eve::sinpicospi)(T(x[i]));
    TTS_ULP_EQUAL(p0, eve::sinpi(T(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, eve::cospi(T(x[i])), 0.5);
  }
}
