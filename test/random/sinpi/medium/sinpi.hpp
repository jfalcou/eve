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
#include <eve/function/sinpi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE("wide random check on sinpi")
{
  
  auto my_stdsinpi =  tts::vectorize<Type>([](auto x){return boost::math::sin_pi(x); }); 
  eve::rng_producer<Type> p(Value(-100000.0), Value(100000.0));
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::medium_(eve::sinpi)); 
}
