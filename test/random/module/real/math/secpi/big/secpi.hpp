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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on secpi", EVE_TYPE)
{
  auto my_stdsecpi  = [](auto x)
                    {
                      auto z = eve::abs(x);

                      if (z >= eve::maxflint(eve::as(x))) return EVE_VALUE(1);
                      if (eve::is_even(z)) return   EVE_VALUE(1);

                      if ((z-EVE_VALUE(0.5) == eve::trunc(z)) && (z != z-EVE_VALUE(0.5) ))
                        return eve::nan(eve::as<EVE_VALUE>());

                      return  EVE_VALUE(eve::rec(boost::math::cos_pi(double(x))));
                    };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::big(eve::secpi));
}
