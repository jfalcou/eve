//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ASECD_HPP
#define ASECD_HPP

#include <eve/function/scalar/asecd.hpp>
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

TTS_CASE("Check asecd return type")
{
  TTS_EXPR_IS(eve::asecd(Type(0)),  Type);
}

TTS_CASE("Check eve::asecd behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::asecd(eve::Inf<Type>()), 90, 0.5);
  TTS_ULP_EQUAL(eve::asecd(eve::Minf<Type>()), 90, 0.5);
  TTS_IEEE_EQUAL(eve::asecd(eve::Nan<Type>()), eve::Nan<Type>());
  TTS_IEEE_EQUAL(eve::asecd(eve::Zero<Type>()), eve::Nan<Type>());
#endif

  TTS_ULP_EQUAL(eve::asecd(Type(-2)), Type(120), 0.5);
  TTS_ULP_EQUAL(eve::asecd(eve::Mone<Type>()), Type(180), 0.5);
  TTS_ULP_EQUAL(eve::asecd(eve::One<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asecd(Type(2)), Type(60), 0.5);
} 
#endif
