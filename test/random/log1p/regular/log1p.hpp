//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log1p.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on log1p")
{
  auto std_log1p = tts::vectorize<EVE_TYPE>( [](auto e) { return std::log1p(e); } );

  eve::rng_producer<EVE_TYPE> p(EVE_VALUE(-1), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_log1p, eve::log1p); 
}
