//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  using eve::logical;

  using l_t = logical<wide<Type, T>>;

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type,T> lhs([](auto i, auto c) { return c - i; }), rhs([](auto i, auto c) { return i%2 ? i : c-i; });
    TTS_EQUAL(eve::is_unordered(lhs, rhs), l_t(false));
  }
  else
  {
    wide<Type, T> lhs([](auto i, auto c ) { return c - i; }), rhs([](auto i, auto ) { return i/Type(i); });
    l_t           ref([](auto i, auto c) { return eve::is_unordered(Type(c - i), Type(i/Type(i))); });
    TTS_EQUAL(ref, eve::is_unordered(lhs, rhs));
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
  using eve::logical;

  using l_t = logical<wide<Type, T>>;

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto) { return i; });
    l_t ref1([](auto i, auto) { return eve::is_unordered(Type(i), Type(2)); });
    l_t ref2([](auto i, auto) { return eve::is_unordered(Type(2), Type(i)); });
    TTS_EQUAL(ref1, eve::is_unordered(lhs, Type(2)));
    TTS_EQUAL(ref2, eve::is_unordered(Type(2), lhs));
  }
  else
  {
    wide<Type, T> lhs([](auto i, auto) { return i%2 ? i : Nan<Type>(); });
    l_t ref1([](auto i, auto) { return eve::is_unordered(i%2 ? Type(i) : Nan<Type>(), Type(2)); });
    l_t ref2([](auto i, auto) { return eve::is_unordered(Type(2), i%2 ? Type(i) : Nan<Type>()); });
    TTS_EQUAL(ref1, eve::is_unordered(lhs, Type(2)));
    TTS_EQUAL(ref2, eve::is_unordered(Type(2), lhs));
  }
}

#endif
