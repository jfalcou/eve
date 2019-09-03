//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_EQUAL_HPP
#define IS_NOT_EQUAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_equal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_equal behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  using t_t = wide<Type, T>;
  using l_t = eve::as_logical_t<t_t>;
  t_t lhs([](auto i, auto c) { return c - i; }),
      rhs([](auto i, auto c) { return i % 2 ? i : c - i; });
  l_t ref([](auto i, auto c) { return eve::is_not_equal(Type(c - i), Type(i % 2 ? i : c - i)); });

  TTS_EQUAL(ref, eve::is_not_equal(lhs, rhs));
  TTS_EQUAL(ref, (lhs != rhs));
}

TTS_CASE_TPL("Check is_not_equal behavior on wide and scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  using t_t = wide<Type, T>;
  using l_t = eve::as_logical_t<t_t>;
  t_t lhs([](auto i, auto) { return i; });
  l_t ref([](auto i, auto c) { return eve::is_not_equal(Type(i), Type(2)); });

  TTS_EQUAL(ref, eve::is_not_equal(lhs, Type(2)));
  TTS_EQUAL(ref, eve::is_not_equal(Type(2), lhs));

  TTS_EQUAL(ref, lhs != 2);
  TTS_EQUAL(ref, 2 != lhs);
}

#endif
