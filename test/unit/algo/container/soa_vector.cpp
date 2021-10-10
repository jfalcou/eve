//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/algo/container/soa_vector.hpp>
#include "unit/api/udt/udt.hpp"
#include <memory>

using t_t = kumi::tuple<int,float,char>;

TTS_CASE("Check soa_vector default ctor")
{
  eve::algo::soa_vector<t_t>          empty_tuple;
  eve::algo::soa_vector<udt::grid2d>  empty_udt;

  TTS_EQUAL ( empty_tuple.size() , 0ULL );
  TTS_EXPECT( empty_tuple.empty()       );

  TTS_EQUAL ( empty_udt.size(), 0ULL  );
  TTS_EXPECT( empty_udt.empty()       );
}

TTS_CASE("Check soa_vector sized ctor")
{
  eve::algo::soa_vector<t_t>          tuple_vector( 37 );
  eve::algo::soa_vector<udt::grid2d>  udt_vector( 37 );

  TTS_EQUAL     ( tuple_vector.size() , 37ULL );
  TTS_EXPECT_NOT( tuple_vector.empty()        );

  TTS_EQUAL ( udt_vector.size(), 37ULL);
  TTS_EXPECT_NOT( udt_vector.empty()  );

  // grid2d has some specific default
  TTS_EQUAL( get<0>(udt_vector.get(0)), +1  );
  TTS_EQUAL( get<1>(udt_vector.get(0)), -1  );
  TTS_EQUAL( udt_vector.get(0), udt::grid2d{});
}

TTS_CASE("Check soa_vector sized ctor with default value")
{
  eve::algo::soa_vector<t_t>          tuple_vector( 71, t_t{13,3.7f,'Z'} );
  eve::algo::soa_vector<udt::grid2d>  udt_vector  ( 71, udt::grid2d{4,19} );

  TTS_EQUAL     ( tuple_vector.size() , 71ULL   );
  TTS_EXPECT_NOT( tuple_vector.empty()          );
  TTS_EQUAL( get<0>(tuple_vector.get(0)), 13    );
  TTS_EQUAL( get<1>(tuple_vector.get(0)), 3.7f  );
  TTS_EQUAL( get<2>(tuple_vector.get(0)), 'Z'   );

  TTS_EQUAL ( udt_vector.size(), 71ULL);
  TTS_EXPECT_NOT( udt_vector.empty()  );
  TTS_EQUAL( get<0>(udt_vector.get(0)), 4 );
  TTS_EQUAL( get<1>(udt_vector.get(0)), 19);
}

TTS_CASE("Check soa_vector initializer list ctor")
{
  eve::algo::soa_vector<t_t>          tuple_vector  = { t_t{1,2.3f  ,'4'}
                                                , t_t{5,6.7f  ,'8'}
                                                , t_t{9,10.11f,'X'}
                                                };

  eve::algo::soa_vector<udt::grid2d>  udt_vector    = { udt::grid2d{1,2}
                                                , udt::grid2d{3,4}
                                                , udt::grid2d{5,8}
                                                };
  TTS_EQUAL(tuple_vector.size(), 3ULL );
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));
  TTS_EQUAL(tuple_vector.get(1), (t_t{5,6.7f  ,'8'}));
  TTS_EQUAL(tuple_vector.get(2), (t_t{9,10.11f,'X'}));

  TTS_EQUAL(udt_vector.size(), 3ULL );
  TTS_EQUAL(udt_vector.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(udt_vector.get(1), (udt::grid2d{3,4}));
  TTS_EQUAL(udt_vector.get(2), (udt::grid2d{5,8}));
}

TTS_CASE("Check soa_vector::clear behavior")
{
  eve::algo::soa_vector<t_t>          tuple_vector(71);
  eve::algo::soa_vector<udt::grid2d>  udt_vector  (71);

  TTS_EQUAL     ( tuple_vector.size() , 71ULL   );
  TTS_EXPECT_NOT( tuple_vector.empty()          );

  tuple_vector.clear();

  TTS_EQUAL     ( tuple_vector.size() , 0ULL  );
  TTS_EXPECT    ( tuple_vector.empty()        );

  TTS_EQUAL     ( udt_vector.size(), 71ULL);
  TTS_EXPECT_NOT( udt_vector.empty()  );

  udt_vector.clear();

  TTS_EQUAL     ( udt_vector.size(), 0ULL);
  TTS_EXPECT    ( udt_vector.empty()  );
}

TTS_CASE("Check soa_vector::swap behavior")
{
  eve::algo::soa_vector<t_t>          tv1  =  { t_t{1,2.3f  ,'4'}
                                        , t_t{5,6.7f  ,'8'}
                                        , t_t{9,10.11f,'X'}
                                        }
                              , tv2;

  eve::algo::soa_vector<udt::grid2d>  uv1 = { udt::grid2d{1,2}
                                      , udt::grid2d{3,4}
                                      , udt::grid2d{5,8}
                                      }
                              , uv2;

  TTS_EQUAL(tv1.size(), 3ULL );
  TTS_EQUAL(tv2.size(), 0ULL );

  swap(tv1, tv2);

  TTS_EQUAL(tv1.size(), 0ULL );
  TTS_EQUAL(tv2.size(), 3ULL );

  TTS_EQUAL(tv2.get(0), (t_t{1,2.3f  ,'4'}));
  TTS_EQUAL(tv2.get(1), (t_t{5,6.7f  ,'8'}));
  TTS_EQUAL(tv2.get(2), (t_t{9,10.11f,'X'}));

  TTS_EQUAL(uv1.size(), 3ULL );
  TTS_EQUAL(uv2.size(), 0ULL );

  swap(uv1, uv2);

  TTS_EQUAL(uv1.size(), 0ULL );
  TTS_EQUAL(uv2.size(), 3ULL );

  TTS_EQUAL(uv2.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(uv2.get(1), (udt::grid2d{3,4}));
  TTS_EQUAL(uv2.get(2), (udt::grid2d{5,8}));
}

TTS_CASE("Check soa_vector::push_back behavior")
{
  eve::algo::soa_vector<t_t>          tvref  =  { t_t{1,2.3f  ,'4'}
                                          , t_t{5,6.7f  ,'8'}
                                          , t_t{9,10.11f,'X'}
                                          }
                              , tv;

  eve::algo::soa_vector<udt::grid2d>  uvref = { udt::grid2d{1,2}
                                        , udt::grid2d{3,4}
                                        , udt::grid2d{5,8}
                                        }
                              , uv;

  TTS_EQUAL(tv.size(), 0ULL );

  tv.push_back( t_t{1,2.3f  ,'4'} );
  tv.push_back( t_t{5,6.7f  ,'8'} );
  tv.push_back( t_t{9,10.11f,'X'} );

  TTS_EQUAL(tv, tvref);

  TTS_EQUAL(uv.size(), 0ULL );

  uv.push_back( udt::grid2d{1,2} );
  uv.push_back( udt::grid2d{3,4} );
  uv.push_back( udt::grid2d{5,8} );

  TTS_EQUAL(uv, uvref);
}

TTS_CASE("Check soa_vector::pop behavior")
{
  eve::algo::soa_vector<t_t>          tv  = { t_t{1,2.3f  ,'4'}
                                      , t_t{5,6.7f  ,'8'}
                                      , t_t{9,10.11f,'X'}
                                      }
                              , tvref;

  eve::algo::soa_vector<udt::grid2d>  uv = { udt::grid2d{1,2}
                                     , udt::grid2d{3,4}
                                     , udt::grid2d{5,8}
                                     }
                              , uvref;

  TTS_EQUAL(tv.size(), 3ULL );

  tv.pop_back();
  tv.pop_back();
  tv.pop_back();

  TTS_EQUAL(tv, tvref);

  TTS_EQUAL(uv.size(), 3ULL );

  uv.pop_back();
  uv.pop_back();
  uv.pop_back();

  TTS_EQUAL(uv, uvref);
}

TTS_CASE("Check soa_vector::data behavior")
{
  eve::algo::soa_vector<t_t>          tv  = { t_t{1,2.3f  ,'4'}
                                      , t_t{5,6.7f  ,'8'}
                                      , t_t{9,10.11f,'X'}
                                      };

  eve::algo::soa_vector<udt::grid2d>  uv = { udt::grid2d{1,2}
                                     , udt::grid2d{3,4}
                                     , udt::grid2d{5,8}
                                     };

  auto tv_data = tv.data();
  for(std::size_t i = 0;i< tv.size();++i)
    TTS_EQUAL( eve::read(tv_data++), tv.get(i));

  auto uv_data = uv.data();
  for(std::size_t i = 0;i< uv.size();++i)
    TTS_EQUAL( eve::read(uv_data++), uv.get(i));
}

TTS_CASE("Check soa_vector::begin/end behavior")
{
  eve::algo::soa_vector<t_t>          tv  = { t_t{1,2.3f  ,'4'}
                                      , t_t{5,6.7f  ,'8'}
                                      , t_t{9,10.11f,'X'}
                                      };

  eve::algo::soa_vector<udt::grid2d>  uv = { udt::grid2d{1,2}
                                     , udt::grid2d{3,4}
                                     , udt::grid2d{5,8}
                                     };

  auto tv_begin = tv.begin();
  auto tv_end = tv.end();
  int i = 0;
  while(tv_begin != tv_end)
    TTS_EQUAL( eve::read(tv_begin++), tv.get(i++));

  auto uv_begin = uv.begin();
  auto uv_end   = uv.end();
  i = 0;
  while(uv_begin != uv_end)
    TTS_EQUAL( eve::read(uv_begin++), uv.get(i++));
}

TTS_CASE("Check types")
{
  using T        = udt::grid2d;
  using ap       = eve::aligned_ptr<int,       eve::fixed<64 / sizeof(int)>>;
  using const_ap = eve::aligned_ptr<int const, eve::fixed<64 / sizeof(int)>>;

  using v = eve::algo::soa_vector<udt::grid2d>;
  TTS_TYPE_IS(v::pointer,               (eve::algo::views::zip_iterator<int*,       int*>));
  TTS_TYPE_IS(v::const_pointer,         (eve::algo::views::zip_iterator<int const*, int const*>));
  TTS_TYPE_IS(v::pointer_aligned,       (eve::algo::views::zip_iterator<ap,   ap>));
  TTS_TYPE_IS(v::const_pointer_aligned, (eve::algo::views::zip_iterator<const_ap,   const_ap>));

  TTS_TYPE_IS(v::iterator,               (eve::algo::views::converting_iterator<v::pointer,               T>));
  TTS_TYPE_IS(v::const_iterator,         (eve::algo::views::converting_iterator<v::const_pointer,         T>));
  TTS_TYPE_IS(v::iterator_aligned,       (eve::algo::views::converting_iterator<v::pointer_aligned,       T>));
  TTS_TYPE_IS(v::const_iterator_aligned, (eve::algo::views::converting_iterator<v::const_pointer_aligned, T>));
}

TTS_CASE("erase(pos)")
{
  using grids = eve::algo::soa_vector<udt::grid2d>;
  grids v {
    udt::grid2d{0, 0}, udt::grid2d{1, 1}, udt::grid2d{2, 2},
  };

  grids expected { v.get(0), v.get(2) };

  grids::iterator pos = v.erase(v.begin() + 1);
  TTS_EQUAL(v, expected);
  TTS_EQUAL((pos - v.begin()), 1);

  expected.pop_back();
  pos = v.erase(v.cbegin() + 1);
  TTS_EQUAL(v, expected);
  TTS_EQUAL((pos - v.begin()), 1);

  expected.pop_back();

  // We might want to return a iterator_aligned here but w/e
  pos = v.erase(v.begin_aligned());
  TTS_EQUAL(v, expected);
  TTS_EQUAL((pos - v.begin()), 0);

  v.push_back({1, 1});

  pos = v.erase(v.begin_aligned());
  TTS_EQUAL(v, expected);
  TTS_EQUAL((pos - v.begin()), 0);
}

TTS_CASE("erase(f, l)")
{
  using grids = eve::algo::soa_vector<udt::grid2d>;
  grids v {
    udt::grid2d{0, 0}, udt::grid2d{1, 1},
    udt::grid2d{2, 2}, udt::grid2d{3, 3},
  };

  grids::iterator pos;

  // empty range
  {
    pos = v.erase(v.begin(), v.begin());
    TTS_EQUAL(v.size(), 4u);
    TTS_EQUAL(pos, v.begin());

    pos = v.erase(v.cbegin(), v.cbegin());
    TTS_EQUAL(v.size(), 4u);
    TTS_EQUAL(pos, v.begin());

    pos = v.erase(v.begin_aligned(), v.begin());
    TTS_EQUAL(v.size(), 4u);
    TTS_EQUAL(pos, v.begin());

    pos = v.erase(v.cbegin_aligned(), v.cbegin());
    TTS_EQUAL(v.size(), 4u);
    TTS_EQUAL(pos, v.begin());
  }

  // last 2
  {
    grids expected { udt::grid2d{0, 0}, udt::grid2d{1, 1} };

    pos = v.erase(v.cbegin() + 2, v.cend());
    TTS_EQUAL(expected, v);
    TTS_EQUAL(pos, v.end());
  }

  v.push_back(udt::grid2d{2, 2});

  // middle
  {
    grids expected { udt::grid2d{0, 0}, udt::grid2d{2, 2} };

    pos = v.erase(v.begin() + 1, v.begin() + 2);
    TTS_EQUAL(expected, v);
    TTS_EQUAL(pos, v.begin() + 1);
  }

  // all
  {
    pos = v.erase(v.begin_aligned(), v.end());
    TTS_EQUAL(v.size(), 0u);
    TTS_EQUAL(pos, v.begin());
  }
}
