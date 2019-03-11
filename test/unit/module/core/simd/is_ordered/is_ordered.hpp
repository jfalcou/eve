//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_ORDERED_HPP
#define IS_ORDERED_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_ordered.hpp>
#include <eve/constant/nan.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp> 

using eve::fixed;

TTS_CASE_TPL("Check is_ordered behavior on homogeneous wide",
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
      wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_ordered(Type(c - i), Type(i%2 ? i : c-i)); });
      TTS_SECTION("supports eve::is_ordered") { TTS_EQUAL(ref, eve::is_ordered(lhs, rhs)); }
    }
    else
    {
      wide<Type, T> lhs([](int i, int c ) { return c - i; }), rhs([](int i, int ) { return i/Type(i); });
      wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_ordered(Type(c - i), Type(i/Type(i))); });
      TTS_SECTION("supports eve::is_ordered") { TTS_EQUAL(ref, eve::is_ordered(lhs, rhs)); }
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
      wide<eve::logical<Type>, T> ref1([](int i, int) { return eve::is_ordered(Type(i), Type(2)); });
      wide<eve::logical<Type>, T> ref2([](int i, int) { return eve::is_ordered(Type(2), Type(i)); });   
      TTS_SECTION("supports eve::is_ordered wide/scalar") { TTS_EQUAL(ref1, eve::is_ordered(lhs, Type(2))); }
      TTS_SECTION("supports eve::is_ordered scalar/wide") { TTS_EQUAL(ref2, eve::is_ordered(Type(2), lhs)); }
    }
    else
    {
      wide<Type, T> lhs([](auto i, auto) { return i%2 ? i : Nan<Type>(); });
      wide<eve::logical<Type>, T> ref1([](int i, int) { return eve::is_ordered(i%2 ? Type(i) : Nan<Type>(), Type(2)); });
      wide<eve::logical<Type>, T> ref2([](int i, int) { return eve::is_ordered(Type(2), i%2 ? Type(i) : Nan<Type>()); });
      TTS_SECTION("supports eve::is_ordered wide/scalar") { TTS_EQUAL(ref1, eve::is_ordered(lhs, Type(2))); }
      TTS_SECTION("supports eve::is_ordered scalar/wide") { TTS_EQUAL(ref2, eve::is_ordered(Type(2), lhs)); }
    }
  }
}
#endif
