//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COSD_HPP
#define COSD_HPP

#include <eve/function/scalar/cosd.hpp>
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

TTS_CASE("Check cosd return type")
{
  TTS_EXPR_IS(eve::cosd(Type(0)),  Type);
}

TTS_CASE("Check eve::cosd behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::cosd(eve::Inf<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::cosd(eve::Minf<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::cosd(eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::cosd(eve::Half<Type>()), eve::Pi<Type>()/3, 0.5);
  TTS_ULP_EQUAL(eve::cosd(eve::Mhalf<Type>()), 2*eve::Pi<Type>()/3, 0.5);
  TTS_ULP_EQUAL(eve::cosd(eve::Mone<Type>()), eve::Pi<Type>(), 0);
  TTS_ULP_EQUAL(eve::cosd(eve::One<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::cosd(eve::Zero<Type>()), eve::Pio_2<Type>(), 0); 
} 
#endif
