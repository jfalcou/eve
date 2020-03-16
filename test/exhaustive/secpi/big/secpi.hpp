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



TTS_CASE("wide exhaustive check on secpi") 
{
  auto my_stdsecpi =  tts::vectorize<EVE_TYPE>([](auto x){return ((eve::frac(std::abs(x)) == eve::Half<EVE_VALUE>()))
                                               ?  eve::Nan<EVE_VALUE>()
                                               : eve::rec(boost::math::cos_pi(x)); });
  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, my_stdsecpi, eve::big_(eve::secpi)); 
}
