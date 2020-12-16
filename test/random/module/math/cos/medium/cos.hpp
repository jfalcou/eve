//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cos", EVE_TYPE)
{
  auto std_cos = [](auto e) -> EVE_VALUE { return std::cos(double(e)); };

  auto l = eve::detail::Rempio2_limit(eve::medium_type(), eve::as<EVE_VALUE>());
  eve::uniform_prng<EVE_VALUE> p(-l, l);
  TTS_RANGE_CHECK_WITH(p, std_cos, eve::medium(eve::cos), 0.5);
}
