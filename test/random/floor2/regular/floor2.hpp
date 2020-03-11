//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/floor2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on floor2")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_floor2 = tts::vectorize<EVE_TYPE>( [](auto e) { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); } );
    eve::rng_producer<EVE_TYPE> p(eve::Zero<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_floor2, eve::floor2);
  }
  else if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    auto std_floor2 = tts::vectorize<EVE_TYPE>( [](auto e) { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); } );
    eve::rng_producer<EVE_TYPE> p(eve::Zero<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_floor2, eve::floor2);
  }
  else
  {
    auto std_floor2 = tts::vectorize<EVE_TYPE>( [](auto e) { return (e == 0)? 0 : ((e <= 1) ? 1 : std::exp2l(std::floor(std::log2l(e)))); } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_floor2, eve::floor2);
  }
  
  
}
