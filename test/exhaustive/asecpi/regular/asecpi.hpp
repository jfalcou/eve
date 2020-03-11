//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/invpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on asecpi")
{
  auto std_asecpi = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::Invpi<EVE_VALUE>()*std::acos(eve::rec(e)); } );

  eve::exhaustive_producer<EVE_TYPE> p1(eve::Valmin<EVE_VALUE>(), EVE_VALUE(-1));
  TTS_RANGE_CHECK(p1, std_asecpi, eve::asecpi); 
  eve::exhaustive_producer<EVE_TYPE> p2(EVE_VALUE(1), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p2, std_asecpi, eve::asecpi); 
}
