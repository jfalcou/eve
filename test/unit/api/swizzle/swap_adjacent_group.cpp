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
#include <eve/function/swap_adjacent_group.hpp>
#include <bit>

//==================================================================================================
// SWAG test
//==================================================================================================
auto swag_tests = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                            , T data, L logicals
                                            )
{
  constexpr auto ssz = std::bit_width( std::size_t(T::size()) );

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
            {
              constexpr std::size_t sz = 1ULL << N;
              S ref = [=](auto i, auto c)
              {
                constexpr auto p = eve::swap_adjacent_group_n<sz,S::size()>;
                return simd.get(p(i,c));
              };

              TTS_EQUAL( (simd[eve::swap_adjacent_group_n<sz,S::size()>]) , ref);
              TTS_EQUAL( eve::swap_adjacent_group(simd, eve::lane<sz>)    , ref);
            };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ... );
    ( f(logicals, std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
};

EVE_TEST_BED( "Check behavior of SWAGs swizzle"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50)
                                  , eve::test::logicals(1, 2)
                                  )
            , swag_tests
            );
