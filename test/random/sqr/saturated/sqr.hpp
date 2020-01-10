//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

TTS_CASE("wide random check on sqr")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_sqr = tts::vectorize<Type>( [](auto e) { return e*e; } );
    eve::rng_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_sqr, eve::saturated_(eve::sqr));
  }
  else if constexpr(std::is_signed_v<Value>)
  {
    auto std_sqr = tts::vectorize<Type>( [](auto e) { return eve::abs(e) > eve::Sqrtvalmax<Value>() ? eve::Valmax<Value>() : e*e; } );
    eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_sqr, eve::sqr);
  }
  else
  {
    auto std_sqr = tts::vectorize<Type>( [](auto e) { return e > eve::Sqrtvalmax<Value>() ? eve::Valmax<Value>() : e*e; } );
    eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_sqr, eve::sqr);
  }
  
  
}
