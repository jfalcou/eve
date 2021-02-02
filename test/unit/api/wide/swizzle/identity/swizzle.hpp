//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/logical.hpp>
#include <eve/wide.hpp>

template<int N> inline constexpr auto identity = eve::swizzle<N>( [](int i, int){ return i; } );

TTS_CASE_TPL("Check identity swizzle for arithmetic type", EVE_TYPE )
{
  T simd([](int i, int) { return 1+i; });
  TTS_EQUAL(simd[identity<EVE_CARDINAL>], simd);
}

TTS_CASE_TPL("Check identity swizzle for logical type", EVE_TYPE )
{
  eve::logical<T> simd([](int i, int) { return i%3==0; });
  TTS_EQUAL(simd[identity<EVE_CARDINAL>], simd);
}
