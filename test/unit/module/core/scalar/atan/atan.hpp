//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATAN_HPP
#define ATAN_HPP

#include <eve/function/scalar/atan.hpp>
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
#include <eve/constant/pio_4.hpp>   
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check atan return type")
{
  TTS_EXPR_IS(eve::atan(Type(0)),  Type);
}

TTS_CASE("Check eve::atan behavior")
{
#ifndef BOOST_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::atan(eve::Inf<Type>()), eve::Pio_2<Type>(), 0);
  TTS_ULP_EQUAL(eve::atan(eve::Minf<Type>()), -eve::Pio_2<Type>(), 0);
  TTS_ULP_EQUAL(eve::atan(eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::atan(eve::Half<Type>()), Type(4.636476090008061e-01), 0.5);
  TTS_ULP_EQUAL(eve::atan(eve::Mhalf<Type>()), Type(-4.636476090008061e-01), 0.5);
  TTS_ULP_EQUAL(eve::atan(eve::Mone<Type>()), -eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan(eve::One<Type>()), eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan(eve::Zero<Type>()), eve::Zero<Type>(), 0.5);
  TTS_EQUAL(eve::is_negative(eve::atan(eve::Mzero<Type>())), eve::True<Type>());
  TTS_EQUAL(eve::is_positive(eve::atan(eve::Zero<Type>())), eve::True<Type>());

}
  
#endif
