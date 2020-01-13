//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inearest.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on inearest")
{
  using vi_t =  eve::detail::as_integer_t<Type>; 
  if constexpr(std::is_floating_point_v<Value>)
  {
    using i_t =  eve::detail::as_integer_t<Value>; 
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return i_t(std::nearbyint(e)); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_inearest, eve::inearest);
  }
  else
  {
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return e; } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_inearest, eve::inearest);
  }
  
  
}
