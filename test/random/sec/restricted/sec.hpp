//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/constant/pio_4.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sec")
{
  auto std_sec = tts::vectorize<EVE_TYPE>( [](auto e) { return 1/std::cos(e); } );

  eve::rng_producer<EVE_TYPE> p(-eve::Pio_4<EVE_VALUE>(), eve::Pio_4<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_sec, eve::restricted_(eve::sec)); 
}
