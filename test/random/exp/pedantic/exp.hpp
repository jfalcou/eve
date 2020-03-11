//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on exp")
{
  auto std_exp = tts::vectorize<EVE_TYPE>( [](auto e) { return std::exp(e); } );

  eve::rng_producer<EVE_TYPE> p(eve::Minlog<EVE_VALUE>(), eve::Maxlog<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_exp, eve::pedantic_(eve::exp)); 
}
