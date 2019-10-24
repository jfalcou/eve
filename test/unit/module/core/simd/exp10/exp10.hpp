//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXP10_HPP
#define EXP10_HPP

#include <eve/function/exp10.hpp>
#include <eve/wide.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/maxlog10.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/platform.hpp>
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
  TTS_EXPR_IS ( eve::exp10(t_t(0)), t_t);
  
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_ULP_EQUAL(eve::exp10(t_t(1)), t_t(10), 0.5);
    TTS_ULP_EQUAL(eve::exp10(t_t(2)), t_t(100), 0.5);
    TTS_ULP_EQUAL(eve::exp10(t_t(-2)),t_t(1)/100, 0.5);
    TTS_ULP_EQUAL(eve::exp10(t_t(0)), t_t(1), 0.5);
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eve::exp10(eve::Nan<t_t>()), eve::Nan<t_t>()); 
      TTS_IEEE_EQUAL(eve::exp10(eve::Inf<t_t>()), eve::Inf<t_t>());
      TTS_IEEE_EQUAL(eve::exp10(eve::Minf<t_t>()), eve::Zero<t_t>());
    }
    TTS_IEEE_EQUAL(eve::exp10(eve::Maxlog2<t_t>()), eve::Inf<t_t>());
    TTS_IEEE_EQUAL(eve::exp10(eve::Minlog2<t_t>()), eve::Zero<t_t>());
      
    for(int i=1; i < eve::Maxlog10<Type>(); i *= 3)
    {
      TTS_ULP_EQUAL(eve::exp10(t_t(i)), t_t(std::pow(10, Type(i))), 0.5);
      TTS_ULP_EQUAL(eve::exp10(-t_t(i)), t_t(std::pow(10, -Type(i))), 0.5); 
    }
  }
  else 
  {
    for(Type i=0; i < eve::Maxlog10<Type>(); ++i)
    {
      TTS_ULP_EQUAL(eve::exp10(t_t(i)), t_t(std::pow(10, Type(i))), 0.5);
    }
  }
}

#endif
 
