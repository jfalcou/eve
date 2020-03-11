//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on acosh")
{
  auto std_acosh = tts::vectorize<EVE_TYPE>( [](auto e) { return std::acosh(e); } );

  eve::exhaustive_producer<EVE_TYPE> p(EVE_VALUE(1), eve::Maxlog<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_acosh, eve::acosh); 
}
