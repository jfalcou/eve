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
#include <eve/function/cospi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>



TTS_CASE("wide random check on cospi") 
{
  auto my_stdcospi =  tts::vectorize<EVE_TYPE>([](auto x){return boost::math::cos_pi(x); });
  eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, my_stdcospi, eve::big_(eve::cospi)); 
}



// #include <crlibm.h>

// TTS_CASE("wide random check on cospi") 
// {
//   ::crlibm_init(); 
//   auto my_stdcospi =  tts::vectorize<EVE_TYPE>([](EVE_VALUE x){return EVE_VALUE(::cospi_rn(x)); });
//   eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
//   TTS_RANGE_CHECK(p, my_stdcospi, eve::big_(eve::cospi)); 
// }
