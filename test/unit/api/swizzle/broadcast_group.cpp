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
#include <bit>

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
    constexpr auto grp = (T::size()/(1<<g));
    eve::detail::for_<0,1,(1<<Group::value)>
    ( [&]<typename Index>(Index)
    {
      T ref = [=](auto i, auto c)
              {
                constexpr auto p = eve::broadcast_group_n<grp,Index::value,T::size()>;
                return simd.get(p(i,c));
              };

      L lref  = [=](auto i, auto c)
                {
                  constexpr auto p = eve::broadcast_group_n<grp,Index::value,T::size()>;
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
      TTS_EQUAL ( (simd[eve::broadcast_group_n<grp,Index::value,T::size()>]), ref );
      TTS_EQUAL ( (logicals[eve::broadcast_group_n<grp,Index::value,T::size()>]), lref );
    }
    );
  }
  );
};
