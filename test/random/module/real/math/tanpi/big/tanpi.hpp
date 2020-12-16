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
#include <eve/function/tanpi.hpp>
#include <eve/function/abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/trunc.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on tanpi", EVE_TYPE)
{
  auto my_stdtanpi  = [](auto x)
                    {
                      auto z = eve::abs(x);
                      if (z == trunc(z)) return   EVE_VALUE(0);
                      if (z-EVE_VALUE(0.5) == eve::trunc(z)) return eve::nan(eve::as<EVE_VALUE>());
                      return  EVE_VALUE(boost::math::sin_pi(double(x))/boost::math::cos_pi(double(x)));
                    };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, my_stdtanpi, eve::big(eve::tanpi));
}
