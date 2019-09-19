//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ASEC_HPP
#define ASEC_HPP

#include <eve/function/scalar/asec.hpp>
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
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check asec return type")
{
  TTS_EXPR_IS(eve::asec(Type(0)),  Type);
}

TTS_CASE("Check eve::asec behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::asec(eve::Inf<Type>()), eve::Pio_2<Type>(), 0);
  TTS_ULP_EQUAL(eve::asec(eve::Minf<Type>()), eve::Pio_2<Type>(), 0);
  TTS_ULP_EQUAL(eve::asec(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::asec(eve::Zero<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::asec(Type(-2)), 2*eve::Pi<Type>()/3, 0.5);
  TTS_ULP_EQUAL(eve::asec(eve::Mone<Type>()), eve::Pi<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asec(eve::One<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asec(Type(2)), eve::Pi<Type>()/3, 0.5);
//   TTS_ULP_EQUAL(eve::asec(Type(1.0001)), Type(0.014141546406083379035490219782316842988512297143463), 0.5);
//   TTS_ULP_EQUAL(eve::asec(Type(1.00001)), Type(0.0044721173212346034193436538350258335056634438959045), 0.5);
}

#endif

