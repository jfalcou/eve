//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>
#include <eve/module/core/regular/broadcast_group.hpp>
#include <eve/module/core/regular/shuffle.hpp>
#include <bit>

//================================================================================================
// Premade pattern generator
template<std::ptrdiff_t G, std::ptrdiff_t I, std::ptrdiff_t N>
inline constexpr auto broadcast_group_n = eve::fix_pattern<N>( [](auto i, auto) { return I*G + i%G; } );

//==================================================================================================
// Identity test
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of broadcast swizzle", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
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
    constexpr auto grp = (eve::wide<s_t>::size()/(1<<g));
    eve::detail::for_<0,1,(1<<Group::value)>
    ( [&]<typename Index>(Index)
    {
      eve::wide<s_t> ref = [&](auto i, auto c)
              {
                constexpr auto p = broadcast_group_n<grp,Index::value,eve::wide<s_t>::size()>;
                return simd.get(p(i,c));
              };

      TTS_EQUAL ( eve::broadcast_group( simd, eve::lane<grp>
                                      , eve::index<Index::value>, eve::lane<eve::wide<s_t>::size()>
                                      )
                , ref
                );

      TTS_EQUAL ( eve::shuffle(simd,broadcast_group_n<grp,Index::value,eve::wide<s_t>::size()>), ref );
    }
    );
  }
  );
};
