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
#include <eve/function/secpi.hpp>
#include <tts/tests/range.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE("wide exhaustive check on secpi")
{
  auto my_stdsecpi =  tts::vectorize<Type>([](auto x){return ((eve::frac(std::abs(x)) == eve::Half<Value>()))
                                               ?  eve::Nan<Value>()
                                               : eve::rec(boost::math::cos_pi(x)); });
  eve::exhaustive_producer<Type> p(Value(-100000.0), Value(100000.0));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::medium_(eve::secpi)); 
}
