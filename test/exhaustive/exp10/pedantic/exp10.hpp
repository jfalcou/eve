//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/maxlog10.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on exp10")
{
  auto std_exp10 = tts::vectorize<EVE_TYPE>( [](auto e) { return ::exp10(e); } );

  eve::exhaustive_producer<EVE_TYPE> p(eve::Minlog10<EVE_VALUE>(), eve::Maxlog10<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_exp10, eve::pedantic_(eve::exp10)); 
}
