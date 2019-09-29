//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATANPI_HPP
#define ATANPI_HPP

#include <eve/function/scalar/atanpi.hpp>
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
#include <eve/function/scalar/is_negative.hpp>
#include <eve/function/scalar/is_positive.hpp>
#include <eve/function/scalar/inpi.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check atanpi return type")
{
  TTS_EXPR_IS(eve::atanpi(Type(0)),  Type);
}

TTS_CASE("Check eve::eve::atanpi behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atanpi(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atanpi(eve::Inf<Type>()),   Type(0.5), 0);
    TTS_ULP_EQUAL(eve::atanpi(eve::Minf<Type>()), -Type(0.5), 0);
  }
  TTS_ULP_EQUAL(eve::atanpi(eve::Half<Type>()),  eve::inpi(Type(4.636476090008061e-01)),  0.5);
  TTS_ULP_EQUAL(eve::atanpi(eve::Mhalf<Type>()), eve::inpi(Type(-4.636476090008061e-01)), 0.5);
  TTS_ULP_EQUAL(eve::atanpi(eve::Mone<Type>()),  -Type(0.25),                             0.5);
  TTS_ULP_EQUAL(eve::atanpi(eve::One<Type>()),   Type(0.25),                              0.5);
  TTS_ULP_EQUAL(eve::atanpi(eve::Zero<Type>()),   eve::Zero<Type>(),                      0.5);        
  TTS_EXPECT(eve::is_negative(eve::atanpi(eve::Mzero<Type>())));
  TTS_EXPECT(eve::is_positive(eve::atanpi(eve::Zero<Type>())));
}  


#endif
