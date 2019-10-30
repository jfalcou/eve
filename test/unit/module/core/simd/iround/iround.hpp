//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_IROUND_HPP
#define IS_IROUND_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/iround.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/scalar/iround.hpp>
#include <eve/function/scalar/ceil.hpp>
#include <eve/function/scalar/trunc.hpp>
#include <eve/function/scalar/floor.hpp>
#include <eve/function/scalar/nearest.hpp>
using eve::fixed;

TTS_CASE_TPL("Check iround behavior on wide",
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
  using i_t = eve::detail::as_integer_t<wide<Type, T>>; 
  wide<Type, T> lhs([](auto i, auto) { return Type(i) / 3; }); 
  i_t    ref([](auto i, auto) { return eve::iround(Type(i) / 3); }),
    ref1([](auto i, auto) { return eve::iround(Type(i) / 3, eve::upward_); }),
    ref2([](auto i, auto) { return eve::iround(Type(i) / 3, eve::toward_zero_); }),
    ref3([](auto i, auto) { return eve::iround(Type(i) / 3, eve::downward_); }),
    ref4([](auto i, auto) { return eve::iround(Type(i) / 3, eve::to_nearest_); });
  
  TTS_EQUAL(ref, eve::iround(lhs));
  TTS_EQUAL(ref1, eve::iround(lhs, eve::upward_));
  TTS_EQUAL(ref2, eve::iround(lhs, eve::toward_zero_));
  TTS_EQUAL(ref3, eve::iround(lhs, eve::downward_));
  TTS_EQUAL(ref4, eve::iround(lhs, eve::to_nearest_));
}

#endif
