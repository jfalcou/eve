//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU    

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscpi.hpp>
#include <eve/function/indeg.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on acscpi")
{
  auto std_acscpi = tts::vectorize<Type>( [](auto e) { return eve::Invpi<Value>()*std::asin(eve::rec(e)); } );

  eve::rng_producer<Type> p1(eve::Valmin<Value>(), Value(-1));
  TTS_RANGE_CHECK(p1, std_acscpi, eve::acscpi); 
  eve::rng_producer<Type> p2(Value(1), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p2, std_acscpi, eve::acscpi); 

}
