//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_NAN_HPP
#define IS_NOT_NAN_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_nan.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp> 

using eve::fixed;

TTS_CASE_TPL("Check is_not_nan behavior on homogeneous wide",
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

  TTS_SETUP("A correctly initialized wide")
  {
    if constexpr(std::is_integral_v<Type>)
    {                   
      wide<Type, T> lhs([](int i, int c) { return c - i; });
      wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_not_nan(Type(c - i)); });
      TTS_SECTION("supports eve::is_not_nan") { TTS_EQUAL(ref, eve::is_not_nan(lhs)); }
    }
    else
    {
      wide<Type, T> lhs([](int i, int ) { return i/Type(i); });
      wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_not_nan(Type(i/Type(i))); });
      TTS_SECTION("supports eve::is_not_nan") { TTS_EQUAL(ref, eve::is_not_nan(lhs)); }
    }
    
  }
}

#endif
