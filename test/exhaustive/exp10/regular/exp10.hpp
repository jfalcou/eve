//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/maxlog10.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on exp10")
{
  auto std_exp10 = tts::vectorize<Type>( [](auto e) { return ::exp10(e); } );

  eve::exhaustive_producer<Type> p(eve::Minlog10<Value>(), eve::Maxlog10<Value>());
  TTS_RANGE_CHECK(p, std_exp10, eve::exp10); 
}
