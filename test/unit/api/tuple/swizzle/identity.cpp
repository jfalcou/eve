//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <bit>

template<int N>
inline constexpr auto identity = eve::fix_pattern<N>( [](int i, int){ return i; } );

//==================================================================================================
// Identity test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of identity swizzle", eve::test::scalar::all_types)
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
                if constexpr(sz <= S::size())
                {
                  eve::as_wide_t<S,eve::fixed<sz>> ref = [&](auto i, auto) { return simd.get(i); };
                  TTS_EQUAL(eve::shuffle(simd,identity<sz>), ref);
                }
              };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
};
