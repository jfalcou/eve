//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPONENT_HPP
#define EXPONENT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/exponent.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check exponent behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using i_t =  eve::detail::as_integer_t<Type>; 
  wide<Type, T> lhs([](int i, int) { return i % 2 ? 10*i + 2 : -10*i - 2; }); 
  wide<i_t,  T> ref([](int i, int) { return eve::exponent(Type(i % 2 ? 10*i + 2 : -10*i - 2)); });
  TTS_EQUAL(ref, eve::exponent(lhs));
}

#endif
