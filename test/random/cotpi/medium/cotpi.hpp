//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>
#include <eve/function/cotpi.hpp>
#include <tts/tests/range.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE("wide random check on cotpi")
{
  auto my_stdcotpi =  tts::vectorize<Type>([](auto x){return (x == 0 || !eve::is_flint(x))
                                               ? boost::math::cos_pi(x)/boost::math::sin_pi(x)
                                               : eve::Nan<Value>(); });
  eve::rng_producer<Type> p(Value(-100000.0), Value(100000.0));
  TTS_RANGE_CHECK(p, my_stdcotpi, eve::medium_(eve::cotpi)); 
}
