//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <bit>

template<int N> inline constexpr auto n_zeros = eve::fix_pattern<N>( [](int, int){ return -1; } );

template<typename T, typename Env, typename Filler>
void test_zero(Env& runtime, bool verbose, Filler filler)
{
  T simd(filler);
  constexpr auto ssz = std::bit_width( std::size_t(EVE_CARDINAL) );

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
            {
              constexpr std::size_t sz = 1ULL << N;
              std::cout << "using pattern " << n_zeros<sz> << "\n";

              using type = eve::as_wide_t<T,eve::fixed<sz>>;

              type ref(typename type::value_type(0));
              TTS_EQUAL(simd[n_zeros<sz>], ref);
            };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
}

TTS_CASE_TPL("Check zeroing swizzle for arithmetic type", EVE_TYPE )
{
  test_zero<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check zeroing swizzle for logical type", EVE_TYPE )
{
  test_zero<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3 == 0; } );
}
