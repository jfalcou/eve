//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ADD_HPP
#define ADD_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/add.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check add behavior on wide",
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

  wide<Type, T> lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return c - i; }),
    ref(T::value);

  TTS_EQUAL(ref, eve::add(lhs, rhs));
  TTS_EQUAL(ref, lhs + rhs);
}

TTS_CASE_TPL("Check add behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i; }),
    ref([](auto i, auto) { return i + Type(4); });

  TTS_EQUAL(ref, eve::add(lhs, 4));
  TTS_EQUAL(ref, eve::add(4, lhs));
  TTS_EQUAL(ref, lhs + 4);
  TTS_EQUAL(ref, 4 + lhs);
}

TTS_CASE_TPL("Check saturated_(add) behavior on wide",
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

  wide<Type, T> lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return c - i; }),
    ref(T::value);

  TTS_EQUAL(ref, eve::saturated_(eve::add)(lhs, rhs));
}

TTS_CASE_TPL("Check saturated_(add) behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i; }),
    ref([](auto i, auto) { return i + Type(4); });

  TTS_EQUAL(ref, eve::saturated_(eve::add)(lhs, 4));
  TTS_EQUAL(ref, eve::saturated_(eve::add)(4, lhs));
}


#endif
