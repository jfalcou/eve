//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/constant/invpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cospi", EVE_TYPE)
{
  auto my_stdcospi = [](auto x) -> EVE_VALUE {return boost::math::cos_pi(x); };

  eve::uniform_prng<EVE_VALUE> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdcospi, eve::restricted(eve::cospi));
}
