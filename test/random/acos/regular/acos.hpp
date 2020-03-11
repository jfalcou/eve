//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acos.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on acos")
{
  auto std_acos = tts::vectorize<EVE_TYPE>( [](auto e) { return std::acos(e); } );

  eve::rng_producer<EVE_TYPE> p(-1,1);
  TTS_ULP_RANGE_CHECK(p, std_acos, eve::acos, 1024.0);
}
