//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <bit>

//==================================================================================================
// SWAG test
//==================================================================================================
//==================================================================================================
// slide_right test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of slide_right swizzle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;
  using w_t = eve::wide<s_t>;

  constexpr auto ssz = std::bit_width( std::size_t(w_t::size()) );

  w_t data = [](auto i, auto) { return  s_t { static_cast<std::int8_t>(65+i)
                                            , static_cast<T>(i + 1)
                                            , 1.5*(1+i)
                                            };
                              };
  [&]<std::size_t... I>( std::index_sequence<I...>)
  {
    auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
            {
              constexpr std::size_t sz = 1ULL << N;
              S ref = [&](auto i, auto c)
              {
                constexpr auto p = eve::swap_adjacent_groups_pattern<sz,S::size()>;
                return simd.get(p(i,c));
              };

              constexpr auto swags = eve::swap_adjacent_groups_pattern<sz,S::size()>;
              TTS_EQUAL( eve::shuffle(simd,swags)                       , ref);
              TTS_EQUAL( eve::swap_adjacent_groups(simd, eve::lane<sz>) , ref);
            };

    ( f(data    , std::integral_constant<std::size_t,I>{}), ... );
  }( std::make_index_sequence<ssz>{} );
};
