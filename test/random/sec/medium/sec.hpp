//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on sec")
{
  auto std_sec = tts::vectorize<Type>( [](auto e) { return 1/std::cos(double(e)); } );
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), Value()); 

  eve::rng_producer<Type>  p(-l, l);
  TTS_RANGE_CHECK(p, std_sec, eve::medium_(eve::sec)); 
}
