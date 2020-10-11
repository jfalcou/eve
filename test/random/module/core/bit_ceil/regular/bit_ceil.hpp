//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on bit_ceil", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    auto std_bit_ceil = [](auto e) -> EVE_VALUE { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); };
    eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>())/4);
    TTS_RANGE_CHECK(p, std_bit_ceil, eve::bit_ceil);
  }
  else
  {
    auto std_bit_ceil = [](auto e) -> EVE_VALUE { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), (1ul << (sizeof(EVE_VALUE)*8-2)));
    TTS_RANGE_CHECK(p, std_bit_ceil, eve::bit_ceil);
  }
}
