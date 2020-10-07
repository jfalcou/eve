//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/constant/pio_2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sincos")
{
  auto std_sin  = [](auto e) -> EVE_VALUE { return std::sin(double(e)); };
  auto std_cos  = [](auto e) -> EVE_VALUE { return std::cos(double(e)); };
  auto sincos_s = [](auto e) { auto [s, c] = eve::small(eve::sincos)(e); return s; };
  auto sincos_c = [](auto e) { auto [s, c] = eve::small(eve::sincos)(e); return c; };

  eve::uniform_prng<EVE_VALUE> p(-eve::pio_2(eve::as<EVE_VALUE>()), eve::pio_2(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sin, sincos_s);
  TTS_RANGE_CHECK(p, std_cos, sincos_c);
}
