//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sec", EVE_TYPE)
{
  auto std_sec = [](auto e) -> EVE_VALUE { return 1/std::cos(double(e)); };
  auto l = eve::detail::Rempio2_limit(eve::circle_type(), eve::as<EVE_VALUE>());

  eve::uniform_prng<EVE_VALUE>  p(-l, l);
  TTS_RANGE_CHECK(p, std_sec, eve::circle(eve::sec));
}
