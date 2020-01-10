//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/prev.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on prev")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_prev = tts::vectorize<Type>( [](auto e) { return (e ==  eve::Minf<Value>()) ?  eve::Nan<Value>() : std::nextafter(e, eve::Minf<Value>()); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_prev, eve::saturated_(eve::prev));
  }
  else
  {
    auto std_prev = tts::vectorize<Type>( [](auto e) { return e == eve::Valmin<Value>() ? e : e-1; } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_prev, eve::saturated_(eve::prev));
  }
    
}
