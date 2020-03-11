//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on ceil2")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_ceil2 = tts::vectorize<EVE_TYPE>( [](auto e) { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); } );
    eve::rng_producer<EVE_TYPE> p(eve::Zero<EVE_VALUE>(), eve::Valmax<EVE_VALUE>()/4);
    TTS_RANGE_CHECK(p, std_ceil2, eve::ceil2);
  }
  else
  {
    auto std_ceil2 = tts::vectorize<EVE_TYPE>( [](auto e) { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), (1ul << (sizeof(EVE_VALUE)*8-2)));
    TTS_RANGE_CHECK(p, std_ceil2, eve::ceil2);
  }
  
  
}
