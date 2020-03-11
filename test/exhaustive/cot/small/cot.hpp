//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/pio_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cot")
{
  auto std_cot = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::rec(std::tan(double(e))); } );

  eve::exhaustive_producer<EVE_TYPE> p(-eve::Pio_2<EVE_VALUE>(), eve::Pio_2<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_cot, eve::small_(eve::cot)); 
}
