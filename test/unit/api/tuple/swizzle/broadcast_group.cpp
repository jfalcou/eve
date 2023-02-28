//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <bit>

//================================================================================================
// Premade pattern generator
template<std::ptrdiff_t G, std::ptrdiff_t I, std::ptrdiff_t N>
inline constexpr auto broadcast_group_n = eve::fix_pattern<N>( [](auto i, auto) { return I*G + i%G; } );

template<auto N>
using constant = std::integral_constant<decltype(N),N>;


template<typename Index, typename Group, typename T>
void bg_test(Index, Group, T simd)
{
  static constexpr auto grp = (T::size()/(1UL<<Group::value));

   T ref = [&](auto i, auto c)
          {
            auto p = broadcast_group_n<grp,Index::value,T::size()>;
            return simd.get(p(i,c));
          };

  TTS_EQUAL ( eve::broadcast_group( simd, eve::lane<grp>
                                  , eve::index<Index::value>, eve::lane<T::size()>
                                  )
            , ref
            );

  TTS_EQUAL ( eve::shuffle(simd,broadcast_group_n<grp,Index::value,T::size()>), ref );
}

//==================================================================================================
// Identity test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of broadcast swizzle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;

  eve::wide<s_t> simd = [](auto i, auto){ return s_t{ static_cast<std::int8_t>(65+i)
                                                    , static_cast<T>(i + 1)
                                                    , 1.5*i
                                                    };
                                            };

  constexpr auto ssz = std::bit_width( std::size_t(eve::wide<s_t>::size()) );

  eve::detail::for_<0,1,ssz>
  ( [&]<typename Group>(Group g)
  {
    constexpr auto v = 1ULL<<Group::value;
    eve::detail::for_<0,1,v>( [&](auto i) { bg_test(i,g,simd); } );
  }
  );
};
