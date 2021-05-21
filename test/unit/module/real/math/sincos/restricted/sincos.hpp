//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>
#include <tuple>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted(eve::sincos) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::sincos)(T()), (std::array<T,2>));
}

TTS_CASE_TPL("Check eve::restricted(eve::sincos) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  static const int N = 6;
  v_t x[N]  = { v_t(1)/8, -v_t(1)/8, v_t(1)/4, -v_t(1)/4, v_t(1), v_t(-1) };

  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted(eve::sincos)(T(x[i]));
    TTS_ULP_EQUAL(p0, T(std::sin(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, T(std::cos(x[i])), 0.5);
  }

  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted(eve::sincos)(T(x[i]));
    TTS_ULP_EQUAL(p0, eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(p1, eve::nan(eve::as<T>()), 0.5);
  }
}
