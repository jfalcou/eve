//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

TTS_CASE_TPL("Check sincos return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::sincos(T())), (std::array<T,2>));
}

TTS_CASE_TPL("Check (eve::sincos behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto pi_v   = eve::pi(eve::as<v_t>());
  auto max_v  = eve::valmax(eve::as<v_t>());
  auto min_v  = eve::valmin(eve::as<v_t>());

  v_t x[] = { pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, v_t(1), v_t(-1), v_t(10), v_t(-10)
            , v_t(1000000), v_t(-1000000), v_t(1000000000), v_t(-1000000000)
            , max_v, min_v, max_v/100000, min_v/100000
            };

  for(auto v : x)
  {
    auto [p0, p1] = eve::sincos(T(v));
    TTS_ULP_EQUAL(p0, T(std::sin(v)), 0.5);
    TTS_ULP_EQUAL(p1, T(std::cos(v)), 0.5);
  }
}
