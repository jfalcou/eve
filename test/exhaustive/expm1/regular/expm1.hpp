//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expm1.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on expm1")
{
  auto std_expm1 = tts::vectorize<Type>( [](auto e) { return std::expm1(e); } );

  eve::exhaustive_producer<Type> p(eve::Minlog<Value>(), eve::Maxlog<Value>()-1);
  TTS_RANGE_CHECK(p, std_expm1, eve::expm1); 
}
