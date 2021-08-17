//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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

TTS_CASE_TPL("wide random check on secpi", EVE_TYPE)
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
