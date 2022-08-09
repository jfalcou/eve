//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <bit>

template<int N> inline constexpr auto n_zeros = eve::fix_pattern<N>( [](int, int){ return -1; } );

//==================================================================================================
// Zero test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of zero swizzle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;

  constexpr auto ssz = std::bit_width( std::size_t(eve::wide<s_t>::size()) );

  eve::wide<s_t> data = [](auto i, auto){ return s_t{ static_cast<std::int8_t>(65+i)
                                                    , static_cast<T>(i + 1)
                                                    , 1.5*(1+i)
                                                    };
                                            };

  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
            {
              constexpr std::size_t sz = 1ULL << N;
              using type = eve::as_wide_t<S,eve::fixed<sz>>;
              type ref(s_t{'\0',T{0},0.});

              TTS_EQUAL(eve::shuffle(simd,n_zeros<sz>), ref);
            };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ...);

  }( std::make_index_sequence<ssz>{} );
};
