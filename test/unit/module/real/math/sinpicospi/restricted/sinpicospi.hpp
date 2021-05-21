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
#include <eve/constant/nan.hpp>


TTS_CASE_TPL("Check sinpicospi  return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::sinpicospi)(T()), (std::array<T,2>));
}

TTS_CASE_TPL("Check (eve::sinpicospi behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  static const int N = 6;
  v_t x[N] = { v_t(1)/8, -v_t(1)/8, v_t(1)/4, -v_t(1)/4, v_t(1), v_t(-1) };

  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted(eve::sinpicospi)(T(x[i]));
    TTS_ULP_EQUAL(p0, T(eve::restricted(eve::sinpi)(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, T(eve::restricted(eve::cospi)(x[i])), 0.5);
  }

  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted(eve::sinpicospi)(T(x[i]));
    TTS_ULP_EQUAL(p0, eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(p1, eve::nan(eve::as<T>()), 0.5);
  }
}
