//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NEXT_HPP
#define NEXT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/next.hpp>
#include <eve/wide.hpp>
#include <eve/detail/meta.hpp>

using eve::fixed;

TTS_CASE_TPL("Check next behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using si_t =  eve::detail::as_integer_t<Type>; 
  using i_t =  eve::detail::as_integer_t<wide<Type, T>>; 
  wide<Type, T> lhs([](int i, int) { return i % 2 ? i + 2 : -i - 2; }),
      ref([](int i, int) { return eve::next(Type(i % 2 ? i + 2 : -i - 2)); }), 
    ref2([](int i, int) { return eve::next(Type(i % 2 ? i + 2 : -i - 2), si_t(2)); });
  i_t rhs(2); 
  TTS_EQUAL(ref, eve::next(lhs));
  TTS_EQUAL(ref2, eve::next(lhs, si_t(2)));
  TTS_EQUAL(ref2, eve::next(lhs, 2)); 
  TTS_EQUAL(ref2, eve::next(lhs, rhs)); 
}

#endif
