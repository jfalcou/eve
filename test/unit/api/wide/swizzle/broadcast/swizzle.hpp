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

template<typename T, typename Env, typename Filler>
void test_broadcast(Env& runtime, bool verbose, Filler f)
{
  T simd(f);

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  [&]<std::size_t... V>(std::index_sequence<V...>)
                  {
                    ([&]()
                    {
                      std::cout << "using pattern " << eve::broadcast_n<V,sz> << "\n";
                      typename T::template reshape<eve::fixed<sz>> ref(simd[V]);
                      TTS_EQUAL((simd[eve::broadcast_n<V,sz>]), ref);
                    }(), ...);

                  }( std::make_index_sequence<sz>{} );
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}

TTS_CASE_TPL("Check broadcast swizzle for arithmetic type", EVE_TYPE )
{
  test_broadcast<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check broadcast swizzle for logical type", EVE_TYPE )
{
  test_broadcast<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3 == 0; });
}