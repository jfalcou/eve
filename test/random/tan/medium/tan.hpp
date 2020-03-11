//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on tan")
{
  auto std_tan = tts::vectorize<EVE_TYPE>( [](auto e) { return std::tan(e); } );
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), EVE_VALUE()); 

  eve::rng_producer<EVE_TYPE> p(-l, l);
  TTS_RANGE_CHECK(p, std_tan, eve::medium_(eve::tan)); 
}
