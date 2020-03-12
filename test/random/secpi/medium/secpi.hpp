//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/secpi.hpp>
#include <tts/tests/range.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/rec.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <type_traits>

TTS_CASE("wide random check on secpi")
{
  auto my_stdsecpi =  tts::vectorize<EVE_TYPE>([](auto x){return ((x < eve::Maxflint<EVE_VALUE>()) && eve::is_odd(x*2)) ? eve::Nan<EVE_VALUE>() : eve::rec(boost::math::cos_pi(x)); });
  eve::rng_producer<EVE_TYPE> p(EVE_VALUE(-100000.0), EVE_VALUE(100000.0));
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::medium_(eve::secpi)); 
}
