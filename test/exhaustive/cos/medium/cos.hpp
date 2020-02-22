//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/reduce_medium_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cos")
{
  auto std_cos = tts::vectorize<Type>( [](auto e) { return std::cos(e); } );

  eve::exhaustive_producer<Type> p(-eve::Reduce_medium_limits<Value>(), eve::Reduce_medium_limits<Value>());
  TTS_RANGE_CHECK(p, std_cos, eve::medium_(eve::cos)); 
}
