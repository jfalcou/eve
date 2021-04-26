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
#include <eve/function/slide_right.hpp>
#include <bit>

template<std::ptrdiff_t Shift, std::ptrdiff_t N>
inline constexpr
auto slide_right_pattern = fix_pattern<N>([](auto i, auto ){ return i<Shift ? eve::na_ : i-Shift;});

//==================================================================================================
// slide_right test
//==================================================================================================
EVE_TEST( "Check behavior of slide_right swizzle"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-50, 50)
                              , eve::test::logicals(0, 1)
                              )
        )
<typename T, typename L>(T simd, L logicals)
{
  eve::detail::for_<0,1,T::size()>
  ( [&]<typename Shift>(Shift)
  {
    T ref = [=](auto i, auto)
            {
              return (i < Shift::value) ? 0 : simd.get(i-Shift::value);
            };

    L lref  = [=](auto i, auto)
              {
                using l_t = typename L::value_type;
                return l_t{ i >= Shift::value};
              };

    TTS_EQUAL(eve::slide_right(simd,eve::index<Shift::value>)    , ref);
    TTS_EQUAL(eve::slide_right(logicals,eve::index<Shift::value>), lref);

    // TTS_EQUAL( (simd[slide_right_pattern<Shift::value,T::size()>])     , ref   );
    // TTS_EQUAL( (logicals[slide_right_pattern<Shift::value,T::size()>]) , lref  );
  }
  );
};
