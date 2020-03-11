//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atanh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on atanh")
{
  auto std_atanh = tts::vectorize<EVE_TYPE>( [](auto e) { return std::atanh(e); } );

  eve::exhaustive_producer<EVE_TYPE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_atanh, eve::atanh); 
}
