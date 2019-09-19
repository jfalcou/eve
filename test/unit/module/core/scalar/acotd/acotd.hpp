//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOTD_HPP
#define ACOTD_HPP

#include <eve/function/scalar/acotd.hpp>
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

TTS_CASE("Check eve::acotd return type")
{
  TTS_EXPR_IS(eve::acotd(Type(0)),  Type);
}

TTS_CASE("Check eve::acotd behavior")
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::acotd(eve::Inf<Type>()), 0, 0);
  TTS_ULP_EQUAL(eve::acotd(eve::Minf<Type>()), 0, 0);
  TTS_ULP_EQUAL(eve::acotd(eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::acotd(-eve::Zero<Type>()), Type(-90), 0.5);
  TTS_ULP_EQUAL(eve::acotd(eve::Mone<Type>()), Type(-45), 0.5);
  TTS_ULP_EQUAL(eve::acotd(eve::One<Type>()), Type(45), 0.5);
  TTS_ULP_EQUAL(eve::acotd(eve::Zero<Type>()), Type(90), 0.5);

}


#endif
