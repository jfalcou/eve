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
#include <eve/constant/reduce_medium_limits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide rng check on csc")
{
  auto std_csc = tts::vectorize<Type>( [](auto e) { return 1/std::sin(double(e)); } );

  if constexpr(eve::platform::supports_denormals)
  {
    eve::rng_producer<Type>  p(-eve::Reduce_medium_limits<Value>(), eve::Reduce_medium_limits<Value>());
    TTS_RANGE_CHECK(p, std_csc, eve::medium_(eve::csc));
  }
  else
  {
    eve::rng_producer<Type>  p(eve::Smallestposval<Value>(), eve::Reduce_medium_limits<Value>());
    TTS_RANGE_CHECK(p, std_csc, eve::medium_(eve::csc));
  }
}
