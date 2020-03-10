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
#include <eve/function/cotpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>



TTS_CASE("wide exhaustive check on cotpi") 
{
  auto my_stdcotpi =  tts::vectorize<Type>([](auto x){return (x == 0 || !eve::is_flint(x))
                                               ? boost::math::cos_pi(x)/boost::math::sin_pi(x)
                                               : eve::Nan<Value>(); });
  eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, my_stdcotpi, eve::big_(eve::cotpi)); 
}
