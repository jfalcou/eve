//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cot")
{
  auto std_cot = tts::vectorize<EVE_TYPE>( [](auto e) { return 1/std::tan(double(e)); } );
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), EVE_VALUE()); 

  if constexpr(eve::platform::supports_denormals)
  {
    eve::rng_producer<EVE_TYPE>  p(-l, l);
    TTS_RANGE_CHECK(p, std_cot, eve::medium_(eve::cot));
  }
  else
  {
    eve::rng_producer<EVE_TYPE>  p(eve::Smallestposval<EVE_VALUE>(), l);
    TTS_RANGE_CHECK(p, std_cot, eve::medium_(eve::cot));
  } 
}
