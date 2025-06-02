//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <bit>

template<int I, int N>
inline constexpr auto broadcast = eve::fix_pattern<N>( [](int, int){ return I; } );
TTS_CASE_TPL( "Check behavior of broadcast for scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::broadcast(T{42}), eve::wide<T>{42});

  auto f  = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              auto check = []<std::ptrdiff_t L>(eve::fixed<L>)
              {
                TTS_EQUAL(eve::broadcast(T{42},eve::lane<L>), (eve::wide<T,eve::fixed<L>>{42}));
              };

              (check(eve::lane<(1<<N)>),...);
            };

  f(std::make_index_sequence<8>{});
};

//==================================================================================================
// Broadcast test
//==================================================================================================
TTS_CASE_WITH( "Check behavior of broadcast swizzle"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::logicals(1, 2)
                              )
        )
<typename T, typename L> (T data, L logicals)
{
  auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
            {
              [&]<std::size_t... V>(std::index_sequence<V...>)
              {
                ([&]()
                {
                  typename S::template rescale<typename S::cardinal_type> ref(simd.get(V));
                  TTS_EQUAL(eve::shuffle(simd,broadcast<V,S::size()>) , ref);
                  TTS_EQUAL((eve::broadcast(simd, eve::index<V>))     , ref);
                }(), ...);

              }( std::make_index_sequence<S::size()>{} );
            };

  f(data    , std::integral_constant<std::size_t,T::size()>{});
  f(logicals, std::integral_constant<std::size_t,L::size()>{});
};
