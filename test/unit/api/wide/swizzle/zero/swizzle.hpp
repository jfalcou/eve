//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/wide.hpp>
#include <eve/logical.hpp>

template<int N> inline constexpr auto n_zeros = eve::swizzle<N>( [](int, int){ return -1; } );

TTS_CASE_TPL("Check zeroing swizzle for arithmetic type", EVE_TYPE )
{
  using type = eve::as_wide_t<T,eve::fixed<EVE_CARDINAL>>;

  T simd([](int i, int) { return 1+i; });
  type ref(typename type::value_type(0));

  TTS_EQUAL(simd[n_zeros<EVE_CARDINAL>], ref);
}

TTS_CASE_TPL("Check zeroing swizzle for logical type", EVE_TYPE )
{
  using type = eve::as_wide_t<eve::logical<T>,eve::fixed<EVE_CARDINAL>>;

  eve::logical<T> simd([](int i, int) { return i%3 == 0; });
  type ref(typename type::value_type(0));

  TTS_EQUAL(simd[n_zeros<EVE_CARDINAL>], ref);
}
