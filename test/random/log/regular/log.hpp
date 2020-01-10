//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on log")
{
  auto std_log = tts::vectorize<Type>( [](auto e) { return std::log(e); } );

  eve::rng_producer<Type> p(eve::Zero<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_log, eve::log); 
}
