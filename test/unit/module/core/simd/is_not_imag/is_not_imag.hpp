//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_IMAG_HPP
#define IS_NOT_IMAG_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_imag.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_imag behavior",
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

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type, T> arg([](auto i, auto c) { return c - i; });
    l_t           ref([](auto i, auto c) { return eve::is_not_imag(c - i); });
    TTS_EQUAL(ref, eve::is_not_imag(arg));
  }
  else
  {
    wide<Type, T> arg([](auto i, auto) { return i / Type(i); });
    l_t           ref([](auto i, auto c) { return eve::is_not_imag(Type(i / Type(i))); });
    TTS_EQUAL(ref, eve::is_not_imag(arg));
  }
}

#endif
