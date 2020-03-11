//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on sqr")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_sqr = tts::vectorize<EVE_TYPE>( [](auto e) { return e*e; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>()+1, eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_sqr, eve::saturated_(eve::sqr));
  }
  else if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    auto std_sqr = tts::vectorize<EVE_TYPE>( [](auto e) { return eve::abs(e) > eve::Sqrtvalmax<EVE_VALUE>() ? eve::Valmax<EVE_VALUE>() : e*e; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_sqr, eve::sqr);
  }
  else
  {
    auto std_sqr = tts::vectorize<EVE_TYPE>( [](auto e) { return e > eve::Sqrtvalmax<EVE_VALUE>() ? eve::Valmax<EVE_VALUE>() : e*e; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_sqr, eve::sqr);
  }
  
  
}
