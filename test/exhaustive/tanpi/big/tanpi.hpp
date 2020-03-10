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
#include <eve/function/tanpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>



TTS_CASE("wide exhaustive check on tanpi") 
{
  auto my_stdtanpi =  tts::vectorize<Type>([](auto x){return ((eve::frac(std::abs(x)) == eve::Half<Value>()))
                                               ?  eve::Nan<Value>()
                                               : boost::math::sin_pi(x)/boost::math::cos_pi(x); });
  eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, my_stdtanpi, eve::big_(eve::tanpi)); 
}
