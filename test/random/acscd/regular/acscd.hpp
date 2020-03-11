//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscd.hpp>
#include <eve/function/indeg.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on acscd")
{
  auto std_acscd = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::indeg(std::asin(eve::rec(e))); } );

  eve::rng_producer<EVE_TYPE> p1(eve::Valmin<EVE_VALUE>(), EVE_VALUE(-1));
  TTS_RANGE_CHECK(p1, std_acscd, eve::acscd); 
  eve::rng_producer<EVE_TYPE> p2(EVE_VALUE(1), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p2, std_acscd, eve::acscd); 

}
