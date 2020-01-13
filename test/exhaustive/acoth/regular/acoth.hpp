//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acoth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on acoth")
{
  auto std_acoth = tts::vectorize<Type>( [](auto e) { return std::atanh(eve::rec(e)); } );

  eve::exhaustive_producer<Type> p1(Value(1), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p1, std_acoth, eve::acoth); 
  eve::exhaustive_producer<Type> p2(eve::Valmin<Value>(), Value(-1));
  TTS_RANGE_CHECK(p2, std_acoth, eve::acoth); 
}
