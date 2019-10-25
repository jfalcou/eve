//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef HYPOT_HPP
#define HYPOT_HPP

#include <eve/function/scalar/hypot.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/function/exp.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <type_traits>
#include <iomanip>
TTS_CASE("Check eve::hypot behavior")
{
  // specific values tests
#ifndef EVE_NO_INVALIDS
  TTS_ULP_EQUAL(eve::hypot(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Minf<Type>(), eve::Minf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Inf<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::hypot(eve::Mone<Type>(), eve::Mone<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::One<Type>(), eve::One<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Valmax<Type>(), eve::Zero<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Zero<Type>(), eve::Valmax<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2), 0.5);
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Mindenormal<Type>(),eve::Mindenormal<Type>()), eve::Sqrt_2<Type>()*eve::Mindenormal<Type>(), 0.5); 
    TTS_ULP_EQUAL(eve::hypot(eve::Smallestposval<Type>(),eve::Smallestposval<Type>()), eve::Sqrt_2<Type>()*eve::Smallestposval<Type>(), 0.5); 
  }
  
  
  for(int i=0; i < eve::Maxlog<Type>() ;  i+= 2*sizeof(Type))
  {
    Type z = exp(Type(i)/2); //no overflow
    TTS_ULP_EQUAL(eve::hypot(z, eve::Sqrt_2<Type>()), std::hypot(z, eve::Sqrt_2<Type>()), 0.5);
    TTS_ULP_EQUAL(eve::hypot(z, z), std::hypot(z, z), 0.5);
  }
} 

TTS_CASE("Check pedantic_(eve::hypot) behavior")
{

  // specific values tests
#ifndef EVE_NO_INVALIDS
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Minf<Type>(), eve::Minf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Nan<Type>()), eve::Inf<Type>(), 0);
#endif
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Mone<Type>(), eve::Mone<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::One<Type>(), eve::One<Type>()), eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Type>(), eve::Zero<Type>()), eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Zero<Type>(), eve::Valmax<Type>()), eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2), 0.5);
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Mindenormal<Type>(),eve::Mindenormal<Type>()), eve::Sqrt_2<Type>()*eve::Mindenormal<Type>(), 0.5); 
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Smallestposval<Type>(),eve::Smallestposval<Type>()), eve::Sqrt_2<Type>()*eve::Smallestposval<Type>(), 0.5); 
  }
  
  for(int i=0; i < eve::Maxlog<Type>() ; i+= 2*sizeof(Type))
 {
   Type z = eve::exp(Type(i));
   TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(z, eve::Sqrt_2<Type>()), std::hypot(z, eve::Sqrt_2<Type>()), 0.5);
   TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(z, z), std::hypot(z, z), 0.5);
 }
} 
#endif 
