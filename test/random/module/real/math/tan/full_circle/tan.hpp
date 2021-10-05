//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on tan", EVE_TYPE)
{
  auto std_tan = [](auto e) { return std::tan(e); };
  auto l = eve::detail::Rempio2_limit(eve::full_circle_type(), eve::as<EVE_VALUE>());

  eve::uniform_prng<EVE_VALUE> p(-l, l);
  TTS_RANGE_CHECK(p, std_tan, eve::full_circle(eve::tan));
}
