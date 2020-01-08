//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on arg")
{
  auto std_arg = tts::vectorize<Type>( [](auto e) { return eve::is_negative(e) ? eve::Pi<Value>() : eve::Zero<Value>(); } );

  eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_arg, eve::pedantic_(eve::arg)); 
}
