//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ASINPI_HPP
#define ASINPI_HPP

#include <eve/function/scalar/asinpi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>  
#include <eve/constant/nan.hpp>
#include <eve/function/scalar/is_negative.hpp>
#include <eve/function/scalar/is_positive.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check asinpi return type")
{
  TTS_EXPR_IS(eve::asinpi(Type(0)),  Type);
}

TTS_CASE("Check eve::eve::asinpi behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asinpi(eve::Nan<Type>()),     eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asinpi(Type(2)),              eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asinpi(Type(-2)),             eve::Nan<Type>(), 0);       
  }  
  TTS_ULP_EQUAL(eve::asinpi(eve::Half<Type>()),    Type(1)/6, 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Mhalf<Type>()),   -Type(1)/6, 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Mone<Type>()),    -Type(0.5), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::One<Type>()),     Type(0.5), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Zero<Type>()),    eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Mzero<Type>()),   eve::Zero<Type>(), 0.5);
  TTS_EXPECT(eve::is_negative(eve::asinpi(eve::Mzero<Type>())));
  TTS_EXPECT(eve::is_positive(eve::asinpi(eve::Zero<Type>())));
} 

#endif
