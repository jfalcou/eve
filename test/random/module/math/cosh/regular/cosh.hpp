//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cosh")
{
  auto std_cosh = [](auto e) { return std::cosh(e); };

  eve::uniform_prng<EVE_VALUE> p(-eve::maxlog(eve::as<EVE_VALUE>()), eve::maxlog(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_cosh, eve::cosh);
}
