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
void test_identity(Env& runtime, bool verbose, Filler filler)
{
  T simd(filler);

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << N;
                if constexpr(sz <= EVE_CARDINAL)
                {
                  std::cout << "using pattern " << eve::identity_n<sz> << "\n";

                  typename T::template reshape<eve::fixed<sz>> ref(filler);
                  TTS_EQUAL(simd[eve::identity_n<sz>], ref);
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<7>{} );
}

TTS_CASE_TPL("Check identity swizzle for arithmetic type", EVE_TYPE )
{
  test_identity<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check identity swizzle for logical type", EVE_TYPE )
{
  test_identity<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3==0; } );
}
