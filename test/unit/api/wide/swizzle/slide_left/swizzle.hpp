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

TTS_CASE_TPL( "Check slide_left swizzle for arithmetic type", EVE_TYPE )
{
  if constexpr(T::static_size == 1) TTS_PASS("Type is too small for swizzle.");

  T simd([](int i, int) { return 1+i; });

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << (N+1);
                if constexpr(sz <= EVE_CARDINAL)
                {
                  [&]<std::size_t... V>(std::index_sequence<V...>)
                  {
                    ([&]()
                    {
                      constexpr auto pt = eve::slide_left_n<V+1,sz,EVE_CARDINAL>;
                      std::cout << "using pattern " << pt << "\n";

                      typename T::template reshape<eve::fixed<sz>>
                      ref([=](int i, int) { return pt(i,sz) !=-1 ? simd[pt(i,sz)] : 0; } );

                      TTS_EQUAL((simd[pt]), ref);
                    }(), ...);

                  }( std::make_index_sequence<EVE_CARDINAL-1>{} );
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<6>{} );
}

TTS_CASE_TPL("Check slide_left swizzle for logical type", EVE_TYPE )
{
  eve::logical<T> simd([](int i, int) { return i%3==0; });

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << (N+1);
                if constexpr(sz <= EVE_CARDINAL)
                {
                  [&]<std::size_t... V>(std::index_sequence<V...>)
                  {
                    ([&]()
                    {
                      constexpr auto pt = eve::slide_left_n<V+1,sz,EVE_CARDINAL>;
                      std::cout << "using pattern " << pt << "\n";

                      typename eve::logical<T>::template reshape<eve::fixed<sz>>
                      ref ( [=](int i, int)
                            {
                              using value_t = typename eve::logical<T>::value_type;
                              return pt(i,sz) !=-1 ? simd[pt(i,sz)] : value_t{false};
                            }
                          );

                      TTS_EQUAL((simd[pt]), ref);
                    }(), ...);

                  }( std::make_index_sequence<EVE_CARDINAL-1>{} );
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<6>{} );
}
