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
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check cosd return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::cosd)(Type(0)),  Type);
}

TTS_CASE("Check eve::restricted_(eve::cosd) behavior")
{
  using eve::cosd; 

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::restricted_(cosd)(eve::Inf<Type>()),  eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(eve::Minf<Type>()), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(eve::Nan<Type>()),  eve::Nan<Type>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::restricted_(cosd)(Type(-180)),       eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(Type(-45)),        eve::Sqrt_2o_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(Type(-90)),        eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(Type(180)),        eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(Type(45)),         eve::Sqrt_2o_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(Type(90)),         eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(cosd)(eve::Zero<Type>()), eve::One<Type>(), 0.5);
}



#endif
