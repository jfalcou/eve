//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COTH_HPP
#define COTH_HPP

#include <eve/function/coth.hpp>
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
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <iomanip>

using eve::fixed;
TTS_CASE_TPL("Check coth behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>)
{
  using t_t =  eve::wide<Type, T>; 
  TTS_EXPR_IS ( eve::coth(t_t(0)), t_t);
  
  TTS_ULP_EQUAL(eve::coth(t_t(1)), t_t(eve::rec(std::tanh(Type(1)))), 0.5);
  TTS_ULP_EQUAL(eve::coth(t_t(2)), t_t(eve::rec(std::tanh(Type(2)))), 0.5);
  TTS_ULP_EQUAL(eve::coth(t_t(-2)),t_t(eve::rec(std::tanh(Type(-2)))), 0.5);
  TTS_ULP_EQUAL(eve::coth(t_t(-1)),t_t(eve::rec(std::tanh(Type(-1)))), 0.5);
  TTS_IEEE_EQUAL(eve::coth(t_t(0.0)), eve::Inf<t_t>());
  TTS_IEEE_EQUAL(eve::coth(t_t(-0.0)),eve::Minf<t_t>() );
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::coth(eve::Nan<t_t>()), eve::Nan<t_t>()); 
    TTS_IEEE_EQUAL(eve::coth(eve::Inf<t_t>()), t_t(1));
    TTS_IEEE_EQUAL(eve::coth(eve::Minf<t_t>()), t_t(-1));
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::coth(t_t(i)), t_t(eve::rec(std::tanh(Type(i)))), 0.5);
    TTS_ULP_EQUAL(eve::coth(-t_t(i)), t_t(eve::rec(std::tanh(Type(-i)))), 0.5); 
    TTS_ULP_EQUAL(eve::coth(1/t_t(i)), t_t(eve::rec(std::tanh(1/Type(i)))), 0.5);
    TTS_ULP_EQUAL(eve::coth(-1/t_t(i)), t_t(eve::rec(std::tanh(1/Type(-i)))), 0.5); 
  }
}

#endif
