//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/bit_shr.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on popcount")
{
  using u_t =  eve::detail::as_integer_t<EVE_TYPE, unsigned>; 
  auto std_popcount = tts::vectorize<u_t>(
    [](auto e) { unsigned int j = 0;
      for(int i = 0; i < sizeof(EVE_VALUE)*8; ++i)
      {
        if (e&EVE_VALUE(1)) ++j;
        e = eve::bit_shr(e, 1);
      }
      return j; }
  );

  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_popcount, eve::popcount); 
}
