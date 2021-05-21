//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/all.hpp>
#include <cmath>

TTS_CASE_TPL("Check  eve::big(eve::sincos) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big(eve::sincos)(T()), (std::array<T,2>));
}

TTS_CASE_TPL("Check  eve::big(eve::sincos) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto pi_v = eve::pi(eve::as<v_t>());

  v_t x[] = {  pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, v_t(1), v_t(-1), v_t(10), v_t(-10)};

 for(int i=0; i < 8; ++i)
  {
    auto [p0, p1] = eve::big(eve::sincos)(T(x[i]));
    v_t pp0 = std::sin(x[i]);
    v_t pp1 = std::cos(x[i]);
    TTS_ULP_EQUAL(p0, T(pp0), 0.5);
    TTS_ULP_EQUAL(p1, T(pp1), 0.5);
  }

}
