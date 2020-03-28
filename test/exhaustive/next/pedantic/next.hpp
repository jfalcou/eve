//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/next.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/is_negative.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on next")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_next = tts::vectorize<EVE_TYPE>( [](auto e) { return (e == 0) && eve::is_negative(e) ? eve::Zero<EVE_VALUE>()
                                                  :  ((e ==  eve::Inf<EVE_VALUE>()) ?  eve::Nan<EVE_VALUE>()
                                                      : std::nextafter(e, eve::Inf<EVE_VALUE>())); } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_ULP_RANGE_CHECK(p, std_next, eve::pedantic_(eve::next), 0);
  }
  else
  {
    auto std_next = tts::vectorize<EVE_TYPE>( [](auto e) { return e == eve::Valmax<EVE_VALUE>() ? e : e+1; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_ULP_RANGE_CHECK(p, std_next, eve::pedantic_(eve::next), 0);
  }
  
  
}
