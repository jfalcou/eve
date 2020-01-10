//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinpi.hpp>
#include <eve/constant/invpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on asinpi")
{
  auto std_asinpi = tts::vectorize<Type>( [](auto e) { return eve::Invpi<Value>()*std::asin(e); } );

  eve::exhaustive_producer<Type> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asinpi, eve::asinpi); 
}
