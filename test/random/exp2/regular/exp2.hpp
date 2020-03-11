//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/constant/minlog2.hpp>
#include <eve/constant/maxlog2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on exp2")
{
  auto std_exp2 = tts::vectorize<EVE_TYPE>( [](auto e) { return std::exp2(e); } );

  eve::rng_producer<EVE_TYPE> p(eve::Minlog2<EVE_VALUE>()+1, eve::Maxlog2<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_exp2, eve::exp2); 
}
