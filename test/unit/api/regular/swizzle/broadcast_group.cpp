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
#include <eve/function/broadcast_group.hpp>
#include <eve/function/shuffle.hpp>
#include <bit>

//================================================================================================
// Premade pattern generator
template<std::ptrdiff_t G, std::ptrdiff_t I, std::ptrdiff_t N>
inline constexpr auto broadcast_group_n = eve::fix_pattern<N>( [](auto i, auto) { return I*G + i%G; } );

//==================================================================================================
// SWAG test
//==================================================================================================
EVE_TEST( "Check behavior of broadcast_groups swizzle"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50)
                              , eve::test::logicals(1, 2)
                              )
        )
<typename T, typename L>(T simd, L logicals)
{
  constexpr auto ssz = std::bit_width( std::size_t(T::size()) );

  eve::detail::for_<0,1,ssz>
  ( [&]<typename Group>(Group g)
  {
    eve::detail::for_<0,1,(1<<Group::value)>
    ( [&]<typename Index>(Index)
    {
      T ref = [=](auto i, auto c)
              {
                constexpr auto grp = (T::size()/(1<<g));
                constexpr auto p = broadcast_group_n<grp,Index::value,T::size()>;
                return simd.get(p(i,c));
              };

      L lref  = [=](auto i, auto c)
                {
                  constexpr auto grp = (T::size()/(1<<g));
                  constexpr auto p = broadcast_group_n<grp,Index::value,T::size()>;
                  return logicals.get(p(i,c));
                };

      constexpr auto grp = (T::size()/(1<<g));
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
    );
  }
  );
};
