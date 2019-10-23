//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXP2_HPP
#define EXP2_HPP

#include <eve/function/exp2.hpp>
#include <eve/wide.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/maxlog2.hpp>
#include <cmath>
#include <iomanip>

using eve::fixed;
TTS_CASE_TPL("Check abs behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t =  eve::wide<Type, T>; 
  TTS_EXPR_IS ( eve::exp2(t_t(0)), t_t);
  
  TTS_ULP_EQUAL(eve::exp2(t_t(1)), t_t(std::exp2(Type(1))), 0.5);
  TTS_ULP_EQUAL(eve::exp2(t_t(2)), t_t(std::exp2(Type(2))), 0.5);
  TTS_ULP_EQUAL(eve::exp2(t_t(-2)),t_t(std::exp2(Type(-2))), 0.5);
  TTS_ULP_EQUAL(eve::exp2(t_t(0)), t_t(Type(1)), 0.5);
  
  for(int i=1; i < eve::Maxlog2<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::exp2(t_t(i)), t_t(std::exp2(Type(i))), 0.5);
    TTS_ULP_EQUAL(eve::exp2(-t_t(i)), t_t(std::exp2(Type(-i))), 0.5); 
  }
}

#endif
