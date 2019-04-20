//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_IMAG_HPP
#define IS_IMAG_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_imag.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_imag behavior",
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

  using l_t = logical<wide<Type,T>>;

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type, T>         arg([](auto i, auto c) { return c - i; });
    l_t           ref([](auto i, auto c) { return eve::is_imag(c-i); });
    TTS_EQUAL(ref, eve::is_imag(arg));
  }
  else
  {
    wide<Type, T> arg([](auto i, auto  ) { return i/Type(i); });
    l_t           ref([](auto i, auto c) { return eve::is_imag(Type(i/Type(i))); });
    TTS_EQUAL(ref, eve::is_imag(arg));
  }
}

#endif
