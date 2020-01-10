//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on sqrt")
{
  auto std_sqrt = tts::vectorize<Type>( [](auto e) { return std::sqrt(e); } );

  eve::exhaustive_producer<Type> p(Value(0), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_sqrt, eve::sqrt); 
}
