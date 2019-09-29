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

#include <eve/function/scalar/acosd.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/indeg.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check acos return type")
{
  TTS_EXPR_IS(eve::acosd(Type(0)),  Type);
}

TTS_CASE("Check eve::acosd behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acosd(Type(2)), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::acosd(Type(-2)), eve::Nan<Type>(), 0); 
  }
  TTS_ULP_EQUAL(eve::acosd(eve::Half<Type>()),    Type(60), 0.5);
  TTS_ULP_EQUAL(eve::acosd(eve::Mhalf<Type>()),   Type(120), 0.5);
  TTS_ULP_EQUAL(eve::acosd(eve::Mone<Type>()),    Type(180), 0.5);
  TTS_ULP_EQUAL(eve::acosd(eve::One<Type>()),     Type(0), 0);
  TTS_ULP_EQUAL(eve::acosd(eve::Zero<Type>()),    Type(90), 0.5);   
  TTS_EXPECT(eve::is_positive(eve::acosd(eve::One<Type>())));
  TTS_ULP_EQUAL(eve::acosd(Type(8.414715528e-01)), eve::indeg(std::acos(Type(8.414715528e-01))), 1.5 );
  TTS_ULP_EQUAL(eve::acosd(Type(9.689134359e-01)), eve::indeg(std::acos(Type(9.689134359e-01))), 4.0 );
  TTS_ULP_EQUAL(eve::acosd(Type(9.922192097e-01)), eve::indeg(std::acos(Type(9.922192097e-01))), 7.5 );
  TTS_ULP_EQUAL(eve::acosd(Type(9.995127916e-01)), eve::indeg(std::acos(Type(9.995127916e-01))), 26.5);
  TTS_ULP_EQUAL(eve::acosd(Type(9.998779893e-01)), eve::indeg(std::acos(Type(9.998779893e-01))), 44.5);
  TTS_ULP_EQUAL(eve::acosd(Type(9.999695420e-01)), eve::indeg(std::acos(Type(9.999695420e-01))), 142);
  TTS_ULP_EQUAL(eve::acosd(Type(9.999927878e-01)), eve::indeg(std::acos(Type(9.999927878e-01))), 234 );
  TTS_ULP_EQUAL(eve::acosd(Type(9.999984503e-01)), eve::indeg(std::acos(Type(9.999984503e-01))), 361.5);
  TTS_ULP_EQUAL(eve::acosd(Type(9.999996424e-01)), eve::indeg(std::acos(Type(9.999996424e-01))), 867.5);
  TTS_ULP_EQUAL(eve::acosd(Type(9.999999404e-01)), eve::indeg(std::acos(Type(9.999999404e-01))), 1643.5);
} 
#endif
