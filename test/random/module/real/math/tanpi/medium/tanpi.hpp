//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_odd.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on tanpi", EVE_TYPE)
{
  auto my_stdtanpi  = [](auto x)
                      {
                        auto z = eve::abs(x);

                        if (z == trunc(z))                      return EVE_VALUE(0);
                        if (z-EVE_VALUE(0.5) == eve::trunc(z))  return eve::nan(eve::as<EVE_VALUE>());

                        return  EVE_VALUE(boost::math::sin_pi(double(x))/boost::math::cos_pi(double(x)));
                      };

  TTS_RANGE_CHECK ( eve::uniform_prng<EVE_VALUE>(EVE_VALUE(-100000.0), EVE_VALUE(100000.0))
                  , my_stdtanpi, eve::medium(eve::tanpi)
                  );
}
