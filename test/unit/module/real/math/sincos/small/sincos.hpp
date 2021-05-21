//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::small(eve::sincos) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small(eve::sincos)(T()), (std::array<T,2>));
}

TTS_CASE_TPL("Check eve::small(eve::sincos) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto pi_v = eve::pi(eve::as<v_t>());

  v_t x[] = {  pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, 3*pi_v/8, -3*pi_v/8
            , eve::pio_2(eve::as<v_t>()), -pi_v/2, v_t(1.57079632679489655800e+00)
            };

  for(auto v :x)
  {
    auto [p0, p1] = eve::small(eve::sincos)(T(v));
    TTS_ULP_EQUAL(p0, T(std::sin(v)), 3.5);
    TTS_ULP_EQUAL(p1, T(std::cos(v)), 3.5);
  }
}
