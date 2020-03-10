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
#include <tts/tests/range.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE("wide exhaustive check on tanpi")
{
  auto my_stdtanpi =  tts::vectorize<Type>([](auto x){return  ((eve::frac(std::abs(x)) == eve::Half<Value>()))
                                               ?  eve::Nan<Value>()
                                               : boost::math::sin_pi(x)/boost::math::cos_pi(x); });
  eve::exhaustive_producer<Type> p(Value(-100000.0), Value(100000.0));
  TTS_RANGE_CHECK(p, my_stdtanpi, eve::medium_(eve::tanpi)); 
}
