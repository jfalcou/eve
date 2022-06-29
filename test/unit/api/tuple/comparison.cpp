//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>
#include <utility>

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// Operator==
//==================================================================================================
TTS_CASE_TPL( "Check eve::wide<tuple>operator==", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;
  using l_t = eve::as_logical_t<w_t>;

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

  l_t checks = [&](auto i, auto)  { return lhs.get(i) == rhs.get(i); };

  TTS_EQUAL( (lhs == rhs), checks );
};

//==================================================================================================
// Operator!=
//==================================================================================================
TTS_CASE_TPL( "Check eve::wide<tuple>operator!=", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;
  using l_t = eve::as_logical_t<w_t>;

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

  l_t checks = [&](auto i, auto)  { return lhs.get(i) != rhs.get(i); };

  TTS_EQUAL( (lhs != rhs), checks );
};

//==================================================================================================
// Ordering
//==================================================================================================
TTS_CASE_TPL( "Check eve::wide<tuple> ordering", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  w_t lhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>('a'+i%3)
                                            , static_cast<T>(i%5)
                                            , i%2 ? -1.5 : 1.5
                                            };
                              };

  w_t rhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>('a'+i%4)
                                            , static_cast<T>(i%2)
                                            , i%3 ? -1.5 : 1.5
                                            };
                              };

  using l_t = eve::as_logical_t<w_t>;

  l_t clt = [&](auto i, auto) { return lhs.get(i) <  rhs.get(i); };
  l_t cle = [&](auto i, auto) { return lhs.get(i) <= rhs.get(i); };
  l_t cgt = [&](auto i, auto) { return lhs.get(i) >  rhs.get(i); };
  l_t cge = [&](auto i, auto) { return lhs.get(i) >= rhs.get(i); };

  TTS_EQUAL( (lhs <  rhs), clt );
  TTS_EQUAL( eve::is_less(lhs, rhs), clt );

  TTS_EQUAL( (lhs <= rhs), cle );
  TTS_EQUAL( eve::is_less_equal(lhs, rhs), cle );

  TTS_EQUAL( (lhs >  rhs), cgt );
  TTS_EQUAL( eve::is_greater(lhs, rhs), cgt );

  TTS_EQUAL( (lhs >= rhs), cge );
  TTS_EQUAL( eve::is_greater_equal(lhs, rhs), cge );
};

