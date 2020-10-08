//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on oneminus", EVE_TYPE)
{

  if constexpr(eve::signed_value<T>)
  {
    auto std_oneminus = [](auto e) -> EVE_VALUE { return e <= eve::valmin(eve::as<EVE_VALUE>())+1 ? eve::valmax(eve::as<EVE_VALUE>()) : EVE_VALUE(1)-e; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_oneminus,  eve::saturated(eve::oneminus));
 }
  else
  {
    auto std_oneminus = [](auto e) -> EVE_VALUE { return (e <= 1) ? EVE_VALUE(1)-e : EVE_VALUE(0); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_oneminus, eve::saturated(eve::oneminus));
  }
}
