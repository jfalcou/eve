//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <utility>

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// Construct from a lambda returning a tuple
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide lambda constructor", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  w_t ref;

  for(int i=0;i<ref.size();++i)
  {
    ref.set(i, s_t{ static_cast<std::int8_t>('a'+i), static_cast<T>(i + 1), 1.5 * (1+i)} );
  }

  w_t simd = [&](auto i, auto)  { return s_t{ static_cast<std::int8_t>('a'+i)
                                            , static_cast<T>(i + 1)
                                            , 1.5*(1+i)
                                            };
                                };

  TTS_EQUAL(simd  , ref );
};

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
    ref.set(i, s_t{ static_cast<std::int8_t>('a'+i), static_cast<T>(i + 1), 1. + i} );
  }

  w_t simd  = [&]<std::size_t... N>(std::index_sequence<N...>)
              {
                return w_t(s_t{static_cast<std::int8_t>('a'+N), static_cast<T>(N + 1), N + 1. }...);
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

//==================================================================================================
// Construct from raw storage
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide constructor from raw storage", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using w_t = eve::wide<tuple_t<T>>;
  using s_t = typename eve::wide<tuple_t<T>>::storage_type;
  using w0_t = std::tuple_element_t<0, s_t>;
  using w1_t = std::tuple_element_t<1, s_t>;
  using w2_t = std::tuple_element_t<2, s_t>;

  TTS_EQUAL ( w_t( s_t{ w0_t('A'), w1_t(99), w2_t(13.37) } )
            , w_t(tuple_t<T>{ 'A', T{99}, 13.37 } )
            );
};

//==================================================================================================
// Slice API
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide::slice behavior", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using w_t = eve::wide<tuple_t<T>>;

  if constexpr( w_t::size() > 1 )
  {
    using split_t = typename eve::cardinal_t<w_t>::split_type;
    using ref_t   = typename w_t::template rescale<split_t>;

    w_t d = [&](auto i, auto) { return tuple_t<T> { static_cast<std::int8_t>('a'+i)
                                                  , static_cast<T>(i + 1)
                                                  , 1.5*(1+i)
                                                  };
                              };

    auto [ low, high ] = d.slice();
    TTS_EQUAL(low , ref_t([&](auto i, auto  ) { return d.get(i);     } ) );
    TTS_EQUAL(high, ref_t([&](auto i, auto c) { return d.get(i + c); } ) );

    TTS_EQUAL(d.slice(eve::lower_) , ref_t([&](auto i, auto  ) { return d.get(i);     } ) );
    TTS_EQUAL(d.slice(eve::upper_) , ref_t([&](auto i, auto c) { return d.get(i + c); } ) );
  }
  else
  {
    TTS_PASS("Type is too small to be split.");
  }
};

//==================================================================================================
// Combine API
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide::combine behavior", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  using w_t = eve::wide<tuple_t<T>>;

  if constexpr(w_t::size() < 64)
  {
    using comb_t  = typename eve::cardinal_t<w_t>::combined_type;
    using ref_t   = typename w_t::template rescale<comb_t>;

    w_t d = [&](auto i, auto) { return tuple_t<T> { static_cast<std::int8_t>('a'+i)
                                                  , static_cast<T>(i + 1)
                                                  , 1.5*(1+i)
                                                  };
                              };

    TTS_EQUAL( (ref_t{d,d})       , ref_t ( [&](auto i, auto c) { return  d.get(i % (c/2)); } ) );
    TTS_EQUAL( eve::combine(d,d)  , ref_t ( [&](auto i, auto c) { return  d.get(i % (c/2)); } ) );
  }
  else
  {
    TTS_PASS("No combine for 512 bits char wide");
  }
};
