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
#include <eve/function/slide_left.hpp>
#include <bit>

template<std::ptrdiff_t Shift, std::ptrdiff_t N>
inline constexpr
auto slide_left_pattern = eve::fix_pattern<N> ( [](auto i, auto c)
                                                {
                                                  return (i+Shift) < c ? i+Shift : eve::na_;
                                                }
                                              );

//==================================================================================================
// slide_left test
//==================================================================================================
EVE_TEST( "Check behavior of slide_left swizzle"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50)
                              , eve::test::logicals(0, 1)
                              )
        )
<typename T, typename L>(T simd, L logicals)
{
  eve::detail::for_<0,1,T::size()>
  ( [&]<typename Shift>(Shift)
  {
    T ref = [=](auto i, auto c)
            {
              return (i+Shift::value) < c ? simd.get(i+Shift::value) : 0;
            };

    L lref  = [=](auto i, auto c)
              {
                using l_t = typename L::value_type;
                return l_t{ (i+Shift::value) < c};
              };

    TTS_EQUAL(eve::slide_left(simd,eve::index<Shift::value>)    , ref);
    TTS_EQUAL(eve::slide_left(logicals,eve::index<Shift::value>), lref);

    TTS_EQUAL( (simd[slide_left_pattern<Shift::value,T::size()>])     , ref   );
    TTS_EQUAL( (logicals[slide_left_pattern<Shift::value,T::size()>]) , lref  );
  }
  );
};
