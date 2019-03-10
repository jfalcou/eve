//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_INF_HPP
#define IS_INF_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_inf.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check is_inf behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  TTS_SETUP("A correctly initialized wide")
  {
    if constexpr(std::is_integral_v<Type>)
    {
      wide<Type, T> lhs([](int i, int) { return i%2; }); 
      wide<eve::logical<Type>, T> ref([](int i, int) { return eve::is_inf(Type(i%2)); });
      
      TTS_SECTION("supports eve::is_inf") { TTS_EQUAL(ref, eve::is_inf(lhs)); }
    }
    else
    {
      wide<Type, T> lhs([](int i, int) { return i%3/Type(i%2); }); 
      wide<eve::logical<Type>, T> ref([](int i, int) { return eve::is_inf(Type(i%3/Type(i%2))); });
      
      TTS_SECTION("supports eve::is_inf") { TTS_EQUAL(ref, eve::is_inf(lhs)); }
    }
  }
}

#endif
