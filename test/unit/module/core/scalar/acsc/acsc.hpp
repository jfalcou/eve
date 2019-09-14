//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACSC_HPP
#define ACSC_HPP

#include <eve/function/scalar/acsc.hpp>
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
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check acsc return type")
{
  TTS_EXPR_IS(eve::acsc(Type(0)),  Type);
}

TTS_CASE("Check eve::acsc behavior")
{

#ifndef BOOST_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::acsc(eve::Inf<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::acsc(eve::Minf<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::acsc(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::acsc(eve::Zero<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::acsc(Type(-2)), -eve::Pi<Type>()/6, 0.5);
  TTS_ULP_EQUAL(eve::acsc(eve::Mone<Type>()), -eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::acsc(eve::One<Type>()), eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::acsc(Type(2)), eve::Pi<Type>()/6, 0.5);
} 
#endif
