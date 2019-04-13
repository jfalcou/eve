//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP
#define IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_equal_with_equal_nans.hpp>
#include <eve/constant/nan.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_equal_with_equal_nans behavior on homogeneous wide",
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

  if constexpr(std::is_floating_point_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto c) { return i%3 ? Type(i%3)/Type(i%2) : Type(i); })
                , rhs([](auto i, auto c) { return i%2 ? Type(i%2)/Type(i%3) : Type(c-i); });

    logical<wide<Type, T>>  ref([&](auto i, auto) { return eve::is_not_equal_with_equal_nans(lhs[i],rhs[i]); });
    TTS_EQUAL(ref, eve::is_not_equal_with_equal_nans(lhs, rhs));
  }
  else
  {
    wide<Type, T> lhs([](auto i, auto c) { return i%3 ? Type(i%3): Type(i); })
                , rhs([](auto i, auto c) { return i%2 ? Type(i%2) : Type(c-i); });

    logical<wide<Type, T>>  ref([&](auto i, auto) { return eve::is_not_equal_with_equal_nans(lhs[i],rhs[i]); });
    TTS_EQUAL(ref, eve::is_not_equal_with_equal_nans(lhs, rhs));
  }
}

TTS_CASE_TPL("Check is_not_equal_with_equal_nans behavior on wide and scalar",
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

  wide<Type, T>             lhs([](auto i, auto) { return i; });
  logical< wide<Type, T> >  ref([](auto i, auto) { return eve::is_not_equal_with_equal_nans(Type(i), Type(2)); });

  TTS_EQUAL(ref, eve::is_not_equal_with_equal_nans(lhs, Type(2)));
  TTS_EQUAL(ref, eve::is_not_equal_with_equal_nans(Type(2), lhs));
}

#endif
