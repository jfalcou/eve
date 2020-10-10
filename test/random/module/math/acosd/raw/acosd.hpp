//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acosd", EVE_TYPE)
{
  auto std_acosd = [](auto e) { return eve::radindeg(std::acos(e)); };
  double th = std::is_same_v<EVE_VALUE, double> ? 8192.0 : 1024.0;

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK_WITH(p, std_acosd, eve::raw(eve::acosd), th);
}
