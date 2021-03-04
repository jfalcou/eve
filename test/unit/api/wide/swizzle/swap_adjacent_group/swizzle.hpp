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
#include <eve/function/swap_adjacent_group.hpp>
#include <bit>

template<typename T, typename Env, typename Filler>
void test_swag(Env& runtime, bool verbose, Filler filler)
{
  T simd(filler);
  constexpr auto ssz = std::bit_width( std::size_t(EVE_CARDINAL) );

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
            {
              constexpr std::size_t sz = 1ULL << N;
              std::cout << "using pattern " << eve::swap_adjacent_group_n<sz,EVE_CARDINAL> << "\n";

              T ref = [=](auto i, auto c)
              {
                constexpr auto p = eve::swap_adjacent_group_n<sz,EVE_CARDINAL>;
                return filler(p(i,c),c);
              };

              TTS_EQUAL( (simd[eve::swap_adjacent_group_n<sz,EVE_CARDINAL>]), ref);
              TTS_EQUAL( eve::swap_adjacent_group(simd, eve::lane<sz>)      , ref);
            };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
}

TTS_CASE_TPL("Check swap_adjacent_group swizzle for arithmetic type", EVE_TYPE )
{
  test_swag<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check swap_adjacent_group swizzle for logical type", EVE_TYPE )
{
  test_swag<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3 == 0; } );
}
