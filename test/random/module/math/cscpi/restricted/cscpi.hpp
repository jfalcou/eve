//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cscpi")
{
  auto my_stdcscpi  = [](auto x) { return  eve::rec(boost::math::sin_pi(x)); };

  eve::uniform_prng<EVE_VALUE> p(-0.25, 0.25);
  TTS_RANGE_CHECK_WITH(p, my_stdcscpi, eve::restricted(eve::cscpi), 4);
}
