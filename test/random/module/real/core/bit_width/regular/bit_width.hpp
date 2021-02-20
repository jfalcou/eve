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

TTS_CASE_TPL("wide random check on bit_width", EVE_TYPE)
{
  using i_t = eve::as_integer_t<EVE_VALUE, unsigned>;
  auto std_bit_width = [](auto e) -> i_t { return sizeof(EVE_VALUE)*8-std::countl_zero(e); };
  eve::uniform_prng<EVE_VALUE> p(eve::zero(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_bit_width, eve::bit_width);
}
