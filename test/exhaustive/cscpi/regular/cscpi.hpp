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
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>    
#include <eve/constant/nan.hpp>
#include <eve/function/is_flint.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide exhaustive check on cscpi")
{
  auto my_stdcscpi =  tts::vectorize<Type>([](auto x){return (x == 0 || !eve::is_flint(x)) ? eve::rec(boost::math::sin_pi(x)) : eve::Nan<Value>(); });
  eve::exhaustive_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, my_stdcscpi, eve::cscpi); 
}
