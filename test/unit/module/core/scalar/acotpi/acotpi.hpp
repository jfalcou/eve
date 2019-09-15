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
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check eve::acotpi return type")
{
  TTS_EXPR_IS(eve::acotpi(Type(0)),  Type);
}

TTS_CASE("Check eve::acotpi behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::acotpi(eve::Inf<Type>()), 0, 0);
  TTS_ULP_EQUAL(eve::acotpi(eve::Minf<Type>()), 0, 0);
  TTS_ULP_EQUAL(eve::acotpi(eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::acotpi(-eve::Zero<Type>()), Type(-0.5), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::Mone<Type>()), Type(-0.25), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::One<Type>()), Type(0.25), 0.5);
  TTS_ULP_EQUAL(eve::acotpi(eve::Zero<Type>()), Type(0.5), 0.5);

}


#endif
