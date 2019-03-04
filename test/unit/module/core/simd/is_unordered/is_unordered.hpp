//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_UNORDERED_HPP
#define IS_UNORDERED_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_unordered.hpp>
#include <eve/constant/nan.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp> 

using eve::fixed;

TTS_CASE_TPL("Check is_unordered behavior on homogeneous wide",
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
      wide<Type, T> lhs([](int i, int c) { return c - i; }), rhs([](int i, int c) { return i%2 ? i : c-i; });
      wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_unordered(Type(c - i), Type(i%2 ? i : c-i)); });
      TTS_SECTION("supports eve::is_unordered") { TTS_EQUAL(ref, eve::is_unordered(lhs, rhs)); }
    }
    else
    {
      wide<Type, T> lhs([](int i, int c ) { return c - i; }), rhs([](int i, int ) { return i/Type(i); });
      wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_unordered(Type(c - i), Type(i/Type(i))); });
      TTS_SECTION("supports eve::is_unordered") { TTS_EQUAL(ref, eve::is_unordered(lhs, rhs)); }
    }
    
  }
}

TTS_CASE_TPL("Check plus behavior on wide and scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::Nan; 

  TTS_SETUP("A correctly initialized wide and a scalar")
  {
    if constexpr(std::is_integral_v<Type>)
    {                   
      wide<Type, T> lhs([](auto i, auto) { return i; });
      wide<eve::logical<Type>, T> ref1([](int i, int) { return eve::is_unordered(Type(i), Type(2)); });
      wide<eve::logical<Type>, T> ref2([](int i, int) { return eve::is_unordered(Type(2), Type(i)); });   
      TTS_SECTION("supports eve::is_unordered wide/scalar") { TTS_EQUAL(ref1, eve::is_unordered(lhs, Type(2))); }
      TTS_SECTION("supports eve::is_unordered scalar/wide") { TTS_EQUAL(ref2, eve::is_unordered(Type(2), lhs)); }
    }
    else
    {
      wide<Type, T> lhs([](auto i, auto) { return i%2 ? i : Nan<Type>(); });
      wide<eve::logical<Type>, T> ref1([](int i, int) { return eve::is_unordered(i%2 ? Type(i) : Nan<Type>(), Type(2)); });
      wide<eve::logical<Type>, T> ref2([](int i, int) { return eve::is_unordered(Type(2), i%2 ? Type(i) : Nan<Type>()); });
      TTS_SECTION("supports eve::is_unordered wide/scalar") { TTS_EQUAL(ref1, eve::is_unordered(lhs, Type(2))); }
      TTS_SECTION("supports eve::is_unordered scalar/wide") { TTS_EQUAL(ref2, eve::is_unordered(Type(2), lhs)); }
    }
  }
}
#endif
