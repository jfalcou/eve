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

TTS_CASE("wide random check on acos")
{
  auto std_acos = [](auto e) { return std::acos(e); };

  eve::uniform_prng<EVE_VALUE> p(-1,1);
  TTS_RANGE_CHECK_WITH(p, std_acos, eve::acos, 1024.0);
}
