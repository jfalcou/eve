//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TOUINT_HPP
#define TOUINT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/touint.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check touint behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using i_t = eve::detail::as_integer_t<wide<Type, T>, unsigned>;
  {
  wide<Type, T> lhs([](auto i, auto) { return i; }); 
  i_t  ref([](auto i, auto) { return eve::touint(Type(i)); });
  TTS_EQUAL(ref, eve::touint(lhs));
  }
  {
  wide<Type, T> lhs([](auto i, auto) { return i%2 ? i : -i; }); 
  i_t  ref([](auto i, auto) { return eve::pedantic_(eve::touint)(Type(i%2 ? i : -i)); });
  TTS_EQUAL(ref, eve::pedantic_(eve::touint)(lhs));
  }
}

#endif
