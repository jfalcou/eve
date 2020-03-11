//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_real.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on is_real")
{
  using l_t = eve::as_logical_t<EVE_TYPE>; 
  auto std_is_real = tts::vectorize<l_t>( [](auto e) { return true; } );

  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_is_real, eve::is_real); 
}
