//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef RSHR_HPP
#define RSHR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/rshr.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check rshr behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using i_t = eve::detail::as_integer_t<Type, signed>;

  std::ptrdiff_t n = sizeof(Type) * 8 - 1;
  wide<Type, T>  lhs([](int i, int c) { return c - i; }),
      ref([n](int i, int c) { return eve::rshr(Type(c - i), (i - c / 2) % n); });
  wide<i_t, T> rhs([n](int i, int c) { return (i - c / 2) % n; });
  TTS_EQUAL(ref, eve::rshr(lhs, rhs));
}

TTS_CASE_TPL("Check rshr behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  int           rhs = sizeof(Type) * 4;
  wide<Type, T> lhs([](int i, int c) { return c - i; });
  wide<Type, T> ref1([rhs](int i, int c) { return eve::rshr(Type(c - i), rhs); }),
      ref2([rhs](int i, int c) { return eve::rshr(Type(c - i), -rhs); });

  TTS_EQUAL(ref1, eve::rshr(lhs, rhs));
  TTS_EQUAL(ref2, eve::rshr(lhs, -rhs));
}

#endif
