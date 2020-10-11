//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on arg", EVE_TYPE)
{
  auto std_arg = [](auto e) { return eve::is_negative(e) ? eve::pi(eve::as<EVE_VALUE>()) : EVE_VALUE(0);};

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_arg, eve::pedantic(eve::arg));
}
