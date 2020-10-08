//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/prev.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide rng check on prev")
{
  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    auto std_prev = [](auto e)  { return  (e == 0) && eve::is_positive(e) ?
                                          EVE_VALUE(-0.)
                                        : (e ==  eve::minf(eve::as<EVE_VALUE>())) ?
                                            eve::nan(eve::as<EVE_VALUE>())
                                          : std::nextafter(e, eve::minf(eve::as<EVE_VALUE>()));
                                };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_prev, eve::pedantic(eve::prev));
  }
  else
  {
    auto std_prev = [](auto e) { return e == eve::valmin(eve::as<EVE_VALUE>()) ? e : e-1; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_prev, eve::pedantic(eve::prev));
  }
}
