//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/pio_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sin")
{
  auto std_sin = tts::vectorize<EVE_TYPE>( [](auto e) { return std::sin(double(e)); } );

  eve::rng_producer<EVE_TYPE> p(-eve::Pio_2<EVE_VALUE>(), eve::Pio_2<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_sin, eve::small_(eve::sin)); 
}
