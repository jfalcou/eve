//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinpi.hpp>
#include <eve/constant/invpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asinpi", EVE_TYPE)
{
  auto std_asinpi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*std::asin(e); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asinpi, eve::asinpi);
}
