//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_GREATER_HPP
#define IS_NOT_GREATER_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_greater.hpp>
#include <eve/constant/nan.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check is_not_greater behavior on homogeneous wide",
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
  logical<wide<Type, T>> ref(
      [](auto i, auto c) { return eve::is_not_greater(Type(c - i), Type(i % 2 ? i : c - i)); });

  TTS_EQUAL(ref, eve::is_not_greater(lhs, rhs));
  if constexpr(std::is_floating_point_v<Type>)
  {
    wide<Type, T> lhs1([](auto i, auto c) { return Type(i % 3) / Type(i % 2); }),
        rhs1([](auto i, auto c) { return Type(i % 2) / Type(i % 3); });

    logical<wide<Type, T>> ref1([](auto i, auto c) {
      return eve::is_not_greater(Type(i % 3) / Type(i % 2), Type(i % 2) / Type(i % 3));
    });
    TTS_EQUAL(ref1, eve::is_not_greater(lhs1, rhs1));
  }
}

TTS_CASE_TPL("Check is_not_greater behavior on wide and scalar",
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
  logical<wide<Type, T>> refl([](auto i, auto) { return eve::is_not_greater(Type(i), Type(2)); });
  logical<wide<Type, T>> refr([](auto i, auto) { return eve::is_not_greater(Type(2), Type(i)); });

  TTS_EQUAL(refl, eve::is_not_greater(lhs, Type(2)));
  TTS_EQUAL(refr, eve::is_not_greater(Type(2), lhs));
  if constexpr(std::is_floating_point_v<Type>)
  {
    logical<wide<Type, T>> refln(
        [](auto i, auto) { return eve::is_not_greater(eve::Nan<Type>(), Type(i)); });
    logical<wide<Type, T>> refrn(
        [](auto i, auto) { return eve::is_not_greater(Type(i), eve::Nan<Type>()); });
    TTS_EQUAL(refln, eve::is_not_greater(lhs, eve::Nan<Type>()));
    TTS_EQUAL(refrn, eve::is_not_greater(eve::Nan<Type>(), lhs));
  }
}

#endif
