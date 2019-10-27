//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SINH_HPP
#define SINH_HPP

#include <eve/function/sinh.hpp>
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
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/all.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <iomanip>

using eve::fixed;
TTS_CASE_TPL("Check sinh behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>)
{
  using t_t =  eve::wide<Type, T>; 
  TTS_EXPR_IS ( eve::sinh(t_t(0)), t_t);
  
  TTS_ULP_EQUAL(eve::sinh(t_t(1)), t_t(std::sinh(Type(1))), 0.5);
  TTS_ULP_EQUAL(eve::sinh(t_t(2)), t_t(std::sinh(Type(2))), 0.5);
  TTS_ULP_EQUAL(eve::sinh(t_t(-2)),t_t(std::sinh(Type(-2))), 0.5);
  TTS_ULP_EQUAL(eve::sinh(t_t(-1)),t_t(std::sinh(Type(-1))), 0.5);
  TTS_IEEE_EQUAL(eve::sinh(t_t(0)), t_t(Type(0)));
  TTS_IEEE_EQUAL(eve::sinh(-t_t(0)), t_t(Type(0)));
  TTS_EXPECT(eve::all(eve::is_positive(eve::sinh(t_t(0.0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::sinh(t_t(-0.0)))));
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::Nan<t_t>()), eve::Nan<t_t>()); 
    TTS_IEEE_EQUAL(eve::sinh(eve::Inf<t_t>()), eve::Inf<t_t>());
    TTS_IEEE_EQUAL(eve::sinh(eve::Minf<t_t>()), eve::Minf<t_t>());
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 2)
  {
    TTS_ULP_EQUAL(eve::sinh(t_t(i)), t_t(std::sinh(Type(i))), 0.5);
    TTS_ULP_EQUAL(eve::sinh(-t_t(i)), t_t(std::sinh(Type(-i))), 0.5); 
    TTS_ULP_EQUAL(eve::sinh(1/t_t(i)), t_t(std::sinh(1/Type(i))), 0.5);
    TTS_ULP_EQUAL(eve::sinh(-1/t_t(i)), t_t(std::sinh(1/Type(-i))), 0.5); 
  }
}

#endif
