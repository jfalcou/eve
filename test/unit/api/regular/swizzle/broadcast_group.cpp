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

//================================================================================================
// Premade pattern generator
template<std::ptrdiff_t G, std::ptrdiff_t I, std::ptrdiff_t N>
inline constexpr auto broadcast_group_n = eve::fix_pattern<N>( [](auto i, auto) { return I*G + i%G; } );

template<typename Index, typename Group, typename T, typename L>
void bg_test(Index, Group, T simd, L logicals)
{
  static constexpr auto grp = (T::size()/(1ULL<<Group::value));

  T ref = [=](auto i, auto c)
          {
            auto p = broadcast_group_n<grp,Index::value,T::size()>;
            return simd.get(p(i,c));
          };

  L lref  = [=](auto i, auto c)
            {
              auto p = broadcast_group_n<grp,Index::value,T::size()>;
              return logicals.get(p(i,c));
            };

  TTS_EQUAL ( eve::broadcast_group( simd, eve::lane<grp>
                                  , eve::index<Index::value>, eve::lane<T::size()>
                                  )
            , ref
            );
  TTS_EQUAL ( eve::broadcast_group( logicals, eve::lane<grp>
                                  , eve::index<Index::value>, eve::lane<T::size()>
                                  )
            , lref
            );
  TTS_EQUAL ( eve::shuffle(simd,broadcast_group_n<grp,Index::value,T::size()>), ref );
  TTS_EQUAL ( eve::shuffle(logicals,broadcast_group_n<grp,Index::value,T::size()>), lref );
}

//==================================================================================================
// SWAG test
//==================================================================================================
TTS_CASE_WITH( "Check behavior of broadcast_groups swizzle"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(-50, 50)
                              , tts::logicals(1, 2)
                              )
        )
<typename T, typename L>(T simd, L logicals)
{
  constexpr auto ssz = std::bit_width( std::size_t(T::size()) );

  eve::detail::for_<0,1,ssz>
  ( [&]<typename Group>(Group g)
  {
    constexpr auto v = 1ULL<<Group::value;
    eve::detail::for_<0,1,v>( [&](auto i) { bg_test(i,g,simd,logicals); } );
  }
  );
};
