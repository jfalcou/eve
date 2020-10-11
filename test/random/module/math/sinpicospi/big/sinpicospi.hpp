//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on sinpicospi", EVE_TYPE)
{
  auto std_sinpi    = [](auto e) -> EVE_VALUE { return eve::sinpi(double(e)); };
  auto std_cospi    = [](auto e) -> EVE_VALUE { return eve::cospi(double(e)); };
  auto sinpicospi_s = [](auto e) { auto [s, c] = eve::big(eve::sinpicospi)(e); return s; };
  auto sinpicospi_c = [](auto e) { auto [s, c] = eve::big(eve::sinpicospi)(e); return c; };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sinpi, sinpicospi_s);
  TTS_RANGE_CHECK(p, std_cospi, sinpicospi_c);
}
