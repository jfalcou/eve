//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/atand.hpp>
#include <eve/function/radindeg.hpp>

#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on atand", EVE_TYPE)
{
  auto std_atand = [](auto e) { return eve::radindeg(std::atan(e)); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_atand, eve::atand);
}
