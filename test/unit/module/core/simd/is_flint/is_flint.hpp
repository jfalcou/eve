//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_FLINT_HPP
#define IS_FLINT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_flint.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_flint behavior",
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

  using l_t = logical<wide<Type, T>>;

  wide<Type, T> arg([](auto i, auto c) { return Type(c - i) / 2; });
  l_t           ref([](auto i, auto c) { return eve::is_flint(Type(c - i) / 2); });

  TTS_EQUAL(eve::is_flint(arg), ref);
}

#endif
