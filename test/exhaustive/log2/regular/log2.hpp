//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on log2")
{
  auto std_log2 = tts::vectorize<Type>( [](auto e) { return std::log2(e); } );

  eve::exhaustive_producer<Type> p(eve::Zero<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_log2, eve::log2); 
}
