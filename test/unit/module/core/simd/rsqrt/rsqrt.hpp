//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef RSQRT_HPP
#define RSQRT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/rsqrt.hpp>
#include <eve/function/simd/rec.hpp>
#include <eve/function/simd/sqr.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check rsqrt behavior on wide",
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

  wide<Type, T> lhs([](auto i, auto) { return Type(i); }),
      ref([](auto i, auto) { return eve::rsqrt(Type(i)); });

  TTS_ULP_EQUAL(ref, eve::rsqrt(lhs), 1);
}

TTS_CASE_TPL("Check raw(rsqrt) behavior on wide",
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

  wide<Type, T> lhs([](auto i, auto) { return Type(i); }),
      ref([](auto i, auto) { return eve::rsqrt(Type(i)); });

  TTS_RELATIVE_EQUAL(ref, eve::raw_(eve::rsqrt)(lhs), 1);
}

#endif
