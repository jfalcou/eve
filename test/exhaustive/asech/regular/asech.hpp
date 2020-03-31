//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asech.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on asech")
{
  auto std_asech = tts::vectorize<EVE_TYPE>( [](auto e) { return std::acosh(eve::rec(e)); } );

  eve::exhaustive_producer<EVE_TYPE> p(EVE_VALUE(-1), EVE_VALUE(1));
  TTS_RANGE_CHECK(p, std_asech, eve::asech); 
}
