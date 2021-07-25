//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/api/udt/udt.hpp"
#include <eve/wide.hpp>
#include <utility>

//==================================================================================================
// Type & constraints over udt and wide<udt>
//==================================================================================================
TTS_CASE("Check User Defined Type properties with respect to SIMDification")
{
  TTS_CONSTEXPR_EXPECT    ( eve::product_type         <udt::grid2d> );
  TTS_CONSTEXPR_EXPECT    ( eve::scalar_value         <udt::grid2d> );
  TTS_CONSTEXPR_EXPECT_NOT( eve::integral_scalar_value<udt::grid2d> );

  TTS_CONSTEXPR_EXPECT    ( eve::simd_value<eve::wide <udt::grid2d>>);
  TTS_CONSTEXPR_EXPECT_NOT( eve::integral_simd_value  <udt::grid2d> );

  TTS_CONSTEXPR_EXPECT( eve::value<udt::grid2d>            );
  TTS_CONSTEXPR_EXPECT( eve::value<eve::wide <udt::grid2d>>);
};

//==================================================================================================
// Default constructors
//==================================================================================================
TTS_CASE("Check eve::wide<udt> default constructor")
{
  udt::grid2d p;
  TTS_EQUAL(p.x, +1);
  TTS_EQUAL(p.y, -1);

  eve::wide<udt::grid2d> vp;
  TTS_EQUAL(coord_x(vp), eve::wide<int>(+1));
  TTS_EQUAL(coord_y(vp), eve::wide<int>(-1));
};

//==================================================================================================
// Construct from a single value
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> splat constructor")
{
  eve::wide<udt::grid2d> vp{ udt::grid2d{+6,-9} };

  TTS_EQUAL(coord_x(vp), eve::wide<int>(+6));
  TTS_EQUAL(coord_y(vp), eve::wide<int>(-9));
};

//==================================================================================================
// Construct from a lambda returning an UDT
//==================================================================================================
TTS_CASE("Check eve::wide<udt> Lambda construction")
{
  eve::wide<udt::grid2d> vp = [](int i, int c) { return udt::grid2d{i,c-i-1}; };

  TTS_EQUAL(coord_x(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(coord_y(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));
};

//==================================================================================================
// Construct from a list of values
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> enumerating constructor" )
{
  constexpr auto sz = eve::wide<udt::grid2d>::size();

  auto vp = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              return eve::wide<udt::grid2d>( udt::grid2d{N,sz-N-1}...);
            }( std::make_index_sequence<sz>());

  TTS_EQUAL(coord_x(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(coord_y(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));
};

//==================================================================================================
// Construct from raw storage
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> constructor from raw storage")
{
  auto st = kumi::make_tuple( eve::wide<int>([](int i, int  ) { return i;    } )
                            , eve::wide<int>([](int i, int c) { return c-i-1;} )
                            );

  eve::wide<udt::grid2d> vp = st;

  TTS_EQUAL(coord_x(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(coord_y(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));
};

#if 0
//==================================================================================================
// Slice API
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide::slice behavior", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
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
<typename T>(eve::as<T>)
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

//==================================================================================================
// Structured bindings
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide<tuple> structured binding behavior", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t  = tuple_t<T>;
  using w2_t = eve::wide<tuple_t<T>, eve::fixed<2>>;
  using w4_t = eve::wide<tuple_t<T>, eve::fixed<4>>;
  using w8_t = eve::wide<tuple_t<T>, eve::fixed<8>>;

  auto const filler = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>('a'+i)
                                            , static_cast<T>(i + 1)
                                            , 1.5*(1+i)
                                            };
                                        };
  w2_t w2 = filler;
  w4_t w4 = filler;
  w8_t w8 = filler;

  auto[s20,s21] = w2;
  TTS_EQUAL(s20, w2.get(0));
  TTS_EQUAL(s21, w2.get(1));

  auto[s40,s41,s42,s43] = w4;
  TTS_EQUAL(s40, w4.get(0));
  TTS_EQUAL(s41, w4.get(1));
  TTS_EQUAL(s42, w4.get(2));
  TTS_EQUAL(s43, w4.get(3));

  auto[s80,s81,s82,s83,s84,s85,s86,s87] = w8;
  TTS_EQUAL(s80, w8.get(0));
  TTS_EQUAL(s81, w8.get(1));
  TTS_EQUAL(s82, w8.get(2));
  TTS_EQUAL(s83, w8.get(3));
  TTS_EQUAL(s84, w8.get(4));
  TTS_EQUAL(s85, w8.get(5));
  TTS_EQUAL(s86, w8.get(6));
  TTS_EQUAL(s87, w8.get(7));
};

#endif
