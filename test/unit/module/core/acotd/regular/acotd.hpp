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
#include <eve/function/scalar/indeg.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>   
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check acotd return type")
{
  TTS_EXPR_IS(eve::acotd(Type(0)),  Type);
}

TTS_CASE("Check eve::acotd behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::Inf<Type>()), 0, 0);
    TTS_ULP_EQUAL(eve::acotd(eve::Minf<Type>()), 0, 0);
  }
 if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::Nan<Type>()),   eve::Nan<Type>(), 0);
  }
  TTS_ULP_EQUAL(eve::acotd(eve::Half<Type>()),   Type(63.4349488229220), 1);
  TTS_ULP_EQUAL(eve::acotd(eve::Mhalf<Type>()),  Type(-63.4349488229220), 1);
  TTS_ULP_EQUAL(eve::acotd(eve::Mone<Type>()),   Type(-45), 0.5);
  TTS_ULP_EQUAL(eve::acotd(eve::One<Type>()),    Type(45), 0.5);   
  TTS_ULP_EQUAL(eve::acotd(eve::Zero<Type>()),   Type(90), 0.5);
  TTS_ULP_EQUAL(eve::acotd(eve::Mzero<Type>()),  Type(-90), 0.5);   
  TTS_ULP_EQUAL(eve::acotd(eve::rec(eve::Smallestposval<Type>())), eve::indeg(eve::Smallestposval<Type>()), 0.5);
} 
#endif
