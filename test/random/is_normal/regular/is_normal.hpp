//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_normal.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/as_logical.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on is_normal")
{
  using l_t = eve::as_logical_t<EVE_TYPE>; 
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_is_normal = tts::vectorize<l_t>( [](auto e) { return std::fpclassify(e) == FP_NORMAL; } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_is_normal, eve::is_normal);
  }
  else
  {
    auto std_is_normal = tts::vectorize<l_t>( [](auto e) { return e !=  EVE_VALUE(0); } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_is_normal, eve::is_normal);
  }
  
  
}
