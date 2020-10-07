//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on iceil")
{
  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    using i_t   = eve::detail::as_integer_t<EVE_VALUE>;
    auto std_iceil = [](auto e) { return i_t(std::ceil(e)); };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<i_t>()), eve::valmax(eve::as<i_t>()));
    TTS_RANGE_CHECK(p, std_iceil, eve::int_(eve::ceil));
  }
  else
  {
    auto std_iceil = [](auto e) { return e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_iceil, eve::int_(eve::ceil));
  }
}
