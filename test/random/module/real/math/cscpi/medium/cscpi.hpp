//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cscpi", EVE_TYPE)
{
  auto my_stdcscpi  = [](auto x)
                      {
                        return    (x == 0 || !eve::is_flint(x))
                                ? EVE_VALUE(eve::rec(boost::math::sin_pi(double(x))))
                                : eve::nan(eve::as<EVE_VALUE>());
                      };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-100000.0), EVE_VALUE(100000.0));
  TTS_RANGE_CHECK_WITH(p, my_stdcscpi, eve::medium(eve::cscpi), 4);
}
