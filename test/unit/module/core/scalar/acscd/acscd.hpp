//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACSCD_HPP
#define ACSCD_HPP

#include <eve/function/scalar/acscd.hpp>
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

TTS_CASE("Check acscd return type")
{
  TTS_EXPR_IS(eve::acscd(Type(0)),  Type);
}

TTS_CASE("Check eve::acscd behavior")
{

#ifndef BOOST_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::acscd(eve::Inf<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::acscd(eve::Minf<Type>()), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::acscd(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::acscd(eve::Zero<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::acscd(-Type(2)), Type(-30), 0.5);
  TTS_ULP_EQUAL(eve::acscd(eve::Mone<Type>()), Type(-90), 0.5);
  TTS_ULP_EQUAL(eve::acscd(eve::One<Type>()),  Type(90), 0.5);
  TTS_ULP_EQUAL(eve::acscd(Type(2)),  Type(30), 0.5);
} 
#endif
