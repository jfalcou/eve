//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/log1p.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on log1p", EVE_TYPE)
{
  auto std_log1p = [](auto e) { return std::log1p(e); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(-1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_log1p, eve::log1p);
}
