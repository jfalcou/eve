//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sech.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/maxlog.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on sech")
{
  auto std_sech = tts::vectorize<EVE_TYPE>( [](auto e) { return EVE_VALUE(1)/std::cosh(double(e)); } );

  eve::exhaustive_producer<EVE_TYPE> p(eve::Minlog<EVE_VALUE>()+1, eve::Maxlog<EVE_VALUE>()-1);
  TTS_RANGE_CHECK(p, std_sech, eve::sech); 
}
