//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ifloor.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on ifloor")
{
  using vi_t =  eve::detail::as_integer_t<Type>;
  if constexpr(std::is_floating_point_v<Value>)
  {
    using i_t =  eve::detail::as_integer_t<Value>; 
    auto std_ifloor = tts::vectorize<vi_t>( [](auto e) { return i_t(std::floor(e)); } );
    eve::rng_producer<Type> p(eve::Valmin<i_t>(), eve::Valmax<i_t>());
    TTS_RANGE_CHECK(p, std_ifloor, eve::ifloor);
  }
  else
  {
    auto std_ifloor = tts::vectorize<vi_t>( [](auto e) { return e; } );
    eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
    TTS_RANGE_CHECK(p, std_ifloor, eve::ifloor);
  }
  
  
}
