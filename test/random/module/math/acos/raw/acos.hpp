//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acos.hpp>
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE_TPL("wide random check on acos", EVE_TYPE)
{
  auto std_acos = [](auto e) { return std::acos(e); };

  double th = std::is_same_v<EVE_VALUE, double> ? 4096.0 : 512.0;
  eve::uniform_prng<EVE_VALUE> p(-1,1);
  TTS_RANGE_CHECK_WITH(p, std_acos, eve::raw(eve::acos), th);
}
