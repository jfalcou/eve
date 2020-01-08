//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_inf.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on is_not_inf")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    auto std_is_not_inf = tts::vectorize<Type>( [](auto e) { return std::is_not_inf(e); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_not_inf, eve::is_not_inf);
  }
  else if constexpr(std::is_signed_v<Value>)
  {
    auto std_is_not_inf = tts::vectorize<Type>( [](auto e) { return  std::is_not_inf(e); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_not_inf, eve::is_not_inf);
  }
  else
  {
    auto std_is_not_inf = tts::vectorize<Type>( [](auto e) { return e; } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_not_inf, eve::is_not_inf);
  }
  
  
}
