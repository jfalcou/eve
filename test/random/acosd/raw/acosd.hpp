//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE("wide random check on acosd")
{
  auto   std_acosd = tts::vectorize<EVE_TYPE>([](auto e) { return eve::radindeg(std::acos(e)); });
  double th        = std::is_same_v<EVE_VALUE, double> ? 8192.0 : 1024.0;

  eve::rng_producer<EVE_TYPE> p(-1, 1);
  TTS_ULP_RANGE_CHECK(p, std_acosd, eve::raw_(eve::acosd), th);
}
