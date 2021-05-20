//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

template<typename T>
using tuple_t = kumi::tuple<char,T,double>;

//==================================================================================================
// Construct from a list of values
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide enumerating constructor", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  w_t ref;

  for(int i=0;i<ref.size();++i)
  {
    ref.set(i, s_t{ static_cast<char>('a'+i), static_cast<T>(i + 1), 1. + i} );
  }

  w_t simd  = [&]<std::size_t... N>(std::index_sequence<N...>)
              {
                return w_t(s_t{static_cast<char>('a'+N), static_cast<T>(N + 1), N + 1. }...);
              }( std::make_index_sequence<w_t::size()>());

  TTS_EQUAL(simd  , ref );
};

//==================================================================================================
// Construct from a single value
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide splat constructor", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using w_t = eve::wide<tuple_t<T>>;

  TTS_EQUAL ( w_t(tuple_t<T>{ 'z', T{69}, 13.37 })
            , w_t([](auto, auto) { return tuple_t<T>{ 'z', T{69}, 13.37 }; } )
            );
};

