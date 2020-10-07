//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asind.hpp>
#include <eve/function/radindeg.hpp>

#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on asind")
{
  auto std_asind = [](auto e) { return eve::radindeg(std::asin(e)); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asind, eve::asind);
}
