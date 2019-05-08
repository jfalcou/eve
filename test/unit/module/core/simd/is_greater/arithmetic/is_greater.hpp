//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_GREATER_HPP
#define IS_GREATER_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_greater.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_greater behavior on homogeneous wide",
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

  wide<Type, T> lhs([](auto i, auto c) { return c - i; }),
                rhs([](auto i, auto c) { return i%2 ? i : c-i; });

  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::is_greater(Type(c - i), Type(i%2 ? i : c-i)); });

  TTS_EQUAL(ref, eve::is_greater(lhs, rhs));
  TTS_EQUAL(ref, (lhs >  rhs));
}

TTS_CASE_TPL("Check is_greater behavior on wide and scalar",
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
  logical< wide<Type, T> >  refl([](auto i, auto) { return eve::is_greater(Type(i), Type(2)); });
  logical< wide<Type, T> >  refr([](auto i, auto) { return eve::is_greater(Type(2), Type(i)); });

  TTS_EQUAL(refl, eve::is_greater(lhs, Type(2)));
  TTS_EQUAL(refr, eve::is_greater(Type(2), lhs));
  TTS_EQUAL(refl, lhs > 2);
  TTS_EQUAL(refr, 2 > lhs);
}

#endif
