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
#include <eve/function/cospi.hpp>
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide random check on cospi", EVE_TYPE)
{
  auto my_stdcospi = [](auto x) -> EVE_VALUE {return boost::math::cos_pi(x); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-1000.0), EVE_VALUE(1000.0));
  TTS_RANGE_CHECK(p, my_stdcospi, eve::medium(eve::cospi));
}
