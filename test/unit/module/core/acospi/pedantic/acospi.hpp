//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOS_HPP
#define ACOS_HPP

#include <eve/function/scalar/acospi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/inpi.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check acos return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::acospi)(Type(0)),  Type);
}

TTS_CASE("Check eve::pedantic_(eve::acospi) behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(2)), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(-2)), eve::Nan<Type>(), 0); 
  }
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(eve::Half<Type>()),   Type(1)/3, 0.5);   
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(eve::Mhalf<Type>()),  2*Type(1)/3, 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(eve::Mone<Type>()),   Type(1), 0.5);    
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(eve::One<Type>()),    Type(0), 0);      
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(eve::Zero<Type>()),   Type(1)/2, 0.5);  
  TTS_EXPECT(eve::is_positive(eve::pedantic_(eve::acospi)(eve::One<Type>())));
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(8.414715528e-01)), eve::inpi(std::acos(Type(8.414715528e-01))), 1);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.689134359e-01)), eve::inpi(std::acos(Type(9.689134359e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.922192097e-01)), eve::inpi(std::acos(Type(9.922192097e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.995127916e-01)), eve::inpi(std::acos(Type(9.995127916e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.998779893e-01)), eve::inpi(std::acos(Type(9.998779893e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.999695420e-01)), eve::inpi(std::acos(Type(9.999695420e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.999927878e-01)), eve::inpi(std::acos(Type(9.999927878e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.999984503e-01)), eve::inpi(std::acos(Type(9.999984503e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.999996424e-01)), eve::inpi(std::acos(Type(9.999996424e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.999999404e-01)), eve::inpi(std::acos(Type(9.999999404e-01))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::acospi)(Type(9.999999404e-01)), eve::inpi(std::acos(Type(9.999999404e-01))), 0.5);
} 
#endif
