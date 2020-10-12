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

// identity swizzle with N values
template<std::size_t N> auto identity = eve::swizzler<N>( [](int i, int ) { return i; } );

TTS_CASE_TPL("Check identity swizzle for arithmetic type", EVE_TYPE )
{
  auto const filler = [](int i, int) { return 1+i; };
  T simd(filler);

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << identity<sz> << "\n";

                  typename T::template reshape<eve::fixed<sz>> ref(filler);
                  TTS_EQUAL(simd[identity<sz>], ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}

TTS_CASE_TPL("Check identity swizzle for logical type", EVE_TYPE )
{
  auto const filler = [](int i, int) { return i%3==0; };
  eve::logical<T> simd(filler);

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << identity<sz> << "\n";

                  typename eve::logical<T>::template reshape<eve::fixed<sz>> ref(filler);
                  TTS_EQUAL(simd[identity<sz>], ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}
