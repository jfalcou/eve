//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosh.hpp>
#include <eve/constant/maxlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on acosh")
{
  auto std_acosh = [](auto e) { return std::acosh(e); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(1), eve::maxlog(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_acosh, eve::acosh);
}
