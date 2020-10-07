//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/radinpi.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include "producers.hpp"

TTS_CASE("wide random check on inpi")
{
  auto std_inpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*e; };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_inpi, eve::radinpi);
}
