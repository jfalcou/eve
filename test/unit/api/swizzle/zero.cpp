//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <bit>

template<int N> inline constexpr auto n_zeros = eve::fix_pattern<N>( [](int, int){ return -1; } );

//==================================================================================================
// Zero test
//==================================================================================================
auto zero_tests = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                            , T data, L logicals
                                            )
{
  constexpr auto ssz = std::bit_width( std::size_t(T::size()) );

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
            {
              constexpr std::size_t sz = 1ULL << N;
              std::cout << "using pattern " << n_zeros<sz> << "\n";

              using type = eve::as_wide_t<S,eve::fixed<sz>>;
              type ref(typename type::value_type(0));

              TTS_EQUAL(simd[n_zeros<sz>], ref);
            };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ...);
    ( f(logicals, std::integral_constant<std::size_t,I>{}), ...);

  }( std::make_index_sequence<ssz>{} );
};

EVE_TEST_BED( "Check behavior of zeroes swizzle"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50)
                                  , eve::test::logicals(1, 2)
                                  )
            , zero_tests
            );
