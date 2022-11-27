//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "unit/api/udt/udt.hpp"



//==================================================================================================
// Construct from multiple existing wides
//==================================================================================================
TTS_CASE_TPL( "Check eve::wide tuple like constructor", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using wide_grid   = eve::wide<udt::grid2d, eve::fixed<T::size()>>;

  auto vp = []<std::size_t... N>(std::index_sequence<N...>)
            {
              return wide_grid( udt::grid2d{N,T::size()-N-1}...);
            }( std::make_index_sequence<T::size()>());

  using w0_t = std::tuple_element_t<0, wide_grid>;
  using w1_t = std::tuple_element_t<1, wide_grid>;

  w0_t wx = [](auto i, auto  ) { return i;      };
  w1_t wy = [](auto i, auto c) { return c-1-i;  };

  TTS_EQUAL(vp, eve::zip(eve::as<udt::grid2d>(),wx,wy) );
  TTS_EQUAL(vp.get(0), eve::zip(eve::as<udt::grid2d>(),wx.get(0),wy.get(0)) );
};
