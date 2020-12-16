//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/exp10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/maxlog10.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exp10", EVE_TYPE)
{
  auto std_exp10 = [](auto e) -> EVE_VALUE { return ::exp10l(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::minlog10(eve::as<EVE_VALUE>())+1, eve::maxlog10(eve::as<EVE_VALUE>())-1);
  TTS_RANGE_CHECK(p, std_exp10, eve::pedantic(eve::exp10));
}
