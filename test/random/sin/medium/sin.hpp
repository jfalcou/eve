//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sin")
{
  auto std_sin = tts::vectorize<Type>( [](auto e) { return std::sin(e); } );

  eve::rng_producer<Type> p(-Value(10000), Value(10000));
  TTS_RANGE_CHECK(p, std_sin, eve::medium_(eve::sin)); 
}
