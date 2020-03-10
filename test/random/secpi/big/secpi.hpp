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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/rec.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>



TTS_CASE("wide random check on secpi") 
{
  auto my_stdsecpi =  tts::vectorize<Type>([](auto x){return ((x < eve::Maxflint<Value>()) && eve::is_odd(x*2)) ?  eve::Nan<Value>() : eve::rec(boost::math::cos_pi(x)); });
  eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::big_(eve::secpi)); 
}
