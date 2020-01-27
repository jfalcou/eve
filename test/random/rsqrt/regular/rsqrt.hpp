//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  auto std_rsqrt = tts::vectorize<Type>( [](auto e) { return Value(1)/std::sqrt(e); } );

  eve::rng_producer<Type> p(eve::Smallestposval<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_rsqrt, eve::rsqrt); 
}
