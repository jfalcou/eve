//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/radinpi.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on inpi", EVE_TYPE)
{
  auto std_inpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*e; };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_inpi, eve::radinpi);
}
