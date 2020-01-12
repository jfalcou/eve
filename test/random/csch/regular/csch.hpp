//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on csch")
{
  auto std_csch = tts::vectorize<Type>( [](auto e) { return eve::rec(std::sinh(e)); } );

  eve::rng_producer<Type> p(-eve::Maxlog<Value>()+1, eve::Maxlog<Value>()-1);
  TTS_RANGE_CHECK(p, std_csch, eve::csch); 
}
