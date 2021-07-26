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
  TTS_EQUAL(get<0>(vp), eve::wide<int>(+1));
  TTS_EQUAL(get<1>(vp), eve::wide<int>(-1));
};

//==================================================================================================
// Construct from a single value
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> splat constructor")
{
  eve::wide<udt::grid2d> vp{ udt::grid2d{+6,-9} };

  TTS_EQUAL(get<0>(vp), eve::wide<int>(+6));
  TTS_EQUAL(get<1>(vp), eve::wide<int>(-9));
};

//==================================================================================================
// Construct from a lambda returning an UDT
//==================================================================================================
TTS_CASE("Check eve::wide<udt> Lambda construction")
{
  eve::wide<udt::grid2d> vp = [](int i, int c) { return udt::grid2d{i,c-i-1}; };

  TTS_EQUAL(get<0>(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(get<1>(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));
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

  TTS_EQUAL(get<0>(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(get<1>(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));
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

  TTS_EQUAL(get<0>(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(get<1>(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));
};

//==================================================================================================
// Slice API
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> slice behavior")
{
  using w_t = eve::wide<udt::grid2d>;

  if constexpr( w_t::size() > 1 )
  {
    using c_t = typename w_t::cardinal_type::split_type;
    constexpr int s = c_t::value;

    eve::wide<udt::grid2d>      vp  = [](int i, int c) { return udt::grid2d{  i, c  -i-1}; };
    eve::wide<udt::grid2d, c_t> vl  = [](int i, int c) { return udt::grid2d{  i, c+s-i-1}; };
    eve::wide<udt::grid2d, c_t> vh  = [](int i, int  ) { return udt::grid2d{s+i,   s-i-1}; };

    auto[lo,hi] = vp.slice();

    TTS_EQUAL(lo, vl);
    TTS_EQUAL(hi, vh);
  }
  else
  {
    TTS_PASS("Type is too small to be split.");
  }
};

//==================================================================================================
// Combine API
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> combine behavior")
{
  using w_t = eve::wide<udt::grid2d>;

  if constexpr(w_t::size() < 64)
  {
    using comb_t  = typename eve::cardinal_t<w_t>::combined_type;
    using ref_t   = typename w_t::template rescale<comb_t>;

    w_t vp = [](int i, int c) { return udt::grid2d{  i, c  -i-1}; };

    TTS_EQUAL( (ref_t{vp,vp})     , ref_t ( [&](auto i, auto c) { return vp.get(i % (c/2)); } ) );
    TTS_EQUAL( eve::combine(vp,vp), ref_t ( [&](auto i, auto c) { return vp.get(i % (c/2)); } ) );
  }
  else
  {
    TTS_PASS("No combine for 512 bits char wide");
  }
};

//==================================================================================================
// Structured bindings
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> structured binding behavior")
{
  eve::wide<udt::grid2d> vp = [](int i, int c) { return udt::grid2d{  i, c-i-1}; };

  auto[p0,p1] = vp;
  auto s0 = p0;
  auto s1 = p1;

  TTS_EQUAL(s0, eve::wide<int>{[](int i, int  ){ return i;      } } );
  TTS_EQUAL(s1, eve::wide<int>{[](int i, int c){ return c-i-1;  } } );
};
