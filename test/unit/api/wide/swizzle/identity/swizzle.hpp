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
#include <bit>

template<int N>
inline constexpr auto identity = eve::fix_pattern<N>( [](int i, int){ return i; } );

template<typename T, typename Env, typename Filler>
void test_identity(Env& runtime, bool verbose, Filler filler)
{
  T simd(filler);

  constexpr auto ssz = std::bit_width( std::size_t(EVE_CARDINAL) );

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << identity<sz> << "\n";

                  eve::as_wide_t<T,eve::fixed<sz>> ref(filler);
                  TTS_EQUAL(simd[identity<sz>], ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
}

TTS_CASE_TPL("Check identity swizzle for arithmetic type", EVE_TYPE )
{
  test_identity<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check identity swizzle for logical type", EVE_TYPE )
{
  test_identity<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3==0; } );
}
