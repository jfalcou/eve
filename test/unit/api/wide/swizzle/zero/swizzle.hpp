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

// zeroing swizzle with N values
template<std::size_t N> auto zeroing = eve::swizzler<N>( [](int, int ) { return -1; } );

TTS_CASE_TPL("Check zeroing swizzle for arithmetic type", EVE_TYPE )
{
  T simd([](int i, int) { return 1+i; });

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << zeroing<sz> << "\n";

                  typename T::template reshape<eve::fixed<sz>> ref(0);
                  TTS_EQUAL(simd[zeroing<sz>], ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}

TTS_CASE_TPL("Check zeroing swizzle for logical type", EVE_TYPE )
{
  eve::logical<T> simd([](int i, int) { return i%3==0; });

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << zeroing<sz> << "\n";

                  typename eve::logical<T>::template reshape<eve::fixed<sz>> ref(false);
                  TTS_EQUAL(simd[zeroing<sz>], ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}
