//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_floor.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on bit_floor")
{

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    auto std_bit_floor = [](auto e) -> EVE_VALUE{ return (e <= 1)? 0 : std::exp2l(std::floor(std::log2l(e))); };
    eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_bit_floor, eve::bit_floor);
  }
  else if constexpr(eve::signed_value<EVE_TYPE>)
  {
    auto std_bit_floor = [](auto e) -> EVE_VALUE { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); };
    eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_bit_floor, eve::bit_floor);
  }
  else
  {
    auto std_bit_floor = [](auto e) -> EVE_VALUE { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_bit_floor, eve::bit_floor);
  }
}
