//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on oneminus")
{
  if constexpr(std::is_unsigned_v<EVE_VALUE>)
  {
    auto std_oneminus = tts::vectorize<EVE_TYPE>( [](auto e) { return EVE_VALUE(1)-e; } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);  
    
  }
  else
  {
    auto std_oneminus = tts::vectorize<EVE_TYPE>( [](auto e) { return EVE_VALUE(1)-e; } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>()+1, eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);  
  }
}
