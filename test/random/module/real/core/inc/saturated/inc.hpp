//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/saturated/inc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on inc", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    auto std_inc = [](auto e) -> EVE_VALUE { return e+1; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_inc, eve::saturated(eve::inc));
  }
  else
  {
    auto std_inc = [](auto e) -> EVE_VALUE { return  e == eve::valmax(eve::as<EVE_VALUE>()) ? e : e+1; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_inc, eve::saturated(eve::inc));
  }
}
