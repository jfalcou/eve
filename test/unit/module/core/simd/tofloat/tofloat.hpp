//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TOFLOAT_HPP
#define TOFLOAT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/tofloat.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check tofloat behavior on wide",
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
  using f_t = eve::detail::as_floating_point_t<wide<Type, T>>; 
  wide<Type, T> lhs([](auto i, auto) { return i; }); 
  f_t  ref([](auto i, auto) { return eve::tofloat(Type(i)); });
  TTS_EQUAL(ref, eve::tofloat(lhs));
}

#endif
