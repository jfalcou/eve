//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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



TTS_CASE("wide exhaustive check on sinpi") 
{
  auto my_stdsinpi =  tts::vectorize<EVE_TYPE>([](auto x){return boost::math::sin_pi(x); });
  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, my_stdsinpi, eve::big_(eve::sinpi)); 
}



// #include <crlibm.h>

// TTS_CASE("wide exhaustive check on sinpi") 
// {
//   ::crlibm_init(); 
//   auto my_stdsinpi =  tts::vectorize<EVE_TYPE>([](EVE_VALUE x){return EVE_VALUE(::sinpi_rn(x)); });
//   eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
//   TTS_RANGE_CHECK(p, my_stdsinpi, eve::big_(eve::sinpi)); 
// }
