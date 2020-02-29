//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on cosh")
{
  auto std_cosh = tts::vectorize<Type>( [](auto e) { return std::cosh(double(e)); } );

  eve::exhaustive_producer<Type> p(eve::Valmin<Value>()+1, eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, std_cosh, eve::cosh); 
}
