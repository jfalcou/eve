//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  using eve::logical;

  using l_t = logical<wide<Type, T>>;

  TTS_EQUAL(eve::is_ordered(l_t(true), l_t(false)), l_t(true));

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type,T> lhs([](auto i, auto c) { return c - i; }), rhs([](auto i, auto c) { return i%2 ? i : c-i; });
    TTS_EQUAL(eve::is_ordered(lhs, rhs), l_t(true));
  }
  else
  {
    wide<Type, T> lhs([](auto i, auto c ) { return c - i; }), rhs([](auto i, auto ) { return i/Type(i); });
    l_t           ref([](auto i, auto c) { return eve::is_ordered(Type(c - i), Type(i/Type(i))); });
    TTS_EQUAL(ref, eve::is_ordered(lhs, rhs));
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

  TTS_EQUAL(eve::is_ordered(l_t(true), Type(0)), l_t(true));
  TTS_EQUAL(eve::is_ordered(Type(1), l_t(false)), l_t(true));

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto) { return i; });
    l_t ref1([](auto i, auto) { return eve::is_ordered(Type(i), Type(2)); });
    l_t ref2([](auto i, auto) { return eve::is_ordered(Type(2), Type(i)); });
    TTS_EQUAL(ref1, eve::is_ordered(lhs, Type(2)));
    TTS_EQUAL(ref2, eve::is_ordered(Type(2), lhs));
  }
  else
  {
    wide<Type, T> lhs([](auto i, auto) { return i%2 ? i : Nan<Type>(); });
    l_t ref1([](auto i, auto) { return eve::is_ordered(i%2 ? Type(i) : Nan<Type>(), Type(2)); });
    l_t ref2([](auto i, auto) { return eve::is_ordered(Type(2), i%2 ? Type(i) : Nan<Type>()); });
    TTS_EQUAL(ref1, eve::is_ordered(lhs, Type(2)));
    TTS_EQUAL(ref2, eve::is_ordered(Type(2), lhs));
  }
}

#endif
