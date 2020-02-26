//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cos")
{
  auto std_cos = tts::vectorize<Type>( [](auto e) { return std::cos(double(e)); } );

  auto l = eve::Rempio2_limit(eve::medium_type(), Value()>()
  eve::rng_producer<Type> p(-l, l));
  TTS_RANGE_CHECK(p, std_cos, eve::medium_(eve::cos)); 
}
