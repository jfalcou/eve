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
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on rsqrt")
{
  auto std_rsqrt = tts::vectorize<EVE_TYPE>( [](auto e) { return EVE_VALUE(1)/std::sqrt(e); } );

  eve::rng_producer<EVE_TYPE> p(eve::Smallestposval<EVE_VALUE>(), EVE_VALUE(eve::Valmax<float>()));
  TTS_RANGE_CHECK(p, std_rsqrt, eve::rsqrt); 
}
