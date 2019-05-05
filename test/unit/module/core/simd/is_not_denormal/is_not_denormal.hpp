//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_DENORMAL_HPP
#define IS_NOT_DENORMAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_denormal.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_denormal behavior on wide",
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

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto) { return i/2; });
    TTS_EQUAL(eve::is_not_denormal(lhs),  (eve::True<wide<Type,T>>()) );
  }
  else
  {
    Type s = eve::Smallestposval<Type>();
    wide<Type, T> lhs([s](auto i, auto) { return i%2 ? s*i : s/i; });
    logical<wide<Type, T>> ref([s](auto i, auto) { return eve::is_not_denormal(i%2 ? s*i : s/i); });

    TTS_EQUAL(eve::is_not_denormal(lhs), ref);
  }
}

TTS_CASE_TPL("Check is_not_denormal behavior on logical<wide>",
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

  logical<wide<Type, T>> lhs([](auto i, auto) { return i%2 == 1; });
  TTS_EQUAL(eve::is_not_denormal(lhs), eve::True(eve::as(lhs)));
}

#endif
