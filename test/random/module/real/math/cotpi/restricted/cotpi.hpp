//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cotpi", EVE_TYPE)
{
  auto my_stdcotpi  = [](auto x) { return boost::math::cos_pi(x)/boost::math::sin_pi(x); };

  eve::uniform_prng<EVE_VALUE> p(-0.25, 0.25);
  TTS_RANGE_CHECK_WITH(p, my_stdcotpi, eve::restricted(eve::cotpi), 4);
}
