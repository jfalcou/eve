//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIV_HPP
#define DIV_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/div.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

using eve::fixed; 

TTS_CASE_TPL("Check eve::div toward_zero behavior",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide; 
  using t_t = wide<Type, T>; 
  TTS_EXPR_IS(eve::div(t_t(1), t_t(1), eve::toward_zero_) , t_t);

  if constexpr(std::is_integral_v<Type>)
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::div(eve::Mone<t_t>(),   eve::Mone<t_t>(), eve::toward_zero_), eve::One<t_t>());
      TTS_EQUAL(eve::div(eve::One<t_t>(),    eve::One<t_t>() , eve::toward_zero_), eve::One<t_t>());
      TTS_EQUAL(eve::div(eve::Valmax<t_t>(), eve::Mone<t_t>(), eve::toward_zero_), eve::Valmin<t_t>()+eve::One<t_t>());
      TTS_EQUAL(eve::div(eve::Valmax<t_t>(), eve::One<t_t>() , eve::toward_zero_), eve::Valmax<t_t>());
      TTS_EQUAL(eve::div(eve::Valmin<t_t>(), eve::Mone<t_t>(), eve::toward_zero_), eve::Valmax<t_t>());
      TTS_EQUAL(eve::div(eve::Zero<t_t>(),   eve::Zero<t_t>(), eve::toward_zero_), eve::Zero<t_t>());
      TTS_EQUAL(eve::div(eve::Mone<t_t>(),   eve::Zero<t_t>(), eve::toward_zero_), eve::Valmin<t_t>());
      TTS_EQUAL(eve::div(eve::Valmin<t_t>(), eve::Zero<t_t>(), eve::toward_zero_), eve::Valmin<t_t>());
      TTS_EQUAL(eve::div(eve::One<t_t>(),    eve::Zero<t_t>(), eve::toward_zero_), eve::Valmax<t_t>());
      TTS_EQUAL(eve::div(eve::Valmax<t_t>(), eve::Zero<t_t>(), eve::toward_zero_), eve::Valmax<t_t>());
  TTS_EQUAL(eve::div(t_t{-1} , t_t{2}, eve::toward_zero_), t_t(0));
  TTS_EQUAL(eve::div(t_t{-4} , t_t{3}, eve::toward_zero_), t_t(-1));
    }
    else
    {
      TTS_EQUAL(eve::div(eve::One<t_t>()   , eve::One<t_t>() , eve::toward_zero_) , eve::One<t_t>());
      TTS_EQUAL(eve::div(eve::Valmax<t_t>(),eve::One<t_t>()  , eve::toward_zero_) , eve::Valmax<t_t>());
      TTS_EQUAL(eve::div(eve::Zero<t_t>()  , eve::Zero<t_t>(), eve::toward_zero_) , eve::Zero<t_t>());
      TTS_EQUAL(eve::div(eve::One<t_t>()   , eve::Zero<t_t>(), eve::toward_zero_) , eve::Valmax<t_t>());
      TTS_EQUAL(eve::div(eve::Valmax<t_t>(), eve::Zero<t_t>(), eve::toward_zero_) , eve::Valmax<t_t>());
    }
  }
  else
  {
    TTS_EQUAL(eve::div(t_t(-1) , t_t{2}, eve::toward_zero_), t_t(0));
    TTS_EQUAL(eve::div(t_t(-4) , t_t{3}, eve::toward_zero_), t_t(-1));
  }
  TTS_EQUAL(eve::div(t_t{0} , t_t{1}, eve::toward_zero_), t_t{0});
  TTS_EQUAL(eve::div(t_t{1} , t_t{1}, eve::toward_zero_), t_t{1});
  TTS_EQUAL(eve::div(t_t{12}, t_t{4}, eve::toward_zero_), t_t{3});
  TTS_EQUAL(eve::div(t_t{1} , t_t{2}, eve::toward_zero_), t_t(0));
  TTS_EQUAL(eve::div(t_t{4} , t_t{3}, eve::toward_zero_), t_t(1));
}

#endif
