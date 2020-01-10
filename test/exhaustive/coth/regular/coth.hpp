//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/coth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on coth")
{
  auto std_coth = tts::vectorize<Type>( [](auto e) { return eve;::rec(std::tanh(e)); } );

  eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), Value(-1));
  TTS_RANGE_CHECK(p, std_coth, eve::coth); 
  eve::exhaustive_producer<Type> p(Value(1), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_coth, eve::coth); 
}
