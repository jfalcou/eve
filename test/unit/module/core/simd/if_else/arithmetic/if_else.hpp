//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_HPP
#define IF_ELSE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check if_else behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::is_nez;
  using eve::wide;

  wide<Type, T> cond([](auto i, auto) { return (i % 2) * i; }),
      rhs1([](auto i, auto) { return i % 2 + 1; }), rhs2([](auto i, auto) { return i % 3; });

  wide<Type, T> ref(
      [](int i, int) { return eve::if_else(Type((i % 2) * i), Type(i % 2 + 1), Type(i % 3)); });

  TTS_EQUAL(ref, eve::if_else(cond, rhs1, rhs2));         // w w w
  TTS_EQUAL(ref, eve::if_else(is_nez(cond), rhs1, rhs2)); // lw w w
}

TTS_CASE_TPL("Check if_else behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::is_nez;
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return i % 3; }),
      refsw([](int i, int) { return eve::if_else(Type(i % 3), Type(7), Type(i * (i % 2))); }),
      refws([](int i, int) { return eve::if_else(Type(i % 3), Type(i * (i % 2)), Type(8)); }),
      x([](int i, int) { return i * (i % 2); });

  TTS_EQUAL(refsw, eve::if_else(lhs, Type(7), x));         // w s w
  TTS_EQUAL(refsw, eve::if_else(is_nez(lhs), Type(7), x)); // lw s w

  TTS_EQUAL(refws, eve::if_else(lhs, x, Type(8)));         // w w s
  TTS_EQUAL(refws, eve::if_else(is_nez(lhs), x, Type(8))); // lw w s
}

#endif
