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
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>

TTS_CASE("wide random check on tan")
{
  auto std_tan = tts::vectorize<Type>( [](auto e) { return std::tan(e); } );
  auto l = eve::Rempio2_limit(eve::medium_type(), Value()); 

  eve::exhaustive_producer<Type>  p(-l, l);
  TTS_RANGE_CHECK(p, std_tan, eve::medium_(eve::tan)); 
}
