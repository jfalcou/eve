//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nlez.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on is_nlez")
{
  using l_t = eve::as_logical_t<Type>; 
  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_is_nlez = tts::vectorize<l_t>( [](auto e) { return !(e <= Value(0)); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_nlez, eve::is_nlez);
  }
  else
  {
    auto std_is_nlez = tts::vectorize<l_t>( [](auto e) { return e!=Value(0); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_nlez, eve::is_nlez);
  }
  
  
}
