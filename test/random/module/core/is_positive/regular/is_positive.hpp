//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_positive.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on is_positive")
{
  using l_t = eve::as_logical_t<EVE_TYPE>;

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    auto std_is_positive = [](auto e)  ->eve::logical<EVE_VALUE> { return std::signbit(e) == 0; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_positive, eve::is_positive);
  }
  else
  {
    auto std_is_positive = [](auto e) ->eve::logical<EVE_VALUE> { return e >= 0; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_is_positive, eve::is_positive);
  }
}
