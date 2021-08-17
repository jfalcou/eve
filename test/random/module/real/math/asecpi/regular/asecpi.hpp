//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asecpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/invpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asecpi", EVE_TYPE)
{
  auto std_asecpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*std::acos(eve::rec(e)); };

  eve::uniform_prng<EVE_VALUE> p1(eve::valmin(eve::as<EVE_VALUE>()), EVE_VALUE(-1));
  TTS_RANGE_CHECK(p1, std_asecpi, eve::asecpi);

  eve::uniform_prng<EVE_VALUE> p2(EVE_VALUE(1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p2, std_asecpi, eve::asecpi);
}
