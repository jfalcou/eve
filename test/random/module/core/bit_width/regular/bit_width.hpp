//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_width.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <bit>

TTS_CASE("wide random check on bit_width")
{

  auto std_bit_width = [](auto e) { return sizeof(EVE_VALUE)*8-std::countl_zero(e); } );
  eve::uniform_prng<EVE_VALUE> p(eve::zero(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_bit_width, eve::bit_width);
}
