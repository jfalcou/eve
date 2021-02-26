//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/logical.hpp>
#include <eve/wide.hpp>

template<int I, int N>
inline constexpr auto broadcast = eve::fix_pattern<N>( [](int, int){ return I; } );

template<typename T, typename Env, typename Filler>
void test_broadcast(Env& runtime, bool verbose, Filler filler)
{
  T simd(filler);

  auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
            {
              [&]<std::size_t... V>(std::index_sequence<V...>)
              {
                ([&]()
                {
                  eve::as_wide_t<T,eve::fixed<EVE_CARDINAL>> ref(simd.get(V));

                  TTS_EQUAL((simd[broadcast<V,EVE_CARDINAL>]), ref);
                  TTS_EQUAL( (eve::broadcast(simd, eve::index<V>)), ref);
                }(), ...);

              }( std::make_index_sequence<EVE_CARDINAL>{} );
            };

  f(std::integral_constant<std::size_t,EVE_CARDINAL>{});
}

TTS_CASE_TPL("Check broadcast swizzle for arithmetic type", EVE_TYPE )
{
  test_broadcast<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check broadcast swizzle for logical type", EVE_TYPE )
{
  test_broadcast<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3 == 0; });
}
