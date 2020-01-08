//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on exp")
{
  auto std_exp = tts::vectorize<Type>( [](auto e) { return std::exp(e); } );

  eve::exhaustive_producer<Type> p(eve::Minlog<Value>(), eve::Maxlog<Value>());
  TTS_RANGE_CHECK(p, std_exp, eve::exp); 
}
