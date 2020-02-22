//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/reduce_medium_limits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on cot")
{
  auto std_cot = tts::vectorize<Type>( [](auto e) { return 1/std::tan(double(e)); } );

  if constexpr(eve::platform::supports_denormals)
  {
    eve::exhaustive_producer<Type>  p(-eve::Reduce_medium_limits<Value>(), eve::Reduce_medium_limits<Value>());
    TTS_RANGE_CHECK(p, std_cot, eve::medium_(eve::cot));
  }
  else
  {
    eve::exhaustive_producer<Type>  p(eve::Smallestposval<Value>(), eve::Reduce_medium_limits<Value>());
    TTS_RANGE_CHECK(p, std_cot, eve::medium_(eve::cot));
  }
}
