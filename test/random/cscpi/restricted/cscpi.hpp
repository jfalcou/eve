//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cscpi")
{
  auto my_stdcscpi =  tts::vectorize<EVE_TYPE>([](auto x){return eve::rec(boost::math::sin_pi(x)); }); 
  eve::rng_producer<EVE_TYPE> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdcscpi, eve::restricted_(eve::cscpi)); 
}
