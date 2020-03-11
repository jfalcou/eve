//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/pio_4.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on tan")
{
  auto std_tan = tts::vectorize<EVE_TYPE>( [](auto e) { return std::tan(e); } );

  eve::rng_producer<EVE_TYPE> p(-eve::Pio_4<EVE_VALUE>(), eve::Pio_4<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_tan, eve::restricted_(eve::tan)); 
}
