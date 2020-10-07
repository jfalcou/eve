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
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"

TTS_CASE("wide random check on tanpi")
{
  auto my_stdtanpi = [](auto x){return boost::math::sin_pi(x)/boost::math::cos_pi(x); };

  TTS_RANGE_CHECK ( eve::uniform_prng<EVE_VALUE>(-0.25, 0.25)
                  , my_stdtanpi
                  , eve::restricted(eve::tanpi)
                  );
}
