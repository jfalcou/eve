//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on csch")
{
  auto std_csch = [](auto e) { return eve::rec(std::sinh(e)); };

  eve::uniform_prng<EVE_VALUE> p(-eve::maxlog(eve::as<EVE_VALUE>())+1, eve::maxlog(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_csch, eve::csch);
}
