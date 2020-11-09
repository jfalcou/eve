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

template<int N, int O>
inline constexpr auto partial_unpack = eve::swizzler<N>([](int i, int){ return (i/2)+O; });

template<int N, int O, bool Left>
inline constexpr auto unpack_with_zero  =  eve::swizzler<N>([](int i, int)
                                            {
                                              bool s = i%2 == 0;
                                              if constexpr(Left) return s ? -1 : (i/2)+O;
                                              else               return s ? (i/2)+O : -1;
                                            });

template<typename T, typename Env, typename Filler, typename Pattern>
void test_unpack(Env& runtime, bool verbose, Filler filler, Pattern pt)
{
  if constexpr(eve::cardinal_v<T> < 1) TTS_PASS("Type is too small to swizzle.");

  T simd(filler);
  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N>(std::integral_constant<std::size_t,N>)
              {
                constexpr std::size_t sz = 1ULL << (N+2);
                if constexpr(sz <= EVE_CARDINAL)
                {
                  [&]<std::size_t... V>(std::index_sequence<V...>)
                  {
                    ([&]()
                    {
                      auto upt = pt ( std::integral_constant<std::size_t,sz>()
                                    , std::integral_constant<std::size_t,V>()
                                    );
                      std::cout << "using pattern " << upt << "\n";

                      using type = typename T::template reshape<eve::fixed<sz>>;

                      // constexpr inside lambda leads to strange error :/
                      type ref([sz=sz,p=upt,&simd](int i, int)
                              {
                                auto idx = p(i,sz);
                                bool check = idx != -1;
                                return check ? simd[check ? idx : 0] : typename type::value_type(0);
                              }
                              );
                      TTS_EQUAL((simd[upt]), ref);
                    }(), ...);

                  }( std::make_index_sequence<EVE_CARDINAL-sz/2+1>{} );
                }
              };

    ( f(std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<5>{} );
}

TTS_CASE_TPL( "Check unpack swizzle for arithmetic type", EVE_TYPE )
{
  auto f =  [](int i, int) { return 1+i; };
  test_unpack<T>(runtime, verbose, f, [](auto sz, auto v) { return partial_unpack<sz,v>; } );
  test_unpack<T>(runtime, verbose, f, [](auto sz, auto v) { return unpack_with_zero<sz,v,true>; } );
  test_unpack<T>(runtime, verbose, f, [](auto sz, auto v) { return unpack_with_zero<sz,v,false  >; } );
}

TTS_CASE_TPL("Check unpack swizzle for logical type", EVE_TYPE )
{
  using L = eve::logical<T>;
  auto  f =  [](int i, int) { return i%3==0; };
  test_unpack<L>(runtime, verbose, f, [](auto sz, auto v) { return partial_unpack<sz,v>; } );
  test_unpack<L>(runtime, verbose, f, [](auto sz, auto v) { return unpack_with_zero<sz,v,true>; } );
  test_unpack<L>(runtime, verbose, f, [](auto sz, auto v) { return unpack_with_zero<sz,v,false  >; } );
}
