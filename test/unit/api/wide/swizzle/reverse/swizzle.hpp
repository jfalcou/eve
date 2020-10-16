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

template<typename T, typename Env, typename Filler>
void test_reverse(Env& runtime, bool verbose, Filler filler)
{
  T simd(filler);

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << partial_reverse<T::static_size, sz> << "\n";

                  using type = typename T::template reshape<eve::fixed<sz>>;
                  type ref([&simd](int i, int ) { return simd[simd.size()-1-i]; });

                  TTS_EQUAL((simd[partial_reverse<T::static_size, sz>]), ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}

TTS_CASE_TPL( "Check identity swizzle for arithmetic type", EVE_TYPE )
{
  test_reverse<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check identity swizzle for logical type", EVE_TYPE )
{
  test_reverse<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3==0; } );
}
