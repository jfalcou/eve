//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SIGNNZ_HPP
#define SIGNNZ_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/signnz.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check signnz behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical;

  if constexpr(std::is_signed_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto) { return i%2 ? Type(i) : -Type(i); })
      ,  ref([](auto i, auto) { return eve::signnz(i%2 ? Type(i) : -Type(i)); });
    TTS_EQUAL(eve::signnz(lhs),  ref );
  }
  else
  {
    wide<Type, T> lhs([](auto i, auto) { return i%3; })
      ,  ref([](auto i, auto) { return eve::signnz(i%3); });
    TTS_EQUAL(eve::signnz(lhs),  ref );
  }
}

#endif
