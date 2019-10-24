//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXP_HPP
#define EXP_HPP

#include <eve/function/exp.hpp>
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
TTS_CASE_TPL("Check exp behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t =  eve::wide<Type, T>; 
  TTS_EXPR_IS ( eve::exp(t_t(0)), t_t);
  
  TTS_ULP_EQUAL(eve::exp(t_t(1)), t_t(std::exp(Type(1))), 0.5);
  TTS_ULP_EQUAL(eve::exp(t_t(2)), t_t(std::exp(Type(2))), 0.5);
  TTS_ULP_EQUAL(eve::exp(t_t(-2)),t_t(std::exp(Type(-2))), 0.5);
  TTS_ULP_EQUAL(eve::exp(t_t(0)), t_t(Type(1)), 0.5);
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::exp(eve::Nan<t_t>()), eve::Nan<t_t>()); 
    TTS_IEEE_EQUAL(eve::exp(eve::Inf<t_t>()), eve::Inf<t_t>());
    TTS_IEEE_EQUAL(eve::exp(eve::Minf<t_t>()), eve::Zero<t_t>());
  }
  TTS_IEEE_EQUAL(eve::exp(eve::Maxlog<t_t>()), eve::Inf<t_t>());
  TTS_IEEE_EQUAL(eve::exp(eve::Minlog<t_t>()), eve::Zero<t_t>());
  
  for(int i=1; i < 70; i *= 3)
  {
    TTS_ULP_EQUAL(eve::exp(t_t(i)), t_t(std::exp(Type(i))), 0.5);
    TTS_ULP_EQUAL(eve::exp(-t_t(i)), t_t(std::exp(Type(-i))), 0.5); 
  }
}

#endif
