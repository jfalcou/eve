//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_not.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on logical_not")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_logical_not = tts::vectorize<Type>( [](auto e) { return std::logical_not(e); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_logical_not, eve::logical_not);
  }
  else if constexpr(std::is_signed_v<Value>)
  {
    auto std_logical_not = tts::vectorize<Type>( [](auto e) { return  std::logical_not(e); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_logical_not, eve::logical_not);
  }
  else
  {
    auto std_logical_not = tts::vectorize<Type>( [](auto e) { return e; } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_logical_not, eve::logical_not);
  }
  
  
}
