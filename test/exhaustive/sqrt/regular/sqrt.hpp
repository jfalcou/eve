//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on sqrt")
{
  auto std_sqrt = tts::vectorize<EVE_TYPE>( [](auto e) { return std::sqrt(e); } );

  eve::exhaustive_producer<EVE_TYPE> p(EVE_VALUE(0), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_sqrt, eve::sqrt); 
}
