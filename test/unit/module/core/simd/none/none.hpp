//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NONE_HPP
#define NONE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/none.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/is_nez.hpp>

using eve::fixed;

TTS_CASE_TPL("Check none behavior on wide",
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

  wide<Type, T> lhs([](int i, int) { return Type(1); });

  TTS_EQUAL(false, eve::none(lhs));

  for(int j=0; j < T::value; ++j)
  {
    wide<Type, T> rhs1([j](int i, int) { return i >= j ? 0 : 1; });
    wide<Type, T> rhs2([j](int i, int) { return i <= j ? 0 : 1; });
    wide<Type, T> rhs3([j](int i, int) { return i == j ? 0 : 1; });
    wide<Type, T> rhs4([j](int i, int) { return 0; });

    TTS_EQUAL(j == 0, eve::none(rhs1));
    TTS_EQUAL(j == T::value-1, eve::none(rhs2));
    TTS_EQUAL(T::value == 1, eve::none(rhs3));

    TTS_EQUAL(true, eve::none(rhs4));
  }
}

#endif
