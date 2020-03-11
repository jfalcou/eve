//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/eps.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on eps")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_eps = tts::vectorize<EVE_TYPE>( [](auto e) { return (e > 0 ? e : -e)*eve::Eps<EVE_VALUE>()/2; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_eps, eve::eps);
  }
  else
  {
    auto std_eps = tts::vectorize<EVE_TYPE>( [](auto e) { return  EVE_VALUE(1); } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_eps, eve::eps);
  }
  
}
