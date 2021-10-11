//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on rec", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::integral_value<T>)
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
};