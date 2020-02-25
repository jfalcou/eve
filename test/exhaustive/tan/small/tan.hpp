//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/pio_2.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on tan")
{
  auto std_tan = tts::vectorize<Type>( [](auto e) { return std::tan(double(e)); } );

  eve::exhaustive_producer<Type> p(-eve::Pio_2<Value>(), eve::Pio_2<Value>());
  TTS_RANGE_CHECK(p, std_tan, eve::small_(eve::tan)); 
}
