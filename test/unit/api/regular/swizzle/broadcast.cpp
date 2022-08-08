//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <bit>

template<int I, int N>
inline constexpr auto broadcast = eve::fix_pattern<N>( [](int, int){ return I; } );

//==================================================================================================
// Broadcast test
//==================================================================================================
TTS_CASE_WITH( "Check behavior of broadcast swizzle"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(-50, 50)
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
