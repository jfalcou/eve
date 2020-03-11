//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide rng check on rsqrt")
{
  auto std_rsqrt = tts::vectorize<EVE_TYPE>( [](auto e) { return EVE_VALUE(1.0l/std::sqrt((long double)e)); } );

  eve::rng_producer<EVE_TYPE> p(EVE_VALUE(0), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_rsqrt, eve::pedantic_(eve::rsqrt)); 
}
