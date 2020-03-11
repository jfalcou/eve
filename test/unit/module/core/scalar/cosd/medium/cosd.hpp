//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COSD_HPP
#define COSD_HPP

#include <eve/function/scalar/cosd.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/sqrt_2o_2.hpp>  
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check cosd return type")
{
  TTS_EXPR_IS(eve::medium_(eve::cosd)(EVE_TYPE(0)),  EVE_TYPE);
}

TTS_CASE("Check eve::medium_(eve::cosd) behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Inf<EVE_TYPE>()),  eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Minf<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Nan<EVE_TYPE>()),  eve::Nan<EVE_TYPE>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(-180)),       eve::Mone<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(-45)),        eve::Sqrt_2o_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(-90)),        eve::Zero<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(180)),        eve::Mone<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(45)),         eve::Sqrt_2o_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(90)),         eve::Zero<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Zero<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(135)/2), EVE_TYPE(0.3826834323650897717284599840304), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(270)), eve::Zero<EVE_TYPE>(), 1);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(EVE_TYPE(-270)), eve::Zero<EVE_TYPE>(), 1);
}



#endif
