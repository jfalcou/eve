//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/saturated/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on oneminus", EVE_TYPE)
<typename T>(::tts::type<T>)
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
};