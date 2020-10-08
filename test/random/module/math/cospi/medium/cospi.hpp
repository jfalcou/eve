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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE("wide random check on cospi")
{
  auto my_stdcospi = [](auto x) {return EVE_VALUE(boost::math::cos_pi(x)); };
  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-100000), EVE_VALUE(100000));
    TTS_RANGE_CHECK(p, my_stdcospi, eve::medium(eve::cospi));
  }
  else
  {
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, my_stdcospi, eve::medium(eve::cospi));
  }
}
