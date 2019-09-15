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
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check asinpi return type")
{
  TTS_EXPR_IS(eve::asinpi(Type(0)),  Type);
}

TTS_CASE("Check eve::asinpi behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::asinpi(eve::Inf<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::asinpi(eve::Minf<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::asinpi(eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::asinpi(eve::Half<Type>()), 1/Type(6), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Mhalf<Type>()),1/Type(-6), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Mone<Type>()), Type(-0.5), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::One<Type>()), Type(0.5), 0.5);
  TTS_ULP_EQUAL(eve::asinpi(eve::Zero<Type>()),Type(0), 0); 
}


#endif
