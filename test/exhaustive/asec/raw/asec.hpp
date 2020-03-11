//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asec.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on asec")
{
  auto std_asec = tts::vectorize<EVE_TYPE>( [](auto e) { return std::acos(eve::rec(e)); } );
  double th =  std::is_same_v<EVE_VALUE, double> ? 4096 : 512; 
  eve::exhaustive_producer<EVE_TYPE> p1(eve::Valmin<EVE_VALUE>(), EVE_VALUE(-1));
  TTS_ULP_RANGE_CHECK(p1, std_asec, eve::raw_(eve::asec), th); 
  eve::exhaustive_producer<EVE_TYPE> p2(EVE_VALUE(1), eve::Valmax<EVE_VALUE>());
  TTS_ULP_RANGE_CHECK(p2, std_asec, eve::raw_(eve::asec), th);
}
