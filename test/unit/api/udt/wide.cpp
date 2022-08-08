//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
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
  TTS_CONSTEXPR_EXPECT    ( eve::product_type         <udt::grid2d>         );
  TTS_CONSTEXPR_EXPECT    ( eve::product_type         <udt::label_position> );
  TTS_CONSTEXPR_EXPECT    ( eve::scalar_value         <udt::grid2d>         );
  TTS_CONSTEXPR_EXPECT    ( eve::scalar_value         <udt::label_position> );
  TTS_CONSTEXPR_EXPECT_NOT( eve::integral_scalar_value<udt::grid2d>         );
  TTS_CONSTEXPR_EXPECT_NOT( eve::integral_scalar_value<udt::label_position> );

  TTS_CONSTEXPR_EXPECT    ( eve::simd_value<eve::wide <udt::grid2d>>        );
  TTS_CONSTEXPR_EXPECT    ( eve::simd_value<eve::wide <udt::label_position>>);
  TTS_CONSTEXPR_EXPECT_NOT( eve::integral_simd_value  <udt::grid2d>         );
  TTS_CONSTEXPR_EXPECT_NOT( eve::integral_simd_value  <udt::label_position> );

  TTS_CONSTEXPR_EXPECT( eve::value<udt::grid2d>                     );
  TTS_CONSTEXPR_EXPECT( eve::value<udt::label_position>             );
  TTS_CONSTEXPR_EXPECT( eve::value<eve::wide <udt::grid2d>>         );
  TTS_CONSTEXPR_EXPECT( eve::value<eve::wide <udt::label_position>> );
};

//==================================================================================================
// Sizeof
//==================================================================================================
TTS_CASE_TPL( "Check eve::wide<tuple> binary size", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using c_t = eve::cardinal_t<eve::wide<udt::grid2d>>;
  using d_t = eve::cardinal_t<eve::wide<udt::label_position>>;

  TTS_EQUAL ( sizeof(eve::wide<udt::grid2d>)
            , sizeof(kumi::tuple<eve::wide<int,c_t>,eve::wide<int,c_t>>)
            , REQUIRED
            );

  TTS_EQUAL ( sizeof(eve::wide<udt::label_position>)
            , sizeof(kumi::tuple<eve::wide<float,d_t>,eve::wide<std::uint8_t,d_t>>)
            , REQUIRED
            );
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

  eve::wide<udt::label_position> wp{ udt::label_position{42.69f, 'Z'} };

  using pos_t   = std::tuple_element_t<0,eve::wide<udt::label_position>>;
  using label_t = std::tuple_element_t<1,eve::wide<udt::label_position>>;

  TTS_EQUAL(position(wp), pos_t(42.69f) );
  TTS_EQUAL(label(wp)   , label_t('Z')  );
};

//==================================================================================================
// Construct from a lambda returning an UDT
//==================================================================================================
TTS_CASE("Check eve::wide<udt> Lambda construction")
{
  eve::wide<udt::grid2d> vp = [](int i, int c) { return udt::grid2d{i,c-i-1}; };

  TTS_EQUAL(get<0>(vp), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(get<1>(vp), eve::wide<int>([](int i, int c) { return c-i-1;} ));

  eve::wide<udt::label_position> wp = [](int i, int )
  {
    return udt::label_position{1.f/(1+i),std::uint8_t('A'+i)};
  };

  using pos_t   = std::tuple_element_t<0,eve::wide<udt::label_position>>;
  using label_t = std::tuple_element_t<1,eve::wide<udt::label_position>>;

  TTS_EQUAL(position(wp), pos_t  ([](int i, int  ) { return 1.f/(i+1);            }) );
  TTS_EQUAL(label(wp)   , label_t([](int i, int  ) { return std::uint8_t('A'+i);  }) );
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
// Construct from piecewise construction
//==================================================================================================
TTS_CASE( "Check eve::wide<udt> constructor from piecewise data")
{
  int data[eve::wide<int>::size()];
  for(auto& e: data) e = 9;

  eve::wide<udt::grid2d> vls ( [](auto i, auto) { return i; }
                            , 77
                            );

  eve::wide<udt::grid2d> vwl( eve::wide<int>{44}
                            , [](auto i, auto) { return i*2; }
                            );

  eve::wide<udt::grid2d> vpl( &data[0]
                            , [](auto i, auto) { return i-1; }
                            );

  TTS_EQUAL(get<0>(vls), eve::wide<int>([](int i, int  ) { return i;    } ));
  TTS_EQUAL(get<1>(vls), eve::wide<int>(77 ));

  TTS_EQUAL(get<0>(vwl), eve::wide<int>(44));
  TTS_EQUAL(get<1>(vwl), eve::wide<int>([](int i, int  ) { return i*2; } ));

  TTS_EQUAL(get<0>(vpl), eve::wide<int>(9));
  TTS_EQUAL(get<1>(vpl), eve::wide<int>([](int i, int  ) { return i-1; } ));
};

TTS_CASE_TPL( "Check eve::wide extract<Idx...>", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<udt::label_position>;
  using c_t = eve::cardinal_t<w_t>;

  auto gen_f  = [](auto i, auto) { return 1.f/(1+i); };
  auto gen_i8 = [](auto i, auto) { return std::uint8_t('A'+i); };

  w_t w(gen_f,gen_i8);

  eve::wide<kumi::tuple<std::uint8_t,float>, c_t> revert(gen_i8,gen_f);

  eve::wide<kumi::tuple<std::uint8_t,float,std::uint8_t>, eve::cardinal_t<w_t>>
  mirror(gen_i8,gen_f,gen_i8);

  TTS_EQUAL ( revert, (eve::get<1,0>(w)) );
  TTS_EQUAL ( mirror, (eve::get<1,0,1>(w)) );
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
    TTS_PASS("Type is too half_c to be split.");
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
