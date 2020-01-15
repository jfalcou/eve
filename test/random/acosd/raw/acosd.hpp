//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosd.hpp>
#include <eve/function/indeg.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on acosd")
{
  auto std_acosd = tts::vectorize<Type>( [](auto e) { return eve::indeg(std::acos(e)); } );
  double th = std::is_same_v<Value, double> ? 8192.0 : 1024.0; 

  eve::rng_producer<Type> p(-1, 1);
  TTS_ULP_RANGE_CHECK(p, std_acosd, eve::raw_(eve::acosd), th); 
}
