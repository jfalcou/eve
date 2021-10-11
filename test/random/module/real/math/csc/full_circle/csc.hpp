//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide rng check on csc", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_csc = [](auto e) -> EVE_VALUE { return 1/std::sin(double(e)); };
  auto l = eve::detail::Rempio2_limit(eve::full_circle_type(), eve::as<EVE_VALUE>());

  if constexpr(eve::platform::supports_denormals)
  {
    eve::uniform_prng<EVE_VALUE>  p(-l, l);
    TTS_RANGE_CHECK(p, std_csc, eve::full_circle(eve::csc));
  }
  else
  {
    eve::uniform_prng<EVE_VALUE>  p(eve::smallestposval(eve::as<EVE_VALUE>()), l);
    TTS_RANGE_CHECK(p, std_csc, eve::full_circle(eve::csc));
  }
};