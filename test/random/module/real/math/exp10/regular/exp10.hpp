//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/exp10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/maxlog10.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp10", EVE_TYPE)
{
  auto std_exp10 = [](auto e) -> EVE_VALUE { return ::exp10l(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::minlog10(eve::as<EVE_VALUE>())+1, eve::maxlog10(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_exp10, eve::exp10);
}
