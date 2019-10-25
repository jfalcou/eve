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


#include <eve/function/hypot.hpp>
#include "test.hpp"
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
#include <eve/wide.hpp>
#include <type_traits>
#include <iomanip>

using eve::fixed;
using eve::wide; 
TTS_CASE_TPL("Check hypot behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)  // specific values tests
{
  using t_t = wide<Type, T>; 
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Inf<t_t>(), eve::Inf<t_t>()), eve::Inf<t_t>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Minf<t_t>(), eve::Minf<t_t>()), eve::Inf<t_t>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Nan<t_t>(), eve::Nan<t_t>()), eve::Nan<t_t>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Nan<t_t>(), eve::Inf<t_t>()), eve::Nan<t_t>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Inf<t_t>(), eve::Nan<t_t>()), eve::Nan<t_t>(), 0);
  }
  
  TTS_ULP_EQUAL(eve::hypot(eve::Mone<t_t>(), eve::Mone<t_t>()), eve::Sqrt_2<t_t>(), 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::One<t_t>(), eve::One<t_t>()), eve::Sqrt_2<t_t>(), 0.5);
  TTS_ULP_EQUAL(eve::hypot(eve::Zero<t_t>(), eve::Zero<t_t>()), eve::Zero<t_t>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Valmax<t_t>(), eve::Zero<t_t>()), eve::Inf<t_t>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Zero<t_t>(), eve::Valmax<t_t>()), eve::Inf<t_t>(), 0);
  TTS_ULP_EQUAL(eve::hypot(eve::Sqrt_2<t_t>(), eve::Sqrt_2<t_t>()), t_t(2), 0.5);
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Mindenormal<t_t>(),eve::Mindenormal<t_t>()), eve::Sqrt_2<t_t>()*eve::Mindenormal<t_t>(), 0.5); 
    TTS_ULP_EQUAL(eve::hypot(eve::Smallestposval<t_t>(),eve::Smallestposval<t_t>()), eve::Sqrt_2<t_t>()*eve::Smallestposval<t_t>(), 0.5); 
  }
  
  
  for(int i=0; i < eve::Maxlog<Type>() ;  i+= 2*sizeof(t_t))
  {
    Type sz = eve::exp(Type(i)/2); //no overflow
    t_t z = t_t(sz); 
    TTS_ULP_EQUAL(eve::hypot(z, eve::Sqrt_2<t_t>()), t_t(std::hypot(sz, eve::Sqrt_2<Type>())), 0.5);
    TTS_ULP_EQUAL(eve::hypot(z, z), t_t(std::hypot(sz, sz)), 0.5);
  }
} 

TTS_CASE_TPL("Check pedantic hypot behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)  // specific values tests
{
  using t_t = wide<Type, T>; 
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<t_t>(), eve::Inf<t_t>()), eve::Inf<t_t>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Minf<t_t>(), eve::Minf<t_t>()), eve::Inf<t_t>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<t_t>(), eve::Nan<t_t>()), eve::Nan<t_t>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<t_t>(), eve::Inf<t_t>()), eve::Inf<t_t>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<t_t>(), eve::Nan<t_t>()), eve::Inf<t_t>(), 0);
  }
  
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Mone<t_t>(), eve::Mone<t_t>()), eve::Sqrt_2<t_t>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::One<t_t>(), eve::One<t_t>()), eve::Sqrt_2<t_t>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Zero<t_t>(), eve::Zero<t_t>()), eve::Zero<t_t>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<t_t>(), eve::Zero<t_t>()), eve::Valmax<t_t>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Zero<t_t>(), eve::Valmax<t_t>()), eve::Valmax<t_t>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<t_t>(), eve::Sqrt_2<t_t>()), t_t(2), 0.5);
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Mindenormal<t_t>(),eve::Mindenormal<t_t>()), eve::Sqrt_2<t_t>()*eve::Mindenormal<t_t>(), 0.5); 
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Smallestposval<t_t>(),eve::Smallestposval<t_t>()), eve::Sqrt_2<t_t>()*eve::Smallestposval<t_t>(), 0.5); 
  }
  
  for(int i=0; i < eve::Maxlog<Type>() ; i+= 2*sizeof(t_t))
  {
    Type sz = eve::exp(Type(i));
    t_t z =t_t(sz); 
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(z, eve::Sqrt_2<t_t>()), t_t(std::hypot(sz, eve::Sqrt_2<Type>())), 0.5);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(z, z), t_t(std::hypot(sz, sz)), 0.5);
  }
} 
#endif
