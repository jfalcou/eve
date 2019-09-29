//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ASECPI_HPP
#define ASECPI_HPP

#include <eve/function/scalar/asecpi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>  
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check asecpi return type")
{
  TTS_EXPR_IS(eve::asecpi(Type(0)),  Type);
}

TTS_CASE("Check eve::asecpi behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asecpi(eve::Inf<Type>()),     Type(0.5), 0);
    TTS_ULP_EQUAL(eve::asecpi(eve::Minf<Type>()),    Type(0.5), 0);
  }
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asecpi(eve::Nan<Type>()),     eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asecpi(eve::Zero<Type>()),    eve::Nan<Type>(), 1);
    TTS_ULP_EQUAL(eve::asecpi(eve::Mzero<Type>()),   eve::Nan<Type>(), 1);       
  }  
  TTS_ULP_EQUAL(eve::asecpi(Type(-2)),             Type(2)/3, 1);
  TTS_ULP_EQUAL(eve::asecpi(Type(2)),              Type(1)/3, 1);
  TTS_ULP_EQUAL(eve::asecpi(eve::Mone<Type>()),    Type(1), 0.5);
  TTS_ULP_EQUAL(eve::asecpi(eve::One<Type>()),     eve::Zero<Type>(), 0.5);
} 

#endif
