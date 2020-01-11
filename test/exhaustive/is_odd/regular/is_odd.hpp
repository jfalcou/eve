//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_odd.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/dec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on is_odd")
{

  if constexpr(std::is_floating_point_v<Value>)
  {
    using l_t = eve::as_logical_t<Type>; 
    auto std_is_odd = tts::vectorize<l_t>( [](auto e) {  auto da = eve::dec(e);     
                                              return (e!= da) && eve::is_even(da); } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
  else 
  {
    using l_t = eve::as_logical_t<Type>; 
    auto std_is_odd = tts::vectorize<l_t>( [](auto e) { return  (e/2)*2!= e; } );
    eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
  
}
