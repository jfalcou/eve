//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acospi.hpp>
#include <eve/constant/invpi.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acospi", EVE_TYPE)
{
  auto std_acospi = [](auto e) { return eve::invpi(eve::as<EVE_VALUE>())*std::acos(e); };
  double th = std::is_same_v<EVE_VALUE, double> ? 4096.0 : 512.0;

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK_WITH(p, std_acospi, eve::raw(eve::acospi), th);
}
