//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef PLUS_HPP
#define PLUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
<<<<<<< HEAD:test/unit/module/core/simd/ldexp/ldexp.hpp
#include <eve/function/ldexp.hpp>
=======
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/all.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/is_negative.hpp>
>>>>>>> csch:test/unit/module/core/simd/unary_minus/unary_minus.hpp
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
<<<<<<< HEAD:test/unit/module/core/simd/ldexp/ldexp.hpp
  
  wide<Type, T> lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); }),
    ref([](auto i, auto) { return  eve::ldexp(Type(i), Type(i)); });
  TTS_EQUAL(ref, eve::ldexp(lhs, rhs)); 
=======
  using t_t =  wide<Type, T>; 
  t_t lhs([](int i, int) { return i + 1; }),
      ref([](int i, int) { return eve::unary_minus(Type(i + 1)); });

  TTS_EQUAL(ref, eve::unary_minus(lhs));
  TTS_EQUAL(ref, -lhs);
  if constexpr(std::is_floating_point_v<T>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::unary_minus(t_t(0)))));
    TTS_EXPECT(eve::all(eve::is_negative(-t_t(0))));
  }
>>>>>>> csch:test/unit/module/core/simd/unary_minus/unary_minus.hpp
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

    wide<Type, T> lhs([](auto i, auto) { return i; }),
      ref([](auto i, auto) { return  eve::ldexp(Type(i), 4); });

    TTS_EQUAL(ref, eve::ldexp(lhs, 4)); 
}

#endif
