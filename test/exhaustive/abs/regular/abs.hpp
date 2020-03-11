//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on abs")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_abs = tts::vectorize<EVE_TYPE>( [](auto e) { return (e < 0) ? -e : e; } );
    eve::exhaustive_producer<EVE_TYPE> p(-1,1);
    TTS_RANGE_CHECK(p, std_abs, eve::abs);
  }
  else if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    auto std_abs = tts::vectorize<EVE_TYPE>( [](auto e) {
                                           return (e < 0) ? -e : e; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_abs, eve::abs);
  }
  else
  {
    auto std_abs = tts::vectorize<EVE_TYPE>( [](auto e) { return e; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_abs, eve::abs);
  }
  
  
}
