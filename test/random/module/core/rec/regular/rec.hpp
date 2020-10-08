//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include "producers.hpp"

TTS_CASE("wide random check on rec")
{
  if constexpr(eve::integral_value<EVE_TYPE>)
  {
    auto std_rec  = [](auto e)  -> EVE_VALUE
                    {
                      return e ? EVE_VALUE(1)/e : eve::valmax(eve::as<EVE_VALUE>());
                    };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_rec, eve::rec);
  }
  else
  {
    auto std_rec = [](auto e) { return EVE_VALUE(1)/e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_rec, eve::rec);
  }
}
