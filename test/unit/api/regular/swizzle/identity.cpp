//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <bit>

template<int N>
inline constexpr auto identity = eve::fix_pattern<N>( [](int i, int){ return i; } );

//==================================================================================================
// Identity test
//==================================================================================================
EVE_TEST( "Check behavior of identity swizzle"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50)
                              , eve::test::logicals(1, 2)
                              )
        )
<typename T, typename L>(T data, L logicals)
{
  constexpr auto ssz = std::bit_width( std::size_t(T::size()) );

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
              {
                constexpr typename S::size_type sz = 1ULL << N;
                if constexpr(sz <= S::size())
                {
                  eve::as_wide_t<S,eve::fixed<sz>> ref = [&](auto i, auto) { return simd.get(i); };
                  TTS_EQUAL(eve::shuffle(simd,identity<sz>), ref);
                }
              };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ... );
    ( f(logicals, std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
};
