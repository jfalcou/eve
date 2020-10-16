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

template<int C, int N>
inline constexpr auto partial_reverse = eve::swizzler<N>([](int i, int) { return C-i-1; });

TTS_CASE_TPL("Check reverse swizzle for arithmetic type", EVE_TYPE )
{
  T simd([](int i, int) { return 1+i; });

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                // No 1 element reverse
                constexpr std::size_t sz = 1ULL << (N+1);
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << partial_reverse<T::static_size, sz> << "\n";

                  typename T::template reshape<eve::fixed<sz>> ref([](int i, int) { return T::static_size-i; });
                  TTS_EQUAL((simd[partial_reverse<T::static_size, sz>]), ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<6>{} );
}

TTS_CASE_TPL("Check reverse swizzle for logical type", EVE_TYPE )
{
  eve::logical<T> simd([](int i, int) { return i%3==0; });

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                // No 1 element reverse
                constexpr std::size_t sz = 1ULL << (N+1);
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << partial_reverse<T::static_size, sz> << "\n";

                  typename eve::logical<T>::template reshape<eve::fixed<sz>>
                  ref([](int i, int) { return (T::static_size-1-i)%3==0;} );
                  TTS_EQUAL((simd[partial_reverse<T::static_size, sz>]), ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<6>{} );
}
