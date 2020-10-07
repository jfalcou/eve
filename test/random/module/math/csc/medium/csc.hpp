//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide rng check on csc")
{
  auto std_csc = [](auto e) -> EVE_VALUE { return 1/std::sin(double(e)); };
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), eve::as<EVE_VALUE>());

  if constexpr(eve::platform::supports_denormals)
  {
    eve::uniform_prng<EVE_VALUE>  p(-l, l);
    TTS_RANGE_CHECK(p, std_csc, eve::medium(eve::csc));
  }
  else
  {
    eve::uniform_prng<EVE_VALUE>  p(eve::smallestposval(eve::as<EVE_VALUE>()), l);
    TTS_RANGE_CHECK(p, std_csc, eve::medium(eve::csc));
  }
}
