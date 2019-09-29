//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOTPI_HPP
#define ACOTPI_HPP

#include <eve/function/scalar/acotpi.hpp>
#include <eve/function/scalar/inpi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/smallestposval.hpp>
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

TTS_CASE("Check eve::acotpi return type")
{
  TTS_EXPR_IS(eve::acotpi(Type(0)),  Type);
}

TTS_CASE("Check eve::acotpi behavior")
{

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::Inf<Type>()),  0, 0);
    TTS_ULP_EQUAL(eve::acotpi(eve::Minf<Type>()), 0, 0);
  }
  TTS_ULP_EQUAL(eve::acotpi(eve::Half<Type>()),   eve::inpi(Type(1.107148717794090e+00)), 1.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::Mhalf<Type>()),  eve::inpi(Type(-1.107148717794090e+00)), 1.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::Mzero<Type>()),  Type(-0.5), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::Mone<Type>()),   Type(-0.25), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::One<Type>()),    Type(0.25), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::Zero<Type>()),   Type(0.5), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::rec(eve::Smallestposval<Type>())), eve::inpi(eve::Smallestposval<Type>()), 0.5);

}


#endif
