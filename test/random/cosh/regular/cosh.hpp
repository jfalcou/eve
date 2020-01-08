//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cosh")
{
  auto std_cosh = tts::vectorize<Type>( [](auto e) { return std::cosh(e); } );

  eve::rng_producer<Type> p(-eve::Maxlog<Value>(), eve::Maxlog<Value>());
  TTS_RANGE_CHECK(p, std_cosh, eve::cosh); 
}
