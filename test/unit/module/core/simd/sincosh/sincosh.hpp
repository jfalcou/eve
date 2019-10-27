//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FREXP_HPP
#define FREXP_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/sincosh.hpp>
#include <eve/wide.hpp>
#include <eve/function/load.hpp>
#include <eve/detail/meta.hpp>
#include <utility>

using eve::fixed;

TTS_CASE_TPL("Check frexp behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using t_t =  wide<Type, T>; 
  t_t lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); });
  Type m[T::value];
  Type e[T::value];
  for(int i=0; i < T::value ; ++i)
  {
    std::tie(m[i], e[i]) = eve::sincosh(Type(i));
  }
  t_t refm([m](auto i, auto){return m[i]; }); 
  t_t refe([e](auto i, auto){return e[i]; }); 
  auto [vm, ve] =  eve::sincosh(lhs); 
  TTS_EQUAL(refm, vm);
  TTS_EQUAL(refe, ve);
}

#endif
