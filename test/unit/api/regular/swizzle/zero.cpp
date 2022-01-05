//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <eve/function/shuffle.hpp>
#include <bit>

template<int N> inline constexpr auto n_zeros = eve::fix_pattern<N>( [](int, int){ return -1; } );

//==================================================================================================
// Zero test
//==================================================================================================
EVE_TEST( "Check behavior of zeroes swizzle"
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
              constexpr std::size_t sz = 1ULL << N;
              using type = eve::as_wide_t<S,eve::fixed<sz>>;
              type ref(typename type::value_type(0));

              TTS_EQUAL(eve::shuffle(simd,n_zeros<sz>), ref);
            };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ...);
    ( f(logicals, std::integral_constant<std::size_t,I>{}), ...);

  }( std::make_index_sequence<ssz>{} );
};
