//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cotpi")
{
  auto my_stdcotpi  = [](auto x)
                      { return    (x == 0 || !eve::is_flint(x))
                                ? boost::math::cos_pi(x)/boost::math::sin_pi(x)
                                : eve::nan(eve::as<EVE_VALUE>());
                      };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-100000.0), EVE_VALUE(100000.0));
  TTS_RANGE_CHECK_WITH(p, my_stdcotpi, eve::medium(eve::cotpi), 4);
}
