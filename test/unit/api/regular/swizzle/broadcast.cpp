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

template<std::size_t... V, typename S>
auto bcast_test(S d, std::index_sequence<V...>)
{
  auto check = [&]<typename I>(S simd, I idx)
  {
    constexpr auto i = I::value;
    typename S::template rescale<typename S::cardinal_type> ref(simd.get(i));
    TTS_EQUAL(eve::shuffle(simd,broadcast<i,S::size()>) , ref);
    TTS_EQUAL((eve::broadcast(simd, idx))     , ref);
  };

  (check(d,eve::index<V>), ...);
};

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
  bcast_test( data    , std::make_index_sequence<T::size()>{} );
  bcast_test( logicals, std::make_index_sequence<L::size()>{} );
};
