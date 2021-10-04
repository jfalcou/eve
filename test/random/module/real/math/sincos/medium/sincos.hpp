//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sincos", EVE_TYPE)
{
  auto std_sin  = [](auto e) -> EVE_VALUE { return std::sin(double(e)); };
  auto std_cos  = [](auto e) -> EVE_VALUE { return std::cos(double(e)); };
  auto sincos_s = [](auto e) { auto [s, c] = eve::medium(eve::sincos)(e); return s; };
  auto sincos_c = [](auto e) { auto [s, c] = eve::medium(eve::sincos)(e); return c; };

  auto l = eve::detail::Rempio2_limit(eve::half_circle_type(), eve::as<EVE_VALUE>());
  eve::uniform_prng<EVE_VALUE> p(-l, l);
  TTS_RANGE_CHECK(p, std_sin, sincos_s);
  TTS_RANGE_CHECK(p, std_cos, sincos_c);
}
