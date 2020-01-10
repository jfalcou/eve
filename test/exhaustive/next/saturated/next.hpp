//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/next.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on next")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_next = tts::vectorize<Type>( [](auto e) { return (e ==  eve::Inf<Value>()) ?  eve::Nan<Value>() : std::nextafter(e, eve::Inf<Value>()); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_next, eve::saturated_(eve::next));
  }
  else
  {
    auto std_next = tts::vectorize<Type>( [](auto e) { return e == eve::Valmax<Value>() ? e : e+1; } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_next, eve::saturated_(eve::next));
  }
  
  
}
