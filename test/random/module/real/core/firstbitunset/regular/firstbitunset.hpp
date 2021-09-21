//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/firstbitunset.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on firstbitunset", EVE_TYPE)
{
  auto std_firstbitunset = [](auto e) -> EVE_VALUE{ return ~e & (e+1); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_firstbitunset, eve::firstbitunset);
}
