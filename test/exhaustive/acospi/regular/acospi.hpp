//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acospi.hpp>
#include <eve/constant/invpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on acospi")
{
  auto std_acospi = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::Invpi<EVE_VALUE>()*std::acos(e); } );

  eve::exhaustive_producer<EVE_TYPE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_acospi, eve::acospi); 
}
