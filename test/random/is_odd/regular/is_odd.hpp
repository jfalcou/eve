//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE("wide random check on is_odd")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    using l_t = eve::as_logical_t<EVE_TYPE>; 
    auto std_is_odd = tts::vectorize<l_t>( [](auto e) {  auto da = eve::dec(e);     
                                              return (e!= da) && eve::is_even(da); } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
  else 
  {
    using l_t = eve::as_logical_t<EVE_TYPE>; 
    auto std_is_odd = tts::vectorize<l_t>( [](auto e) { return  (e/2)*2!= e; } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_is_odd, eve::is_odd);
  }
  
}
