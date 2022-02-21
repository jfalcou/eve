//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <utility>

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// if_else
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide<tuple> if_else", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;
  using c_t = eve::cardinal_t<w_t>;

  w_t lhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%3)
                                            , static_cast<T>(i%5)
                                            , i%2 ? -1.5 : 1.5
                                            };
                              };

  w_t rhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%4)
                                            , static_cast<T>(i%2)
                                            , i%3 ? -1.5 : 1.5
                                            };
                              };

  eve::logical<eve::wide<float,c_t>> mask = [](auto i, auto) { return i%2 == 1; };

  w_t ref_mask = [&](int i, int) { return mask.get(i) ? lhs.get(i) : rhs.get(i); };
  TTS_EQUAL( eve::if_else(mask, lhs,rhs), ref_mask );

  w_t ref_t0 = [&](int i, int) { return mask.get(i) ? lhs.get(i) : s_t{0,0,0}; };
  TTS_EQUAL( eve::if_else(mask, lhs, eve::zero ), ref_t0 );
  TTS_EQUAL( eve::if_else(mask, lhs, s_t{0,0,0}), ref_t0 );

  w_t ref_0f = [&](int i, int) { return mask.get(i) ? s_t{0,0,0} : rhs.get(i) ; };
  TTS_EQUAL( eve::if_else(mask, eve::zero , rhs), ref_0f );
  TTS_EQUAL( eve::if_else(mask, s_t{0,0,0}, rhs), ref_0f );
};

//==================================================================================================
// replace_ignored
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide<tuple> replace_ignored", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  w_t lhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%3)
                                            , static_cast<T>(i%5)
                                            , i%2 ? -1.5 : 1.5
                                            };
                              };

  w_t rhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%4)
                                            , static_cast<T>(i%2)
                                            , i%3 ? -1.5 : 1.5
                                            };
                              };

  w_t ref_mask = [&](int i, int c) { return i < c/2 ? lhs.get(i) : rhs.get(i); };
  TTS_EQUAL( eve::replace_ignored(lhs, eve::ignore_last(lhs.size()/2), rhs), ref_mask );

  w_t ref_0 = [&](int i, int c) { return i < c/2 ? lhs.get(i) : s_t{0,0,0}; };
  TTS_EQUAL( eve::replace_ignored(lhs, eve::ignore_last(lhs.size()/2), eve::zero), ref_0 );
  TTS_EQUAL( eve::replace_ignored(lhs, eve::ignore_last(lhs.size()/2), s_t{0,0,0}), ref_0 );
};
