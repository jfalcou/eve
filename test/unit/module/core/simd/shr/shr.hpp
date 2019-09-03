//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SHR_HPP
#define SHR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/shr.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check shr behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using i_t = eve::detail::as_integer_t<Type>;

  int           n = sizeof(Type) * 8 - 1;
  wide<Type, T> lhs([](auto i, auto c) { return c - i; }),
      ref([n](auto i, auto c) { return eve::shr(Type(c - i), i % n); });
  wide<i_t, T> rhs([n](auto i, auto) { return i % n; });

  TTS_EQUAL(ref, eve::shr(lhs, rhs));
  TTS_EQUAL(ref, (lhs >> rhs));
}

TTS_CASE_TPL("Check shr behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  auto          rhs = sizeof(Type) * 4;
  wide<Type, T> lhs([](auto i, auto c) { return c - i; }),
      ref([rhs](auto i, auto c) { return eve::shr(Type(c - i), rhs); });

  TTS_EQUAL(ref, eve::shr(lhs, rhs));
  TTS_EQUAL(ref, (lhs >> rhs));
}

#endif
