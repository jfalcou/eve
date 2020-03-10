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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>



TTS_CASE("wide random check on sinpi") 
{
  auto my_stdsinpi =  tts::vectorize<Type>([](auto x){return boost::math::sin_pi(x); });
  eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::big_(eve::sinpi)); 
}



// #include <crlibm.h>

// TTS_CASE("wide random check on sinpi") 
// {
//   ::crlibm_init(); 
//   auto my_stdsinpi =  tts::vectorize<Type>([](Value x){return Value(::sinpi_rn(x)); });
//   eve::rng_producer<Type> p(eve::Valmin<Value>(), eve::Valmax<Value>());
//   TTS_RANGE_CHECK(p, my_stdsinpi, eve::big_(eve::sinpi)); 
// }
