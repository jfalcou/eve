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
  TTS_EXPR_IS(eve::medium_(eve::cosd)(Type(0)),  Type);
}

TTS_CASE("Check eve::medium_(eve::cosd) behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Inf<Type>()),  eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Minf<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Nan<Type>()),  eve::Nan<Type>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(-180)),       eve::Mone<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(-45)),        eve::Sqrt_2o_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(-90)),        eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(180)),        eve::Mone<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(45)),         eve::Sqrt_2o_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(90)),         eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(eve::Zero<Type>()), eve::One<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(135)/2), Type(0.3826834323650897717284599840304), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(270)), eve::Zero<Type>(), 1);
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(Type(-270)), eve::Zero<Type>(), 1);
}



#endif
