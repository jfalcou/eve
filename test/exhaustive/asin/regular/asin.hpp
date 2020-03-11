//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on asin")
{
  auto std_asin = tts::vectorize<EVE_TYPE>( [](auto e) { return std::asin(e); } );

  eve::exhaustive_producer<EVE_TYPE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_asin, eve::asin); 
}
