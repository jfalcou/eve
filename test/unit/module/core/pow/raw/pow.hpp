//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::raw_(eve::pow) return type")
{
  TTS_EXPR_IS(eve::raw_(eve::pow)(Type(0), Type(0)), (Type));
}

// TTS_CASE("Check eve::raw_(eve::pow) behavior")
// {
//  // specific values tests
//   #ifndef BOOST_SIMD_NO_INVALIDS
//   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<Type>(),3), eve::Inf<Type>(), 0);
//   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<Type>(),3), eve::Minf<Type>(), 0);
//   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Nan<Type>(),3), eve::Nan<Type>(), 0);
//   #endif

//   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Two<Type>(),-3), (eve::Ratio<Type, 1, 8>()),  0);
//  }


TTS_CASE("pow conformity")
{

  // std::pow conform
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(0), Type(-1)), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(0), Type(-2)), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(0), Type(-2)), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(0),  eve::Minf<Type>()),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(0),  eve::Minf<Type>()),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(0.5), eve::Inf<Type>()),  eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(2), eve::Inf<Type>()),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(0.5), eve::Minf<Type>()),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(2), eve::Minf<Type>()),  eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<Type>(), Type(4) ),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<Type>(), Type(-4) ),  eve::Zero<Type>(), 0);
  // std::pow non conform
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(0), Type(-1)), eve::Inf<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(1),  eve::Minf<Type>()),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(1),  eve::Inf <Type>()),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(Type(1), eve::Nan<Type>()) ,  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Nan<Type>(), Type(0)) ,  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Nan<Type>(), -Type(0)) ,  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(0.5), eve::Inf<Type>()),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(2), eve::Inf<Type>()),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(0.5), eve::Minf<Type>()),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(-Type(2), eve::Minf<Type>()),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<Type>(), Type(-3) ),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<Type>(), Type(-4) ),  eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<Type>(),  Type(-4)), eve::Nan<Type>(), 0);
   TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<Type>(), Type(-4)) , eve::Nan<Type>(), 0);  
}
