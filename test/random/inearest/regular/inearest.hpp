//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE("wide random check on inearest")
{
  using vi_t =  eve::detail::as_integer_t<EVE_TYPE>; 
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>; 
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return i_t(std::nearbyint(e)); } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<i_t>(), eve::Valmax<i_t>());
    TTS_RANGE_CHECK(p, std_inearest, eve::inearest);
  }
  else
  {
    auto std_inearest = tts::vectorize<vi_t>( [](auto e) { return e; } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_inearest, eve::inearest);
  }
  
  
}
