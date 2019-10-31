//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TANH_HPP
#define TANH_HPP

#include <eve/function/tanh.hpp>
#include <eve/wide.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp> 
#include <cmath>
#include <iomanip>

using eve::fixed;
TTS_CASE_TPL("Check tanh behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>)
{
  using t_t =  eve::wide<Type, T>; 
  TTS_EXPR_IS ( eve::tanh(t_t(0)), t_t);
  
  TTS_ULP_EQUAL(eve::tanh(t_t(1)), t_t(std::tanh(Type(1))), 0.5);
  TTS_ULP_EQUAL(eve::tanh(t_t(2)), t_t(std::tanh(Type(2))), 0.5);
  TTS_ULP_EQUAL(eve::tanh(t_t(-2)),t_t(std::tanh(Type(-2))), 0.5);
  TTS_ULP_EQUAL(eve::tanh(t_t(-1)),t_t(std::tanh(Type(-1))), 0.5);
  TTS_IEEE_EQUAL(eve::tanh(t_t(0.0)), t_t(Type(0)));
  TTS_IEEE_EQUAL(eve::tanh(t_t(-0.0)), t_t(Type(0)));
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::tanh(eve::Nan<t_t>()), eve::Nan<t_t>()); 
    TTS_IEEE_EQUAL(eve::tanh(eve::Inf<t_t>()), t_t(1));
    TTS_IEEE_EQUAL(eve::tanh(eve::Minf<t_t>()), t_t(-1));
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::tanh(t_t(i)), t_t(std::tanh(Type(i))), 1);
    TTS_ULP_EQUAL(eve::tanh(-t_t(i)), t_t(std::tanh(Type(-i))), 1); 
    TTS_ULP_EQUAL(eve::tanh(1/t_t(i)), t_t(std::tanh(1/Type(i))), 1);
    TTS_ULP_EQUAL(eve::tanh(-1/t_t(i)), t_t(std::tanh(1/Type(-i))), 1); 
  }
}

#endif
