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
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on tanpi")
{
  auto my_stdtanpi =  tts::vectorize<Type>([](auto x){return boost::math::sin_pi(x)/boost::math::cos_pi(x); }); 
  eve::rng_producer<Type> p(-0.25, 0.25);
  TTS_RANGE_CHECK(p, my_stdtanpi, eve::restricted_(eve::tanpi)); 
}
