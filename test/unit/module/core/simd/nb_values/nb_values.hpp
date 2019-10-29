//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NB_VALUES_HPP
#define NB_VALUES_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/nb_values.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check plus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using sui_t = eve::detail::as_integer_t<Type, unsigned>; 
  using ui_t = wide<sui_t, T>;
  using t_t  = wide<Type, T>; 
  t_t lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return c - i; }); 
  ui_t ref([](auto i, auto c) { return eve::nb_values(Type(i), Type(c - i)); });

  TTS_EQUAL(ref, eve::nb_values(lhs, rhs));
}

TTS_CASE_TPL("Check plus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using sui_t = eve::detail::as_integer_t<Type, unsigned>; 
  using ui_t = wide<sui_t, T>; 
  using t_t  = wide<Type, T>; 

  t_t lhs([](auto i, auto) { return i; }); 
  ui_t ref([](auto i, auto) { return eve::nb_values(Type(i), Type(2)); });

  TTS_EQUAL(ref, eve::nb_values(lhs, Type(2)));
  TTS_EQUAL(ref, eve::nb_values(Type(2), lhs));
}

#endif
