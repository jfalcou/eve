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
#include <eve/function/secpi.hpp>
#include <eve/function/abs.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on secpi")
{
  auto my_stdsecpi =  [](auto x)
                      {
                        auto z = eve::abs(x);
                        if (eve::is_even(z)) return   EVE_VALUE(1);
                        if (z-EVE_VALUE(0.5) == eve::trunc(z)) return eve::nan(eve::as<EVE_VALUE>());
                        return  EVE_VALUE(eve::rec(boost::math::cos_pi(double(x))));
                      };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-100000.0), EVE_VALUE(100000.0));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::medium(eve::secpi));
}
