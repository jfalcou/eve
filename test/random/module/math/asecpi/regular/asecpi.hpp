//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/invpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on asecpi")
{
  auto std_asecpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*std::acos(eve::rec(e)); };

  eve::uniform_prng<EVE_VALUE> p1(eve::valmin(eve::as<EVE_VALUE>()), EVE_VALUE(-1));
  TTS_RANGE_CHECK(p1, std_asecpi, eve::asecpi);

  eve::uniform_prng<EVE_VALUE> p2(EVE_VALUE(1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p2, std_asecpi, eve::asecpi);
}
