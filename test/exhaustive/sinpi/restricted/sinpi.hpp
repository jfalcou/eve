//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/constant/pi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sinpi")
{
  auto std_sinpi = tts::vectorize<Type>( [](auto e) { return std::sin(double(e)*eve::Pi<double>()); } );

  eve::exhaustive_producer<Type> p(-Value(0.25), Value(0.25));
  TTS_RANGE_CHECK(p, std_sinpi, eve::restricted_(eve::sinpi)); 
}
