//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/func/tmp/boost_math_cospi.hpp>
#include <eve/function/secpi.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on secpi", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto my_stdsecpi  = [](auto x)
                      {
                        auto z = eve::abs(x);

                        if (z >= eve::maxflint(eve::as(x))) return EVE_VALUE(1);
                        if (eve::is_even(z)) return   EVE_VALUE(1);
                        if (eve::is_infinite(z)) return eve::nan(eve::as<EVE_VALUE>());
                        if ((z-EVE_VALUE(0.5) == eve::trunc(z)) && (z != z-EVE_VALUE(0.5) ))
                          return eve::nan(eve::as<EVE_VALUE>());

                        return  EVE_VALUE(eve::rec(boost::math::cos_pi(double(x))));
                      };

  eve::uniform_prng<EVE_VALUE> p(-2*eve::maxflint(eve::as<EVE_VALUE>()), 2*eve::maxflint(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::secpi);
};