//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FMS_HPP
#define FMS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/fms.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check fms behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto  ) { return i; }),
                arg1([](auto i, auto c) { return c; }),
    arg2([](auto i, auto c) { return Type(c - i); }),
    ref ([](auto i, auto c) { return Type(i)*c - Type(c-i); });
  TTS_EQUAL(ref, eve::fms(arg0, arg1, arg2));
}

TTS_CASE_TPL("Check fms behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto  ) { return i; }),
                arg1([](auto i, auto c) { return c; }),
                arg2([](auto i, auto c) { return c - i; }),
    refvvs ([](auto i, auto c) { return i*c - Type(4); }),
    refvss ([](auto i, auto c) { return i*10 - Type(4); }),
    refvsv ([](auto i, auto c) { return i*10 - Type(c-i); }),
    refsvs ([](auto i, auto c) { return 5*c - Type(4); }),
    refssv ([](auto i, auto c) { return 5*10 - Type(c-i); }),
    refsvv ([](auto i, auto c) { return 5*c - Type(c-i); });

  TTS_EQUAL(refvvs, eve::fms(arg0, arg1 , 4   ));
  TTS_EQUAL(refvss, eve::fms(arg0, 10   , 4   ));
  TTS_EQUAL(refvsv, eve::fms(arg0, 10   , arg2));
  TTS_EQUAL(refsvs, eve::fms(5   , arg1 , 4   ));
  TTS_EQUAL(refssv, eve::fms(5   , 10   , arg2));
  TTS_EQUAL(refsvv, eve::fms(5   , arg1 , arg2));
}

#endif
