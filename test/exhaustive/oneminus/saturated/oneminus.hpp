//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide exhaustive check on oneminus")
{

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    auto std_oneminus = tts::vectorize<EVE_TYPE>( [](auto e) { return e < eve::Valmin<EVE_VALUE>()+2 ? eve::Valmax<EVE_VALUE>() : EVE_VALUE(1)-e; } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_oneminus, eve::saturated_(eve::oneminus));
  }
  else
  {
    auto std_oneminus = tts::vectorize<EVE_TYPE>( [](auto e) { return (e == 0) ? EVE_VALUE(1) : EVE_VALUE(0); } );
    eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_oneminus,  eve::saturated_(eve::oneminus));
  }
}
