//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_DENORMAL_HPP 
#define IS_DENORMAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_denormal.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_denormal behavior on wide",
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
      wide<Type, T> lhs([](int i, int) { return i/2; }); 
      wide<eve::logical<Type>, T> ref([](int i, int) { return eve::is_denormal(Type(i/2)); });
      TTS_SECTION("supports eve::is_denormal") { TTS_EQUAL(ref, eve::is_denormal(lhs)); }
    }
    else
    {
      Type s = Smallestposval<Type>(); 
      wide<Type, T> lhs([](int i, int) { return i%2 ? s*i : s/i; }); 
      wide<eve::logical<Type>, T> ref([](int i, int) { return eve::is_denormal( return i%2 ? s*i : s/i;); });
      TTS_SECTION("supports eve::is_denormal") { TTS_EQUAL(ref, eve::is_denormal(lhs)); }
    }


  }
}

#endif
