//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/pio_4.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on csc")
{
  auto std_csc = tts::vectorize<Type>( [](auto e) { return 1/std::sin(double(e)); } );

  eve::exhaustive_producer<Type> p(-eve::Pio_4<Value>(), eve::Pio_4<Value>());
  TTS_RANGE_CHECK(p, std_csc, eve::restricted_(eve::csc)); 
}
