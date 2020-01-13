//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/invpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on asecpi")
{
  auto std_asecpi = tts::vectorize<Type>( [](auto e) { return eve::Invpi<Value>()*std::acos(eve::rec(e)); } );

  eve::exhaustive_producer<Type> p1(eve::Valmin<Value>(), Value(-1));
  TTS_RANGE_CHECK(p1, std_asecpi, eve::pedantic_(eve::asecpi)); 
  eve::exhaustive_producer<Type> p2(Value(1), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p2, std_asecpi, eve::pedantic_(eve::asecpi)); 
}
