//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CSCH_HPP
#define CSCH_HPP

#include <eve/function/csch.hpp>
#include <eve/wide.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/rec.hpp>
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
TTS_CASE_TPL("Check csch behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>)
{
  using t_t =  eve::wide<Type, T>; 
  TTS_EXPR_IS ( eve::csch(t_t(0)), t_t);
  
  TTS_ULP_EQUAL(eve::csch(t_t(1)), t_t(eve::rec(std::sinh(Type(1)))), 0.5);
  TTS_ULP_EQUAL(eve::csch(t_t(2)), t_t(eve::rec(std::sinh(Type(2)))), 0.5);
  TTS_ULP_EQUAL(eve::csch(t_t(-2)),t_t(eve::rec(std::sinh(Type(-2)))), 0.5);
  TTS_ULP_EQUAL(eve::csch(t_t(-1)),t_t(eve::rec(std::sinh(Type(-1)))), 0.5);
  TTS_IEEE_EQUAL(eve::csch(t_t(0)), t_t(eve::Inf<Type>()));
  TTS_IEEE_EQUAL(eve::csch(t_t(-0.0)), t_t(eve::Minf<Type>()));
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::csch(eve::Nan<t_t>()), eve::Nan<t_t>()); 
    TTS_IEEE_EQUAL(eve::csch(eve::Inf<t_t>()), eve::Zero<t_t>());
    TTS_IEEE_EQUAL(eve::csch(eve::Minf<t_t>()), eve::Zero<t_t>());
    TTS_EXPECT(eve::all(eve::is_positive(eve::csch(eve::Inf<t_t>()))));
    TTS_EXPECT(eve::all(eve::is_negative(eve::csch(eve::Minf<t_t>()))));
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 2)
  {
    TTS_ULP_EQUAL(eve::csch(t_t(i)), t_t(eve::rec(std::sinh(Type(i)))), 0.5);
    TTS_ULP_EQUAL(eve::csch(-t_t(i)), t_t(eve::rec(std::sinh(Type(-i)))), 0.5); 
    TTS_ULP_EQUAL(eve::csch(1/t_t(i)), t_t(eve::rec(std::sinh(1/Type(i)))), 0.5);
    TTS_ULP_EQUAL(eve::csch(-1/t_t(i)), t_t(eve::rec(std::sinh(1/Type(-i)))), 0.5); 
  }
}

#endif
