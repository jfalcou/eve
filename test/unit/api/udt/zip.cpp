//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/api/udt/udt.hpp"

#include <eve/module/core/regular/zip.hpp>


//==================================================================================================
// Construct from multiple existing wides
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide tuple like constructor", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  constexpr auto sz = T::size();
  using wide_grid   = eve::wide<udt::grid2d, eve::fixed<T::size()>>;

  auto vp = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              return wide_grid( udt::grid2d{N,sz-N-1}...);
            }( std::make_index_sequence<sz>());

  using w0_t = std::tuple_element_t<0, wide_grid>;
  using w1_t = std::tuple_element_t<1, wide_grid>;

  w0_t wx = [](auto i, auto  ) { return i;      };
  w1_t wy = [](auto i, auto c) { return c-1-i;  };

  TTS_EQUAL(vp, eve::zip(eve::as<udt::grid2d>(),wx,wy) );
  TTS_EQUAL(vp.get(0), eve::zip(eve::as<udt::grid2d>(),wx.get(0),wy.get(0)) );
};
