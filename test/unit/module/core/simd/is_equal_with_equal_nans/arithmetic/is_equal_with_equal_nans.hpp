//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQUAL_WITH_EQUAL_NANS_HPP
#define IS_EQUAL_WITH_EQUAL_NANS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_equal_with_equal_nans.hpp>
#include <eve/constant/nan.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_equal_with_equal_nans behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto c) { return c - i; }),
      rhs([](auto i, auto c) { return i % 2 ? i : c - i; });

  logical<wide<Type, T>> ref([](auto i, auto c) {
    return eve::is_equal_with_equal_nans(Type(c - i), Type(i % 2 ? i : c - i));
  });

  if constexpr(std::is_integral_v<Type>)
  { TTS_EQUAL(ref, eve::is_equal_with_equal_nans(lhs, rhs)); }
  else
  {
    lhs[ lhs.size() / 2 ] = rhs[ rhs.size() / 2 ] = eve::Nan<Type>();
    logical<wide<Type, T>> nref(
        [&](auto i, auto) { return eve::is_equal_with_equal_nans(lhs[ i ], rhs[ i ]); });

    TTS_EQUAL(nref, eve::is_equal_with_equal_nans(lhs, rhs));
  }
}

TTS_CASE_TPL("Check is_equal_with_equal_nans behavior on wide and scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  wide<Type, T>          lhs([](auto i, auto) { return i; });
  logical<wide<Type, T>> ref(
      [](auto i, auto) { return eve::is_equal_with_equal_nans(Type(i), Type(2)); });

  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(lhs, Type(2)));
  TTS_EQUAL(ref, eve::is_equal_with_equal_nans(Type(2), lhs));
}

#endif
