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
#include <eve/wide.hpp>
#include <eve/logical.hpp>


template<typename T, typename Env, typename Filler>
void test_slide(Env& runtime, bool verbose, Filler filler)
{
  if constexpr(eve::cardinal_v<T> == 1) TTS_PASS("Type is too small to swizzle.");

  T simd(filler);

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
                      constexpr auto pt = eve::slide_right_n<V+1,sz,EVE_CARDINAL>;
                      std::cout << "using pattern " << pt << "\n";

                      using type = typename T::template reshape<eve::fixed<sz>>;

                      // constexpr inside lambda leads to strange error :/
                      type ref([sz=sz,pt,&simd](int i, int)
                              {
                                auto idx = pt(i,sz);
                                bool check = idx != -1;
                                return check ? simd[check ? idx : 0] : typename type::value_type(0);
                              }
                              );
                      TTS_EQUAL((simd[pt]), ref);
                    }(), ...);

                  }( std::make_index_sequence<sz-1>{} );
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<6>{} );
}

TTS_CASE_TPL( "Check slide_right swizzle for arithmetic type", EVE_TYPE )
{
  test_slide<T>(runtime, verbose, [](int i, int) { return 1+i; });
}

TTS_CASE_TPL("Check slide_right swizzle for logical type", EVE_TYPE )
{

  test_slide<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3==0; });
}
