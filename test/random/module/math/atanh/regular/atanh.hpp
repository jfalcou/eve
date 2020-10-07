//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atanh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on atanh")
{
  auto std_atanh = [](auto e) { return std::atanh(e); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_atanh, eve::atanh);
}
