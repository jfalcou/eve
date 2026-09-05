//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/algo.hpp>
#include "unit/api/udt/udt.hpp"
#include <memory>

using t_t = kumi::tuple<int,float,std::int8_t>;
using n_t = kumi::tuple<int,kumi::tuple<float,std::int8_t>,double>;

TTS_CASE("Check types")
{
  using T        = udt::grid2d;
  using ap       = eve::aligned_ptr<int,       eve::fixed<64 / sizeof(int)>>;
  using const_ap = eve::aligned_ptr<int const, eve::fixed<64 / sizeof(int)>>;

  using v = eve::algo::soa_vector<udt::grid2d>;

  using base_pointer                = eve::algo::views::zip_iterator<int*,       int*>;
  using base_const_pointer          = eve::algo::views::zip_iterator<int const*, int const*>;
  using base_pointer_aligned        = eve::algo::views::zip_iterator<ap,   ap>;
  using base_const_pointer_aligned  = eve::algo::views::zip_iterator<const_ap,   const_ap>;

  TTS_TYPE_IS(v::iterator,               (eve::algo::views::converting_iterator<base_pointer,               T>));
  TTS_TYPE_IS(v::const_iterator,         (eve::algo::views::converting_iterator<base_const_pointer,         T>));
  TTS_TYPE_IS(v::iterator_aligned,       (eve::algo::views::converting_iterator<base_pointer_aligned,       T>));
  TTS_TYPE_IS(v::const_iterator_aligned, (eve::algo::views::converting_iterator<base_const_pointer_aligned, T>));

  TTS_TYPE_IS(v::pointer,               v::iterator,             );
  TTS_TYPE_IS(v::const_pointer,         v::const_iterator,       );
  TTS_TYPE_IS(v::pointer_aligned,       v::iterator_aligned,     );
  TTS_TYPE_IS(v::const_pointer_aligned, v::const_iterator_aligned);

  TTS_CONSTEXPR_EXPECT((std::convertible_to<v::iterator, v::const_iterator>));
  TTS_CONSTEXPR_EXPECT((std::convertible_to<v::pointer,  v::const_pointer>));
};

TTS_CASE("Check soa_vector default ctor")
{
  eve::algo::soa_vector<t_t>          empty_tuple;
  eve::algo::soa_vector<n_t>          empty_nested;
  eve::algo::soa_vector<udt::grid2d>  empty_udt;

  TTS_EQUAL ( empty_tuple.size() , 0ULL );
  TTS_EXPECT( empty_tuple.empty()       );

  TTS_EQUAL ( empty_nested.size(), 0ULL );
  TTS_EXPECT( empty_nested.empty()      );

  TTS_EQUAL ( empty_udt.size(), 0ULL  );
  TTS_EXPECT( empty_udt.empty()       );
};

TTS_CASE("Check soa_vector sized ctor")
{
  eve::algo::soa_vector<t_t>          tuple_vector( 37 );
  eve::algo::soa_vector<n_t>          nested_vector( 37 );
  eve::algo::soa_vector<udt::grid2d>  udt_vector( 37 );

  TTS_EQUAL     ( tuple_vector.size() , 37ULL );
  TTS_EXPECT_NOT( tuple_vector.empty()        );

  TTS_EQUAL ( nested_vector.size(), 37ULL);
  TTS_EXPECT_NOT( nested_vector.empty()  );

  TTS_EQUAL ( udt_vector.size(), 37ULL);
  TTS_EXPECT_NOT( udt_vector.empty()  );

  // grid2d has some specific default
  TTS_EQUAL( udt_vector.get(0), udt::grid2d{});
};

TTS_CASE("Check soa_vector sized ctor with default value")
{
  eve::algo::soa_vector<t_t>          tuple_vector  ( 71, t_t{13,3.7f,'Z'}        );
  eve::algo::soa_vector<n_t>          nested_vector ( 71, n_t{13,{3.7f,'Z'},0.50} );
  eve::algo::soa_vector<udt::grid2d>  udt_vector    ( 71, udt::grid2d{4,19}       );

  TTS_EQUAL     ( tuple_vector.size() , 71ULL   );
  TTS_EXPECT_NOT( tuple_vector.empty()          );
  TTS_EQUAL     ( tuple_vector.get(35), (t_t{13,3.7f,'Z'})  );

  TTS_EQUAL     ( nested_vector.size() , 71ULL   );
  TTS_EXPECT_NOT( nested_vector.empty()          );
  TTS_EQUAL     ( nested_vector.get(35), (n_t{13,{3.7f,'Z'},0.50})  );

  TTS_EQUAL     ( udt_vector.size(), 71ULL);
  TTS_EXPECT_NOT( udt_vector.empty()  );
  TTS_EQUAL     ( udt_vector.get(35), (udt::grid2d{4,19}) );
};

TTS_CASE("Check soa_vector copy ctor")
{
  eve::algo::soa_vector<t_t>          tuple_original( 71, t_t{13,3.7f,'Z'} )
                                    , tuple_copy(tuple_original);

  eve::algo::soa_vector<n_t>          nested_original( 71, n_t{13,{3.7f,'Z'},0.50} )
                                    , nested_copy(nested_original);

  eve::algo::soa_vector<udt::grid2d>  udt_original  ( 71, udt::grid2d{4,19} )
                                    , udt_copy(udt_original);

  TTS_EQUAL     ( tuple_copy.size() , 71ULL   );
  TTS_EXPECT_NOT( tuple_copy.empty()          );
  TTS_EQUAL     ( tuple_copy.get(35), (t_t{13,3.7f,'Z'})  );

  TTS_EQUAL     ( udt_copy.size(), 71ULL);
  TTS_EXPECT_NOT( udt_copy.empty()  );
  TTS_EQUAL     ( udt_copy.get(35), (udt::grid2d{4,19}) );
};

TTS_CASE("Check soa_vector initializer list ctor")
{
  eve::algo::soa_vector<t_t>          tuple_vector  = { t_t{1,2.3f  ,'4'}
                                                      , t_t{5,6.7f  ,'8'}
                                                      , t_t{9,10.11f,'X'}
                                                      };

  eve::algo::soa_vector<n_t>          nested_vector = { n_t{10,{1.2f,'A'},0.50}
                                                      , n_t{20,{2.2f,'B'},0.25}
                                                      , n_t{30,{3.1f,'C'},0.15}
                                                      };

  eve::algo::soa_vector<udt::grid2d>  udt_vector    = { udt::grid2d{1,2}
                                                      , udt::grid2d{3,4}
                                                      , udt::grid2d{5,8}
                                                      };

  TTS_EQUAL(tuple_vector.size(), 3ULL );
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));
  TTS_EQUAL(tuple_vector.get(1), (t_t{5,6.7f  ,'8'}));
  TTS_EQUAL(tuple_vector.get(2), (t_t{9,10.11f,'X'}));

  TTS_EQUAL(nested_vector.size(), 3ULL );
  TTS_EQUAL(nested_vector.get(0), (n_t{10,{1.2f,'A'},0.50}));
  TTS_EQUAL(nested_vector.get(1), (n_t{20,{2.2f,'B'},0.25}));
  TTS_EQUAL(nested_vector.get(2), (n_t{30,{3.1f,'C'},0.15}));

  TTS_EQUAL(udt_vector.size(), 3ULL );
  TTS_EQUAL(udt_vector.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(udt_vector.get(1), (udt::grid2d{3,4}));
  TTS_EQUAL(udt_vector.get(2), (udt::grid2d{5,8}));
};

TTS_CASE("Check soa_vector::data behavior")
{
  eve::algo::soa_vector<t_t>          tv  = { t_t{1,2.3f  ,'4'}
                                            , t_t{5,6.7f  ,'8'}
                                            , t_t{9,10.11f,'X'}
                                            };

  eve::algo::soa_vector<n_t>          nv  = { n_t{10,{1.2f,'A'},0.50}
                                            , n_t{20,{2.2f,'B'},0.25}
                                            , n_t{30,{3.1f,'C'},0.15}
                                            };

  eve::algo::soa_vector<udt::grid2d>  uv  = { udt::grid2d{1,2}
                                            , udt::grid2d{3,4}
                                            , udt::grid2d{5,8}
                                            };

  auto tv_data = tv.data();
  for(std::size_t i = 0;i< tv.size();++i)
    TTS_EQUAL( eve::read(tv_data++), tv.get(i));

  auto nv_data = nv.data();
  for(std::size_t i = 0;i< nv.size();++i)
    TTS_EQUAL( eve::read(nv_data++), nv.get(i));

  auto uv_data = uv.data();
  for(std::size_t i = 0;i< uv.size();++i)
    TTS_EQUAL( eve::read(uv_data++), uv.get(i));
};

TTS_CASE("Check soa_vector::begin/end behavior")
{
  eve::algo::soa_vector<t_t>          tv  = { t_t{1,2.3f  ,'4'}
                                            , t_t{5,6.7f  ,'8'}
                                            , t_t{9,10.11f,'X'}
                                            };

  eve::algo::soa_vector<n_t>          nv  = { n_t{10,{1.2f,'A'},0.50}
                                            , n_t{20,{2.2f,'B'},0.25}
                                            , n_t{30,{3.1f,'C'},0.15}
                                            };

  eve::algo::soa_vector<udt::grid2d>  uv  = { udt::grid2d{1,2}
                                            , udt::grid2d{3,4}
                                            , udt::grid2d{5,8}
                                            };

  auto tv_begin = tv.begin();
  auto tv_end = tv.end();
  int i = 0;
  while(tv_begin != tv_end)
    TTS_EQUAL( eve::read(tv_begin++), tv.get(i++));

  auto nv_begin = nv.begin();
  auto nv_end   = nv.end();
  i = 0;
  while(nv_begin != nv_end)
    TTS_EQUAL( eve::read(nv_begin++), nv.get(i++));

  auto uv_begin = uv.begin();
  auto uv_end   = uv.end();
  i = 0;
  while(uv_begin != uv_end)
    TTS_EQUAL( eve::read(uv_begin++), uv.get(i++));
};

TTS_CASE("Check soa_vector resize")
{
  eve::algo::soa_vector<t_t>          tuple_vector  = { t_t{1,2.3f  ,'4'}
                                                      , t_t{5,6.7f  ,'8'}
                                                      , t_t{9,10.11f,'X'}
                                                      };

  eve::algo::soa_vector<n_t>          nested_vector = { n_t{10,{1.2f,'A'},0.50}
                                                      , n_t{20,{2.2f,'B'},0.25}
                                                      , n_t{30,{3.1f,'C'},0.15}
                                                      };

  eve::algo::soa_vector<udt::grid2d>  udt_vector   =  { udt::grid2d{1,2}
                                                      , udt::grid2d{3,4}
                                                      , udt::grid2d{5,8}
                                                      };

  // Resize to smaller
  auto old_tuple_capacity = tuple_vector.capacity();
  tuple_vector.resize(1);
  TTS_EQUAL(tuple_vector.size()     , 1ULL );
  TTS_EQUAL(tuple_vector.capacity() , old_tuple_capacity );
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));

  auto old_nested_capacity = nested_vector.capacity();
  nested_vector.resize(2);
  TTS_EQUAL(nested_vector.size(), 2ULL );
  TTS_EQUAL(nested_vector.capacity() , old_nested_capacity );
  TTS_EQUAL(nested_vector.get(0), (n_t{10,{1.2f,'A'},0.50}));
  TTS_EQUAL(nested_vector.get(1), (n_t{20,{2.2f,'B'},0.25}));

  auto old_udt_capacity = udt_vector.capacity();
  udt_vector.resize(2);
  TTS_EQUAL(udt_vector.size(), 2ULL );
  TTS_EQUAL(udt_vector.capacity() , old_udt_capacity );
  TTS_EQUAL(udt_vector.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(udt_vector.get(1), (udt::grid2d{3,4}));

  // Resize back at size
  tuple_vector.resize(3);
  TTS_EQUAL(tuple_vector.size(), 3ULL );
  TTS_EQUAL(tuple_vector.capacity() , old_tuple_capacity );
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));
  TTS_EQUAL(tuple_vector.get(1), (t_t{}));
  TTS_EQUAL(tuple_vector.get(2), (t_t{}));

  nested_vector.resize(3);
  TTS_EQUAL(nested_vector.size(), 3ULL );
  TTS_EQUAL(nested_vector.capacity() , old_nested_capacity );
  TTS_EQUAL(nested_vector.get(0), (n_t{10,{1.2f,'A'},0.50}));
  TTS_EQUAL(nested_vector.get(1), (n_t{20,{2.2f,'B'},0.25}));
  TTS_EQUAL(nested_vector.get(2), (n_t{}));

  udt_vector.resize(3);
  TTS_EQUAL(udt_vector.size(), 3ULL );
  TTS_EQUAL(udt_vector.capacity() , old_udt_capacity );
  TTS_EQUAL(udt_vector.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(udt_vector.get(1), (udt::grid2d{3,4}));
  TTS_EQUAL(udt_vector.get(2), (udt::grid2d{}));

  // Resize to max capacity
  auto c = tuple_vector.capacity();
  tuple_vector.resize(c);
  TTS_EQUAL(tuple_vector.size(), tuple_vector.capacity() );
  TTS_EQUAL(tuple_vector.capacity() , old_tuple_capacity );
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));
  TTS_EQUAL(tuple_vector.get(1), (t_t{}));
  TTS_EQUAL(tuple_vector.get(2), (t_t{}));

  for(std::size_t i=3;i<tuple_vector.size();++i)
    TTS_EQUAL(tuple_vector.get(i), (t_t{}));

  c = nested_vector.capacity();
  nested_vector.resize(c);
  TTS_EQUAL(nested_vector.size(), nested_vector.capacity() );
  TTS_EQUAL(nested_vector.capacity() , old_nested_capacity );
  TTS_EQUAL(nested_vector.get(0), (n_t{10,{1.2f,'A'},0.50}));
  TTS_EQUAL(nested_vector.get(1), (n_t{20,{2.2f,'B'},0.25}));
  TTS_EQUAL(nested_vector.get(2), (n_t{}));

  for(std::size_t i=3;i<nested_vector.size();++i)
    TTS_EQUAL(nested_vector.get(i), (n_t{}));

  c = udt_vector.capacity();
  udt_vector.resize(c);
  TTS_EQUAL(udt_vector.size(), udt_vector.capacity() );
  TTS_EQUAL(udt_vector.capacity() , old_udt_capacity );
  TTS_EQUAL(udt_vector.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(udt_vector.get(1), (udt::grid2d{3,4}));
  TTS_EQUAL(udt_vector.get(2), (udt::grid2d{}));

  for(std::size_t i=3;i<udt_vector.size();++i)
    TTS_EQUAL(udt_vector.get(i), (udt::grid2d{}));

  // Resize over capacity
  c = tuple_vector.capacity();
  tuple_vector.resize(c+7);
  TTS_EQUAL(tuple_vector.size(), c+7);
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));

  for(std::size_t i=1;i<tuple_vector.size();++i)
    TTS_EQUAL(tuple_vector.get(i), (t_t{}));

  c = nested_vector.capacity();
  nested_vector.resize(c+7);
  TTS_EQUAL(nested_vector.size(), c+7 );
  TTS_EQUAL(nested_vector.get(0), (n_t{10,{1.2f,'A'},0.50}));
  TTS_EQUAL(nested_vector.get(1), (n_t{20,{2.2f,'B'},0.25}));
  TTS_EQUAL(nested_vector.get(2), (n_t{}));

  for(std::size_t i=3;i<nested_vector.size();++i)
    TTS_EQUAL(nested_vector.get(i), (n_t{}));

  c = udt_vector.capacity();
  udt_vector.resize(c+7);
  TTS_EQUAL(udt_vector.size(), c+7 );
  TTS_EQUAL(udt_vector.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(udt_vector.get(1), (udt::grid2d{3,4}));

  for(std::size_t i=2;i<udt_vector.size();++i)
    TTS_EQUAL(udt_vector.get(i), (udt::grid2d{}));
};

TTS_CASE("Check soa_vector shrink_to_fit")
{
  eve::algo::soa_vector<t_t>          tuple_vector  = { t_t{1,2.3f  ,'4'}
                                                      , t_t{5,6.7f  ,'8'}
                                                      , t_t{9,10.11f,'X'}
                                                      };

  eve::algo::soa_vector<n_t>          nested_vector = { n_t{10,{1.2f,'A'},0.50}
                                                      , n_t{20,{2.2f,'B'},0.25}
                                                      , n_t{30,{3.1f,'C'},0.15}
                                                      };

  eve::algo::soa_vector<udt::grid2d>  udt_vector    = { udt::grid2d{1,2}
                                                      , udt::grid2d{3,4}
                                                      , udt::grid2d{5,8}
                                                      };

  auto c = tuple_vector.capacity();
  tuple_vector.resize(7*c);
  tuple_vector.resize(3);
  tuple_vector.shrink_to_fit();

  TTS_EQUAL(tuple_vector.size()     , 3ULL );
  TTS_EQUAL(tuple_vector.capacity() , 16ULL);
  TTS_EQUAL(tuple_vector.get(0), (t_t{1,2.3f  ,'4'}));
  TTS_EQUAL(tuple_vector.get(1), (t_t{5,6.7f  ,'8'}));
  TTS_EQUAL(tuple_vector.get(2), (t_t{9,10.11f,'X'}));

  c = nested_vector.capacity();
  nested_vector.resize(7*c);
  nested_vector.resize(3);
  nested_vector.shrink_to_fit();

  TTS_EQUAL(nested_vector.size()     , 3ULL );
  TTS_EQUAL(nested_vector.capacity() , 8ULL);
  TTS_EQUAL( nested_vector.get(0), (n_t{10,{1.2f,'A'},0.50}) );
  TTS_EQUAL( nested_vector.get(1), (n_t{20,{2.2f,'B'},0.25}) );
  TTS_EQUAL( nested_vector.get(2), (n_t{30,{3.1f,'C'},0.15}) );

  c = udt_vector.capacity();
  udt_vector.resize(7*c);
  udt_vector.resize(3);
  udt_vector.shrink_to_fit();

  TTS_EQUAL(udt_vector.size()     , 3ULL );
  TTS_EQUAL(udt_vector.capacity() , 16ULL);
  TTS_EQUAL( udt_vector.get(0), (udt::grid2d{1,2}) );
  TTS_EQUAL( udt_vector.get(1), (udt::grid2d{3,4}) );
  TTS_EQUAL( udt_vector.get(2), (udt::grid2d{5,8}) );
};

TTS_CASE("Check soa_vector::clear behavior")
{
  eve::algo::soa_vector<t_t>          tuple_vector  (71);
  eve::algo::soa_vector<n_t>          nested_vector (71);
  eve::algo::soa_vector<udt::grid2d>  udt_vector    (71);

  TTS_EQUAL     ( tuple_vector.size() , 71ULL   );
  TTS_EXPECT_NOT( tuple_vector.empty()          );

  tuple_vector.clear();

  TTS_EQUAL     ( tuple_vector.size() , 0ULL  );
  TTS_EXPECT    ( tuple_vector.empty()        );

  TTS_EQUAL     ( nested_vector.size(), 71ULL);
  TTS_EXPECT_NOT( nested_vector.empty()  );

  nested_vector.clear();

  TTS_EQUAL     ( nested_vector.size(), 0ULL);
  TTS_EXPECT    ( nested_vector.empty()  );

  TTS_EQUAL     ( udt_vector.size(), 71ULL);
  TTS_EXPECT_NOT( udt_vector.empty()  );

  udt_vector.clear();

  TTS_EQUAL     ( udt_vector.size(), 0ULL);
  TTS_EXPECT    ( udt_vector.empty()  );
};

TTS_CASE("Check soa_vector::swap behavior")
{
  eve::algo::soa_vector<t_t>  tv1 = { t_t{1,2.3f  ,'4'}
                                    , t_t{5,6.7f  ,'8'}
                                    , t_t{9,10.11f,'X'}
                                    }
                            , tv2;

  eve::algo::soa_vector<n_t>  nv1 = { n_t{10,{1.2f,'A'},0.50}
                                    , n_t{20,{2.2f,'B'},0.25}
                                    , n_t{30,{3.1f,'C'},0.15}
                                    }
                              , nv2;

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

  TTS_EQUAL(nv1.size(), 3ULL );
  TTS_EQUAL(nv2.size(), 0ULL );

  swap(nv1, nv2);

  TTS_EQUAL(nv1.size(), 0ULL );
  TTS_EQUAL(nv2.size(), 3ULL );

  TTS_EQUAL(nv2.get(0), (n_t{10,{1.2f,'A'},0.50}));
  TTS_EQUAL(nv2.get(1), (n_t{20,{2.2f,'B'},0.25}));
  TTS_EQUAL(nv2.get(2), (n_t{30,{3.1f,'C'},0.15}));

  TTS_EQUAL(uv1.size(), 3ULL );
  TTS_EQUAL(uv2.size(), 0ULL );

  swap(uv1, uv2);

  TTS_EQUAL(uv1.size(), 0ULL );
  TTS_EQUAL(uv2.size(), 3ULL );

  TTS_EQUAL(uv2.get(0), (udt::grid2d{1,2}));
  TTS_EQUAL(uv2.get(1), (udt::grid2d{3,4}));
  TTS_EQUAL(uv2.get(2), (udt::grid2d{5,8}));
};

TTS_CASE("Check soa_vector::push_back behavior")
{
  eve::algo::soa_vector<t_t>  tvref = { t_t{1,2.3f  ,'4'}
                                      , t_t{5,6.7f  ,'8'}
                                      , t_t{9,10.11f,'X'}
                                      }
                              , tv;

  eve::algo::soa_vector<n_t>  nvref = { n_t{10,{1.2f,'A'},0.50}
                                      , n_t{20,{2.2f,'B'},0.25}
                                      , n_t{30,{3.1f,'C'},0.15}
                                      }
                            , nv;

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

  TTS_EQUAL(nv.size(), 0ULL );

  nv.push_back( n_t{10,{1.2f,'A'},0.50} );
  nv.push_back( n_t{20,{2.2f,'B'},0.25} );
  nv.push_back( n_t{30,{3.1f,'C'},0.15} );

  TTS_EQUAL(nv, nvref);

  TTS_EQUAL(uv.size(), 0ULL );

  uv.push_back( udt::grid2d{1,2} );
  uv.push_back( udt::grid2d{3,4} );
  uv.push_back( udt::grid2d{5,8} );

  TTS_EQUAL(uv, uvref);
};

TTS_CASE("Check soa_vector::pop behavior")
{
  eve::algo::soa_vector<t_t>    tv  = { t_t{1,2.3f  ,'4'}
                                      , t_t{5,6.7f  ,'8'}
                                      , t_t{9,10.11f,'X'}
                                      }
                              , tvref;

  eve::algo::soa_vector<n_t>  nv  = { n_t{10,{1.2f,'A'},0.50}
                                    , n_t{20,{2.2f,'B'},0.25}
                                    , n_t{30,{3.1f,'C'},0.15}
                                    }
                            , nvref;

  eve::algo::soa_vector<udt::grid2d>  uv  = { udt::grid2d{1,2}
                                            , udt::grid2d{3,4}
                                            , udt::grid2d{5,8}
                                            }
                                      , uvref;

  TTS_EQUAL(tv.size(), 3ULL );

  tv.pop_back();
  tv.pop_back();
  tv.pop_back();

  TTS_EQUAL(tv, tvref);

  TTS_EQUAL(nv.size(), 3ULL );

  nv.pop_back();
  nv.pop_back();
  nv.pop_back();

  TTS_EQUAL(nv, nvref);

  TTS_EQUAL(uv.size(), 3ULL );

  uv.pop_back();
  uv.pop_back();
  uv.pop_back();

  TTS_EQUAL(uv, uvref);
};

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
};

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
};
