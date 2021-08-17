//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/bit_mask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on bit_mask", EVE_TYPE)
{
  auto std_bit_mask = [](auto e) { return e ? eve::allbits(eve::as<EVE_VALUE>()) : eve::zero(eve::as<EVE_VALUE>()); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_bit_mask, eve::bit_mask);
}
